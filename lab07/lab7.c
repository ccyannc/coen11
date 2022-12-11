#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void insert(char *fn, char *ln, int age);
void read_all(FILE *fp);
void save_all(char *file_name);
float check_duplicate(char *fn, char *ln);
void delete(char *fn, char *ln);
void show();
void show_age(int age_to_find);
void change_age(char *fn, char *ln, int o_age, int n_age);
void delete_node_array(NODE *p);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("PROGRAM MISSING FILE NAME\n");
		return 1;
	} else {
		FILE *fp;
		fp = fopen(argv[1], "rb");
		if (fp == NULL) {
			printf("Binary file %s cannot be opened.\nWould you like to create a new binary file by this name? (y/n)\n", argv[1]);
			char response[1];
			scanf("%c", response);
			if (response[0] == 'y') {
				fp = fopen(argv[1], "wb");
				if ( fp != NULL) {
					printf("Successfully created binary file %s\n", argv[1]);
				} else {
					return 1;
				}
			} else {
				return 1;
			}
		}
		//passes all checks, assume that file exists and can be loaded
		printf("\n");
		read_all(fp);
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
				
				if (check_duplicate(fn, ln) == 0) {
					insert(fn, ln, age);
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
			case 0: //save and exit
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
	printf("Loading %s %s, %i into list %i\n", fn, ln, age, index+1);
	printf("done\n");
	printf("\n");
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

void read_all(FILE *fp) { //f
	
	NODE user;
	
	int ctr = 0;
	char first_name[20];
	char last_name[20];
	int age;
	
	while (fread(&user, sizeof(NODE), 1, fp) == 1) {
		strcpy(first_name, user.first);
		strcpy(last_name, user.last);
		age = user.age;
		
		insert(first_name, last_name, age);
		ctr++;
	}
	printf("\n");
	printf("Loaded %i entries\n", ctr);
	printf("\n");
	fclose(fp);
	
}

void save_all(char *file_name) {
	NODE *p;
	FILE *fp;
	int i;
	
	fp = fopen(file_name, "wb");
	
	if (fp == NULL) {
		return;
	}
	
	
	for (i = 0; i < 3; i++) {
		p = database[i].head;
		
		
		while (p != NULL) {
			printf("Saving node %s %s, %i from list %i\n", p->first, p->last, p->age, i);
			fwrite(p, sizeof(NODE), 1, fp);
			p = p->next;
		}
		
		delete_node_array(database[i].head);
	}
	fclose(fp);
	
}

void delete_node_array(NODE *head) {
	
	if (head == NULL) {
		return;
	}
	delete_node_array(head->next);
	printf("Deleting node %s %s, %i\n", head->first, head->last, head->age);
	free(head);
	printf("done\n");
	printf("\n");
	
}




