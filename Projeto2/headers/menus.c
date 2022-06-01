/**
 * Author: Nicolae Malai
 * Email: a23495@alunos.ipca.pt
 * Github: niiK0
 * Date: 27/03/2022
 * Descrição: Functions of the menus, Trabalho Pratico - EDA
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "structs.h"
#include "menus.h"

/**
 * @brief Function to verify user input
 *
 * @param [in] Int min value
 * @param [in] Int max value
 *
 * @param [out] Int user choice
 */
int GetInt(int min, int max) // gets the user choice as an integer between or equal to min and max
{
    int ChoiceInt = -1; // -1 so it automatically gives error if user's input is not an integer
    char ChoiceChar;    // char buffer to read a letter so when the user inputs a letter it resets the ChoiceInt Buffer
    printf("\n\t> ");
    scanf(" %d", &ChoiceInt);
    scanf("%c", &ChoiceChar);
    while (ChoiceInt > max || ChoiceInt < min) // check if user input is in the range of the menu options and repeats the code if not
    {
        printf("\n\t//Invalid Option//\n\n");
        printf("\n> ");
        scanf(" %d", &ChoiceInt);
        scanf("%c", &ChoiceChar);
    }
    system("cls");    // clears the console
    return ChoiceInt; // returns user choice
}

/**
 * @brief Main Menu
 */
void MainMenu()
{
    system("cls");
    int ChoiceInt;
    job *jobHead = read_job();

    do
    {
        printf("\t--- MAIN MENU ---\n"
               "\t Enter 1 - List Job\n"
               "\t Enter 2 - Add Job\n"
               "\t Enter 3 - Remove Job\n"
               "\t Enter 4 - Add Operation\n"
               "\t Enter 5 - Remove Operation\n"
               "\t Enter 6 - Change Operation\n"
               "\t Enter 7 - Data\n"
               "\n\t Enter 0 - Quit\n");

        ChoiceInt = GetInt(0, 7);
        switch (ChoiceInt)
        {
        case 1:
            job_list_menu(jobHead);
            break;
        case 2:
            jobHead = add_job_menu(jobHead);
            break;
        case 3:
            jobHead = remove_job_menu(jobHead);
            break;
        case 4:
            jobHead = add_operation_menu(jobHead, -1);
            break;
        case 5:
            jobHead = remove_operation_menu(jobHead);
            break;
        case 6:
            jobHead = change_operation_menu(jobHead);
            break;
        case 7:
            data_menu(jobHead);
            break;
        case 0:
            break;
        default:
            printf("\n\t//Invalid Option//\n\n");
            MainMenu();
            break;
        }

    } while (ChoiceInt != 0);
}

/**
 * @brief Menu for operation changes
 *
 * @param [in] Pointer job header
 *
 * @param [out] Pointer job header
 */
