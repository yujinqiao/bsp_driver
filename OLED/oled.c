#include "OLED/oled.h"
#include "OLED/oledfont.h"  	 
#include "SYSTICK/SysTick.h"
#include "OLED/myi2c.h"
#include "BMP.h"
#include "string.h"



/*********************OLED写数据************************************/
void OLED_WrDat(u8 IIC_Data)
{
	OLED_IIC_Start();
	OLED_IIC_Send_Byte(OLED_ADDRESS);
	OLED_IIC_Send_Byte(0x40);      // write data
	OLED_IIC_Send_Byte(IIC_Data);
	OLED_IIC_Stop();
}


/*********************OLED写命令************************************/
void OLED_WrCmd(u8 IIC_Command)
{
	OLED_IIC_Start();
	OLED_IIC_Send_Byte(OLED_ADDRESS);
	OLED_IIC_Send_Byte(0x00);      // write command
	OLED_IIC_Send_Byte(IIC_Command);
	OLED_IIC_Stop();
}


/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(u8 x, u8 y)
{
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
}


/*********************OLED全屏************************************/
void OLED_Fill(u8 bmp_dat)
{
	u8 y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}

/*********************OLED复位************************************/
void OLED_CLS(void)
{
	u8 y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}


/**********************************屏幕设置函数**************************************/
/**
 * 功能：设置屏幕反色  
 * 参数：
 * 		set：设置参数   SCREEN_NORMAL,SCREEN_REVERSE可选
 * 返回值：None
 */
void setScreenReverse(SCREEN_SHOW set)
{
	if(set==SCREEN_REVERSE)		//屏幕反色
	{
		OLED_WrCmd(0xA7);
	}else 						//屏幕常色
	{
		OLED_WrCmd(0xA6);
	}
}

/**
 * 功能：设置屏幕显示方向，类似于手机屏幕翻转  
 * 参数：
 * 		set：设置参数   SCREEN_UP,SCREEN_DOWN可选
 * 返回值：None
 */
void setScreenDir(SCREEN_DIR set)
{
	if(set==SCREEN_UP)			//屏幕正向
	{
		OLED_WrCmd(0xA1);
		OLED_WrCmd(0xC8);
	}else 						//屏幕倒向
	{
		OLED_WrCmd(0xA0);
		OLED_WrCmd(0xC0);
	}
}

/**
 * 功能：设置屏幕是否开启，类似于手机息屏和唤醒
 * 参数：
 * 		set：设置参数   SCREEN_ON,SCREEN_OFF可选
 * 返回值：None
 */
void setScreenSwtich(SCREEN_SWITCH set)
{
	if(set==SCREEN_ON)
	{
		OLED_WrCmd(0xAF);
	}else 
	{
		OLED_WrCmd(0xAE);
	}
}



/*********************OLED初始化************************************/
void OLED_Init(void)
{
	Delay_ms (500); //这里的延时很重要
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7)
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //初始清屏
	OLED_Set_Pos(0,0);
}
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void OLED_P6x8Str(u8 x, u8 y,u8 ch[])
{
	u8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WrDat(F6x8[c][i]);
		x+=6;
		j++;
	}
}
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void OLED_P8x16Str(u8 x,u8 y,u8 ch[])
{
	u8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		OLED_WrDat(F8X16[c*16+i]);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WrDat(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void OLED_P16x16Ch(u8 x,u8 y,u8 n)
{
	u8 wm=0;
	u16 adder=32*n;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
}




/******************************************************************************
      函数说明：显示单个16x16汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                sizey 字号
                mode: 字符串S有几个汉字
      返回值：  无
******************************************************************************/
static void LCD_ShowChinese16x16(uint16_t x, uint16_t y, uint8_t *s, uint8_t sizey)
{
    uint8_t i= 0;
    uint16_t k;
    uint16_t HZnum;//汉字数目
//    uint16_t TypefaceNum;//一个字符所占字节大小
//    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    
    
    HZnum = sizeof(tfont16) / sizeof(typFNT_GB16);	//统计汉字数目
//    printf("TypefaceNum=%d\r\n",TypefaceNum);  //查看汉字的大小
//    printf("HZnum=%d\r\n",HZnum);        //查看有多少个汉字
//    printf("HZnum=%s\r\n",s+4);        //查看有多少个汉字
    

    for(k = 0; k < HZnum; k++)
    {
        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
        {
                       
            OLED_Set_Pos(x,y);
            for(i = 0; i < sizey; i++)
            {
                OLED_WrDat(tfont16[k].Msk[i]);
            }
            OLED_Set_Pos(x,y+1);
            for(i = 0; i < sizey; i++)
            {
                OLED_WrDat(tfont16[k].Msk[i+sizey]);
            } 
            
        }
        continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }
         
} 


/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void Draw_BMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[])
{
	u16 j=0;
	u8 x,y;

  if(y1%8==0) y=y1/8;
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {
	    	OLED_WrDat(BMP[j++]);
	    }
	}
}




