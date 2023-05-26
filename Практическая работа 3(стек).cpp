#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <stack>

using namespace std;



bool isStrDigit(string digitBuffer);
int priority(char i);
int isVariable(char i);
int calculatePostfix(string postfix);
int calculatePrefix(string prefix);
int calculateInfix(string str);
void add(stack<int>* new_stc);
void deduct(stack<int>* new_stc);
void multiply(stack<int>* new_stc);
void divide(stack<int>* new_stc);
void printMainMenu();



int main(){
    setlocale(0, "Rus");    
    string str;
    int i = 0;
    while (i != 4) 
    {
        printMainMenu();
        cout << "Выберите пункт: ";
        cin >> i;
        string equation; // строка для хранения ввода
        switch (i) 
        {
            case 1:
                cin.ignore();
                system("CLS");
                cout << "Введите выражение\n";
                getline(cin, equation);
                calculateInfix(equation);
                system("pause");
                break;
            case 2:
                cin.ignore();
                system("CLS");
                cout << "Введите выражение, каждый операнд и операторар должны быть разделены пробелами\n";
                getline(cin, equation);
                calculatePostfix(equation);
                system("pause");
                break;
            case 3:
                cin.ignore();
                system("CLS");
                cout << "Введите выражение, каждый операнд и операторар должны быть разделены пробелами\n";
                getline(cin, equation);
                calculatePrefix(equation);
                system("pause");
                break;
        }

    }
} 





int calculatePostfix(string postfix) {
    if (postfix.find(")") != -1 || postfix.find("(") != -1) { // проверка на скобки
        cout << "Некорректное выражение, в нотации должны отсутствовать скобки";
        return 0;
    }
    stack <int> new_stc;
    postfix += " "; // добавление пробела для корректного считывания символа
    string digitBuffer = ""; // строка для считывания чисел
    int iV;
    for (int i = 0; i < postfix.size(); i++) {
        iV = isVariable(postfix[i]);
        switch (iV) {
        case 1: {
            if (digitBuffer.size() != 0) {
                int a = stoi(digitBuffer);
                new_stc.push(a);
                digitBuffer = "";
            }
            break;
        }
        case 2: {
            digitBuffer += postfix[i];
            break;
        }
        case 0: {
            if (new_stc.size() < 2) { // проверка на корректность 
                cout << "Выражение некорретно, дублирование символов или их недостаток";
                return 0;
            }
            switch (postfix[i]) {
            case '+':
                if (!new_stc.empty()) {
                    add(&new_stc);
                    break;
                }

            case '-':
                if (!new_stc.empty()) {
                    deduct(&new_stc);
                    break;
                }

            case '*':
                if (!new_stc.empty()) {
                    multiply(&new_stc);
                    break;
                }

            case '/':
                if (!new_stc.empty()) {
                    divide(&new_stc);
                    break;
                }

            }
            break;

        }


        }

    }
    if (new_stc.size() > 1) { // проверка на корректность выражения 
        cout << "Неправильная расстановка операторов, их дублирование или недостаток";
        return 0;
    }
    cout << new_stc.top() << " " << "Значение корректного выражения.\n";
    return 1;
}




int calculateInfix(string str) {
    stack <char> stc; // инициализация стека
    string postfix; // строка для хранения постфиксной записи
    int pr; // переменная для хранения приоритета
    for (int i = 0; i < str.size(); i++) {
        pr = priority(str[i]); // вычисление приоретета операции
        switch (pr)
        {
            case 1: { // открывающаяся скобка
                postfix += " ";
                stc.push(str[i]);
                break;
            }

            case 0: {
                if (str[i] == ')') {
                    postfix += " ";
                    while (!stc.empty() && stc.top() != '(') {
                        postfix += " ";
                        postfix += stc.top();
                        postfix += " ";
                        stc.pop();
                    }
                    if (!stc.empty()) {
                        postfix += " ";
                        stc.pop();
                    }
                    else {
                        cout << "Неправильное расположение скобок, их дублирование или недостаток\n";
                        return 0;
                    }
                }
                else {
                    if (str[i] != ' ' and !isdigit(str[i])) {
                        cout << "Встречена переменная " << str[i] << " иницализируйте её\n";
                        cout << "Значение переменной: ";
                        string stringForInit = " "; // строка для хранения инициализированного числа
                        while (!isStrDigit(stringForInit)) { // пока пользователь не инициализирует переменную
                            getline(cin, stringForInit);
                            if (!isStrDigit(stringForInit))  cout << "Вы ввели не число: ";
                        }
                        postfix += stringForInit;
                    }
                    else {
                        postfix += str[i]; // добавление символа в строку постфиксной записи
                    }
                }
                break;
            }
            default:
            {
                if (!stc.empty())
                {
                    postfix += " ";
                    while (!stc.empty() && priority(stc.top()) >= pr) {

                        postfix += stc.top();
                        postfix += " ";
                        stc.pop();
                    }
                    stc.push(str[i]);
                }
                else {
                    postfix += " ";
                    stc.push(str[i]);
                }

                break;

            }

        }
    }
    if (!stc.empty()) { // вытаскивание из стека отсавшихся операций
        postfix += " ";
        while (!stc.empty())
        {
            postfix += stc.top();
            postfix += " ";
            stc.pop();
        }
    }
    while (postfix.find("  ") != -1) { // удаление лишних пробелов
        postfix.replace(postfix.find("  "), 2, " ");
    }
    cout << "Преобразованное выражение в обратную польскую нотацию: " << "\033[38;2;25;255;25m" << postfix << "\033[0m\n";
    calculatePostfix(postfix);
    
}


