//
// Created by webve on 12.12.2017.
//

#ifndef LABA2BST_TREE_H
#define LABA2BST_TREE_H

#include <iostream>
#include "stack"

template<class Key, class Data>
class Tree
{
    class Node{
    public:
        Key key;
        Data value;
        Node* left;
        Node* right;
        int levelNode;
        Node(Key k, Data d) {
            key = k;
            value = d;
            left = NULL;
            right = NULL;
        }
        ~Node() {
            key = NULL;
            value = NULL;
            left = NULL;
            right = NULL;
        };
    };
    Node * root;
    int size = 0;

public:
    Tree();
    ~Tree();
    int getSize();
    void clear();
    bool isEmpty();
    Data get(Key k);
    void put(Key k, Data d);
    void remove(Key key);
    void print();

    class Iterator {
        Tree* pointer;
        Node* current;
        std::stack<Node*>* stack;
        std::stack<Node*>* back_stack;


    public:
        int level = 0;
        explicit Iterator(Tree* tree) {
            pointer = tree;
            current = tree->root;
            stack = new std::stack<Node*>();
            back_stack = new std::stack<Node*>();

        };
        explicit Iterator(Node * node){
            current = node;
            stack = new std::stack<Node*>();
            back_stack = new std::stack<Node*>();
            stack->push(current);
        }
        ~Iterator()
        {

        }
        //установить итератор в начало
        Node* begin()
        {
            delete stack;
            level = 0;
            stack = new std::stack<Node*>();
            current = pointer->root;
                while (current->left != NULL) {
                    stack->push(current);
                    current = current->left;
                    level++;
                }
            return current;
        }
        //установить итератор в конец
        Node* end(){
            current = pointer->root;
            while (current->right != NULL) {
                current = current->right;
                level++;
            }
            return current;
        }
        //проверка состояния итератора
        Key checkState() {
            return current->key;
        }
        //доступ к данным текущего узла
        Node* getNote()
        {
            return current;
        }
        //доступ и переход итератора к следующему узлу
        Node* next()
        {
            if (!stack->empty() && current == stack->top())
            {
                stack->pop();
                back_stack->push(current);
                if (current->right != NULL)
                {
                    current = current->right;
                    level++;
                    while (current->left != NULL)
                    {
                        stack->push(current);
                        current = current->left;
                        level++;
                    }
                    return current;
                }
                else
                {
                    current = stack->top();
                    level--;
                    return current;
                }
            }
            else
            {
                back_stack->push(current);
                if (current->right != NULL) {
                    current = current->right;
                    level++;
                }
                else {
                    current = stack->top();
                    level--;
                }
                return current;
            }
        }
        //Доступ и переход к предыдущему узлу
        //----------------------------------
        Node* back() {
            //back_stack->pop();
            current = back_stack->top();
            back_stack->pop();
            return current;
        }
    };
    friend class Iterator;
};
template<class Key, class Data>
Tree<Key, Data>::Tree()
{
    root = NULL;
}

template<class Key, class Data>
Tree<Key, Data>::~Tree()
{

}
//Возращает размер дерева
template<class Key, class Data>
int Tree<Key, Data>::getSize()
{
    return size;
}
//Очищает дерево
template<class Key, class Data>
void Tree<Key, Data>::clear()
{
    Iterator iterator(this);
    while (!this->isEmpty()){
        iterator.begin();
        remove(iterator.getNote()->key);
    }
}
//Провереят дерево на пустоту
template<class Key, class Data>
bool Tree<Key, Data>::isEmpty()
{
    return size == 0;
}
//Возращает значение по заданому ключу
template<class Key, class Data>
Data Tree<Key, Data>::get(Key key)
{
    return Data();
}

//добавление данных с заданным ключем
template<class Key, class Data>
void Tree<Key, Data>::put(Key k, Data d)
{
    Node * new_node = new Node(k, d);
    if (root == NULL){
        root = new_node;
    }
    else
    {
        Node* current_note = root;
        //bool flag = true;
        while (true)
        {
            if (current_note->key == k)
            {
                current_note->value = d;
                break;
            }
            else
            if (current_note->key > k)
                if (current_note->left == NULL) {
                    current_note->left = new_node;
                    break;
                }
                else
                    current_note = current_note->left;
            else
            if (current_note->right == NULL) {
                current_note->right = new_node;
                break;
            }
            else
                current_note = current_note->right;
        }
    }
    size++;
}
//Удаляет значение по заданому ключу
template<class Key, class Data>
void Tree<Key, Data>::remove(Key key)
{
    Node * forBack = root;
    Node * forDelete = root;
    while (forDelete->key != key ){
        forBack = forDelete;
        if (key < forDelete->key)
            forDelete = forDelete->left;
        else
            forDelete = forDelete->right;
        if (forDelete == NULL) {
            std::cout << "Key not found" << std::endl;
            return;
        }
    }
    if (forDelete == root){
        Iterator iterator(forDelete->right);
        Node * forChange = iterator.begin();
//        if (iterator.getNote()->left != NULL && iterator.getNote()->right != NULL)
//            while (iterator.next()->left != NULL);
        iterator.next();
        iterator.getNote()->left = forDelete ->left;
        iterator.getNote()->right = forDelete->right;
        root = iterator.getNote();

    } else if (forDelete->left == NULL && forDelete->right == NULL) {
        if (forBack->right == forDelete)
            forBack->right = NULL;
        else
            forBack->left =NULL;
    } else if (forDelete->right !=NULL && forDelete->left == NULL){
        forBack->right = forDelete->right;
        if (forBack->right == forDelete)
            forBack->right = NULL;
        else
            forBack->left =NULL;
    } else if (forDelete->left != NULL && forDelete->right == NULL ){
        forBack->left = forDelete->left;
        if (forBack->right == forDelete)
            forBack->right = NULL;
        else
            forBack->left =NULL;
    } else {
        Iterator iterator(forDelete->right);
        if (iterator.getNote()->left != NULL && iterator.getNote()->right != NULL)
            while (iterator.next()->left != NULL);
        if (forBack->left == forDelete)
            forBack->left = iterator.getNote();
        else
            forBack->right = iterator.getNote();
        if (forDelete->left == iterator.getNote()->left){
            iterator.getNote()->left = NULL;
            forDelete->left = NULL;
        } else if (forDelete->right == iterator.getNote()->right)
            iterator.getNote()->right = NULL;
            forDelete->right = NULL;
        iterator.getNote()->left = forDelete->left;
        iterator.getNote()->right = forDelete->right;
        delete forDelete;
    }
    delete forDelete;
    size--;
    return;
}
//Обход и печать всего дерева
template<class Key, class Data>
void Tree<Key, Data>::print()
{
    Iterator iterator(this);
    Node * end = iterator.end();
    iterator.begin();
    for (int i = 0; i < iterator.level ; i++)
        std::cout << "\t";
    std::cout << iterator.getNote()->key << std::endl;
//    int countTab = 0;
    while (iterator.next()!= end ){
        for (int i = 0; i < iterator.level ; i++)
            std::cout << "\t";
        std::cout << iterator.getNote()->key << std::endl;
    }
    for (int i = 0; i < iterator.level ; i++)
        std::cout << "\t";
    std::cout << iterator.getNote()->key << std::endl;
}


#endif //LABA2BST_TREE_H
