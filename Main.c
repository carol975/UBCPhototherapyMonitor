#include "ADC.h"

/*
 * Software for controlling the Phototherapy Monitor
 * Date: April 2nd, 2016
 * Author: UBC BEST Phototherapy Team
 */
 
double voltage = 0;
void main()
{
	  adc_Setup();
	  while(1)
	  {	
	  	// Reads the voltage from PIN 1.0
		 voltage = getVoltage();
	  }
}

