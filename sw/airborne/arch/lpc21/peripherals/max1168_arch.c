/*
 * Copyright (C) 2008-2009 Antoine Drouin <poinix@gmail.com>
 * Copyright (C) 2012 Gautier Hattenberger
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "peripherals/max1168.h"

#include "LPC21xx.h"
#include "interrupt_hw.h"
#include BOARD_CONFIG

#if CS_74138
#include "ssp_hw.h"
#endif

static void EXTINT0_ISR(void) __attribute__((naked));

void max1168_arch_init( void ) {

#if CS_74138
  /* P1.25-16 are used as GPIO */
  PINSEL2 &= ~(_BV(3));
  /* unselected max1168 */
  Max1168Unselect();
  /* SS pin is output */
  SetBit(MAX1168_SS_IODIR, MAX1168_SS_PIN);
#endif // CS_74138
  /* connect P0.16 to extint0 (EOC) */
  MAX1168_EOC_PINSEL |= MAX1168_EOC_PINSEL_VAL << MAX1168_EOC_PINSEL_BIT;
  /* extint0 is edge trigered */
  SetBit(EXTMODE, MAX1168_EOC_EINT);
  /* extint0 is trigered on falling edge */
  ClearBit(EXTPOLAR, MAX1168_EOC_EINT);
  /* clear pending extint0 before enabling interrupts */
  SetBit(EXTINT, MAX1168_EOC_EINT);

   /* initialize interrupt vector */
  VICIntSelect &= ~VIC_BIT( MAX1168_EOC_VIC_IT );                     // EXTINT0 selected as IRQ
  VICIntEnable = VIC_BIT( MAX1168_EOC_VIC_IT );                       // EXTINT0 interrupt enabled
  _VIC_CNTL(MAX1168_EOC_VIC_SLOT) = VIC_ENABLE | MAX1168_EOC_VIC_IT;
  _VIC_ADDR(MAX1168_EOC_VIC_SLOT) = (uint32_t)EXTINT0_ISR;   // address of the ISR
}
#define CS_74138a 0
#if CS_74138a

//void max1168_read( void ) {
/* ASSERT((max1168_status == STA_MAX1168_IDLE),		\  */
//     DEBUG_MAX_1168, MAX1168_ERR_READ_OVERUN);
  /* select max1168 */
//  Max1168Select();
  /* enable SPI */
//  SSP_ClearRti();
//  SSP_DisableRti();
//  SSP_Enable();
  /* write control byte - wait EOC on extint */
  /* use internal reference and clock, sequentially scan channels 0-7 */
 // SSPDR = (1 << 0 | 1 << 3 | 7 << 5) << 8;
//  max1168_status = STA_MAX1168_SENDING_REQ;

//}

void EXTINT0_ISR(void) {
  ISR_ENTRY();
  ASSERT((max1168_status == MAX1168_SENDING_REQ),	\
     DEBUG_MAX_1168, MAX1168_ERR_SPURIOUS_EOC);
  /* read dummy control byte reply */
  uint16_t foo __attribute__ ((unused));
  foo = SSPDR;
  /* trigger 8 frames read */
  SSP_Send(0);
  SSP_Send(0);
  SSP_Send(0);
  SSP_Send(0);
  SSP_Send(0);
  SSP_Send(0);
  SSP_Send(0);
  SSP_Send(0);
  SSP_ClearRti();
  SSP_EnableRti();
  max1168_status = MAX1168_READING_RES;
  //SetBit(EXTINT, MAX1168_EOC_EINT);   /* clear extint0 */
  EXTINT = (1<<MAX1168_EOC_EINT);
  VICVectAddr = 0x00000000;             /* clear this interrupt from the VIC */

  ISR_EXIT();
}
#else
void EXTINT0_ISR(void) {
  ISR_ENTRY();
  //ASSERT((max1168_status == MAX1168_SENDING_REQ),	DEBUG_MAX_1168, MAX1168_ERR_SPURIOUS_EOC);

  max1168_status = MAX1168_GOT_EOC;

  //SetBit(EXTINT, MAX1168_EOC_EINT);   /* clear extint0 */
  EXTINT = (1<<MAX1168_EOC_EINT);
  VICVectAddr = 0x00000000;             /* clear this interrupt from the VIC */

  ISR_EXIT();
}

#endif



