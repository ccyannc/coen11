#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define NODE struct node

struct node {
	char first[21];
	char last[21];
	char age;
	NODE *next;
};

struct array_node {
	NODE *head;
	NODE *tail;
	
};

struct array_node database[3];
pthread_mutex_t key;
pthread_t thread;

void insert(char *fn, char *ln, int age);
float check_duplicate(char *fn, char *ln);
void delete(char *fn, char *ln);

void read_all(char *fn);
void read_all_binary(char *fn);
void save_all(char *fn);
void *temp_save(void *fn);

void show();
void show_age(int age_to_find);
void change_age(char *fn, char *ln, int o_age, int n_age);

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

void insert(char *fn, char *ln, int age) { //f
	NODE *p;
	
	p = (NODE *)malloc(sizeof(NODE));
	
	if (p == NULL) {
		return;
	}
	
	
	
	strcpy(p->first, fn);
	strcpy(p->last, ln);
	p-> age = age;
	
	int index;
	
	if (age < 18) {
		index = 0;
	} else if (age < 65) {
		index = 1;
	} else {
		index = 2;
	}
	
	if (database[index].head == NULL) { //if empty
		database[index].head = p;
		p -> next = NULL;
	} else if (database[index].tail == NULL) { //if only one element head
		database[index].tail = p;
		database[index].head -> next = p; //next element is tail
		database[index].tail -> next = NULL; //tail next does not exist
	} else { //otherwise if 2 elements or more
		database[index].tail -> next = p; //tail next
		database[index].tail = p; //update tail
		database[index].tail -> next = NULL; //tail next = NULL
	}
	
	
	printf("Loaded %s %s, %i into list %i\n", fn, ln, age, index+1);
}

void show() { //f
	NODE *p;
	int i;
	for (i = 0; i < 3; i++) {
		printf("\n");
		printf("List %i:\n", i+1);
		p = database[i].head;
		while (p != NULL) {
			printf("%s %s, %i\n", p->first, p-> last, p->age);
			p = p->next;
		}
		
	}
}

void show_age(int age_to_find) { //f
	NODE *p;
	int i;
	for (i = 0; i < 3; i++) {
		p = database[i].head;
		while (p != NULL) {
			if (p-> age == age_to_find) {
				printf("%s %s, %i\n", p->first, p-> last, p->age);
			}
			p = p->next;
		}
	}
}

void change_age(char *fn, char *ln, int o_age, int n_age) {
	NODE *p;
	int i;
	pthread_mutex_lock(&key);
	for (i = 0; i < 3; i++) {
		p = database[i].head;
		while (p != NULL) {
			if ((strcmp(p->first, fn) ==0) && (strcmp(p->last, ln) ==0) && (p->age == o_age)) {
				delete(fn, ln);
				insert(fn, ln, n_age);
				printf("Successfully changed age from %i to %i\n", o_age, n_age);
			}
			p = p->next;
		}
		
	}
	pthread_mutex_unlock(&key);
	
}

