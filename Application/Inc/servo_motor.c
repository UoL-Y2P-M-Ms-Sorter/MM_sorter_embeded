#include"servo_motor.h"
#include "main.h"
#include "freertos.h"
#include "task.h"
#include "tim.h"
void servo_motor_angleset(int angle);
void servo_motor_task(void *argument)
{
	while(1)
	{
		vTaskDelay(1);
	}
}



