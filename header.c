#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "header.h"

//  от Носорев Даниил
//  вывод меню в терменал
int menu() {
	int number;
	printf("Menu:\n1. Load data from input file into array of structures\n2. Add a row to the array\n3. Delete a row by key\n4. Replace a row\n5. Insertion sort\n6. Selection sort\n7. Bubble sort (exchange sort)\n8. Save data to file\n9. Print file or array with pagination and page number header\n0. Exit\n");
	scanf("%d", &number);
	return number;
}

//  от Носорев Даниил
//  загрузка данных из входного файла 
int fsafe(struct result result[]) {
	struct tovar arr[100];
	struct tovar ftovar;
	int count = 0;
	FILE* fh = fopen("in.txt", "r");
	if (fh == NULL) { printf("Couldn't open the file\n"); return 0; }
	while (count < 100) {
		int result = fscanf(fh, "%d %*d.%*d.%*d %49s", &ftovar.polka, ftovar.name);
		if (result == EOF) break;
		arr[count] = ftovar;
		count++;
	}
	fclose(fh);
	count = process(arr, count, result);
	return count;
}

//  сортировка пузырьком от Носорев Даниил
void bubble_sort(struct result results[], int count) {
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

//  от Носорев Даниил
//  Вывод данных в файл
void my_fprint(struct result results[], int count) {
	FILE* out = fopen("out.txt", "w");
	if (!out) {
		printf("Couldn't open the file\n");
		return;
	}
	fprintf(out, "Cargo name\t\tNumber of shelves\n");
	for (int i = 0; i < count; i++) {
		fprintf(out, "%s\t\t%d\n", results[i].name, results[i].polka_count);
	}
	fclose(out);
	printf("Data saved to out.txt\n");
}

//  от Носорев Даниил
//  преобразвование данных
int process(struct tovar ar[], int count, struct result results[]) {
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
		}
		else {
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
	return result_count;
}

//  от Евстифеева Марина (пункт 9)
//я предполагаю что должно выглядеть так:
//Страница 1
//Название груза    Количество стеллажей
//=========================================
//Продукты           количество стеллажей
//----------------------------------------
//Страница 2 и тд

void print_terminal_pagik_trushniy(struct result results[], int count) {
	int page_size = 3;  //строки на странице
	int line = 0;
	int page = 1;

	for (int i = 0; i < count; i++) {
		if (line % page_size == 0 && line != 0) {
			printf("-------------------------------------------\n");
		}
		// новая страница
		if (line % page_size == 0) {
			printf("\nPage %d\n", page++);
			printf("Cargo name\t\t Number of racks\n");
			printf("========================================\n");
		}

		printf("%-20s %5d\n",//выравнивание текста
			results[i].name,
			results[i].polka_count); //вывод
		line++;

	}
}

//  сортировка выбором оот Евстифеева Марина (6 пункт)
void sort_choice(struct result results[], int count) {
	for (int i = 0; i < count - 1; i++) {
		int min_ind = i;
		for (int j = i + 1; j < count; j++) {
			if (strcmp(results[j].name, results[min_ind].name) < 0) {
				min_ind = j;
			}
		}
		if (min_ind != i) {
			struct result temp = results[i];
			results[i] = results[min_ind];
			results[min_ind] = temp;
		}
	}
}

//  сортировка вставкой от Евстифеева Марина (5 пункт)
void sort_input(struct result results[], int count) {
	for (int i = 1; i < count; i++) {
		struct result key = results[i];
		int j = i - 1;
		while (j >= 0 && strcmp(results[j].name, key.name) > 0) {
			results[j + 1] = results[j];
			j--;
		}
		results[j + 1] = key;
	}
}

//пункт 4. Замена строчки
//если речь о перезаписи в строчке то тут проблема, ибо в C нельзя перезаписать строчку если длинна отличается
//по сути чтоб перезаписать надо тупо файл пересоздавать
void replacee() {
	int line_num;
	printf("Enter line number to replace (1 - first data line): ");
	scanf("%d", &line_num);
	if (line_num < 1) {
		printf("Invalid line number.\n");
		return;
	}

	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("temp.txt", "w");
	if (!in || !out) {
		printf("File opening error\n");
		if (in) fclose(in);
		if (out) fclose(out);
		return;
	}

	int polka, day, month, year, cur = 0;
	char name[50];
	int replaced = 0;

	while (fscanf(in, "%d %d.%d.%d %49s", &polka, &day, &month, &year, name) == 5) {
		cur++;
		if (cur == line_num) {
			printf("Enter new shelf number, date (day month year), and cargo name:\n");
			scanf("%d %d %d %d %49s", &polka, &day, &month, &year, name);
			replaced = 1;
		}
		fprintf(out, "%d %d.%d.%d %s\n", polka, day, month, year, name);
	}
	fclose(in);
	fclose(out);
	if (replaced) {
		remove("in.txt");
		rename("temp.txt", "in.txt");
		printf("Line %d replaced.\n", line_num);
	}
	else {
		remove("temp.txt");
		printf("Line %d not found.\n", line_num);
	}
}

//от Евстифеева Марина Пункт 3. удаление строчки по ключу
//По сути пишется так же как замена, только при перезаписи файла пропускать указанную строчку
void deletik() {
	char key[50];
	printf("Enter cargo name to delete: ");
	scanf("%49s", key);

	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("temp.txt", "w");
	if (!in || !out) {
		printf("File opening error\n");
		if (in) fclose(in);
		if (out) fclose(out);
		return;
	}

	int polka, day, month, year, deleted = 0;
	char name[50];
	while (fscanf(in, "%d %d.%d.%d %49s", &polka, &day, &month, &year, name) == 5) {
		if (strcmp(name, key) != 0) {
			fprintf(out, "%d %d.%d.%d %s\n", polka, day, month, year, name);
		}
		else {
			deleted++;
		}
	}
	fclose(in);
	fclose(out);
	remove("in.txt");
	rename("temp.txt", "in.txt");
	printf("Deleted %d row(s).\n", deleted);
}

//  от Носорев Даниил (пункт 2)
//Добавить строчку в массив
void adding() {
	int polka, day, month, year;
	char name[50];
	printf("Enter shelf number: ");
	scanf("%d", &polka);
	printf("Enter date (day month year separated by spaces): ");
	scanf("%d %d %d", &day, &month, &year);
	printf("Enter cargo name: ");
	scanf("%49s", name);

	FILE* f = fopen("in.txt", "a");
	if (!f) {
		printf("File opening error in.txt\n");
		return;
	}
	fprintf(f, "%d %d.%d.%d %s\n", polka, day, month, year, name);
	fclose(f);
	printf("Row added.\n");
}