static u8 findCNIndex(u8* str,u8* cnfont_index)
{
	u16 cnfont_size = strlen((const char *)cnfont_index);

	u8 index = 0;
	for(index=0;index<cnfont_size/3;++index)
	{
		if(((str[0]^cnfont_index[index*3+0])||(str[1]^cnfont_index[index*3+1])||(str[2]^cnfont_index[index*3+2]))==0)//匹配到汉字索引
		{
			return index;
		}
	}

	return 0; //没有匹配到直接返回字库第一个索引，这里是“风”
}


/**
 * 功能：显示16*16点阵汉字
 * 参数：
 * 		x:x轴坐标 0-127
 * 		y:y轴坐标 0-7
 * 		str:待显示汉字支持单个汉字和多个汉字
 * 		f_size:字体大小 目前只提供了16*16点阵汉字，如果要用其他大小的汉字添加对应判断即可
 * 			    本函数中该参数无效
 * 返回值：None
 */ 
void showCNString(u8 x,u8 y,u8* str,FONT_SIZE f_size)
{   
	u8 i;
	u8 cn_index;
	u8 count;
    u8  charCount=0;
	if(x > 127 || y > 7) //参数异常处理
	{
		x = 0;
		y = 0;
	}  
    charCount = strlen((const char *)str)/3;

//    printf("charCount=%d\r\n",charCount);
//	for(count=0;count<strlen((const char *)str)/3;++count)
    for(count=0;count<charCount;++count)
	{
		cn_index = findCNIndex(str+count*3,CN1616_Index);
		OLED_Set_Pos(x+16*count,y);
		for(i=0;i<16;++i)
		{
			OLED_WrDat(CN1616[cn_index][i]);
		}
		OLED_Set_Pos(x+16*count,y+1);
		for(i=16;i<32;++i)
		{
			OLED_WrDat(CN1616[cn_index][i]);
		}
	} 			    
		
}


/**
 * 功能：在制定区域显示图片
 * 参数：
 * 		x:x轴坐标 0-127
 * 		y:y轴坐标 0-7
 * 		x_len:显示区域横坐标长度 0-128
 *		y_len:显示区域纵坐标长度 0-8
 * 		image_index:图片枚举索引
 * 说明：该函数一般用于显示全屏LOGO，另外灵活运用可以显示PPT切换特效
 * 		如让x_len递增LOGO就会从左到右逐渐显示，其他用法类似
 * 返回值：None
 */ 
void showImage(u8 xpos, u8 ypos,u8 x_len, u8 y_len,IMAGE_INDEX  image_index)
{ 	
	u16 i,j;

	for(i=0;i<y_len;++i)					//页地址控制
	{
		OLED_Set_Pos(xpos,ypos++);
		
		for(j=i*128+xpos;j<i*128+x_len;++j) //列地址控制
		{
			switch(image_index)
			{
				case FM_LOGO_ENUM        :OLED_WrDat(FM_LOGO[j]);        break;
				case BRIGHTNESS_LOGO_ENUM:OLED_WrDat(BRIGHTNESS_LOGO[j]);break;
				case DIRECT_LOGO_ENUM    :OLED_WrDat(DIRECT_LOGO[j]);    break;
				case REVERSAL_LOGO_ENUM  :OLED_WrDat(REVERSAL_LOGO[j]);  break;

				default                  :                              break;
			}
			
		}
	}
} 







