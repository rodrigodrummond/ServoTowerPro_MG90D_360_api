/*
 * servo_MG90D_Tower_Pro.h
 *
 *  Created on: 17 de jul de 2021
 *      Author: Rodrigo Drummond Lima
 *      Federal University of Minas Gerais (UFMG) - Brazil
 *      MIT Licence
 *  Version 1.0 - API with the following functions:
    Servo initServo(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period)
      - This function initializes the servo motor with the desired specifications
        and returns an object with those features. Make sure to put the Counter Period
        you calculated in **uint16_t period** field.

    void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse)
      - This function is used internally in other functions and configures the timer
        to generate the PWM signal with the desired pulse width and period.
        It was developed by professor Ricardo de Oliveira Duarte, UFMG.

    void setClockwiseSpeed(Servo S, float percent_speed)
      - This function makes the motor rotate clockwise with the desired percentage speed,
        relative to the nominal maximum speed. This function caps the speed at 110% to
        prevent damage to the motor. If you want, you can change it inside the program to get higher speeds.

    void setCounterClockwiseSpeed(Servo S, float percent_speed)
      - This function makes the motor rotate counterclockwise with the desired percentage speed,
        relative to the nominal maximum speed. This function caps the speed at 110% to
        prevent damage to the motor.

    void stopServo(Servo S);
      - This function simulates the motor braking, so it gradually reduces the speed until it stops.

    *Function setPWM is designed by professor Ricardo de Oliveira Duarte.

    This API implements a series of functions to control the
    Servo Motor MG90D Tower Pro 360° with the STM32 NUCLEO F103RB.
    Feel free to use, modify and adapt this API.

    This API was developed as a project for the Embedded Systems Programming
    course at the Federal University of Minas Gerais (UFMG) in July 2021,
    with professor Ricardo de Oliveira Duarte - Department of Electronic Engineering.
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
