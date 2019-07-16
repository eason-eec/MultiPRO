
//******************** COPYRIGHT  ********************
// File Name          :RA8875_subroutine.c
// Author             :RAIO 
// Version            :V1.0 
// Date               :09/28/11 
// Description        : 	
//****************************************************

#include <linux/kernel.h>
#include <linux/delay.h>
//#include "stdlib.h"
#include "RA8875_lcd.h"
#include "RA8875_subroutine.h"

extern u8 LCD_DataRead(void);
extern void LCD_DataWrite(unsigned int val);
extern void LCD_CmdWrite(unsigned int val);

//----------------------------//


void RA8875_PLL_ini(void)
{
#ifdef P320x240
	LCD_CmdWrite(0x88);    
	LCD_DataWrite(0x0a);
	mdelay(1);
	LCD_CmdWrite(0x89);
	LCD_DataWrite(0x02);       
	mdelay(1);
#endif


#ifdef P480x272
	LCD_CmdWrite(0x88);      
	LCD_DataWrite(0x0a);
	mdelay(1);     
	LCD_CmdWrite(0x89);        
	LCD_DataWrite(0x02);  
	mdelay(1);
#endif

#ifdef P640x480
	LCD_CmdWrite(0x88);    
	LCD_DataWrite(0x0b);
	mdelay(1);    
	LCD_CmdWrite(0x89);        
	LCD_DataWrite(0x02);	 
	mdelay(1);
#endif

#ifdef P800x480
	LCD_CmdWrite(0x88);	   
	LCD_DataWrite(0x0b);
	mdelay(1);	
	LCD_CmdWrite(0x89);	   
	LCD_DataWrite(0x02);  
	mdelay(1);
#endif
}	

