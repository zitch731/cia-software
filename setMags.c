#include <stdio.h>
#include <stdbool.h>
#include "ciaAllocation.h"

void setMags(struct setMagsParameters *parameters,
             struct CIADataStruct *CIAData) {

    // assign variables
    double* commands = (*parameters).commands;
    bool* magStatus  = (*parameters).magStatus;
    double xCommand = *commands;
    double yCommand = *(commands + 1);
    double zCommand = *(commands + 2);

    // printf("magStatus[1] = %s\n", *(magStatus+1) ? "true" : "false");

    //code
    double command;
    int firstMag;
    bool posXworking;
    bool negXworking;

    // xMags
    command = xCommand;
    firstMag = 1;
    posXworking = *magStatus;
    negXworking = *(magStatus + 1);

    // if both mags are working
    if (posXworking && negXworking) {
        struct allocationParameters posParam;
        struct allocationParameters negParam;
        posParam.command = command/2;
        negParam.command = -command/2;
        posParam.whichMag = firstMag;
        negParam.whichMag = firstMag + 1;
        oneSidedAllocation(&posParam, CIAData);
        oneSidedAllocation(&negParam, CIAData);

    // if positive mag works
    } else if (posXworking) {
        struct allocationParameters posParam;
        posParam.command = command;
        posParam.whichMag = firstMag;
        oneSidedAllocation(&posParam, CIAData);
        for (int i = 0; i < 4; ++i) {
            CIAData->negXlead1[i] = offLead[i];
            CIAData->negXlead2[i] = offLead[i];
        }

    // if negative mag works
    } else if (negXworking) {
        struct allocationParameters negParam;
        negParam.command = -command;
        negParam.whichMag = firstMag + 1;
        oneSidedAllocation(&negParam, CIAData);
        for (int i = 0; i < 4; ++i) {
            CIAData->posXlead1[i] = offLead[i];
            CIAData->posXlead2[i] = offLead[i];
        }

    // if neither mag works
    } else {
        for (int i = 0; i < 4; ++i) {
            CIAData->posXlead1[i] = offLead[i];
            CIAData->posXlead2[i] = offLead[i];
            CIAData->negXlead1[i] = offLead[i];
            CIAData->negXlead2[i] = offLead[i];
        }
    }

}
