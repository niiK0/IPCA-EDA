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
    int ChoiceInt;

    do
    {
        printf("\t--- MAIN MENU ---\n"
               "\t Enter 1 - List \n"
               "\t Enter 2 - Add \n"
               "\t Enter 3 - Remove \n"
               "\t Enter 4 - Change \n"
               "\n\t Enter 0 - Quit\n");

        ChoiceInt = GetInt(0, 5);
        switch (ChoiceInt)
        {
        case 1:
            break;
        case 2:

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
        if (ChoiceInt != 0)
        {
            printf("\n\tPress any key to go back");
            getch();
            system("cls");
        }

    } while (ChoiceInt != 0);
}