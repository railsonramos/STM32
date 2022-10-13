/*
 * testes.h
 *
 *  Created on: Jul 19, 2022
 *      Author: arthu
 */

#ifndef TESTES_H_
#define TESTES_H_

#include "main.h"


#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define TESTE_REDE BIT0
#define TESTE_BAT_EXT BIT1
#define TESTE_BAT_INT BIT2
#define TESTE_24VOUT BIT3
#define TESTE_VCA BIT4
#define TESTE_VBUS_MON BIT5
#define TESTE_ALL BIT0|BIT1|BIT2|BIT3|BIT4|BIT5

// Funcoes exclusivas para comunicacao interface uart
void welcome_message(void);
void uart_transmit(uint8_t transmit,uint8_t test);




/*********************************************************************************************
//Funcoes de testes utilizam
// 		* LEDs da placa discoveryF4
//		* Verificacao da chave on/off
//		* Comunicacao uart
//		* Controle do IO_SW
*********************************************************************************************/
void teste_leds(uint8_t contador_passado);
void teste_usb (char* data, uint8_t contador_passado);
void teste_chav_state(uint8_t contador_passado);
void teste_sw_state(uint8_t contador_passado);
void teste_iosw(uint8_t contador_passado);
void uart_transmit(uint8_t transmit,uint8_t test);
/*********************************************************************************************
 * as funcoes teste_chav_XXXX são referentes ao "teste de chaveamento"
 *          * fecham a chave correspondente a fonte que querem testar
 *          * um led indica que foi ligado (ou execução do teste)
 *          * teste e feito manualmente (multimetro ou osciloscopio)
 ***********************************************************************************************/

void teste_chav_rede(uint8_t contador_passado);
void teste_chav_bat_ext(uint8_t contador_passado);
void teste_chav_bat_int(uint8_t contador_passado);


/*********************************************************************************************
 * as funcoes teste_XXXX são referentes aos testes de funcionamento correto do adc
 *          * fecham a chave correspondente a fonte que querem testar
 *          * um led indica que foi ligado (ou execução do teste)
 *          * o valor das fontes é constantemente atualizado na tela pela interface UART
 ***********************************************************************************************/

void teste_rede(uint8_t contador_passado);
void teste_bat_int(uint8_t contador_passado);
void teste_bat_ext(uint8_t contador_passado);

/*********************************************************************************************
 * as funcoes teste_vca é referente ao correto funcionamento (qualidade da tensao) no pino vca
 *          * Pode-se escolher qual fonte utilizar (a rede deve estar presente)
 *          * um led indica a execução do teste
 *         		 	* verificar o valor de tensao do VCA com um osciloscópio
 *          		* verificar o valor de tensao do pino vca amostrado pelo adc e disposto via UART
 *
 ***********************************************************************************************/
void teste_vca(uint8_t contador_passado);



/*********************************************************************************************
 * funcoes de atraso e avanco do timer, propositos
  	  	 * programar a amostragem do adc para acontecer numa taxa de 10 Hz
 	 	 * programar o pino sample para ser ligado momentos antes do inicio da transferencia
 ***********************************************************************************************/
void MX_TIM4_Init_at(void);
void MX_TIM4_Init_av(void);


// funcoes gerais de resetar pinos
void reset_led(void);
void reset_fontes(void);

// funcao para gerar um atraso no debounce da chave
void debounce(int x);

// funcao que monitora a chave e retorna um contador para execucao dos testes
int monitor_chave(void);

// funcao geral de testes (todas funcoes de testes anteriores estao dentro dela)
void teste(void);

// funcao para calcular o CRC
uint8_t crc8(uint8_t, uint8_t*, uint32_t);

extern char uart_buf[200];
extern int uart_buf_len;


#endif /* TESTES_H_ */
