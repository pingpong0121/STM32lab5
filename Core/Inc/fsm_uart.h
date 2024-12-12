/*
 * fsm_uart.h
 *
 *  Created on: DEC, 2024
 *      Author: ASUS
 */

#ifndef INC_FSM_UART_H_
#define INC_FSM_UART_H_

#include "software_timer.h"
#include "main.h"
#include "stdio.h"
#include "string.h"

#define MAX_BUFFER_SIZE 30

void command_parser_fsm();
void uart_communication_fsm();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];

extern uint8_t buffer_flag ;


#endif /* INC_FSM_UART_H_ */
