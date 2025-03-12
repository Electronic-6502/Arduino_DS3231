/**
 * @file    ds3231.h
 * @author  Electronic-6502 (HS6502)  Link : https://github.com/Electronic-6502
 * @version V1.0
 * @date    5-Mar-2025
 * @brief   DS3231 RTC Module Library Header File for Arduino
 */
#ifndef __DS3231_H__
#define __DS3231_H__

#include <Arduino.h>
#include <Wire.h>

#define _DS3231_Bus_Address      0x68

class _DS3231 {
    public:
        // Initialize DS3231 Interface
        void begin (void);

        // Set DS3231 Time : Hour, Minute and Second
        void Set_Time (uint8_t Hour, uint8_t Minute, uint8_t Second);

        // Set Only DS3231 Hour
        void Set_Hour (uint8_t Hour);

        // Set Only DS3231 Minute
        void Set_Minute (uint8_t Minute);

        // Set Only DS3231 Second
        void Set_Second (uint8_t Second);

        // Read Time from DS3231
        void Get_Time (uint8_t *Hour, uint8_t *Minute, uint8_t *Second);    


        // Set Year, Month and Day of Month
        void Set_Date (uint8_t Year, uint8_t Month, uint8_t Day_of_Month);

        // Set Only Day of Month from 1 to 31
        void Set_Day (uint8_t Day_of_Month);    

        // Set Only Month
        void Set_Month (uint8_t Month);

        // Set Only Year from 0 to 99 or 2000 to 2099
        void Set_Year (uint16_t Year);

        // Read Year, Month and Day of Month
        void Get_Date (uint16_t *Year, uint8_t *Month, uint8_t *Day_of_Month);

    private:
        // Convert Decimal Number to BCD Number
        uint8_t Decimal_to_BCD (uint8_t Decimal);

        // Convert BCD Number to Decimal Number
        uint8_t BCD_to_Decimal (uint8_t BCD);

        // Write Data to DS3231 Internal Registers
        void    Write (uint8_t Address, uint8_t Data);

        // Read Data from DS3231 Internal Registers
        uint8_t Read (uint8_t Address); 
};

extern _DS3231 DS3231;

#endif