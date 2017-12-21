/*
 * Copyright (c) 2017 Ingenic Semiconductor Co., Ltd.
 *              http://www.ingenic.com/
 *
 * JZ4780 npm3701 board lcd setup routines.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mm.h>
#include <linux/console.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/pwm_backlight.h>

#include <mach/jzfb.h>
#include <mach/fb_hdmi_modes.h>

#ifdef CONFIG_LCD_KR070LA0S_270
#include <linux/kr070la0s_270.h>
static struct platform_kr070la0s_270_data kr070la0s_270_pdata= {
/* gpio had been hardware control */
};

/* LCD Panel Device */
struct platform_device kr070la0s_270_device = {
	.name		= "kr070la0s_270-lcd",
	.dev		= {
		.platform_data	= &kr070la0s_270_pdata,
	},
};
#endif

#ifdef CONFIG_LCD_EK070TN93
#include <linux/ek070tn93.h>
static struct platform_ek070tn93_data ek070tn93_pdata= {
	.gpio_de = GPIO_PC(9),
	.gpio_vs = GPIO_PC(19),
	.gpio_hs = GPIO_PC(18),
//	.gpio_reset = GPIO_PB(22),

	.de_mode = 0,
};

/* LCD Panel Device */
struct platform_device ek070tn93_device = {
	.name		= "ek070tn93-lcd",
	.dev		= {
		.platform_data	= &ek070tn93_pdata,
	},
};
#endif

#ifdef CONFIG_FB_JZ4780_LCDC0
/* LCDC0 output to HDMI and the default hdmi video mode list
 * define in soc-4780/include/mach/fb_hdmi_modes.h
 * or initialization a different platform data at here
 */
static struct fb_videomode jzfb0_hdmi_videomode[] = {
	DEFAULT_HDMI_VIDEO_MODE_LIST,
};

struct jzfb_platform_data jzfb0_hdmi_pdata = {
	.num_modes = ARRAY_SIZE(jzfb0_hdmi_videomode),
	.modes = jzfb0_hdmi_videomode,

	.lcd_type = LCD_TYPE_GENERIC_24_BIT,
	.bpp = 24,
	.width = 0,
	.height = 0,

	.pixclk_falling_edge = 1,
	.date_enable_active_low = 0,

	.alloc_vidmem = 0,
};
#endif

#ifdef CONFIG_FB_JZ4780_LCDC1
/* LCD Controller 1 output to LVDS TFT panel */
static struct fb_videomode jzfb1_videomode[] = {

#ifdef CONFIG_LCD_KR070LA0S_270_65HZ // 65Hz@vpll=480MHz, 63Hz@vpll=888MHz
	{
		.name = "1024x600",
		.refresh = 65,
		.xres = 1024,
		.yres = 600,
		.pixclock = KHZ2PICOS(48000),
		.left_margin = 171,
		.right_margin = 0,
		.upper_margin = 18,
		.lower_margin = 0,
		.hsync_len = 0,
		.vsync_len = 0,
		.sync = 0 | 0, /* FB_SYNC_HOR_HIGH_ACT:0, FB_SYNC_VERT_HIGH_ACT:0 */
		.vmode = FB_VMODE_NONINTERLACED,
		.flag = 0
	},
#endif

#ifdef CONFIG_LCD_S369FG06 
	{
		.name = "480*800",
		.refresh = 60, 
		.xres = 480, 
		.yres = 800, 
		.pixclock = KHZ2PICOS(30844), 
		.left_margin = 50,
		.right_margin = 50,
		.upper_margin = 7,		/* If you change upper and lower margin, */
		.lower_margin = 8,		/* change it in struct specific_tl2796. */
		.hsync_len = 50, 
		.vsync_len = 1,		/* for tl2796: VFP = vsync_len + upper_margin */
		.sync = 0 | 0, /* FB_SYNC_HOR_HIGH_ACT:0, FB_SYNC_VERT_HIGH_ACT:0 */
		.vmode = FB_VMODE_NONINTERLACED,
		.flag = 0
	},
#endif

#ifdef CONFIG_LCD_KR070LA0S_270 // 60Hz@vpll=888MHz
	{
		.name = "1024x600",
		.refresh = 60,
		.xres = 1024,
		.yres = 600,
		.pixclock = KHZ2PICOS(52240),
		.left_margin = 336,
		.right_margin = 0,
		.upper_margin = 40,
		.lower_margin = 0,
		.hsync_len = 0,
		.vsync_len = 0,
		.sync = 0 | 0, /* FB_SYNC_HOR_HIGH_ACT:0, FB_SYNC_VERT_HIGH_ACT:0 */
		.vmode = FB_VMODE_NONINTERLACED,
		.flag = 0
	},
#endif

#ifdef CONFIG_LCD_KR070LA0S_270_55HZ // 55Hz@vpll=888MHz
	{
		.name = "1024x600",
		.refresh = 55,
		.xres = 1024,
		.yres = 600,
		.pixclock = KHZ2PICOS(46800),
		.left_margin = 320,
		.right_margin = 0,
		.upper_margin = 32,
		.lower_margin = 0,
		.hsync_len = 0,
		.vsync_len = 0,
		.sync = 0 | 0, /* FB_SYNC_HOR_HIGH_ACT:0, FB_SYNC_VERT_HIGH_ACT:0 */
		.vmode = FB_VMODE_NONINTERLACED,
		.flag = 0
	},
#endif

#ifdef CONFIG_LCD_EK070TN93
	{
		.name = "800x480",
		.refresh = 60,
		.xres = 800,
		.yres = 480,
		.pixclock = KHZ2PICOS(33300),
		.left_margin = 28,
		.right_margin = 210,
		.upper_margin = 15,
		.lower_margin = 22,
		.hsync_len = 18,
		.vsync_len = 8,
		.sync = 0 | 0, /* FB_SYNC_HOR_HIGH_ACT:0, FB_SYNC_VERT_HIGH_ACT:0 */
		.vmode = FB_VMODE_NONINTERLACED,
		.flag = 0
	},
#endif
};

