/*
 * fsm_uart.c
 *
 *  Created on: DEC 10, 2024
 *      Author: ASUS
 */
#include "fsm_uart.h"



uint8_t temp = 0;

uint8_t buffer [ MAX_BUFFER_SIZE ] = {'\0'};
uint8_t index_buffer = 0;

uint8_t buffer_flag = 0;

uint32_t ADC_value = 0;
char str[20];

int commandStatus = 1;
int uartStatus = 1;


void HAL_UART_RxCpltCallback ( UART_HandleTypeDef * huart ) {
	if( huart -> Instance == USART2 ) {
		buffer [ index_buffer ++] = temp ;
		if( index_buffer == 30) index_buffer = 0;
		buffer_flag = 1;
		HAL_UART_Transmit (& huart2 , & temp , 1 , 50) ;
		HAL_UART_Receive_IT (&huart2 , & temp , 1) ;
	}
}

void command_parser_fsm() {
    switch (commandStatus) {
        case 1:
            if (temp == '!') {
            	commandStatus = 2;
            }
            break;
        case 2:
            if (temp == '#') {
            	commandStatus = 1;
                uartStatus = 2;
            }
            break;
        default:
            break;
    }
}
void clear(){
	for (int i = 0; i < MAX_BUFFER_SIZE; i++) {
	        buffer[i] = '\0';
	    }
	    index_buffer = 0;
}

char* getBuffer() {
    return (char*) buffer;
}
void uart_communication_fsm() {
    switch (uartStatus) {
        case 1:
            break;
        case 2:

            if (strncmp(getBuffer(), "!RST#",5) == 0) {
                ADC_value = HAL_ADC_GetValue(&hadc1);
                HAL_UART_Transmit(&huart2, (void *)str,  sprintf(str, "\r\n!ADC=%ld#", ADC_value), 1000);
                setTimer1(300);
                clear();
                uartStatus = 3;
            } else {
                uartStatus = 1;
            }
            clear();
            break;
        case 3:

            if (timer1_flag == 1) {

                ADC_value = HAL_ADC_GetValue(&hadc1);
                HAL_UART_Transmit(&huart2, (void*) str,  sprintf(str, "\r\n!ADC=%ld#", ADC_value), 1000);
                setTimer1(300);
            }
            if (strncmp(getBuffer(), "!OK#",4) == 0) {
                uartStatus = 1;
            }
            break;
        default:
            break;
    }
}
