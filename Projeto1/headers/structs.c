#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// Jobs
job *j_create_new(int jobId, operation *operationHead)
{
    job *result = malloc(sizeof(job));
    result->id = jobId;
    result->operationHead = operationHead;
    result->next = NULL;
    return result;
}

job *j_insert_end(job **head, job *job_to_insert)
{
    job_to_insert->next = NULL;

    if (*head == NULL)
        *head = job_to_insert;
    else
    {
        job *last = *head;

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = job_to_insert;
    }
    return *head;
}

job *j_find(job *head, int id)
{
    job *temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void showJobs(job *head)
{
    job *temp = head;
    while (temp != NULL)
    {
        printf("  Id: %d", temp->id);
        temp = temp->next;
    }
}

// Operations
operation *o_create_new(int operationId, machine *machineHead)
{

    operation *result = malloc(sizeof(operation));
    result->num = operationId;
    result->machineHead = machineHead;
    result->next = NULL;
    return result;
}

operation *o_insert_end(operation **head, operation *operation_to_insert)
{
    operation_to_insert->next = NULL;

    if (*head == NULL)
        *head = operation_to_insert;
    else
    {
        operation *last = *head;

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = operation_to_insert;
    }
    return *head;
}

operation *o_find(operation *head, int num)
{
    operation *temp = head;
    while (temp != NULL)
    {
        if (temp->num == num)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void showOperations(operation *head)
{
    operation *temp = head;
    while (temp != NULL)
    {
        printf("  Num: %d", temp->num);
        temp = temp->next;
    }
}

// Machine
machine *m_create_new(int id)
{
    machine *result = malloc(sizeof(machine));
    result->id = id;
    result->next = NULL;
}

void showMachines(machine *head)
{
    machine *temp = head;
    while (temp != NULL)
    {
        printf("  ID: %d Time: %d - ", temp->id, temp->timeValue);
        temp = temp->next;
    }
}

machine *m_insert_end(machine **head, machine *machine_to_insert)
{
    machine_to_insert->next = NULL;

    if (*head == NULL)
        *head = machine_to_insert;
    else
    {
        machine *last = *head;

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = machine_to_insert;
    }
    return *head;
}

machine *m_find(machine *head, int id)
{
    machine *temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

job *read_job(FILE *planFile)
{
    int jobCount = 1;
    job *jobHead = NULL;
    operation *operationHead = NULL;
    char *temp, *temp2;

    while (fscanf(planFile, "%*c", &temp) != EOF)
    { // scan until file end
        operationHead = read_operations(planFile);
        job *jtemp = j_create_new(jobCount, operationHead);
        jobHead = j_insert_end(&jobHead, jtemp);
        jobCount++;
        operationHead = NULL;
    }

    return jobHead;
}

operation *read_operations(FILE *planFile)
{
    int i, opCount = 1, mCount = 1, alreadyCreatedO = 0;
    operation *operationHead = NULL;
    machine *machineHead = NULL;
    char *temp, *temp2;

    // GET MACHINES
    while (i != 99)
    {
        while (fscanf(planFile, " %d", &i) == 1)
        {
            if (i == 99)
            {
                fscanf(planFile, "%*c", temp2);
                return operationHead;
            }
            machine *mtemp = m_create_new(i);
            machineHead = m_insert_end(&machineHead, mtemp);
            mCount++;
        }
        fscanf(planFile, "%*c", temp2);
        // GET TIMINGS
        while (fscanf(planFile, " %d", &i) == 1)
        {
            if (alreadyCreatedO == 0)
            {
                operation *otemp = o_create_new(opCount, machineHead);
                operationHead = o_insert_end(&operationHead, otemp);
                opCount++;
                alreadyCreatedO = 1;
            }

            machineHead->timeValue = i;      // start filling values, dont care about machineHead changing since we used it already
            machineHead = machineHead->next; // move to the next to fill values again
        }
        alreadyCreatedO = 0;
        machineHead = NULL;
        mCount = 1;
        if(fscanf(planFile, "%*c", &temp) == EOF) return operationHead;
    }
    return operationHead;
}

void showJob(job *job){
    printf("Job %d :\n", job->id);
    operation *otemp = job->operationHead;
    while(otemp != NULL){
        printf("Operation %d :\n", otemp->num);
        printf("Machines on operation %d : ", otemp->num);
        machine *mtemp = otemp->machineHead;
        while(mtemp != NULL){
            printf("\nID: %d Time: %d", mtemp->id, mtemp->timeValue);
            mtemp = mtemp->next;
        }
        printf("\n");
        otemp = otemp->next;
    }
}