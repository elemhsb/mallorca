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

/*
 * Module to extend the baro_board module with an airspeed sensor
 * Init and event functions are handled by the baro_board module
 */

#include "modules/sensors/airspeed_ltc2485.h"
#include "subsystems/sensors/baro.h"
#include "baro_board.h"

void airspeed_periodic(void) {
  ltc2485_read(&BARO_DIFF_LTC);
}



