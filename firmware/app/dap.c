/*******************************************************************************
 * @file dap.c
 * @brief Low level SWD interface functions.
 * @author Silicon Labs
 * @version 1.03
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <setjmp.h>
#include "dap.h"
#include "errors.h"

#include "main.h"

/* These codes are only needed for SWD protocol version 2 with multidrop */
static uint32_t selectionAlertSequence[] = { 0x6209F392, 0x86852D95, 0xE3DDAFE9, 0x19BC0EA2 };
static uint32_t activationCode = 0x1A;
extern uint32_t ErrorFlag;

#define SPI1_DR_8bit (*(__IO uint8_t *)((uint32_t)&(SPI1->DR)))
#define SPI1_DR_16bit (*(__IO uint16_t *)((uint32_t)&(SPI1->DR)))




/**********************************************************
 * Reads from an AP or DP register.
 * 
 * @param ap
 *   If this parameter is true, read from AP register. 
 *   If false read from DP register. 
 *
 * @param reg
 *   The register number [0-3] to read from
 * 
 * @param data[out]
 *   The register value is written to this parameter
 **********************************************************/    
static uint32_t readReg(bool ap, int reg, uint32_t *data)
{
	int i;
	uint32_t parity;
	uint32_t b;
	uint32_t ack = 0;
	uint32_t ret = SWD_ERROR_OK;
	
	uint16_t Rx1, Rx2;
	uint8_t Rxack;
	uint8_t Txd;
   
	/* Initalize output variable */
	*data = 0;
  
	/* Convert to int */
	int _ap = (int)ap;
	int _read = (int)1;
  
	int A2 = reg & 0x1;
	int A3 = (reg >> 1) & 0x1;
  
	/* Calulate parity */
	parity = (_ap + _read + A2 + A3) & 0x1;
  
  
	SWDIO_SET_OUTPUT();
	SPI1->CR2 = 0x1708; //set 8 bit - cmd
	
	
	/* Send request */
	
	Txd = 0x81;
	Txd |= _ap << 1;
	Txd |= _read << 2;
	Txd |= A2 << 3;
	Txd |= A3 << 4;
	Txd |= parity << 5;
	
	//uPrintf(" R: %02X, ", Txd);
	
	SpiSendByte(Txd);
	
	/* Turnaround */
	SWDIO_SET_INPUT();
	
	//read 
	SPI1->CR2 = 0x1408; //set 5 bit - gap + ACK + LSB
	Rxack = SpiSendByte(0xFF);
	ack = (Rxack >> 1) & 0x07;
	
	/* Verify that ACK is OK */
	if (ack == ACK_OK) {
  
		
		SPI1->CR2 = 0x1F08; //set 16 bit
		Rx1 = SpiSendWord(0xFFFF); //read 16 bit
		Rx2 = SpiSendWord(0xFFFF); //read 15 bit + parity
		SPI1->CR2 = 0x1708; //set 8 bit - tail
		
		SWDIO_SET_OUTPUT();
		SpiSendByte(0x00);
		
		*data = 0;
		*data |= (Rxack & 0x10) >> 4;
		*data |= Rx1 << 1;
		*data |= Rx2 << 17;
		parity = (Rx2 & 0x8000) >> 15;
		

		//uPrintf("%08X  ", data);
		
		b = *data;
		b = b - ((b >> 1) & 0x55555555); // add pairs of bits
		b = (b & 0x33333333) + ((b >> 2) & 0x33333333); // quads
		b = (b + (b >> 4)) & 0x0F0F0F0F; // groups of 8
		b = (b * 0x01010101) >> 24;          // horizontal sum of bytes
    
		/* Verify parity */
		if ((b & 0x01) == parity) 
		{
			ret = SWD_ERROR_OK;
		}
		else {
			ret = SWD_ERROR_PARITY;
		}
    
	} 
	else if (ack == ACK_WAIT) 
	{
		ret = SWD_ERROR_WAIT;
	} 
	else if (ack == ACK_FAULT) 
	{
		ret = SWD_ERROR_FAULT;
	} 
	else 
	{
		/* Line not driven. Protocol error */
		ret = SWD_ERROR_PROTOCOL;
	}
  
	return ret;
}

/**********************************************************
 * Writes to a DP or AP register.
 * 
 * @param ap
 *   If this parameter is true, write to AP register. 
 *   If false write to DP register. 
 *
 * @param reg
 *   The register number [0-3] to write to
 * 
 * @param data
 *   The value to write to the register
 **********************************************************/
