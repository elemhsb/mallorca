#ifndef CONFIG_HBMINI_V2_0_H
#define CONFIG_HBMINI_V2_0_H

/* Master oscillator freq.       */
#define FOSC (12000000)

/* PLL multiplier                */
#define PLL_MUL (5)

/* CPU clock freq.               */
#define CCLK (FOSC * PLL_MUL)

/* Peripheral bus speed mask 0x00->4, 0x01-> 1, 0x02 -> 2   */
#define PBSD_BITS 0x02
#define PBSD_VAL 2

/* Peripheral bus clock freq. */
#define PCLK (CCLK / PBSD_VAL)

/* Onboard LEDs */
#ifndef USE_LED_1
#define USE_LED_1 1
#endif
#define LED_1_BANK 1
#define LED_1_PIN 18 // GREEN

#ifndef USE_LED_2
#define USE_LED_2 1
#endif
#define LED_2_BANK 1
#define LED_2_PIN 19 // RED

#ifndef USE_LED_3
#define USE_LED_3 1
#endif
#define LED_3_BANK 1
#define LED_3_PIN 20 // BUZZER

#ifndef USE_LED_4
#define USE_LED_4 1
#endif
#define LED_4_BANK 1
#define LED_4_PIN 17 // FUNKIO

/*
#ifndef USE_LED_5
#define USE_LED_5 1
#endif
#define LED_5_BANK 1
#define LED_5_PIN 18

#define POWER_SWITCH_LED 1
#define POWER_SWITCH2_LED 2
*/


#ifndef USE_LED_6
#define USE_LED_6 1
#endif
#define LED_6_BANK 1
#define LED_6_PIN 25 // CAM_POWER_SWITCH

#define CAM_SWITCH_LED 6


#ifndef USE_LED_7
#define USE_LED_7 1
#endif
#define LED_7_BANK 1
#define LED_7_PIN 21	// CSSEL0

#ifndef USE_LED_8
#define USE_LED_8 1
#endif
#define LED_8_BANK 1
#define LED_8_PIN 22	// CSSEL1

#ifndef USE_LED_9
#define USE_LED_9 1
#endif
#define LED_9_BANK 1
#define LED_9_PIN 23	// CSSEL2

/* PPM : rc rx on P0.28 ( CAP0.2 ) */
// #define PPM_PINSEL PINSEL1
// #define PPM_PINSEL_VAL 0x02
// #define PPM_PINSEL_BIT 24
// #define PPM_CRI TIR_CR2I
// #define PPM_CCR_CRF TCCR_CR2_F
// #define PPM_CCR_CRR TCCR_CR2_R
// #define PPM_CCR_CRI TCCR_CR2_I
// #define PPM_CR T0CR2

/* PPM : rc rx on P0.6   war 15.08.2012*/
#define PPM_PINSEL PINSEL0
#define PPM_PINSEL_VAL 0x02
#define PPM_PINSEL_BIT 12
#define PPM_CRI TIR_CR2I
#define PPM_CCR_CRF TCCR_CR2_F
#define PPM_CCR_CRR TCCR_CR2_R
#define PPM_CCR_CRI TCCR_CR2_I
#define PPM_CR T0CR2

/* ADC */

/* select P0.13 (ADC_SPARE) as AD1.4 for ADC_0 */
#define ADC_0 AdcBank1(4)
#ifdef USE_ADC_0
#ifndef USE_AD1
#define USE_AD1
#endif
#define USE_AD1_4
#endif

/* select P0.4 (SCK_0) as AD0.6 for ADC_1 */
#define ADC_1 AdcBank0(6)
#ifdef USE_ADC_1
#ifndef USE_AD0
#define USE_AD0
#endif
#define USE_AD0_6
#endif

/* select P0.5 (MISO_0) as AD0.7 for ADC_2 */
#define ADC_2 AdcBank0(7)
#ifdef USE_ADC_2
#ifndef USE_AD0
#define USE_AD0
#endif
#define USE_AD0_7
#endif

/* select P0.6 (MOSI_0) as AD1.0 for ADC_3  war 16.8.2012 */
//#define ADC_3 AdcBank1(0)
//#ifdef USE_ADC_3
//#ifndef USE_AD1
//#define USE_AD1
//#endif
//#define USE_AD1_0
//#endif

/* battery */
/* allow to define ADC_CHANNEL_VSUPPLY in the airframe file*/
#ifndef ADC_CHANNEL_VSUPPLY
#define ADC_CHANNEL_VSUPPLY AdcBank1(6)
#ifndef USE_AD1
#define USE_AD1
#endif
#define USE_AD1_6
#endif

#define DefaultVoltageOfAdc(adc) (0.0330*adc)

/* baro */
/*#define ADC_CHANNEL_BARO AdcBank1(2)
#ifndef USE_AD1
#define USE_AD1
#endif
#define USE_AD1_2
*/


/* PWM5 on CAM connector */
/* P0.21 */
//#define PWM0_PINSEL PINSEL1
//#define PWM0_PINSEL_VAL 0x01
//#define PWM0_PINSEL_BIT 10

/* PWM2 on SPI connector */
/* P0.7 */
#define PWM1_PINSEL PINSEL0
#define PWM1_PINSEL_VAL 0x02
#define PWM1_PINSEL_BIT 14

//war 24.08.2012
#define BOARD_HAS_BARO 1

/*
 * Modem
 */
//#define MODEM_DEVICE Uart1
//#define MODEM_UART_FLAG

/* Default actuators driver */
//#define CFG_ROTORCRAFT
#ifdef FIRMWARE // we assume ROTOCRAFT
#define ACTUATORS_MKK_NB 4
#define DEFAULT_ACTUATORS "subsystems/actuators/actuators_mkk.h"
#define ActuatorDefaultSet(_x,_y) ActuatorMkkSet(_x,_y)
#define ActuatorsDefaultInit() ActuatorsMkkInit()
#define ActuatorsDefaultCommit() ActuatorsMkkCommit()
#else
#define DEFAULT_ACTUATORS "subsystems/actuators/actuators_4017.h"
#define ActuatorDefaultSet(_x,_y) Actuator4017Set(_x,_y)
#define ActuatorsDefaultInit() Actuators4017Init()
#define ActuatorsDefaultCommit() Actuators4017Commit()
#endif

/* P0.5 aka MAT0.1  */
#define SERVO_CLOCK_PIN  5
#define SERVO_CLOCK_PINSEL PINSEL0
#define SERVO_CLOCK_PINSEL_VAL 0x02
#define SERVO_CLOCK_PINSEL_BIT 10
// p1.24

// SPI PINS and PORTS
/** Todo: right for hbmini ? olri */
#define SERVO_RESET_PIN 24
#define SPI_SELECT_SLAVE0_PORT 0
#define SPI_SELECT_SLAVE0_PIN 20
#define SPI_SELECT_SLAVE0_PINSEL PINSEL1
#define SPI_SELECT_SLAVE0_PINSEL_BIT 8
#define SPI_SELECT_SLAVE0_PINSEL_VAL 0

/* MAX1168 EOC pin (e.g. booz2 imu) */
/** Todo: right for hbmini ? olri */
#define MAX1168_EOC_PIN 16
#define MAX1168_EOC_PINSEL PINSEL1
#define MAX1168_EOC_PINSEL_BIT 0
#define MAX1168_EOC_PINSEL_VAL 1
#define MAX1168_EOC_EINT 0
#define MAX1168_EOC_VIC_IT VIC_EINT0

/* HMC5843 PORT */
#define HMC5843_I2C_DEV i2c1

#endif /* CONFIG_HBMINI_V2_0_H */