//------------------------------------------//
void RA8875_LCD_Initial(void)
{ 	

	RA8875_PLL_ini();

	LCD_CmdWrite(0x10);  //SYSR   bit[4:3]=00 256 color  bit[2:1]=  00 8bit MPU interface
	//LCD_DataWrite(0x000c);   // if 8bit MCU interface   and 65k color display  							
	LCD_DataWrite(0x0F); // if 16bit MCU interface   and 65k color display  
	udelay(1); 
#ifdef P320x240
//==============	Display Window	320x240 ==================	
	LCD_CmdWrite(0x04);	 //set PCLK invers
	LCD_DataWrite(0x03);  
	mdelay(1);
	
	 //Horizontal set
	LCD_CmdWrite(0x14); //HDWR//Horizontal Display Width Setting Bit[6:0] 
	LCD_DataWrite(0x27);//Horizontal display width(pixels) = (HDWR + 1)*8  
	LCD_CmdWrite(0x15); //Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
	LCD_DataWrite(0x00);//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]  
	LCD_CmdWrite(0x16); //HNDR//Horizontal Non-Display Period Bit[4:0] 
	LCD_DataWrite(0x03);//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8   
	LCD_CmdWrite(0x17); //HSTR//HSYNC Start Position[4:0] 
	LCD_DataWrite(0x02);//HSYNC Start Position(PCLK) = (HSTR + 1)*8 
	LCD_CmdWrite(0x18); //HPWR//HSYNC Polarity ,The period width of HSYNC. 
	LCD_DataWrite(0x03);//HSYNC Width [4:0]   HSYNC Pulse width(PCLK) = (HPWR + 1)*8 
	 //Vertical set 
	LCD_CmdWrite(0x19); //VDHR0 //Vertical Display Height Bit [7:0] 
	LCD_DataWrite(0xef);//Vertical pixels = VDHR + 1

	LCD_CmdWrite(0x1A); //VDHR1 //Vertical Display Height Bit [8] 
	LCD_DataWrite(0x00);//Vertical pixels = VDHR + 1 

	LCD_CmdWrite(0x1B); //VNDR0 //Vertical Non-Display Period Bit [7:0]
	LCD_DataWrite(0x0f);//Vertical Non-Display area = (VNDR + 1) 

	LCD_CmdWrite(0x1C); //VNDR1 //Vertical Non-Display Period Bit [8] 
	LCD_DataWrite(0x00);//Vertical Non-Display area = (VNDR + 1)   
	LCD_CmdWrite(0x1D); //VSTR0 //VSYNC Start Position[7:0]
	LCD_DataWrite(0x0e);//VSYNC Start Position(PCLK) = (VSTR + 1) 
	LCD_CmdWrite(0x1E); //VSTR1 //VSYNC Start Position[8] 
	LCD_DataWrite(0x06);//VSYNC Start Position(PCLK) = (VSTR + 1) 
	LCD_CmdWrite(0x1F); //VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]
	LCD_DataWrite(0x01);//VSYNC Pulse Width(PCLK) = (VPWR + 1) 

  //Active window  set 
  //setting active window X
	LCD_CmdWrite(0x30); //Horizontal Start Point 0 of Active Window (HSAW0)
	LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [7:0]
	LCD_CmdWrite(0x31); //Horizontal Start Point 1 of Active Window (HSAW1)	   
	LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [9:8]
	LCD_CmdWrite(0x34); //Horizontal End Point 0 of Active Window (HEAW0)
	LCD_DataWrite(0x3F); //Horizontal End Point of Active Window [7:0]
	LCD_CmdWrite(0x35); //Horizontal End Point 1 of Active Window (HEAW1)	   
	LCD_DataWrite(0x01); //Horizontal End Point of Active Window [9:8]

   //setting active window Y
	LCD_CmdWrite(0x32); //Vertical Start Point 0 of Active Window (VSAW0)
	LCD_DataWrite(0x00); //Vertical Start Point of Active Window [7:0]
	LCD_CmdWrite(0x33); //Vertical Start Point 1 of Active Window (VSAW1)	   
	LCD_DataWrite(0x00); //Vertical Start Point of Active Window [8]
	LCD_CmdWrite(0x36); //Vertical End Point of Active Window 0 (VEAW0)
	LCD_DataWrite(0xef); //Vertical End Point of Active Window [7:0]
	LCD_CmdWrite(0x37); //Vertical End Point of Active Window 1 (VEAW1)	   
	LCD_DataWrite(0x00); //Vertical End Point of Active Window [8]

#endif

#ifdef P480x272
    LCD_CmdWrite(0x04);    //set PCLK invers
    LCD_DataWrite(0x82); 
    mdelay(1);

    //Horizontal set
    LCD_CmdWrite(0x14); //HDWR//Horizontal Display Width Setting Bit[6:0]                   
    LCD_DataWrite(0x3B);//Horizontal display width(pixels) = (HDWR + 1)*8                   
    LCD_CmdWrite(0x15); //Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
    LCD_DataWrite(0x00);//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]            
    LCD_CmdWrite(0x16); //HNDR//Horizontal Non-Display Period Bit[4:0]                      
    LCD_DataWrite(0x01);//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8             
    LCD_CmdWrite(0x17); //HSTR//HSYNC Start Position[4:0]                                   
    LCD_DataWrite(0x00);//HSYNC Start Position(PCLK) = (HSTR + 1)*8                         
    LCD_CmdWrite(0x18); //HPWR//HSYNC Polarity ,The period width of HSYNC.                  
    LCD_DataWrite(0x05);//HSYNC Width [4:0]   HSYNC Pulse width(PCLK) = (HPWR + 1)*8        
                                             
    //Vertical set                                            
    LCD_CmdWrite(0x19); //VDHR0 //Vertical Display Height Bit [7:0]                            
    LCD_DataWrite(0x0f); //Vertical pixels = VDHR + 1                                      
    LCD_CmdWrite(0x1a); //VDHR1 //Vertical Display Height Bit [8]                  
    LCD_DataWrite(0x01); //Vertical pixels = VDHR + 1                           
    LCD_CmdWrite(0x1b);  //VNDR0 //Vertical Non-Display Period Bit [7:0]                    
    LCD_DataWrite(0x02);  //VSYNC Start Position(PCLK) = (VSTR + 1)                          
    LCD_CmdWrite(0x1c);  //VNDR1 //Vertical Non-Display Period Bit [8]                             
    LCD_DataWrite(0x00); //Vertical Non-Display area = (VNDR + 1)                            
    LCD_CmdWrite(0x1d); //VSTR0 //VSYNC Start Position[7:0]                               
    LCD_DataWrite(0x07);//VSYNC Start Position(PCLK) = (VSTR + 1)                           
    LCD_CmdWrite(0x1e); //VSTR1 //VSYNC Start Position[8]                   
    LCD_DataWrite(0x00);//VSYNC Start Position(PCLK) = (VSTR + 1)                            
    LCD_CmdWrite(0x1f);    //VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]
    LCD_DataWrite(0x09);   //VSYNC Pulse Width(PCLK) = (VPWR + 1) 

  //Active window  set 
  //setting active window X
    LCD_CmdWrite(0x30); //Horizontal Start Point 0 of Active Window (HSAW0)
    LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [7:0]
    LCD_CmdWrite(0x31); //Horizontal Start Point 1 of Active Window (HSAW1)	   
    LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [9:8]
    LCD_CmdWrite(0x34); //Horizontal End Point 0 of Active Window (HEAW0)
    LCD_DataWrite(0xDF); //Horizontal End Point of Active Window [7:0]
    LCD_CmdWrite(0x35); //Horizontal End Point 1 of Active Window (HEAW1)	   
    LCD_DataWrite(0x01); //Horizontal End Point of Active Window [9:8]

   //setting active window Y
    LCD_CmdWrite(0x32); //Vertical Start Point 0 of Active Window (VSAW0)
    LCD_DataWrite(0x00); //Vertical Start Point of Active Window [7:0]
    LCD_CmdWrite(0x33); //Vertical Start Point 1 of Active Window (VSAW1)	   
    LCD_DataWrite(0x00); //Vertical Start Point of Active Window [8]
    LCD_CmdWrite(0x36); //Vertical End Point of Active Window 0 (VEAW0)
    LCD_DataWrite(0x0F); //Vertical End Point of Active Window [7:0]
    LCD_CmdWrite(0x37); //Vertical End Point of Active Window 1 (VEAW1)	   
    LCD_DataWrite(0x01); //Vertical End Point of Active Window [8]

#endif



#ifdef P640x480
//==============	Display Window	640x480 ==================	
    LCD_CmdWrite(0x04);    //PCLK inverse
    LCD_DataWrite(0x01);
    mdelay(1);
    
    //Horizontal set
    LCD_CmdWrite(0x14);//HDWR//Horizontal Display Width Setting Bit[6:0]                   
    LCD_DataWrite(0x4F);//Horizontal display width(pixels) = (HDWR + 1)*8                   
    LCD_CmdWrite(0x15); //Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
    LCD_DataWrite(0x05);//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]            
    LCD_CmdWrite(0x16);//HNDR//Horizontal Non-Display Period Bit[4:0]                      
    LCD_DataWrite(0x0f);//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8             
    LCD_CmdWrite(0x17);//HSTR//HSYNC Start Position[4:0]                                   
    LCD_DataWrite(0x01);//HSYNC Start Position(PCLK) = (HSTR + 1)*8                         
    LCD_CmdWrite(0x18); //HPWR//HSYNC Polarity ,The period width of HSYNC.                  
    LCD_DataWrite(0x00);//HSYNC Width [4:0]   HSYNC Pulse width(PCLK) = (HPWR + 1)*8  
    //Vertical set       
    LCD_CmdWrite(0x19); //VDHR0 //Vertical Display Height Bit [7:0]                         
    LCD_DataWrite(0xdf);//Vertical pixels = VDHR + 1                                        
    LCD_CmdWrite(0x1A);//VDHR1 //Vertical Display Height Bit [8]                           
    LCD_DataWrite(0x01);//Vertical pixels = VDHR + 1                                        
    LCD_CmdWrite(0x1B);//VNDR0 //Vertical Non-Display Period Bit [7:0]                     
    LCD_DataWrite(0x0A);//Vertical Non-Display area = (VNDR + 1)                            
    LCD_CmdWrite(0x1C);//VNDR1 //Vertical Non-Display Period Bit [8]                       
    LCD_DataWrite(0x00);//Vertical Non-Display area = (VNDR + 1)                            
    LCD_CmdWrite(0x1D);//VSTR0 //VSYNC Start Position[7:0]                                 
    LCD_DataWrite(0x0E);//VSYNC Start Position(PCLK) = (VSTR + 1)                           
    LCD_CmdWrite(0x1E);//VSTR1 //VSYNC Start Position[8]                                   
    LCD_DataWrite(0x00);//VSYNC Start Position(PCLK) = (VSTR + 1)                           
    LCD_CmdWrite(0x1F);//VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]                     
    LCD_DataWrite(0x01);//VSYNC Pulse Width(PCLK) = (VPWR + 1)                              
   
   //Active window  set 
   //setting active window X
    LCD_CmdWrite(0x30); //Horizontal Start Point 0 of Active Window (HSAW0)
    LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [7:0]
    LCD_CmdWrite(0x31); //Horizontal Start Point 1 of Active Window (HSAW1)	   
    LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [9:8]
    LCD_CmdWrite(0x34); //Horizontal End Point 0 of Active Window (HEAW0)
    LCD_DataWrite(0x7f); //Horizontal End Point of Active Window [7:0]
    LCD_CmdWrite(0x35); //Horizontal End Point 1 of Active Window (HEAW1)	   
    LCD_DataWrite(0x02); //Horizontal End Point of Active Window [9:8]

   //setting active window Y
    LCD_CmdWrite(0x32); //Vertical Start Point 0 of Active Window (VSAW0)
    LCD_DataWrite(0x00); //Vertical Start Point of Active Window [7:0]
    LCD_CmdWrite(0x33); //Vertical Start Point 1 of Active Window (VSAW1)	   
    LCD_DataWrite(0x00); //Vertical Start Point of Active Window [8]
    LCD_CmdWrite(0x36); //Vertical End Point of Active Window 0 (VEAW0)
    LCD_DataWrite(0xdf); //Vertical End Point of Active Window [7:0]
    LCD_CmdWrite(0x37); //Vertical End Point of Active Window 1 (VEAW1)	   
    LCD_DataWrite(0x01); //Vertical End Point of Active Window [8]

#endif   


#ifdef P800x480

//AT070TN92  setting
//==============	Display Window	800x480 ==================	
  
   LCD_CmdWrite(0x04);     //PCLK inverse 
   LCD_DataWrite(0x81);
   mdelay(1);
  
   //Horizontal set
   LCD_CmdWrite(0x14); //HDWR//Horizontal Display Width Setting Bit[6:0]                   
   LCD_DataWrite(0x63);//Horizontal display width(pixels) = (HDWR + 1)*8 
                   
   LCD_CmdWrite(0x15); //Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
   LCD_DataWrite(0x03);//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]   
          
   LCD_CmdWrite(0x16); //HNDR//Horizontal Non-Display Period Bit[4:0]                      
   LCD_DataWrite(0x03);//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8 
             
   LCD_CmdWrite(0x17); //HSTR//HSYNC Start Position[4:0]                                   
   LCD_DataWrite(0x02);//HSYNC Start Position(PCLK) = (HSTR + 1)*8    
                     
   LCD_CmdWrite(0x18); //HPWR//HSYNC Polarity ,The period width of HSYNC.                  
   LCD_DataWrite(0x00);//HSYNC Width [4:0]   HSYNC Pulse width(PCLK) = (HPWR + 1)*8   

   //Vertical set    
   LCD_CmdWrite(0x19); //VDHR0 //Vertical Display Height Bit [7:0]                         
   LCD_DataWrite(0xdf);//Vertical pixels = VDHR + 1       
                                 
   LCD_CmdWrite(0x1a); //VDHR1 //Vertical Display Height Bit [8]                           
   LCD_DataWrite(0x01);//Vertical pixels = VDHR + 1  
                                      
   LCD_CmdWrite(0x1b); //VNDR0 //Vertical Non-Display Period Bit [7:0]                     
   LCD_DataWrite(0x14);//Vertical Non-Display area = (VNDR + 1) 
                           
   LCD_CmdWrite(0x1c); //VNDR1 //Vertical Non-Display Period Bit [8]                       
   LCD_DataWrite(0x00);//Vertical Non-Display area = (VNDR + 1)  
                          
   LCD_CmdWrite(0x1d); //VSTR0 //VSYNC Start Position[7:0]                                 
   LCD_DataWrite(0x06);//VSYNC Start Position(PCLK) = (VSTR + 1)  
                          
   LCD_CmdWrite(0x1e); //VSTR1 //VSYNC Start Position[8]                                   
   LCD_DataWrite(0x00);//VSYNC Start Position(PCLK) = (VSTR + 1)   
                        
   LCD_CmdWrite(0x1f); //VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]                     
   LCD_DataWrite(0x01);//VSYNC Pulse Width(PCLK) = (VPWR + 1)                              

   LCD_CmdWrite(0xf2);  
   LCD_DataWrite(0x01);
  
   LCD_CmdWrite(0x8e);  
   LCD_DataWrite(0x80);
   mdelay(20);

//HSD050IDW1,ET0700B3DMA setting
//==============	Display Window	800x480 ==================	
 /*
 LCD_CmdWrite(0x04);  //PCLK inverse
 LCD_DataWrite(0x81);
 mdelay(1);
 
 //Horizontal set
 LCD_CmdWrite(0x14); //HDWR//Horizontal Display Width Setting Bit[6:0]                      
 LCD_DataWrite(0x63);//Horizontal display width(pixels) = (HDWR + 1)*8                      
 LCD_CmdWrite(0x15);//Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)   
 LCD_DataWrite(0x00);//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]               
 LCD_CmdWrite(0x16); //HNDR//Horizontal Non-Display Period Bit[4:0]                         
 LCD_DataWrite(0x03);//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8                
 LCD_CmdWrite(0x17); //HSTR//HSYNC Start Position[4:0]                                      
 LCD_DataWrite(0x03);//HSYNC Start Position(PCLK) = (HSTR + 1)*8                            
 LCD_CmdWrite(0x18); //HPWR//HSYNC Polarity ,The period width of HSYNC.                     
 LCD_DataWrite(0x0B);//HSYNC Width [4:0]   HSYNC Pulse width(PCLK) = (HPWR + 1)*8    
 //Vertical set                             
 LCD_CmdWrite(0x19); //VDHR0 //Vertical Display Height Bit [7:0]                            
 LCD_DataWrite(0xdf);//Vertical pixels = VDHR + 1                                           
 LCD_CmdWrite(0x1a); //VDHR1 //Vertical Display Height Bit [8]                              
 LCD_DataWrite(0x01);//Vertical pixels = VDHR + 1                                           
 LCD_CmdWrite(0x1b); //VNDR0 //Vertical Non-Display Period Bit [7:0]                        
 LCD_DataWrite(0x20);//Vertical Non-Display area = (VNDR + 1)                               
 LCD_CmdWrite(0x1c); //VNDR1 //Vertical Non-Display Period Bit [8]                          
 LCD_DataWrite(0x00);//Vertical Non-Display area = (VNDR + 1)                               
 LCD_CmdWrite(0x1d); //VSTR0 //VSYNC Start Position[7:0]                                    
 LCD_DataWrite(0x16);//VSYNC Start Position(PCLK) = (VSTR + 1)                              
 LCD_CmdWrite(0x1e); //VSTR1 //VSYNC Start Position[8]                                      
 LCD_DataWrite(0x00);//VSYNC Start Position(PCLK) = (VSTR + 1)                              
 LCD_CmdWrite(0x1f); //VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]                        
 LCD_DataWrite(0x01);//VSYNC Pulse Width(PCLK) = (VPWR + 1)                                 
  */
   
  //Active window  set 
   //setting active window X
    LCD_CmdWrite(0x30); //Horizontal Start Point 0 of Active Window (HSAW0)
    LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [7:0]
	//udelay(1); 
    LCD_CmdWrite(0x31); //Horizontal Start Point 1 of Active Window (HSAW1)	   
    LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [9:8]
	//udelay(1); 
    LCD_CmdWrite(0x34); //Horizontal End Point 0 of Active Window (HEAW0)
    LCD_DataWrite(0x1F); //Horizontal End Point of Active Window [7:0]
	//udelay(1); 
    LCD_CmdWrite(0x35); //Horizontal End Point 1 of Active Window (HEAW1)	   
    LCD_DataWrite(0x03); //Horizontal End Point of Active Window [9:8]
	//udelay(1); 

   //setting active window Y
    LCD_CmdWrite(0x32); //Vertical Start Point 0 of Active Window (VSAW0)
    LCD_DataWrite(0x00); //Vertical Start Point of Active Window [7:0]
	//udelay(1); 
    LCD_CmdWrite(0x33); //Vertical Start Point 1 of Active Window (VSAW1)	   
    LCD_DataWrite(0x00); //Vertical Start Point of Active Window [8]
	//udelay(1); 
    LCD_CmdWrite(0x36); //Vertical End Point of Active Window 0 (VEAW0)
    LCD_DataWrite(0xdf); //Vertical End Point of Active Window [7:0]
	//udelay(1); 
    LCD_CmdWrite(0x37); //Vertical End Point of Active Window 1 (VEAW1)	   
    LCD_DataWrite(0x01); //Vertical End Point of Active Window [8]
	//udelay(1); 

#endif         

}


				
//------------------------//
//STATUS 
void Chk_Busy(void)
{
/*	u8 temp; 	
	do
	{
	temp=LCD_StatusRead();
	}while((temp&0x80)==0x80);
*/
	mdelay(1);	
}
void Chk_Busy_BTE(void)
{
/*	u8 temp;
   	
	do
	{
	 temp=LCD_StatusRead();
	}while((temp&0x40)==0x40);
*/	   
}

