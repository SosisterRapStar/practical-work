#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;
void printMenu();
float median(int* arr);

//чтобы сделать работу с файлом, необходимо поместить файл в папку с проектом
struct  Student {
	string fullName = "";
	string sex = "";
	long int group = 0000;
	int id = 0;
	int marks[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	float rating;
	string writeToFile() {
		string a = fullName + "\n";
		string c = sex + "\n";
		string d = to_string(group) + "\n";
		string b = to_string(id) + "\n";
		string cc;
		for (int i = 0; i < 8; i++) {
			cc += to_string(marks[i]) + "\n";
		}

		string full = a + c + d + b + cc;
		return full;
	}
	void printInfo() {
		cout << '\n' << "-------------------------------------------" << '\n';
		cout << "ФИО: " << fullName << '\n';
		cout << "Номер в группе: ";
		cout << id << "\n";
		cout << "Пол: ";
		cout << sex << "\n";
		cout << "Группа: ";
		cout << group << "\n";
		cout << "Оценки:";
		for (int i = 0; i < 8; i++) {
			cout << marks[i] << " ";
		}
		cout << '\n';
		cout << rating << "\n";
	}

};

struct DataBase {

	int dinamycSize = 8;   
	int usedMemory = -1;
	Student* base = new Student[dinamycSize];

	int put(Student student) {
		for (int i = 0; i < 8; i++) {
			if (student.marks[i] == 2) {
				return 1;
			}
		}
		usedMemory += 1;
		base[usedMemory] = student;

		if ((float)usedMemory / dinamycSize >= 0.75) {
			this->rebuildBase();

		}
		return 0;

	}

	void printInfo() {
		for (int i = 0; i < usedMemory + 1; i++) {
			base[i].printInfo();
		}

	}
	void writeToFile(ofstream* baseFile) {
		for (int i = 0; i < usedMemory + 1; i++) {
			*baseFile << base[i].writeToFile();
		}

	}
	void exit() {
		delete[] base;

	}
	void getRecordByGroup(int a) {
		bool flag = false;
		cout << "\033[38;2;0;165;mИнформация о студентах группы:" << a << "\033[0m \n";
		for (int i = 0; i < usedMemory + 1; i++) {
			if (base[i].group == a) {
				flag = true;
				base[i].printInfo();
			}
		}
		if (!flag) {
			cout << "Информации о данной группе нет.";
		}
	}

	int creatRecord() {
		Student newStudent;
		cin.ignore();
		cout << "Введите имя студента: ";
		getline(cin, newStudent.fullName);
		cout << '\n';
		cout << "Введите пол студента(male/female): ";
		getline(cin, newStudent.sex);
		cout << '\n';
		cout << "Введите номер группы: ";
		cin.ignore();
		cin >> newStudent.group;
		cout << '\n';
		cout << "Введите номер в списке группы: ";
		cin >> newStudent.id;
		cout << '\n';
		cout << "Оценки за сессию: \n";
		int mark;
		cout << "Введите оценки:\n";
		for (int i = 0; i < 8; i++) {
			int mark = 0;
			while (mark < 3 or mark > 5) {
				cout << "Оценка " << i + 1 << ": ";
				cin >> mark; cout << '\n';
				if (mark == 2) {
					cout << "\033[34;1;4mСтудента не удается добавить в базу, так как он получил 2ку\033[0m\n";
					return 1;
				}
				else if (mark < 2 or mark > 5) {
					cout << "Вы ввели неправильное число\n";
				}
				
			}
			newStudent.marks[i] = mark;
		}

		cout << '\n';
		newStudent.rating = median(newStudent.marks);
		this->put(newStudent);
		cout << "\033[34;1;4mУспешно добавлена запись\033[0m\n";
		return 0;
	}
	void getRecordById(int a) {
		cout << "\033[38;2;0;165;mИнформация о студентах c номером:" << a << "\033[0m \n";
		for (int i = 0; i < usedMemory + 1; i++) {
			if (base[i].id == a) {
				base[i].printInfo();
			}
		}
	}
	void getLastRecord() {
		base[usedMemory].printInfo();
	}
	int getRecordByKeyId(int keyId) {
		if (keyId > usedMemory) {
			cout << "\033[34;1;4mТакой записи не было добавлено\033[0m\n";
			return 1;
		}
		base[keyId].printInfo();
		return 0;
	}
	void rating() {
		for (int i = 0; i < usedMemory + 1; i++) {
			for (int n = 0; n < usedMemory - 1 - i; n++) {
				if (base[n].rating > base[n + 1].rating) {
					swap(base[n], base[n + 1]);
				}
			}
		}
		for (int i = 0; i < usedMemory + 1; i++) {
			cout << "-----" << i + 1 << "-----" << base[i].fullName << "\n";
		}
	}

