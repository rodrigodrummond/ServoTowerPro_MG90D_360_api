/*
 * servo_MG90D_Tower_Pro.c
 *
 *  Created on: 17 de jul de 2021
 *      Author: RodrigoDrummond
 */

#include "servo_MG90D_Tower_Pro.h"
#include "main.h"


Servo initServo(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period){
	Servo s;
	s.timer = timer;
	s.channel = channel;
	s.period = period;
	s.pw = ZERO_SPEED_DC*period;
	setPWM(s.timer, s.channel, s.period, s.pw);
	return s;
}

void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse)
{
	 HAL_TIM_PWM_Stop(&timer, channel); // stop generation of pwm
	 TIM_OC_InitTypeDef sConfigOC;
	 timer.Init.Period = period; // set the period duration
	 HAL_TIM_PWM_Init(&timer); // reinititialise with new period value
	 sConfigOC.OCMode = TIM_OCMODE_PWM1;
	 sConfigOC.Pulse = pulse; // set the pulse duration
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	 HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
	 HAL_TIM_PWM_Start(&timer, channel); // start pwm generation
}

void setClockwiseSpeed(Servo S, float percent_speed){
	if(percent_speed>110){
		percent_speed = 110;
	}
	uint16_t pw;
	pw = S.period*ZERO_SPEED_DC-percent_speed/100*((ZERO_SPEED_DC- MAX_SPEED_CW_DC)*S.period);
	setPWM(S.timer,S.channel,S.period,pw);
	S.pw = pw;
}

void setCounterClockwiseSpeed(Servo S, float percent_speed){
	if(percent_speed>110){
		percent_speed = 110;
	}
	uint16_t pw;
	pw = S.period*ZERO_SPEED_DC+percent_speed/100*(( MAX_SPEED_CCW_DC -ZERO_SPEED_DC)*S.period);
	setPWM(S.timer,S.channel,S.period,pw);
	S.pw = pw;
}

void stopServo(Servo S){
	uint16_t pw_inicial = S.pw;
	float pw_aux = S.period*ZERO_SPEED_DC;
	float resto = pw_aux- (int)pw_aux;
	int arredonda = 0;
	if(resto>0.5){
		arredonda = 1;
	}
	int pw_final = (int) pw_aux + arredonda;
	if(pw_inicial > pw_final){
		for(uint16_t i = pw_inicial; i > pw_final; i--){
			setPWM(S.timer, S.channel, S.period, i);
			S.pw = i;
			HAL_Delay(100);
		}
		return;
	}
	if(pw_inicial < pw_final){
		for(int i = pw_inicial; i < pw_final; i++){
			setPWM(S.timer, S.channel, S.period, i);
			S.pw = i;
			HAL_Delay(100);
		}
		return;
	}
}

