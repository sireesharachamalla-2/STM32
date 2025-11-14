/* Includes */
#include "main.h"
#include "cmsis_os.h"
#include<stdarg.h>
#include<stdio.h>
#include<string.h>

/* RGB GPIO pins */
#define RED_PIN    GPIO_PIN_5
#define GREEN_PIN  GPIO_PIN_6
#define BLUE_PIN   GPIO_PIN_7

/* Task handles */
osThreadId redTaskHandle;
osThreadId greenTaskHandle;
osThreadId blueTaskHandle;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Red_Task(void const * argument);
void Green_Task(void const * argument);
void Blue_Task(void const * argument);

void debug_printf(const char *fmt, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	uint16_t i = 0;
	while(buffer[i] != '\0')
	{
		ITM_SendChar(buffer[i]);
		i++;
	}
}
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    // Create tasks
    osThreadDef(redTask, Red_Task, osPriorityNormal, 0, 128);
    redTaskHandle = osThreadCreate(osThread(redTask), NULL);

    osThreadDef(greenTask, Green_Task, osPriorityNormal, 0, 128);
    greenTaskHandle = osThreadCreate(osThread(greenTask), NULL);

    osThreadDef(blueTask, Blue_Task, osPriorityNormal, 0, 128);
    blueTaskHandle = osThreadCreate(osThread(blueTask), NULL);

    // Start scheduler
    osKernelStart();

    while(1);
}

/* Red LED*/
void Red_Task(void const * argument)
{
	debug_printf(" red led task running\n");
    while(1)
    {

        HAL_GPIO_WritePin(GPIOA, RED_PIN, GPIO_PIN_SET);
        osDelay(500);
        HAL_GPIO_WritePin(GPIOA, RED_PIN, GPIO_PIN_RESET);
        osDelay(500);
    }
}

/* Green LED  */
void Green_Task(void const * argument)
{
	debug_printf(" green led task running\n");
    while(1)
    {
        HAL_GPIO_WritePin(GPIOA, GREEN_PIN, GPIO_PIN_SET);
        osDelay(300);
        HAL_GPIO_WritePin(GPIOA, GREEN_PIN, GPIO_PIN_RESET);
        osDelay(300);
    }
}

/* Blue LED  */
void Blue_Task(void const * argument)
{
	debug_printf(" blue led task running\n");
    while(1)
    {
        HAL_GPIO_WritePin(GPIOA, BLUE_PIN, GPIO_PIN_SET);
        osDelay(1000);
        HAL_GPIO_WritePin(GPIOA, BLUE_PIN, GPIO_PIN_RESET);
        osDelay(1000);
    }
}

/* GPIO Init */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = RED_PIN | GREEN_PIN | BLUE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLP = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
}