int calculatePrefix(string prefix) {
    if (prefix.find(")") != -1 || prefix.find("(") != -1) { // проверка на присутсвие в выражении скобок
        cout << "В нотации должны отсутсвовать скобки\n";
        return 0;
    }
    stack <int> new_stc;
    // добавляем пробел для корректного считывания символов
    string digitBuffer = "";
    int iV;
    for (int i = prefix.size(); i > -1; i--) {
        iV = isVariable(prefix[i]);
        switch (iV) {
            case 1: { // считывание числа
                if (digitBuffer.size() != 0) {
                    reverse(digitBuffer.begin(), digitBuffer.end());
                    int a = stoi(digitBuffer);
                    new_stc.push(a);
                    digitBuffer = "";
                }
                break;
            }
            case 2: { // добавление числа в строку (если встречен пробел -> в буферной строке - число
                digitBuffer += prefix[i];
                break;
            }
            case 0: {
                if (new_stc.size() < 2) {
                    cout << "Выражение некорретно, дублирование знаков или их недостаток\n";
                    return 0;
                }
                int fV;
                int sV;
                switch (prefix[i]) {
                case '+':
                    if (!new_stc.empty()) {
                        add(&new_stc);
                        break;
                    }

                case '-':
                    if (!new_stc.empty()) {
                        deduct(&new_stc);
                        break;
                    }

                case '*':
                    if (!new_stc.empty()) {
                        multiply(&new_stc);
                        break;
                    }

                case '/':
                    if (!new_stc.empty()) {
                        divide(&new_stc);
                        break;
                    }
                }
                break;

            }
        }
    }
    if (new_stc.size() > 1) {
        cout << "Выражение неккоректно\n";
        return 1;
    }

    cout << new_stc.top() << " " << "Значение корректного выражения.\n";
    return 1;

}

bool isStrDigit(string digitBuffer) {
    for (int i = 0; i < digitBuffer.size(); i++) {
        if (!isdigit(digitBuffer[i])) {
            return false;
        }
    }
    return true;
}

int priority(char i) {
    switch (i) {
    case '(': return 1;
    case '+': case '-': return 2;
    case '*': case '/': return 3;
    default: return 0;
    }
}


int isVariable(char i) {
    switch (i) {
    case '+': case '-': case '*': case '/': return 0;
    case ' ': return 1;
    default: return 2;
    }
}

void add(stack<int>* new_stc) {
    int fV = new_stc->top();
    new_stc->pop();
    int sV = new_stc->top();
    new_stc->pop();
    int result = fV + sV;
    cout << fV << " + " << sV << "\n";
    new_stc->push(result);
}
void deduct(stack<int>* new_stc) {
    int fV = new_stc->top();
    new_stc->pop();
    int sV = new_stc->top();
    new_stc->pop();
    int result = sV - fV;
    cout << sV << " - " << fV << "\n";
    new_stc->push(result);
}

void multiply(stack<int>* new_stc) {
    int fV = new_stc->top();
    new_stc->pop();
    int sV = new_stc->top();
    new_stc->pop();
    int result = fV * sV;
    cout << fV << " * " << sV << "\n";
    new_stc->push(result);
}
void divide(stack<int>* new_stc) {
    int fV = new_stc->top();
    new_stc->pop();
    int sV = new_stc->top();
    new_stc->pop();
    int result = fV / sV;
    cout << fV << " / " << sV << "\n";
    new_stc->push(result);
}

void printMainMenu() {
    system("CLS");
    cout << "1-Преобразовать инфиксную запись и найти значение выражения.\n";
    cout << "2-Найти значение выражение в постфиксной записи\n";
    cout << "3-Найти значение выражения в префиксной записи\n";
    cout << "4-Выход\n";
}