void Chk_Busy_DIR_Access(void)
{
/*	u8  temp;
   	
	do
	{
	 temp=LCD_StatusRead();
	}while((temp&0x01)==0x01);
*/	   
}

//REG[BFh]
void Chk_DMA_Busy(void)
{
	u8 temp; 	
	do
	{
	LCD_CmdWrite(0xBF);
	temp = LCD_DataRead();
	}while((temp&0x01)==0x01);   
}
//REG[01h]		 

void Display_ON(void)
{	
	LCD_CmdWrite(0x01);//PWRR
	LCD_DataWrite(0x80);
}

void Display_OFF(void)
{
	LCD_CmdWrite(0x01);//PWRR
	LCD_DataWrite(0x00);
}

void Normal_Mode_exitSleep(void)
{	
	LCD_CmdWrite(0x01);//PWRR
	LCD_DataWrite(0x00);
}
void Sleep_Mode(void)
{
	LCD_CmdWrite(0x01);//PWRR
	LCD_DataWrite(0x02);
}
void Software_Reset(void)
{	
	LCD_CmdWrite(0x01);//PWRR
	LCD_DataWrite(0x01);
	LCD_DataWrite(0x00);
	mdelay(1);// 
}							   
//-------------------------------//
//REG[04h] for test 
void PCLK_inversion(void)
{ 	u8 temp;
  	LCD_CmdWrite(0x04);//PWRR
	temp = LCD_DataRead();
	temp |= cSetD7;
	LCD_DataWrite(temp);
}
void PCLK_non_inversion(void)
{ 	u8 temp;
  	LCD_CmdWrite(0x04);//PWRR
	temp = LCD_DataRead();
	temp &= cClrD7;
	LCD_DataWrite(temp);
}

void PCLK_width(u8 setx) //bit[1:0]
{ 	u8 temp;
  	LCD_CmdWrite(0x04);//PWRR
	temp = LCD_DataRead();
	temp &=0x80;
	temp |= setx;
	LCD_DataWrite(temp);
}

//-------------------------------//
//REG[05h]
void Serial_ROM_select0(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=cClrD7;
	LCD_DataWrite(temp);
}

void Serial_ROM_select1(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp |=cSetD7;
	LCD_DataWrite(temp);
}

void Serial_ROM_Address_set_24bit(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=cClrD6;
	LCD_DataWrite(temp);
}

void Serial_ROM_Address_set_32bit(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp |=cSetD6;
	LCD_DataWrite(temp);
}

void Select_Serial_Waveform_mode0(void)
{	u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=cClrD5;
	LCD_DataWrite(temp);
}

