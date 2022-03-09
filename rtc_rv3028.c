/*
 * rtc_rv3028.c
 *
 * Created: 03.02.2021 08:26:43
 *  Author: gfcwfzkm
 */ 

#include "rtc_rv3028.h"

#define RV3028_ADDRESS			0xA4
#define RV3028_READ				0x01
#define RV3028_WRITE			0x00

static uint8_t bcd2bin (uint8_t val)
{
	return val - 6 * ((val & 0xF0) >> 4);
}

static uint8_t bin2bcd (uint8_t val)
{
	return ((val / 10) << 4) | (val % 10);
}

void rv3028_initStruct(RV3028_t *rtc,
			void *ioInterface, uint8_t (*startTransaction)(void*),
			uint8_t (*sendBytes)(void*,uint8_t,uint8_t*,uint16_t),
			uint8_t (*getBytes)(void*,uint8_t,uint8_t*,uint16_t),
			uint8_t (*endTransaction)(void*))
{
	rtc->ioInterface = ioInterface;
	rtc->startTransaction = startTransaction;
	rtc->sendBytes = sendBytes;
	rtc->getBytes = getBytes;
	rtc->endTransaction = endTransaction;
}

enum RV3028_error rv3028_init(RV3028_t *rtc)
{
	uint8_t regRead;
	rtc->error = RV3028_NO_ERROR;	
	
	regRead = rv3028_readReg(rtc, RV3028_R_ID);
	rtc->HID = regRead >> 4;
	rtc->VID = regRead & 0x0F;
	rv3028_writeReg(rtc, RV3028_R_STATUS,0);
	
	return rtc->error;
}

void rv3028_writeReg(RV3028_t *rtc, uint8_t regAddr, uint8_t regVal)
{
	uint8_t tempBuf[2] = {regAddr, regVal};
	
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->sendBytes(rtc->ioInterface,
				RV3028_ADDRESS | RV3028_WRITE, tempBuf, 2);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
}

uint8_t rv3028_readReg(RV3028_t *rtc, uint8_t regAddr)
{
	uint8_t tempBuf = regAddr;
	
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->sendBytes(rtc->ioInterface,
				RV3028_ADDRESS | RV3028_WRITE, &tempBuf, 1);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
	
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->getBytes(rtc->ioInterface,
				RV3028_ADDRESS | RV3028_READ, &tempBuf, 1);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
	
	return tempBuf;
}

void rv3028_setTime(RV3028_t *rtc, RV3028_TIME_t *tme)
{
	uint8_t tempBuffer[8];
	rtc->error = RV3028_NO_ERROR;
	
	tempBuffer[0] = RV3028_R_SECOND;
	tempBuffer[1] = bin2bcd(tme->seconds);
	tempBuffer[2] = bin2bcd(tme->minutes);
	tempBuffer[3] = bin2bcd(tme->hours);
	tempBuffer[4] = bin2bcd(tme->weekday);
	tempBuffer[5] = bin2bcd(tme->date);
	tempBuffer[6] = bin2bcd(tme->month);
	tempBuffer[7] = bin2bcd(tme->year);
	
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->sendBytes(rtc->ioInterface, 
				RV3028_ADDRESS | RV3028_WRITE, tempBuffer, 8);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
}

void rv3028_getTime(RV3028_t *rtc, RV3028_TIME_t *tme)
{
	uint8_t tempBuffer[8];
	rtc->error = RV3028_NO_ERROR;
		
	tempBuffer[0] = RV3028_R_SECOND;
		
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->sendBytes(rtc->ioInterface,
				RV3028_ADDRESS | RV3028_WRITE, tempBuffer, 1);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
		
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->getBytes(rtc->ioInterface,
				RV3028_ADDRESS | RV3028_READ, tempBuffer, 7);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
	
	tme->seconds = bcd2bin(tempBuffer[0]);
	tme->minutes = bcd2bin(tempBuffer[1]);
	tme->hours = bcd2bin(tempBuffer[2]);
	tme->weekday = bcd2bin(tempBuffer[3]);
	tme->date = bcd2bin(tempBuffer[4]);
	tme->month = bcd2bin(tempBuffer[5]);
	tme->year = bcd2bin(tempBuffer[6]);
}

void rv3028_setUnixTime(RV3028_t *rtc, uint32_t unixTime)
{
	uint8_t tempBuffer[5];
	rtc->error = RV3028_NO_ERROR;
	
	tempBuffer[0] = RV3028_R_UNIXTIME_0;
	tempBuffer[1] = (uint8_t)unixTime;
	tempBuffer[2] = (uint8_t)(unixTime >> 8);
	tempBuffer[3] = (uint8_t)(unixTime >> 16);
	tempBuffer[4] = (uint8_t)(unixTime >> 24);
	
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->sendBytes(rtc->ioInterface,
			RV3028_ADDRESS | RV3028_WRITE, tempBuffer, 5);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
}

