#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void my_sort(struct result results[], int count) {
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


void my_fprint(struct result results[], int count)
{
	FILE* out = fopen("out.txt", "w");
	fprintf(out, "Название груза\t\tКоличество стеллажей\n");
	for (int i = 0; i < count; i++) {
		fprintf(out, "%s\t\t%d\n", results[i].name, results[i].polka_count);
	}
	fclose(out);
}
//погоди даня а где обработка ошибки открытия файла??

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

	my_sort(results, result_count);
	my_fprint(results, result_count);

	//от мариооо (пункт 9)
	//меням функцию чтоб выводила по страничкам
	//я предполагаю что должно выглядеть так:
	//Страница 1
	//Название груза    Количество стеллажиков
	//=========================================
	//Фрукты всякие, продукты      количество стеллажей

	//а ля я туплю надо переделать, че я вообще написала
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
				printf("\nСтраница %d\n", page++);
				printf("Название груза\t\tКоличество стеллажей\n");
				printf("========================================\n");
			}

			printf("%-20s %5d\n",
				results[i].name,
				results[i].polka_count); //-20 эт выравнивание текста шоб по красоте
			line++;
			
		}
	}

	//сортировка выбором от мариоооо (6 пункт)
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
	//сортировка вставкой от мариоооо (5 пункт)
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
	//если речь о перезаписи в строчке то тут проблемка, ибо в C нельзя перезаписать строчку если длинна отличается
	//я попробую накидать, но по сути чтоб перезаписать надо тупо файл пересоздавать

	void replacee() {
		FILE* in = fopen("in.txt", "r");
		FILE* out = fopen("out.txt", "w");
		//дальше обработочка ошибочки
		if (!in || !out) {
			printf("Ошибка открытия файла\n");
			if (in) fclose(in);
			if (out) fclose(out);
			return;
		}
		char line[256];
		char new_namik[100]; 
		int new_count;
		int chosen_line;
		int now_line = 0;

		printf("Введите номер строки, которую хотите заменить: ");
		scanf("%d", &chosen_line);
		printf("Введите новое название груза: ");
		scanf("%99s", new_namik);
		printf("Введите новое количество стеллажей: ");
		scanf("%d", &new_count);


		while (fgets(line, sizeof(line), in)) { //чтение файла построчно
			if (now_line < 2) { //первые две строки это загооловочки, их коп без изм
				fputs(line, out);
			}
			else {
				int data_ind = now_line - 2; //делаем строчку с данными так, чтобы отсчитывался от 0, а не от 2
				if (data_ind == chosen_line - 1) { //замена строчки, -1 потому что польз вводит с 1, а массив должен быть с 0
					fprintf(out, "%-20s %5d\n", new_namik, new_count);
				}
				else { //другие строчечки копируются просто
					fputs(line, out);
				}
			}
			now_line++;
		}
		fclose(in);
		fclose(out);
		remove("in.txt"); //удаляем старый интик
		rename("out.txt", "in.txt"); //перезаписываем изменённый в интик
	}

	//Пункт 3. удаление строчки по ключууу
	//По сути пишется так же как замена, ток моя идея в том, чтобы при
	//перезаписи файла пропускать указанную строчку
	void deletik() {
		FILE* in = fopen("in.txt", "r");
		FILE* out = fopen("out.txt", "w");

		if (!in || !out) {
			printf("Ошибка открытия файла\n");
			if (in) fclose(in);
			if (out) fclose(out);
			return;
		}

		char line[256];
		char name[100];
		int count;
		char key[100];

		printf("Введите название груза для удаления: ");
		scanf("%99s", key);

		int now_line = 0;

		while (fgets(line, sizeof(line), in)) {
			if (now_line < 2) {
				// копируем заголовок
				fputs(line, out);
			}
			else {
				// читаем строку с данными
				if (sscanf(line, "%99s %d", name, &count) == 2) {
					// если не совпадает — записываем
					if (strcmp(name, key) != 0) {
						fputs(line, out);
					}
					// если совпадает удаляем
				}
				else {
					// если строка упоротая
					fputs(line, out);
				}
			}
			now_line++;
		}

		fclose(in);
		fclose(out);

		// заменяем файл
		remove("in.txt");
		rename("out.txt", "in.txt");

		printf("Удалено.\n");
	}

		//можно ещё сделать по другому чутка, чтоб оно ток одну строчку такю удаляло
		/*int deletik_only_one = 0;
		if (strcmp(name, key) == 0 && !deletik_only_one) {
			deletik_only_one = 1;
			continue;
		}*/


