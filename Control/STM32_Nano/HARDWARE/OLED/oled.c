#include "oled.h"
#include "delay.h"
#include "oledfont.h"
#include "stm32f10x.h"
#include "delay.h"
//cmd 0  data 1

/**********************************************************************************************************/
static void Delay(void)
{
    uint8_t i;
    for (i = 0; i < 10; i++);
}

void OLED_I2C_Start(void)
{
    OLED_SDA_1();
    OLED_SCL_1();
    Delay();
    OLED_SDA_0();
    Delay();
    OLED_SCL_0();
    Delay();
}

void OLED_I2C_Stop(void)
{
    OLED_SDA_0();
    OLED_SCL_1();
    Delay();
    OLED_SDA_1();
}

void OLED_I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (Byte & 0x80)
            OLED_SDA_1();
        else
            OLED_SDA_0();
        Delay();
        OLED_SCL_1();
        Delay();
        OLED_SCL_0();
        if (i == 7)
            OLED_SDA_1(); //??¡¤?¡Á???
        Byte <<= 1;
        Delay();
    }
}

uint8_t OLED_I2C_WaitACK(void)
{
    uint8_t res;
    OLED_SDA_1();
    Delay();
    OLED_SCL_1();
    Delay();
    if (OLED_SDA_READ())
        res = 1;
    else
        res = 0;
    OLED_SCL_0();
    Delay();
    return res;
}

void OLED_I2C_WriteCmd(uint8_t cmd)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);
    OLED_I2C_WaitACK();
    OLED_I2C_SendByte(0x00);
    OLED_I2C_WaitACK();
    OLED_I2C_SendByte(cmd);
    OLED_I2C_WaitACK();
    OLED_I2C_Stop();
}

void OLED_I2C_WriteData(uint8_t data)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);
    OLED_I2C_WaitACK();
    OLED_I2C_SendByte(0x40);
    OLED_I2C_WaitACK();
    OLED_I2C_SendByte(data);
    OLED_I2C_WaitACK();
    OLED_I2C_Stop();
}

static void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(OLED_RCC_PORT, ENABLE);
    GPIO_InitStructure.GPIO_Pin = OLED_SCL_PIN | OLED_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStructure);
    OLED_I2C_Stop();
}
/**********************************************************************************************************/

void OLED_WriteByte(uint8_t data, uint8_t cmd)
{
    if (cmd)
        OLED_I2C_WriteData(data);
    else
        OLED_I2C_WriteCmd(data);
}

void OLED_Clear(void)
{
    uint8_t i, n;
    for (i = 0; i < 8; i++)
    {
        OLED_WriteByte(0xB0 + i, 0);
        OLED_WriteByte(0x00, 0);
        OLED_WriteByte(0x10, 0);
        for (n = 0; n < 128; n++)
            OLED_WriteByte(0, 1);
    }
}

void OLED_DisplayON(void)
{
    OLED_WriteByte(0x8D, 0);
    OLED_WriteByte(0x14, 0);
    OLED_WriteByte(0xAF, 0);
}

void OLED_SetPos(uint8_t x, uint8_t y)
{
    OLED_WriteByte(0xB0 + y, 0);
    OLED_WriteByte(((x & 0xF0) >> 4) | 0x10, 0);
    OLED_WriteByte((x & 0x0f), 0);
}

void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size)
{
    uint8_t c, i;
    c = chr - ' ';
    if (x > Max_Column - 1)
    {
        x = 0;
        y = y + 2;
    }

    if (size == 16)
    {
        OLED_SetPos(x, y);
        for (i = 0; i < 8; i++)
            OLED_WriteByte(F8X16[c * 16 + i], 1);
        OLED_SetPos(x, y + 1);
        for (i = 0; i < 8; i++)
            OLED_WriteByte(F8X16[c * 16 + i + 8], 1);
    }
    else
    {
        OLED_SetPos(x, y);
        for (i = 0; i < 6; i++)
            OLED_WriteByte(F6x8[c][i], 1);
    }
}

static uint32_t Pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}

void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size)
{
    uint8_t i, tmp, enshow = 0;
    for (i = 0; i < len; i++)
    {
        tmp = (num / Pow(10, len - i - 1)) % 10;
        if (enshow == 0 && i < (len - 1))
        {
            if (tmp == 0)
            {
                OLED_ShowChar(x + (size / 2) * i, y, ' ', size);
                continue;
            }
            else
                enshow = 1;
        }
        OLED_ShowChar(x + (size / 2) * i, y, tmp + '0', size);
    }
}

