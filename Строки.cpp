#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;





//возвращает настоящую длину массива, нужно для оптимизации массива
int realLength(string* arr, int size) {
    int length = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] != "NULL") {
            length++;
        }
        else {
            return length;
        }
        
    }
    
}


//разделяет строку в массив по знаку
string* split(string str, char delim, int& size) {
    size = 1000;
    str += delim;
    string* array = new string[size];
    for (int i = 0; i < size; i++) {
        array[i] = "NULL";
    }
    string word = "";
    int k = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != delim) {
            word += str[i];
        }
        else {
            
            array[k] = word;
            k++;
            word = "";
        }
    }
    size = realLength(array, size);
    string* newArr = new string[size];
    for (int i = 0; i < size; i++) {
        newArr[i] = array[i];
    }
    delete[] array;
    return newArr;
}



//объединяет массив строк в строку чреез знак
string join(string* str,  char del, int& size) {
    string stroka = "";
    for (int i = 0; i < size; i++) {

        stroka += str[i] + del;
    }
    size = stroka.length();
    return stroka;
}






//удаляет вообще все знаки, нужно для заданий, где выводятся только слова
void deleteAllSignesAndDots(string& str) {
    
    while (str.find(",") != -1) {
        str.replace(str.find(","), 1, " ");
    }

    while (str.find("?") != -1) {
        str.replace(str.find("?"), 1, " ");
    }

    while (str.find("!") != -1) {
        str.replace(str.find("!"), 1, " ");
    }

    while (str.find("-") != -1) {
        str.replace(str.find("-"), 1, " ");
    }

    while (str.find(".") != -1) {
        str.replace(str.find("."), 1, " ");
    }

    while (str.find(")") != -1) {
        str.replace(str.find(")"), 1, " ");
    }

    while (str.find("(") != -1) {
        str.replace(str.find("("), 1, " ");
    }

    while (str.find("  ") != -1) {
        str.replace(str.find("  "), 2, " ");
    }
}

//удаляет лишние знаки
void deleteSignes(string& str, int& size) {
    while (str.find("  ") != -1) {
        str.replace(str.find("  "), 2, " ");
    }
    while (str.find(",,") != -1) {
        str.replace(str.find(",,"), 2, ",");
    }
    while (str.find("??") != -1) {
        str.replace(str.find("??"), 2, "?");
    }
    while (str.find("!!") != -1) {
        str.replace(str.find("!!"), 2, "!");
    }
    while (str.find("--") != -1) {
        str.replace(str.find("--"), 2, "-");
    }
    while (str.find("((") != -1) {
        str.replace(str.find("(("), 2, "(");
    }
    while (str.find("))") != -1) {
        str.replace(str.find("))"), 2, ")");
    }

    size = str.length();
}



//приводит слово к нижнему регистру
void redactorOfRegister(string& str) {
    for(int i = 0; i < str.length(); i++){
        if (str[i] <= 'Z' && str[i] >= 'A')
            str[i] -= ('Z' - 'z');
        else if (str[i] <= 'Я' && str[i] >= 'А')
            str[i] -= ('Я' - 'я');
    }
}


//делает из символа заглавную букву
void mainLetter(char& a) {
    if (a <= 'z' && a >= 'a')
        a -= ('z' - 'Z');
    else if (a <= 'я' && a >= 'а')
        a -= ('я' - 'Я');
}



//удаляет все лишние точки, кроме знака моноготочия
void deleteDots(string& str, int& size) {
    while (str.find("...") != -1) {
        if (str[str.find("...") + 3] != '.' and str[str.find("...") - 1] != '.' and str[str.find("...") - 1] != '<' and str[str.find("...") + 3] != '<') {
            str.replace(str.find("..."), 3, "*");
        }
        else {
            str.replace(str.find("..."), 3, "<");
        }
        
    }
    while (str.find("<") != -1) {
        str.replace(str.find("<"), 1, "...");
    }
    while (str.find("..") != -1) {
        str.replace(str.find(".."), 2, ".");
    }
    while (str.find("*") != -1) {
        str.replace(str.find("*"), 1, "...");
    }

    size = str.length();
}


//редактирует строку в нормальный вид
string redactorOfSentances(string& str, int& size) {
    deleteSignes(str, size);
    deleteDots(str, size);
    string* b = split(str, ' ', size);
    for (int i = 0; i < size; i++) {
        redactorOfRegister(b[i]); 
    }
    string newStr = join(b, ' ', size);
    b = split(newStr, '.', size);
    for (int i = 0; i < size; i++) {
        if (b[i][0] != ' ') {
            mainLetter(b[i][0]);
        }
        else {
            mainLetter(b[i][1]);
        }
        
    }
  
    newStr = join(b, '.', size);
    newStr.replace(newStr.length() - 1, 1, "");
    return newStr;
    delete[] b;
}

//проверяет является ли символ числом
bool isDigit(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] <= '9' && str[i] >= '0') {
            return false;
        }
            
    }
}


//функция для первого задания
void problem1(string str, int size) {
    deleteAllSignesAndDots(str);
    string* b = split(str, ' ', size);
    for (int i = 0; i < size; i++) {
        if (isDigit(b[i])) {
            redactorOfRegister(b[i]);
            cout << b[i] << " ";
        }

    }   


}


