/*
 * servo_MG90D_Tower_Pro.h
 *
 *  Created on: 17 de jul de 2021
 *      Author: RodrigoDrummond
 */

#ifndef SERVO_MG90D_TOWER_PRO_H_
#define SERVO_MG90D_TOWER_PRO_H_
#include <stdint.h>
#include "main.h"
#define MAX_SPEED_CCW_DC 0.1125
#define MAX_SPEED_CW_DC 0.0375
#define ZERO_SPEED_DC 0.075

typedef struct{
	TIM_HandleTypeDef timer;
	uint32_t channel;
	uint16_t period;
	uint16_t pw;
} Servo;

Servo initServo(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period);

void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);

void setClockwiseSpeed(Servo S, float percent_speed);

void setCounterClockwiseSpeed(Servo S, float percent_speed);

void stopServo(Servo S);

#endif /* SERVO_MG90D_TOWER_PRO_H_ */
