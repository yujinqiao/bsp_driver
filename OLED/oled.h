#ifndef __OLED_H
#define __OLED_H			  	 
#include "SYSTEM/system.h"
#include "stdlib.h"	    


#define OLED_ADDRESS 0x78
#define	Brightness	0xCF
#define X_WIDTH 	128
#define Y_WIDTH 	64

void OLED_WrDat(u8 IIC_Data);
void OLED_WrCmd(u8 IIC_Command);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Fill(u8 bmp_dat);
void OLED_CLS(void);
void OLED_Init(void);
void OLED_P6x8Str(u8 x, u8 y,u8 ch[]);
void OLED_P8x16Str(u8 x,u8 y,u8 ch[]);
void OLED_P16x16Ch(u8 x,u8 y,u8 n);
void Draw_BMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void LCD_ShowChinese16x16(uint16_t x, uint16_t y, uint8_t *s, uint8_t sizey);





/**************************??????*****************************/				   
typedef enum
{
    SCREEN_UP = 0,
    SCREEN_DOWN = 1
}SCREEN_DIR;

/**************************??????*****************************/	
typedef enum
{
    SCREEN_NORMAL = 0,
    SCREEN_REVERSE = 1
}SCREEN_SHOW;


/**************************????/????*****************************/	
typedef enum
{
    SCREEN_ON = 0,
    SCREEN_OFF = 1
}SCREEN_SWITCH;


/**************************??????*****************************/	
typedef enum
{
    FONT_8_EN  = 6,
    FONT_16_EN = 8,
    FONT_16_CN = 16
}FONT_SIZE;


/**************************????*****************************/	
typedef enum 
{
    OCT = 8,
    DEC = 10,
    HEX = 16
}RADIX;


/**************************??????*****************************/	
//?????????????????????????????????????????
typedef enum
{
    FM_LOGO_ENUM = 0,
    DIRECT_LOGO_ENUM = 1,
    BRIGHTNESS_LOGO_ENUM = 2,
    REVERSAL_LOGO_ENUM = 3
}IMAGE_INDEX;

#endif  
	 



