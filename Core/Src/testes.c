/*
 * testes.c
 *
 *  Created on: Jul 19, 2022
 *      Author: arthu
 */
#include"main.h"
#include"testes.h"
#include"stdio.h"
#include "USB_protocolo.h"


char uart_buf[200];
int uart_buf_len;
char* data = "Hello world\n";

UART_HandleTypeDef* add_uart = &huart2;
Buffer* envioUSB;

void teste(void)
{
	static uint8_t contador=0; // contadores que indicam quantas vezes a chave foi pressionada
    static uint8_t contador_passado; // guarda o estado passado, para que as chaves nao fiquem ligando e desligando

	welcome_message(); //  somente exibe uma mensagem de inicializacao dos testes

	contador=monitor_chave(); // um contador e utilzado para que receba o quantidade de vezes que a chave foi pressionada

	if(contador==1)
	{
		teste_leds(contador_passado);
	}
	else if(contador==2)
	{
		teste_usb (data, contador_passado);
	}
	else if(contador==3)
	{
		teste_chav_state(contador_passado);
	}
	else if(contador==4)
	{
		teste_sw_state(contador_passado);
	}
	else if(contador==5)
	{
		teste_iosw(contador_passado);
	}
	else if(contador==6)
	{
		teste_chav_rede(contador_passado); // somente liga a conexao do VCA (verificacao deve ser manual)
		//LEDs sao para debug na discoveryF406
	}
	else if(contador==7)
	{
		teste_chav_bat_ext(contador_passado); // somente liga a conexao do VCA (verificacao deve ser manual)
		//LEDs sao para debug na discoveryF406

	}
	else if(contador==8)
	{
		teste_chav_bat_int(contador_passado); // somente liga a conexao do VCA (verificacao deve ser manual)
		//LEDs sao para debug na discoveryF406

	}
	if(contador==9)
	{
		teste_rede(contador_passado); // Liga a fonte e mostra os valores pela UART das tensoes amostradas (ADC)
		//LEDs sao para debug na discoveryF406

	}
	else if(contador==10)
	{
		teste_bat_ext(contador_passado); //Liga a bateria externa e mostra os valores pela UART das tensoes amostradas (ADC)
		//LEDs sao para debug na discoveryF406

	}
	else if(contador==11)
	{
		teste_bat_int(contador_passado); //Liga a bateria interna e mostra os valores pela UART das tensoes amostradas (ADC)
		//LEDs sao para debug na discoveryF406

	}
	else if(contador==12)
	{
		teste_vca(contador_passado); //  mostra os valores VCA amostrados (ADC)
		//LEDs sao para debug na discoveryF406

	}
	else if(contador==13)
	{
	//	teste_chav_bat_ext();


	}

	contador_passado=contador;

}

