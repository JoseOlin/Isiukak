#ifndef MICROCONTROLLER_HPP
#define MICROCONTROLLER_HPP

//#include <pins_arduino.h>

#define NUCLEO_F40 1
#define INFINEON_XMC4700 0

#if NUCLEO_F40
#include <Arduino.h>

#define pinD0 D0    // PA_3     Serial RX
#define pinD1 D1    // PA_2     Serial TX
#define pinD2 D2    // PA_10    smcSerial RX
#define pinD3 D3    // PB3      pinVDDVirtual
#define pinD4 D4    // PB5      pinOutput_PalancaBajar
#define pinD5 D5    // PB4      pinOutput_PalancaSubir
#define pinD6 D6
#define pinD7 D7    // PA8      pinGNDVirtual
#define pinD8 D8    // PA9      smcSerial TX
#define pinD9 D9    // PC7      pinBotonParoEmergencia
#define pinD10 D10  // PB6      pinFijarPosicionFreno
#define pinD11 D11  // PA7      pinBajarPalanca
#define pinD12 D12  // PA6      pinAGND
#define pinD13 D13  // PA5      pinAVDD

//#define pinD14 (Lo que esté conectado a A4)
//#define pinD15 (Lo que esté conectado a A5)

#define pinD16 PC2  //          pinModoCarretera
#define pinD17 PC3  //          pinSubirPalanca

#define pinD18 PC3 // CN7->37
#define pinD19 PC2 // CN7->35


#define pinA0 A0 //PA0
#define pinA1 A1 //PA1
#define pinA2 A2 //PA4
#define pinA3 A3 //PB0

//#define USART6_rxPin PA_12
//#define USART6_txPin PA_11


#endif


#if INFINEON_XMC4700
//#define ARDUINO_MAIN 1
/*
 *
 *
#define DP0 P2_15
#define DP1 P2_14
#define DP2 P1_0
#define DP3 P1_1
#define DP4 P1_8
#define DP5 P2_12
#define DP6 P2_11

#define DP7 7

#define DP8  P1_10
#define DP9  P1_11
#define DP10 P3_10
#define DP11 P3_8
#define DP12 P3_7
#define DP13 P3_9
//#define D14 //GND
//#define D15 // VA REF
//#define D16 P3.15 (A4)
//#define D17 P0.13 (A5)
#define DP18 P3_12
#define DP19 P0_12
*/

//#define smcRxPin P1_0  // RX pin D2, PA_10
//#define smcTxPin P1_10  // TX pin D8, PA_9
// From /home/user/.platformio/packages/framework-arduinoxmc/variants/XMC4700/config/XMC4700_Relax_Kit/pins_arduino.h
#define PBUTTON1 BUTTON1

// X1 Odd pins
#define PX1_1 36 //P3_4     PWM42-2 / PWM12
#define PX1_3 37 //P0_5     I2C_1 SDA  // SPI_4 MOSI
#define PX1_5 38 //P0_3     PWM80-2 / PWM10
#define PX1_7 39 //P0_1     PWM80-1 / PWM9
#define PX1_9 40 //P0_10
#define PX1_11 41 //P3_2
#define PX1_13 42 //P3_1
#define PX1_15 43 //P15_16  A6 / ADC Input
#define PX1_17 44 //P15_5   A7 / ADC Input
#define PX1_19 45 //P15_3   A8 / ADC Input
#define PX1_21 46 //P14_15  A9 / ADC Input
#define PX1_23 47 //P14_13  A10 / ADC Input
#define PX1_25 48 //P14_7   A11 / ADC Input
#define PX1_27 49 //P15_15  A12 / ADC Input
#define PX1_29 50 //P14_9   DAC0 // A13 / ADC Input
#define PX1_31 51 //P2_13
#define PX1_33 52 //P5_10
//#define PX1_35  //VDD5
//#define PX1_37  //GND
//#define PX1_39  //GND

// X1 even pins. Closer to Arduino shield Digital pins
#define PX1_2 69 //P0_11
#define PX1_4 68 //P0_6
#define PX1_6 67 //P0_4
#define PX1_8 66 //P0_2
#define PX1_10 65 //P0_0
#define PX1_12 64 //P0_9
#define PX1_14 63 //P3_0
#define PX1_16 62 //P15_7   A21 / ADC (INPUT ONLY)
#define PX1_18 61 //P15_4   A20 / ADC(INPUT ONLY)
#define PX1_20 60 //P15_2   A19 / ADC(INPUT ONLY)
#define PX1_22 59 //P14_14  A18 / ADC(INPUT ONLY)
#define PX1_24 58 //P14_12  A17 / ADC(INPUT ONLY)
#define PX1_26 57 //P14_6   A16 / ADC(INPUT ONLY)
#define PX1_28 56 //P15_14  A15 / ADC(INPUT ONLY)
#define PX1_30 55 //P14_8   DAC1 A14 / ADC(INPUT ONLY)
#define PX1_32 54 //P1_14
#define PX1_34 53 //P5_11
//#define PX1_36  //VDD3_3
//#define PX1_38  //GND
//#define PX1_40  //GND

