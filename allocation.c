#include "ciaAllocation.h"

// see ciaAllocation.h for function description
void allocation(struct allocationParameters *parameters, struct CIADataStruct *CIAData) {

    double command = parameters->command;
    // convert command to duty cycle
    //float absDutyCycle = 0.4; // example duty cycle
    double absDutyCycle = command / maxMoment;

    if (absDutyCycle < 0) {
        absDutyCycle = -absDutyCycle;
    }

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

    // edge case for "all on" or "all off"
    if(onLead[3] >= 16) {
        onLead[1] = 16;
        onLead[3] = 0;
    } else if (onLead[2] == 0 && onLead[3] == 0) {
        onLead[3] = 16;
    }

    // assign powered and non-powered leads based off command direction
    if (command >= 0.0) {
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
