
#include <vector>
#include <iostream>

#include <fstream>
#include <string>
using namespace std;
#include <chrono>




class Node {
public:
    int key = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0;
    
};


class Tree {
private:
    Node* recursionInsert(int insKey, Node* node);
    Node* recursionDelete(int delKey, Node* node);
    Node* recursionDeleteForFile(int delKey, Node* node, ofstream& output_ans);
    Node* recursionInsertForFile(int insKey, Node* node, ofstream& output_ans);
    Node* removeMaxFromleft(Node* node);
    Node* removeMaxFromleftForFile(Node* node, ofstream& output_ans);
    Node* findMaxFromLeft(Node* node);
public:
    Node* deleteNode(int delKey);
    Node* find(Node* root, int fKey);
    Node* root = nullptr;
    void deleteForTask(int delKey, ofstream& output_ans);
    int size = 0;
    bool isRoot();
    int insert(int insKey);
    int insertForFile(int insKey, ofstream& output_ans);
    void Destroy(Node* node);
};

struct Trunk
{
    Trunk* prev;
    string str;

    Trunk(Trunk* prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};




void updateHeight(Node* node);
void printTreeToFile(Node* root, Trunk* prev, bool isLeft, ofstream& file);
void printTree(Node* root, Trunk* prev, bool isLeft);
void showTrunks(Trunk* p);
int returnRandKey();
int balanceFactor(Node* node);
Node* balanceTreeForFile(Node* node, ofstream& output_ans);
Node* balanceTree(Node* node);


Node* Tree::findMaxFromLeft(Node* node)
{
    cout << "Поиск максимального слева\n";
    Node* curr = node;
    while (curr->right) {
        curr = curr->right;
    }
    cout << curr->key << "\n";
    return curr;
}





Node* Tree::removeMaxFromleft(Node* node)
{
    
    if (node->right) {
        node->right = removeMaxFromleft(node->right); 
    }
    else {
        return nullptr;
    }
    
    return balanceTree(node); // нужно написать return, чтобы node->left сбалансировался
    /*
             4 - удаляем его                                4
           /  \                                            / \
       -- 3    6   - правый поворот относительно 3        2   6
        /  \    \                                        / \   \
       2  null    7                                     1   3   7
      /
     1

    */
}
Node* Tree::removeMaxFromleftForFile(Node* node, ofstream& output_ans)
{

    if (node->right) {
        node->right = removeMaxFromleft(node->right);
    }
    else {
        return nullptr;
    }

    return balanceTreeForFile(node, output_ans);
}


Node* Tree::recursionDelete(int delKey, Node* node)
{
    
    if (delKey > node->key) { 
        node->right = recursionDelete(delKey, node->right);
    }


    if (delKey < node->key) {
        node->left = recursionDelete(delKey, node->left);
    }

    if (delKey == node->key) {
        if (!node) return 0;
        if (node->right == nullptr and node->left == nullptr) { // если у удаляемого узла нет потомков то просто удаляем лист
            delete node;
            return nullptr;
        }
        if (node->right == nullptr && node->left != nullptr){ // если 1 потомок, то возвращаем один из них
            Node* bufferLeft = node->left;
            delete node;
            return bufferLeft;
        }
        if (node->right != nullptr && node->left == nullptr) { // если 1 потомок, то возвращаем один из них
            
            Node* bufferRight = node->right;
            delete node;
            return bufferRight;
            
        }
        if (node->right != nullptr && node->left != nullptr) { // если 2 потомка, то ищем минимальный элемент в правом дереве
            cout << node->key << '\n';
            cout << "Первое условие\n";
            Node* bufferNode = findMaxFromLeft(node->left);// почему зеленый ?
            cout << "Буферный узел " << bufferNode -> key << "\n";
            bufferNode->left = removeMaxFromleft(node->left);
           
            bufferNode->right = node->right;
            delete node;
            return balanceTree(bufferNode);
        }
    }
    return balanceTree(node);
    
    
}
Node* Tree::recursionDeleteForFile(int delKey, Node* node, ofstream& output_ans)
{

    if (delKey > node->key) {
        node->right = recursionDeleteForFile(delKey, node->right, output_ans);
    }
    if (delKey < node->key) {
        node->left = recursionDeleteForFile(delKey, node->left, output_ans);
    }

    if (delKey == node->key) {
        if (!node) return 0;
        if (node->right == nullptr and node->left == nullptr) { // если у удаляемого узла нет потомков то просто удаляем лист
            delete node;
            return nullptr;
        }
        if (node->right == nullptr && node->left != nullptr) { // если 1 потомок, то возвращаем один из них
            Node* bufferLeft = node->left;
            delete node;
            return bufferLeft;
        }
        if (node->right != nullptr && node->left == nullptr) { // если 1 потомок, то возвращаем один из них
            Node* bufferRight = node->right;
            delete node;
            return bufferRight;
        }
        if (node->right != nullptr && node->left != nullptr) { // если 2 потомка, то ищем минимальный элемент в правом дереве
            output_ans << node->key << '\n';
            output_ans << "У узла два наследника\n";
            Node* bufferNode = findMaxFromLeft(node->left);// почему зеленый ?
            output_ans << "Буферный узел " << bufferNode->key << "\n";
            bufferNode->left = removeMaxFromleftForFile(node->left, output_ans);

            bufferNode->right = node->right;
            delete node; 
            return balanceTreeForFile(bufferNode, output_ans);
        }
    }
    return balanceTreeForFile(node, output_ans);


}
Node* Tree::find(Node* root, int fKey){
    if (!root)
        return nullptr;
    if (root->key == fKey)
        return root;
    if (root->key < fKey) 
        return find(root->right, fKey);
    return find(root->left, fKey);
}
Node* Tree::deleteNode(int delKey)
{
    if (!find(root, delKey)){
        return nullptr;
    }
    root = recursionDelete(delKey, root);
}
void Tree::deleteForTask(int delKey, ofstream& output_ans)
{
    root = recursionDeleteForFile(delKey, root, output_ans);
}
int getHeight(Node* node) {
    return node == nullptr ? -1 :node->height;
}
Node* rotateRight(Node* node) { // простой правый поворот относительно узла node
   
    Node* leftNode = node->left;
    node->left = leftNode->right;
    leftNode->right = node;
    // поворот завершен
    updateHeight(node);
    updateHeight(leftNode);
    return leftNode;
}
Node* rotateLeft(Node* node) { // простой левый поворот относительно node
    Node* rightNode = node->right;
    node->right = rightNode->left;
    rightNode->left = node;
    // поворот завершен
    updateHeight(node);
    updateHeight(rightNode);
    return rightNode;
}





Node* balanceTree(Node* node) {
    updateHeight(node); // каждый раз обновляем высоту
    if (balanceFactor(node) == 2) { // правая часть перевешивает
        if (balanceFactor(node->right) < 0) { // если относительно потомка перевес в левую сторону         
            node->right = rotateRight(node->right); // правый поворот - потом левый
        }
        return rotateLeft(node); // обычный левый поворот относительно изначального узла
    }
    if (balanceFactor(node) == -2) { // левая часть перевешивает
        
        if (balanceFactor(node->left) > 0) { // потомок несбалансированного узла перевешен вправо
            
            node->left = rotateLeft(node->left); // левый - правый поворот
        } 
        
        return rotateRight(node); // простой правый поворот
    }
    return node; // возвращения узла если дерево сбалансированно
    
}
Node* balanceTreeForFile(Node* node, ofstream &output_ans) {
    updateHeight(node); // каждый раз обновляем высоту
    if (balanceFactor(node) == 2) { // правая часть перевешивает
        output_ans << "Балансировка правой части\n";
        if (balanceFactor(node->right) < 0) { // если относительно потомка перевес в левую сторону
            output_ans << "Выполняется правый-левый поворот поддерева\n";
            node->right = rotateRight(node->right); // правый поворот - потом левый
        }

        printTreeToFile(node, nullptr, false, output_ans);
        return rotateLeft(node); // обычный левый поворот относительно изначального узла
    }

     
    if (balanceFactor(node) == -2) { // левая часть перевешивает
        output_ans << "Балансировка левой части\n";
        if (balanceFactor(node->left) > 0) { // потомок несбалансированного узла перевешен вправо
            output_ans << "Выполняется левый-правый поворот поддерева\n";
            node->left = rotateLeft(node->left); // левый - правый поворот
        }
        printTreeToFile(node, nullptr, false, output_ans);
        return rotateRight(node); // простой правый поворот
    }
    return node; // возвращения узла если дерево сбалансированно

}



void showTrunks(Trunk* p)
{
    if (p == nullptr) {
        return;
    }
    showTrunks(p->prev);
    cout << p->str;
}

void printTree(Node* root, Trunk* prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);
    printTree(root->right, trunk, true);


