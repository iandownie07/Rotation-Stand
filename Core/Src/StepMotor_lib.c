/*
 * StepMotor_lib.c
 *
 *  Created on: Apr 22, 2025
 *      Author: ilbeyli
 */


#include "StepMotor_lib.h"
#include "configuration.h"
// ../../Core/Src/StepMotor_lib.c

void stepper_motor_init(m_cnfg_s *motor_conf, TIM_HandleTypeDef *tim_handle,
		uint32_t tim_channel, GPIO_TypeDef *dir_portx, uint32_t dir_pin){
	motor_conf->tim_handle = tim_handle;
	motor_conf->tim_channel= tim_channel;
	motor_conf->dir_portx = dir_portx;
	motor_conf->dir_pin = dir_pin;
	motor_conf->m_set.state = MOTOR_OFF;
	motor_conf->m_set.counter = 0;
	motor_conf->m_set.step = 0;
	}

void set_pwm_period_and_duty(m_cnfg_s* motor_conf, uint8_t index)
{
	float freq = freq_table[index].frequency_hz;
    float duty = freq_table[index].duty_cycle;

    uint32_t arr = (uint32_t)((1.0f / (freq*1600)) * 1000000.0f) - 1; // 
    uint32_t ccr = (uint32_t)(arr * duty);

    // Stop the timer
    //HAL_TIM_PWM_Stop(motor_conf->tim_handle, motor_conf->tim_channel);

    // Set the new period
    __HAL_TIM_SET_AUTORELOAD(motor_conf->tim_handle, arr);

    // Set the new pulse width based on duty cycle
    __HAL_TIM_SET_COMPARE(motor_conf->tim_handle, motor_conf->tim_channel, ccr);

    // Force update to apply ARR immediately
    __HAL_TIM_DISABLE(motor_conf->tim_handle);
    motor_conf->tim_handle->Instance->EGR |= TIM_EGR_UG;  // Generate update event
    __HAL_TIM_ENABLE(motor_conf->tim_handle);

    // Restart PWM
    //HAL_TIM_PWM_Start(motor_conf->tim_handle, motor_conf->tim_channel);
}

void startMotor(m_cnfg_s* motor_conf, direction_e direction, int step){
	if(motor_conf->m_set.state == MOTOR_OFF){
		motor_conf->m_set.step = step;
		motor_conf->m_set.state = MOTOR_ON;
		switch(direction){
			case CW:
				HAL_GPIO_WritePin(motor_conf->dir_portx, motor_conf->dir_pin, 1);
				break;
			case CCW:
				HAL_GPIO_WritePin(motor_conf->dir_portx, motor_conf->dir_pin, 0);
				break;
		}
		//__HAL_TIM_SET_COMPARE(motor_conf->tim_handle, motor_conf->tim_channel, 500); // 50% duty cycle on a 1 kHz pulse
		if (0 != step) {HAL_TIM_PWM_Start_IT(motor_conf->tim_handle, motor_conf->tim_channel);}
	}
}

void stopMotor(m_cnfg_s *motor_conf){
	if (motor_conf->m_set.counter == motor_conf->m_set.step){
		HAL_TIM_PWM_Stop_IT(motor_conf->tim_handle, motor_conf->tim_channel);
		motor_conf->m_set.counter= 0;
		motor_conf->m_set.step= 0;
		motor_conf->m_set.state= MOTOR_OFF;
	}
}