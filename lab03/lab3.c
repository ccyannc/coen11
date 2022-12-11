#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(char fn[], char ln[], int age, int ctr);
void show(int ctr);
void show_age(int age_to_find, int ctr);
void removal(char fn[], char ln[], int ctr);
void shift(int direction, int index); // 0 for add, 1 for remove
int check_duplicate(char fn[], char ln[], int ctr);

//struct declaration
struct person {
    char f_name[20];
    char l_name[20];
    int age;
};

//global variables
struct person db[20];
int ctr = 0;


int main() {
    int command;
    int flag = 0;
    
    char user_fn[20];
    char user_ln[20];
    int user_age;
    
    int check_number;

    while(flag == 0){

        printf("Enter Command:\n");
        check_number = scanf("%i", &command);
        while (check_number != 1) {
            scanf("%*[^\n]");
            printf("Invalid input. ");
            printf("Enter Command:\n");
            check_number = scanf("%i", &command);
        }
        switch(command) {
            case 1: //insert
                
                printf("Enter first name:\n");
                scanf("%s", user_fn);
                printf("Enter last name:\n");
                scanf("%s", user_ln);
                printf("Enter age:\n");
                scanf("%i", &user_age);
                
                if (check_duplicate(user_fn, user_ln, ctr) == 1) {
                    printf("Duplicate\n");
                } else {
                    insert(user_fn, user_ln, user_age, ctr);
                    ctr++;
                }
                break;
            case 2: //
                show(ctr);
                break;
            case 3:
                printf("Search by age:");
                scanf("%i", &user_age);
                show_age(user_age, ctr);
                break;
            case 4:
                printf("Enter first name:\n");
                scanf("%s", user_fn);
                printf("Enter last name:\n");
                scanf("%s", user_ln);
                removal(user_fn, user_ln, ctr);
                break;
            case 0:
                flag = 1;
                break;
            default:
                printf("Invalid input.\n");
                command = -1;
        }
    }
}


void insert(char *fn, char *ln, int age, int counter) {
    
    
    struct person *p;
    p = db;
    
    int i;
    int j;
    for (i = 0; i < counter; i++, p++) {
        if(strcmp(&ln[0], p->l_name) < 0) {
            while (counter >= i) {
                *(p+counter) = *(p+(counter-1));
                counter--;
            }
            break;
        }
    }

    strcpy(p -> f_name, fn);
    strcpy(p -> l_name, ln);
    p -> age = age;
    
}

void show(int ctr) {
    struct person *p;
    p = db;
    
    int i;
    for (i = 0; i < ctr; i++, p++) {
        printf("%s ", p-> f_name);
        printf("%s, ", p-> l_name);
        printf("%i\n", p-> age);
    }
    
}

void show_age(int age_to_find, int ctr) {
    struct person *p;
    p = db;
    
    int i;
    for (i = 0; i < ctr; i++, p++) {
        if (p->age == age_to_find) {
            printf("%s ", p-> f_name);
            printf("%s, ", p-> l_name);
            printf("%i\n", p-> age);
        }
    }
}

void removal(char fn[], char ln[], int counter) {
    struct person *p;
    p = db;
    
    char db_name[40];
    char fn_plus_ln[40];
    strcpy(fn_plus_ln, fn);
    strcat(fn_plus_ln, ln);
    
    int i;
    for (i = 0; i < ctr; i++, p++) {
        strcpy(db_name, p -> f_name);
        strcat(db_name, p -> l_name);
        if (strcmp(db_name, fn_plus_ln) == 0) {
            while (i <= counter) {
                *(p) = *(p+1);
                i++;
                p++;
            }
            ctr--;
            break;
        }
    }
}

int check_duplicate(char fn[], char ln[], int ctr) {
    struct person *p;
    p = db;
    
    char db_name[40];
    char fn_plus_ln[40];
    strcpy(fn_plus_ln, fn);
    strcat(fn_plus_ln, ln);
    
    int i;
    for (i = 0; i < ctr; i++, p++) {
        strcpy(db_name, p -> f_name);
        strcat(db_name, p -> l_name);
        if (strcmp(db_name, fn_plus_ln) == 0) {
            return 1;
        }
    }
    return 0;
}

