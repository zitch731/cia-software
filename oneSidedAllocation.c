#include <stdio.h>
#include <math.h>

static void oneSidedAllocation(void *pvParameters);

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

// creation of CIA data struct
struct CIADataStruct CIAData;

int main(void)
{
    // test code
    float xCommand = 5.5;
    float whichMag = 1.0;
    float parameters[] = {xCommand, whichMag};
    oneSidedAllocation(parameters);

    printf("posXlead1[0] = %i\n", (int) CIAData.posXlead1[0]);
    printf("posXlead1[1] = %i\n", (int) CIAData.posXlead1[1]);
    printf("posXlead1[2] = %i\n", (int) CIAData.posXlead1[2]);
    printf("posXlead1[3] = %i\n", (int) CIAData.posXlead1[3]);

    printf("posXlead2[0] = %i\n", (int) CIAData.posXlead2[0]);
    printf("posXlead2[1] = %i\n", (int) CIAData.posXlead2[1]);
    printf("posXlead2[2] = %i\n", (int) CIAData.posXlead2[2]);
    printf("posXlead2[3] = %i", (int) CIAData.posXlead2[3]);
}

// takes in a float array of two elements. The first element is a magnetic moment command 
// for a single magnetorquer. The second element takes on integer values between 1-5 to 
// indicate which magnetorquer to write to (1.0 indicates positive x face magnetorquer). 
static void oneSidedAllocation(void *pvParameters) {
    float* parameters = (float*) pvParameters;
    float command = *parameters;
    int whichMag = (int) *(parameters + 1);

    // convert command to duty cycle
    float absDutyCycle = 0.4; // example duty cycle

    // compute values for each lead
    char onLead[4];
    char offLead[4];

    // powered lead
    int delay = round(0);
    int onTime = round(absDutyCycle*4096);
    onLead[0] = (char) (delay % 256);
    onLead[1] = (char) (delay / 256);

    int offStart = delay + onTime;
    onLead[2] = (char) (offStart % 256);
    onLead[3] = (char) (offStart / 256);

    // non-powered lead
    offLead[0] = 0;
    offLead[1] = 0;
    offLead[2] = 0;
    offLead[3] = 16; // 0001 0000, full off

    // assign powered and non-powered leads based off command direction
    char* lead1;
    char* lead2;
    if (command >= 0.0) {
        lead1 = onLead;
        lead2 = offLead;
    } else {
        lead1 = offLead;
        lead2 = onLead;
    }

    // switch case for assigning to correct magnetorquer
    switch (whichMag)
    {
        case 1:
            CIAData.posXlead1[0] = lead1[0];
            CIAData.posXlead1[1] = lead1[1];
            CIAData.posXlead1[2] = lead1[2];
            CIAData.posXlead1[3] = lead1[3];

            CIAData.posXlead2[0] = lead2[0];
            CIAData.posXlead2[1] = lead2[1];
            CIAData.posXlead2[2] = lead2[2];
            CIAData.posXlead2[3] = lead2[3];
            break;
        case 2:
            CIAData.negXlead1[0] = lead1[0];
            CIAData.negXlead1[1] = lead1[1];
            CIAData.negXlead1[2] = lead1[2];
            CIAData.negXlead1[3] = lead1[3];

            CIAData.negXlead2[0] = lead2[0];
            CIAData.negXlead2[1] = lead2[1];
            CIAData.negXlead2[2] = lead2[2];
            CIAData.negXlead2[3] = lead2[3];
            break;
        case 3:
            CIAData.posYlead1[0] = lead1[0];
            CIAData.posYlead1[1] = lead1[1];
            CIAData.posYlead1[2] = lead1[2];
            CIAData.posYlead1[3] = lead1[3];

            CIAData.posYlead2[0] = lead2[0];
            CIAData.posYlead2[1] = lead2[1];
            CIAData.posYlead2[2] = lead2[2];
            CIAData.posYlead2[3] = lead2[3];
            break;
        case 4:
            CIAData.negYlead1[0] = lead1[0];
            CIAData.negYlead1[1] = lead1[1];
            CIAData.negYlead1[2] = lead1[2];
            CIAData.negYlead1[3] = lead1[3];

            CIAData.negYlead2[0] = lead2[0];
            CIAData.negYlead2[1] = lead2[1];
            CIAData.negYlead2[2] = lead2[2];
            CIAData.negYlead2[3] = lead2[3];
            break;
        case 5:
            CIAData.posZlead1[0] = lead1[0];
            CIAData.posZlead1[1] = lead1[1];
            CIAData.posZlead1[2] = lead1[2];
            CIAData.posZlead1[3] = lead1[3];

            CIAData.posZlead2[0] = lead2[0];
            CIAData.posZlead2[1] = lead2[1];
            CIAData.posZlead2[2] = lead2[2];
            CIAData.posZlead2[3] = lead2[3];
            break;
    }
}
