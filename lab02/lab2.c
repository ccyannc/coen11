#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_user_count 20

void insert(char first_name[], char last_name[], int age, int cur_num_users);
int check_duplicate(char first_name[], char last_name[], int cur_num_users);
void list(int cur_num_users);
void list_by_age(int age, int cur_num_users);

char first_names[max_user_count][20];
char last_names[max_user_count][20];
int ages[max_user_count];

int main() {
	int command;
	int flag = 0;
	int cur_num_users = 0;
    char user_input_first[20];
    char user_input_last[20];
    int user_input_age;
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
			case 1:
                printf("User #%i\n", (cur_num_users+1));
                
                printf("Enter first name:\n");
                scanf("%s", user_input_first);
                printf("Enter last name:\n");
                scanf("%s", user_input_last);
                printf("Enter age:\n");
                scanf("%i", &user_input_age);
                
                if (check_duplicate(user_input_first, user_input_last, cur_num_users) == 0) {
                    insert(user_input_first, user_input_last, user_input_age, cur_num_users);
                    cur_num_users++;
                } else {
                    printf("Duplicate of pre-existing name.\n");
                }
				break;
			case 2:
                printf("List of users:\n");
                list(cur_num_users);
				break;
			case 3:
                printf("Search by age:");
                scanf("%i", &user_input_age);
                list_by_age(user_input_age, cur_num_users);
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

void insert(char first_name[], char last_name[], int age, int cur_num_users) {
	strcpy(first_names[cur_num_users], first_name);
	strcpy(last_names[cur_num_users], last_name);
	ages[cur_num_users] = age;
}

int check_duplicate(char first_name[], char last_name[], int cur_num_users) {
	int first_name_found = 0;
	int last_name_found = 0;
	int ctr = 0;

	for (ctr= 0; ctr < cur_num_users; ctr++) {
		if (strcmp(first_name, first_names[ctr]) == 0) {
			first_name_found = 1;
			break;
			}
		}
    
    ctr = 0;
    
    for (ctr= 0; ctr < cur_num_users; ctr++) {
        if (strcmp(last_name, last_names[ctr]) == 0) {
            last_name_found = 1;
            break;
            }
        }
    
    if (first_name_found == 1 && last_name_found == 1) {
        return 1;
    } else {
        return 0;
    }
}

void list(int cur_num_users) {
    int ctr = 0;
    for (ctr= 0; ctr < cur_num_users; ctr++) {
        printf("%s %s, %i\n", first_names[ctr], last_names[ctr], ages[ctr]);
    }
}

void list_by_age(int age, int cur_num_users) {
    int ctr = 0;
    for (ctr = 0; ctr < cur_num_users; ctr++) {
        if (ages[ctr] == age) {
            printf("%s %s, %i\n", first_names[ctr], last_names[ctr], ages[ctr]);
        }
    }
}
