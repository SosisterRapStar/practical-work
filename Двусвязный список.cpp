
#include <iostream>
#include<string>
#include<Windows.h>
#include<cmath>
#include <cstdlib>
#include <time.h>
#include <chrono>
using namespace std;
using namespace std::chrono;




class Node {  // класс реализующий элемент двусвязного списка
    Node *next = 0;
    Node *prev = 0;
    
    public:
        int data;
        Node* getNext() {
            return this->next;
        }

        void setNext(Node* nextNode) {
            this->next = nextNode;
        }

        Node* getPrev() {
            return this->prev;
        }

        void setPrev(Node* prevNode) {
            this->prev = prevNode;
        }

};

class LinkedList { // класс реализующий двусвязный список
    
    public:
        Node* tail = 0;
        Node* head = 0;

        int length = 0;
        int putToEnd(int data);
        Node* getByIndex(int index);
        Node* getByValue(int value);
        int deleteItemByValue(int value);
        int deleteItemByIndex(int index);
        int insert(int index, int data);
        int getList();
        int exchange(int index1, int index2);
        int generateList(int size);
};


int LinkedList::generateList(int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        int x = rand() % 100;
        putToEnd(x);
    }
    cout << "Список создан\n";
    return 1;
        
}

int LinkedList::exchange(int index1, int index2) {
    if (index1 > index2) {
        swap(index1, index2);
    }
    if (index1 == index2) {
        cout << "Нельзя обменять элемент сам с собой.\n";
        return NULL;
    }
    Node* node1 = getByIndex(index1);
    if (!node1) {
        cout << "Не найден первый узел \n";
        return NULL;
    }
    Node* node2 = getByIndex(index2);
    if (!node2) {
        cout << "Не найден второй узел \n";
        return NULL;
    }
    char isHead = 0;
    char isTail = 0;
    if (index1 - index2 == -1) {
        auto begin = std::chrono::steady_clock::now();
        if (node1->getPrev() != 0) {
            node1->getPrev()->setNext(node2);
        } else isHead = 1;
        if (node2->getNext() != 0) {
            node2->getNext()->setPrev(node1);
        }
        else isTail = 1;
        node2->setPrev(node1->getPrev());
        node1->setNext(node2->getNext());
        node1->setPrev(node2);
        node2->setNext(node1);
        if (isHead == 1) {
            head = node2;
        }
        if (isTail == 1) {
            tail = node1;
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cout << "Обмен выполнен \n";
        std::cout << "Время обмена: " << elapsed_ms.count() << " ns\n";
        return 1;
    }
    auto begin = std::chrono::steady_clock::now();
    if (node1->getPrev() != 0) {
        node1->getPrev()->setNext(node2);
    } else isHead = 1; 
    node1->getNext()->setPrev(node2);
    if (node2->getNext() != 0) {
        node2->getNext()->setPrev(node1);
    }
    else isTail = 0;
    node2->getPrev()->setNext(node1);
    
    Node* oldPrev1 = node1->getPrev();
    Node* oldNext1 = node1->getNext();
    node1->setNext(node2->getNext());
    node1->setPrev(node2->getPrev());
    node2->setNext(oldNext1);
    node2->setPrev(oldPrev1);
    if (isHead) {
        head = node2;
    }
    if (isTail) {
        tail = node1;
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "Обмен выполнен \n";
    std::cout << "Время обмена: " << elapsed_ms.count() << " ns\n";
    return 1;


}


int LinkedList::insert(int index, int data) {
    if (index >= length) {
        cout << "Элемента с таким индексом нет в списке\n";
        return NULL;
    }
    if (index < 0) {
        cout << "Элемента с таким индексом нет в списке\n";
        return NULL;
    }
    if (index == length - 1) {
        length++;
        auto begin = std::chrono::steady_clock::now();
        putToEnd(data);
        cout << "Вставка выполнена\n";
        auto end = std::chrono::steady_clock::now();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        std::cout << "Время вставки: " << elapsed_ms.count() << " ns\n";

        return 1;
    }
    length++;
    auto begin = std::chrono::steady_clock::now();
    Node* newData = new Node;
    newData->data = data;
    Node* node;
    node = getByIndex(index);
    newData->setPrev(node);
    newData->setNext(node->getNext());
    newData->getNext()->setPrev(newData);
    node->setNext(newData);
    cout << "Вставка выполнена\n";
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "Время вставки: " << elapsed_ms.count() << " ns\n";
    return elapsed_ms.count();
}

int  LinkedList::getList() {
    if (length == 0) {
        cout << "Список пустой\n";
        return 0;
    }
    Node* node = new Node;
    node = head;
    cout << "|NULL| <-> |";
    while (node) {
        cout << node->data << "| <-> |";
        node = node->getNext();
    }
    cout << "NULL|";
    return 1;
}


int LinkedList::deleteItemByValue(int value) {
    Node* node = new Node;
    node = getByValue(value);
    if (!node) {
        cout << "Удаление не удалось\n";
        return NULL;
    }
    if (length == 1) {
        auto begin = std::chrono::steady_clock::now();
        length--;
        head = 0;
        tail = 0;
        delete node;
        auto end = std::chrono::steady_clock::now();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cout << "Элемент удален\n";
        std::cout << "Время удаления: " << elapsed_ms.count() << " ns\n";
        return 1;
    }
    if (node == head) {
        length--;
        auto begin = std::chrono::steady_clock::now();
        node->getNext()->setPrev(0);
        head = node->getNext();
        delete node;
        auto end = std::chrono::steady_clock::now();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cout << "Элемент удален\n";
        std::cout << "Время удаления: " << elapsed_ms.count() << " ns\n";
        return 1;
    }
    if (node == tail) {
        length--;
        auto begin = std::chrono::steady_clock::now();
        node->getPrev()->setNext(0);
        tail = node->getPrev();
        delete node;
        auto end = std::chrono::steady_clock::now();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cout << "Элемент удален\n";
        std::cout << "Время удаления: " << elapsed_ms.count() << " ns\n";
        return 1;
    }
    
    length--;
    auto begin = std::chrono::steady_clock::now();
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
    delete node;
    auto end = std::chrono::steady_clock::now();

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "Элемент удален\n";
    std::cout << "Время удаления: " << elapsed_ms.count() << " ns\n";
    return 1;
}

int LinkedList::deleteItemByIndex(int index) {
    Node* node = new Node; // промежуточная переменная
    node = getByIndex(index); // получаю ноду по индексу
    if (!node) {
        cout << "Удаление не удалось\n";
        return NULL;
    }
    if (length == 1) { // удали голову
        length--;
        auto begin = std::chrono::steady_clock::now();
        head = 0;
        tail = 0;
        delete node;
        auto end = std::chrono::steady_clock::now();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cout << "Элемент удален\n";
        std::cout << "Время удаления: " << elapsed_ms.count() << " ns\n";
        return elapsed_ms.count();
    }
    if (node == head) { // удали голову
        length--;
        auto begin = std::chrono::steady_clock::now();

        node->getNext()->setPrev(0);   // второй элемент уже не указывает на голову
        head = node->getNext(); // второй элемент сам стал головой
        delete node;
        auto end = std::chrono::steady_clock::now();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cout << "Элемент удален\n";
        std::cout << "Время удаления: " << elapsed_ms.count() << " ns\n";
 
        return elapsed_ms.count();
    }
    if (node == tail) {
        length--;
        auto begin = std::chrono::steady_clock::now();
        node->getPrev()->setNext(0);
        tail = node->getPrev();
        delete node;
        auto end = std::chrono::steady_clock::now();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cout << "Элемент удален\n"; 
        std::cout << "Время удаления: " << elapsed_ms.count() << " ns\n";
        return elapsed_ms.count();
    }
    
    length--;
    auto begin = std::chrono::steady_clock::now();
    node->getPrev()->setNext(node->getNext());  // следующему говорю перепрыгни текущий нод и укажи на позапрошлый
    node->getNext()->setPrev(node->getPrev());
    delete node;
    auto end = std::chrono::steady_clock::now();

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "Элемент удален\n";
    std::cout << "Время удаления: " << elapsed_ms.count() << " ns\n";
    return elapsed_ms.count();
}


int LinkedList::putToEnd(int data)
{
    length += 1;
    if (head == 0) {
        Node* newNode = new Node;
        newNode->data = data;
        tail = newNode;
        head = newNode;
        return 1;
    }
    Node *newNode =  new Node;
    newNode -> data = data;
    Node* node = tail;
    tail = newNode;
    node->setNext(newNode);
    tail->setPrev(node);
    return 1;
}



Node* LinkedList::getByIndex(int index)
{
    if (index >= length) {
        cout<<  "Обращений к несуществующему индексу \n";
        return NULL;
    }
    Node* node = head;
    int counter = 0;
    auto begin = std::chrono::steady_clock::now();
    while (node && counter != index) {
        counter += 1;
        node = node->getNext(); 
    }
    auto end = std::chrono::steady_clock::now();

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "------ " << node << " АДРЕС ЭЛЕМЕНТА\n";
    std::cout << "Время получения элемента: " << elapsed_ms.count() << " ns\n";
    return node;
  
}

Node* LinkedList::getByValue(int value)
{
    Node* node = head;
    auto begin = std::chrono::steady_clock::now();
    while (node && node->data != value) {
        node = node->getNext();
    }
    auto end = std::chrono::steady_clock::now();
    if (node) {
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cout << "------ " << node << " АДРЕС ЭЛЕМЕНТА\n";
        std::cout << "Время получение элемента:  " << elapsed_ms.count() << " ns\n";
        return node;
    }
    cout << "Элемента с таким значением нет в списке \n";
    return NULL;
    
}

LinkedList generateList(int size);
void insert(LinkedList* list);
void exchange(LinkedList* list);
void insert(LinkedList* list);
void deleteByValue(LinkedList* list);
void getByValue(LinkedList* list);
void deleteByIndex(LinkedList* list);
void getByIndex(LinkedList* list);
void printMainMenu();
void getList(LinkedList* list);
void IDZ(); 
int* deleteEl(int* arr, int& len);
int main()
{
    setlocale(0, "Rus"); 
    int isListCreated = 0;
    int i = 0;
    LinkedList list = generateList(1);
    while (i != 9) 
    {
        printMainMenu();
        cout << "Введите пункт: ";
        cin >> i;
        switch (i)
        {
        case 1:
            system("CLS");
            cout << "Введите кол-во узлов\n";
            int N;
            cin >> N;
            list = generateList(N);
            isListCreated = 1;
            system("pause");
            break;
        case 2:
            system("CLS");
            if (!isListCreated) {
                cout << "Вы не создали список\n";
                system("pause");
                break;
            }
            insert(&list);
            system("pause");
            break;
        case 3:
            system("CLS");
            if (!isListCreated) {
                cout << "Вы не создали список\n";
                system("pause");
                break;
            }
            deleteByIndex(&list);
            system("pause");
            break;

        case 4:
            system("CLS");
            if (!isListCreated) {
                cout << "Вы не создали список\n";
                system("pause");
                break;
            }
            deleteByValue(&list);
            system("pause");
            break;
        case 5:
            system("CLS");
            if (!isListCreated) {
                cout << "Вы не создали список\n";
                system("pause");
                break;
            }
            getByValue(&list);
            system("pause");
            break;
        case 6:
            system("CLS");
            if (!isListCreated) {
                cout << "Вы не создали список\n";
                system("pause");
                break;
            }
            getByIndex(&list);
            system("pause");
            break;
        case 7:
            system("CLS");
            if (!isListCreated) {
                cout << "Вы не создали список\n";
                system("pause");
                break;
            }
            exchange(&list);
            system("pause");
            break;
        case 8:
            system("CLS");
            if (!isListCreated) {
                cout << "Вы не создали список\n";
                system("pause");
                break;
            }
            getList(&list);
            system("pause");
            break;

        case 9:
            cout << "Программа завершена\n";
        }
    }

    IDZ();
    

    
}
void printMainMenu() {
    system("CLS");
    cout << "1-Генерация связного списка размерности N\n";
    cout << "2-Вставка элемента, введите индекс после которого хотите вставить элемент\n";
    cout << "3-Удаление элемента по индексу.\n";
    cout << "4-Удаление элемента по значению.\n";
    cout << "5-Получение элемента по значению.\n";
    cout << "6-Получение элемента по индексу.\n";
    cout << "7-Обмен элементов.\n";
    cout << "8-Получить список\n";
    cout << "9 - Выход\n";

}

void deleteByIndex(LinkedList* list) {
    cout << "Введите индекс элемента, который хотите удалить\n";
    int ind;
    cin >> ind;
    list->deleteItemByIndex(ind);

}

void exchange(LinkedList* list) {
    cout << "Введите 2 индекса элементов, которые хотите поменять местами\n";
    int index1;
    int index2;
    cout << "Индекс-1: ";
    cin >> index1;
    cout << "Индекс-2: ";
    cin >> index2;
    list->exchange(index1, index2);
}

void deleteByValue(LinkedList* list) {
    cout << "Введите значение элемента, который хотите удалить\n";
    int vala;
    cin >> vala;
    list->deleteItemByValue(vala);

}

void insert(LinkedList* list) {
    cout << "Введите индекс элемента после которого хотите вставить элемент\n";
    int ind;
    cin >> ind;
    cout << "Введите значение для нового узла\n";
    int data;
    cin >> data;
    list->insert(ind, data);
   
}

void getByValue(LinkedList* list) {
    cout << "Введите значение элемента, который хотите получить\n";
    int val = 0;
    cin >> val;
    list->getByValue(val);
    
}

void getByIndex(LinkedList* list) {
    cout << "Введите индекс элемента, который хотите получить\n";
    int in = 0;
    cin >> in;
    list->getByIndex(in);
    
}


void IDZ() {
    cout << "Введите кол-во элементов: ";
    int N = 0;
    cin >> N;
    int M = N;
    LinkedList doubleList = generateList(N);
    int* dynamicArr = new int[N];
    auto begin = std::chrono::steady_clock::now();
    while(N) {
        dynamicArr = deleteEl(dynamicArr, N);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);



    int time1 = 0;
    int time2 = 0;


    for (int i = 0; i < M; i++) {
        time2 += doubleList.deleteItemByIndex(0);
    }
    
    time1 = elapsed_ms.count();
    
    cout << "Время удаления из списка: " << time2 << "ns" << " Время удаления из массива: " << time1 << "ns";

}



 
int* deleteEl(int* arr, int& len) {
  
    if (len == 0) {
        return nullptr;
    }
    if (len == 1) {
        len -= 1;
        delete[] arr;
        cout << "Список удален \n";
        return nullptr;
    }
    len -= 1;
    int* newArr = new int[len];
    
    for (int i = 0; i < len; i++) {
        newArr[i] = arr[i];
    }
    
    delete[] arr;
    arr = newArr;
    return arr;
}


void getList(LinkedList* list) {
    list->getList();
    cout << "\n";
    cout << "Длина текущего списка: " << list->length << '\n';
}

LinkedList generateList(int size) {
    LinkedList object;
    object.generateList(size);
    cout << "Список на " << size << " элементов создан.\n";
    return object;

}