void Select_Serial_Waveform_mode3(void)
{	u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp |=cSetD5;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Read_Cycle_4bus(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=0xE7;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Read_Cycle_5bus(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=0xE7;
	temp |=cSetD3;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Read_Cycle_6bus(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=0xE7;
	temp |=cSetD4;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Font_mode(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=cClrD2;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_DMA_mode(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp |=cSetD2;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Signal_mode(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=0xFC;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Dual_mode0(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=0xFC;
	temp |=cSetD1;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Dual_mode1(void)
{   u8 temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=0xFC;
	temp |=cSetD1;
	temp |=cSetD0;
	LCD_DataWrite(temp);
}

void SROM_CLK_DIV(u8 CLK_DIV)
{
	LCD_CmdWrite(0x06);
	LCD_DataWrite(CLK_DIV);
}


//-------------------------------//
//REG[10h]
void Color_256(void)
{
	u8 temp;
	LCD_CmdWrite(0x10);//SYSR
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	LCD_DataWrite(temp);
} 

void Color_65K(void)
{
	u8 temp;
	LCD_CmdWrite(0x10);//SYSR
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	temp |= cSetD3ClrD2 ;
	LCD_CmdWrite(0x10);//SYSR
	LCD_DataWrite(temp);
}
void MPU_8bit_Interface(void)
{
	u8 temp;
	LCD_CmdWrite(0x10);//SYSR
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	LCD_DataWrite(temp);
}

void MPU_16bit_Interface(void)
{
	u8 temp;
	LCD_CmdWrite(0x10);//SYSR
	temp = LCD_DataRead();
	temp |= cSetD1ClrD0 ;
	LCD_DataWrite(temp);
} 								 
//--------------------------------//
//REG[12h] 

u8 GPI_data(void)
{   u8 temp;
	LCD_CmdWrite(0x12);//SYSR
	temp = LCD_DataRead();
	return temp;
}

void GPO_data(u8 setx)
{
  LCD_CmdWrite(0x13); 
  LCD_DataWrite(setx);
}

							
//---------------------------------//
//REG[20h]

void One_Layer(void)
{
	u8 temp;
	LCD_CmdWrite(0x20);//DPCR
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);
}	
				 
void Two_Layers(void)
{	u8 temp;
	LCD_CmdWrite(0x20);//DPCR
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);
}

void HDIR_SEG0_SEGn(void)
{	u8 temp;
	LCD_CmdWrite(0x20);//DPCR
	temp = LCD_DataRead();
	temp &= cClrD3 ;
	LCD_DataWrite(temp);
}
void HDIR_SEGn_SEG0(void)
{
	u8 temp;

	LCD_CmdWrite(0x20);//DPCR
	temp = LCD_DataRead();
	temp |= cSetD3 ;
	LCD_DataWrite(temp);
}
void VDIR_COM0_COMn(void)
{
	u8 temp;

	LCD_CmdWrite(0x20);//DPCR
	temp = LCD_DataRead();
	temp &= cClrD2 ;
	LCD_DataWrite(temp);
}
void VDIR_COMn_COM0(void)
{
	u8 temp;

	LCD_CmdWrite(0x20);//DPCR
	temp = LCD_DataRead();
	temp |= cSetD2 ;
	LCD_DataWrite(temp);
}


//----------------------------------//
//REG[21h] 
void CGROM_Font(void)
{
	u8 temp;
	LCD_CmdWrite(0x21);//FNCR0
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);
}
void CGRAM_Font(void)
{
	u8 temp;
	LCD_CmdWrite(0x21);//FNCR0
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);
}

void Internal_CGROM(void)
{
	u8 temp;
	LCD_CmdWrite(0x21);//FNCR0
	temp = LCD_DataRead();
	temp &= cClrD5 ;
	LCD_DataWrite(temp);
}
void External_CGROM(void)
{
	u8 temp;
	LCD_CmdWrite(0x21);//FNCR0
	temp = LCD_DataRead();
	temp |= cSetD5 ;
	LCD_DataWrite(temp);
}

void ISO8859_1(void)
{
	u8 temp;
	LCD_CmdWrite(0x21);//FNCR0
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	LCD_DataWrite(temp);
}
void ISO8859_2(void)
{
	u8 temp;
	LCD_CmdWrite(0x21);//FNCR0
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	temp |= cClrD1SetD0 ;
	LCD_DataWrite(temp);
}
void ISO8859_3(void)
{
	u8 temp;
	LCD_CmdWrite(0x21);//FNCR0
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	temp |= cSetD1ClrD0 ;
	LCD_DataWrite(temp);
}
void ISO8859_4(void)
{
	u8 temp;
	LCD_CmdWrite(0x21);//FNCR0
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	temp |= cSetD1D0 ;
	LCD_DataWrite(temp);
}								 
//--------------------------------//
//REG[22h]

void No_FullAlignment(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);
}
void FullAlignment(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);
}
void Font_with_BackgroundColor(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD6 ;
	LCD_DataWrite(temp);
}
void Font_with_BackgroundTransparency(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp |= cSetD6 ;
	LCD_DataWrite(temp);
}


void NoRotate_Font(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD4 ;
	LCD_DataWrite(temp);
}
void Rotate90_Font(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp |= cSetD4 ;
	LCD_DataWrite(temp);
}


void Horizontal_FontEnlarge_x1(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	LCD_DataWrite(temp);
}
void Horizontal_FontEnlarge_x2(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	temp |= cClrD3SetD2 ;
	LCD_DataWrite(temp);
}
void Horizontal_FontEnlarge_x3(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	temp |= cSetD3ClrD2 ;
	LCD_DataWrite(temp);
}
void Horizontal_FontEnlarge_x4(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	temp |= cSetD3D2 ;
	LCD_DataWrite(temp);
}
void Vertical_FontEnlarge_x1(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	LCD_DataWrite(temp);
}
void Vertical_FontEnlarge_x2(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	temp |= cClrD1SetD0 ;
	LCD_DataWrite(temp);
}
void Vertical_FontEnlarge_x3(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	temp |= cSetD1ClrD0 ;
	LCD_DataWrite(temp);
}
void Vertical_FontEnlarge_x4(void)
{
	u8 temp;
	LCD_CmdWrite(0x22);//FNCR1
	temp = LCD_DataRead();
	temp &= cClrD1D0 ;
	temp |= cSetD1D0 ;
	LCD_DataWrite(temp);
}

//-------------------------------------------//
//REG[23h]									 
void CGRAM_Select_Number(u8 setx)
{ 
	LCD_CmdWrite(0x23);//CGSR
	LCD_DataWrite(setx);
}	
								
//-------------------------------------------//
//REG[24h]REG[25h]REG[26h]REG[27h]
void Scroll_Offset(u16 X,u16 Y)
{

	LCD_CmdWrite(0x24);//HOFS0
	LCD_DataWrite(X);
  
	LCD_CmdWrite(0x25);//HOFS1	   
	LCD_DataWrite(X>>8);

	  
	LCD_CmdWrite(0x26);//VOFS0
	LCD_DataWrite(Y);  

	LCD_CmdWrite(0x27);//VOFS1	   
	LCD_DataWrite(Y>>8); 
}	 
//-------------------------------------------//
//REG[29h]
void Line_distance(u8 setx)
{ 
	LCD_CmdWrite(0x29);//LDS
	LCD_DataWrite(setx);
}	  
//-------------------------------------------//
//REG[2Ah]REG[2Bh]REG[2Ch]REG[2Dh]
void Font_Coordinate(u16 X,u16 Y)
{
 
	LCD_CmdWrite(0x2A);//HOFS0
	LCD_DataWrite(X);

	LCD_CmdWrite(0x2B);//HOFS1	   
	LCD_DataWrite(X>>8);

 
	LCD_CmdWrite(0x2C);//VOFS0
	LCD_DataWrite(Y);

	LCD_CmdWrite(0x2D);//VOFS1	   
	LCD_DataWrite(Y>>8); 
}


//-------------------------------------------//
//REG[2Eh]
void Font_size_16x16_8x16(void) 
{
 	u8 temp;
	LCD_CmdWrite(0x2E);//FNCR1
	temp = LCD_DataRead();
	temp &= 0x3f;
	LCD_DataWrite(temp);
}

void Font_size_24x24_12x24(void) 
{
 	u8 temp;
	LCD_CmdWrite(0x2E);//FNCR1
	temp = LCD_DataRead();
	temp &= 0x3f;
	temp |= 0x40; 
	LCD_DataWrite(temp);
}

void Font_size_32x32_16x32(void) 
{
 	u8 temp;
	LCD_CmdWrite(0x2E);//FNCR1
	temp = LCD_DataRead();
	temp &= 0x3f;
	temp |= 0x80; 
	LCD_DataWrite(temp);
}


void Font_spacing_set(u8 setx) //bit[5:0]
{   u8 temp,temp1;
	temp1=setx&0x3F;
   	LCD_CmdWrite(0x2E);//FNCR1
	temp = LCD_DataRead();
	temp &= 0xc0;
	temp |= temp1; 
	LCD_DataWrite(temp);

}

//-------------------------------------------//
//REG[2Fh]
void GT_serial_ROM_select_GT21L16T1W(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0x1f;
  LCD_DataWrite(temp);
}

void GT_serial_ROM_select_GT23L16U2W(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0x1f;
  temp |= 0x20;
  LCD_DataWrite(temp);
}

void GT_serial_ROM_select_GT23L24T3Y(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0x1f;
  temp |= 0x40;
  LCD_DataWrite(temp);
}

void GT_serial_ROM_select_GT23L24M1Z(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0x1f;
  temp |= 0x60;
  LCD_DataWrite(temp);
}

void GT_serial_ROM_select_GT23L32S4W(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0x1f;
  temp |= 0x80;
  LCD_DataWrite(temp);
}

void Font_code_GB2312(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xE3;
  LCD_DataWrite(temp);
}

void Font_code_GB12345(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xE3;
   temp |= 0x04;
  LCD_DataWrite(temp);
}

void Font_code_BIG5(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xE3;
  temp |= 0x08;
  LCD_DataWrite(temp);
}

void Font_code_UNICODE(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xE3;
  temp |= 0x0C;
  LCD_DataWrite(temp);
}

void Font_code_ASCII(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xE3;
  temp |= 0x10;
  LCD_DataWrite(temp);
}

void Font_code_UNIJIS(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xE3;
  temp |= 0x14;
  LCD_DataWrite(temp);
}

void Font_code_JIS0208(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xE3;
  temp |= 0x18;
  LCD_DataWrite(temp);
}

void Font_code_LATIN(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xE3;
  temp |= 0x1C;
  LCD_DataWrite(temp);
}

void Font_Standard(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xFC;
  LCD_DataWrite(temp);
}

void Font_Arial(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xFC;
  temp |= 0x01;
  LCD_DataWrite(temp);
}

void Font_Roman(void)
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= 0xFC;
  temp |= 0x02;
  LCD_DataWrite(temp);
}

void Font_Bold(void) //for ASCII
{ u8 temp;
  LCD_CmdWrite(0x2F);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD1D0;
  temp |= cSetD1D0;
  LCD_DataWrite(temp);
}

//-------------------------------------------//
//REG[30h]~REG[37h]
void Active_Window(u16 XL,u16 XR ,u16 YT ,u16 YB)
{
	//setting active window X
  
	LCD_CmdWrite(0x30);//HSAW0
	LCD_DataWrite(XL); 
	LCD_CmdWrite(0x31);//HSAW1	   
	LCD_DataWrite(XL>>8);

	LCD_CmdWrite(0x34);//HEAW0
	LCD_DataWrite(XR);
	LCD_CmdWrite(0x35);//HEAW1	   
	LCD_DataWrite(XR>>8);

	//setting active window Y
  
	LCD_CmdWrite(0x32);//VSAW0
	LCD_DataWrite(YT);  
	LCD_CmdWrite(0x33);//VSAW1	   
	LCD_DataWrite(YT>>8);
  
	LCD_CmdWrite(0x36);//VEAW0
	LCD_DataWrite(YB); 
	LCD_CmdWrite(0x37);//VEAW1	   
	LCD_DataWrite(YB>>8);
}
//--------------------------------------------//
//REG[38h]~REG[3Fh]

void Scroll_Window(u16 XL,u16 XR ,u16 YT ,u16 YB)
{
 
	LCD_CmdWrite(0x38);//HSSW0
	LCD_DataWrite(XL);
	LCD_CmdWrite(0x39);//HSSW1	   
	LCD_DataWrite(XL>>8);
  
	LCD_CmdWrite(0x3c);//HESW0
	LCD_DataWrite(XR);  
	LCD_CmdWrite(0x3d);//HESW1	   
	LCD_DataWrite(XR>>8);   
	
	LCD_CmdWrite(0x3a);//VSSW0
	LCD_DataWrite(YT);
	LCD_CmdWrite(0x3b);//VSSW1	   
	LCD_DataWrite(YT>>8);
  
	LCD_CmdWrite(0x3e);//VESW0
	LCD_DataWrite(YB);  
	LCD_CmdWrite(0x3f);//VESW1	   
	LCD_DataWrite(YB>>8);
}  


//--------------------------------------------//
//REG[40h]
void Graphic_Mode(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);
}

void Text_Mode(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);	 
} 

void Text_Cursor_Disable(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD6 ;
	LCD_DataWrite(temp);
}

void Text_Cursor_Enable(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp |= cSetD6 ;
	LCD_DataWrite(temp);	 	
} 

void Text_Cursor_Blink_Disable(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD5 ;
	LCD_DataWrite(temp);
}

void Text_Cursor_Blink_Enable(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp |= cSetD5 ;
	LCD_DataWrite(temp);
}

void Memory_Write_LeftRight_TopDown(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	LCD_DataWrite(temp);
}

void Memory_Write_RightLeft_TopDown(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	temp |= cClrD3SetD2 ;
	LCD_DataWrite(temp);
}

void Memory_Write_DownTop_LeftRight(void)
{	u8 temp;	
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	temp |= cSetD3D2 ;
	LCD_DataWrite(temp);
}

void Memory_Write_TopDown_LeftRight(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	temp |= cSetD3ClrD2 ;
	LCD_DataWrite(temp);
} 

void MemoryWrite_Cursor_autoIncrease(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD1 ;
	LCD_DataWrite(temp);
}

void MemoryWrite_Cursor_NoautoIncrease(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp |= cSetD1 ;
	LCD_DataWrite(temp);
}

void MemoryRead_Cursor_autoIncrease(void)
{	u8 temp;
	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp &= cClrD0 ;
	LCD_DataWrite(temp);
}

void MemoryRead_Cursor_NoautoIncrease(void)
{
	u8 temp;

	LCD_CmdWrite(0x40);//MWCR0
	temp = LCD_DataRead();
	temp |= cSetD0 ;
	LCD_DataWrite(temp);
}  										 

//--------------------------------------------//
//REG[41h]
void No_Graphic_Cursor(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);
}

void Graphic_Cursor(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);
}

void Graphic_Cursor_Set1(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD6D5D4;
	LCD_DataWrite(temp);
}

void Graphic_Cursor_Set2(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD6D5D4 ;
	temp |= cClrD6D5SetD4 ;
	LCD_DataWrite(temp);
}

