
//#define  P320x240
//#define  P480x272
//#define  P640x480
#define  P800x480

//#define  Parallel8080	
#define	cSetD0		     0x01
#define	cSetD1		     0x02
#define	cSetD2		     0x04
#define	cSetD3		     0x08
#define	cSetD4		     0x10
#define	cSetD5		     0x20
#define	cSetD6		     0x40
#define	cSetD7		     0x80

#define	cClrD0		     0xfe
#define	cClrD1		     0xfd
#define	cClrD2		     0xfb
#define	cClrD3		     0xf7
#define	cClrD4		     0xef
#define	cClrD5		     0xdf
#define	cClrD6		     0xbf
#define	cClrD7		     0x7f

#define cClrD1D0         0xfc
#define cClrD1SetD0	     0x01
#define cSetD1ClrD0	     0x02
#define cSetD1D0		 0x03
#define cClrD3D2         0xf3
#define cClrD3SetD2      0x04
#define cSetD3ClrD2      0x08
#define cSetD3D2		 0x0c

#define cClrD2D1D0		 0xf8
#define cClrD2D1SetD0	 0x01
#define cClrD2SetD1ClrD0 0x02
#define cClrD2SetD1D0	 0x03
#define cSetD2ClrD1D0	 0x04
#define cSetD2ClrD1SetD0 0x05

#define cClrD6D5D4	     0x8f
#define cClrD6D5SetD4    0x10
#define cClrD6SetD5ClrD4 0x20
#define cClrD6SetD5D4	 0x30
#define cSetD6ClrD5D4	 0x40
#define cSetD6ClrD5SetD4 0x50
#define cSetD6D5ClrD4	 0x60
#define cSetD6D5D4		 0x70


//#define Color256
#define Color65k

#define color_black   0x0000
#define color_white   0xffff
#define color_red     0xf800
#define color_green   0x07e0
#define color_blue    0x001f
#define color_yellow  color_red|color_green
#define color_cyan    color_green|color_blue
#define color_purple  color_red|color_blue

#define color_grayscale1    2113
#define color_grayscale2    2113*2
#define color_grayscale3    2113*3
#define color_grayscale4    2113*4
#define color_grayscale5    2113*5
#define color_grayscale6    2113*6
#define color_grayscale7    2113*7
#define color_grayscale8    2113*8
#define color_grayscale9    2113*9
#define color_grayscale10   2113*10
#define color_grayscale11   2113*11
#define color_grayscale12   2113*12
#define color_grayscale13   2113*13
#define color_grayscale14   2113*14
#define color_grayscale15   2113*15
#define color_grayscale16   2113*16
#define color_grayscale17   2113*17
#define color_grayscale18   2113*18
#define color_grayscale19   2113*19
#define color_grayscale20   2113*20
#define color_grayscale21   2113*21
#define color_grayscale22   2113*22
#define color_grayscale23   2113*23
#define color_grayscale24   2113*24
#define color_grayscale25   2113*25
#define color_grayscale26   2113*26
#define color_grayscale27   2113*27
#define color_grayscale28   2113*28
#define color_grayscale29   2113*29
#define color_grayscale30   2113*30

extern u8 LCD_DataRead(void);
extern void LCD_DataWrite(unsigned int val);
extern void LCD_CmdWrite(unsigned int val);


void RA8875_PLL_ini(void) ;
void RA8875_LCD_Initial(void);


//STATUS 
void Chk_Busy(void);
void Chk_Busy_BTE(void);
void Chk_Busy_DIR_Access(void);

//REG[BFh]
void Chk_DMA_Busy(void);

//REG[01h]
void Display_ON(void);
void Display_OFF(void);
void Normal_Mode_exitSleep(void);
void Sleep_Mode(void);
void Software_Reset(void);

//REG[04h]
void PCLK_inversion(void);
void PCLK_non_inversion(void);
void PCLK_width(u8 setx);

//REG[05h] 
void Serial_ROM_select0(void);//bit7
void Serial_ROM_select1(void);//bit7

void Serial_ROM_Address_set_24bit(void);//bit6
void Serial_ROM_Address_set_32bit(void);//bit6

void Select_Serial_Waveform_mode0(void);//bit5
void Select_Serial_Waveform_mode3(void);//bit5