	int changeStudent() {
		int i = this->findStudent();
		if (i == -1) {
			return 1;
		}
		Student* changeSt = &base[i];
		bool exit = false;
		i = 0;
		while (i != 6) {

			printMenu();
			cout << "Выберите пункт меню: "; cin >> i;
			switch (i)
			{
			case 1:
				cin.ignore();
				system("CLS");
				cout << "Введите новое имя: ";
				getline(cin, changeSt->fullName);
				break;
			case 2:
				system("CLS");
				cin.ignore();
				cout << "Введите пол: ";
				getline(cin, changeSt->sex);
				break;
			case 3:
				system("CLS");

				cout << "Введите новую группу: ";
				cin >> changeSt->group;
				break;
			case 4:
				system("CLS");

				cout << "Введите новый номер: ";
				cin >> changeSt->id;

				break;
			case 5:
				system("CLS");

				int mark;
				cout << "Введите оценки\n";
				for (int i = 0; i < 8; i++) {
					int mark = 0;
					while (mark < 1 or mark > 5) {
						cout << "Оценка " << i + 1 << ": ";
						cin >> mark; cout << '\n';
						if (mark < 3 or mark > 5) {
							cout << "Вы ввели неправильное число\n";
						}


					}
					changeSt->marks[i] = mark;
				}

				break;


			}
		}
	}