void Graphic_Cursor_Set3(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD6D5D4 ;
	temp |= cClrD6SetD5ClrD4 ;
	LCD_DataWrite(temp);
}

void Graphic_Cursor_Set4(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD6D5D4 ;
	temp |= cClrD6SetD5D4 ;
	LCD_DataWrite(temp);
}

void Graphic_Cursor_Set5(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD6D5D4 ;
	temp |= cSetD6ClrD5D4 ;
	LCD_DataWrite(temp);
}

void Graphic_Cursor_Set6(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD6D5D4 ;
	temp |= cSetD6ClrD5SetD4 ;
	LCD_DataWrite(temp);
}

void Graphic_Cursor_Set7(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD6D5D4 ;
	temp |= cSetD6D5ClrD4 ;
	LCD_DataWrite(temp);
}

void Graphic_Cursor_Set8(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD6D5D4 ;
	temp |= cSetD6D5D4 ;
	LCD_DataWrite(temp);
}

void Write_To_Bank1and2(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD3D2 ;
	LCD_DataWrite(temp);
}

void Write_To_CGRAM(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= 0xf3;
	temp |= cClrD3SetD2 ;
	LCD_DataWrite(temp);
}

void Write_To_GraphicCursor(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= 0xf3;
	temp |= cSetD3ClrD2 ;
	LCD_DataWrite(temp);
}

void Write_To_Pattern(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= 0xf3;
	temp |= cSetD3D2 ;
	LCD_DataWrite(temp);
}
						   
void Write_To_Bank1(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp &= cClrD0 ;
	LCD_DataWrite(temp);
}

void Write_To_Bank2(void)
{	u8 temp;
	LCD_CmdWrite(0x41);//MWCR1
	temp = LCD_DataRead();
	temp |= cSetD0 ;
	LCD_DataWrite(temp);  
}	
							
//--------------------------------------------//
//--------------------------------------------//
//REG[44h]
void Text_Blink_Time(u8 setx)
{	
	LCD_CmdWrite(0x44);//CURS
	LCD_DataWrite(setx);
}

//--------------------------------------------//
//REG[45h]  
void Memory_read_LeftRight_TopDown(void)
{	u8 temp;
	LCD_CmdWrite(0x45);//MRCD
	temp = LCD_DataRead();
	temp &= cClrD1D0;
	LCD_DataWrite(temp);
}
void Memory_read_RightLeft_TopDown(void)
{	u8 temp;
	LCD_CmdWrite(0x45);//MRCD
	temp = LCD_DataRead();
	temp |= cClrD1SetD0;
	LCD_DataWrite(temp);
}
void Memory_read_TopDown_LeftRight(void)
{	u8 temp;
	LCD_CmdWrite(0x45);//MRCD
	temp = LCD_DataRead();
	temp |= cSetD1ClrD0;
	LCD_DataWrite(temp);
}
void Memory_read_DownTop_LeftRight(void)
{	u8 temp;
	LCD_CmdWrite(0x45);//MRCD
	temp = LCD_DataRead();
	temp |= cSetD1D0;
	LCD_DataWrite(temp);
}			

//--------------------------------------------//
//REG[46h]~REG[49h]
void XY_Coordinate(u16 X,u16 Y)
{
	LCD_CmdWrite(0x46);
	LCD_DataWrite(X);  
	LCD_CmdWrite(0x47);	   
	LCD_DataWrite(X>>8);
 
	LCD_CmdWrite(0x48);
	LCD_DataWrite(Y);  
	LCD_CmdWrite(0x49);	   
	LCD_DataWrite(Y>>8);
}



//--------------------------------------------//
//REG[4Ah]~REG[4Dh]
void Memory_read_Coordinate(u16 X,u16 Y)
{

	LCD_CmdWrite(0x4a);
	LCD_DataWrite(X);   
	LCD_CmdWrite(0x4b);	   
	LCD_DataWrite(X>>8);
   
	LCD_CmdWrite(0x4c);
	LCD_DataWrite(Y);
	LCD_CmdWrite(0x4d);	   
	LCD_DataWrite(Y>>8);
} 
						  
//--------------------------------------------//
//REG[4Eh]
void Text_Cursor_Horizontal_Size(u8 setx)//bit[3:0]
{
	LCD_CmdWrite(0x4E);//CURS	   
	LCD_DataWrite(setx);
} 
								
//REG[4Fh] 
void Text_Cursor_Vertical_Size(u8 setx)//bit[3:0]
{
	LCD_CmdWrite(0x4F);//CURS	   
	LCD_DataWrite(setx);
} 	
	
//--------------------------------------------//
//REG[50h] 
void no_BTE_write(void)
{	u8 temp;
	LCD_CmdWrite(0x50);//BECR0
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);  
}

void BTE_enable(void)
{	u8 temp;
	LCD_CmdWrite(0x50);//BECR0
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);  
}

void BTE_contiguous_Data(void)
{	u8 temp;
	LCD_CmdWrite(0x50);//BECR0
	temp = LCD_DataRead();
	temp |= cSetD6 ;
	LCD_DataWrite(temp);  
}

void BTE_rectangular_Data(void)
{	u8 temp;												   
	LCD_CmdWrite(0x50);//BECR0
	temp = LCD_DataRead();
	temp &= cClrD6 ;
	LCD_DataWrite(temp);  
}									  

//---------------------------------------------//
//REG[51h] 
void BTE_ROP_Code(u8 setx)
{	 
	LCD_CmdWrite(0x51);//BECR1	   
	LCD_DataWrite(setx); 
}									   

//---------------------------------------------//
//REG[52h] 
void Layer1_Visible(void)
{	u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0xf8;
	LCD_DataWrite(temp);  
}

void Layer2_Visible(void)
{   u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0xf8;
	temp|=0x01;
	LCD_DataWrite(temp);  
}	
						
void Transparent_Mode(void)
{	u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0xf8;
	temp|=0x03;
	LCD_DataWrite(temp);  
}

void Lighten_Overlay_Mode(void)
{   u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0xf8;
	temp|=0x02;
	LCD_DataWrite(temp);  
}	
						
void Boolean_OR(void)
{   u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0xf8;
	temp|=0x04;
	LCD_DataWrite(temp);
}

void Boolean_AND(void)
{	u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0xf8;
	temp|=0x05;
	LCD_DataWrite(temp);  
}  	 
	
  
void Floating_window_mode(void)
{	u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0xf8;
	temp|=0x06;
	LCD_DataWrite(temp);  
} 

void Floating_Window_transparent_with_BGTR_enable(void)
{   u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp|=cSetD5;
	LCD_DataWrite(temp);  
}

void Floating_Window_transparent_with_BGTR_disable(void)
{   u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=cClrD5;
	LCD_DataWrite(temp);  
}


void Layer1_2_scroll(void)
{	u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0x3f;
	LCD_DataWrite(temp);  
}  	 

void Layer1_scroll(void)
{	u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0x3f;
	temp|=0x40;
	LCD_DataWrite(temp);  
} 

void Layer2_scroll(void)
{	u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0x3f;
	temp|=0x80;
	LCD_DataWrite(temp);  
} 

void Buffer_scroll(void)
{	u8 temp;
	LCD_CmdWrite(0x52);//LTPR0
	temp = LCD_DataRead();
	temp&=0x3f;
	temp|=0xC0;
	LCD_DataWrite(temp);  
} 

//---------------------------------------------//
//REG[53h] 
void layer2_1_transparency(u8 setx)
{  
   LCD_CmdWrite(0x53);//LTPR1
   LCD_DataWrite(setx); 
}

//---------------------------------------------//
//REG[54h]~ [5Fh]
void BTE_Source_Destination	(u16 XL,u16 XR ,u16 YT ,u16 YB)
{
	u8 temp,temp1;
	
	temp=XL;   
	LCD_CmdWrite(0x54);//HSBE0
	LCD_DataWrite(temp);
	temp=XL>>8;   
	LCD_CmdWrite(0x55);//HSBE1	   
	LCD_DataWrite(temp);

	temp=XR;   
	LCD_CmdWrite(0x58);//HDBE0
	LCD_DataWrite(temp);
	temp=XR>>8;   
	LCD_CmdWrite(0x59);//HDBE1	   
	LCD_DataWrite(temp); 
	
	temp=YT;   
	LCD_CmdWrite(0x56);//VSBE0
	LCD_DataWrite(temp);
	temp=YT>>8;   
	LCD_CmdWrite(0x57);//VSBE1
	temp1 = LCD_DataRead();
	temp1 &= 0x80;
	temp=temp|temp1; 
	LCD_CmdWrite(0x57);//VSBE1  
	LCD_DataWrite(temp);


	temp=YB;   
	LCD_CmdWrite(0x5a);//VDBE0
	LCD_DataWrite(temp);
	temp=YB>>8;   
	LCD_CmdWrite(0x5b);//VDBE1
	temp1 = LCD_DataRead();
	temp1 &= 0x80;
	temp=temp|temp1;	
	LCD_CmdWrite(0x5b);//VDBE1   
	LCD_DataWrite(temp);
}							

void Source_Layer1(void)
{   u8 temp;	
	LCD_CmdWrite(0x57);//VSBE1
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);
}

void Source_Layer2(void)
{	u8 temp;	
	LCD_CmdWrite(0x57);//VSBE1
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);
}

void Destination_Layer1(void)
{	u8 temp;	
	LCD_CmdWrite(0x5b);//VDBE1
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);
}

void Destination_Layer2(void)
{	u8 temp;	
	LCD_CmdWrite(0x5b);//VDBE1
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);
}
		  
//---------------------------------------------//
//---------------------------------------------//
void BTE_Size_setting(u16 X,u16 Y)
{	 
	LCD_CmdWrite(0x5c);//BEWR0
	LCD_DataWrite(X); 
	LCD_CmdWrite(0x5d);//BEWR1	   
	LCD_DataWrite(X>>8);
  
	LCD_CmdWrite(0x5e);//BEHR0
	LCD_DataWrite(Y);   
	LCD_CmdWrite(0x5f);//BEHR1	   
	LCD_DataWrite(Y>>8);
}									 