    if (!prev) {
        trunk->str = "root";
    }
    else if (isLeft)
    {
        trunk->str = ".--->";
        prev_str = "   |";
    }
    else {
        trunk->str = "'--->";
        prev->str = prev_str;
    }
    showTrunks(trunk);
    cout << " " << root->key << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}


int balanceFactor(Node* node) { // функция для проверки баланса дерева
    return getHeight(node->right) - getHeight(node->left);
}

bool Tree::isRoot()
{ 
    if (root) {
        return true;
    }
    cout << "У дерева нет корня\n";
    return false;
}







void updateHeight(Node* node) { // обновляет высоту для каждого узла
    node->height = getHeight(node->left) > getHeight(node->right)? getHeight(node->left) + 1  : getHeight(node->right) + 1;
}




Node* Tree::recursionInsert(int insKey,Node* node) // рекурсивная вставка
{
    if (!node) { // условие выхода из рекурсии
        Node* newNode = new Node;
        newNode->key = insKey;
        return newNode;
    }
    if (insKey >= node->key) {
        node->right = recursionInsert(insKey, node->right);
    }
    else {
        node->left = recursionInsert(insKey, node->left);
    }
    balanceTree(node); // при развертывании рекурсии каждый узел пройдет проверку на балансировку
}

Node* Tree::recursionInsertForFile(int insKey, Node* node, ofstream& output_ans) // рекурсивная вставка
{
    if (!node) { // условие выхода из рекурсии
        Node* newNode = new Node;
        newNode->key = insKey;
        return newNode;
    }
    if (insKey >= node->key) {
        node->right = recursionInsertForFile(insKey, node->right, output_ans);
    }
    else {
        node->left = recursionInsertForFile(insKey, node->left, output_ans);
    }
    balanceTreeForFile(node, output_ans); // при развертывании рекурсии каждый узел пройдет проверку на балансировку
}


