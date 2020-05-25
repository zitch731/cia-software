#include <stdbool.h>


#ifndef CIA_ALLOCATION_H
#define CIA_ALLOCATION_H

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
    see PCA9685 data sheet for more info
    */

    // positive x-face commands
    char posXlead1[4]; //!< 4 commands for the positive x face magnetorquer, lead 1
    char posXlead2[4]; //!< 4 commands for the positive x face magnetorquer, lead 2

    // negative x-face commands
    char negXlead1[4]; //!< 4 commands for the negative x face magnetorquer, lead 1
    char negXlead2[4]; //!< 4 commands for the negative x face magnetorquer, lead 2

    // positive y-face commands
    char posYlead1[4]; //!< 4 commands for the positive y face magnetorquer, lead 1
    char posYlead2[4]; //!< 4 commands for the positive y face magnetorquer, lead 2

    // negative y-face commands
    char negYlead1[4]; //!< 4 commands for the negative y face magnetorquer, lead 1
    char negYlead2[4]; //!< 4 commands for the negative y face magnetorquer, lead 2

    // positive z-face commands
    char posZlead1[4]; //!< 4 commands for the positive z face magnetorquer, lead 1
    char posZlead2[4]; //!< 4 commands for the positive z face magnetorquer, lead 2

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

const char offLead[4] = {0,0,0,16};
const unsigned int separateBytes = 256;
const unsigned int cycleLength = 4096;

// function declarations
void setMags(struct setMagsParameters *parameters,
             struct CIADataStruct *CIAData);
void allocation(struct allocationParameters *parameters,
						struct CIADataStruct *CIAData);

#endif // CIA_ALLOCATION_H
