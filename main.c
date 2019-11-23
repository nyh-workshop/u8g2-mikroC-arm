#include "u8g2_csrc/u8g2.h"

u8g2_t u8g2;

const uint8_t SSD1306_ADDR = 0x3C;

//source: http://45.76.185.145/2018/04/14/U8g2_stm32_hw_i2c/
// another source: https://github.com/w1ne/u8g2-ssd1306-CubeMX/blob/master/Src/main.c
uint8_t u8x8_byte_stm32_hw(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  static uint8_t buffer[32]; /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
  static uint8_t buf_idx;
  uint8_t *_data;

  switch (msg)
  {
  case U8X8_MSG_BYTE_INIT:
    break;

  case U8X8_MSG_BYTE_SET_DC:
    break;

  case U8X8_MSG_BYTE_START_TRANSFER:
  {
    buf_idx = 0;
  }
  break;

  case U8X8_MSG_BYTE_SEND:
    {
      _data = (uint8_t *)arg_ptr;
      while (arg_int > 0)
      {
        buffer[buf_idx++] = *_data;
        _data++;
        arg_int--;
      }
    }
    break;

  case U8X8_MSG_BYTE_END_TRANSFER:
    I2C2_Start();
    I2C2_Write(SSD1306_ADDR, buffer , buf_idx, END_MODE_STOP);
    break;

  default:
    return 0;
  }
  return 1;
}

uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
  return 1;
}

void main()
{
  I2C2_Init();
  I2C_Set_Active(&I2C2_Start, &I2C2_Read, &I2C2_Write); 
  GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_ALL); // Set PORTC as digital output
  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw, u8g2_gpio_and_delay_stm32);
  u8g2_InitDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);
  u8g2_ClearDisplay(&u8g2);
  u8g2_ClearBuffer(&u8g2);
  u8g2_FirstPage(&u8g2);
  u8g2_SetDrawColor(&u8g2, 1);
  u8g2_SetFont(&u8g2, u8g2_font_amstrad_cpc_extended_8f);
  u8g2_DrawStr(&u8g2, 16, 16 , "12345");
  u8g2_DrawStr(&u8g2, 16, 32 , "Hello World!");

  //u8g2_DrawGlyph(&u8g2, 16, 1, (uint16_t)'z');
  u8g2_DrawLine(&u8g2, 0,0, 127, 63);
  //u8g2_DrawTriangle(&u8g2, 20,5, 27,50, 5,32);
  u8g2_DrawCircle(&u8g2, 40, 40, 10, U8G2_DRAW_ALL);
  u8g2_SendBuffer(&u8g2);
  
  while (1)
  {
    GPIOC_ODR |= (1 << 8);
    Delay_ms(100);
    GPIOC_ODR &= ~(1 << 8);
    Delay_ms(100);
  }
}