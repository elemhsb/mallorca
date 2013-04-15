/*#include "std.h"
#include "mcu_periph/sys_time.h"
#include "led.h"
#include "mcu.h"
#include "subsystems/imu.h"
olri */

#include "mcu_periph/spi.h"
#include "mcu_periph/spi_arch_new.h"

#include "std.h"
#include "LPC21xx.h"
#include "interrupt_hw.h"
#include "armVIC.h"
#include BOARD_CONFIG

xxx

// Variables
struct spi_transaction* slave0;

// Prototypes
static void SPI1_ISR(void) __attribute__((naked));

// Defines
/* ssp input clock 468.75kHz, clock that divided by SCR+1 */
/* #define SSP_CLOCK 468750 WARM */
#define SSP_CLOCK 8000000

/* SSPCR0 settings */
#define SSP_DDS  0x07 << 0  /* data size         : 8 bits        */
#define SSP_FRF  0x00 << 4  /* frame format      : SPI           */
#define SSP_CPOL 0x00 << 6  /* clock polarity    : data captured on first clock transition */
#define SSP_CPHA 0x00 << 7  /* clock phase       : SCK idles low */
#define SSP_SCR  0x0F << 8  /* serial clock rate : divide by 16  */

/* SSPCR1 settings */
#define SSP_LBM  0x00 << 0  /* loopback mode     : disabled                  */
#define SSP_SSE  0x00 << 1  /* SSP enable        : disabled                  */
#define SSP_MS   0x00 << 2  /* master slave mode : master                    */
#define SSP_SOD  0x00 << 3  /* slave output disable : don't care when master */

#define SS_PIN   20
#define SS_IODIR IO0DIR
#define SS_IOSET IO0SET
#define SS_IOCLR IO0CLR

void spi_init( void ) {
  /* setup pins for SSP (SCK, MISO, MOSI) */
  PINSEL1 |= 2 << 2 | 2 << 4 | 2 << 6;

  /* setup SSP */
  SSPCR0 = SSP_DDS | SSP_FRF | SSP_CPOL | SSP_CPHA | SSP_SCR;
  SSPCR1 = SSP_LBM | SSP_MS | SSP_SOD;
  /* set prescaler for SSP clock */
  SSPCPSR = PCLK/SSP_CLOCK;

  return;

  /* initialize interrupt vector */
  VICIntSelect &= ~VIC_BIT(VIC_SPI1);   // SPI1 selected as IRQ
  VICIntEnable = VIC_BIT(VIC_SPI1);     // SPI1 interrupt enabled
  VICVectCntl7 = VIC_ENABLE | VIC_SPI1;
  VICVectAddr7 = (uint32_t)SPI1_ISR;    // address of the ISR

  /* configure SS pin */
 // SetBit(SS_IODIR, SS_PIN); /* pin is output  */
 // ScpUnselect();            /* pin idles high */
  // TODO: MUX PINS setzen for 74138

  /* configure DRDY pin */
  /* connected pin to EXINT */
  /*
  SPI1_DRDY_PINSEL |= SPI1_DRDY_PINSEL_VAL << SPI1_DRDY_PINSEL_BIT;
  SetBit(EXTMODE, SPI1_DRDY_EINT); // EINT is edge trigered
  SetBit(EXTPOLAR,SPI1_DRDY_EINT); // EINT is trigered on rising edge
  SetBit(EXTINT,SPI1_DRDY_EINT);   // clear pending EINT

  // initialize interrupt vector

  VICIntSelect &= ~VIC_BIT( SPI1_DRDY_VIC_IT );  // select EINT as IRQ source
  VICIntEnable = VIC_BIT( SPI1_DRDY_VIC_IT );    // enable it
  VICVectCntl11 = VIC_ENABLE | SPI1_DRDY_VIC_IT;
  VICVectAddr11 = (uint32_t)EXTINT_ISR;         // address of the ISR

  baro_scp_status = STA_UNINIT;
  */
}


void SPI1_ISR(void) {
  ISR_ENTRY();
/*
  // READ
  slave0->miso_buf[...] = SSPDR;

// TODO: unselect  ScpUnselect();
  SpiClearRti();
  SpiDisable();
*/
  VICVectAddr = 0x00000000; /* clear this interrupt from the VIC */
  ISR_EXIT();
}

void spi_rw(struct spi_transaction  * _trans) {
	// Store local copy to notify of the results

	slave0 = _trans;
	slave0->status = SPITransRunning;

	Spi2Slave0Select();
	SpiEnable();

	int pos=0;
	while( pos<slave0->length ) {
		// write to
		SSPDR = slave0->mosi_buf[pos];
		// wait while RNE
        while(!(SSPSR & (1<<2)));
        // read from
		slave0->miso_buf[pos] = SSPDR;
		pos++;
	}

	Spi2Slave0Unselect();

	// mark as available
	spi_message_received = TRUE;

	slave0->status = SPITransSuccess;
//} // while(1)
	*(slave0->ready) = 1;
}
