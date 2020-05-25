#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "ciaAllocation.h"
#include "allocation.c"
#include "setMags.c"

int main(void)
{
    // allocation
    printf("allocation Unit Test\n");
    struct CIADataStruct CIAData1;
    struct allocationParameters parameters1;

    parameters1.command = 5.5;
    parameters1.whichMag = 1;
    allocation(&parameters1,&CIAData1);

    // outputs are not based on real calculations (check allocation
    // under "convert command to duty cycle"
    printf("posXlead1[0] = %i\n", (int) CIAData1.posXlead1[0]); // 0
    printf("posXlead1[1] = %i\n", (int) CIAData1.posXlead1[1]); // 0
    printf("posXlead1[2] = %i\n", (int) CIAData1.posXlead1[2]); // 102
    printf("posXlead1[3] = %i\n", (int) CIAData1.posXlead1[3]); // 6

    printf("posXlead2[0] = %i\n", (int) CIAData1.posXlead2[0]); // 0
    printf("posXlead2[1] = %i\n", (int) CIAData1.posXlead2[1]); // 0
    printf("posXlead2[2] = %i\n", (int) CIAData1.posXlead2[2]); // 0
    printf("posXlead2[3] = %i\n", (int) CIAData1.posXlead2[3]); // 16
    printf("\n");

    // setMags
    printf("setMags Unit Test\n");
    struct CIADataStruct CIAData2;
    struct setMagsParameters parameters2;
    parameters2.commands[0] = 3;
    parameters2.commands[1] = 3;
    parameters2.commands[2] = 3;
    int i;
    for (i = 0; i < 5; ++i) {
        parameters2.magStatus[i] = true;
    }

    setMags(&parameters2, &CIAData2);

    // value every powered lead should take on when using example duty cycle
    // (see allocation)
    char onLead[] = {0, 0, 102, 6};

    int passedLeads = 0;
    bool passed;
    // posXlead1
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.posXlead1[i] != onLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("posXlead1 == onLead\n");
        passedLeads++;
    } else {
        printf("posXlead1 != onLead\n");
    }

    // posXlead2
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.posXlead2[i] != offLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("posXlead2 == offLead\n");
        passedLeads++;
    } else {
        printf("posXlead2 != offLead\n");
    }

    // negXlead1
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.negXlead1[i] != offLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("negXlead1 == offLead\n");
        passedLeads++;
    } else {
        printf("negXlead1 != offLead\n");
    }

    // negXlead2
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.negXlead2[i] != onLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("negXlead2 == onLead\n");
        passedLeads++;
    } else {
        printf("negXlead2 != onLead\n");
    }

    // posYlead1
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.posYlead1[i] != onLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("posYlead1 == onLead\n");
        passedLeads++;
    } else {
        printf("posYlead1 != onLead\n");
    }

    // posYlead2
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.posYlead2[i] != offLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("posYlead2 == offLead\n");
        passedLeads++;
    } else {
        printf("posYlead2 != offLead\n");
    }

    // negYlead1
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.negYlead1[i] != offLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("negYlead1 == offLead\n");
        passedLeads++;
    } else {
        printf("negYlead1 != offLead\n");
    }

    // negYlead2
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.negYlead2[i] != onLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("negYlead2 == onLead\n");
        passedLeads++;
    } else {
        printf("negYlead2 != onLead\n");
    }

    // posZlead1
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.posZlead1[i] != onLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("posZlead1 == onLead\n");
        passedLeads++;
    } else {
        printf("posZlead1 != onLead\n");
    }

    // posZlead2
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.posZlead2[i] != offLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("posZlead2 == offLead\n");
        passedLeads++;
    } else {
        printf("posZlead2 != offLead\n");
    }

    printf("%i out of 10 leads are correct\n", passedLeads);

    return(0);
}
