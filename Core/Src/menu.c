/*
 * menu.c
 *
 *  Created on: Mar 13, 2024
 *      Author: Arif Mandal
 */

#include "menu.h"

char *main_menu_items[] = { "-> Set Frequency", "-> Set DutyCycle", "-> About" };
uint8_t selectedMenuItem = 0;
uint32_t encoderValue = 0;

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
	HAL_Delay(150);

	encoderValue = (TIM1 ->CNT) >> 3;
	selectedMenuItem = encoderValue % MAIN_MENU_ITEM_COUNT;

	ssd1306_WriteString(main_menu_items[selectedMenuItem], Font_7x10, White);

	if (selectedMenuItem == 0 && SELECT_CLICK) {
		selectedMenuItem = 0;
		while(1){
			setFrequency();
			HAL_Delay(150);
			if (SELECT_CLICK) {
				TIM1 ->CNT = 0;
				break;
			}
		}

		return;

	}

}

void setFrequency(){

	ssd1306_Fill(Black);
	ssd1306_SetCursor(10, 10);
	ssd1306_WriteString("set freq", Font_7x10, White);
	ssd1306_UpdateScreen();
}
