/*
 * rtc_rv3028.h
 *
 * Created: 03.02.2021 08:26:36
 *  Author: gfcwfzkm
 */ 


#ifndef RTC_RV3028_H_
#define RTC_RV3028_H_

#include <inttypes.h>

#define RV3028_R_SECOND			0x00
#define RV3028_R_MINUTES		0x01
#define RV3028_R_HOURS			0x02
#define RV3028_R_HOURS_AMPM		0x20 // Valid for HOURS_ALARM and HOURS_TS as well
#define RV3028_R_WEEKDAY		0x03
#define RV3028_R_DATE			0x04
#define RV3028_R_MONTH			0x05
#define RV3028_R_YEAR			0x06
#define RV3028_R_MINUTES_ALARM	0x07
#define RV3028_R_HOURS_ALARM	0x08
#define RV3028_R_WEEKDAY_DATE_ALARM		0x09
#define RV3828_R_ALARM_ENABLE_BIT		0x80	// Valid for MINUTES_ALARM, HOURS_ALARM & WEEKDAY_DATE_ALARM
#define RV3028_R_TIMER_VALUE_L	0x0A	// 12-bit value
#define RV3028_R_TIMER_VALUE_H	0x0B
#define RV3028_R_TIMER_STATUS_L	0x0C	// 12-bit value
#define RV3028_R_TIMER_STATUS_H	0x0D
#define RV3028_R_STATUS			0x0E
#define RV3028_R_STATUS_EEBUSY			0x80
#define RV3028_R_STATUS_CLKF			0x40
#define RV3028_R_STATUS_BSF				0x20
#define RV3028_R_STATUS_UF				0x10
#define RV3028_R_STATUS_TF				0x08
#define RV3028_R_STATUS_AF				0x04
#define RV3028_R_STATUS_EVF				0x02
#define RV3028_R_STATUS_PORF			0x01
#define RV3028_R_CONTROL_1		0x0F
#define RV3028_R_CONTROL_1_TRPT			0x80
#define RV3028_R_CONTROL_1_WADA			0x20
#define RV3028_R_CONTROL_1_USEL			0x10
#define RV3028_R_CONTROL_1_EERD			0x08
#define RV3028_R_CONTROL_1_TE			0x04
#define RV3028_R_CONTROL_1_TD1			0x02
#define RV3028_R_CONTROL_1_TD0			0x01
#define RV3028_R_CONTROL_1_TDgc			0x03
#define RV3028_R_CONTROL_2		0x10
#define RV3028_R_CONTROL_2_TSE			0x80
#define RV3028_R_CONTROL_2_CLKIE		0x40
#define RV3028_R_CONTROL_2_UIE			0x20
#define RV3028_R_CONTROL_2_TIE			0x10
#define RV3028_R_CONTROL_2_AIE			0x08
#define RV3028_R_CONTROL_2_EIE			0x04
#define RV3028_R_CONTROL_2_12_24		0x02
#define RV3028_R_CONTROL_2_RESET		0x01
#define RV3028_R_GP_BITS		0x11
#define RV3028_R_CLOCK_INT_MASK	0x12
#define RV3028_R_CLOCK_INT_MASK_CEIE	0x08
#define RV3028_R_CLOCK_INT_MASK_CAIE	0x04
#define RV3028_R_CLOCK_INT_MASK_CTIE	0x02
#define RV3028_R_CLOCK_INT_MASK_CUIE	0x01
#define RV3028_R_EVENT_CONTROL	0x13
#define RV3028_R_EVENT_CONTROL_EHL		0x40
#define RV3028_R_EVENT_CONTROL_ET1		0x20
#define RV3028_R_EVENT_CONTROL_ET0		0x10
#define RV3028_R_EVENT_CONTROL_TSR		0x04
#define RV3028_R_EVENT_CONTROL_TSOW		0x02
#define RV3028_R_EVENT_CONTROL_TSS		0x01
#define RV3028_R_COUNT_TS		0x14
#define RV3028_R_SECONDS_TS		0x15
#define RV3028_R_MINUTES_TS		0x16
#define RV3028_R_HOURS_TS		0x17
#define RV3028_R_DATE_TS		0x18
#define RV3028_R_MONTH_TS		0x19
#define RV3028_R_YEAR_TS		0x1A
#define RV3028_R_UNIXTIME_0		0x1B
#define RV3028_R_UNIXTIME_1		0x1C
#define RV3028_R_UNIXTIME_2		0x1D
#define RV3028_R_UNIXTIME_3		0x1E
#define RV3028_R_USER_RAM_1		0x1F
#define RV3028_R_USER_RAM_2		0x20
#define RV3028_R_PASSWORD_0		0x21
#define RV3028_R_PASSWORD_1		0x22
#define RV3028_R_PASSWORD_2		0x23
#define RV3028_R_PASSWORD_3		0x24
#define RV3028_R_EE_ADDRESS		0x25
#define RV3028_R_EE_DATA		0x26
#define RV3028_R_EE_COMMAND		0x27
#define RV3028_R_EE_COMMAND_NOP			0x00
#define RV3028_R_EE_COMMAND_UPDATE		0x11
#define RV3028_R_EE_COMMAND_REFRESH		0x12
#define RV3028_R_EE_COMMAND_WRITE		0x21
#define RV3028_R_EE_COMMAND_READ		0x22
#define RV3028_R_ID				0x28
#define RV3028_R_EEPROM_PW_EN	0x30
#define RV3028_R_EEPROM_PW_0	0x31
#define RV3028_R_EEPROM_PW_1	0x32
#define RV3028_R_EEPROM_PW_2	0x33
#define RV3028_R_EEPROM_PW_3	0x34
#define RV3028_R_EEPROM_CLKOUT	0x35
#define RV3028_R_EEPROM_CLKOUT_CLKOE	0x80
#define RV3028_R_EEPROM_CLKOUT_CLKSY	0x40
#define RV3028_R_EEPROM_CLKOUT_PORIE	0x08
#define RV3028_R_EEPROM_CLKOUT_FD2		0x04
#define RV3028_R_EEPROM_CLKOUT_FD1		0x02
#define RV3028_R_EEPROM_CLKOUT_FD0		0x01
#define RV3028_R_EEPROM_OFFSET	0x36
#define RV3028_R_EEPROM_BACKUP	0x37
#define RV3028_R_EEPROM_BACKUP_EEOFFST0	0x80
#define RV3028_R_EEPROM_BACKUP_BSIE		0x40
#define RV3028_R_EEPROM_BACKUP_TCE		0x20
#define RV3028_R_EEPROM_BACKUP_FEDE		0x10
#define RV3028_R_EEPROM_BACKUP_BSM1		0x08
#define RV3028_R_EEPROM_BACKUP_BSM0		0x04
#define RV3028_R_EEPROM_BACKUP_TCR1		0x02
#define RV3028_R_EEPROM_BACKUP_TCR0		0x01

