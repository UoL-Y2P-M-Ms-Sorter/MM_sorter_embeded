#include "step_motor.h"
#include "main.h"
#include "freertos.h"
#include "task.h"
#include "usart.h"
#define STEP_MOTOR_ROTATION_SPEED 1000;
#define SERVO_MOTOR_DIVIDE_ANGLE 60
void step_motor_speedset(int speed);
sorter_state_t sorter_state;
void calc_step_motor_speed();
void sorter_mode_set();
void sorter_run_mode_speed_set();
void step_motor_task(void *argument)
{
	sorter_state.working_mode = STOP;
	sorter_state.sorting_mode = PICK_SUGER;
	sorter_state.MMs_COLOR = NO_COLOR;
	while(1)
	{
		sorter_mode_set();
		calc_step_motor_speed();
		step_motor_speedset(sorter_state.step_motor_speed);
		vTaskDelay(1);
	}
}

void sorter_mode_set()
{
	if(sorter_state.working_mode == RUN)
	{
		if(sorter_state.sorting_mode == PICK_SUGER)
		{
	/*		if(HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState))
			{
				sorter_state.sorting_mode = CLASSIFY;
			}
	*/
		}
	}
	else if(sorter_state.working_mode == SAMPLE)
	{
		if(sorter_state.sorting_mode == PICK_SUGER)
		{


		}
	}
}
void calc_step_motor_speed()
{
	if(sorter_state.working_mode == STOP)
	{
		sorter_state.step_motor_speed = 0;
		return;
	}
	else if(sorter_state.working_mode == RUN)
	{
		sorter_run_mode_speed_set();
	}
	else if(sorter_state.working_mode == SAMPLE)
	{

	}
}
void sorter_run_mode_speed_set()
{
	if(sorter_state.sorting_mode == PICK_SUGER)
	{

	}
	else
	{
		switch (sorter_state.MMs_COLOR)
		{
		case NO_COLOR:
			sorter_state.step_motor_speed = 0;
			break;
		case BLUE:
			sorter_state.step_motor_speed = STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = SERVO_MOTOR_DIVIDE_ANGLE;
			break;
		case BROWN:
			sorter_state.step_motor_speed = STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = 0;
			break;
		case GREEN:
			sorter_state.step_motor_speed = STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = -SERVO_MOTOR_DIVIDE_ANGLE;
			break;
		case ORANGE:
			sorter_state.step_motor_speed = -STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = SERVO_MOTOR_DIVIDE_ANGLE;
			break;
		case RED:
			sorter_state.step_motor_speed = -STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = 0;
			break;
		case YELLOW:
			sorter_state.step_motor_speed = -STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = -SERVO_MOTOR_DIVIDE_ANGLE;
			break;
		default:
			break;
		}
	}
}
void sorter_sample_mode_speed_set()
{
	if(sorter_state.sorting_mode == PICK_SUGER)
	{

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