//---------------------------------------------//
//REG[60h]~REG[67h]

void Background_color(u16 color)
{
 #ifdef Color65k
	LCD_CmdWrite(0x60);
	LCD_DataWrite((color&0xf800)>>11);
	LCD_CmdWrite(0x61);
	LCD_DataWrite((color&0x07e0)>>5);
	LCD_CmdWrite(0x62);
	LCD_DataWrite((color&0x001f));
 #endif
	
 #ifdef Color256
	LCD_CmdWrite(0x60);
	LCD_DataWrite((color&0xf800)>>13);
	
	LCD_CmdWrite(0x61);
	LCD_DataWrite((color&0x07e0)>>8);
	
	LCD_CmdWrite(0x62);
	LCD_DataWrite((color&0x001f)>>3);
 #endif
}

 void Text_color(u16 color) 
{
 #ifdef Color65k
	LCD_CmdWrite(0x63);
	LCD_DataWrite((color&0xf800)>>11);
	
	LCD_CmdWrite(0x64);
	LCD_DataWrite((color&0x07e0)>>5);
	
	LCD_CmdWrite(0x65);
	LCD_DataWrite((color&0x001f));
 #endif
 
  #ifdef Color256
	LCD_CmdWrite(0x63);
	LCD_DataWrite((color&0xf800)>>13);
	
	LCD_CmdWrite(0x64);
	LCD_DataWrite((color&0x07e0)>>8);
	
	LCD_CmdWrite(0x65);
	LCD_DataWrite((color&0x001f)>>3);
 #endif
 
}

void Text_Background_Color(u8 setR,u8 setG,u8 setB)
{
	LCD_CmdWrite(0x60);//BGCR0
	LCD_DataWrite(setR);
   
	LCD_CmdWrite(0x61);//BGCR0
	LCD_DataWrite(setG);

	LCD_CmdWrite(0x62);//BGCR0
	LCD_DataWrite(setB);
} 

void Text_Foreground_Color(u8 setR,u8 setG,u8 setB)
{		
	LCD_CmdWrite(0x63);//BGCR0
	LCD_DataWrite(setR);
   
	LCD_CmdWrite(0x64);//BGCR0
	LCD_DataWrite(setG);

	LCD_CmdWrite(0x65);//BGCR0
	LCD_DataWrite(setB);

}
//======================================
	
void Pattern_Set_8x8(void)
{  u8 temp;

 LCD_CmdWrite(0x66);//PTNO
 temp = LCD_DataRead();
 temp &= cClrD7;
 LCD_DataWrite(temp);
}	

void Pattern_Set_16x16(void)
{  u8  temp;

 LCD_CmdWrite(0x66);//PTNO
 temp = LCD_DataRead();
 temp |= cSetD7; 
 LCD_DataWrite(temp);
}								


void Pattern_Set_number(u8 setx)
{   u8 temp;
		
	LCD_CmdWrite(0x66);//PTNO
	temp = LCD_DataRead();
	temp &= 0x80;	
	LCD_DataWrite(temp|setx);
} 	
							
void BackgroundColor_TransparentMode(u16 color)
{
#ifdef Color65k
	LCD_CmdWrite(0x67);
	LCD_DataWrite((color&0xf800)>>11);
	
	LCD_CmdWrite(0x68);
	LCD_DataWrite((color&0x07e0)>>5);
	
	LCD_CmdWrite(0x69);
	LCD_DataWrite((color&0x001f));
 #endif
	
 #ifdef Color256
	LCD_CmdWrite(0x67);
	LCD_DataWrite((color&0xf800)>>13);
	
	LCD_CmdWrite(0x68);
	LCD_DataWrite((color&0x07e0)>>8);
	
	LCD_CmdWrite(0x69);
	LCD_DataWrite((color&0x001f)>>3);
 #endif

}	  

//REG[70h]~REG[74h]
//==============================================================================
//Subroutine:	Enable_TP 
//==============================================================================
void Enable_TP(void)
{   u8 temp;	  
	LCD_CmdWrite(0x70);//TPCR0	
	temp = LCD_DataRead();
	temp |= cSetD7;   
	LCD_DataWrite(temp);
}
//==============================================================================
//Subroutine:	Disable_TP 
//==============================================================================
void Disable_TP(void)
{ u8 temp;
  LCD_CmdWrite(0x70);//TPCR0
  temp = LCD_DataRead();
  temp &= cClrD7;   
  LCD_DataWrite(temp);
 }

//==============================================================================
//Subroutine:	Enable_Touch_WakeUp
//==============================================================================
void Enable_Touch_WakeUp(void)
{
	u8 temp;
	LCD_CmdWrite(0x70);//TPCR0	
	temp = LCD_DataRead();
	temp |= cSetD3;   //cSetb3 = 00001000
	LCD_DataWrite(temp);
}
//==============================================================================
//Subroutine:	Disable_Touch_WakeUp
//==============================================================================
void Disable_Touch_WakeUp(void)
{	u8 temp;
	LCD_CmdWrite(0x70);//TPCR0	
	temp = LCD_DataRead();
	temp &= cClrD3;
	LCD_DataWrite(temp);
}

//==============================================================================
//Subroutine:	TP manual or auto  mode enable
//==============================================================================
void TP_manual_mode(void)
{	u8 temp;
  	LCD_CmdWrite(0x71);//TPCR1	
	temp = LCD_DataRead();
	temp |= cSetD6;
	LCD_DataWrite(temp);
}
void TP_auto_mode(void)
{	u8 temp;
  	LCD_CmdWrite(0x71);//TPCR1	
	temp = LCD_DataRead();
	temp &= cClrD6;
	LCD_DataWrite(temp);
}
//==============================================================================
//Subroutine:	TP_IDLE_mode
//==============================================================================
void TP_IDLE_mode(void)
{ u8 temp;
  LCD_CmdWrite(0x71);//TPCR1
  temp=LCD_DataRead(); 
  temp &= 0xf0;
  LCD_DataWrite(temp);
 }
//==============================================================================
//Subroutine:	TP_event_mode
//==============================================================================
void TP_event_mode(void)
{ u8 temp;
  LCD_CmdWrite(0x71);//TPCR1
  temp=LCD_DataRead(); 
  temp &= 0xf0;
  temp |= 0x01;
  LCD_DataWrite(temp);
//  LCD_DataWrite(0xc1);
}
//==============================================================================
//Subroutine:	TP_latch_X
//==============================================================================
void TP_latch_X(void)
{ u8 temp;
  LCD_CmdWrite(0x71);//TPCR1
  temp=LCD_DataRead(); 
  temp &= 0xc0;
  temp |= 0x02;
  LCD_DataWrite(temp);
 }
 //==============================================================================
//Subroutine:	TP_latch_Y
//==============================================================================
void TP_latch_Y(void)
{ u8 temp;
  LCD_CmdWrite(0x71);//TPCR1
  temp=LCD_DataRead(); 
  temp &= 0xc0;
  temp |= 0x03;
  LCD_DataWrite(temp);
 }
//==============================================================================
//Subroutine:	Detect_TP_X_Y coordinate 
//==============================================================================
u8 ADC_X(void)
{	u8 temp;
	LCD_CmdWrite(0x72);//TPXH	 X_coordinate high byte
	//Chk_Busy();
	temp=LCD_DataRead();
	return temp;
}

u8 ADC_Y(void)
{	u8 temp;
	LCD_CmdWrite(0x73);//TPYH	  Y_coordinate high byte
	//Chk_Busy();
	temp=LCD_DataRead();
	return temp;
}

u8 ADC_XY(void)
{	u8 temp;
 	LCD_CmdWrite(0x74);//TPXYL	  bit[3:2] Y_coordinate low byte  bit[1:0] X_coordinate low byte 
	temp=LCD_DataRead();
	return temp;
}   



//REG[80h]~REG[83h]
void Graphic_Cursor_Coordinate(u16 X,u16 Y)
{
	LCD_CmdWrite(0x80);
	LCD_DataWrite(X);  
	LCD_CmdWrite(0x81);	   
	LCD_DataWrite(X>>8);
  
	LCD_CmdWrite(0x82);
	LCD_DataWrite(Y);  
	LCD_CmdWrite(0x83);	   
	LCD_DataWrite(Y>>8);
}

//---------------------------------//
//REG[84h]

void Graphic_Cursor_Color_0(u8 setx)
{	  
	LCD_CmdWrite(0x84);//GCC0
	LCD_DataWrite(setx); 
}  									  

void Graphic_Cursor_Color_1(u8 setx)
{	 
	LCD_CmdWrite(0x85);//GCC1
	LCD_DataWrite(setx); 
}  	
 	 						  
//---------------------------------------------//
//REG[8A]
void PWM1_enable(void)
{
	u8 temp;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);  
 }

void PWM1_disable(void)
{
	u8 temp;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);  
 }

void PWM1_disable_level_low(void)
{
	u8 temp;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD6 ;
	LCD_DataWrite(temp);  
}

void PWM1_disable_level_high(void)
{
	u8 temp;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD6 ;
	LCD_DataWrite(temp);  
}

 void PWM1_fnuction_sel(void)
{
	u8 temp;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD4 ;
	LCD_DataWrite(temp);  
 }

 void PWM1_system_clk_out(void)
{
	u8 temp;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD4 ;
	LCD_DataWrite(temp);  
 }

 void PWM1_clock_ratio(u8 setx) //bit0~3 
{
	u8 temp,temp1;
	temp1= setx&0x0f;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp &= 0xf0;
	temp |= temp1 ;
	LCD_DataWrite(temp);  
 }

 void PWM1_duty_cycle(u8 setx) //bit0~7
{
  
	LCD_CmdWrite(0x8b);//PTNO
	LCD_DataWrite(setx);
} 	

