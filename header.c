#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	if (fh == NULL) { printf("Couldn't open the file\n"); return 1; }
	while (count < 100) {
		int result = fscanf(fh, "%d %*d.%*d.%*d %49s", &ftovar.polka, ftovar.name);
		if (result == EOF) {
			break;
		}
		arr[count] = ftovar;
		count++;
	}
	fclose(fh);
	count = process(arr, count, result);
	return count;
}

//  сортировка пузырьком от Евстифеева Марина
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
void my_fprint(struct result results[], int count)
{
	FILE* out = fopen("out.txt", "w");
	if (!out) {
		printf("Couldn't open the file\n");
		return;
	}
	fprintf(out, "Название груза\t\tКоличество стеллажей\n");
	for (int i = 0; i < count; i++) {
		fprintf(out, "%s\t\t%d\n", results[i].name, results[i].polka_count);
	}
	fclose(out);
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
	/*my_sort(results, result_count);
	my_fprint(results, result_count);*/
}

//  от Евстифеева Марина (пункт 9)
//  меняем функцию чтоб выводила по страничкам
//  макет вывода данных:
//  Страница 1
//  Название груза    Количество стеллажиков
//  =========================================
//  Фрукты всякие, продукты      количество стеллажей
void print_file_pagik_trushniy(struct result results[], int count) {
		FILE* out = fopen("out.txt", "w");
		if (!out) {
			printf("Couldn't open the file\n");
			return ;
		}
		int page_size = 3;  
		int line = 0;
		int page = 1;

		for (int i = 0; i < count; i++) {

			if (line % page_size == 0) {
				fprintf(out, "\nСтраница %d\n", page++);
				fprintf(out, "Название груза\t\tКоличество стеллажей\n");
				fprintf(out, "========================================\n");
			}

			fprintf(out, "%-20s %5d\n",
				results[i].name,
				results[i].polka_count); 
			line++;
		}

		fclose(out);
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

//  пункт 4. Замена строчки от Евстифеева Марина
//  если речь о перезаписи в строчке то тут проблемка, ибо в C нельзя перезаписать строчку если длинна отличается
//  я попробую накидать, но по сути чтоб перезаписать надо тупо файл пересоздавать
void replacee() {
		FILE* in = fopen("in.txt", "r");
		FILE* out = fopen("out.txt", "w");
		if (!in || !out) {
			printf("Couldn't open the file\n");
			if (in) fclose(in);
			if (out) fclose(out);
			return;
		}
		char line[256];
		char new_namik[100];
		int new_count;
		int chosen_line;
		int now_line = 0;

		printf("Enter the number of the line you want to replace: ");
		scanf("%d", &chosen_line);
		printf("Enter a new cargo name: ");
		scanf("%99s", new_namik);
		printf("Enter a new number of shelves: ");
		scanf("%d", &new_count);


		while (fgets(line, sizeof(line), in)) {
			if (now_line < 2) {
				fputs(line, out);
			}
			else {
				int data_ind = now_line - 2;
				if (data_ind == chosen_line - 1) {
					fprintf(out, "%-20s %5d\n", new_namik, new_count);
				}
				else {
					fputs(line, out);
				}
			}
			now_line++;
		}
		fclose(in);
		fclose(out);
		remove("in.txt");
		rename("out.txt", "in.txt");
	}

//  от Евстифеева Марина (пункт 2)
// Удалить строчку по ключу

//  от Евстифеева Марина (пункт 2 )
//Добавить строчку в массив