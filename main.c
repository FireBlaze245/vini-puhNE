/*Носорев Даниил Евстифеева Марина
Носорев делает main.c с построением логики и реализации функций сохранить в массив из файла
евстифеева делает реализацию функций в header.c
набросан шаблоны и макет будующих функций
реализация всего на 50% заняло 1.5 часа. Будем ДОДЕЛЫВАЬТЬ */
//В базе данных склада содержатся сведения о грузах и размещении на стеллажах.
//Структура входного файла in.txt (Номер стеллажа Дата укладки Название груза)
//1 25.10.2022 Printer_HP
//1 25.10.2022 Monitor_Samsung
//2 24.10.2022 Monitor_Samsung
//1 26.10.2022 Printer_HP
//3 25.10.2022 Monitor_Samsung
//2 26.10.2022 Printer_HP
//4 24.10.2022 Scanner_Canon
//3 26.10.2022 Scanner_Canon
//1 27.10.2022 Scanner_Canon
//5 25.10.2022 Keyboard_Logitech
//3 27.10.2022 Keyboard_Logitech
//2 28.10.2022 Mouse_Logitech
//4 25.10.2022 Mouse_Logitech
//Сформировать список наименований груза с указанием числа использованных
//стеллажей, упорядочив по наименованию
//Структура выходного файла out.txt
//Название груза Количество стеллажей
//Монитор_Samsung 2
//Принтер_HP 1
/* По своему проекту Винни уровня 3 или 4:
Меню:
0. Выход +
1. Загрузить данные из входного файла в массив структур
2. Добавить строчку в массив
3. Удалить строчку по ключу
4. Заменить строчку
5. Сортировка вставкой +
6. Сортировка выбором  +
7. Сортировка обменом (пузырек) +
8. Сохранить данные в файл
9. Отпечатать файл или массив с разбивкой по страницам и шапкой с номером страницы 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "header.h"




int main(void) {
	int number, counter=0, loaded=0;
	struct result arr[100];
	setlocale(LC_ALL, "");
	number = menu();
	while (number != 0) {
		switch (number) {
		case 1:
			//1. Загрузить данные из входного файла в массив структур
			counter = fsafe(arr);
			loaded = 1;
			break;
		case 2:
			//2. Добавить строчку в массив не сделано
			if (loaded != 1) { printf("First, upload the data (point 1)\n"); break; }
			else { break; }

		case 3:
			//3. Удалить строчку по ключу не сделано
			if (loaded != 1) {printf("First, upload the data (point 1)\n"); break;}
			else { break; }
		case 4:
			//4. Заменить строчку не сделано
			if (loaded != 1) {printf("First, upload the data (point 1)\n"); break;}
			else { break; }
		case 5:
			//5. Сортировка вставкой
			if (loaded != 1) { printf("First, upload the data (point 1)\n"); break;}
			else { sort_input(arr, counter); break;}
		case 6:
			//6. Сортировка выбором
			if (loaded != 1) { printf("First, upload the data (point 1)\n"); break;}
			else { sort_choice(arr, counter); break;}
		case 7:
			//7. Сортировка обменом (пузырек)
			if (loaded != 1) { printf("First, upload the data (point 1)\n"); break;}
			else { bubble_sort(arr, counter); break;}
		case 8:
			//8. Сохранить данные в файл
			if (loaded != 1) { printf("First, upload the data (point 1)\n"); break;}
			else{my_fprint(arr, counter); break;}
		case 9:
			//9. Отпечатать файл или массив с разбивкой по страницам и шапкой с номером страницы, сделано как вывод в файл
			if (loaded != 1) { printf("First, upload the data (point 1)\n"); break;}
			else{print_file_pagik_trushniy(arr, counter);break;}
		case 0:
			//Выход
			break;
		default:
			printf("Input number in range 0 - 9\n");
			break;
		};
		number = menu();
	}
	return 0;
}


