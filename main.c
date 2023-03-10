/**
  ******************************************************************************
  * @file    main.c
  * @author  Shaurya Chandra
  * @version v1.0
  * @date    08-March-2023
  * @brief   Main program body.
  ******************************************************************************
  */

/* Header includes -----------------------------------------------------------*/
#include "main.h"
#include "CAN.h"

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
static CanTxMsg canTxMsg = {0};
static CanRxMsg canRxMsg = {0};

/* Function declarations -----------------------------------------------------*/
static void SystemClock_Config(void);

/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
int main(void)
{
  /* Configure the system clock to 72MHz. */
  SystemClock_Config();
  SystemCoreClockUpdate();

  /* Add your application code here. */
  CAN_Configure(CAN1, CAN_WorkModeLoopBack, CAN_BaudRate250K, 0xAA55, 0x55AA);

  /* Infinite loop. */
  while(1)
  {
    canTxMsg.StdId = 0xAA55;
    canTxMsg.ExtId = 0x55AA;
    canTxMsg.IDE   = CAN_ID_STD;
    canTxMsg.RTR   = CAN_RTR_DATA;
    canTxMsg.DLC   = 8;
    
    canTxMsg.Data[0]++;
    canTxMsg.Data[1]++;
    canTxMsg.Data[2]++;
    canTxMsg.Data[3]++;
    canTxMsg.Data[4]++;
    canTxMsg.Data[5]++;
    canTxMsg.Data[6]++;
    canTxMsg.Data[7]++;
    
    CAN_SetTransmitMessage(CAN1, &canTxMsg, 1);
    
    while(CAN_IsReceiveBufferEmpty(CAN1) == true);
    
    CAN_GetReceiveMessage(CAN1, &canRxMsg, 1);
  }
}

/**
  * @brief  System Clock Configuration.
  *         The system clock is configured as follow:
  *         System Clock Source = PLL(HSE)
  *         SYSCLK(Hz)          = 72000000
  *         HCLK(Hz)            = 72000000
  *         AHB Prescaler       = 1
  *         APB1 Prescaler      = 2
  *         APB2 Prescaler      = 1
  *         HSE Frequency(Hz)   = 8000000
  *         HSE PREDIV1         = 1
  *         PLLMUL              = 9
  *         Flash Latency(WS)   = 2
  * @param  None.
  * @return None.
  */
static void SystemClock_Config(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration. */
  /* RCC system reset. */
  RCC_DeInit();
  
  /* Enable HSE. */
  RCC_HSEConfig(RCC_HSE_ON);
  
  /* Wait till HSE is ready. */
  ErrorStatus HSEStartUpStatus = RCC_WaitForHSEStartUp();
  
  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable prefetch buffer. */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    
    /* Flash 2 wait state. */
    FLASH_SetLatency(FLASH_Latency_2);
    
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    
    /* PCLK1 = HCLK / 2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* Configure PLLs. */
#ifdef STM32F10X_CL
    /* PLL2 configuration: PLL2CLK = (HSE(8MHz) / 2) * 10 = 40MHz. */
    RCC_PREDIV2Config(RCC_PREDIV2_Div2);
    RCC_PLL2Config(RCC_PLL2Mul_10);
    
    /* Enable PLL2. */
    RCC_PLL2Cmd(ENABLE);
    
    /* Wait till PLL2 is ready. */
    while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET);
    
    /* PLL configuration: PLLCLK = (PLL2(40MHz) / 5) * 9 = 72MHz. */
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
#else
    /* PLLCLK = HSE(8MHz) * 9 = 72MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
#endif

    /* Enable PLL. */
    RCC_PLLCmd(ENABLE);
    
    /* Wait till PLL is ready. */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    
    /* Select PLL as system clock source. */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    
    /* Wait till PLL is used as system clock source. */
    while(RCC_GetSYSCLKSource() != 0x08);
  }
  else
  {
    /* Disable HSE. */
    RCC_HSEConfig(RCC_HSE_OFF);
    
    /* Enable HSI. */
    RCC_HSICmd(ENABLE);
    
    /* Enable prefetch buffer. */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    
    /* Flash 1 wait state. */
    FLASH_SetLatency(FLASH_Latency_1);
    
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    
    /* PCLK1 = HCLK */
    RCC_PCLK1Config(RCC_HCLK_Div1);
    
    /* Configure PLLs. */
    /* PLLCLK = HSI(8MHz) / 2 * 9 = 36MHz */
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_9);
    
    /* Enable PLL. */
    RCC_PLLCmd(ENABLE);
    
    /* Wait till PLL is ready. */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    
    /* Select PLL as system clock source. */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    
    /* Wait till PLL is used as system clock source. */
    while(RCC_GetSYSCLKSource() != 0x08);
  }
}
