#include"servo_motor.h"
#include "main.h"
#include "freertos.h"
#include "task.h"
#include "tim.h"
int angle = 30;
void servo_motor_angleset(int angle);
void servo_motor_task(void *argument)
{
	HAL_TIM_PWM_Start (&htim2, TIM_CHANNEL_1);
	while(1)
	{
		servo_motor_angleset(angle);
	}
}


void servo_motor_angleset(int angle)
{
	int duty = (135 + angle)/0.9;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);

}