Tree task_createTreeByRandomVector(ofstream& output_key, ofstream& output_ans);
Tree createTreeByRandomVector(ofstream& output_key, ofstream& output_ans);
int Tree::insert(int insKey)
{ 
    if (!root) {
        root = new Node;
        root->key = insKey;
        return 0;
    }
    root = recursionInsert(insKey, root);
}
int Tree::insertForFile(int insKey, ofstream& output_ans)
{
    if (!root) {
        root = new Node;
        root->key = insKey;
        return 0;
    }
    root = recursionInsertForFile(insKey, root, output_ans);
}

bool isStrDigit(string digitBuffer) {
    for (int i = 0; i < digitBuffer.size(); i++) {
        if (!isdigit(digitBuffer[i]) and digitBuffer[i] != '-') {
            return false;
        }
    }
    return true;
}

void showTrunksToFile(Trunk* p, ofstream& file)
{
    if (p == nullptr) {
        return;
    }

    showTrunksToFile(p->prev, file);
    file << p->str;
}

void printTreeToFile(Node* root, Trunk* prev, bool isLeft, ofstream& file) {
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);
    printTreeToFile(root->right, trunk, true, file);


    if (!prev) {
        trunk->str = "root";
    }
    else if (isLeft)
    {
        trunk->str = ".--->";
        prev_str = "   |";
    }
    else {
        trunk->str = "'--->";
        prev->str = prev_str;
    }

    showTrunksToFile(trunk, file);
    file << " " << root->key << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTreeToFile(root->left, trunk, false, file);
}

