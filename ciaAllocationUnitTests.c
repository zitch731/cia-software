#include <stdio.h>
#include <math.h>
#include "ciaAllocation.h"

int main(void)
{
    // oneSidedAllocation
    struct CIADataStruct CIAData;
    struct pvParameters parameters;

    parameters.command = 5.5;
    parameters.whichMag = 1;
    oneSidedAllocation(&parameters,&CIAData);

    printf("posXlead1[0] = %i\n", (int) CIAData.posXlead1[0]); // 0
    printf("posXlead1[1] = %i\n", (int) CIAData.posXlead1[1]); // 0
    printf("posXlead1[2] = %i\n", (int) CIAData.posXlead1[2]); // 102
    printf("posXlead1[3] = %i\n", (int) CIAData.posXlead1[3]); // 6

    printf("posXlead2[0] = %i\n", (int) CIAData.posXlead2[0]); // 0
    printf("posXlead2[1] = %i\n", (int) CIAData.posXlead2[1]); // 0
    printf("posXlead2[2] = %i\n", (int) CIAData.posXlead2[2]); // 0
    printf("posXlead2[3] = %i\n", (int) CIAData.posXlead2[3]); // 16
  
    return(0);  
}
