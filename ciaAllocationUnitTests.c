#include "ciaAllocation.h"

int main(void)
{
    // allocation middle case
    printf("allocation Unit Test\n");
    struct CIADataStruct CIAData1;
    struct allocationParameters parameters1;

    parameters1.command = 0.4 * maxMoment;
    parameters1.whichMag = 1;
    allocation(&parameters1, &CIAData1);

    printf("posXlead1[0] = %d, should be %d\n", (int) CIAData1.posXlead1[0], 0); // 0
    printf("posXlead1[1] = %d, should be %d\n", (int) CIAData1.posXlead1[1], 0); // 0
    printf("posXlead1[2] = %d, should be %d\n", (int) CIAData1.posXlead1[2], 102); // 102
    printf("posXlead1[3] = %d, should be %d\n", (int) CIAData1.posXlead1[3], 6); // 6

    printf("posXlead2[0] = %d, should be %d\n", (int) CIAData1.posXlead2[0], 0); // 0
    printf("posXlead2[1] = %d, should be %d\n", (int) CIAData1.posXlead2[1], 0); // 0
    printf("posXlead2[2] = %d, should be %d\n", (int) CIAData1.posXlead2[2], 0); // 0
    printf("posXlead2[3] = %d, should be %d\n", (int) CIAData1.posXlead2[3], 16); // 16
    printf("\n");

    // allocation "full on" edge case
    printf("allocation \"Full On\"\n");

    parameters1.command = 1.0 * maxMoment;
    parameters1.whichMag = 2;
    allocation(&parameters1, &CIAData1);

    printf("negXlead1[0] = %d, should be %d\n", (int) CIAData1.negXlead1[0], 0); // 0
    printf("negXlead1[1] = %d, should be %d\n", (int) CIAData1.negXlead1[1], 16); // 16
    printf("negXlead1[2] = %d, should be %d\n", (int) CIAData1.negXlead1[2], 0); // 0
    printf("negXlead1[3] = %d, should be %d\n", (int) CIAData1.negXlead1[3], 0); // 0

    printf("negXlead2[0] = %d, should be %d\n", (int) CIAData1.negXlead2[0], 0); // 0
    printf("negXlead2[1] = %d, should be %d\n", (int) CIAData1.negXlead2[1], 0); // 0
    printf("negXlead2[2] = %d, should be %d\n", (int) CIAData1.negXlead2[2], 0); // 0
    printf("negXlead2[3] = %d, should be %d\n", (int) CIAData1.negXlead2[3], 16); // 16
    printf("\n");

    // allocation "full off" edge case
    printf("allocation \"Full Off\"\n");

    parameters1.command = 0.0 * maxMoment;
    parameters1.whichMag = 3;
    allocation(&parameters1, &CIAData1);

    printf("posYlead1[0] = %d, should be %d\n", (int) CIAData1.posYlead1[0], 0); // 0
    printf("posYlead1[1] = %d, should be %d\n", (int) CIAData1.posYlead1[1], 0); // 0
    printf("posYlead1[2] = %d, should be %d\n", (int) CIAData1.posYlead1[2], 0); // 0
    printf("posYlead1[3] = %d, should be %d\n", (int) CIAData1.posYlead1[3], 16); // 16

    printf("posYlead2[0] = %d, should be %d\n", (int) CIAData1.posYlead2[0], 0); // 0
    printf("posYlead2[1] = %d, should be %d\n", (int) CIAData1.posYlead2[1], 0); // 0
    printf("posYlead2[2] = %d, should be %d\n", (int) CIAData1.posYlead2[2], 0); // 0
    printf("posYlead2[3] = %d, should be %d\n", (int) CIAData1.posYlead2[3], 16); // 16
    printf("\n");

    // allocation negative case
    printf("allocation Negative Command\n");

    parameters1.command = -0.65 * maxMoment;
    parameters1.whichMag = 4;
    allocation(&parameters1, &CIAData1);

    printf("negYlead1[0] = %d, should be %d\n", (int) CIAData1.negYlead1[0], 0); // 0
    printf("negYlead1[1] = %d, should be %d\n", (int) CIAData1.negYlead1[1], 0); // 0
    printf("negYlead1[2] = %d, should be %d\n", (int) CIAData1.negYlead1[2], 0); // 0
    printf("negYlead1[3] = %d, should be %d\n", (int) CIAData1.negYlead1[3], 16); // 16

    printf("negYlead2[0] = %d, should be %d\n", (int) CIAData1.negYlead2[0], 0); // 0
    printf("negYlead2[1] = %d, should be %d\n", (int) CIAData1.negYlead2[1], 0); // 0
    printf("negYlead2[2] = %d, should be %d\n", (int) CIAData1.negYlead2[2], 102); // 102
    printf("negYlead2[3] = %d, should be %d\n", (int) CIAData1.negYlead2[3], 10); // 10
    printf("\n");

    // setMags
    printf("setMags Unit Test\n");
    struct CIADataStruct CIAData2;
    struct setMagsParameters parameters2;
    parameters2.commands[0] = 0.4 * maxMoment;
    parameters2.commands[1] = 0.4 * maxMoment;
    parameters2.commands[2] = 0.4 * maxMoment;
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
        if (CIAData2.posXlead1[i] != onLead[i]/2){
            passed = false;
        }
    }
    if (passed) {
        printf("posXlead1 == {0, 0, 51, 3}\n");
        passedLeads++;
    } else {
        printf("posXlead1 != {0, 0, 51, 3}\n");
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
        if (CIAData2.negXlead2[i] != onLead[i]/2){
            passed = false;
        }
    }
    if (passed) {
        printf("negXlead2 == {0, 0, 51, 3}\n");
        passedLeads++;
    } else {
        printf("negXlead2 != {0, 0, 51, 3}\n");
    }

    // posYlead1
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.posYlead1[i] != onLead[i]/2){
            passed = false;
        }
    }
    if (passed) {
        printf("posYlead1 == {0, 0, 51, 3}\n");
        passedLeads++;
    } else {
        printf("posYlead1 != {0, 0, 51, 3}\n");
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
        if (CIAData2.negYlead2[i] != onLead[i]/2){
            passed = false;
        }
    }
    if (passed) {
        printf("negYlead2 == {0, 0, 51, 3}\n");
        passedLeads++;
    } else {
        printf("negYlead2 != {0, 0, 51, 3}\n");
    }

    // posZlead1
    passed = true;
    for (i = 0; i < 4; ++i) {
        if (CIAData2.posZlead1[i] != onLead[i]){
            passed = false;
        }
    }
    if (passed) {
        printf("posZlead1 == {0, 0, 102, 6}\n");
        passedLeads++;
    } else {
        printf("posZlead1 != {0, 0, 102, 6}\n");
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