void task_insert(Tree* tree, int key, ofstream& output_key, ofstream& output_ans) {
    tree->insertForFile(key, output_ans);
}
 
int task_deleteNode(Tree* tree, int key, ofstream& output_key, ofstream& output_ans) {
    output_key << '\n';
    if (!tree->find(tree->root, key)) {
        output_key << "Узел не найден\n";
        return 0;
    }
    tree->deleteForTask(key, output_ans);
}

void printNumberTask(int i, int variant, ofstream& output_file, int key) {
    switch (variant) {
    case 1:
        output_file << '\n';
        output_file << "Задание: " << i << "-cоздание дерева из массива целых чисел.\n";
        output_file << '\n';
        
        break;
    case 2:
        output_file << '\n';
        output_file << "Задание: " << i << " - удаление элемента " << key << " из дерева.\n";
        output_file << '\n';
        break;
    case 3:
        output_file << '\n';
        output_file << "Задание: " << i << "-вставка элемента " << key << " в дерево.\n";
        output_file << '\n';
        break;
        
    }
    
}

int returnRandKeyForDelete() {
    int minForValue = -44;
    int maxForValue = 44;
    int key = rand() % (maxForValue - minForValue + 1) + minForValue;
    return key;
}

int generateTasks(int numberOfTasks) {
    int max = 3;
    int min = 1;
    int variant = 1;
    srand(time(0));
    ofstream output_task("output_task.txt", ios_base::out | ios_base::trunc);
    if (!output_task.is_open()) {
        cout << "Файл невозможно открыть.\n";
        return 0;
    }
    ofstream output_key("output_key.txt", ios_base::out | ios_base::trunc);
    if (!output_key.is_open()) {
        cout << "Файл невозможно открыть.\n";
        return 0;
    }
    ofstream output_ans("output_ans.txt", ios_base::out | ios_base::trunc);
    if (!output_ans.is_open()) {
        cout << "Файл невозможно открыть.\n";
        return 0;
    }
    Tree tree;
    Tree* pTree = nullptr;
    int key;
    for (int i = 0; i < numberOfTasks; i++) {
        
        variant = rand() % (max - min + 1) + min;
        cout << variant<<'\n';
        switch (variant)
        { 
        case 1: 
            printNumberTask(i + 1, variant, output_key, 0);
            printNumberTask(i + 1, variant, output_ans, 0);
            tree = task_createTreeByRandomVector(output_key, output_ans);
            pTree = &tree;
            printTreeToFile(tree.root, nullptr, false, output_key);
            printTreeToFile(tree.root, nullptr, false, output_ans);
            output_task << i + 1 << ")" << "Создание дерева из массива целых чисел.\n";
            break;
            
        case 2:
            if (pTree) {
                cout << "Есть дерево";
                key = returnRandKeyForDelete();
                output_task << i + 1 << ")" << "-Удаление ключа из существуещего дерева узел : " << key << "\n";
                printNumberTask(i + 1, variant, output_key, key);
                printNumberTask(i + 1, variant, output_ans, key);
                cout << key << "\n";
                if (!task_deleteNode(pTree, key, output_key, output_ans)) break;
                printTreeToFile(tree.root, nullptr, false, output_key);
                printTreeToFile(tree.root, nullptr, false, output_ans);
                break;
            }
            else {
                cout << "Нет дерева";
                key = returnRandKeyForDelete();
                output_task << i + 1 << ")" << "-Удаление узла из существуещего дерева. Узел: " << key << "\n";
                printNumberTask(i + 1, variant, output_key, key);
                printNumberTask(i + 1, variant, output_ans, key);
                tree = createTreeByRandomVector(output_key, output_ans);
                output_key << "Создание случайного дерева, для удаления\n";
                output_key << "\n";
                output_ans << "Создание случайного дерева, для удаления\n";
                output_ans << "\n";
                printTreeToFile(tree.root, nullptr, false, output_ans);
                printTreeToFile(tree.root, nullptr, false, output_key);
                pTree = &tree;
                cout << key << "\n";
                if (!task_deleteNode(pTree, key, output_key, output_ans)) break;
                printTreeToFile(tree.root, nullptr, false, output_key);
                printTreeToFile(tree.root, nullptr, false, output_ans);
                break;
            }
        case 3:
            key = returnRandKey();
            printNumberTask(i + 1, variant, output_key, key);
            printNumberTask(i + 1, variant, output_ans, key);
            if (pTree) {
                
                output_task << i + 1 << ")" << "-Добавление узла в существуещее дерево. Узел: " << key << "\n";
                
                task_insert(pTree, key, output_key, output_ans);
                printTreeToFile(tree.root, nullptr, false, output_ans);
                printTreeToFile(tree.root, nullptr, false, output_key);
                break;
            }
            
            output_task << i + 1 << ")" << "-Создание дерева и добавление в него узла. Узел: " << key << "\n";
            tree = createTreeByRandomVector(output_key, output_ans);
            output_key << "Создание случайного дерева, для вставки\n";
            output_key << "\n";
            output_ans << "Создание случайного дерева, для вставки\n";
            output_ans << "\n";
            printTreeToFile(tree.root, nullptr, false, output_ans);
            pTree = &tree;
            task_insert(pTree, key, output_key, output_ans);
            printTreeToFile(tree.root, nullptr, false, output_ans);
            printTreeToFile(tree.root, nullptr, false, output_key);
            output_task << "Вставка ключа, если дерева не существует: " << key << "\n";
            break;
            
        default:
            break;
        }
    }
    output_ans.close();
    output_key.close();
    output_task.close();
}



