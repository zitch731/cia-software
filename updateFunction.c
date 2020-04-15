#include <stdio.h>

// function definitions
static int updateCIA(void *pvParameters);

// example data struct definition
struct CIADataStruct
{
    /** definitions of the 4 bytes in each lead
    register	Bit	    Access	Value 	    Description
    LEDX_ON_L	[7:0]	R/W	    0000 0000*	LEDn_ON count for LEDX, 8 LSBs
    LEDX_ON_H	[7:5]	R	    000*	    non-writable
                [4]	    R/W	       0*	    LEDX full ON
                [3:0]	R/W	         0000*	LEDn_ON count for LEDX, 4 MSBs
    LEDX_OFF_L	[7:0]	R/W	    0000 0000*	LEDn_OFF count for LEDX, 8 LSBs
    LEDX_OFF_H	[7:5]	R	    000*	    non-writable
                [4]	    R/W	       1*	    LEDX full OFF
                [3:0]	R/W	         0000*	LEDn_OFF count for LEDX, 4 MSBs
    * - default value
    see PCA9685 data sheet for more info
    */

    // positive x-face commands
    char posXlead1[4];
    char posXlead2[4];

    // negative x-face commands
    char negXlead1[4];
    char negXlead2[4];

    // positive y-face commands
    char posYlead1[4];
    char posYlead2[4];

    // negative y-face commands
    char negYlead1[4];
    char negYlead2[4];

    // positive z-face commands
    char posZlead1[4];
    char posZlead2[4];
};

// creation of CIA data struct
struct CIADataStruct CIAData;

// main function
int main(void)
{

}

static int updateCIA(void *pvParameters) {

}
