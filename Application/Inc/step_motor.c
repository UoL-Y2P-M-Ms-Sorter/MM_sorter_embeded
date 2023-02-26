#include "step_motor.h"
#include "main.h"
#include "freertos.h"
#include "task.h"
#include "usart.h"
#include "tim.h"
#define STEP_MOTOR_ROTATION_SPEED 10;
#define SERVO_MOTOR_DIVIDE_ANGLE 40
extern int16_t tim_step_speed;
extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim2;
int16_t speed_test=0;
void step_motor_speedset(int speed);
void servo_motor_angleset(int angle);

sorter_state_t sorter_state;

void calc_step_motor_speed();
void sorter_mode_set();
void sorter_run_mode_speed_set();
void step_motor_task(void *argument)
{
	sorter_state.working_mode = STOP;
	sorter_state.sorting_mode = PICK_SUGER;
	sorter_state.MMs_COLOR = ORANGE;
	sorter_state.servo_motor_angle = 0;
	HAL_TIM_PWM_Start (&htim2, TIM_CHANNEL_1);
	while(1)
	{
		sorter_mode_set();
		calc_step_motor_speed();
		step_motor_speedset(sorter_state.step_motor_speed);
		servo_motor_angleset(sorter_state.servo_motor_angle);
		vTaskDelay(1);
	}
}

void sorter_mode_set()
{
	static uint16_t times = 0;
	if(sorter_state.working_mode == RUN)
	{
		if(sorter_state.sorting_mode == PICK_SUGER)
		{
			times++;
			if(times>2000)
			{
				if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8))
				{
					times = 0;
					sorter_state.sorting_mode = CHOOSE_COLOR;
				}
			}

		}
		else if(sorter_state.sorting_mode == CLASSIFY)
		{
			times++;
			if(times>2000)
			{
				if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8))
				{
					times = 0;
					sorter_state.sorting_mode = PICK_SUGER;
				}
			}

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
uint16_t counts = 0;
void sorter_run_mode_speed_set()
{
	if(sorter_state.sorting_mode == PICK_SUGER)
	{
		sorter_state.step_motor_speed = -STEP_MOTOR_ROTATION_SPEED;
	}
	else if(sorter_state.sorting_mode == CHOOSE_COLOR)
	{
		sorter_state.sorting_mode = CLASSIFY;
		switch (sorter_state.MMs_COLOR)
		{
		case NO_COLOR:
			sorter_state.step_motor_speed = 0;
			sorter_state.sorting_mode = CHOOSE_COLOR;
			counts++;
			if (counts>100)
			{
				counts = 0;
				sorter_state.sorting_mode = CLASSIFY;
				sorter_state.step_motor_speed = STEP_MOTOR_ROTATION_SPEED;
				sorter_state.servo_motor_angle = SERVO_MOTOR_DIVIDE_ANGLE;
			}
			break;
		case BLUE:
			counts = 0;
			sorter_state.step_motor_speed = STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = SERVO_MOTOR_DIVIDE_ANGLE;
			break;
		case BROWN:
			counts = 0;
			sorter_state.step_motor_speed = STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = 0;
			break;
		case GREEN:
			sorter_state.step_motor_speed = STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = -SERVO_MOTOR_DIVIDE_ANGLE;
			break;
		case ORANGE:
			counts = 0;
			sorter_state.step_motor_speed = -STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = SERVO_MOTOR_DIVIDE_ANGLE;
			break;
		case RED:
			counts = 0;
			sorter_state.step_motor_speed = -STEP_MOTOR_ROTATION_SPEED;
			sorter_state.servo_motor_angle = 0;
			break;
		case YELLOW:
			counts = 0;
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
	if(sorter_state.sorting_mode == CLASSIFY)
	{
		if(sorter_state.MMs_COLOR<3)
		{

		}
		else
		{

		}
	}

}
void servo_motor_angleset(int angle)
{
	int duty = (135 + angle)/0.9;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);

}
void step_motor_speedset(int speed)
{
	tim_step_speed = speed;
	uint16_t frequency;
	if(speed < 0){
		speed = -speed;
	}
	else if (speed == 0){
		HAL_TIM_Base_Stop_IT(&htim11);
		return;
	}
	frequency = (6 * speed * 64)/5.625;
	__HAL_TIM_SET_PRESCALER(&htim11,(2400/frequency)-1);
	HAL_TIM_Base_Start_IT(&htim11);
}
