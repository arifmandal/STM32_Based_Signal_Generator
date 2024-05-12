/*
 * menu.c
 *
 *  Created on: Mar 13, 2024
 *      Author: Arif Mandal
 */

#include "menu.h"

extern TIM_HandleTypeDef htim4;

char *main_menu_items[] = { "-> Set Frequency", "-> Set DutyCycle", "-> About" };
uint8_t selectedMenuItem = 0;
uint32_t encoderValue = 0;
uint32_t frequency = 0;
uint32_t dutyCycle = 0;
uint8_t onoffFlag = 1;

void printMenuItems(uint8_t menuCount) {

	ssd1306_Fill(Black);

	int i = 0;

	for (i = 0; i < menuCount; i++) {
		ssd1306_SetCursor(0, i * 20);

		if (i == selectedMenuItem) {
			ssd1306_WriteString(main_menu_items[i], Font_7x10, Black);
		} else {
			ssd1306_WriteString(main_menu_items[i], Font_7x10, White);
		}

	}

	ssd1306_UpdateScreen();
}

void handleMenuNavigation() {

	printMenuItems(MAIN_MENU_ITEM_COUNT);
	HAL_Delay(75);

	encoderValue = (TIM1->CNT) >> 3;
	selectedMenuItem = encoderValue % MAIN_MENU_ITEM_COUNT;

	ssd1306_WriteString(main_menu_items[selectedMenuItem], Font_7x10, White);

	if (selectedMenuItem == 0 && SELECT_CLICK) {
		selectedMenuItem = 0;
		TIM1->CNT = 0;
		while (1) {
			uint8_t outputStatus = HAL_GPIO_ReadPin(output_ON_GPIO_Port, output_ON_Pin);

			if (outputStatus) {
				showInfo();
				break;
			}
			setFrequency();
			HAL_Delay(150);
			if (SELECT_CLICK) {
				TIM1->CNT = 0;
				break;
			}
		}

		return;

	}

	if (selectedMenuItem == 1 && SELECT_CLICK) {
		selectedMenuItem = 0;
		TIM1->CNT = 0;
		while (1) {
			uint8_t outputStatus = HAL_GPIO_ReadPin(output_ON_GPIO_Port, output_ON_Pin);
			if (outputStatus) {
				showInfo();
				break;
			}
			setDutyCycle();
			HAL_Delay(150);
			if (SELECT_CLICK) {
				TIM1->CNT = 0;
				break;
			}
		}

		return;

	}

	if (selectedMenuItem == 2 && SELECT_CLICK) {
		selectedMenuItem = 0;
		while (1) {
			showAbout();
			HAL_Delay(150);
			if (SELECT_CLICK) {
				TIM1->CNT = 0;
				break;
			}
		}

		return;

	}

	if (ONOFF_CLICK) {

		if (!onoffFlag) {
			HAL_GPIO_WritePin(output_OFF_GPIO_Port, output_OFF_Pin, 1);
			HAL_GPIO_WritePin(output_ON_GPIO_Port, output_ON_Pin, 0);
			pwmChannelStop(&htim4, TIM_CHANNEL_1);
			onoffFlag = 1;
		} else {
			HAL_GPIO_WritePin(output_OFF_GPIO_Port, output_OFF_Pin, 0);
			HAL_GPIO_WritePin(output_ON_GPIO_Port, output_ON_Pin, 1);
			setPWMFreqDuty(frequency, dutyCycle);
			pwmChannelStart(&htim4, TIM_CHANNEL_1);
			onoffFlag = 0;
		}

	}

}

void setFrequency() {

	char buffer[20];
	frequency = 0;
	frequency = (TIM1->CNT) >> 1;
	frequency *= 100;
	if (frequency >= 1000000) {
		frequency = 1000000;
	}
	sprintf(buffer, "%ld", frequency);
	ssd1306_Fill(Black);
	ssd1306_SetCursor(30, 10);
	ssd1306_WriteString("Frequency", Font_7x10, White);
	ssd1306_SetCursor(50, 30);
	ssd1306_WriteString(buffer, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void setDutyCycle() {
	char buffer[20];
	dutyCycle = 0;
	dutyCycle = (TIM1->CNT) >> 1;
	dutyCycle *= 5;
	if (dutyCycle >= 100) {
		dutyCycle = 100;
	}
	sprintf(buffer, "%ld", dutyCycle);
	ssd1306_Fill(Black);
	ssd1306_SetCursor(30, 10);
	ssd1306_WriteString("Duty Cycle", Font_7x10, White);
	ssd1306_SetCursor(50, 30);
	ssd1306_WriteString(buffer, Font_7x10, White);
	ssd1306_UpdateScreen();

}

void showAbout() {

	ssd1306_Fill(Black);
	ssd1306_SetCursor(20, 10);
	ssd1306_WriteString("STM32 Based", Font_7x10, White);
	ssd1306_SetCursor(10, 30);
	ssd1306_WriteString("Signal Generator", Font_7x10, White);
	ssd1306_SetCursor(40, 50);
	ssd1306_WriteString("v1.0", Font_7x10, White);
	ssd1306_UpdateScreen();

}

void showInfo(){

	ssd1306_Fill(Black);
	ssd1306_SetCursor(20, 10);
	ssd1306_WriteString("Output ON", Font_7x10, White);
	ssd1306_UpdateScreen();
	HAL_Delay(2000);

}