static uint32_t writeReg(bool ap, int reg, uint32_t data, bool ignoreAck)
{
	uint32_t ack = 0;
	int i;
	uint32_t parity = 0;
	uint32_t b;
	uint32_t ret = SWD_ERROR_OK;
	uint8_t Txd;
  
	uint8_t Rxack;
	
	/* Convert to int */
	int _ap = (int)ap;
	int _read = (int)0;
  
	/* Calulate address bits */
	int A2 = reg & 0x1;
	int A3 = (reg >> 1) & 0x1;
  
	/* Calculate parity */
	parity = (_ap + _read + A2 + A3) & 0x1;
  
	SWDIO_SET_OUTPUT();
  
	SPI1->CR2 = 0x1708; //set 8 bit - cmd
	
	
	/* Write request */
	
	Txd = 0x81;
	Txd |= _ap << 1;
	Txd |= _read << 2;
	Txd |= A2 << 3;
	Txd |= A3 << 4;
	Txd |= parity << 5;
	
	SpiSendByte(Txd);
	
	//uPrintf("W: %02X, ", Txd);

	SPI1->CR2 = 0x1408; //set 5 bit - gap + ACK + gap
	SWDIO_SET_INPUT(); 
	
	Rxack = SpiSendByte(0xFF);
	
	ack = (Rxack >> 1) & 0x07;
	
	  
	if (ack == ACK_OK || ignoreAck) 
	{

		SWDIO_SET_OUTPUT();
    
		/* Write data */

		SPI1->CR2 = 0x1F08; //set 16 bit
		SpiSendWord(data);
		SpiSendWord(data >> 16);
		
		//uPrintf("%08X\r\n", data);
		
		b = data;
		b = b - ((b >> 1) & 0x55555555); // add pairs of bits
		b = (b & 0x33333333) + ((b >> 2) & 0x33333333); // quads
		b = (b + (b >> 4)) & 0x0F0F0F0F; // groups of 8
		b = (b * 0x01010101) >> 24;  
    
		/* Write parity bit an tail */
		SPI1->CR2 = 0x1308; //set 4 bit
		SpiSendByte(b & 0x01);
		
		SWDIO_SET_OUTPUT();
		/* 8-cycle idle period. Make sure transaction
		 * is clocked through DAP. */

		SPI1->CR2 = 0x1508; //set 6 bit
		SpiSendByte(0x00);
		
  
	} 
	else if (ack == ACK_WAIT) 
	{
		ret = SWD_ERROR_WAIT;
	} 
	else if (ack == ACK_FAULT) 
	{
		ret = SWD_ERROR_FAULT;
	} 
	else {
		/* Line not driven. Protocol error */
		ret = SWD_ERROR_PROTOCOL;
	}
    
  
	return ret;
  
}


/**********************************************************
 * Sends the JTAG-to-SWD sequence. This must be performed
 * at the very beginning of every debug session and
 * again in case of a protocol error. 
 **********************************************************/

void JTAG_to_SWD_Sequence(void)
{
	
	SPI1->CR2 = 0x1F08; //set 16 bit
	SWDIO_SET_OUTPUT();
	
	SpiSendWord(0xFFFF);
	SpiSendWord(0xFFFF);
	SpiSendWord(0xFFFF);
	SpiSendWord(0xFFFF);
	SpiSendWord(0xE79E); //reset
	SpiSendWord(0xFFFF);
	SpiSendWord(0xFFFF);
	SpiSendWord(0xFFFF);
	SpiSendWord(0x0000); //init
}

/**********************************************************
 * This function is used to take the target DAP from 
 * 'dormant' state to 'reset' state. It is only used
 * on DAPs that implement SWD protocol version 2 (or
 * later) that implements multidrop. 
 **********************************************************/

void exitDormantState(void)
{
	int i, j, b;
  
	SWDIO_SET_OUTPUT();
  
	/* At least 8 cycles with SWDIO high */
	SPI1->CR2 = 0x1F08; //set 16 bit
	SpiSendWord(0xFFFF);
  
	/* 128-bt selection alert sequence */
	for (i = 0; i < 4; i++)
	{
		SpiSendWord(selectionAlertSequence[i]);
		SpiSendWord(selectionAlertSequence[i] >> 16);
	}
	
	/* Four cycles with SWDIO low */
	SPI1->CR2 = 0x1308; //set 4 bit
	SpiSendByte(0x00);

  
	/* Serial Wire Activation code */

	SPI1->CR2 = 0x1708; //set 8 bit
	SpiSendByte(activationCode);


  
	/* Line reset */
	SPI1->CR2 = 0x1F08; //set 16 bit
	SWDIO_SET_OUTPUT();
  
	SpiSendWord(0xFFFF);
	SpiSendWord(0xFFFF);
	SpiSendWord(0xFFFF);
	SpiSendWord(0xFFFF);
}
  
