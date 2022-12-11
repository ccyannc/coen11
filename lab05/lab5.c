#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NODE struct node


struct node {
    char user_first[20];
    char user_last[20];
    int user_age;
    NODE *next;
};

NODE *head = NULL;


void insert(char fn[], char ln[], int age);
void show();
void show_age(int search_num);
void delete(char *fn, char *ln);
int check_duplicate(char *fn, char *ln);


int main() {
	int command;
	int flag = 0;
	
	char fn[20];
	char ln[20];
	int age;
	
	int check_number;
	
	while(flag == 0) {
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
				printf("Enter first name:\n");
				scanf("%s", fn);
				printf("Enter last name:\n");
				scanf("%s", ln);
				printf("Enter age:\n");
				scanf("%i", &age);
				
				insert(fn, ln, age);
				break;
			case 2:
				show();
				break;
			case 3:
				printf("Enter age:\n");
				scanf("%i", &age);
				show_age(age);
				break;
			case 4:
				printf("Enter first name:\n");
				scanf("%s", fn);
				printf("Enter last name:\n");
				scanf("%s", ln);
				
				delete(fn, ln);
				
				break;
			case 0:
				flag = 1;
				break;
				
		}
	}
}

void insert(char fn[], char ln[], int age) { //finished
    
	if (check_duplicate(fn, ln) != -1) {
		printf("Duplicate\n");
		return;
	}
	
	
	NODE *p;
    p = (NODE *)malloc(sizeof(NODE));
    
	if (p == NULL) { //was memory successfully allocated?
		return;
	}
	
	strcpy(p->user_first, fn);
	strcpy(p->user_last, ln);
	p-> user_age = age;
	
	if (head == NULL) {
		p -> next = NULL;
		head = p;
	} else {
		p-> next = head;
		head = p;
	}
	
	
}

void show() { //finished
	NODE *p;
	p = head;
	
	while (p != NULL) {
		printf("%s %s, %i\n", p->user_first, p-> user_last, p->user_age);
		p = p->next;
	}
}

void show_age(int search_num) { //finished
	NODE *p;
	p = head;
	
	while (p != NULL) {
		if (p->user_age == search_num) {
			printf("%s %s, %i\n", p->user_first, p-> user_last, p->user_age);
		}
		p = p-> next;
	}
}

void delete(char *fn, char *ln) {
	NODE *p, *q;
	p = q = head;
	
	int i;
	int result = check_duplicate(fn, ln);
	printf("%i\n", result);
	
	if (result != -1) {
		if (result == 0) { //if we're deleting first element
			head = p -> next; //new head
			free(q);
			return;
		} else {
			for (i = 0; i < result - 1; i++) {
				q = q->next; //navigate to the node to be deleted, minus 1
			}
			p = q; //set our "previous" helper pointer
			p = p->next; //set p pointer to be node to be deleted
		}
	} else {
		printf("Not found\n");
		return;
	}
	q->next = p->next;
	free(p);
}

int check_duplicate(char *fn, char *ln) {
	NODE *p;
	p = head;
	int ctr = 0;
	
	while (p != NULL) {
		if (strcmp(fn, p->user_first) == 0) {
			if (strcmp(ln, p-> user_last) == 0) {
				return ctr;
			}
		}
		ctr++;
		p = p->next;
	}
	ctr = -1;
	return ctr;
}