void SERIAL_ROM_Read_Cycle_4bus(void); //bit4~3
void SERIAL_ROM_Read_Cycle_5bus(void); //bit4~3
void SERIAL_ROM_Read_Cycle_6bus(void); //bit4~3

void SERIAL_ROM_Font_mode(void); //bit2
void SERIAL_ROM_DMA_mode(void);  //bit2

void SERIAL_ROM_Signal_mode(void); //bit1~0
void SERIAL_ROM_Dual_mode0(void);  //bit1~0
void SERIAL_ROM_Dual_mode1(void);  //bit1~0

  
void SROM_CLK_DIV(u8 CLK_DIV);

//REG[10h]
void Color_256(void);
void Color_64K(void);
void MPU_8bit_Interface(void);
void MPU_16bit_Interface(void);


//REG[12h] 
u8 GPI_data(void);
//REG[13h] 
void GPO_data(u8 setx);

//REG[20h]
void One_Layer(void);
void Two_Layers(void);
void HDIR_SEG0_SEGn(void);
void HDIR_SEGn_SEG0(void);
void VDIR_COM0_COMn(void);
void VDIR_COMn_COM0(void);

//REG[21h] 
void CGROM_Font(void);
void CGRAM_Font(void);
void Internal_CGROM(void);
void External_CGROM(void);
void ISO8859_1(void);
void ISO8859_2(void);
void ISO8859_3(void);
void ISO8859_4(void);

//REG[22h]
void No_FullAlignment(void);
void FullAlignment(void);
void Font_with_BackgroundColor(void);
void Font_with_BackgroundTransparency(void);

void Horizontal_FontEnlarge_x1(void);
void Horizontal_FontEnlarge_x2(void);
void Horizontal_FontEnlarge_x3(void);
void Horizontal_FontEnlarge_x4(void);
void Vertical_FontEnlarge_x1(void);
void Vertical_FontEnlarge_x2(void);
void Vertical_FontEnlarge_x3(void);
void Vertical_FontEnlarge_x4(void);

//REG[23h]	
void CGRAM_Select_Number(u8 number);

//REG[24h]REG[25h]REG[26h]REG[27h]	
void Scroll_Offset(u16 X,u16 Y);

//REG[29h]
void Line_distance(u8 setx);

//REG[2Ah]~REG[2Dh]
void Font_Coordinate(u16 X,u16 Y);

//REG[2Eh]
void Font_size_16x16_8x16(void);
void Font_size_24x24_12x24(void);
void Font_size_32x32_16x32(void);
void Font_spacing_set(u8 setx); //bit[5:0]

//REG[2Fh]
void GT_serial_ROM_select_GT21L16T1W(void);
void GT_serial_ROM_select_GT23L16U2W(void);
void GT_serial_ROM_select_GT23L24T3Y(void);
void GT_serial_ROM_select_GT23L24M1Z(void);
void GT_serial_ROM_select_GT23L32S4W(void);
void Font_code_GB2312(void);
void Font_code_GB12345(void);
void Font_code_BIG5(void);
void Font_code_UNICODE(void);
void Font_code_ASCII(void);
void Font_code_UNIJIS(void);
void Font_code_JIS0208(void);
void Font_code_LATIN(void);
void Font_Standard(void);
void Font_Arial(void);
void Font_Roman(void);
void Font_Bold(void); //for ASCII

//REG[30h]~REG[37h]
void Active_Window(u16 XL,u16 XR ,u16 YT ,u16 YB);

//REG[38h]~REG[3Fh]
void Scroll_Window(u16 XL,u16 XR ,u16 YT ,u16 YB);
//REG[40h]
void Graphic_Mode(void);
void Text_Mode(void);
void Text_Cursor_Disable(void);
void Text_Cursor_Enable(void);
void Text_Cursor_Blink_Disable(void);
void Text_Cursor_Blink_Enable(void);
void Memory_Write_LeftRight_TopDown(void);
void Memory_Write_RightLeft_TopDown(void);
void Memory_Write_DownTop_LeftRight(void);
void Memory_Write_TopDown_LeftRight(void);
void MemoryWrite_Cursor_autoIncrease(void);
void MemoryWrite_Cursor_NoautoIncrease(void);
void MemoryRead_Cursor_autoIncrease(void);
void MemoryRead_Cursor_NoautoIncrease(void);

