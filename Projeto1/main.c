#include <stdio.h>
#include <stdlib.h>
#include "headers/structs.h"

void main(){
    FILE *planFile;
    job *jobHead = NULL;

    if((planFile = fopen("plan.txt", "r")) == NULL){
        printf("File not found!");
        exit(1);
    }
    jobHead = read_job(planFile);

    showJob(jobHead->next);

    fclose(planFile);
}