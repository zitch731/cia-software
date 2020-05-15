#include <stdio.h>
#include <stdbool.h>
#include "ciaAllocation.h"

void setMags(struct setMagsParameters *parameters) {
    // creation of CIA data struct
    struct CIADataStruct CIAData;

    // assign variables
    double* commands = (*parameters).commands;
    bool* magStatus  = (*parameters).magStatus;
    double xCommand = *commands;
    double yCommand = *(commands + 1);
    double zCommand = *(commands + 2);

    printf("magStatus[1] = %s", *(magStatus+1) ? "true" : "false");

}