void welcome_message(void)
{
	static int flag_umavez=0;
	if(flag_umavez==0)
	{
	uart_buf_len = sprintf(uart_buf, "-------Rotina de testes-------\n\r-------Pressiona SW para prosseguir-------\n\r\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
	flag_umavez=1;
	}
}
void uart_transmit(uint8_t transmit,uint8_t test)
{

	static uint8_t trans;
	static uint8_t test_a;
	static volatile uint32_t counter=0;



	trans=transmit;
	test_a=test;

	counter++;
	if (counter>90000)
	{
		    if((test_a & TESTE_REDE)==TESTE_REDE)
		    {
				uart_buf_len = sprintf(uart_buf, "EXECUCAO DO TESTE DE REDE\n\r\n\r");
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
		    }
		    if((test_a & TESTE_BAT_EXT)==TESTE_BAT_EXT)
		    {
				uart_buf_len = sprintf(uart_buf, "EXECUCAO DO TESTE DE BATERIA EXTERNA\n\r\n\r");
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
		    }
		    if((test_a & TESTE_BAT_INT)==TESTE_BAT_INT)
  		    {
   				uart_buf_len = sprintf(uart_buf, "EXECUCAO DO TESTE DE BATERIA INTERNA\n\r\n\r");
   				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
   		    }
		    if((test_a & TESTE_VCA)==TESTE_VCA)
  		    {
   				uart_buf_len = sprintf(uart_buf, "EXECUCAO DO TESTE DE VCA\n\r\n\r");
   				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
   		    }


		// escreve os valores de tensão e corrente da rede
			if((trans & TESTE_REDE)==TESTE_REDE)
			{
				uart_buf_len = sprintf(uart_buf, "V_REDE=%d   I_REDE=%d\r\n",adcResultsDMA[2],adcResultsDMA[5]);
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
			}

			// escreve os valores de tensão e corrente da bat_ext
			if((trans & TESTE_BAT_EXT)==TESTE_BAT_EXT)
			{
				uart_buf_len = sprintf(uart_buf, "VBAT_EXT=%d IBAT_EXT=%d\r\n",adcResultsDMA[1],adcResultsDMA[4]);
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);

			}
			// escreve os valores de tensão e corrente da bat_int
			if((trans & TESTE_BAT_INT)==TESTE_BAT_INT)
			{
				uart_buf_len = sprintf(uart_buf, "VBAT_INT=%d IBAT_INT=%d\r\n",adcResultsDMA[0],adcResultsDMA[3]);
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);

			}
			// escreve os valores de tensão e corrente 24V
			if((trans & TESTE_24VOUT)==TESTE_24VOUT)
			{
				uart_buf_len = sprintf(uart_buf, "V_24VOUT=%d V_24VOUT=%d\r\n",adcResultsDMA[8],adcResultsDMA[9]);
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);

			}
			//escreve os valores de tensão do VCA e VBUS_MON
			if((trans & TESTE_VCA)==TESTE_VCA)
			{
				uart_buf_len = sprintf(uart_buf, "VCA=%d\r\n",adcResultsDMA[6]);
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);

			}
			if((trans & TESTE_VBUS_MON)==TESTE_VBUS_MON)
			{
				uart_buf_len = sprintf(uart_buf, "VBUS_MON=%d\r\n",adcResultsDMA[7]);
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
			}

				uart_buf_len = sprintf(uart_buf, "-----------------------------------------\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);

	counter=0;
	}
	else
	{
		asm("nop");
	}


}

void teste_leds(uint8_t contador_passado){
	if (contador_passado == 0 ){
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, GPIO_PIN_RESET);
		HAL_Delay(500);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_RESET);
		HAL_Delay(500);

		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
		HAL_Delay(500);

		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
}

void teste_usb (char* data, uint8_t contador_passado){
	  envioUSB->versaoProtocolo = 101;
	  envioUSB->versaoHardware = 1;
	  envioUSB->versaoFirmware = 1;
	  envioUSB->comando = 1;
	  envioUSB->estadoLEDS = 2;
	  envioUSB->estadoChave = 1;
	  envioUSB->presencaCA = 1;
	  envioUSB->presencaBatExt = 1;
	  envioUSB->presencaBatInt = 1;
	  envioUSB->fonteUso = 2;
	  envioUSB->mudancaAli = 0;
	  envioUSB->estadoNivelBatExt = 1;
	  envioUSB->estadoNivelBatInt = 2;
	  envioUSB->tensaoAlimentacao = 15;
	  envioUSB->correnteAlimentacao = 1;
	  envioUSB->nivelBatExt = 60;
	  envioUSB->nivelBatInt = 90;
	  envioUSB->reservado1 = 0;
	  envioUSB->reservado2 = 0;
	  envioUSB->reservado3 = 0;
	  envioUSB->reservado4 = 0;
	  envioUSB->crc = 0;


	if (contador_passado == 1){
//		CDC_Transmit_FS((char*)data, strlen(data));
//		HAL_Delay(2000);
		CDC_Transmit_FS(envioUSB, sizeof(envioUSB));
		HAL_Delay(1000);
	}
}

