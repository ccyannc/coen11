#include "header.h"

void insert(char *fn, char *ln, int age);
float check_duplicate(char *fn, char *ln);
void delete(char *fn, char *ln);
void show();
void show_age(int age_to_find);
void change_age(char *fn, char *ln, int o_age, int n_age);

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