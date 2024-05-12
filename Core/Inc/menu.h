/*
 * menu.h
 *
 *  Created on: Mar 13, 2024
 *      Author: Arif Mandal
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#include "main.h"
#include "ssd1306_conf.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"
#include "pwm.h"


#define MAIN_MENU_ITEM_COUNT    3
#define SELECT_CLICK          !(HAL_GPIO_ReadPin(select_GPIO_Port, select_Pin))
#define ONOFF_CLICK           (HAL_GPIO_ReadPin(ONOFF_BUTTON_GPIO_Port, ONOFF_BUTTON_Pin))

void printMenuItems(uint8_t menuCount);
void handleMenuNavigation(void);
void setFrequency(void);
void setDutyCycle(void);
void showAbout(void);
void showInfo(void);
#endif /* INC_MENU_H_ */