int returnRandKey() {
    int minForValue = -99;
    int maxForValue = 99;
    int key = rand() % (maxForValue - minForValue + 1) + minForValue;
    return key;
}

vector <int> createRandomVector() {
    vector<int> nums;
    int min = 10; //не забыть srand(0)
    int max = 40;
    int lenght = rand() % (max - min + 1) + min;
    for (int i = 0; i < lenght; i++) {
        nums.push_back(returnRandKey());
    }
    return nums; // не возвращаем ссылку, так как вектор создается в функции
    // вектор будет удален после завершения работы функции, поэтому ссылки на него не будет
}

Tree createTreeByVector(vector <int>& numbers) {
    Tree newTree;
    for (int n : numbers) {
        newTree.insert(n);
    }
    return newTree;
}

Tree createTreeByRandomVector(ofstream& output_key, ofstream& output_ans) {
    vector<int> numbers = createRandomVector();
    Tree newTree;
    for (int n : numbers) {
        newTree.insert(n);
    }
    return newTree;
}
Tree task_createTreeByRandomVector(ofstream& output_key, ofstream& output_ans) {
    vector<int> numbers = createRandomVector();
    Tree newTree;
    for (int n : numbers) {
        newTree.insertForFile(n, output_ans);
    }
    return newTree;
}

vector <int> creatVector() {
    vector <int> numbers;
    string value = " ";
    cout << "Для прекращения ввода введите пустую строку\n";
    while (value != "") {
        cout << "Введите элемент: ";
        getline(cin, value);
        while (!isStrDigit(value) and value != "") {
            cout << "Вы ввели не число\n";
            cout << "Введите элемент еще раз: ";
            getline(cin, value);
        }
        if (value != "") {
            numbers.push_back(stoi(value));
        }

        cout << "\n";
    }
    return numbers;
}

