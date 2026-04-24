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

void my_fprint(struct result results[], int count){
	FILE *out = fopen("out.txt", "w");	
	fprintf(out, "Название груза\t\tКоличестddво стеллажей\n");
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
}

int menu(){
	int number;
	printf("Меню:\n0. Выход\n1. Загрузить данные из входного файла в массив структур\n2. Добавить строчку в массив\n3. Удалить строчку по ключу\n4. Заменить строчку\n5. Сортировка вставкой\n6. Сортировка выбором\n7. Сортировка обменом (пузырек)\n8. Сохранить данные в файл\n9. Отпечатать файл или массив с разбивкой по страницам и шапкой с номером страницы\n");
	scanf("%d", &number);
	switch (number) {
	case 0:
		//0. Выход
		break;
	case 1:
		//1. Загрузить данные из входного файла в массив структур
		break;
	case 2:
		//2. Добавить строчку в массив
		break;
	case 3:
		//3. Удалить строчку по ключу
		break;
	case 4:
		//4. Заменить строчку
		break;
	case 5:
		//5. Сортировка вставкой
		break;
	case 6:
		//6. Сортировка выбором
		break;
	case 7:
		//7. Сортировка обменом (пузырек)
		break;
	case 8:
		//8. Сохранить данные в файл
		break;
	case 9:
		//9. Отпечатать файл или массив с разбивкой по страницам и шапкой с номером страницы
		break;
	default:
		printf("Введите число от 0 до 9\n");
		break;
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
