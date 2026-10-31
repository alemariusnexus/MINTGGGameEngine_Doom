/* MINTGGGameEngine_Doom - A port of Doom to MINTGGGameEngine
 *
 * Copyright (C) 2026 David Lerch
 * SPDX-License-Identifier: GPL-3.0-or-later
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#define MGG_ENABLE_STRONG_COPYLEFT_ADDONS   1

#define MGG_APP_ID      "doom"
#define MGG_APP_NAME    "DOOM"

#define MGG_BUS_I2C_0_PIN_SCL           8
#define MGG_BUS_I2C_0_PIN_SDA           7

#define MGG_BUS_SPI_0_PIN_MISO          39
#define MGG_BUS_SPI_0_PIN_MOSI          44
#define MGG_BUS_SPI_0_PIN_SCK           43

#define MGG_STORAGE_SDCARD_PIN_CS       42
#define MGG_STORAGE_SDCARD_CLOCK        10000000

#define MGG_SCREEN_MAIN_TYPE            MGG_SCREEN_TYPE_RPI_TC358762
#define MGG_SCREEN_MAIN_PIXEL_FORMAT    PixelFormat::RGB565
