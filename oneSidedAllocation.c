#include <stdio.h>
#include <math.h>
#include "ciaAllocation.h"

int main(void)
{
	// creation of CIA data struct
	struct CIADataStruct CIAData;
	struct pvParameters parameters;

    // test code
    // float xCommand = 5.5;
    // unsigned int whichMag = 1;
    // // float parameters[] = {xCommand, whichMag};
    parameters.command = 5.5;
    parameters.whichMag = 1;
    oneSidedAllocation(&parameters,&CIAData);

    printf("posXlead1[0] = %i\n", (int) CIAData.posXlead1[0]);
    printf("posXlead1[1] = %i\n", (int) CIAData.posXlead1[1]);
    printf("posXlead1[2] = %i\n", (int) CIAData.posXlead1[2]);
    printf("posXlead1[3] = %i\n", (int) CIAData.posXlead1[3]);

    printf("posXlead2[0] = %i\n", (int) CIAData.posXlead2[0]);
    printf("posXlead2[1] = %i\n", (int) CIAData.posXlead2[1]);
    printf("posXlead2[2] = %i\n", (int) CIAData.posXlead2[2]);
    printf("posXlead2[3] = %i", (int) CIAData.posXlead2[3]);

    return(0);
}

// takes in a float array of two elements. The first element is a magnetic moment command 
// for a single magnetorquer. The second element takes on integer values between 1-5 to 
// indicate which magnetorquer to write to (1.0 indicates positive x face magnetorquer). 
void oneSidedAllocation(struct pvParameters *parameters, struct CIADataStruct *CIAData) {

    // convert command to duty cycle
    float absDutyCycle = 0.4; // example duty cycle

    // compute values for each lead
    char onLead[4];
    char lead1[4];
    char lead2[4];
    int i;

    // powered lead
    int delay = round(0);
    int onTime = round(absDutyCycle * multnum);
    onLead[0] = (char) (delay % divnum);
    onLead[1] = (char) (delay / divnum);

    int offStart = delay + onTime;
    onLead[2] = (char) (offStart % divnum);
    onLead[3] = (char) (offStart / divnum);

    // non-powered lead
    // offLead[0] = 0;
    // offLead[1] = 0;
    // offLead[2] = 0;
    // offLead[3] = 16; // 0001 0000, full off

    // assign powered and non-powered leads based off command direction

    if (parameters->command >= 0.0) {
    	for (i = 0; i < 4; ++i) {
    		lead1[i] = onLead[i];
    		lead2[i] = offLead[i];
    	}
        // lead1 = onLead;
        // lead2 = offLead;
    } else {
    	for (i = 0; i < 4; ++i) {
    		lead1[i] = offLead[i];
    		lead2[i] = onLead[i];
    	}
        // lead1 = offLead;
        // lead2 = onLead;
    }

    // switch case for assigning to correct magnetorquer
    switch (parameters->whichMag)
    {
        case 1:
            // CIAData->posXlead1[0] = lead1[0];
            // CIAData->posXlead1[1] = lead1[1];
            // CIAData->posXlead1[2] = lead1[2];
            // CIAData->posXlead1[3] = lead1[3];
            for (i = 0; i < 4; ++i)
            	CIAData->posXlead1[i] = lead1[i];
            

            // CIAData->posXlead2[0] = lead2[0];
            // CIAData->posXlead2[1] = lead2[1];
            // CIAData->posXlead2[2] = lead2[2];
            // CIAData->posXlead2[3] = lead2[3];
            for (i = 0; i < 4; ++i)
            	CIAData->posXlead2[i] = lead2[i];

            break;
        case 2:
            CIAData->negXlead1[0] = lead1[0];
            CIAData->negXlead1[1] = lead1[1];
            CIAData->negXlead1[2] = lead1[2];
            CIAData->negXlead1[3] = lead1[3];

            CIAData->negXlead2[0] = lead2[0];
            CIAData->negXlead2[1] = lead2[1];
            CIAData->negXlead2[2] = lead2[2];
            CIAData->negXlead2[3] = lead2[3];
            break;
        case 3:
            CIAData->posYlead1[0] = lead1[0];
            CIAData->posYlead1[1] = lead1[1];
            CIAData->posYlead1[2] = lead1[2];
            CIAData->posYlead1[3] = lead1[3];

            CIAData->posYlead2[0] = lead2[0];
            CIAData->posYlead2[1] = lead2[1];
            CIAData->posYlead2[2] = lead2[2];
            CIAData->posYlead2[3] = lead2[3];
            break;
        case 4:
            CIAData->negYlead1[0] = lead1[0];
            CIAData->negYlead1[1] = lead1[1];
            CIAData->negYlead1[2] = lead1[2];
            CIAData->negYlead1[3] = lead1[3];

            CIAData->negYlead2[0] = lead2[0];
            CIAData->negYlead2[1] = lead2[1];
            CIAData->negYlead2[2] = lead2[2];
            CIAData->negYlead2[3] = lead2[3];
            break;
        case 5:
            CIAData->posZlead1[0] = lead1[0];
            CIAData->posZlead1[1] = lead1[1];
            CIAData->posZlead1[2] = lead1[2];
            CIAData->posZlead1[3] = lead1[3];

            CIAData->posZlead2[0] = lead2[0];
            CIAData->posZlead2[1] = lead2[1];
            CIAData->posZlead2[2] = lead2[2];
            CIAData->posZlead2[3] = lead2[3];
            break;
    }
}
