/**
 * @file    c
 * @author  Electronic-6502 (HS6502)  Link : https://github.com/Electronic-6502
 * @version V1.0
 * @date    5-Mar-2025
 * @brief   DS3231 RTC Module Library for Arduino
 */

#include "DS3231.h"


void _DS3231::begin (void){
    Wire.begin();
}

void _DS3231::Set_Time (uint8_t Hour, uint8_t Minute, uint8_t Second){

    Set_Second (Second);
    Set_Minute (Minute);
    Set_Second (Second);
}

void _DS3231::Set_Hour (uint8_t Hour){
    if (Hour < 24){
        Write (0x02, Hour);
    }
    else {
        Write (0x02, 0);                        // if Hour New Value out of Range, set to 0
    }      
}

void _DS3231::Set_Minute (uint8_t Minute){
    if (Minute < 60){
        Write (0x01, Minute);
    }
    else{
        Write (0x01, 0);                        // if Minute New Value out of Range, set to 0
    }
}

void _DS3231::Set_Second (uint8_t Second){
    if (Second < 60){
        Write (0x00, Second);
    }
    else{
        Write (0x00, 0);                        // if Second New Value out of Range, set to 0
    }
}

void _DS3231::Get_Time (uint8_t *Hour, uint8_t *Minute, uint8_t *Second){

    *Second = Read (0x00);
    *Minute = Read (0x01);
    *Hour   = Read (0x02);
}



void _DS3231::Set_Date (uint8_t Year, uint8_t Month, uint8_t Day_of_Month){
    Set_Day (Day_of_Month);
    Set_Month (Month);
    Set_Year (Year);
}

void _DS3231::Set_Day (uint8_t Day_of_Month){
    if (Day_of_Month < 32 && Day_of_Month != 0){
        Write (0x04, Day_of_Month);
    }
    else{
        Write (0x04, 1);                        // if Day New Value out of Range, set to 1
    }
}

void _DS3231::Set_Month (uint8_t Month){
    if (Month < 13 && Month != 0){
        Write (0x05, Month);
    }
    else{
        Write (0x05, 1);                        // if Month New Value out of Range, set to 1
    }
}

void _DS3231::Set_Year (uint16_t Year){
    if (Year >= 2000 && Year < 2100){
        Year -= 2000;
        Write (0x06, Year);
    }
    else if (Year < 100){
        Write (0x06, Year);
    }
    else{
        Write (0x06, 0);                        // if Year New Value out of Range, Set to 0
    }
}

void _DS3231::Get_Date (uint16_t *Year, uint8_t *Month, uint8_t *Day_of_Month){
    *Day_of_Month = Read (0x04);
    *Month        = (Read (0x05)) & 0x7F;       // Ignore Century bit
    *Year         = Read (0x06);
}

/*============================================================*/

/*==================== Internal Functions ====================*/

uint8_t _DS3231::Decimal_to_BCD (uint8_t Decimal){
    return ( ((Decimal / 10) << 4) | (Decimal % 10));
}

uint8_t _DS3231::BCD_to_Decimal (uint8_t BCD){
//    BCD &= 0x7F;
    return ( ((BCD >> 4) * 10) + (BCD & 0x0F));
}


void _DS3231::Write (uint8_t Address, uint8_t Data){

    Wire.beginTransmission (_DS3231_Bus_Address);
    Wire.write (Address);
    Wire.write (Decimal_to_BCD (Data));
    Wire.endTransmission ();
}

uint8_t _DS3231::Read (uint8_t Address){

    Wire.beginTransmission (_DS3231_Bus_Address);
    Wire.write (Address);
    Wire.endTransmission ();
    Wire.requestFrom (_DS3231_Bus_Address, 1);
    return BCD_to_Decimal(Wire.read());
}

_DS3231 DS3231;                     // Create Object from _DS3231 Class