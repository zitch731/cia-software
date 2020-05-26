#include <stdio.h>
#include <stdbool.h>
#include "ciaAllocation.h"

void setMags(struct setMagsParameters *parameters,
             struct CIADataStruct *CIAData) {

    // assign variables
    double* commands = (*parameters).commands;
    bool* magStatus  = (*parameters).magStatus;
    *(magStatus + 5) = false;
    double cmdArray[] = {*commands, *(commands + 1), *(commands + 2)};

    // printf("magStatus[1] = %s\n", *(magStatus+1) ? "true" : "false");

    double command;
    int firstMag;
    bool posMagWorking;
    bool negMagWorking;

    for (int i = 0; i < 3; ++i) {
        char* posLead1[4];
        char* posLead2[4];
        char* negLead1[4];
        char* negLead2[4];

        // dummy lead (for -z face that doesn't exist)
        char dummyLead[4];

        switch (i)
        {
            case 0:
                for (int j = 0; j < 4; ++j) {
                    posLead1[j] = &(*CIAData).posXlead1[j];
                    posLead2[j] = &(*CIAData).posXlead2[j];
                    negLead1[j] = &(*CIAData).negXlead1[j];
                    negLead2[j] = &(*CIAData).negXlead2[j];
                }
                break;
            case 1:
                for (int j = 0; j < 4; ++j) {
                    posLead1[j] = &(*CIAData).posYlead1[j];
                    posLead2[j] = &(*CIAData).posYlead2[j];
                    negLead1[j] = &(*CIAData).negYlead1[j];
                    negLead2[j] = &(*CIAData).negYlead2[j];
                }
                break;
            case 2:
                for (int j = 0; j < 4; ++j) {
                    posLead1[j] = &(*CIAData).posZlead1[j];
                    posLead2[j] = &(*CIAData).posZlead2[j];
                    negLead1[j] = &dummyLead[j];
                    negLead2[j] = &dummyLead[j];
                }
                break;
        }

        command = cmdArray[i];
        firstMag = 2*i + 1;
        posMagWorking = *(magStatus + 2*i);
        negMagWorking = *(magStatus + 2*i + 1);

        // if both mags are working
        if (posMagWorking && negMagWorking) {
            struct allocationParameters posParam;
            struct allocationParameters negParam;
            posParam.command = command/2;
            negParam.command = -command/2;
            posParam.whichMag = firstMag;
            negParam.whichMag = firstMag + 1;
            allocation(&posParam, CIAData);
            allocation(&negParam, CIAData);

        // if positive mag works
        } else if (posMagWorking) {
            struct allocationParameters posParam;
            posParam.command = command;
            posParam.whichMag = firstMag;
            allocation(&posParam, CIAData);
            for (int i = 0; i < 4; ++i) {
                *negLead1[i] = offLead[i];
                *negLead2[i] = offLead[i];
            }

        // if negative mag works
        } else if (negMagWorking) {
            struct allocationParameters negParam;
            negParam.command = -command;
            negParam.whichMag = firstMag + 1;
            allocation(&negParam, CIAData);
            for (int i = 0; i < 4; ++i) {
                *posLead1[i] = offLead[i];
                *posLead2[i] = offLead[i];
            }

        // if neither mag works
        } else {
            for (int i = 0; i < 4; ++i) {
                *posLead1[i] = offLead[i];
                *posLead2[i] = offLead[i];
                *negLead1[i] = offLead[i];
                *negLead2[i] = offLead[i];
            }
        }
    }
}
