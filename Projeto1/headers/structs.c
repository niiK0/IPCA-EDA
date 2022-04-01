/**
 * Author: Nicolae Malai
 * Email: a23495@alunos.ipca.pt
 * Github: niiK0
 * Date: 27/03/2022
 * Descrição: Functions of the structs, Trabalho Pratico - EDA
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// Jobs
/**
  * @brief Creates new job
  * 
  * @param [in] Int job id
  * @param [in] Pointer job header
  * 
  * @param [out] Pointer job header
 */
job *j_create_new(int jobId, operation *operationHead)
{
    job *result = malloc(sizeof(job));
    result->id = jobId;
    result->operationHead = operationHead;
    result->next = NULL;
    return result;
}

/**
  * @brief inserts job at end
  * 
  * @param [in] Pointer of pointer of job header
  * @param [in] Pointer job to insert
  * 
  * @param [out] Pointer job header
 */
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

/**
  * @brief find a job
  * 
  * @param [in] Pointer job header
  * @param [in] int job id
  * 
  * @param [out] Pointer job
 */
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

/**
  * @brief Shows all jobs
  * 
  * @param [in] Pointer of job header
 */
void showJobs(job *head)
{
    job *temp = head;
    while (temp != NULL)
    {
        printf("Id: %d  ", temp->id);
        temp = temp->next;
    }
}

// Operations
/**
  * @brief Creates new operation
  * 
  * @param [in] Int operation id
  * @param [in] Pointer operation header
  * 
  * @param [out] Pointer operation header
 */
operation *o_create_new(int operationId, machine *machineHead)
{

    operation *result = malloc(sizeof(operation));
    result->num = operationId;
    result->machineHead = machineHead;
    result->next = NULL;
    return result;
}

/**
  * @brief inserts operation at end
  * 
  * @param [in] Pointer of pointer of operation header
  * @param [in] Pointer operation to insert
  * 
  * @param [out] Pointer operation header
 */
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

/**
  * @brief find a operation
  * 
  * @param [in] Pointer operation header
  * @param [in] int operation id
  * 
  * @param [out] Pointer operation
 */
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

/**
  * @brief find last operation in header
  * 
  * @param [in] Pointer operation header
  * 
  * @param [out] Pointer operation
 */
operation *o_get_last(operation *head){
    operation *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    return temp;
}

/**
  * @brief Shows all operations
  * 
  * @param [in] Pointer of operation header
 */
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
/**
  * @brief Shows all machines
  * 
  * @param [in] Pointer of machine header
 */
void showMachines(machine *head)
{
    machine *temp = head;
    while (temp != NULL)
    {
        printf("  ID: %d Time: %d - ", temp->id, temp->timeValue);
        temp = temp->next;
    }
}

/**
  * @brief removes a machine
  * 
  * @param [in] Pointer machine header
  * @param [in] Pointer machine to remove
  * 
  * @param [out] Pointer machine header
 */
machine *m_remove(machine *head, machine *machine_to_remove){
    machine *mtemp = head;
    while(mtemp != NULL){
        if(mtemp == machine_to_remove){
            head = mtemp->next;
            free(machine_to_remove);
            return head;
        }
        if(mtemp->next == machine_to_remove){
            mtemp->next = machine_to_remove->next;
            free(machine_to_remove);
            return mtemp;
        }
        mtemp = mtemp->next;
    }

    return mtemp;
}

/**
  * @brief Creates new machine
  * 
  * @param [in] Int machine id
  * @param [in] Pointer machine header
  * 
  * @param [out] Pointer machine header
 */
machine *m_create_new(int id)
{
    machine *result = malloc(sizeof(machine));
    result->id = id;
    result->next = NULL;
}

/**
  * @brief inserts machine at end
  * 
  * @param [in] Pointer of pointer of machine header
  * @param [in] Pointer machine to insert
  * 
  * @param [out] Pointer machine header
 */
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

/**
  * @brief find a machine
  * 
  * @param [in] Pointer machine header
  * @param [in] int machine id
  * 
  * @param [out] Pointer machine
 */
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

// General
/**
  * @brief reads plan file to get all jobs
  * 
  * @param [out] Pointer job header
 */
job *read_job()
{
    FILE *planFile;

    if ((planFile = fopen("plan.txt", "r")) == NULL)
    {
        printf("File not found!");
        return NULL;
    }

    int i, opCount = 1, mCount = 1, alreadyCreatedO = 0, jobCount = 1;
    job *jobHead = NULL;
    operation *operationHead = NULL;
    machine *machineHead = NULL;
    char *temp;

    do
    { // scan until file end
        // reads lines in pairs and resets no lines where it starts with "99";
        //  GET MACHINES
        while (fscanf(planFile, " %d", &i) == 1) // read line 1
        {
            if (i == 99) // when changing jobs
            {
                job *jtemp = j_create_new(jobCount, operationHead);
                jobHead = j_insert_end(&jobHead, jtemp);
                jobCount++;
                operationHead = NULL;
                opCount = 1;
                fscanf(planFile, "%*c", &temp);
                fscanf(planFile, " %d", &i);
            }
            machine *mtemp = m_create_new(i);
            machineHead = m_insert_end(&machineHead, mtemp);
            mCount++;
        }
        fscanf(planFile, "%*c", temp); // skips to next line
        // GET TIMINGS
        while (fscanf(planFile, " %d", &i) == 1) // reads line 2
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
    } while (fscanf(planFile, "%*c", &temp) != EOF);
    // create job for the last operations
    job *jtemp = j_create_new(jobCount, operationHead);
    jobHead = j_insert_end(&jobHead, jtemp);

    fclose(planFile);

    return jobHead;
}

/**
  * @brief writes jobs to file
  * 
  * @param [in] Pointer job header
 */
void write_job(job *head)
{
    FILE *planFile;

    if ((planFile = fopen("test.txt", "w")) == NULL)
    {
        printf("File not found!");
        return;
    }

    job *jtemp = head;
    while (jtemp != NULL)
    {
        // read operations
        operation *otemp = jtemp->operationHead;
        while (otemp != NULL)
        {
            // read machine head of the operation
            machine *mtemp = otemp->machineHead;
            // write machine id's line
            while (mtemp != NULL)
            {
                if (mtemp->next == NULL)
                {
                    fprintf(planFile, "%d,\n", mtemp->id);
                }
                else
                {
                    fprintf(planFile, "%d ", mtemp->id);
                }
                mtemp = mtemp->next;
            }
            // write machine time lines
            mtemp = otemp->machineHead;
            while (mtemp != NULL)
            {
                if (mtemp->next == NULL)
                {
                    fprintf(planFile, "%d,\n", mtemp->timeValue);
                }
                else
                {
                    fprintf(planFile, "%d ", mtemp->timeValue);
                }
                mtemp = mtemp->next;
            }
            otemp = otemp->next;
        }
        jtemp = jtemp->next;

        if (jtemp != NULL)
        {
            fprintf(planFile, "99,\n");
        }
    }

    fclose(planFile);
}

/**
  * @brief Shows a specific job
  * 
  * @param [in] Pointer job
 */
void showJob(job *job)
{
    printf("Job %d :\n", job->id);
    operation *otemp = job->operationHead;
    while (otemp != NULL)
    {
        printf("Operation %d :\n", otemp->num);
        printf("Machines on operation %d : ", otemp->num);
        machine *mtemp = otemp->machineHead;
        while (mtemp != NULL)
        {
            printf("\nID: %d Time: %d", mtemp->id, mtemp->timeValue);
            mtemp = mtemp->next;
        }
        printf("\n");
        otemp = otemp->next;
    }
}