void PWM2_enable(void)
{
	u8 temp;
	LCD_CmdWrite(0x8c);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);  
 }

void PWM2_disable(void)
{
	u8 temp;
	LCD_CmdWrite(0x8c);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);  
 }

void PWM2_disable_level_low(void)
{
	u8 temp;
	LCD_CmdWrite(0x8c);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD6 ;
	LCD_DataWrite(temp);  
}

void PWM2_disable_level_high(void)
{
	u8 temp;
	LCD_CmdWrite(0x8c);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD6 ;
	LCD_DataWrite(temp);  
}

 void PWM2_fnuction_sel(void)
{
	u8 temp;
	LCD_CmdWrite(0x8c);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD4 ;
	LCD_DataWrite(temp);  
 }

  void PWM2_system_clk_out(void)
{
	u8 temp;
	LCD_CmdWrite(0x8c);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD4 ;
	LCD_DataWrite(temp);  
 }

  void PWM2_clock_ratio(u8 setx) //bit0~3 
{
	u8 temp,temp1;
	temp1= setx&0x0f;
	LCD_CmdWrite(0x8c);//MCLR
	temp = LCD_DataRead();
	temp &= 0xf0;
	temp |= temp1 ;
	LCD_DataWrite(temp);  
 }
 void PWM2_duty_cycle(u8 setx) //bit0~7
{  
	LCD_CmdWrite(0x8d);//PTNO
	LCD_DataWrite(setx);
} 	


//---------------------------------------------//
//REG[8Eh]
void Stop_Memory_Clear(void)
{
	u8 temp;
	LCD_CmdWrite(0x8e);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD7 ;
	LCD_DataWrite(temp);  
}						 
void Memory_Clear(void)
{
	u8 temp;
	LCD_CmdWrite(0x8e);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp); 
	Chk_Busy(); 
}
void Clear_Full_Window(void)
{
	u8 temp;
	LCD_CmdWrite(0x8e);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD6 ;
	LCD_DataWrite(temp);  
}
void Clear_Active_Window(void)
{
	u8 temp;
	LCD_CmdWrite(0x8e);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD6 ;
	LCD_DataWrite(temp);  
}

									
//---------------------------------------------//
//REG[90h] 
void Draw_line(void)
{ 
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x00);
  LCD_DataWrite(0x80);
  Chk_Busy();
}

void Draw_square(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x10);
  LCD_DataWrite(0x90);
  Chk_Busy();
}

void Draw_square_fill(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x10);
  LCD_DataWrite(0xb0);
  Chk_Busy();
}

void Draw_circle(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x40);
  Chk_Busy();
}

void Draw_circle_fill(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x60);
  Chk_Busy();
}

void Draw_Triangle(void)
{
   LCD_CmdWrite(0x90);//DCR
   LCD_DataWrite(0x00);
   LCD_DataWrite(0x81);
   Chk_Busy();
}

void Draw_Triangle_fill(void)
{
   LCD_CmdWrite(0x90);//DCR
   LCD_DataWrite(0x01);
   LCD_DataWrite(0xA1);
   Chk_Busy();
}

//---------------------------------------------//
//REG[90h]~/EG[9Dh]  									
void Geometric_Coordinate(u16 XL,u16 XR ,u16 YT ,u16 YB)
{	  
	LCD_CmdWrite(0x91);
	LCD_DataWrite(XL);   
	LCD_CmdWrite(0x92);	   
	LCD_DataWrite(XL>>8);
  
	LCD_CmdWrite(0x95);
	LCD_DataWrite(XR);  
	LCD_CmdWrite(0x96);	   
	LCD_DataWrite(XR>>8);
		 
	LCD_CmdWrite(0x93);
	LCD_DataWrite(YT);  
	LCD_CmdWrite(0x94);	   
	LCD_DataWrite(YT>>8);
   
	LCD_CmdWrite(0x97);
	LCD_DataWrite(YB);   
	LCD_CmdWrite(0x98);	   
	LCD_DataWrite(YB>>8);
}

void Circle_Coordinate_Radius(u16 X,u16 Y,u16 R)
{
	  
	LCD_CmdWrite(0x99);
	LCD_DataWrite(X);  
	LCD_CmdWrite(0x9a);	   
	LCD_DataWrite(X>>8);  
	   
	LCD_CmdWrite(0x9b);
	LCD_DataWrite(Y); 
	LCD_CmdWrite(0x9c);	   
	LCD_DataWrite(Y>>8);
 
	LCD_CmdWrite(0x9d);
	LCD_DataWrite(R);
} 

//---------------------------------------------//
//REG[A0h] 
void Draw_Ellipse(void)
{
   LCD_CmdWrite(0xA0);//DCR
   LCD_DataWrite(0x00);
   LCD_DataWrite(0x80);
   Chk_Busy();
}

void Draw_Ellipse_Curve(void)
{  u8 temp;

   LCD_CmdWrite(0xA0);//DCR
   temp = LCD_DataRead();
   temp &=0x1F;
   temp |= 0x90;
   LCD_DataWrite(temp);
}

void Draw_Ellipse_Curve_Fill(void)
{  u8 temp;

   LCD_CmdWrite(0xA0);//DCR
   temp = LCD_DataRead();
   temp &=0x1F;
   temp |= 0xD0;
   LCD_DataWrite(temp);
}

void Draw_Ellipse_fill(void)
{
   LCD_CmdWrite(0xA0);//DCR
   LCD_DataWrite(0x40);
   LCD_DataWrite(0xC0);
   Chk_Busy();
}

void Draw_Circle_Square(void)
{
   LCD_CmdWrite(0xA0);//DCR
   LCD_DataWrite(0x20);
   LCD_DataWrite(0xA0);
   Chk_Busy();
}

void Draw_Circle_Square_fill(void)
{
   LCD_CmdWrite(0xA0);//DCR
   LCD_DataWrite(0x60);
   LCD_DataWrite(0xE0);
   Chk_Busy();
}


void Draw_Ellipse_Curve_part(u8 setx)
{
   u8 temp,temp1;
   LCD_CmdWrite(0xA0);//DCR
   temp = LCD_DataRead();
   temp1 = setx&0x03;
   temp &=0xfc;
   temp |=temp1;
   LCD_DataWrite(temp);   
}


void Ellipse_Coordinate_setting(u16 X,u16 Y,u16 ELL_A,u16 ELL_B)
{

	LCD_CmdWrite(0xA5);
	LCD_DataWrite(X);
	LCD_CmdWrite(0xA6);	   
	LCD_DataWrite(X>>8);  
	   
	LCD_CmdWrite(0xA7);
	LCD_DataWrite(Y); 
	LCD_CmdWrite(0xA8);	   
	LCD_DataWrite(Y>>8);
  
	LCD_CmdWrite(0xA1);
	LCD_DataWrite(ELL_A);
LCD_CmdWrite(0xA2);
	LCD_DataWrite(ELL_A>>8);
  
	LCD_CmdWrite(0xA3);
	LCD_DataWrite(ELL_B);
	LCD_CmdWrite(0xA4);
	LCD_DataWrite(ELL_B>>8);
} 



void Circle_Square_Coordinate_setting(u16 XL,u16 XR ,u16 YT ,u16 YB ,u16 ELL_A,u16 ELL_B)
{		
  
	LCD_CmdWrite(0x91);
	LCD_DataWrite(XL);  
	LCD_CmdWrite(0x92);	   
	LCD_DataWrite(XL>>8);

	LCD_CmdWrite(0x95);
	LCD_DataWrite(XR);   
	LCD_CmdWrite(0x96);	   
	LCD_DataWrite(XR>>8);
		 
	LCD_CmdWrite(0x93);
	LCD_DataWrite(YT);  
	LCD_CmdWrite(0x94);	   
	LCD_DataWrite(YT>>8);

	LCD_CmdWrite(0x97);
	LCD_DataWrite(YB);  
	LCD_CmdWrite(0x98);	   
	LCD_DataWrite(YB>>8);
  
	LCD_CmdWrite(0xA1);
	LCD_DataWrite(ELL_A);
	LCD_CmdWrite(0xA2);
	LCD_DataWrite(ELL_A>>8);
 
	LCD_CmdWrite(0xA3);
	LCD_DataWrite(ELL_B);
	LCD_CmdWrite(0xA4);
	LCD_DataWrite(ELL_B>>8); 
}

 
void Draw_Triangle_3point_Coordinate(u16 P1_X,u16 P1_Y,u16 P2_X,u16 P2_Y,u16 P3_X,u16 P3_Y)
{		
  
	LCD_CmdWrite(0x91);
	LCD_DataWrite(P1_X);  
	LCD_CmdWrite(0x92);	   
	LCD_DataWrite(P1_X>>8);
  
	LCD_CmdWrite(0x93);
	LCD_DataWrite(P1_Y);  
	LCD_CmdWrite(0x94);	   
	LCD_DataWrite(P1_Y>>8);
 
	LCD_CmdWrite(0x95);
	LCD_DataWrite(P2_X);  
	LCD_CmdWrite(0x96);	   
	LCD_DataWrite(P2_X>>8);
 
	LCD_CmdWrite(0x97);
	LCD_DataWrite(P2_Y);  
	LCD_CmdWrite(0x98);	   
	LCD_DataWrite(P2_Y>>8);

	LCD_CmdWrite(0xA9);
	LCD_DataWrite(P3_X);  
	LCD_CmdWrite(0xAA);	   
	LCD_DataWrite(P3_X>>8);
  
	LCD_CmdWrite(0xAB);
	LCD_DataWrite(P3_Y);   
	LCD_CmdWrite(0xAC);	   
	LCD_DataWrite(P3_Y>>8);   
}

//---------------------------------------------//
//REG[B0]~REG[B3]
void DMA_Start_address_setting(u32 set_address)
{ 
  LCD_CmdWrite(0xB0);
  LCD_DataWrite(set_address);

  LCD_CmdWrite(0xB1);
  LCD_DataWrite(set_address>>8);

  LCD_CmdWrite(0xB2);
  LCD_DataWrite(set_address>>16);

  LCD_CmdWrite(0xB3);
  LCD_DataWrite(set_address>>24);

}

