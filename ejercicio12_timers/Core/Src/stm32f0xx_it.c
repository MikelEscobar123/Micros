/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f091xc.h"
#include <stdint.h>
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile uint8_t contLed = 0, numSecuencia = 0, pausa = 0;
volatile uint16_t valorARR = 1;// frecuencia = valorARR * 0,5 Hz
volatile uint32_t ms = 0, PB3ultimo = 0, PB4ultimo = 0, PB5ultimo = 0;
volatile uint16_t tiempoPB3 = 0;
volatile uint8_t pulsadoPB3 = 0, pulsadoPB4 = 0, pulsadoPB5 = 0;
volatile uint8_t modifPB3 = 0, modifPB4 = 0, modifPB5 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
uint16_t calcularARR(uint16_t valor){
  return ((16000u / valor) - 1);
}

void incrementarFrecuencia(void){
  if(valorARR < 20){
    valorARR++;
  }else{
    valorARR = 1;
  }
  TIM6->ARR = calcularARR(valorARR);
}

void secuencia0(uint8_t contLed){
  switch(contLed){
    case 0:
      GPIOA->BSRR = (1UL << 8) | (1UL << 25) | (1UL << 26);
      break;
    case 1:
      GPIOA->BSRR = (1UL << 24) | (1UL << 9) | (1UL << 26);
      break;
    case 2:
      GPIOA->BSRR = (1UL << 24) | (1UL << 25) | (1UL << 10);
      break;
    case 3:
      GPIOA->BSRR = (1UL << 24) | (1UL << 9) | (1UL << 26);
      break;
  }
}

void secuencia1(uint8_t contLed){
  switch(contLed){
    case 0:
      GPIOA->BSRR = (1UL << 8) | (1UL << 9) | (1UL << 26);
      break;
    case 1:
      GPIOA->BSRR = (1UL << 24) | (1UL << 9) | (1UL << 10);
      break;
    case 2:
      GPIOA->BSRR = (1UL << 8) | (1UL << 25) | (1UL << 10);
      break;
    case 3:
      GPIOA->BSRR = (1UL << 24) | (1UL << 9) | (1UL << 10);
      break;
  }
}

void secuencia2(uint8_t contLed){
  switch(contLed){
    case 0:
      GPIOA->BSRR = (1UL << 8) | (1UL << 9) | (1UL << 10);
      break;
    case 1:
      GPIOA->BSRR = (1UL << 24) | (1UL << 25) | (1UL << 26);
      break;
    case 2:
      GPIOA->BSRR = (1UL << 8) | (1UL << 9) | (1UL << 10);
      break;
    case 3:
      GPIOA->BSRR = (1UL << 24) | (1UL << 25) | (1UL << 26);
      break;
  }
}

void secuencias(uint8_t cont){//switch con funciones dentro
  switch(cont){
    case 0:
      secuencia0(contLed);
      break;
    case 1:
      secuencia1(contLed);
      break;
    case 2:
      secuencia2(contLed);
      break;
    default:
      secuencia0(contLed);
      break;
  }
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim16;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
  ms++;
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 2 and 3 interrupts.
  */
void EXTI2_3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_3_IRQn 0 */
  if(ms - PB3ultimo > 10){//Antirebote
    PB3ultimo = ms;
    pulsadoPB3 = 1;
    tiempoPB3 = 0; //Tiempo que pasa PB3 pulsado
    modifPB3 = 1;
    incrementarFrecuencia();
  }
  /* USER CODE END EXTI2_3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI2_3_IRQn 1 */

  /* USER CODE END EXTI2_3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */
  if((EXTI->PR & (1UL << 4)) != 0){
    if(ms - PB4ultimo > 10){
    PB4ultimo = ms;
    numSecuencia++;
    modifPB4 = 1;
    if(numSecuencia > 2){
      numSecuencia = 0;
    }
  }
  }
  if((EXTI->PR & (1UL << 5)) != 0){//Ponemos sistema en pausa
    if(ms - PB5ultimo > 10){
      PB5ultimo = ms;
      pausa++;
      if(pausa > 1){
      pausa = 0;
    }
    }
  }
  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global and DAC channel underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
  if(pausa != 1){
    secuencias(numSecuencia);
    contLed++;
    if(contLed >= 4){
      contLed = 0;
    }
  }
  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
  if(pausa != 1){
    if(pulsadoPB3 == 1){
    if((GPIOB->IDR & (1UL << 3)) != 0){
      tiempoPB3++;
      if(tiempoPB3 >= 2000){
        tiempoPB3 = 1500; //Así cuando pasen 500ms se vuelve a ejecutar el incremento
        incrementarFrecuencia();
      }
    }else{
        pulsadoPB3 = 0;
        tiempoPB3 = 0;
    }
  }
  }
  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles TIM16 global interrupt.
  */
void TIM16_IRQHandler(void)
{
  /* USER CODE BEGIN TIM16_IRQn 0 */
  if(pausa != 1){
    if(modifPB3 != 1 && modifPB4 != 1){//Si no se ha pulsado ningun boton en 5 minutos
    if (((GPIOB->IDR & (1UL << 3)) != 0) || ((GPIOB->IDR & (1UL << 4)) != 0)){// Si se pulsa algun boton se sale del if
      modifPB3 = 1;
      modifPB4 = 1;
    }else{
      GPIOA->BSRR = (1UL << 24) | (1UL << 25) | (1UL << 26);//Si no se pulsa nada se apaga todo
    }
  }
  modifPB3 = 0;
  modifPB4 = 0;
  }
  /* USER CODE END TIM16_IRQn 0 */
  HAL_TIM_IRQHandler(&htim16);
  /* USER CODE BEGIN TIM16_IRQn 1 */

  /* USER CODE END TIM16_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
