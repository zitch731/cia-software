#include "ciaAllocation.h"

void setMags(struct setMagsParameters *parameters,
             struct CIADataStruct *CIAData) {

    unsigned int i,j, firstMag;
    double command;
    bool posMagWorking, negMagWorking;
    struct allocationParameters posParam;
    struct allocationParameters negParam;
    unsigned char *posLead1[4], *posLead2[4], *negLead1[4], *negLead2[4];
    unsigned char dummyLead[4]; // dummy lead (for -z face that doesn't exist)

    // loops through x mags, y mags, and z mag
    for (i = 0; i < 3; ++i) {
        switch (i) {
            case 0: // x mags
                for (j = 0; j < 4; ++j) {
                    posLead1[j] = &CIAData->posXlead1[j];
                    posLead2[j] = &CIAData->posXlead2[j];
                    negLead1[j] = &CIAData->negXlead1[j];
                    negLead2[j] = &CIAData->negXlead2[j];
                }
                break;
            case 1: // y mags
                for (j = 0; j < 4; ++j) {
                    posLead1[j] = &CIAData->posYlead1[j];
                    posLead2[j] = &CIAData->posYlead2[j];
                    negLead1[j] = &CIAData->negYlead1[j];
                    negLead2[j] = &CIAData->negYlead2[j];
                }
                break;
            case 2: // z mags
                for (j = 0; j < 4; ++j) {
                    posLead1[j] = &CIAData->posZlead1[j];
                    posLead2[j] = &CIAData->posZlead2[j];
                    negLead1[j] = &dummyLead[j];
                    negLead2[j] = &dummyLead[j];
                }
                break;
        }

        firstMag = 2*i + 1;
        command = parameters->commands[i];
        posMagWorking = parameters->magStatus[2*i];
        negMagWorking = parameters->magStatus[2*i+1];

        // if both mags are working
        if (posMagWorking && negMagWorking) {
            posParam.command = command/2;
            negParam.command = -command/2;
            posParam.whichMag = firstMag;
            negParam.whichMag = firstMag + 1;
            allocation(&posParam, CIAData);
            allocation(&negParam, CIAData);

        // if positive mag works
        } else if (posMagWorking) {
            posParam.command = command;
            posParam.whichMag = firstMag;
            allocation(&posParam, CIAData);
            for (i = 0; i < 4; ++i) {
                *negLead1[i] = offLead[i];
                *negLead2[i] = offLead[i];
            }

        // if negative mag works
        } else if (negMagWorking) {
            negParam.command = -command;
            negParam.whichMag = firstMag + 1;
            allocation(&negParam, CIAData);
            for (i = 0; i < 4; ++i) {
                *posLead1[i] = offLead[i];
                *posLead2[i] = offLead[i];
            }

        // if neither mag works
        } else {
            for (i = 0; i < 4; ++i) {
                *posLead1[i] = offLead[i];
                *posLead2[i] = offLead[i];
                *negLead1[i] = offLead[i];
                *negLead2[i] = offLead[i];
            }
        }
    }
}
