#
# Makefile
#

CIRCLEHOME = ../../..

OBJS	= u8g2_bitmap.o u8g2_box.o u8g2_buffer.o u8g2_circle.o u8g2_cleardisplay.o u8g2_d_memory.o u8g2_d_setup.o u8g2_font.o u8g2_fonts.o u8g2_hvline.o u8g2_input_value.o u8g2_intersection.o u8g2_kerning.o u8g2_line.o u8g2_ll_hvline.o u8g2_message.o u8g2_polygon.o u8g2_selection_list.o u8g2_setup.o u8log.o u8log_u8g2.o u8log_u8x8.o u8x8_8x8.o u8x8_byte.o u8x8_cad.o u8x8_d_a2printer.o u8x8_d_il3820_296x128.o u8x8_d_ist3020.o u8x8_d_ks0108.o u8x8_d_lc7981.o u8x8_d_ld7032_60x32.o u8x8_d_ls013b7dh03.o u8x8_d_max7219.o u8x8_d_pcd8544_84x48.o u8x8_d_pcf8812.o u8x8_d_pcf8814_hx1230.o u8x8_d_sbn1661.o u8x8_d_sed1330.o u8x8_d_sh1106_64x32.o u8x8_d_sh1106_72x40.o u8x8_d_sh1107.o u8x8_d_sh1108.o u8x8_d_sh1122.o u8x8_d_ssd1305.o u8x8_d_ssd1306_128x32.o u8x8_d_ssd1306_128x64_noname.o u8x8_d_ssd1306_48x64.o u8x8_d_ssd1306_64x32.o u8x8_d_ssd1306_64x48.o u8x8_d_ssd1306_96x16.o u8x8_d_ssd1309.o u8x8_d_ssd1316.o u8x8_d_ssd1317.o u8x8_d_ssd1318.o u8x8_d_ssd1322.o u8x8_d_ssd1325.o u8x8_d_ssd1326.o u8x8_d_ssd1327.o u8x8_d_ssd1329.o u8x8_d_ssd1606_172x72.o u8x8_d_ssd1607_200x200.o u8x8_d_st7511.o u8x8_d_st75256.o u8x8_d_st75320.o u8x8_d_st7565.o u8x8_d_st7567.o u8x8_d_st7586s_erc240160.o u8x8_d_st7586s_s028hn118a.o u8x8_d_st7588.o u8x8_d_st7920.o u8x8_d_stdio.o u8x8_d_t6963.o u8x8_d_uc1601.o u8x8_d_uc1604.o u8x8_d_uc1608.o u8x8_d_uc1610.o u8x8_d_uc1611.o u8x8_d_uc1617.o u8x8_d_uc1638.o u8x8_d_uc1701_dogs102.o u8x8_d_uc1701_mini12864.o u8x8_debounce.o u8x8_display.o u8x8_fonts.o u8x8_gpio.o u8x8_input_value.o u8x8_message.o u8x8_selection_list.o u8x8_setup.o u8x8_string.o u8x8_u16toa.o u8x8_u8toa.o U8g2lib.o

libu8g2.a: $(OBJS)
	@echo "  AR    $@"
	@rm -f $@
	@$(AR) cr $@ $(OBJS)

include $(CIRCLEHOME)/Rules.mk
