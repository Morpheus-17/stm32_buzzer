/*
 * app.c
 *
 *  Created on: Nov 25, 2024
 *      Author: blueb
 */

#include "app.h"
#include "uart.h"

extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;

//Look-up table
uint16_t soundLut[] = {
		261, // �� 4
		293, // �� 4
		329, // �� 4
		349, // �� 4
		392, // �� 4
		440, // �� 4
		493, // �� 4
		523  // �� 5
};

void setSound(int frequency){
	// main clock = 16MHz
	// timer prescaler  = 1/16 -> 1MHz
	// ARR : timer prescaler / frequency - 1;
	// CNT ���� ARR �� �񱳽� CNT�� �ʰ��ϸ� ������ count �Ǳ� ������
	htim1.Instance->ARR	=1000000/frequency-1;
	htim1.Instance->CNT	=0;
	htim1.Instance->CCR1=htim1.Instance->ARR/2;
}

void stopSound(){
	htim1.Instance->CCR1=0;
}

void app(){
	// Ÿ�̸� ����
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	// Initialize uart
	initUart(&huart2);

	// Ÿ�̸� ���ļ� ����
	while(1){
#if 0
//		for(int i=20; i<20000; i++){
//			setSound(i);
//			HAL_Delay(10);
//		}

		for(int i=0; i<8; i++){
			setSound(soundLut[i]);
			HAL_Delay(100);
		}
#else
		char ch = getUart();
		switch(ch){
			case 'c':
				setSound(soundLut[0]);
				break;
			case 'd':
				setSound(soundLut[1]);
				break;
			case 'e':
				setSound(soundLut[2]);
				break;
			case 'f':
				setSound(soundLut[3]);
				break;
			case 'g':
				setSound(soundLut[4]);
				break;
			case 'a':
				setSound(soundLut[5]);
				break;
			case 'b':
				setSound(soundLut[6]);
				break;
			case 'C':
				setSound(soundLut[7]);
				break;
			case ' ':
				stopSound();
				break;
		}
		HAL_Delay(200);
#endif
	}
}
