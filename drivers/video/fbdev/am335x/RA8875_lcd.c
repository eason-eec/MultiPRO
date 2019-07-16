/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : lcd.c
* Author             : MCD Application Team
* Version            : V1.1.1
* Date               : 06/13/2008
* Description        : This file includes the LCD driver for AM-240320L8TNQW00H 
*                     (LCD_ILI9320) Liquid Crystal Display Module of STM3210E-EVAL
*                      board.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "stdlib.h"
#include <linux/kernel.h>
#include "fonts.h"
#include "RA8875_lcd.h"
#include "RA8875_subroutine.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/                              
/* Private variables ---------------------------------------------------------*/
/* Global variables to set the written text color */
static  u16 TextColor = 0x0000, BackColor = 0xFFFF;
  
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
*	REG[02h] Memory Read/Write Command (MRWC)
*	Write Function : Memory Write Data Data to write in memory corresponding to the setting of MWCR1[3:2].  
*					 Continuous  data  write  cycle  can  be  accepted  in bulk data write case.
*	Read Function  : Memory Read Data Data to read from memory corresponding to the setting of MWCR1[3:2].
*					 Continuous  data  read  cycle  can  be  accepted  in bulk  data  read  case.
*					 Note that the first data read cycle is dummy read and need to be ignored.
*	
*/
void LCD_WriteRAM_Prepare(void)
{
  LCD_CmdWrite(0x02); //
}

/*******************************************************************************
* Function Name  : LCD_SetTextColor
* Description    : Sets the Text color.
* Input          : - Color: specifies the Text color code RGB(5-6-5).
* Output         : - TextColor: Text color global variable used by LCD_DrawChar
*                  and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void LCD_SetTextColor(u16 Color)
{
	TextColor = Color;
	LCD_CmdWrite(0x63);
	LCD_DataWrite((Color&0xf800)>>11);
	
	LCD_CmdWrite(0x64);
	LCD_DataWrite((Color&0x07e0)>>5);
	
	LCD_CmdWrite(0x65);
	LCD_DataWrite((Color&0x001f));
}

/*******************************************************************************
* Function Name  : LCD_SetBackColor
* Description    : Sets the Background color.
* Input          : - Color: specifies the Background color code RGB(5-6-5).
* Output         : - BackColor: Background color global variable used by 
*                  LCD_DrawChar and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void LCD_SetBackColor(u16 Color)
{
	BackColor = Color;

	LCD_CmdWrite(0x60);
	LCD_DataWrite((Color&0xf800)>>11);
	LCD_CmdWrite(0x61);
	LCD_DataWrite((Color&0x07e0)>>5);
	LCD_CmdWrite(0x62);
	LCD_DataWrite((Color&0x001f));
}


/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : Clears the hole LCD.
* Input          : Color: the color of the background.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Clear(u16 Color)
{
	u32 index = 0;
  
	LCD_SetCursor(0,0); 

	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

	for(index = 0; index < 384000; index++) {
		LCD_DataWrite(Color);
	}
//	while(1);  
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position. 
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	LCD_CmdWrite(0x46);
	LCD_DataWrite(Xpos);  
	LCD_CmdWrite(0x47);	   
	LCD_DataWrite(Xpos>>8);
	LCD_CmdWrite(0x48);
	LCD_DataWrite(Ypos);
	LCD_CmdWrite(0x49);	   
	LCD_DataWrite(Ypos>>8);
}	

void LCD_SetPoint(u16 x,u16 y,u16 point)
{
	LCD_SetCursor(x,y);
	LCD_WriteRAM_Prepare();
	LCD_DataWrite(point);
}

void LCD_SetReadCursor(u16 Xpos, u16 Ypos)
{
	LCD_CmdWrite(0x4a);
	LCD_DataWrite(Xpos);  
	LCD_CmdWrite(0x4b);           
	LCD_DataWrite(Xpos>>8);
	LCD_CmdWrite(0x4c);
	LCD_DataWrite(Ypos);
	LCD_CmdWrite(0x4d);           
	LCD_DataWrite(Ypos>>8);
}

u16 LCD_GetPoint(u16 x,u16 y)
{	u16 temp;

	LCD_SetReadCursor(x,y);
	LCD_WriteRAM_Prepare();

	temp=LCD_DataRead();//Dummy
/*	__nop();
	__nop();
	__nop();
	__nop();
*/	temp=LCD_DataRead();
	return temp;
}