//input pic data quantity  for example  pic size = 800*480 = 384000
void DMA_Continuous_mode_size_setting(u32 set_size)
{ 
  LCD_CmdWrite(0xB4);
  LCD_DataWrite(set_size);

  LCD_CmdWrite(0xB6);
  LCD_DataWrite(set_size>>8);
 
  LCD_CmdWrite(0xB8);
  LCD_DataWrite(set_size>>16);

}

void DMA_block_mode_size_setting(u16 BWR,u16 BHR,u16 SPWR)
{
  LCD_CmdWrite(0xB4);
  LCD_DataWrite(BWR);
  LCD_CmdWrite(0xB5);
  LCD_DataWrite(BWR>>8);

  LCD_CmdWrite(0xB6);
  LCD_DataWrite(BHR);
  LCD_CmdWrite(0xB7);
  LCD_DataWrite(BHR>>8);

  LCD_CmdWrite(0xB8);
  LCD_DataWrite(SPWR);
  LCD_CmdWrite(0xB9);
  LCD_DataWrite(SPWR>>8);  
}

//---------------------------------------------//
//REG[BFh]
void DMA_Continuous_mode(void)
{ 
  LCD_CmdWrite(0xBF);
  LCD_DataWrite(0x00);
}

void DMA_Block_mode(void)
{ 
  LCD_CmdWrite(0xBF);
  LCD_DataWrite(0x02);
}

void DMA_Start_enable(void)
{  u8 temp;
  LCD_CmdWrite(0xBF);
  temp = LCD_DataRead();
  temp |= 0x01;
  LCD_DataWrite(temp);
}

//---------------------------------------------//
//REG[C0h]
void Key_Scan_Enable(void)
{ u8 temp;
  LCD_CmdWrite(0xC0);
  temp = LCD_DataRead();
  temp |= 0x80;
  LCD_DataWrite(temp);  
}


void Key_Scan_setting(u8 setx)//bit[2:0]
{ u8 temp;
  LCD_CmdWrite(0xC0);
  temp = LCD_DataRead();
  temp &= 0xf0;
  temp|= (setx&0x07);
  LCD_DataWrite(temp);  
} 

void Long_Key_Scan_enable(void)
{ u8 temp;
  LCD_CmdWrite(0xC0);
  temp = LCD_DataRead();
  temp |= 0x40;
  LCD_DataWrite(temp);
}

void Key_Scan_Wakeup_Function_Enable(void)
{ u8 temp;
  LCD_CmdWrite(0xC1);	
  temp = LCD_DataRead();
  temp |= 0x80;	// 
  LCD_DataWrite(temp);
}

void Long_Key_Timing_Adjustment(u8 setx)
{
   u8 temp,temp1;
  temp = setx & 0x1c;
  LCD_CmdWrite(0xC1);
  temp1 = LCD_DataRead();
  temp1|=temp;
  LCD_DataWrite(temp1);   
 
}

//---------------------------------------------//
//REG[D0]
void Floating_window_start_point(u16 X,u16 Y)
{ 
   LCD_CmdWrite(0xD0);
   LCD_DataWrite(X);
   LCD_CmdWrite(0xD1);
   LCD_DataWrite(X>>8);

   LCD_CmdWrite(0xD2);
   LCD_DataWrite(Y);
   LCD_CmdWrite(0xD3);
   LCD_DataWrite(Y>>8);  
}


void Floating_window_size(u16 width_X,u16 high_Y)
{

   LCD_CmdWrite(0xD4);
   LCD_DataWrite(width_X);
   LCD_CmdWrite(0xD5);
   LCD_DataWrite(width_X>>8);

   LCD_CmdWrite(0xD6);
   LCD_DataWrite(high_Y);
   LCD_CmdWrite(0xD7);
   LCD_DataWrite(high_Y>>8);

}

void Floating_window_display_point(u16 X,u16 Y)
{

   LCD_CmdWrite(0xD8);
   LCD_DataWrite(X);
   LCD_CmdWrite(0xD9);
   LCD_DataWrite(X>>8);

   LCD_CmdWrite(0xDA);
   LCD_DataWrite(Y);
   LCD_CmdWrite(0xDB);
   LCD_DataWrite(Y>>8);

}


//REG[E0h] 
void Serial_ROM_direct_access_mode_enable(void)
{
   LCD_CmdWrite(0xE0);
   LCD_DataWrite(0x01);
}

void Serial_ROM_direct_access_mode_disable(void)
{
   LCD_CmdWrite(0xE0);
   LCD_DataWrite(0x00);
}

void Direct_access_mode_Address_32bits(u32 set_address)
{
  u8 temp;  
  temp = set_address>>24;
  LCD_CmdWrite(0xE1);
  LCD_DataWrite(temp);
  temp = set_address>>16;
  LCD_DataWrite(temp);
  temp = set_address>>8;
  LCD_DataWrite(temp);
  temp = set_address;
  LCD_DataWrite(temp);

}

void Direct_access_mode_Address_24bits(u32 set_address)
{
  u8 temp=0;
  
  temp = set_address>>16;
  LCD_CmdWrite(0xE1);
  LCD_DataWrite(temp);  
  temp = set_address>>8;
  LCD_CmdWrite(0xE1);
  LCD_DataWrite(temp);   
  temp = set_address;
  LCD_CmdWrite(0xE1);
  LCD_DataWrite(temp);

}

u8 Direct_access_mode_Read_Data_buffer(void)
{
   u8 Serial_Data;

   LCD_CmdWrite(0xE2);
   Serial_Data=LCD_DataRead(); 
   return Serial_Data;
}

//---------------------------------------------//



//---------------------------------------------//
//REG[F0h] 

void KEYSCAN_Interrupt_Enable(void)
{ u8 temp;
  LCD_CmdWrite(0xF0);	
  temp = LCD_DataRead();
  temp |= 0x10;	// 
  LCD_DataWrite(temp); 
}

void KEYSCAN_Interrupt_Disable(void)
{ u8 temp;
  LCD_CmdWrite(0xF0);	
  temp = LCD_DataRead();
  temp &= 0x0F;	// 
  LCD_DataWrite(temp); 
}


void DMA_Interrupt_Enable(void)
{ u8 temp;
  LCD_CmdWrite(0xF0);	
  temp = LCD_DataRead();
  temp |= 0x08;	// 
  LCD_DataWrite(temp); 
}

void DMA_Interrupt_Disable(void)
{ u8 temp;
  LCD_CmdWrite(0xF0);	
  temp = LCD_DataRead();
  temp &= 0x17;	// 
  LCD_DataWrite(temp); 
}

void Touch_Panel_Interrupt_Enable(void)
{ u8 temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp |= 0x04;
  LCD_DataWrite(temp);
 }

void Touch_Panel_Interrupt_Disable(void)
{ u8 temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp &= 0x1B;
  LCD_DataWrite(temp);
 }

void BTE_Interrupt_Enable(void)
{
  u8 temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp |= 0x02;
  LCD_DataWrite(temp);
}

void BTE_Interrupt_Disable(void)
{
  u8 temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp &= 0x1D;
  LCD_DataWrite(temp);
}

void Font_BTE_read_write_Interrupt_Enable(void)
{
  u8 temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp |= 0x01;
  LCD_DataWrite(temp);
}

void Font_BTE_read_write_Interrupt_Disable(void)
{
  u8 temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp &= 0x1E;
  LCD_DataWrite(temp);
}

//---------------------------------------------//
//REG[F1h] 
void Clear_keyscan_interrupt(void)
{ u8 temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |=cSetD4 ;
  LCD_DataWrite(temp);
}

u8 Keyscan_Status(void)
{   u8 temp;
	LCD_CmdWrite(0xF1);//INTC	
	temp = LCD_DataRead();
	if ((temp&0x10)==0x10)
	return 1;
	else 
	return 0;
}

void Clear_DMA_interrupt(void)
{ u8 temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |=cSetD3 ;
  LCD_DataWrite(temp);

}

u8 DMA_Status(void)
{   u8 temp;
	LCD_CmdWrite(0xF1);//INTC	
	temp = LCD_DataRead();
	if ((temp&0x08)==0x08)
	return 1;
	else 
	return 0;
}

void clear_TP_interrupt(void)
{ u8 temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |= cSetD2;
  LCD_DataWrite(temp);
 }


u8 Touch_Status(void)
{	u8 temp;
	LCD_CmdWrite(0xF1);//INTC	
	temp = LCD_DataRead();
	if ((temp&0x04)==0x04)
	return 1;
	else 
	return 0;
}

void Clear_BTE_interrupt(void)
{ u8 temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |= cSetD1;
  LCD_DataWrite(temp);
}

u8 BTE_Status(void)
{	u8 temp;
	LCD_CmdWrite(0xF1);//INTC	
	temp = LCD_DataRead();
	if ((temp&0x02)==0x02)
	return 1;
	else 
	return 0;
}

void Clear_Font_BTE_read_write_Interrupt(void)
{ u8 temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |= cSetD0;
  LCD_DataWrite(temp);
}

u8 Font_BTE_read_write_Status(void)
{	u8 temp;
	LCD_CmdWrite(0xF1);//INTC	
	temp = LCD_DataRead();
	if ((temp&0x01)==0x01)
	return 1;
	else 
	return 0;
}



void Chk_Wait(void)
{
	
// while(MCU_WAIT==0);	   
}


void Show_String(u8 *str)
{ 
	Text_Mode();
	LCD_WriteRAM_Prepare();
	while(*str != '\0' && *str != '\n')
	{
	 LCD_DataWrite(*str);
	 ++str;
	 udelay(6);
//	 Chk_Busy();
   //Chk_Wait();		
	}
  Graphic_Mode();
}






