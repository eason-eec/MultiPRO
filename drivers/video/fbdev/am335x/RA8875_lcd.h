/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : lcd.h
* Author             : MCD Application Team
* Version            : V1.1.1
* Date               : 06/13/2008
* Description        : This file contains all the functions prototypes for the
*                      lcd firmware driver.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RA8875_LCD_H
#define __RA8875_LCD_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_lib.h"
/*
#define LCD_BASE0        ((u32)0x60020000)
#define LCD_BASE1        ((u32)0x60000000)

#define LCD_CmdWrite(cmd)	  *(vu16*) (LCD_BASE0)= (cmd);
#define LCD_DataWrite(data)   *(vu16*) (LCD_BASE1)= (data);

#define	LCD_StatusRead()	 *(vu16*) (LCD_BASE0) //if use read  Mcu interface DB0~DB15 needs increase pull high 
#define	LCD_DataRead()   	 *(vu16*) (LCD_BASE1) //if use read  Mcu interface DB0~DB15 needs increase pull high 
*/


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

//DEFINE line
#define  APP_LINE_0                0
#define  APP_LINE_1               24
#define  APP_LINE_2               48
#define  APP_LINE_3               72
#define  APP_LINE_4               96
#define  APP_LINE_5              120
#define  APP_LINE_6              144
#define  APP_LINE_7              168
#define  APP_LINE_8              192
#define  APP_LINE_9              216

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define Line0          0
#define Line1          24
#define Line2          48
#define Line3          72
#define Line4          96
#define Line5          120
#define Line6          144
#define Line7          168
#define Line8          192
#define Line9          216
#define Line10         240
#define Line11         264
#define Line12         288
#define Line13         312
#define Line14         336
#define Line15         360
#define Line16         384
#define Line17         408
#define Line18         432
#define Line19         456

#define Horizontal     0x00
#define Vertical       0x01

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/*----- High layer function -----*/

void lcd_rst(void);
/*----- Medium layer function -----*/
void LCD_WriteRAM_Prepare(void);

void LCD_SetTextColor(u16 Color);
void LCD_SetBackColor(u16 Color);

void LCD_Clear(u16 Color);
void LCD_SetCursor(u16 Xpos, u16 Ypos);		 
void LCD_SetPoint(u16 x,u16 y,u16 point);

void LCD_SetReadCursor(u16 Xpos, u16 Ypos);
u16 LCD_GetPoint(u16 x,u16 y);

void LCD_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);

void LCD_DisplayString(u16 X,u16 Y, char *ptr, u16 charColor, u16 bkColor);
void LCD_DisplayStringLine(u16 Line, char *ptr, u16 charColor, u16 bkColor);
void LCD_SetDisplayWindow(u16 Xpos, u16 Ypos, u8 Height, u16 Width);

void LCD_DrawLine(u16 Xpos, u16 Ypos, u16 Length, u8 Direction);
void LCD_DrawRect(u16 Xpos, u16 Ypos, u16 Height, u16 Width);
void LCD_DrawCircle(u16 Xpos, u16 Ypos, u16 Radius);


/*----- Low layer function -----*/
#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
