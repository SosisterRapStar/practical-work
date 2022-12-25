#include <iomanip>
#include <iostream>
#include <Windows.h>

using namespace std;


// функция, которая вывводит массив зигзагом

void zigzag(int arr3[10][10], int arr[10][10], int size) { //слева пустой массив 

	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	destCoord.X = 0;
	destCoord.Y = 0;
	SetConsoleCursorPosition(hStdout, destCoord);





	int columnChanges = 0;
	int stepZigzag = 0;



	int* ppp = &arr[0][0];
	int spacex = 0;
	for (int l = 0; l < size; l++) {
		if (stepZigzag % 2 == 0) {

			for (int g = 0; g < size; g++) {
				arr3[g][columnChanges] = *(ppp);
				destCoord.X = columnChanges + spacex;
				destCoord.Y = g + g + 4;
				SetConsoleCursorPosition(hStdout, destCoord); // отвечает за вывод на экран чисел в нужном порядке
	
				Sleep(10);
				cout << *ppp;
				ppp += 1;


			}
			spacex += 3;
		}
		else {

			for (int jj = size - 1; jj > -1; jj--) {
				arr3[jj][columnChanges] = *(ppp);
				destCoord.X = columnChanges + spacex;
				destCoord.Y = jj + jj + 4;
				SetConsoleCursorPosition(hStdout, destCoord);
				Sleep(10);

				cout << *ppp;
				ppp += 1;

			}
			spacex += 3;
		}
		columnChanges += 1;
		stepZigzag += 1;
	}

	destCoord.X = 0;
	destCoord.Y = 18;
	SetConsoleCursorPosition(hStdout, destCoord);

}


// изменение положения блоков матрицы, которое производится через индексы, меняет левые и правые блоки
void left_rightSwap (int arr[10][10], int size) {
	for (int h = 0; h < size / 2; h++) {
		for (int k = 0; k < size / 2; k++) {
			swap(arr[k][h], arr[k][h + (size / 2)]);
			swap(arr[k + (size / 2)][h], arr[k + (size / 2)][h + (size / 2)]);
		}
	}

}

// меняет верхние и нижние блоки
void up_downSwap(int arr[10][10], int size) {
	for (int h = 0; h < size / 2; h++) {
		for (int k = 0; k < size / 2; k++) {
			swap(arr[h][k], arr[h + (size / 2)][k]);
			swap(arr[h][k + (size / 2)], arr[h + (size / 2)][k + (size / 2)]);
		}
	}

}


// меняет блоки крест-накрест
void left_down_rightSwap(int arr2[10][10], int size) {
	for (int h = 0; h < size / 2; h++) {
		for (int k = 0; k < size / 2; k++) {
			swap(arr2[k][h], arr2[k + (size / 2)][h + (size / 2)]);
			swap(arr2[k + (size / 2)][h], arr2[k][h + (size / 2)]);
		}
	}
}

//  меняет блоки по-спирали (пункт а)
void swapBySpiral(int arr3[10][10], int nn) {

	for (int h = 0; h < nn / 2; h++) {
		for (int k = 0; k < nn / 2; k++) {
			swap(arr3[h][k + (nn / 2)], arr3[h + (nn / 2)][k + (nn / 2)]);
		}
	}
	for (int h = 0; h < nn / 2; h++) {
		for (int k = 0; k < nn / 2; k++) {
			swap(arr3[k][h], arr3[k][h + (nn / 2)]);
		}
	}
	for (int h = 0; h < nn / 2; h++) {
		for (int k = 0; k < nn / 2; k++) {
			swap(arr3[h][k], arr3[h + (nn / 2)][k]);
		}
	}
}



//выводит матрицу на экран
void matrixOutPut(int arr[10][10], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << arr[i][j] << '\t';


		}
		cout << '\n';
	}

	cout << '\n';
	cout << '\n';
	cout << '\n';
}



// сортировка 2мерного массива
void bubbleSort(int arr[10][10], int size)
{
	if (size == 6) {
		int arr2[6][6];
		int* s = &arr2[0][0];
		int* end = &arr[9][9];
		for (int* i = &arr[0][0]; i < end; (++i, s++)) {
			if (*i < 0) {
				s--;
			}
			else {
				*s = *i;
			}
		}
		int* end2 = &arr2[size - 1][size - 1];


		
		
		for (int i = 0; i < (size * size); i++) {
			for (int* j = &arr2[0][0]; j < end2; j++) {
				if (*j > *(j + 1))
					swap(*j, *(j + 1));
			}
		}


		

		s = &arr2[0][0];
		int k = 1;
		for (int* i = &arr[0][0]; i < end + 1; (i++, s++)) {
			if (*i < 0) {
				s--;
			}
			else {
				*i = *s;
			}
		}

		 
	 }
	if (size == 8) {
		int arr2[8][8];
		int* s = &arr2[0][0];
		int* end = &arr[9][9];
		for (int* i = &arr[0][0]; i < end; (++i, s++)) {
			if (*i < 0) {
				s--;
			}
			else {
				*s = *i;
			}
		}
		int* end2 = &arr2[size - 1][size - 1];




		for (int i = 0; i < (size * size); i++) {
			for (int* j = &arr2[0][0]; j < end2; j++) {
				if (*j > *(j + 1))
					swap(*j, *(j + 1));
			}
		}


		s = &arr2[0][0];
		int k = 1;
		for (int* i = &arr[0][0]; i < end + 1; (i++, s++)) {
			if (*i < 0) {
				s--;
			}
			else {
				*i = *s;
			}
		}
	}

	if (size == 10) {
		int* end = &arr[size - 1][size - 1];
		for (int i = 0; i < (size * size); i++) {
			for (int* j = &arr[0][0]; j < end; j++) {
				if (*j > *(j + 1))
					swap(*j, *(j + 1));
			}
		}


	}
}