struct jzfb_platform_data jzfb1_pdata = {
	.num_modes = ARRAY_SIZE(jzfb1_videomode),
	.modes = jzfb1_videomode,

#ifdef CONFIG_LCD_KR070LA0S_270
	.lcd_type = LCD_TYPE_GENERIC_24_BIT,
	.bpp = 24,
	.width = 154,
	.height = 90,

	.pixclk_falling_edge = 0,
	.date_enable_active_low = 0,

	.alloc_vidmem = 1,

	.lvds = 1,
	.txctrl.data_format = VESA,
	.txctrl.clk_edge_falling_7x = 0,
	.txctrl.clk_edge_falling_1x = 1,
	.txctrl.data_start_edge = START_EDGE_4,
	.txctrl.operate_mode = LVDS_1X_CLKOUT,
	.txctrl.edge_delay = DELAY_0_1NS,
	.txctrl.output_amplitude = VOD_350MV,

	.txpll0.ssc_enable = 0,
	.txpll0.ssc_mode_center_spread = 0,
	.txpll0.post_divider = POST_DIV_1,
	.txpll0.feedback_divider = 70,
	.txpll0.input_divider_bypass = 0,
	.txpll0.input_divider = 10,

	.txpll1.charge_pump = CHARGE_PUMP_10UA,
	.txpll1.vco_gain = VCO_GAIN_150M_400M,
	.txpll1.vco_biasing_current = VCO_BIASING_2_5UA,
	.txpll1.sscn = 0,
	.txpll1.ssc_counter = 0,

	.txectrl.emphasis_level = 0,
	.txectrl.emphasis_enable = 0,
	.txectrl.ldo_output_voltage = LDO_OUTPUT_1_1V,
	.txectrl.phase_interpolator_bypass = 1,
	.txectrl.fine_tuning_7x_clk = 0,
	.txectrl.coarse_tuning_7x_clk = 0,

	.dither_enable = 0,
#endif
#ifdef CONFIG_LCD_EK070TN93
	.lcd_type = LCD_TYPE_GENERIC_24_BIT,
	.bpp = 24,
	.width = 154,
	.height = 86,

	.pixclk_falling_edge = 0,
	.date_enable_active_low = 0,

	.alloc_vidmem = 1,
	.lvds = 0,
	.dither_enable = 0,
#endif

#ifdef CONFIG_LCD_S369FG06
	.lcd_type = LCD_TYPE_GENERIC_24_BIT,
	.bpp = 24,
	.width = 48,
	.height = 80,

	.pixclk_falling_edge = 1, //0,
	.date_enable_active_low = 1,

	.alloc_vidmem = 1,
	.lvds = 0,
	.dither_enable = 0,
#endif

};
#endif /* CONFIG_FB_JZ4780_LCDC1 */

#ifdef CONFIG_BACKLIGHT_PWM
static int npm3701_backlight_init(struct device *dev)
{
	return 0;
}

static void npm3701_backlight_exit(struct device *dev)
{
}

static struct platform_pwm_backlight_data npm3701_backlight_data = {
	.pwm_id		= 0,
	.max_brightness	= 255,
	.dft_brightness	= 80,
	.pwm_period_ns	= 10000, /* 100 kHZ */
	.init		= npm3701_backlight_init,
	.exit		= npm3701_backlight_exit,
};

/* Backlight Device */
struct platform_device npm3701_backlight_device = {
	.name		= "pwm-backlight",
	.dev		= {
		.platform_data	= &npm3701_backlight_data,
	},
};

#endif