uint32_t rv3028_getUnixTime(RV3028_t *rtc)
{
	uint32_t unixtime;
	uint8_t tempBuffer[4];
	rtc->error = RV3028_NO_ERROR;
	
	tempBuffer[0] = RV3028_R_UNIXTIME_0;
	
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->sendBytes(rtc->ioInterface,
				RV3028_ADDRESS | RV3028_WRITE, tempBuffer, 1);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
	
	rtc->error |= rtc->startTransaction(rtc->ioInterface);
	rtc->error |= rtc->getBytes(rtc->ioInterface,
				RV3028_ADDRESS | RV3028_READ, tempBuffer, 4);
	rtc->error |= rtc->endTransaction(rtc->ioInterface);
	
	unixtime = (uint32_t)tempBuffer[3] << 24 | (uint32_t)tempBuffer[2] << 16 | (uint32_t)tempBuffer[1] << 8 | tempBuffer[0];
	
	return unixtime;
}

uint8_t rv3028_getStatus(RV3028_t *rtc)
{
	rtc->error = RV3028_NO_ERROR;
	
	return rv3028_readReg(rtc, RV3028_R_STATUS);
}

void rv3028_updateConfigEEPROM(RV3028_t *rtc)
{
	rtc->error = RV3028_NO_ERROR;
	
	do{}while(rv3028_readReg(rtc, RV3028_R_STATUS) & RV3028_R_STATUS_EEBUSY);
		
	rv3028_writeReg(rtc, RV3028_R_EE_COMMAND, RV3028_R_EE_COMMAND_NOP);
	rv3028_writeReg(rtc, RV3028_R_EE_COMMAND, RV3028_R_EE_COMMAND_UPDATE);
	
	do{}while(rv3028_readReg(rtc, RV3028_R_STATUS) & RV3028_R_STATUS_EEBUSY);
}

uint8_t rv3028_readUserEEPROM(RV3028_t *rtc, uint8_t addr)
{
	uint8_t tempReg, readedReg;
	
	rtc->error = RV3028_NO_ERROR;
	while(rv3028_readReg(rtc, RV3028_R_STATUS) & RV3028_R_STATUS_EEBUSY);
		
	tempReg = rv3028_readReg(rtc, RV3028_R_CONTROL_1_EERD);
	rv3028_writeReg(rtc, RV3028_R_CONTROL_1, tempReg | RV3028_R_CONTROL_1_EERD);
	
	rv3028_writeReg(rtc, RV3028_R_EE_ADDRESS, addr);
	rv3028_writeReg(rtc, RV3028_R_EE_COMMAND, RV3028_R_EE_COMMAND_NOP);
	rv3028_writeReg(rtc, RV3028_R_EE_COMMAND, RV3028_R_EE_COMMAND_READ);
	
	while(rv3028_readReg(rtc, RV3028_R_STATUS) & RV3028_R_STATUS_EEBUSY);
	
	readedReg = rv3028_readReg(rtc, RV3028_R_EE_DATA);
	
	rv3028_writeReg(rtc, RV3028_R_CONTROL_1, tempReg);
	
	return readedReg;
}


void rv3028_writeUserEEPROM(RV3028_t *rtc, uint8_t addr, uint8_t val)
{
	uint8_t tempReg;
	
	if (addr > RV3028_E_USER_EEPROM_END)	return;
	
	rtc->error = RV3028_NO_ERROR;
	while(rv3028_readReg(rtc, RV3028_R_STATUS) & RV3028_R_STATUS_EEBUSY);
	
	tempReg = rv3028_readReg(rtc, RV3028_R_CONTROL_1_EERD);
	rv3028_writeReg(rtc, RV3028_R_CONTROL_1, tempReg | RV3028_R_CONTROL_1_EERD);
	
	rv3028_writeReg(rtc, RV3028_R_EE_ADDRESS, addr);
	rv3028_writeReg(rtc, RV3028_R_EE_DATA, val);
	rv3028_writeReg(rtc, RV3028_R_EE_COMMAND, RV3028_R_EE_COMMAND_NOP);
	rv3028_writeReg(rtc, RV3028_R_EE_COMMAND, RV3028_R_EE_COMMAND_WRITE);
	
	while(rv3028_readReg(rtc, RV3028_R_STATUS) & RV3028_R_STATUS_EEBUSY);
	rv3028_writeReg(rtc, RV3028_R_CONTROL_1, tempReg);
}