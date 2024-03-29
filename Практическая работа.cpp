﻿
#include <iostream>

using namespace std;
int main() {
	setlocale(0, "Rus");

	cout << "int: " << sizeof(int) << "\n";
	cout << "short: " << sizeof(short int) << "\n";
	cout << "long: " << sizeof(long int) << "\n";
	cout << "float: " << sizeof(float) << "\n";
	cout << "double: " << sizeof(double) << "\n";
	cout << "long double: " << sizeof(long double) << "\n";
	cout << "char: " << sizeof(char) << "\n";
	cout << "bool: " << sizeof(bool) << "\n";


	int mask;
	mask = 1 << (sizeof(int) * 8) - 1; // создаем маску 1000000... и переводим байты в биты
	// сдвигаем 1 на последний бит
	int number; // инициализайия для введенного числа

	cout << "Введите целое число \n";
	cin >> number;


	for (int i = 0; i < sizeof(int) * 8; i++) // условие цикла
	{
		if (i == 1) // разделение разрядов на знак под символ и под значение
			cout << ' ';

		if (number & mask) // сравнение с маской, если значение после конъюкции не 0, то 1 на экран
			cout << '1';

		else
			cout << '0';

		number <<= 1; // сдвиг числа влево

	}

	cout << "\nВведите вещественное число \n";

	union {
		float floatValue; // запись двух переменных в один адрес
		int numberForFloat;
	};

	cin >> floatValue;

	for (int i = 0; i < sizeof(int) * 8; i++) // условие цикла
	{
		if (i == 1 || i == 23) // выделение мантисы и порядка 0 1000011100111010000000 000000000
			cout << ' ';

		if (numberForFloat & mask) // сравнение с маской, если значение после конъюкции не 0, то 1 на экран
			cout << '1';

		else
			cout << '0';

		numberForFloat <<= 1; // сдвиг числа влево
	}

	cout << "\nВведите вещественное число \n";

	union {
		double doubleValue; // запись двух переменных в один адрес
		int listForDouble[2]; // выделения массива, отводится 8 байт на 2 целочисленных числа
	};
	

	cin >> doubleValue; // после ввода, память выделенная для массива заполняется

	for (int i = 0; i < 8 * 8; i++) // в условии содержиться 64 бита, что соответсвует 8 байтам для типа double
	{
		// так как массив заполняет ячейки по порядку, то сначала выведем алгоритм для 0 элемента
		for (; i < 4 * 8; i++) { // программа работает пока i < 32
			if (i == 1)
				cout << ' ';
			if (listForDouble[0] & mask) // сравнение с маской, если значение после конъюкции не 0, то 1 на экран
				cout << '1';

			else
				cout << '0';

			listForDouble[0] <<= 1; // сдвиг числа влево
		}
		// после окончания работы первого цикла, начинается работа с индексом 1 массива

		if (i == 52) // выделение мантисы
			cout << ' ';

		if (listForDouble[1] & mask) // сравнение с маской, если значение после конъюкции не 0, то 1 на экран
			cout << '1';

		else
			cout << '0';

		listForDouble[1] <<= 1; // сдвиг числа влево
	}
}





	






