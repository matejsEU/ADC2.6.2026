#include <stdbool.h>
#include <stm8s.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
#include "uart1.h"
#include <stdio.h>
#include "adc_helper.h"
// Discovery Board
#ifdef STM8S003
#define LED_PORT GPIOD
#define LED_PIN  GPIO_PIN_0
#define BTN_PORT GPIOB
#define BTN_PIN  GPIO_PIN_7
#endif
// Blue-Board, Dero-Board
#ifdef STM8S103
//   Dero-Board
/*#define LED_PORT GPIOD*/
/*#define LED_PIN  GPIO_PIN_4*/
//   Blue-Board
#define LED_PORT GPIOB
#define LED_PIN  GPIO_PIN_5
#endif
// Discovery Board
#ifdef STM8S105
#define LED_PORT GPIOD
#define LED_PIN  GPIO_PIN_0
#endif
// Nucleo Kit
#ifdef STM8S208
#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#endif


void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    init_milis();
    init_uart1();

    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL2, DISABLE);
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL14, DISABLE);
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL15, DISABLE);

    ADC2_PrescalerConfig(ADC2_PRESSEL_FCPU_D4);
    ADC2_AlignConfig(ADC2_ALIGN_RIGHT);
    ADC2_Select_Channel(ADC2_CHANNEL_2);
    ADC2_Cmd(ENABLE);


}


int main(void)
{
  
    uint32_t time = 0;
    uint16_t value;
    uint16_t voltage;
    
    init();

    while (1) {
        if (milis()-time>1000) {
            REVERSE(LED);
            time = milis();
            value = ADC_get(ADC2_CHANNEL_14);
            voltage = ((uint32_t)5000 * value + 512 / 1024);
            printf("%ld: %d %dmV\n", time, value, voltage);
        }
    }
}


/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
