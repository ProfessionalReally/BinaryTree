#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <iostream>
#include <queue>
#include <conio.h>
#include <Windows.h>
using namespace std;
class BST {
    struct node 
    {
        int data; //Поле данных
        node* left; //Указатель на левый потомок 
        node* right; //Указатель на правый потомок 
    };
    node* root;

    //Добавление узла в бинарное дерево
    node* Add(int x, node* t)
    {
        if (t == NULL) //Возвращаем новый узел, если дерево пустое
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if (x < t->data)
            t->left = Add(x, t->left);
        else if (x > t->data)
            t->right = Add(x, t->right);
        return t;
    }

    //Печать бинарного дерева в виде дерева повернутого на -90 
    void PrintTreeFile(ostream* out, node* t, int l) {
        if (t == NULL)
            return;
        PrintTreeFile(out, t->right, l + 1);
        for (int i = 0; i < l; ++i)
            *out << "\t";
        *out << t->data << endl;
        PrintTreeFile(out, t->left, l + 1);
    }

    //Количество детей и внуков узла
    int AmountChild(node* t) {
        int n = 0;
        if (t != NULL) {
            if (t->left != NULL) {
                n += (t->left->left == NULL) ? 0 : 1;
                n += (t->left->right == NULL) ? 0 : 1;
                n++;
            }
            if (t->right != NULL) {
                n += (t->right->left == NULL) ? 0 : 1;
                n += (t->right->right == NULL) ? 0 : 1;
                n++;
            }
        }
        return n;
    }
public:
    BST() {
        root = NULL;
    }

    //Добавление узла в бинарное дерево.
    void Add(int x) {
        root = Add(x, root);
    }
    //Печать бинарного дерева в виде дерева повернутого на -90 
    void DisplayTree(ostream* out) {
        *out << endl << endl;
        PrintTreeFile(out, root, 0);
        *out << endl << endl;
    }

    //Чтение данных из файла
    void ReadFile(string name) {
        ifstream f;
        f.open(name);
        int num;
        for (int i = 0; f >> num; i++) {
            this->Add(num);
        }
        f.close();
    }

    //Получение уровня узла, число потомков которого на этом уровне максимально
    int MaxLVL(int* maxlvl) 
    {
        int max = 0, n; //max - Максимум потомков, maxlvl - Уровень этого максимума
        node* t;
        queue<node*> q;  //Очередь для узлов
        queue<int> lvl;  //Очередь для уровней
        lvl.push(0);
        q.push(root);

        //Обход в ширину
        while (!q.empty()) {
            
            //Получение следующего узла и его уровня из очереди
            t = q.front();
            n = lvl.front();
            q.pop();
            lvl.pop();

            if (AmountChild(t) > max) {
                max = AmountChild(t);
                *maxlvl = n;
            }

            if (t->left != NULL) {
                q.push(t->left);
                lvl.push(n + 1);
            }
            if (t->right != NULL) {
                q.push(t->right);
                lvl.push(n + 1);
            }
        }
        return max;
    }
};
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream fin; //файл для чтения
    ofstream fout; //файл для записи
    int count; //Количество потомков
    int level; //Уровень
    BST tree; //Дерево
    string s; //Строка с исходными данными

    //Работа с input.dat

    tree.ReadFile("input.dat"); //Чтение данных из файла
    cout << "Дерево: " << endl;
    tree.DisplayTree(&cout); //Печать бинарного дерева в виде дерева повернутого на -90 

    count = tree.MaxLVL(&level); //Получения количество предков и уровень узла

    cout << "Количество предков = " << count << endl;
    cout << "Уровень = " << level << endl;

    fin.open("input.dat");
    getline(fin, s); //Получение исходных данных из input.dat
    fin.close();


    //Работа с output.dat

    fout.open("output.dat");
    fout << "Исходные данные: " << s << endl << "Дерево: ";
    tree.DisplayTree(&fout);

    fout << "Количество предков = " << count << endl;
    fout << "Уровень = " << level << endl;

    fout.close();
    return 0;
}