// создает матрицу
void creatMatrix(int arr2[10][10], int size) {
	int* pointerOnMat = &arr2[0][0];
	int* end = &arr2[size-1][size-1];
	for (int* pointerOnMat = &arr2[0][0]; pointerOnMat <= end; pointerOnMat++)
	{
		*pointerOnMat = 0 + rand() % (size * size) + 1;
	}

}


// умножает матрицу на заданное число
void multiplyMatrix(int arr[10][10], int size) {

	cout << "Введите число на которое хотите умножить матрицу" << '\n';
	int number;
	cin >> number;
	int* pointerOnMat = &arr[0][0];
	for (int* end = pointerOnMat + (size * size); pointerOnMat != end; pointerOnMat++)
	{
		*pointerOnMat *= number;
	}

}


// прибавляет к матрице число
void addMatrix(int arr[10][10], int size) {

	cout << "Введите число которое хотите прибавить к матрице" << '\n';
	int number;
	cin >> number;
	int* pointerOnMat = &arr[0][0];
	for (int* end = pointerOnMat + (size * size); pointerOnMat != end; pointerOnMat++)
	{
		*pointerOnMat += number;
	}

	cout << '\n';
	cout << '\n';

	cout << '\n';
}

// делит матрицу на число
void divideMatrix(int arr[10][10], int size) {

	cout << "Введите число на которое хотите разделить матрицу" << '\n';
	int number;
	cin >> number;
	int* pointerOnMat = &arr[0][0];
	for (int* end = pointerOnMat + (size * size); pointerOnMat != end; pointerOnMat++)
	{
		*pointerOnMat /= number;
	}

}

// вычитает из матрицы число
void subtractMatrix(int arr[10][10], int size) {

	cout << "Введите число на которое хотите уменьшить матрицу" << '\n';
	int number;
	cin >> number;
	int* pointerOnMat = &arr[0][0];
	for (int* end = pointerOnMat + (size * size); pointerOnMat != end; pointerOnMat++)
	{
		*pointerOnMat -= number;
		
	}

}







int main() {
	setlocale(0, "Rus");
	srand(time(0));

	int size;
	cout << "Введите размер матрицы (6, 8, 10): ";
	cin >> size;
	cout << '\n';
	if (size != 8 and size != 6 and size != 10) {
		cout << "Вы ввели неправильный размер матрицы";
		return 1;
	}
	

	int arr[10][10];
	int arr2[10][10];
	
	creatMatrix(arr, size);
	zigzag(arr2, arr, size);


	cout << "Выберете, как хотите поменять блоки матрицы: \n";
	cout << "1 - По спирали\n";
	cout << "2 - Верхине и нижние\n";
	cout << "3 - Левые и правые\n";
	cout << "4 - Крест - накрест\n";

	int s;
	cin >> s;
	switch (s)
	{
	case 1:
		swapBySpiral(arr2, size);
		matrixOutPut(arr2, size);
		break;
	case 2:
		up_downSwap(arr2, size);
		matrixOutPut(arr2, size);
		break;
	case 3:
		left_rightSwap(arr2, size);
		matrixOutPut(arr2, size);
		break;
	case 4:
		left_down_rightSwap(arr2, size);
		matrixOutPut(arr2, size);
		break;
	}

	cout << "Сортировка матрицы \n";

	bubbleSort(arr2, size);

	matrixOutPut(arr2, size);

	cout << "Выберете операцию над матрицей: \n";
	cout << "1 - Прибавление числа\n";
	cout << "2 - Умножение на другое число\n";
	cout << "3 - Вычитание\n";
	cout << "4 - Деление\n";

	int ss;
	cin >> ss;
	switch (ss)
	{
	case 1:
		addMatrix(arr2, size);
		matrixOutPut(arr2, size);
		break;
	case 2:
		multiplyMatrix(arr2, size);
		matrixOutPut(arr2, size);
		break;
	case 3:
		subtractMatrix(arr2, size);
		matrixOutPut(arr2, size);
		break;
	case 4:
		divideMatrix(arr2, size);
		matrixOutPut(arr2, size);
		break;
	}



}