//REG[41h]
void No_Graphic_Cursor(void);
void Graphic_Cursor(void);
void Graphic_Cursor_Set1(void);
void Graphic_Cursor_Set2(void);
void Graphic_Cursor_Set3(void);
void Graphic_Cursor_Set4(void);
void Graphic_Cursor_Set5(void);
void Graphic_Cursor_Set6(void);
void Graphic_Cursor_Set7(void);
void Graphic_Cursor_Set8(void);
void Write_To_Bank1and2(void);
void Write_To_CGRAM(void);
void Write_To_GraphicCursor(void);
void Write_To_Pattern(void);
void Write_To_Bank1(void);
void Write_To_Bank2(void);


//REG[44h]
void Text_Blink_Time(u8 setx);

//REG[45h]  
void Memory_read_LeftRight_TopDown(void);
void Memory_read_RightLeft_TopDown(void);
void Memory_read_TopDown_LeftRight(void);
void Memory_read_DownTop_LeftRight(void);

//REG[46h]~REG[49h]
void XY_Coordinate(u16 X,u16 Y);


//REG[4Ah]~REG[4Dh]
void Memory_read_Coordinate(u16 X,u16 Y);

//REG[4Eh]
void Text_Cursor_Horizontal_Size(u8 setx);//bit[3:0]

//REG[4Fh] 
void Text_Cursor_Vertical_Size(u8 setx);//bit[3:0]

//REG[50h] 
void no_BTE_write(void);
void BTE_enable(void);
void BTE_contiguous_Data(void);
void BTE_rectangular_Data(void);

//REG[51h] 
void BTE_ROP_Code(u8 setx);

//REG[52h] 
void Layer1_Visible(void);
void Layer2_Visible(void);
void Transparent_Mode(void);
void Lighten_Overlay_Mode(void);
void Boolean_OR(void);
void Boolean_AND(void);
void Floating_window_mode(void);
void Floating_Window_transparent_with_BGTR_enable(void);
void Floating_Window_transparent_with_BGTR_disable(void);

void Layer1_2_scroll(void);
void Layer1_scroll(void);
void Layer2_scroll(void);
void Buffer_scroll(void);



//REG[53h] 
void layer2_1_transparency(u8 setx);

//REG[54h]~ [5Fh]
void BTE_Source_Destination	(u16 XL,u16 XR ,u16 YT ,u16 YB);
void Source_Layer1(void);
void Source_Layer2(void);
void Destination_Layer1(void);
void Destination_Layer2(void);
void BTE_Size_setting(u16 X,u16 Y);


//REG[60h]~REG[67h]
void Text_color(u16 color);
void Background_color(u16 color);

void Text_Background_Color(u8 setR,u8 setG,u8 setB);
void Text_Foreground_Color(u8 setR,u8 setG,u8 setB);
void Pattern_Set_number(u8 setx);

void Pattern_Set_8x8(void);
void Pattern_Set_16x16(void);
void Pattern_Set_number(u8 setx);

void BackgroundColor_TransparentMode(u16 color);

//********TP controller*******
//REG[70h]~REG[74h]
void Enable_TP(void);
void Disable_TP(void);
void Enable_Touch_WakeUp(void);
void Disable_Touch_WakeUp(void);
void TP_manual_mode(void);
void TP_auto_mode(void);
void TP_IDLE_mode(void);
void TP_event_mode(void);
void TP_latch_X(void);
void TP_latch_Y(void);
u8 ADC_X(void);
u8 ADC_Y(void);
u8 ADC_XY(void);


//REG[80h]~REG[85h]
void Graphic_Cursor_Coordinate(u16 X,u16 Y);
void Graphic_Cursor_Color_0(u8 setx);
void Graphic_Cursor_Color_1(u8 setx);


//REG[8Ah]
void PWM1_enable(void);
void PWM1_disable(void);
void PWM1_disable_level_low(void);
void PWM1_disable_level_high(void);
void PWM1_fnuction_sel(void);
void PWM1_system_clk_out(void);
void PWM1_clock_ratio(u8 setx); //bit0~3 
//REG[8Bh]
void PWM1_duty_cycle(u8 setx); //bit0~7

