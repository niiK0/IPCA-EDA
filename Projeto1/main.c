#include <stdio.h>
#include <stdlib.h>
#include "headers/structs.h"
#include "headers/menus.h"

void main(){
    job *jobHead = NULL;

    jobHead = read_job();

    job *jtemp = jobHead;
    while(jtemp != NULL){
        showJob(jtemp);
        printf("\n");
        jtemp = jtemp->next;
    }

}