#define NODE struct node
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

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

extern struct array_node database[3];
extern pthread_mutex_t key;
extern pthread_t thread;
extern int key_to_int;

extern void insert(char *fn, char *ln, int age);
extern float check_duplicate(char *fn, char *ln);
extern void delete(char *fn, char *ln);
extern void show();
extern void show_age(int age_to_find);
extern void change_age(char *fn, char *ln, int o_age, int n_age);

extern void read_all(char *fn, int key);
extern void read_all_binary(char *fn);
extern void save_all(char *fn, int key);
extern void *temp_save(void *fn);
