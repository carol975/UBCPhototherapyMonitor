#ifndef ADC_H_
#define ADC_H_

#include "msp430g2553.h"


#define MAX_VOLTAGE 3.3
#define MAX_VOLTAGE_ADC 934


// Set up the adc
void adc_Setup();

// ADC sample conversion function
void adc_Sam10();

__interrupt void ADC10_ISR(void);

// Convert ADC to voltage
double ADC_TO_Voltage(int avg_adc);

// Returns voltage read from the GPIO 1.0
double getVoltage();

#endif /*ADC_H_*/
