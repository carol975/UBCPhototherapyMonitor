
#include "ADC.h"

/*
 * This file contains all neccesary functions for reading a voltage from pin 1.0
 * 
 */
 
 // Global Variables
int adc[10] = {0}; //Sets up an array of 10 integers and zero's the values
int avg_adc = 0;
 
 
// Returns a voltage 
double getVoltage()
{
		
		double voltage; 
		adc_Sam10();		// Function call for adc_samp
		// Add all the sampled data and divide by 10 to find average
		avg_adc = ((adc[0]+adc[1]+adc[2]+adc[3]+adc[4]+adc[5]+adc[6]+adc[7]+adc[8]+adc[9]) / 10);
	  	
	  	voltage = ADC_TO_Voltage(avg_adc);
	  	
}

// Convert ADC to voltage
double ADC_TO_Voltage(int avg_adc){
	double voltage = avg_adc * MAX_VOLTAGE / MAX_VOLTAGE_ADC;
	return voltage;
}


// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

// ADC set-up function
void adc_Setup()
{
	WDTCTL = WDTPW + WDTHOLD;			// Stop WDT
	  
	ADC10CTL1 = CONSEQ_2 + INCH_0;						// Repeat single channel, A0
	ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;	// Sample & Hold Time + ADC10 ON + Interrupt Enable
	ADC10DTC1 = 0x0A;									// 10 conversions
	ADC10AE0 |= 0x01;									// P1.0 ADC option select
}

// ADC sample conversion function
void adc_Sam10()
{
    ADC10CTL0 &= ~ENC;				// Disable Conversion
    while (ADC10CTL1 & BUSY);		// Wait if ADC10 busy
    ADC10SA = (int)adc;				// Transfers data to next array (DTC auto increments address)
    ADC10CTL0 |= ENC + ADC10SC;		// Enable Conversion and conversion start
    __bis_SR_register(CPUOFF + GIE);// Low Power Mode 0, ADC10_ISR
}