void OLED_ShowFloatNum(u8 x,u8 y,double num,u8 len,u8 size)

{
	u32 interger=(u32)num;
	u32 fractional=(u32)((num-interger)*1000);
	u32 x_tmp;
	if(num<0)
	{
		OLED_ShowString(x,y,"Minus!",16);
	}else{if(interger>=100)
	{
		x_tmp=x;
		OLED_ShowNum(x,y,interger,3,size);
	}else if(interger>=10&&interger<=99)
	{
		x_tmp=x-8;
		OLED_ShowNum(x,y,interger,2,size);
	}else if(interger>=1&&interger<=9)
	{
		x_tmp=x-16;
		OLED_ShowNum(x,y,interger,1,size);
	}else{
		x_tmp=x-16;
		OLED_ShowNum(x,y,0,1,size);
	}
		OLED_ShowChar(x_tmp+24,y,'.',size);
	if(fractional>=100)
		OLED_ShowNum(x_tmp+32,y,fractional,3,size);
	else if(fractional>=10&&fractional<=99)
	{
		OLED_ShowNum(x_tmp+40,y,fractional,2,size);
		OLED_ShowChar(x_tmp+32,y,'0',size);
	}else if(fractional>=1&&fractional<=9)
	{
		OLED_ShowNum(x_tmp+48,y,fractional,1,size);
		OLED_ShowChar(x_tmp+40,y,'0',size);
		OLED_ShowChar(x_tmp+32,y,'0',size);
	}else{
		OLED_ShowChar(x_tmp+32,y,'0',size);
		OLED_ShowChar(x_tmp+40,y,'0',size);
		OLED_ShowChar(x_tmp+48,y,'0',size);
	}
	}
	}

void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size)
{
    uint8_t j = 0;
    while (chr[j] != '\0')
    {
        OLED_ShowChar(x, y, chr[j], size);
        x += 8;
        if (x > 120)
        {
            x = 0;
            y += 2;
        }
        j++;
    }
}

void OLED_Init(void)
{
    IIC_Init();
    delay_ms(1000);

    OLED_WriteByte(0xAE, 0); //--display off
    OLED_WriteByte(0x00, 0); //---set low column address
    OLED_WriteByte(0x10, 0); //---set high column address
    OLED_WriteByte(0x40, 0); //--set start line address
    OLED_WriteByte(0xB0, 0); //--set page address
    OLED_WriteByte(0x81, 0); // contract control
    OLED_WriteByte(0xFF, 0); //--128
    OLED_WriteByte(0xA1, 0); //set segment remap
    OLED_WriteByte(0xA6, 0); //--normal / reverse
    OLED_WriteByte(0xA8, 0); //--set multiplex ratio(1 to 64)
    OLED_WriteByte(0x3F, 0); //--1/32 duty
    OLED_WriteByte(0xC8, 0); //Com scan direction
    OLED_WriteByte(0xD3, 0); //-set display offset
    OLED_WriteByte(0x00, 0); //

    OLED_WriteByte(0xD5, 0); //set osc division
    OLED_WriteByte(0x80, 0); //

    OLED_WriteByte(0xD8, 0); //set area color mode off
    OLED_WriteByte(0x05, 0); //

    OLED_WriteByte(0xD9, 0); //Set Pre-Charge Period
    OLED_WriteByte(0xF1, 0); //

    OLED_WriteByte(0xDA, 0); //set com pin configuartion
    OLED_WriteByte(0x12, 0); //

    OLED_WriteByte(0xDB, 0); //set Vcomh
    OLED_WriteByte(0x30, 0); //

    OLED_WriteByte(0x8D, 0); //set charge pump enable
    OLED_WriteByte(0x14, 0); //

    OLED_WriteByte(0xAF, 0); //--turn on oled panel
    OLED_Clear();
}

void OLED_Test(void)
{
    OLED_Clear();
    OLED_DisplayON();
    OLED_ShowString(6, 3, "0.96' OLED TEST", 16);
    OLED_ShowNum(6, 6, 60, 3, 16);
}

