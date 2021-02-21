# RTC-RV3028
Basic library for the RV-3028-C7 RTC by Micro Crystal AG ( https://www.microcrystal.com/en/products/real-time-clock-rtc-modules/rv-3028-c7/ )

Example Code to set the RTC's clockout pin to 1Hz and enables the Backup Battery (no trickle charge)
```c
int main(void)
{
  RV3028_t rtcClock;
  RV3028_TIME_t rtcTime;
  // uC and I2C init
  if (rv3028_init(rtcClk, &twiMaster, &TWI_InterfacePrepare,
     &TWI_InterfaceSendBytes, &TWI_InterfaceGetBytes, &TWI_InterfaceFinish))
  {
    // something went wrong!
  }
  else
  {
    // Write into the EEPROM by checking if the UserRam content is invalid
    if (rv3028_readReg(rtcClk, RV3028_R_USER_RAM_1) != ((BUILD_MONTH << 4) | (BUILD_YEAR & 0x0F)))
    {
	rv3028_writeReg(rtcClk, RV3028_R_CONTROL_1, RV3028_R_CONTROL_1_EERD);
	rv3028_writeReg(rtcClk, RV3028_R_EEPROM_CLKOUT,
	RV3028_R_EEPROM_CLKOUT_CLKOE | RV3028_R_EEPROM_CLKOUT_CLKSY |
	RV3028_R_EEPROM_CLKOUT_FD2 | RV3028_R_EEPROM_CLKOUT_FD0);
	tempVal = rv3028_readReg(rtcClk, RV3028_R_EEPROM_BACKUP);
	tempVal &= RV3028_R_EEPROM_BACKUP_EEOFFST0;
	tempVal |= RV3028_R_EEPROM_BACKUP_FEDE | RV3028_R_EEPROM_BACKUP_BSM1 |
	RV3028_R_EEPROM_BACKUP_BSM0;
	rv3028_writeReg(rtcClk, RV3028_R_EEPROM_BACKUP, tempVal);
	rv3028_updateConfigEEPROM(rtcClk);
	rv3028_writeReg(rtcClk, RV3028_R_USER_RAM_1,(uint8_t)((BUILD_MONTH << 4) | (BUILD_YEAR & 0x0F)));
	bc_log_f(BC_INFO, "Echtzeituhr EEPROM aktualisiert!");
     }
  rv3028_getTime(rtcClk, &rtcTime);
  }
  
  // Rest of the code
}
```