//функция для второго задания
void problem2(string str, int size) {
    deleteAllSignesAndDots(str);
    string* b = split(str, ' ', size);
    for (int i = 0; i < size; i++) {
        redactorOfRegister(b[i]);
        cout << b[i] << '\n';
    }

    
}




int getNumberOfSize(int* arr, string str, char a, int size) { // возвращает число сдвига согласно букве из таблицы сдвигов
    for (int i = 0; i < size -1; i++) {
        if (str[size - arr[i] - 1] == a) {
            return arr[i];
        }
        
     }
    return arr[size - 1]; // возвращает номер сдвига для любого элемента или для последнего, если он не встречается нигде кроме как в конце
 
}





// функция, которая проверяет есть ли проверяемый элемент в массиве уже проверенных элементов
int isElement(string str, int* a,  int j, int size) {

    for (int i = 0; i < size; i++) {
        if (a[i] < str.length() and a[i] >= 0) {
            if (str[a[i]] == str[j]) {
                return a[i];
            }
        };
    }
    return -1;
}



void findInText(string str, string text) { //поиск по алгоритму Бойера-Мура

    int size = str.length();

    int* arrayOfIndexes = new int[size]; //массив, который сохраняет индексы уже обработанных символов в таблице


    int* arrayOfSizes = new int[size]; //сама таблица

    // цикл формирования таблицы
    for (int i = size - 2; i >= 0; i--) {
        int prevIndex = isElement(str, arrayOfIndexes, i, size);
        if (prevIndex != -1) {
            arrayOfSizes[i] = size - (prevIndex + 1);
        }
        else {
            arrayOfSizes[i] = size - (i + 1);
            arrayOfIndexes[i] = i;
        }

    }


    //рассчитывание отступа для последнего элемента
    int prevIndexOfLast = isElement(str, arrayOfIndexes, size - 1, size);

    if (prevIndexOfLast != -1) {
        arrayOfSizes[size - 1] = size - (prevIndexOfLast + 1);
    }
    else {
        arrayOfSizes[size - 1] = size;  
    }




    int *indexes = new int[100];
    int point = 0;
    int counterForIndexes = 0;
    bool isFinded = false;
    while ((point+ str.length()) <= text.length()) {
       
        int k = str.length() - 1;
        int numberOfMatches = 0;
        for (int pointerRev = point + str.length() - 1; point <= pointerRev; pointerRev--) {
            if (text[pointerRev] == str[k]) {
                numberOfMatches += 1;
               
                
                k--;
                if (numberOfMatches == str.length()) {
        
                    indexes[counterForIndexes] = point;
                    counterForIndexes += 1;
                    point += str.length();
                }
            }
            else {
                if (str.find(text[pointerRev]) != -1) {
                    
                    point += getNumberOfSize(arrayOfSizes, str, text[pointerRev], str.length());
            
                    break;
                }
                else {
                    
                    point += str.length();
                    break;
                }
            }

        }
   

    }

    for (int i = 0; i < counterForIndexes; i++) {
        for (int j = 0; j < str.length(); j++) {
            mainLetter(text[indexes[i] + j]);
        }

    }
    delete[] indexes;
    cout << text;

}



void lineSearch(string str, string text) { // линейный поиск
    int* indexes = new int[100]; 
    int e = 0;
    for (int i = 0; i < text.length() - str.length() + 1; i++) {
        int k = 0;
        for (int j = 0; j < str.length(); j++) {
            if (str[j] == text[i + j]) {
                k += 1;
            }
        }
        if (k == str.length()) {
            indexes[e++] = i;
        }
    }

    for (int i = 0; i < e; i++) {
        for (int j = 0; j < str.length(); j++) {
            mainLetter(text[indexes[i] + j]);
        }
        
    }
    cout << text;
    delete[] indexes;

}





int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");
    string text;
    string flag;
    cout << "Как хотите прочесть строку (из файла - введите 1)/(из консоли - введите 2)\n";
    getline(cin, flag);

    if (flag == "1") {
        ifstream fin;
        string path;
        cout << "Введите имя файла и расширение, файл должен быть формата txt, сохраненный в кодировке ANSI: ";
        getline(cin, path);
        fin.open(path); 
        if (!fin.is_open()) {
            cout << "Ошибка открытия" << '\n';
        }
        else {
 
            text = "";
            string line;
            while (getline(fin, line)) {
                text += line + " ";
            }
            
        }
        fin.close();
    }
    else if (flag == "2") {
        cout << "Введите строку: ";
        getline(cin, text);
    }
    else {
        cout << '\n';
        cout << "Произошла ошибка, перезагрузите программу";
        return 1;
    }
    cout << "------------------------------------|Задание-1|------------------------------------";
    cout << '\n';
    problem1(text, text.length());
    cout << '\n';
    cout << "------------------------------------|Задание-2|------------------------------------";
    cout << '\n';
    problem2(text, text.length());
    cout << '\n';

    int size = text.length();
    text = redactorOfSentances(text, size);
    cout << "Введите строку которую хотите найти: ";
    string str;
    getline(cin, str); cout << '\n';
    cout << "---Работа линейного поиска---";
    cout << '\n';
    lineSearch(str, text); cout << '\n' << '\n';
    cout << "---Работа алгоритма Бойера-Мура---";
    cout << '\n';
    findInText(str, text);
    cout << '\n';
    return 0;
}