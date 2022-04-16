#ifndef __OLED_H
#define __OLED_H
#include "sys.h"
#include "stdlib.h"

#define XLevelL 0x00
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64

#define OLED_GPIO_PORT GPIOB
#define OLED_RCC_PORT RCC_APB2Periph_GPIOB
#define OLED_SCL_PIN GPIO_Pin_1
#define OLED_SDA_PIN GPIO_Pin_2

#define OLED_SCL_1() OLED_GPIO_PORT->BSRR = OLED_SCL_PIN            /* SCL = 1 */
#define OLED_SCL_0() OLED_GPIO_PORT->BRR = OLED_SCL_PIN             /* SCL = 0 */
#define OLED_SDA_1() OLED_GPIO_PORT->BSRR = OLED_SDA_PIN            /* SDA = 1 */
#define OLED_SDA_0() OLED_GPIO_PORT->BRR = OLED_SDA_PIN             /* SDA = 0 */
#define OLED_SDA_READ() ((OLED_GPIO_PORT->IDR & OLED_SDA_PIN) != 0) /* ??SDA????¡Á??? */

void OLED_Init(void);
void OLED_Clear(void);
void OLED_Test(void);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size);
void OLED_ShowFloatNum(u8 x,u8 y,double num,u8 len,u8 size);
#endif