void teste_chav_state(uint8_t contador_passado){
	if(contador_passado == 2){

		if (HAL_GPIO_ReadPin(CHAVE_STATE_GPIO_Port, CHAVE_STATE_Pin==0))
			HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_SET);

		else
			HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_RESET);
	}
}

void teste_sw_state(uint8_t contador_passado){
	if(contador_passado == 3){

		if (HAL_GPIO_ReadPin(SW_STATE_GPIO_Port, SW_STATE_Pin==0))
			HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_SET);

		else
			HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_RESET);

		}
}

void teste_iosw(uint8_t contador_passado){
	if(contador_passado == 4){
		HAL_GPIO_WritePin(L_AUX_BAT_VERDE_GPIO_Port, L_AUX_BAT_VERDE_Pin, GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(IO_SW_GPIO_Port, IO_SW_Pin, GPIO_PIN_SET);
	}
}

void teste_chav_rede(uint8_t contador_passado)
{
	if(contador_passado==5)
	{
	reset_fontes();
	reset_led();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(LIGA_REDE_GPIO_Port, LIGA_REDE_Pin, GPIO_PIN_SET);//liga a alimentação da rede

	/// imprime a identificação do teste e procedimento
	uart_buf_len = sprintf(uart_buf, "EXECUCAO DO TESTE P/ CHAVEAMENTO DE REDE\n\r\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
	uart_buf_len = sprintf(uart_buf, "		* VERFICACAO MANUAL\n\r\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
	}


}

void teste_chav_bat_ext(uint8_t contador_passado)
{
	if(contador_passado==6)
	{
	reset_fontes();
	reset_led();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(LIGA_EXT_GPIO_Port, LIGA_EXT_Pin, GPIO_PIN_SET);//liga a alimentação da rede

	/// imprime a identificação do teste e procedimento
	uart_buf_len = sprintf(uart_buf, "EXECUCAO DO TESTE P/ CHAVEAMENTO DE BATERIA EXTERNA\n\r\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
	uart_buf_len = sprintf(uart_buf, "		* VERFICACAO MANUAL\n\r\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
	}
}

void teste_chav_bat_int(uint8_t contador_passado)
{
	if(contador_passado==7)
	{
	reset_fontes();
	reset_led();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(LIGA_BAT_GPIO_Port, LIGA_BAT_Pin, GPIO_PIN_SET);//liga a alimentação da rede

	/// imprime a identificação do teste e procedimento
	uart_buf_len = sprintf(uart_buf, "EXECUCAO DO TESTE P/ CHAVEAMENTO DE BATERIA INTERNA\n\r\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
	uart_buf_len = sprintf(uart_buf, "		* VERFICACAO MANUAL\n\r\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 200);
	}
}

void teste_rede(uint8_t contador_passado)
{
	if(contador_passado==8)
	{
	reset_fontes();
	reset_led();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(LIGA_REDE_GPIO_Port, LIGA_REDE_Pin, GPIO_PIN_SET);//liga a alimentação da rede
	}
	uart_transmit(TESTE_REDE|TESTE_BAT_EXT|TESTE_BAT_INT,TESTE_REDE);

}

void teste_bat_ext(uint8_t contador_passado)
{

	if(contador_passado==9)
	{
	reset_fontes();
	reset_led();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(LIGA_EXT_GPIO_Port, LIGA_EXT_Pin, GPIO_PIN_SET);//liga a alimentação da rede
	}
	uart_transmit(TESTE_REDE|TESTE_BAT_EXT|TESTE_BAT_INT,TESTE_BAT_EXT);
}

void teste_bat_int(uint8_t contador_passado)
{
	if(contador_passado==10)
	{
	reset_fontes();
	reset_led();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(LIGA_BAT_GPIO_Port, LIGA_BAT_Pin, GPIO_PIN_SET);//liga a alimentação da rede
	}
	uart_transmit(TESTE_REDE|TESTE_BAT_EXT|TESTE_BAT_INT,TESTE_BAT_INT);
}

void teste_vca(uint8_t contador_passado)
{
	if(contador_passado==11)
	{
	reset_fontes();
	reset_led();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);//LEDs
	HAL_GPIO_WritePin(LIGA_REDE_GPIO_Port, LIGA_REDE_Pin, GPIO_PIN_SET);//liga a alimentação da rede
	}
	uart_transmit(TESTE_VCA,TESTE_VCA);
}



void reset_led(void)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);//LEDs
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);//LEDs
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);//LEDs
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);//LEDs
}

void reset_fontes(void)
{
HAL_GPIO_WritePin(LIGA_BAT_GPIO_Port, LIGA_BAT_Pin, GPIO_PIN_RESET); // desliga a alimentação da bateria interna
HAL_GPIO_WritePin(LIGA_EXT_GPIO_Port, LIGA_EXT_Pin, GPIO_PIN_RESET); // desliga a alimentação da bateria externa
HAL_GPIO_WritePin(LIGA_REDE_GPIO_Port, LIGA_REDE_Pin, GPIO_PIN_RESET);//desliga a alimentação da rede
}
int monitor_chave(void)
{
	static int S=0;
	static int contador=0;
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==0)
    {
        if(S==0)
        {
            S=1;
            debounce(2000); //atraso para prevenir o debounce da chave
        }
    }
    else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1)
    {
        if(S==1)
        {
            S=0;
            contador=contador+1;
            debounce(2000);// atraso para prevenir o debounce da chave
        }
    }
    if(contador ==8)
    {
    	contador=0;
    }
    return contador;
}

