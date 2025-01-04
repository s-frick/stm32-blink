#include "lights.h"
#include <stdint.h>

#define PERIPHERAL_BASE (0x40000000U)
#define AHB1_BASE (PERIPHERAL_BASE + 0x20000U)
#define GPIOA_BASE (AHB1_BASE + 0x0U)
#define RCC_BASE (AHB1_BASE + 0x3800U)

#define RCC_AHB1ENR_OFFSET (0x30U)
#define RCC_AHB1ENR ((volatile uint32_t *)(RCC_BASE + RCC_AHB1ENR_OFFSET))
#define RCC_AHBRENR_GPIOEN (0x00U)

#define GPIO_MODER_OFFSET (0x00U)
#define GPIOA_MODER ((volatile uint32_t *)(GPIOA_BASE + GPIO_MODER_OFFSET))
#define GPIO_ODR_OFFSET (0x14U)
#define GPIO_ODR ((volatile uint32_t *)(GPIOA_BASE + GPIO_ODR_OFFSET))

#define LED_RED 0
#define LED_YELLOW 1
#define LED_GREEN 4

typedef struct {
  volatile uint32_t *MODER;
  volatile uint32_t *ODR;
} GPIO;

typedef enum {
  GPIO_MODER_INPUT = 0b00,
  GPIO_MODER_OUTPUT = 0b01,
  GPIO_MODER_ALTERNATE = 0b10,
  GPIO_MODER_ANALOG = 0b11,
} GPIO_MODER;

GPIO gpioA;

void GPIO_SetMODER(GPIO *gpio, int pin, GPIO_MODER mode) {
  *gpio->MODER &= ~(0b11 << (pin * 2));
  *gpio->MODER |= (mode & 0b11) << (pin * 2);
}

typedef enum {
  GPIO_LOW = 0b0,
  GPIO_HIGH = 0b1,
} GPIO_VALUE;

void GPIO_set(GPIO *gpio, int pin, GPIO_VALUE v) {
  *gpio->ODR &= ~(0b1 << pin);
  *gpio->ODR |= (v & 0b1) << pin;
}

void GPIO_toggle(GPIO *gpio, int pin) { *gpio->ODR ^= (1 << pin); }

void setLight(LIGHT light, LIGHT_STATE lstate) {
  GPIO_VALUE v = lstate ? GPIO_HIGH : GPIO_LOW;
  switch (light) {
  case LRED:
    GPIO_set(&gpioA, LED_RED, v);
    break;
  case LYELLOW:
    GPIO_set(&gpioA, LED_YELLOW, v);
    break;
  case LGREEN:
    GPIO_set(&gpioA, LED_GREEN, v);
    break;
  }
}
void delay(uint32_t ms) {
  for (uint32_t i = 0; i < ms * 1000; i++)
    ;
}

void main(void) {
  *RCC_AHB1ENR |= (1 << RCC_AHBRENR_GPIOEN);

  volatile uint32_t dummy;
  dummy = *(RCC_AHB1ENR);
  dummy = *(RCC_AHB1ENR);
  gpioA.MODER = GPIOA_MODER;
  gpioA.ODR = GPIO_ODR;

  GPIO_SetMODER(&gpioA, 0, GPIO_MODER_OUTPUT);
  GPIO_SetMODER(&gpioA, 1, GPIO_MODER_OUTPUT);
  GPIO_SetMODER(&gpioA, 4, GPIO_MODER_OUTPUT);

  start_lights();
}
