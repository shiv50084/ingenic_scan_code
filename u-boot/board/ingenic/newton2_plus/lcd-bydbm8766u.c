/*
 * Ingenic dorado lcd code
 *
 * Copyright (c) 2014 Ingenic Semiconductor Co.,Ltd
 * Author: Huddy <hyli@ingenic.cn>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <regulator.h>
#include <asm/gpio.h>
#include <jz_lcd/jz_lcd_v12.h>
#include <jz_lcd/byd_bm8766u.h>

void board_set_lcd_power_on(void)
{
	return;
	char *id = "out11";
	struct regulator *lcd_regulator = regulator_get(id);
	regulator_set_voltage(lcd_regulator, 3300000, 1800000);
	regulator_enable(lcd_regulator);
}

struct jzfb_config_info jzfb1_init_data = {
	.modes = &jzfb1_videomode,
	.lcd_type = LCD_TYPE_GENERIC_24_BIT,
	.bpp = 24,

	.pixclk_falling_edge = 0,
	.date_enable_active_low = 0,

	.dither_enable = 0,
};

struct byd_bm8766u_data byd_bm8766u_pdata = {
	.gpio_lcd_disp = GPIO_PB(30),
	.gpio_lcd_de = 0,	//GPIO_PC(9),   /* chose sync mode */
	.gpio_lcd_vsync = 0,	//GPIO_PC(19),
	.gpio_lcd_hsync = 0,	//GPIO_PC(18),
};