void debounce(int x){
	volatile int z;
	for(z=0;z<x;z++);
}


void MX_TIM4_Init_at(void)
{
  TIM_OC_InitTypeDef sConfigOC = {0};
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 2015;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim4);
}
void MX_TIM4_Init_av(void)
{
  TIM_OC_InitTypeDef sConfigOC = {0};
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 1000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim4);
}




/*
******************************************************************************************************
HAL_ADC_ConvCpltCallback é callback para quando a transferencia do adc se encerra,
HAL_TIM_OC_DelayElapsedCallback é callback para quando o timer atinger determinado valor de contagem
******************************************************************************************************
Portanto, na ordem


** feito na primeira rotina de callback do output compare (passo=0)
1) ligamos o sample quando executamos o atraso no pulso do output compare,
   executamos a rotina de atraso do pulso de callback



** feito na segunda rotina de callback do output compare (passo=1)
2) inicializamos a transferencia de dados com o dma por software
   ligamos um pino de debug
   executamos a rotina de avanço no pulso do output compare
   (agora só será gerado um callback de outputcompare depois que o timer executar um ciclo inteiro)




** feito na rotina de callback de conclusao do adc
3) paramos transferencia do DMA
   desligamos o sample
   desligamos o pino de debug


*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adcConversionComplete=1;
    HAL_ADC_Stop_DMA(&hadc1);
    HAL_GPIO_WritePin(SAMPLE_GPIO_Port, SAMPLE_Pin,GPIO_PIN_RESET); //desligar sample

    HAL_GPIO_WritePin(DEBUG_GPIO_Port, DEBUG_Pin,GPIO_PIN_RESET);// pino para debug
    HAL_GPIO_WritePin(Debug2_GPIO_Port, Debug2_Pin,GPIO_PIN_RESET);// pino para debug


}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	static char passo=0;

	if(passo == 0)
	{
		MX_TIM4_Init_at();
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,GPIO_PIN_SET); // pino para debug
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,GPIO_PIN_SET); // ligar sample

        passo=1;
	}
	if(passo == 1)
	{
		MX_TIM4_Init_av();
        HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcResultsDMA, adcChannelCount);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,GPIO_PIN_SET); // pino para debug
        passo=0;

	}
	  HAL_TIM_OC_Start_IT(&htim4,TIM_CHANNEL_3);

}


//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//
//}