job *change_operation_menu(job *head)
{
    system("cls");

    int id;

    // Prints jobs to user
    printf("\tJobs:\n");
    showJobs(head);

    // Asks user to select job
    printf("\n\nSelect the job id to add the operation: ");
    scanf(" %d", &id);

    // Verify if its a valid job
    job *jtemp = j_find(head, id);

    if (jtemp == NULL)
    {
        system("cls");
        printf("\tInvalid Job! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return head;
    }

    // show operation list to user
    system("cls");
    showOperations(jtemp->operationHead);

    // ask for operation number
    int op_num;
    printf("\nSelect 0 to cancel");
    printf("\nSelect operation number: ");
    scanf(" %d", &op_num);

    // check if operation exists
    operation *otemp = o_find(jtemp->operationHead, op_num);

    if (otemp == NULL)
    {
        system("cls");
        printf("\tInvalid Operation! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return head;
    }

    // show operations change menu
    otemp = choose_change_operation_menu(otemp, jtemp->operationHead);

    system("cls");
    printf("\tOperation changed.\n\n");
    printf("Press any key to continue..");
    getch();
    system("cls"); // extra cls to clear console on return
    return head;
}

/**
 * @brief Menu for operation remove
 *
 * @param [in] Pointer job header
 *
 * @param [out] Pointer job header
 */
job *remove_operation_menu(job *head)
{
    system("cls");

    int id;

    // Prints jobs to user
    printf("\tJobs:\n");
    showJobs(head);

    // Asks user to select job
    printf("\n\nSelect the job id to add the operation: ");
    scanf(" %d", &id);

    // Verify if its a valid job
    job *jtemp = j_find(head, id);

    if (jtemp == NULL)
    {
        system("cls");
        printf("\tInvalid Job! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return head;
    }

    // show operation list to user
    system("cls");
    showOperations(jtemp->operationHead);

    // ask for operation number
    int op_num;
    printf("\nSelect 0 to cancel");
    printf("\nSelect operation number: ");
    scanf(" %d", &op_num);

    // check if operation exists
    operation *otemp = o_find(jtemp->operationHead, op_num);

    if (otemp != NULL)
    {
        operation *otemp2 = o_find(jtemp->operationHead, op_num - 1);
        if (otemp2 != NULL)
        {
            otemp2->next = otemp->next;
        }
        else
        {
            jtemp->operationHead = otemp->next;
        }
        free(otemp);
        otemp = jtemp->operationHead;
        op_num = 1;
        while (otemp != NULL)
        {
            otemp->num = op_num;
            op_num++;
            otemp = otemp->next;
        }
    }

    system("cls");
    printf("\tOperation deleted.\n\n");
    printf("Press any key to continue..");
    getch();
    system("cls"); // extra cls to clear console on return
    return head;
}

/**
 * @brief Menu for job remove
 *
 * @param [in] Pointer job header
 *
 * @param [out] Pointer job header
 */
job *remove_job_menu(job *head)
{
    system("cls");

    int id;

    // Prints jobs to user
    printf("\tJobs:\n");
    showJobs(head);

    // Asks user to select job
    printf("\nSelect 0 to cancel");
    printf("\nSelect job number: ");
    scanf(" %d", &id);

    // Verify if its a valid job
    job *jtemp = j_find(head, id);

    if (jtemp == NULL)
    {
        system("cls");
        printf("\tInvalid Job! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return head;
    }
    else
    {
        free(jtemp->operationHead);
        job *jtemp2 = j_find(head, id - 1);
        if (jtemp2 != NULL)
        {
            jtemp2->next = jtemp->next;
        }
        else
        {
            jtemp = jtemp->next;
        }
        free(jtemp);
        jtemp = head;
        id = 1;
        while (jtemp != NULL)
        {
            jtemp->id = id;
            id++;
            jtemp = jtemp->next;
        }
    }

    system("cls");
    printf("\nJob deleted.\n\n");
    printf("Press any key to continue..");
    getch();
    system("cls"); // extra cls to clear console on return
    return head;
}

/**
 * @brief Menu for job list
 *
 * @param [in] Pointer job header
 */
void job_list_menu(job *head)
{

    system("cls");

    int id;
    // Prints jobs to user
    printf("\tJobs:\n");
    showJobs(head);

    // Asks user to select job
    printf("\n\nSelect the job id to add the operation: ");
    scanf(" %d", &id);
    // Print it
    job *jtemp = j_find(head, id);
    system("cls");
    if (jtemp != NULL)
    {
        showJob(jtemp);
        printf("\nPress any key to continue..");
    }
    else
    {
        printf("\tInvalid Job! Going Back.\n\n");
        printf("Press any key to continue..");
    }

    getch();
    system("cls"); // extra cls to clear console on return
    return;
}

/**
 * @brief Function to find lowest time value for a job
 *
 * @param [in] Pointer job header
 */
void find_lowest_for_job(job *head)
{
    system("cls");

    int id;

    // Prints jobs to user
    printf("\tJobs:\n");
    showJobs(head);

    // Asks user to select job
    printf("\n\nSelect the job id to add the operation: ");
    scanf(" %d", &id);

    // Verify if its a valid job
    job *jtemp = j_find(head, id);

    if (jtemp == NULL)
    {
        system("cls");
        printf("\tInvalid Job! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return;
    }

    // show lowest time possible
    operation *otemp = jtemp->operationHead;
    int temp_time = 0, total_time = 0;
    while (otemp != NULL)
    {
        machine *mtemp = otemp->machineHead;
        temp_time = mtemp->timeValue;
        while (mtemp != NULL)
        {
            if (temp_time > mtemp->timeValue)
            {
                temp_time = mtemp->timeValue;
            }
            mtemp = mtemp->next;
        }
        printf("\nLowest time value for operation %d: %d", otemp->num, temp_time);
        total_time += temp_time;
        otemp = otemp->next;
    }

    printf("\n\n\tLowest time value for job: %d .\n\n", total_time);
    printf("Press any key to continue..");
    getch();
    system("cls"); // extra cls to clear console on return
    return;
}

/**
 * @brief Function to find highest time value for a job
 *
 * @param [in] Pointer job header
 */
void find_highest_for_job(job *head)
{
    system("cls");

    int id;

    // Prints jobs to user
    printf("\tJobs:\n");
    showJobs(head);

    // Asks user to select job
    printf("\n\nSelect the job id to add the operation: ");
    scanf(" %d", &id);

    // Verify if its a valid job
    job *jtemp = j_find(head, id);

    if (jtemp == NULL)
    {
        system("cls");
        printf("\tInvalid Job! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return;
    }

    // show lowest time possible
    operation *otemp = jtemp->operationHead;
    int temp_time = 0, total_time = 0;
    while (otemp != NULL)
    {
        machine *mtemp = otemp->machineHead;
        while (mtemp != NULL)
        {
            if (temp_time < mtemp->timeValue)
            {
                temp_time = mtemp->timeValue;
            }
            mtemp = mtemp->next;
        }
        printf("\nHighest time value for operation %d: %d", otemp->num, temp_time);
        total_time += temp_time;
        temp_time = 0;
        otemp = otemp->next;
    }

    printf("\n\n\tHighest time value for job: %d .\n\n", total_time);
    printf("Press any key to continue..");
    getch();
    system("cls"); // extra cls to clear console on return
    return;
}

/**
 * @brief Function to find average time value for an operation
 *
 * @param [in] Pointer job header
 */
void find_average_for_operation(job *head)
{
    system("cls");

    int id;

    // Prints jobs to user
    printf("\tJobs:\n");
    showJobs(head);

    // Asks user to select job
    printf("\n\nSelect the job id to add the operation: ");
    scanf(" %d", &id);

    // Verify if its a valid job
    job *jtemp = j_find(head, id);

    if (jtemp == NULL)
    {
        system("cls");
        printf("\tInvalid Job! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return;
    }

    // show operation list to user
    system("cls");
    showOperations(jtemp->operationHead);

    // ask for operation number
    int op_num;
    printf("\nSelect 0 to cancel");
    printf("\nSelect operation number: ");
    scanf(" %d", &op_num);

    // check if operation exists
    operation *otemp = o_find(jtemp->operationHead, op_num);

    if (otemp == NULL)
    {
        system("cls");
        printf("\tInvalid Operation! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return;
    }

    int mCount = 0, total_time = 0;
    machine *mtemp = otemp->machineHead;
    while (mtemp != NULL)
    {
        mCount++;
        total_time += mtemp->timeValue;
        mtemp = mtemp->next;
    }

    total_time = total_time / mCount;

    system("cls");
    printf("\n\tAverage time value for operation: %d .\n\n", total_time);
    printf("Press any key to continue..");
    getch();
    system("cls"); // extra cls to clear console on return
    return;
}

/**
 * @brief Menu for the different statistics
 *
 * @param [in] Pointer job header
 */
void data_menu(job *head)
{
    int ChoiceInt;

    do
    {
        system("cls");
        printf("\t--- GET DATA ---\n"
               "\t Enter 1 - Find lowest time value \n"
               "\t Enter 2 - Find highest time value \n"
               "\t Enter 3 - Find average time value (operation) \n"
               "\n\t Enter 0 - Confirm\n");

        ChoiceInt = GetInt(0, 3);
        switch (ChoiceInt)
        {
        case 1:
            find_lowest_for_job(head);
            break;
        case 2:
            find_highest_for_job(head);
            break;
        case 3:
            find_average_for_operation(head);
            break;
        case 0:
            return;
        default:
            printf("\n\t//Invalid Option//\n\n");
            return;
        }
    } while (ChoiceInt != 0);
}

/**
 * @brief Menu to add a new job
 *
 * @param [in] Pointer job header
 *
 * @param [out] Pointer job header
 */
job *add_job_menu(job *head)
{
    system("cls");

    job *j_new = j_create_new(j_get_last(head)->id + 1, NULL);
    j_insert_end(&head, j_new);

    add_operation_menu(head, j_new->id);

    system("cls");
    printf("\nJob inserted.\n\n");
    printf("Press any key to continue..");
    getch();
    system("cls"); // extra cls to clear console on return
    return head;
}

/**
 * @brief Menu to add a new operation to the job
 *
 * @param [in] Pointer job header
 *
 * @param [out] Pointer job header
 */
job *add_operation_menu(job *head, int jobId)
{
    system("cls");

    int id = jobId;

    job *jtemp = NULL;

    if (id == -1)
    {

        // Prints jobs to user
        printf("\tJobs:\n");
        showJobs(head);

        // Asks user to select job
        printf("\n\nSelect the job id to add the operation: ");
        scanf(" %d", &id);

        // Verify if its a valid job
        jtemp = j_find(head, id);
    }
    else
    {
        jtemp = j_find(head, id);
    }

    if (jtemp == NULL)
    {
        system("cls");
        printf("\tInvalid Job! Going Back.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return head;
    }

    // add new machine/s
    machine *m_new = NULL;
    m_new = add_machine_menu(m_new);

    // show operation list to user
    system("cls");
    showOperations(jtemp->operationHead);

    // ask for operation number
    int op_num;
    printf("\nSelect 0 to insert at end");
    printf("\nSelect operation number: ");
    scanf(" %d", &op_num);

    // check if operation already exists
    operation *o_new = NULL;
    operation *otemp = NULL;

    if (jtemp->operationHead == NULL)
    {
        operation *o_new = o_create_new(1, m_new);

        o_insert_end(&jtemp->operationHead, o_new);
    }
    else
    {

        operation *otemp = o_find(jtemp->operationHead, op_num);
        operation *o_new = o_create_new(o_get_last(jtemp->operationHead)->num + 1, m_new);

        o_insert_end(&jtemp->operationHead, o_new);
    }

    // if operation doesnt exist just insert at end
    if (otemp == NULL)
    {
        system("cls");
        printf("\tInserted at end.\n\n");
        printf("Press any key to continue..");
        getch();
        system("cls"); // extra cls to clear console on return
        return head;
    }
    else
    {
        // otherwise swap and insert at that spot
        operation *otemp2 = o_find(jtemp->operationHead, op_num - 1);
        operation *extratemp = o_find(jtemp->operationHead, o_get_last(jtemp->operationHead)->num - 1);
        if (otemp2 != NULL)
        {
            otemp2->next = o_new;
            o_new->next = otemp;
            extratemp->next = NULL;
        }
        else
        {
            extratemp->next = NULL;
            o_new->next = otemp;
            jtemp->operationHead = o_new;
        }

        while (o_new != NULL)
        {
            o_new->num = op_num;
            op_num++;
            o_new = o_new->next;
        }
    }

    system("cls");
    printf("\tOperation inserted.\n\n");
    printf("Press any key to continue..");
    getch();
    system("cls"); // extra cls to clear console on return
    return head;
}

/**
 * @brief Menu to choose the change you want to make on an operation
 *
 * @param [in] Pointer selected operation
 * @param [in] Pointer operation header
 *
 * @param [out] Pointer operation header
 */
operation *choose_change_operation_menu(operation *selected_operation, operation *head)
{
    int ChoiceInt;

    do
    {
        system("cls");
        printf("\t--- OPERATION CHANGE ---\n"
               "\t Enter 1 - Add new machine \n"
               "\t Enter 2 - Remove machine \n"
               "\t Enter 3 - Change time value \n"
               "\t Enter 4 - Swap operations \n"
               "\n\t Enter 0 - Confirm\n");

        ChoiceInt = GetInt(0, 4);
        switch (ChoiceInt)
        {
        case 1:
            system("cls");
            int num, timeValue;
            printf("Insert machine number: ");
            scanf(" %d", &num);
            printf("Insert machine time value: ");
            scanf(" %d", &timeValue);
            machine *mtemp = m_create_new(num);
            mtemp->timeValue = timeValue;
            m_insert_end(&selected_operation->machineHead, mtemp);
            break;
        case 2:
            system("cls");
            showMachines(selected_operation->machineHead);
            printf("\nInsert machine number: ");
            scanf(" %d", &num);
            mtemp = m_find(selected_operation->machineHead, num);
            selected_operation->machineHead = m_remove(selected_operation->machineHead, mtemp);
            break;
        case 3:
            // show machines of that operation
            system("cls");
            showMachines(selected_operation->machineHead);

            // ask for machine
            printf("Select machine number: ");
            scanf(" %d", &num);

            // check if exist
            mtemp = m_find(selected_operation->machineHead, num);

            if (mtemp == NULL)
            {
                system("cls");
                printf("\tInvalid Machine! Going Back.\n\n");
                printf("Press any key to continue..");
                getch();
                system("cls"); // extra cls to clear console on break
                break;
            }

            // ask for new time value
            printf("Insert new time value: ");
            scanf(" %d", &timeValue);

            // change time value
            mtemp->timeValue = timeValue;

            printf("\nTime value changed.\n\n");
            printf("Press any key to continue..");
            getch();

            break;
        case 4:
            // show operations again
            system("cls");
            showOperations(head);

            // ask for operation number
            int op_num;
            printf("\nSelect 0 to cancel");
            printf("\nSelect operation number: ");
            scanf(" %d", &op_num);

            // return if op_num == 1st selected op num
            if (op_num == selected_operation->num)
            {
                system("cls");
                printf("\tCan't swap with the same operation! Going Back.\n\n");
                printf("Press any key to continue..");
                getch();
                system("cls"); // extra cls to clear console on break
                break;
            }

            // check if operation exists
            operation *otemp = o_find(head, op_num);

            if (otemp == NULL)
            {
                system("cls");
                printf("\tInvalid Operation! Going Back.\n\n");
                printf("Press any key to continue..");
                getch();
                system("cls"); // extra cls to clear console on break
                break;
            }

            // swap their machines but keep id
            machine *mHtemp = selected_operation->machineHead;
            selected_operation->machineHead = otemp->machineHead;
            otemp->machineHead = mHtemp;

            printf("\nOperation swapped.\n\n");
            printf("Press any key to continue..");
            getch();

            break;
        case 0:
            return head;
        default:
            printf("\n\t//Invalid Option//\n\n");
            return head;
        }
    } while (ChoiceInt != 0);
}

/**
 * @brief Menu to add a new machine to an operation
 *
 * @param [in] Pointer machine header
 *
 * @param [out] Pointer machine header
 */
machine *add_machine_menu(machine *m_head)
{
    int ChoiceInt;

    do
    {
        system("cls");
        printf("\t--- MACHINE CREATION ---\n"
               "\t Enter 1 - Add new machine \n"
               "\n\t Enter 0 - Confirm\n");

        ChoiceInt = GetInt(0, 1);
        switch (ChoiceInt)
        {
        case 1:
            system("cls");
            int num, timeValue;
            printf("Insert machine number: ");
            scanf(" %d", &num);
            printf("Insert machine time value: ");
            scanf(" %d", &timeValue);
            machine *mtemp = m_create_new(num);
            mtemp->timeValue = timeValue;
            m_insert_end(&m_head, mtemp);
            break;
        case 0:
            return m_head;
        default:
            printf("\n\t//Invalid Option//\n\n");
            return m_head;
        }
    } while (ChoiceInt != 0);
}