/**********************************************************
 * Writes to one of the four AP registers in the currently
 * selected AP bank.
 * 
 * @param reg[in]
 *    The register number [0-3] to write to
 * 
 * @param data[in]
 *    Value to write to the register
 * 
 **********************************************************/
void writeAP(int reg, uint32_t data)
{
	
	//uPrintf("*** W AP: %02X, %08X  ", reg, data);
	
	uint32_t swdStatus;
	uint32_t retry = SWD_RETRY_COUNT;
	ErrorFlag = SWD_ERROR_OK;
	do {
		swdStatus = writeReg(true, reg, data, false);
		retry--;
	} while (swdStatus == SWD_ERROR_WAIT && retry > 0);  
  
	if (swdStatus != SWD_ERROR_OK) 
	{
		//uPrintf("WriteAP Err\r\n");
		ErrorFlag = swdStatus;
	}
}


/**********************************************************
 * Writes to one of the four DP registers.
 * 
 * @param reg[in]
 *    The register number [0-3] to write to
 * 
 * @param data[in]
 *    Value to write to the register
 * 
 **********************************************************/
void writeDP(int reg, uint32_t data)
{
	
	//uPrintf("*** W DP: %02X, %08X  ", reg, data);
	
	uint32_t swdStatus;
	uint32_t retry = SWD_RETRY_COUNT;
	ErrorFlag = SWD_ERROR_OK;
	
	do {
		swdStatus = writeReg(false, reg, data, false);
		retry--;
	} while (swdStatus == SWD_ERROR_WAIT && retry > 0); 
  
	if (swdStatus != SWD_ERROR_OK) 
	{
		//uPrintf("WriteDP Err\r\n");
		ErrorFlag = swdStatus;
	}
}


/**********************************************************
 * Writes to one of the four DP registers and ignores
 * the ACK response. This is needed when writing
 * to the TARGETSEL register.
 * 
 * @param reg[in]
 *    The register number [0-3] to write to
 * 
 * @param data[in]
 *    Value to write to the register
 * 
 **********************************************************/
void writeDpIgnoreAck(int reg, uint32_t data)
{
	
	//uPrintf("***** W DPnask: %02X, %08X\r\n", reg, data);
	
	uint32_t swdStatus;
	uint32_t retry = SWD_RETRY_COUNT;
	ErrorFlag = SWD_ERROR_OK;
	
	do {
		swdStatus = writeReg(false, reg, data, true);
		retry--;
	} while (swdStatus == SWD_ERROR_WAIT && retry > 0); 
  
	if (swdStatus != SWD_ERROR_OK) 
	{
		//uPrintf("WriteDP Err\r\n");
		ErrorFlag = swdStatus;
	}
}




/**********************************************************
 * Reads one of the four AP registers in the currently
 * selected AP bank.
 * 
 * @param reg[in]
 *    The register number [0-3] to read
 * 
 * @param data[out]
 *    Value of register is written to this parameter
 * 
 **********************************************************/
void readAP(int reg, uint32_t *data)
{
	uint32_t swdStatus;
	uint32_t retry = SWD_RETRY_COUNT;
	ErrorFlag = SWD_ERROR_OK;
  
	do {
		swdStatus = readReg(true, reg, data);
		retry--;
	} while (swdStatus == SWD_ERROR_WAIT && retry > 0); 
  
	if (swdStatus != SWD_ERROR_OK) 
	{
		//uPrintf("ReadAP Err\r\n");
		ErrorFlag = swdStatus;
	}
	
	//uPrintf("** R AP: %02X, %08X\r\n", reg, *data);
	
}


/**********************************************************
 * Reads one of the four DP registers.
 * 
 * @param reg[in]
 *    The register number [0-3] to read
 * 
 * @param data[out]
 *    Value of register is written to this parameter
 * 
 **********************************************************/
void readDP(int reg, uint32_t *data)
{
	uint32_t swdStatus;
	uint32_t retry = SWD_RETRY_COUNT;
	ErrorFlag = SWD_ERROR_OK;
  
	do {
		swdStatus = readReg(false, reg, data);
		retry--;
	} while (swdStatus == SWD_ERROR_WAIT && retry > 0); 
  
	if (swdStatus != SWD_ERROR_OK) {
		//uPrintf("ReadDP Err\r\n");
		ErrorFlag = swdStatus;
	}
	
	//uPrintf("** R DP: %02X, %08X\r\n", reg, *data);
}


