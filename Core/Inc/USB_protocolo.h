/*
 * USB_protocolo.h
 *
 *  Created on: Oct 11, 2022
 *      Author: rails
 */

#ifndef INC_USB_PROTOCOLO_H_
#define INC_USB_PROTOCOLO_H_

void dataUSB();

typedef struct buffer{
	short versaoProtocolo;
	short versaoHardware;
	short versaoFirmware;
	char comando;
	char estadoLEDS : 4;
	char estadoChave : 1;
	char presencaCA : 1;
	char presencaBatExt : 1;
	char presencaBatInt : 1;
	char fonteUso : 2;
	char mudancaAli : 1;
	char estadoNivelBatExt : 2;
	char estadoNivelBatInt : 2;
	char tensaoAlimentacao;
	short correnteAlimentacao;
	char nivelBatExt;
	char nivelBatInt;
	char reservado1;
	char reservado2;
	char reservado3;
	char reservado4;
	short crc;
}Buffer;

#endif /* INC_USB_PROTOCOLO_H_ */
