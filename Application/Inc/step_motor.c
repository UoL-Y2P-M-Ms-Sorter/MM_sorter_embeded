#include "step_motor.h"
#include "main.h"
#include "freertos.h"
#include "task.h"
void step_motor_speedset(int speed);
void step_motor_task(void *argument)
{
	while(1)
	{
		step_motor_speedset(-1000);
	}
}


void step_motor_speedset(int speed)
{
		if(speed > 0)
		{
			uint16_t t = 1000/speed;
			//A->PA1  B-PA4  C->PB0  D->PC1
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);//A
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);//AB (set B)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);//B (reset A)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//BC (set C)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);//C (reset B)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);//CD (set D)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//D (reset C)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);//DA
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);//A
			vTaskDelay (t);
		}
		else
		{
			uint16_t t = -1000/speed;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);//A
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);//DA
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);//D (reset A)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//CD (set C)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);//C (reset D)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);//BC (set B)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//B (reset C)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);//AB (set A)
			vTaskDelay (t);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);//A (reset B)
			vTaskDelay (t);

		}
}
