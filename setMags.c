#include <stdio.h>
#include "ciaAllocation.h"

void setMags(void *pvParameters) {
    // creation of CIA data struct
    struct CIADataStruct CIAData;
    
    // assign variables
    float* commands = (float*) pvParameters;
    float xCommand = *commands;
    float yCommand = *(commands + 1);
    float zCommand = *(commands + 2);
    
}