int validateInput() {
    cout << "Введите кол-во элементов n в дереве (1 < n < 50): ";
    string value = "";
    getline(cin, value);
    while (!isStrDigit(value)) {
        cout << "Вы ввели не число\n";
        cout << "Введите значение еще раз: ";
        getline(cin, value);
    }
    return stoi(value);

}
int validateInputForInsDel() {
    cout << "Введите элемент: ";
    string value = "";
    getline(cin, value);
    while (!isStrDigit(value)) {
        cout << "Вы ввели не число\n";
        cout << "Введите значение еще раз: ";
        getline(cin, value);
    }
    return stoi(value);
}
int task_validateInput() {
    cout << "Введите кол-во задач n (1 < n < 15): ";
    string value = "";
    getline(cin, value);
    while (!isStrDigit(value)) {
        cout << "Вы ввели не число\n";
        cout << "Введите значение еще раз: ";
        getline(cin, value);
    }
    return stoi(value);

}



void printMainMenu() {
    system("CLS");
    cout << "1-Создать и вывести дерево из n элементов.\n";
    cout << "2-Создать дерево из неопределенного кол-ва элементав, элементы вводит пользователь.\n";
    cout << "3-Генерация n заданий.\n";
    cout << "4-Вывод ранее сгенерированного дерева.\n";
    cout << "5-Вставка элемента в дерево.\n";
    cout << "6-Удаление элемента из дерева.\n";
    cout << "7-Выход\n";
}
Tree createTree(int N) {
    Tree newTree;
    for (int i = 0; i < N; i++) {
        newTree.insert(returnRandKey());
    }
    return newTree;
}




int main()
{
    setlocale(0, "Rus");
    string str;
    int i = 0;
    int N;
    vector <int> nums;
    Tree newTree;
    Tree* pTree = nullptr; 
    int start;
    int  end;
    auto result = 1;
    while (i != 7)
    {
        printMainMenu();
        cout << "Выберите пункт: ";
        cin >> i;

        switch (i)
        {
        case 1: {
            system("CLS");
            cin.ignore();
            N = validateInput();
            while (N > 50 or N < 1) {
                cout << "Вы ввели недопустимое значение\n";
                cout << "Введите новое значение: ";
                N = validateInput();
            }
            auto start = chrono::steady_clock::now();
            newTree = createTree(N);
            auto end = chrono::steady_clock::now();
            auto result = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            cout << "Время формирования АВЛ дерева: " << result << "\n";
            pTree = &newTree;
            printTree(newTree.root, nullptr, false);

            system("pause");
            break;
        }
            
        case 2: {
            system("CLS");
            cin.ignore();
            nums = creatVector();
            newTree = createTreeByVector(nums);
            printTree(newTree.root, nullptr, false);
            system("pause");
            break;
        }
            

        case 3: {
            system("CLS");
            cin.ignore();
            N = task_validateInput();
            while (N > 15 or N < 1) {
                cout << "Вы ввели недопустимое значение\n";
                cout << "Введите новое значение: ";
                N = task_validateInput();
            }
            generateTasks(N);
            system("pause");
            break;
        }
            

        case 4: {
            system("CLS");
            cin.ignore();
            if (!pTree) {
                cout << "Дерево не создано\n";
                system("pause");
                break;
            }
            printTree(newTree.root, nullptr, false);
            system("pause");
            break;
        }
            
        case 5: {
            system("CLS");
            cin.ignore();
            if (!pTree) {
                cout << "Дерево не создано\n";
                system("pause");
                break;
            }
            printTree(newTree.root, nullptr, false);
            cout << "\n";
            N = validateInputForInsDel();
            auto start = chrono::steady_clock::now();
            pTree->insert(N);
            auto end = chrono::steady_clock::now();
            auto result = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            cout << "Время вставки: " << result << "\n";
            printTree(newTree.root, nullptr, false);
            system("pause");
            break;
        }
            
        case 6: {
            system("CLS");
            cin.ignore();
            if (!pTree) {
                cout << "Дерево не создано\n";
                system("pause");
                break;
            }
            printTree(newTree.root, nullptr, false);
            cout << "\n";

            N = validateInputForInsDel();
            auto start = chrono::steady_clock::now();
            pTree->deleteNode(N);
            auto end = chrono::steady_clock::now();
            auto result = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            cout << "Время удаления: " << result << "\n";
            printTree(newTree.root, nullptr, false);
            system("pause");
            break;
        }
            
        }

    }

}
