#include "header.h"

void read_all(char *fn, int key);
void read_all_binary(char *fn);
void save_all(char *fn, int key);
void *temp_save(void *fn);

void read_all(char *fn, int key) { //f

	printf("%i", key);
	
	FILE *fp;
	fp = fopen(fn, "r");
	if (fp == NULL) return;
	
	
	int ctr = 0;
	char first_name[20];
	char last_name[20];
	int age;

	char line[500];
	char *cp;
	
	printf("\n");
	
	while (fgets(line, 500, fp) != NULL) {
		cp = line;
		while (*cp != '\0') {
				*cp = *cp ^ key;
				cp++;
			}
		sscanf(line, "%s %s %i", first_name, last_name, &age);
		insert(first_name, last_name, age);
		ctr++;
	}
	printf("\n");
	printf("Loaded %i entries\n", ctr);
	fclose(fp);
	
}

void save_all(char *fn, int key) {
	NODE *p;
	FILE *fp;
	int i;
	char line[500];
	char *cp;
	
	fp = fopen(fn, "w");
	
	if (fp == NULL) return;
	
	
	for (i = 0; i < 3; i++) {
		p = database[i].head;
		while (p != NULL) {
			sprintf(line, "%s %s %i\n", p->first, p->last, p->age);
			cp = line;
			while (*cp != '\n') {
				*cp = *cp ^ key;
				cp++;
			}
			fprintf(fp, "%s", line);
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