void delete(char *fn, char *ln) {
	NODE *p, *q;
	
	p = q = database[0].head;
	while (p != NULL) {
		if ((strcmp(p->first, fn) ==0) && (strcmp(p->last, ln) ==0)) {
			//4 cases
			//only one element
			if (p -> next == NULL && q == database[0].head) {
				database[0].head = NULL;
				free(p);
				return;
			}
			//two elements
			if ((p == database[0].head) && (p-> next == database[0].tail)) {
				database[0].head = database[0].tail;
				free(p);
				return;
			}
			
			if (p == database[0].head) {
				database[0].head = p->next;
				free(p);
				return;
			}
			
			if (p == database[0].tail) {
				database[0].tail = q;
				q-> next = NULL;
				free(p);
				return;
			}
			
			if ((p != database[0].head) && (p != database[0].tail)) {
				q -> next = p-> next;
				free(p);
				return;
			}
			
			
		}
		q = p;
		p = p-> next;
	}
	
	p = q = database[1].head;
	while (p != NULL) {
		if ((strcmp(p->first, fn) ==0) && (strcmp(p->last, ln) ==0)) {
			//4 cases
			//only one element
			if (p -> next == NULL && q == database[1].head) {
				database[1].head = NULL;
				free(p);
				return;
			}
			//two elements
			if ((p == database[1].head) && (p-> next == database[1].tail)) {
				database[1].head = database[1].tail;
				free(p);
				return;
			}
			
			if (p == database[1].head) {
				database[1].head = p->next;
				free(p);
				return;
			}
			
			if (p == database[1].tail) {
				database[1].tail = q;
				q-> next = NULL;
				free(p);
				return;
			}
			
			if ((p != database[1].head) && (p != database[1].tail)) {
				q -> next = p-> next;
				free(p);
				return;
			}
			
			
		}
		q = p;
		p = p-> next;
	}
	
	p = q = database[2].head;
	while (p != NULL) {
		if ((strcmp(p->first, fn) ==0) && (strcmp(p->last, ln) ==0)) {
			//4 cases
			//only one element
			if (p -> next == NULL && q == database[2].head) {
				database[2].head = NULL;
				free(p);
				return;
			}
			//two elements
			if ((p == database[2].head) && (p-> next == database[2].tail)) {
				database[2].head = database[2].tail;
				free(p);
				return;
			}
			
			if (p == database[2].head) {
				database[2].head = p->next;
				free(p);
				return;
			}
			
			if (p == database[2].tail) {
				database[2].tail = q;
				q-> next = NULL;
				free(p);
				return;
			}
			
			if ((p != database[2].head) && (p != database[2].tail)) {
				q -> next = p-> next;
				free(p);
				return;
			}
			
			
		}
		q = p;
		p = p-> next;
	}
}

float check_duplicate(char *fn, char *ln) {
	NODE *p;
	int i;
	
	
	for (i = 0; i < 3; i++) {
		p = database[i].head;
		
		while (p != NULL) {
			if (strcmp(fn, p->first) == 0) {
				if (strcmp(ln, p-> last) == 0) {
					
					return 1;
				}
			}
			p = p->next;
		}
	}
	return 0;
}

void read_all(char *fn) { //f
	
	FILE *fp;
	fp = fopen(fn, "r");
	if (fp == NULL) return;
	
	
	int ctr = 0;
	char first_name[20];
	char last_name[20];
	int age;
	
	printf("\n");
	
	while (fscanf(fp, "%s %s %i", first_name, last_name, &age) == 3) {
		insert(first_name, last_name, age);
		ctr++;
	}
	printf("\n");
	printf("Loaded %i entries\n", ctr);
	fclose(fp);
	
}

void save_all(char *fn) {
	NODE *p;
	FILE *fp;
	int i;
	
	fp = fopen(fn, "w");
	
	if (fp == NULL) return;
	
	
	for (i = 0; i < 3; i++) {
		p = database[i].head;
		while (p != NULL) {
			fprintf(fp, "%s %s %i\n", p->first, p->last, p->age);
			p = p->next;
		}
	}
	fclose(fp);
}

void *temp_save(void *fn) {
	int i;
	NODE *p;
	FILE *fp;
	
	for (;;) {
		sleep(15);
		fp = fopen((char*)fn, "wb");
		if (fp == NULL) {
			
		} else {
			pthread_mutex_lock(&key);
			for (i = 0; i < 3; i++) {
				p = database[i].head;
				while (p != NULL) {
					fwrite(p, sizeof(NODE), 1, fp);
					p = p->next;
				}
			}
			pthread_mutex_unlock(&key);
			time_t now = time(0);
			printf("autosaved at %ld\n", now);
			fclose(fp);
		}
		
	}
}

void read_all_binary(char *fn) {
	
	NODE temp;
	
	int i;
	NODE *p;
	FILE *fp;
	
	char first_name[20];
	char last_name[20];
	int age;
	
	fp = fopen(fn, "rb");
	if (fp == NULL) return;
	
	
	pthread_mutex_lock(&key);
	while (fread(&temp, sizeof(NODE), 1, fp) == 1) {
		strcpy(first_name, temp.first);
		strcpy(last_name, temp.last);
		age = temp.age;
		
		printf("%s %s %i\n", first_name, last_name, age);
	}
	pthread_mutex_unlock(&key);
	
	
}





