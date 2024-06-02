#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
/* variables */
struct students // data structre
{
    int id;           // Number of the student
    char name[30];    // name of student
    char subject[50]; // subject the student
    float g1;         // first grade
    float g2;         // second grande
};

int main(void) // main function
{
    // Variables
    bool found;
    int id;
    int c;
    char answer = 'Y';
    struct students students;

    FILE *file;

    file = fopen("students.dat", "ab+");

    if (file == NULL) // checking if the file was opened
    {
        printf("\n cannot open the file... try again.");
        return 1;
    }
    else
    {
        printf("\nFile Opened !!");

        while (answer == 'Y')
        {

            do // Validation -> The program can register only one id by student
            {
                found = false;
                printf("Input your id number: ");
                scanf("%d", &id);
                fflush(stdin);

                fseek(file, 0, SEEK_SET); // return the cursor to the start

                while (fread(&students, sizeof(students), 1, file))
                {
                    if (id == students.id)
                    {
                        found = true;
                        printf("This code already exist...\n");
                        break;
                    }
                }

            } while (found == true);
            students.id = id;

            printf("Type your name: ");
            fgets(students.name, 30, stdin);
            students.name[strcspn(students.name, "\n")] = '\0';
            fflush(stdin); // clearing the buffer

            printf("Type you subject: ");
            fgets(students.subject, 50, stdin);
            students.subject[strcspn(students.subject, "\n")] = '\0';
            fflush(stdin); // clearing the buffer

            printf("Type you grade 1: ");
            scanf("%f", &students.g1);
            fflush(stdin); // clearing the buffer

            printf("Type your grade 2: ");
            scanf("%f", &students.g2);
            fflush(stdin); // clearing the buffer

            fwrite(&students, sizeof(students), 1, file);

            printf("Would you like to continue [y] [n]: ");
            scanf(" %c", &answer);
            answer = toupper(answer); // getting the character in lowercase
            fflush(stdin);            // clearing the buffer

            if (answer == 'N')
            {
                system("cls");
                break; // this end of the loop
            }
        }

        fclose(file); // closing the file

        printf("\n The file was closed.");
    }

    do
    {
        printf("Press 1 to see the registered students.. ");
        scanf("%d", &c);

        if (c != 1)
        {
            printf("Invalid input...Try again\n");
            system("pause");
            system("cls");
        }

    } while (c != 1);

    file = fopen("students.dat", "rb"); // read binary -> This will be read the file
    if (file == NULL)                   // checking if the file is opened
    {
        printf("\n Cannot open the file... Try again.");
        return 1;
    }
    // Show the registered students
    printf("REGISTERED STUDENTS - MARYLAND HIGH SCHOOL 2024\n");
    printf("---------------------------------------------\n");
    printf("  ##  ID  ##    NAME    ##     SUBJECT    ## \n");
    printf("---------------------------------------------\n");
    while (fread(&students, sizeof(students), 1, file))
    {
        printf("%-14d   %-15s   %-15s\n", students.id, students.name, students.subject);
    }

    fclose(file); // close the file

    return 0;
}