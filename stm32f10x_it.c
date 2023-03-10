/**
  ******************************************************************************
  * @file    stm32f10x_it.c
  * @author  Shaurya Chandra
  * @version v1.0
  * @date    08-March-2023
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  */

/* Header includes -----------------------------------------------------------*/
#include "stm32f10x_it.h"

#ifdef _RTE_
#include "RTE_Components.h"
#endif

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None.
  * @return None.
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None.
  * @return None.
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs. */
  while(1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None.
  * @return None.
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs. */
  while(1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None.
  * @return None.
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs. */
  while(1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None.
  * @return None.
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs. */
  while(1)
  {
  }
}

#ifndef RTE_CMSIS_RTOS2_RTX5
/**
  * @brief  This function handles SVCall exception.
  * @param  None.
  * @return None.
  */
void SVC_Handler(void)
{
}
#endif

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None.
  * @return None.
  */
void DebugMon_Handler(void)
{
}

#ifndef RTE_CMSIS_RTOS2_RTX5
/**
  * @brief  This function handles PendSVC exception.
  * @param  None.
  * @return None.
  */
void PendSV_Handler(void)
{
}
#endif

#ifndef RTE_CMSIS_RTOS2_RTX5
/**
  * @brief  This function handles SysTick handler.
  * @param  None.
  * @return None.
  */
void SysTick_Handler(void)
{
}
#endif

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the interrupt handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None.
  * @return None.
  */
/*void PPP_IRQHandler(void)
{
}*/
