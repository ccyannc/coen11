#include "header.h"

struct array_node database[3];
pthread_mutex_t key;
pthread_t thread;

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("missing parameters\n");
		return 1;
	} else {
		FILE *fp;
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			return 1;
		}
		
		read_all(argv[1]);
		pthread_create(&thread, NULL, temp_save, (void *)argv[2]);
		pthread_mutex_init(&key, NULL);
	}
	
	int flag = 0;
	int command;
	int check_number;
	char fn[20];
	char ln[20];
	int age, age1;
	while (flag == 0) {
		printf("\n");
		printf("Enter command:\n");
		check_number = scanf("%i", &command);
		while (check_number != 1) {
			scanf("%*[^\n]");
			printf("Invalid input. ");
			printf("Enter Command:\n");
			check_number = scanf("%i", &command);
		}
		switch (command) {
			case 1: //insert
				printf("Enter first name:\n");
				scanf("%s", fn);
				printf("Enter last name:\n");
				scanf("%s", ln);
				printf("Enter age:\n");
				scanf("%i", &age);
				printf("\n");
				
				if (check_duplicate(fn, ln) == 0) {
					pthread_mutex_lock(&key);
					insert(fn, ln, age);
					pthread_mutex_unlock(&key);
				} else {
					printf("Duplicate\n");
				}
				break;
			case 2: //show all
				show();
				break;
			case 3: //show by age
				printf("Enter age:\n");
				scanf("%i", &age);
				show_age(age);
				break;
			case 4: //remove given fn,ln
				printf("Enter first name:\n");
				scanf("%s", fn);
				printf("Enter last name:\n");
				scanf("%s", ln);
				delete(fn, ln);
				
				break;
			case 5: //ec
				printf("Enter first name:\n");
				scanf("%s", fn);
				printf("Enter last name:\n");
				scanf("%s", ln);
				printf("Enter age:\n");
				scanf("%i", &age);
				printf("Enter new age:\n");
				scanf("%i", &age1);
				change_age(fn, ln, age, age1);
				break;
			case 6:
				read_all_binary(argv[2]);
				break;
			case 0: //save and exit
				pthread_mutex_lock(&key);
				pthread_cancel(thread);
				pthread_mutex_unlock(&key);
				
				save_all(argv[1]);
				flag = 1;
				break;
		}
	}
}