#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "structs.h"
#include "menus.h"

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

void MainMenu()
{
    system("cls");
    int ChoiceInt;
    job *jobHead = read_job();

    do
    {
        printf("\t--- MAIN MENU ---\n"
               "\t Enter 1 - List \n"
               "\t Enter 2 - Add Operation\n"
               "\t Enter 3 - Remove \n"
               "\t Enter 4 - Change \n"
               "\n\t Enter 0 - Quit\n");

        ChoiceInt = GetInt(0, 5);
        switch (ChoiceInt)
        {
        case 1:
            break;
        case 2:
            jobHead = add_operation_menu(jobHead);
            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

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

job *add_operation_menu(job *head)
{
    system("cls");

    int id, valid = 0;

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
        MainMenu();
    }

    // add new machine/s
    machine *m_new = NULL;
    m_new = add_machine_menu(m_new);

    // show operation list to user
    system("cls");
    showOperations(jtemp->operationHead);

    // ask for operation number
    int op_num;
    printf("\nSelect operation number: ");
    scanf(" %d", &op_num);

    printf("\n\n1st\n\n");
    showOperations(jtemp->operationHead);

    // check if operation already exists
    operation *otemp = o_find(jtemp->operationHead, op_num);

    operation *o_new = o_create_new(o_get_last(jtemp->operationHead)->num + 1, m_new);
    o_insert_end(&jtemp->operationHead, o_new);

    printf("\n\n2st\n\n");
    showOperations(jtemp->operationHead);

    // if operation doesnt exist just insert at end
    if (otemp == NULL)
    {
        system("cls");
        printf("\tInvalid Operation! Inserting at end.\n\n");
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
            //TODO
            o_new->next = otemp;
            extratemp->next = NULL;
        }

        printf("\n");
        while(otemp2 != NULL){
            printf("Num: %d ", otemp2->num);
            otemp2 = otemp2->next;
        }

        while (o_new != NULL)
        {
            o_new->num = op_num;
            op_num++;
            o_new = o_new->next;
        }
    }

    printf("\n\n4st\n\n");
    showOperations(jtemp->operationHead);

    showJob(jtemp);
    getch();

    return head;
}

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
            add_machine_menu(m_head);
            break;
        }
    } while (ChoiceInt != 0);
}