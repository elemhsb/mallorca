 /*
 * Copyright (C) 2013 ELEMHSB
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
 *
 */

/* driver for the ADC LTC2485 (24 bits I2C) Linear */


#include "peripherals/ltc2485.h"

#if USE_LTC2485
struct ltc2485_periph ltc2485;
#endif


void ltc2485_init( void ) {
  /* configure the ltc2485 */
#if USE_LTC2485
  ltc2485.i2c_addr = LTC2485_I2C_ADDR;
  ltc2485.trans.buf[0] = LTC2485_CONFIG;
  i2c_transmit(&LTC2485_I2C_DEV, &ltc2485.trans, LTC2485_I2C_ADDR, 1);
  ltc2485.config_done = FALSE;
  ltc2485.data_available = FALSE;
#endif
}


void ltc2485_read( struct ltc2485_periph * p ) {
  // Config done with success
  // start new reading when previous is done (and read if success)
  if (p->config_done && p->trans.status == I2CTransDone) {
  // olri   p->trans.buf[0] = LTC2485_POINTER_CONV_REG;
    i2c_transceive(&LTC2485_I2C_DEV, &(p->trans), p->i2c_addr, 0, 4);
  }
}


