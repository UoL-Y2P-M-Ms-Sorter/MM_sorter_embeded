#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H
#include "main.h"
void step_motor_task(void *argument);

typedef  enum {
	RUN=0,
	SAMPLE=1,
	STOP=2,
}working_mode_e;

typedef  enum {
	PICK_SUGER,
	CLASSIFY,
}sorting_mode_e;
typedef enum{
	NO_COLOR,
	BLUE,
	BROWN,
	GREEN,
	ORANGE,
	RED,
	YELLOW,
}MMs_COLOR_e;
typedef struct {
	working_mode_e working_mode;
	sorting_mode_e sorting_mode;
	int16_t step_motor_speed;
	MMs_COLOR_e MMs_COLOR;
	int16_t servo_motor_angle;
}sorter_state_t;
#endif