/**********************************************************
 * Initalized the SW-DP. This function performs first
 * sends the JTAG-to-SWD sequence and then reads
 * the IDCODE register. 
 * 
 * @returns
 *    The value of the IDCODE register
 **********************************************************/
uint32_t initDp(void)
{
	uint32_t dpId;
  
	/* If connecting to a Multidrop capable SW-DP (SWD version 2), this 
	 * function must be run first. */
	//exitDormantState();
	
	JTAG_to_SWD_Sequence();
	
	//	aapExtensionSequence();
	
	  /* Send the JTAG-to-SWD switching sequence */
//	JTAG_to_SWD_Sequence();
  
	/* Read IDCODE to get the DAP out of reset state */
	readDP(DP_IDCODE, &dpId);

	if (ErrorFlag != SWD_ERROR_OK) return ErrorFlag;
		
	writeDP(0, 0x1E); //abort
	
	if (ErrorFlag != SWD_ERROR_OK) return ErrorFlag;
	
	/* Debug power up request */
	writeDP(DP_CTRL, DP_CTRL_CSYSPWRUPREQ | DP_CTRL_CDBGPWRUPREQ);
	
	if (ErrorFlag != SWD_ERROR_OK) return ErrorFlag;

	writeDP(0, 0x1E); //abort
	
	if (ErrorFlag != SWD_ERROR_OK) return ErrorFlag;

	
	/* Wait until we receive powerup ACK */
	int retry = PWRUP_TIMEOUT + 200;
	uint32_t status;
	while (retry > 0)
	{
		readDP(DP_CTRL, &status);
		
		if (ErrorFlag != SWD_ERROR_OK) return ErrorFlag;
		
		if ((status & (DP_CTRL_CDBGPWRUPACK | DP_CTRL_CSYSPWRUPACK)) 
		           == (DP_CTRL_CDBGPWRUPACK | DP_CTRL_CSYSPWRUPACK))
		{
			break;
		}
    
		retry--;
	}
  
	/* Throw error if we failed to power up the debug interface */
	if ((status & (DP_CTRL_CDBGPWRUPACK | DP_CTRL_CSYSPWRUPACK)) 
	            != (DP_CTRL_CDBGPWRUPACK | DP_CTRL_CSYSPWRUPACK))
	{
		ErrorFlag = SWD_ERROR_DEBUG_POWER;
		return ErrorFlag;
	}

	/* Select first AP bank */
	writeDP(DP_SELECT, 0x00);
	if (ErrorFlag != SWD_ERROR_OK) return ErrorFlag;
	
	return dpId;
}

/**********************************************************
 * Reads the ID of AP #0. This will be either
 *   - EFM32_AHBAP_ID  if device is unlocked
 *   - EFM32_AAP_ID    if device is locked
 * 
 * Note: on Zero Gecko it will always be EFM32_AHBAP_ID
 * and the AAP must be access as a memory mapped peripheral
 * 
 * @returns
 *    The value of IDR register (address 0xFC) for AP #0
 **********************************************************/
uint32_t readApId(void)
{
	uint32_t apId;
  
	/* Select last AP bank */
	writeDP(DP_SELECT, 0xf0);
  
	/* Dummy read AP ID */
	readAP(AP_IDR, &apId);
  
	/* Read AP ID */
	readDP(DP_RDBUFF, &apId);
  
	/* Select first AP bank again */
	writeDP(DP_SELECT, 0x00);
  
	return apId;
}

/**********************************************************
 * Sends the AAP Window Expansion Sequence. This sequence
 * should be sent on SWDIO/SWCLK when reset is held low.
 * This will cause the AAP window to be 255 times longer
 * when reset is released. 
 **********************************************************/
void aapExtensionSequence(void)
{
	
	//todo!
	
//	int i;
//  
//	SWCLK_SET();
//  
//	for (i = 0; i < 4; i++) {
//		SWDIO_CYCLE();
//	}
//  
//	SWCLK_CLR();
//  
//	for (i = 0; i < 4; i++) {
//		SWDIO_CYCLE();
//	}
//  
//	SWCLK_CLR();
}


/**********************************************************
 * Initalize the AHB-AP. The transfer size must be set
 * to 32-bit before trying to access any internal
 * memory. 
 **********************************************************/
void initAhbAp(void)
{    
	/* Set transfer size to 32 bit */  
	writeAP(AP_CSW, AP_CSW_DEFAULT);  
}
