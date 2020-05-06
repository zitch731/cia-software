#include <stdio.h>
#include <math.h>
#include "ciaAllocation.h"

int main(void)
{
    // creation of CIA data struct
    struct CIADataStruct CIAData;
    struct pvParameters parameters;

    // test code
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
void oneSidedAllocation(struct allocationParameters *parameters, struct CIADataStruct *CIAData) {

    // convert command to duty cycle
    float absDutyCycle = 0.4; // example duty cycle

    // compute values for each lead
    char onLead[4];
    char lead1[4];
    char lead2[4];
    int i;

    // powered lead
    int delay = round(0);
    int onTime = round(absDutyCycle * cycleLength);
    onLead[0] = (char) (delay % separateBytes);
    onLead[1] = (char) (delay / separateBytes);

    int offStart = delay + onTime;
    onLead[2] = (char) (offStart % separateBytes);
    onLead[3] = (char) (offStart / separateBytes);

    // assign powered and non-powered leads based off command direction
    if (parameters->command >= 0.0) {
    	for (i = 0; i < 4; ++i) {
    		lead1[i] = onLead[i];
    		lead2[i] = offLead[i];
    	}
    } else {
    	for (i = 0; i < 4; ++i) {
    		lead1[i] = offLead[i];
    		lead2[i] = onLead[i];
    	}
    }

    // switch case for assigning to correct magnetorquer
    switch (parameters->whichMag)
    {
        case 1:
            for (i = 0; i < 4; ++i)
            	CIAData->posXlead1[i] = lead1[i];
            
            for (i = 0; i < 4; ++i)
            	CIAData->posXlead2[i] = lead2[i];
            break;
        case 2:
	    for (i = 0; i < 4; ++i)
            	CIAData->negXlead1[i] = lead1[i];
            
            for (i = 0; i < 4; ++i)
            	CIAData->negXlead2[i] = lead2[i];
            break;
        case 3:
            for (i = 0; i < 4; ++i)
            	CIAData->posYlead1[i] = lead1[i];
            
            for (i = 0; i < 4; ++i)
            	CIAData->posYlead2[i] = lead2[i];
            break;
        case 4:
            for (i = 0; i < 4; ++i)
            	CIAData->negYlead1[i] = lead1[i];
            
            for (i = 0; i < 4; ++i)
            	CIAData->negYlead2[i] = lead2[i];    
            break;
        case 5:
            for (i = 0; i < 4; ++i)
            	CIAData->posZlead1[i] = lead1[i];
            
            for (i = 0; i < 4; ++i)
            	CIAData->posZlead2[i] = lead2[i];
            break;
    }
}
