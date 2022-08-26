#ifndef LECTURATEMPERATURA_HPP
#define LECTURATEMPERATURA_HPP

#include "Config.hpp"
#include "Microcontroller.hpp"

double Microcontroller_TempC;
double Thermistor1_TempC;
double Thermistor2_TempC;

#if NUCLEO_F40
#include "stm32yyxx_ll_adc.h"

/* Values available in datasheet */
#define CALX_TEMP 25
#if defined(STM32F1xx)
#define V25       1430
#define AVG_SLOPE 4300
#define VREFINT   1200
#elif defined(STM32F2xx) || defined(STM32F4xx)
#define V25       760
#define AVG_SLOPE 2500
#define VREFINT   1210
#endif
/* Analog read resolution */
#define LL_ADC_RESOLUTION LL_ADC_RESOLUTION_12B
//#define ADC_RANGE 4096
#define ADC_RANGE 1024


float readTemp_Micro()
{
    //Based on RM0368 Reference Manual STM3F401xB
    //Temperature (in °C) = {(V_SENSE – V_25 ) / Avg_Slope} + 25
    // Where:
    // – V_25 = V_SENSE value for 25° C
    // – Avg_Slope = average slope of the temperature vs. V SENSE curve (given in mV/°C
    // or μV/°C)
    //Refer to the datasheet’s electrical characteristics section for the actual values of V 25
    // and Avg_Slope.
//#define TEMP30_CAL_ADDR *((uint16_t*) ((uint32_t) 0x1FFF7A2C)) //TS ADC raw data acquired at temperature of 30 °C, V DDA = 3.3 V
//#define TEMP110_CAL_ADDR *((uint16_t*) ((uint32_t) 0x1FFF7A2E)) //TS ADC raw data acquired at temperature of 110 °C, V DDA = 3.3 V
//#define AVG_SLOPE ((float)(TS_CAL1 - TS_CAL2))

    float V_25 = 0.75; // V
    //float V_25 = 1.4; // V

    float Avg_Slope = 2.5; // mV/°C
    //float Avg_Slope = AVG_SLOPE;


    float V_Sense = analogRead(pinBoardTemperature);

    double tempC = V_Sense;
    ///double tempC = ((V_Sense - V_25) / Avg_Slope) + 25.0;
    //double tempC =
    //        (   ((110. - 30.)*(V_Sense - TEMP30_CAL_ADDR ))
    //            / (TEMP110_CAL_ADDR - TEMP30_CAL_ADDR)   )  + 30;


    Microcontroller_TempC = tempC;

    return tempC;
}


static int32_t readVref()
{
#ifdef __LL_ADC_CALC_VREFANALOG_VOLTAGE
#ifdef STM32U5xx
  return (__LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC1, analogRead(AVREF), LL_ADC_RESOLUTION));
#else
  return (__LL_ADC_CALC_VREFANALOG_VOLTAGE(analogRead(AVREF), LL_ADC_RESOLUTION));
#endif
#else
  return (VREFINT * ADC_RANGE / analogRead(AVREF)); // ADC sample to mV
#endif
}

#ifdef ATEMP
    static int32_t readTempSensor(int32_t VRef)
    {
        #ifdef __LL_ADC_CALC_TEMPERATURE
            #ifdef STM32U5xx
              return (__LL_ADC_CALC_TEMPERATURE(ADC1, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
            #else
              return (__LL_ADC_CALC_TEMPERATURE(VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
            #endif
        #elif defined(__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS)
              return (__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(AVG_SLOPE, V25, CALX_TEMP, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
            #else
              return 0;
        #endif
    }
#endif

static int32_t readVoltage(int32_t VRef, uint32_t pin)
{
#ifdef STM32U5xx
  return (__LL_ADC_CALC_DATA_TO_VOLTAGE(ADC1, VRef, analogRead(pin), LL_ADC_RESOLUTION));
#else
  return (__LL_ADC_CALC_DATA_TO_VOLTAGE(VRef, analogRead(pin), LL_ADC_RESOLUTION));
#endif
}



#endif

void displayTemperatureInfo()
{
    Serial.print(", Tm_uC: "); Serial.print(Microcontroller_TempC);
    //Serial.print(", Tm_Th1: "); Serial.print(Thermistor1_TempC);
    //Serial.print(", Tm_Th2: "); Serial.print(Thermistor2_TempC);
}


double thermistorConvert(int RawADC)
{
    double Temp;
    double TempLog;

    /// Steinhart–Hart equation implementation
    TempLog = log(( (10240000 / RawADC) - 10000) );
    Temp = 1 /
            (0.001129148 + (0.000234125 + (0.0000000876741 * TempLog * TempLog ))* TempLog );

    Temp = Temp - 273.15;              // Convert Kelvin to Celsius
    //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit - comment out this line if you need Celsius
    return Temp;
}

void readTemp_Thermistors()
{
    int Therm1_V = analogRead(pinThermistor1);
    Thermistor1_TempC = thermistorConvert(Therm1_V);

    int Therm2_V = analogRead(pinThermistor2);
    Thermistor2_TempC = thermistorConvert(Therm2_V);

}

void testReadTemp()
{
    int32_t VRef = readVref();
    //Serial.printf("VRef(mv)= %i", VRef);
    #ifdef ATEMP
      Serial.printf(", Tm_uC: %i", readTempSensor(VRef));
    #endif
    #ifdef AVBAT
      //Serial.printf("\tVbat(mv)= %i", readVoltage(VRef, AVBAT));
    #endif
      //Serial.printf("\tA0(mv)= %i\n", readVoltage(VRef, A0));
      delay(200);
}

void readTemperatures()
{
    //readTemp_Micro();
    testReadTemp();
    //readTemp_Thermistors();
}
#endif // LECTURATEMPERATURA_HPP