/* Start and End Address of the RTC's user-accessible EEPROM */
#define RV3028_E_USER_EEPROM_START	0x00
#define RV3028_E_USER_EEPROM_END	0x2A

enum RV3028_error {
	RV3028_NO_ERROR	= 0,
	RV3028_IOERR	= 1
};

typedef struct {
	uint8_t HID:4;						// Hardware Identification number
	uint8_t VID:4;						// Version Identification number
	enum RV3028_error error;
	void *ioInterface;					// Pointer to the IO/Peripheral Interface library
	// Any return value by the IO interface functions have to return zero when successful or
	// non-zero when not successful.
	uint8_t (*startTransaction)(void*);	// Prepare the IO/Peripheral Interface for a transaction
	uint8_t (*sendBytes)(void*,			// Send data function pointer: InterfacePointer,
						uint8_t,		// Address of the PortExpander (8-Bit Address Format!),
						uint8_t*,		// Pointer to send buffer,
						uint16_t);		// Amount of bytes to send
	uint8_t (*getBytes)(void*,			// Get data function pointer:InterfacePointer,
						uint8_t,		// Address of the PortExpander (8-Bit Address Format!),
						uint8_t*,		// Pointer to receive buffer,
						uint16_t);		// Amount of bytes to receive
	uint8_t (*endTransaction)(void*);	// Finish the transaction / Release IO/Peripheral
}RV3028_t;

// Time basically
typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t weekday;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}RV3028_TIME_t;

void rv3028_initStruct(RV3028_t *rtc,
			void *ioInterface, uint8_t (*startTransaction)(void*),
			uint8_t (*sendBytes)(void*,uint8_t,uint8_t*,uint16_t),
			uint8_t (*getBytes)(void*,uint8_t,uint8_t*,uint16_t),
			uint8_t (*endTransaction)(void*));

enum RV3028_error rv3028_init(RV3028_t *rtc);

void rv3028_writeReg(RV3028_t *rtc, uint8_t regAddr, uint8_t regVal);

uint8_t rv3028_readReg(RV3028_t *rtc, uint8_t regAddr);

void rv3028_setTime(RV3028_t *rtc, RV3028_TIME_t *tme);

void rv3028_getTime(RV3028_t *rtc, RV3028_TIME_t *tme);

void rv3028_setUnixTime(RV3028_t *rtc, uint32_t unixTime);

uint32_t rv3028_getUnixTime(RV3028_t *rtc);

uint8_t rv3028_getStatus(RV3028_t *rtc);

void rv3028_updateConfigEEPROM(RV3028_t *rtc);

uint8_t rv3028_readUserEEPROM(RV3028_t *rtc, uint8_t addr);

void rv3028_writeUserEEPROM(RV3028_t *rtc, uint8_t addr, uint8_t val);

#endif /* RTC_RV3028_H_ */