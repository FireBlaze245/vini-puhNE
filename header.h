#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tovar {
	int polka;
	char name[50];
};

struct result {
	char name[50];
	int polka_count;
};

void process(struct tovar ar[], int count);
void my_sort(struct result results[], int count);
void my_fprint(struct result results[], int count);
void sort_choise(struct result results[], int count);
void sort_input(struct result results[], int count);
int menu();



/*void my_sort(struct result results[], int count) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (strcmp(results[i].name, results[j].name) > 0) {
				struct result temp = results[i];
				results[i] = results[j];
				results[j] = temp;
			}
		}
	}
}

void my_fprint(struct result results[], int count){
	FILE *out = fopen("out.txt", "w");	
	fprintf(out, "Название груза\t\tКоличество стеллажей\n");
	for (int i = 0; i < count; i++) {
		fprintf(out, "%s\t\t%d\n", results[i].name, results[i].polka_count);}
	fclose(out);
}

void process(struct tovar ar[], int count) {
	struct result results[100];
	int result_count = 0;
	for (int i = 0; i < count; i++) {
		int found = -1;
		for (int j = 0; j < result_count; j++) {
			if (strcmp(results[j].name, ar[i].name) == 0) {
				found = j;
				break;
			}
		}
		if (found == -1) {
			strcpy(results[result_count].name, ar[i].name);
			results[result_count].polka_count = 1;
			result_count++;
		} else {
			int shelf_exists = 0;
			for (int k = 0; k < i; k++) {
				if (strcmp(ar[k].name, ar[i].name) == 0 && ar[k].polka == ar[i].polka) {
					shelf_exists = 1;
					break;
				}
			}
			if (!shelf_exists) {
				results[found].polka_count++;
			}
		}
	}
	
	my_sort(results, result_count);
	my_fprint(results, result_count);
}*/

#endif
