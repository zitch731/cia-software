#ifndef CIA_ALLOCATION_H
#define CIA_ALLOCATION_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

// CIA data struct definition
struct CIADataStruct
{
    /** definitions of the 4 bytes in each lead
    register	Bit	    Access	Value 	    Description
    LEDX_ON_L	[7:0]	R/W	    0000 0000*	LEDX_ON count for LEDX, 8 LSBs
    LEDX_ON_H	[7:5]	R	    000*	    non-writable
                [4]	    R/W	       0*	    LEDX full ON
                [3:0]	R/W	         0000*	LEDn_ON count for LEDX, 4 MSBs
    LEDX_OFF_L	[7:0]	R/W	    0000 0000*	LEDn_OFF count for LEDX, 8 LSBs
    LEDX_OFF_H	[7:5]	R	    000*	    non-writable
                [4]	    R/W	       1*	    LEDX full OFF
                [3:0]	R/W	         0000*	LEDn_OFF count for LEDX, 4 MSBs
    * = default value

    The LEDn_ON_H output control bit 4, when set to logic 1, causes the output to be always
    ON. The turning ON of the LED is delayed by the amount in the LEDn_ON registers.
    LEDn_OFF[11:0] are ignored. When this bit = 0, then the LEDn_ON and LEDn_OFF
    registers are used according to their normal definition.

    The LEDn_OFF_H output control bit 4, when set to logic 1, causes the output to be
    always OFF. In this case the values in the LEDn_ON registers are ignored.

    Remark: When all LED outputs are configured as ‘always OFF’, the prescale counter and
    all associated PWM cycle timing logic are disabled. If LEDn_ON_H[4] and
    LEDn_OFF_H[4] are set at the same time, the LEDn_OFF_H[4] function takes
    precedence.

    see PCA9685 data sheet for more info
    */

    // positive x-face commands
    unsigned char posXlead1[4]; //!< 4 commands for the positive x face magnetorquer, lead 1
    unsigned char posXlead2[4]; //!< 4 commands for the positive x face magnetorquer, lead 2

    // negative x-face commands
    unsigned char negXlead1[4]; //!< 4 commands for the negative x face magnetorquer, lead 1
    unsigned char negXlead2[4]; //!< 4 commands for the negative x face magnetorquer, lead 2

    // positive y-face commands
    unsigned char posYlead1[4]; //!< 4 commands for the positive y face magnetorquer, lead 1
    unsigned char posYlead2[4]; //!< 4 commands for the positive y face magnetorquer, lead 2

    // negative y-face commands
    unsigned char negYlead1[4]; //!< 4 commands for the negative y face magnetorquer, lead 1
    unsigned char negYlead2[4]; //!< 4 commands for the negative y face magnetorquer, lead 2

    // positive z-face commands
    unsigned char posZlead1[4]; //!< 4 commands for the positive z face magnetorquer, lead 1
    unsigned char posZlead2[4]; //!< 4 commands for the positive z face magnetorquer, lead 2

    // TODO: add check variables for each magnetorquer
};

struct allocationParameters {
	double command;
	unsigned int whichMag;
};

struct setMagsParameters {
    double commands[3];
    bool magStatus[5];
};

static const char offLead[4] = {0,0,0,16};
static const double maxMoment = 0.0515; // 0.0515 Am2 is max dipole moment
                                 // from SOC-i PDR
static const unsigned int separateBytes = 256;
static const unsigned int cycleLength = 4096;

// function declarations
void setMags(struct setMagsParameters *parameters,
             struct CIADataStruct *CIAData);
void allocation(struct allocationParameters *parameters,
						struct CIADataStruct *CIAData);

#endif // CIA_ALLOCATION_H