void LCD_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
	u16 i=0;
	u16 j=0;
  
	u16 tmp_char=0;

	for (i=0;i<24;i++) {
		tmp_char=ASCII_Table[((c-0x20)*24)+i];	 //搭32熬簿琌才眖秨﹍把σ才ê猔睦
		for (j=0;j<16;j++) {
//			if ( (tmp_char >> 15-j) & 0x01 == 0x01)	酚陪ボ才琌筁ㄓ硂ńэ筁ㄓ碞︽
			if ( (tmp_char >> j) & 0x01 == 0x01) {
				LCD_SetPoint(x+j,y+i,charColor); //才肅︹
			} else {
				LCD_SetPoint(x+j,y+i,bkColor); // 才肅︹
			}
		}
	}
}

void LCD_DisplayString(u16 X,u16 Y, char *ptr, u16 charColor, u16 bkColor)
{
	u32 i = 0;

	/* Send the string character by character on lCD */
	while ((*ptr != 0) & (i < 50)) {
		/* Display one character on LCD */
		LCD_PutChar(X, Y, *ptr, charColor, bkColor);
		/* Decrement the column position by 16 */
		X += 16;
		/* Point on the next character */
		ptr++;
		/* Increment the character counter */
		i++;
	}  	
}

/*******************************************************************************
* Function Name  : LCD_DisplayStringLine
* Description    : Displays a maximum of 20 char on the LCD.
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - *ptr: pointer to string to display on LCD.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayStringLine(u16 Line, char *ptr, u16 charColor, u16 bkColor)
{
	u32 i = 0;
	u16 refcolumn = 0;

	/* Send the string character by character on lCD */
	while ((*ptr != 0) & (i < 50)) {
		/* Display one character on LCD */
		LCD_PutChar(refcolumn, Line, *ptr, charColor, bkColor);
		/* Decrement the column position by 16 */
		refcolumn += 16;
		/* Point on the next character */
		ptr++;
		/* Increment the character counter */
		i++;
	}
}

/*******************************************************************************
* Function Name  : LCD_DrawLine
* Description    : Displays a line.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Length: line length.
*                  - Direction: line direction.
*                    This parameter can be one of the following values: Vertical 
*                    or Horizontal.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawLine(u16 Xpos, u16 Ypos, u16 Length, u8 Direction)
{
	u32 i = 0;
  
	LCD_SetCursor(Xpos,319 - Ypos);

	if(Direction == Horizontal) {
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		for(i = 0; i < Length; i++) {
			LCD_DataWrite(TextColor);
		}
	} else {
		for(i = 0; i < Length; i++) {
			LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
			LCD_DataWrite(TextColor);
			Xpos++;
			LCD_SetCursor(Xpos, 479 - Ypos);
		}
	}
}

/*******************************************************************************
* Function Name  : LCD_DrawRect
* Description    : Displays a rectangle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawRect(u16 Xpos, u16 Ypos, u16 Height, u16 Width)
{
	LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
	LCD_DrawLine((Xpos + Height), Ypos, Width, Horizontal);
  
	LCD_DrawLine(Xpos, Ypos, Height, Vertical);
	LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, Vertical);
}

/*******************************************************************************
* Function Name  : LCD_DrawCircle
* Description    : Displays a circle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawCircle(u16 Xpos, u16 Ypos, u16 Radius)
{
	s32  D;/* Decision Variable */ 
	u32  CurX;/* Current X Value */
	u32  CurY;/* Current Y Value */ 
  
	D = 3 - (Radius << 1);
	CurX = 0;
	CurY = Radius;
  
	while (CurX <= CurY) {
		LCD_SetCursor(Xpos + CurX, Ypos + CurY);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_DataWrite(TextColor);

		LCD_SetCursor(Xpos + CurX, Ypos - CurY);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_DataWrite(TextColor);

		LCD_SetCursor(Xpos - CurX, Ypos + CurY);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_DataWrite(TextColor);

		LCD_SetCursor(Xpos - CurX, Ypos - CurY);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_DataWrite(TextColor);

		LCD_SetCursor(Xpos + CurY, Ypos + CurX);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_DataWrite(TextColor);

		LCD_SetCursor(Xpos + CurY, Ypos - CurX);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_DataWrite(TextColor);

		LCD_SetCursor(Xpos - CurY, Ypos + CurX);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_DataWrite(TextColor);

		LCD_SetCursor(Xpos - CurY, Ypos - CurX);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_DataWrite(TextColor);

		if (D < 0) { 
			D += (CurX << 2) + 6;
		} else {
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
