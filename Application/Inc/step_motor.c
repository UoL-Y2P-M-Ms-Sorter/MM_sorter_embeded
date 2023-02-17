#include "step_motor.h"
#include "main.h"
#include "freertos.h"
#include "task.h"
#include "usart.h"
#include "tim.h"
#define STEP_MOTOR_ROTATION_SPEED 1000;
#define SERVO_MOTOR_DIVIDE_ANGLE 60
extern int16_t tim_step_speed;
extern TIM_HandleTypeDef htim11;
int16_t speed_test=0;
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