	int findStudent() {
		int group;
		int id;
		cout << "Введите группу студента: ";
		cin >> group; cout << "\n";
		cout << "Введите номер в списке: ";
		cin >> id; cout << "\n";
		int gflag = false;
		for (int i = 0; i < usedMemory + 1; i++) {
			if (base[i].group == group) {
				gflag = true;
				if (base[i].id == id) {
					return i;
				}
			}
		}
		if (!gflag) {
			cout << "\033[34;1;4mТакой группы не найдено\033[0m\n";
			return -1;
		}
		cout << "\033[34;1;4mТакого номера в списке не найдено\033[0m\n";
		return -1;
	}
	void maleFemale() {
		int counterMale = 0;
		int counterFemale = 0;
		for (int i = 0; i < usedMemory + 1; i++) {

			if (base[i].sex == "male") {
				counterMale += 1;
			}
			else if (base[i].sex == "female") {
				counterFemale += 1;
			}
		}
		cout << "Студентов мужского пола: " << counterMale << "    " << "Студентов женского пола: " << counterFemale << "\n";
	}
	void excelentStudents() {
		for (int i = 0; i < usedMemory + 1; i++) {
			int fiveCounter = 0;
			int fourCounter = 0;
			int threeCounter = 0;
			for (int n = 0; n < 8; n++) {
				if (base[i].marks[n] == 5) {
					++fiveCounter;
				}
				else if (base[i].marks[n] == 4) {
					++fourCounter;
				}
				else if (base[i].marks[n] == 3) {
					++threeCounter;
				}
			}
			if (fiveCounter > 0 && fourCounter == 0 && threeCounter == 0) {
				base[i].printInfo();
			}
		}

	}
	void goodStudents() {
		for (int i = 0; i < usedMemory + 1; i++) {
			int fiveCounter = 0;
			int fourCounter = 0;
			int threeCounter = 0;
			for (int n = 0; n < 8; n++) {
				if (base[i].marks[n] == 5) {
					++fiveCounter;
				}
				else if (base[i].marks[n] == 4) {
					++fourCounter;
				}
				else if (base[i].marks[n] == 3) {
					++threeCounter;
				}
			}
			if (fiveCounter > 0 && fourCounter > 0 && threeCounter == 0) {
				base[i].printInfo();
			}
		}

	}
	void normalStudents() {
		for (int i = 0; i < usedMemory + 1; i++) {
			int fiveCounter = 0;
			int fourCounter = 0;
			int threeCounter = 0;
			for (int n = 0; n < 8; n++) {
				if (base[i].marks[n] == 5) {
					++fiveCounter;
				}
				else if (base[i].marks[n] == 4) {
					++fourCounter;
				}
				else if (base[i].marks[n] == 3) {
					++threeCounter;
				}
			}
			if (fiveCounter > 0 && fourCounter > 0 && threeCounter > 0) {
				base[i].printInfo();
			}
		}

	}

private:
	void rebuildBase() {
		dinamycSize *= 2;
		Student* base2 = new Student[dinamycSize];
		for (int i = 0; i < usedMemory + 1; i++) {
			base2[i] = base[i];
		}
		Student* a = base;
		base = base2;
		delete[] a;
	}

};



void printMenu() {
	system("CLS");
	cout << "1 Изменить имя. \n";
	cout << "2 Изменить пол. \n";
	cout << "3 Изменить номер группы. \n";
	cout << "4 Изменить номер в списке. \n";
	cout << "5 Изменить оценки. \n";
	cout << "6 Выйти \n";
}


int countLines(string fileName) {
	ifstream infile;
	infile.open(fileName);
	if (!infile.is_open()) {
		cout << "\033[34;1;4mБрат, ошибка нет файла\033[0m\n";
	}
	else {
		if (infile.is_open())
		{
			string data;
			int temp = 0;
			while (!infile.eof())
			{
				getline(infile, data);
				temp++;
			}
			infile.close();
			int n;
			n = temp / 12;
			return n;
		}
	}

}

float median(int* arr) {
	float summ = 0;
	for (int i = 0; i < 8; i++) {
		summ += arr[i];
	}
	return summ / 8;
}

void readFromFile(DataBase* dName, string fileName) {

	ifstream infile;
	infile.open(fileName);
	if (!infile.is_open()) {
		cout << "\033[34;1;4mФайл не найден\033[0m\n";
	}
	else {
		string data;
		int temp = countLines(fileName);
		if (temp != 0){
			for (int i = 0; i < temp; i++) {
				Student newStudent;
				getline(infile, newStudent.fullName);

				getline(infile, newStudent.sex);

				getline(infile, data);
				newStudent.group = stoi(data);

				getline(infile, data);
				newStudent.id = stoi(data);

				getline(infile, data);
				newStudent.marks[0] = stoi(data);


				getline(infile, data);
				newStudent.marks[1] = stoi(data);

				getline(infile, data);
				newStudent.marks[2] = stoi(data);

				getline(infile, data);
				newStudent.marks[3] = stoi(data);

				getline(infile, data);
				newStudent.marks[4] = stoi(data);

				getline(infile, data);
				newStudent.marks[5] = stoi(data);

				getline(infile, data);
				newStudent.marks[6] = stoi(data);

				getline(infile, data);
				newStudent.marks[7] = stoi(data);
				newStudent.rating = median(newStudent.marks);
				dName->put(newStudent);
			}
		}

	}
}


void writeBaseInFile(DataBase* databaseName, string a) {
	ofstream baseFile;
	baseFile.open(a, ofstream::app);
	if (!baseFile.is_open()) {
		cout << "\033[34;1;4mБрат, ошибка нет файла\033[0m\n";
	}
	else {

		databaseName->writeToFile(&baseFile);
		cout << "\033[38;2;0;165;80mИнформация успешно выведена в файл\033[0m\n";
	}
	baseFile.close();
}


int cleanfile(string a) {
	ofstream file(a);
	if (!file.is_open()) {
		cout << "\033[34;1;4mБрат, ошибка нет файла\033[0m\n";
		return 1;
	}
	file << "";
	file.close();
	return 0;
}

void printMainMenu() {
	system("CLS");
	cout << "1-Создать новую запись о студенте\n";
	cout << "2-Импорт данных из стороннего файла со студентами\n";
	cout << "3-Внести изменения в запись\n";
	cout << "4-Вывод всех данных о студентах.\n";
	cout << "5-Вывод информации обо всех студентах группы N.\n";
	cout << "6-Вывод топа самых успешных студентов.\n";
	cout << "7-Вывод количества студентов мужского и женского пола.\n";
	cout << "8-Вывод студентов без стипендии \n";
	cout << "9-Вывод студентов, которые учатся только на хорошо и отлично\n";
	cout << "10-Вывод студентов, которые учатся на отлично\n";
	cout << "11-Вывод студентов с номером K в списке\n";
	cout << "12-Выход\n";

}


int main(void)
{


	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "Rus");
	DataBase data;
	readFromFile(&data, "DataBase.txt");
	int i = 0;
	string fileName;
	while (i != 12)
	{
		printMainMenu();
		cout << "Введите пункт: ";
		cin >> i;
		switch (i)
		{
		case 1:
			system("CLS");
			data.creatRecord();
			system("pause");
			break;
		case 2:
			cin.ignore();

			system("CLS");
			cout << "Введите имя файла, файл должен быть в корневой папке: ";
			getline(cin, fileName);
			readFromFile(&data, fileName);
			writeBaseInFile(&data, "DataBase.txt");
			system("pause");
			break;
		case 3:
			data.changeStudent();
			system("pause");
			break;

		case 4:
			system("CLS");
			data.printInfo();
			system("pause");
			break;
		case 5:
			system("CLS");
			int group;
			cout << "Введите группу: "; cin >> group; cout << "\n";
			data.getRecordByGroup(group);
			system("pause");
			break;
		case 6:
			system("CLS");
			data.rating();
			system("pause");
			break;
		case 7:
			system("CLS");
			data.maleFemale();
			system("pause");
			break;
		case 8:
			system("CLS");
			data.normalStudents();
			system("pause");
			break;
		case 9:
			system("CLS");
			data.goodStudents();
			system("pause");
			break;

		case 10:
			system("CLS");
			data.excelentStudents();
			system("pause");
			break;
		case 11:
			system("CLS");
			int id;
			cout << "Введите номер в списке: "; cin >> id; cout << "\n";
			data.getRecordById(id);
			system("pause");
			break;
		case 12:
			cleanfile("DataBase.txt");
			writeBaseInFile(&data, "DataBase.txt");
			data.exit();
		}
	}
}

