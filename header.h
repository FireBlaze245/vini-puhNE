#ifndef HEADER_H
#define HEADER_H

struct tovar {
	int polka;
	char name[50];
};

struct result {
	char name[50];
	int polka_count;
};

void process(struct tovar ar[], int count, struct result results[]);
void my_sort(struct result results[], int count);
void my_fprint(struct result results[], int count);
void sort_input(struct result results[], int count);
void sort_choice(struct result results[], int count);
int menu();
int fsafe(struct result arr[]);

#endif