// X2 odd pins. Closer to Arduino Shield Analog pins
#define PX2_1 70  // P3_13
#define PX2_3 71  // P3_11
#define PX2_5 72  // P0_14
#define PX2_7 73  // P3_14
#define PX2_9 74  // P0_7
#define PX2_11 75  // P1_2
#define PX2_13 76  // P6_1
#define PX2_15 77  // P6_3
#define PX2_17 78  // P6_5
#define PX2_19 79  // P1_15
#define PX2_21 80  // P5_1
#define PX2_23 81  // P5_3
#define PX2_25 82  // P5_5
#define PX2_27 83  // P5_7
//#define PX2_29   // HIB_IO_0
//#define PX2_31   // VDD5
//#define PX2_33   // CANH
//#define PX2_35   // CANL
//#define PX2_37   // GND
//#define PX2_39   // GND

#define PX2_2 97 // P3_12
#define PX2_4 96 // P0_12
#define PX2_6 95 // P0_15
#define PX2_8 94 // P3_3
#define PX2_10 93 // P0_8
#define PX2_12 92// P6_0
#define PX2_14 91// P6_2
#define PX2_16 90// P6_4
#define PX2_18 89// P6_6
#define PX2_20 88// P5_0
#define PX2_22 87// P5_2
#define PX2_24 86// P5_4
#define PX2_26 85// P5_6
#define PX2_28 84// P2_6
/*#define PX2_30 // HIB_IO_1
#define PX2_32 // RESET#
#define PX2_34 // VDD3.3
#define PX2_36 // VDD3.3
#define PX2_38 // GND
#define PX2_40 // GND
*/

#define pinA0 PX1_15    //Actualmente en PX2_11
#define pinA1 PX1_17    //Actualmente en PX2_9
#define pinA2 PX1_19    //Actualmente en PX2_7
#define pinA3 PX1_21    //Actualmente en PX2_5
//#define pinA4
//#define pinA5

#define pinD0 PX1_2
#define pinD1 PX1_4
#define pinD2 PX1_6
#define pinD3 PX1_8
#define pinD4 PX1_10
#define pinD5 PX1_12
#define pinD6 PX1_14
#define pinD7 PX1_16
#define pinD8 PX1_18
#define pinD9 PX1_20
#define pinD10 PX1_22
#define pinD11 PX1_24
#define pinD12 PX1_26
#define pinD13 PX1_28

//#define pinD14
//#define pinD15

#define pinD16 PX2_4
#define pinD17 PX2_2

#endif



int pinJoystickY = pinA0;
int pinJoystickX = pinA1; //
int pinActFreno  = pinA2; //
int pinActAcel   = pinA3; //
//int pinJoystickRed_Y = A4;
//int pinJoystickRed_X = A5;


int pinGNDVirtual = pinD7; ////TODO: Cambiar pinD7 en XMC es INPUT only
int pinVDDVirtual = pinD3; //
int pinAVDD = pinD13; ////!! Only INPUT en Infineon. TODO: Verificar si es necesario en el Infineon XMC
int pinAGND = pinD12; ////!! Only INPUT en Infineon. TODO: Verificar si es necesario en el Infineon XMC

int pinBotonParoEmergencia = pinD9; // TODO: ADC Considerar cambiar

int pinFijarPosicionFreno = pinD10; // TODO: ADC Considerar cambiar
int pinBajarPalanca = pinD11;      // TODO: ADC Considerar cambiar
int pinSubirPalanca = pinD17; //Se usaban pines analógicos, ahora se usan pines digitales Morpho
//int pinSubirPalanca = P3_12;
int pinModoCarretera = pinD16;
//int pinModoCarretera = P0_12;

int pinOutput_PalancaSubir = pinD5;
int pinOutput_PalancaBajar = pinD4;

#define smcRxPin pinD2 //  TODO: Check qué pines para UART1 en Infineon
#define smcTxPin pinD8 // TODO: Check qué pines para UART1 en Infineon


#endif // MICROCONTROLLER_HPP