//REG[8Ch]
void PWM2_enable(void);
void PWM2_disable(void);
void PWM2_disable_level_low(void);
void PWM2_disable_level_high(void);
void PWM2_fnuction_sel(void);
void PWM2_system_clk_out(void);
void PWM2_clock_ratio(u8 setx); //bit0~3 
//REG[8Dh]
void PWM2_duty_cycle(u8 setx); //bit0~7

//REG[8Eh]
void Stop_Memory_Clear(void);
void Memory_Clear(void);
void Clear_Full_Window(void);
void Clear_Active_Window(void);


//REG[90h] 					
void Draw_line(void);
void Draw_square(void);
void Draw_square_fill(void);
void Draw_circle(void);
void Draw_circle_fill(void);
void Draw_Triangle(void);
void Draw_Triangle_fill(void);


//REG[90h]~REG[9Dh]  
void Geometric_Coordinate(u16 XL,u16 XR ,u16 YT ,u16 YB);
void Circle_Coordinate_Radius(u16 X,u16 Y,u16 R);


//REG[A0h]~REG[ACh] 
void Draw_Ellipse(void);
void Draw_Ellipse_Curve(void);
void Draw_Ellipse_Curve_Fill(void);
void Draw_Ellipse_fill(void);

void Draw_Circle_Square(void);
void Draw_Circle_Square_fill(void);
void Draw_Ellipse_Curve_part(u8 setx);

void Ellipse_Coordinate_setting(u16 X,u16 Y,u16 ELL_A,u16 ELL_B);
void Circle_Square_Coordinate_setting(u16 XL,u16 XR ,u16 YT ,u16 YB ,u16 ELL_A,u16 ELL_B);
void Draw_Triangle_3point_Coordinate(u16 P1_X,u16 P1_Y,u16 P2_X,u16 P2_Y,u16 P3_X,u16 P3_Y);


//REG[B0]~REG[B3]
void DMA_Start_address_setting(u32 set_address);
//REG[B4]~REG[B8]
void DMA_Continuous_mode_size_setting(u32 set_size);
void DMA_block_mode_size_setting(u16 BWR,u16 BHR,u16 SPWR);

//REG[BFh]
void DMA_Continuous_mode(void);
void DMA_Block_mode(void);
void DMA_Start_enable(void);


//REG[C0h]
void Key_Scan_Enable(void);
void Long_Key_Scan_enable(void);
void Key_Scan_setting(u8 setx);//bit[5:0]
void Key_Scan_Wakeup_Function_Enable(void);
void Long_Key_Timing_Adjustment(u8 setx);

//REG[D0]
void Floating_window_start_point(u16 X,u16 Y);
void Floating_window_size(u16 width_X,u16 high_Y);
void Floating_window_display_point(u16 X,u16 Y);


 //REG[E0]
void Serial_ROM_direct_access_mode_enable(void);
void Serial_ROM_direct_access_mode_disable(void);
void Direct_access_mode_Address_32bits(u32 set_address);
void Direct_access_mode_Address_24bits(u32 set_address);
u8 Direct_access_mode_Read_Data_buffer(void);

//REG[F0h] 
void KEYSCAN_Interrupt_Enable(void);
void KEYSCAN_Interrupt_Disable(void);
void DMA_Interrupt_Enable(void);
void DMA_Interrupt_Disable(void);
void Touch_Panel_Interrupt_Enable(void);
void Touch_Panel_Interrupt_Disable(void);
void BTE_Interrupt_Enable(void);
void BTE_Interrupt_Disable(void);
void Font_BTE_read_write_Interrupt_Enable(void);
void Font_BTE_read_write_Interrupt_Disable(void);


//REG[F1h] 
void Clear_keyscan_interrupt(void);
u8 Keyscan_Status(void);

void Clear_DMA_interrupt(void);
u8 DMA_Status(void);

void clear_TP_interrupt(void);
u8 Touch_Status(void);

void Clear_BTE_interrupt(void);
u8 BTE_Status(void);

void Clear_Font_BTE_read_write_Interrupt(void);
u8 Font_BTE_read_write_Status(void);


void Chk_Wait(void);
void Show_String(u8 *str);




