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
volatile uint8_t cont = 0, sentido = 0;            // sentido: 0 asc, 1 desc
volatile uint16_t valorARR = 1;                    // frecuencia = valorARR * 0,5 Hz
volatile uint8_t pulsadoPB3 = 0, pulsadoPB4 = 0;   // 1 mientras el boton esta pulsado
volatile uint8_t bloqueoPB3 = 0, bloqueoPB4 = 0;   // antirrebote (ms restantes)
volatile uint16_t tPB3 = 0;                        // ms que lleva pulsado PB3
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

void secuencia(uint8_t contLed){
  switch(contLed){
    case 0:
      GPIOA->BSRR = (1UL << 24) | (1UL << 25) | (1UL << 26);
      break;
    case 1:
      GPIOA->BSRR = (1UL << 8) | (1UL << 25) | (1UL << 26);
      break;
    case 2:
      GPIOA->BSRR = (1UL << 24) | (1UL << 9) | (1UL << 26);
      break;
    case 3:
      GPIOA->BSRR = (1UL << 8) | (1UL << 9) | (1UL << 26);
      break;
    case 4:
      GPIOA->BSRR = (1UL << 24) | (1UL << 25) | (1UL << 10);
      break;
    case 5:
      GPIOA->BSRR = (1UL << 8) | (1UL << 25) | (1UL << 10);
      break;
    case 6:
      GPIOA->BSRR = (1UL << 24) | (1UL << 9) | (1UL << 10);
      break;
    case 7:
      GPIOA->BSRR = (1UL << 8) | (1UL << 9) | (1UL << 10);
      break;
    default:
      GPIOA->BSRR = (1UL << 24) | (1UL << 25) | (1UL << 26);
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
  if(bloqueoPB3 == 0 && pulsadoPB3 == 0){
    pulsadoPB3 = 1;
    bloqueoPB3 = 20;
    tPB3 = 0;
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
  if(bloqueoPB4 == 0 && pulsadoPB4 == 0){
    pulsadoPB4 = 1;
    bloqueoPB4 = 20;
    if(sentido == 0){
      sentido = 1;
    }else{
      sentido = 0;
    }
  }
  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global and DAC channel underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
  if(sentido == 0){
    if(cont < 7){
      cont++;
    }else{
      cont = 0;
    }
  }else{
    if(cont > 0){
      cont--;
    }else{
      cont = 7;
    }
  }
  secuencia(cont);
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
  // PB3: antirrebote, duracion y repeticion
  if(bloqueoPB3 > 0){
    bloqueoPB3--;
  }else if(pulsadoPB3 == 1){
    if((GPIOB->IDR & (1UL << 3) != 0)){      // sigue pulsado
      tPB3++;
      if(tPB3 >= 2000){
        tPB3 = 1500;                     // la siguiente suma llega 500 ms despues
        incrementarFrecuencia();
      }
    }else{                               // soltado
      pulsadoPB3 = 0;
      bloqueoPB3 = 20;
    }
  }

  // PB4: antirrebote y suelta
  if(bloqueoPB4 > 0){
    bloqueoPB4--;
  }else if(pulsadoPB4 == 1){
    if((GPIOB->IDR >> 4) % 2 == 0){      // soltado
      pulsadoPB4 = 0;
      bloqueoPB4 = 20;
    }
  }

  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);

  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */