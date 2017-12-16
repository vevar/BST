//
// Created by webve on 12.12.2017.
//
#define TEST
#ifndef LABA2BST_TREE_H
#define LABA2BST_TREE_H


#pragma once

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
    Data search(Key key);
    int readings = 0;

    class Iterator {
        Node* pointer;
        Node* current;
        std::stack<Node*>* stack;
        std::stack<Node*>* back_stack;


    public:
        int level = 0;
        explicit Iterator(Tree* tree) {
            pointer = tree->root;
            current = tree->root;
            stack = new std::stack<Node*>();
            back_stack = new std::stack<Node*>();

        };
        explicit Iterator(Node * node){
            current = node;
            pointer = node;
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
            current = pointer;
                while (current->left != NULL) {
                    stack->push(current);
                    current = current->left;
                    level++;
                }
            return current;
        }
        //установить итератор в конец
        Node* end(){
            current = pointer;
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
                    if (!stack->empty())
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
#ifdef TEST
    readings = 0;
#endif
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
    while (!this->isEmpty()){
        Iterator iterator(this);
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
Data Tree<Key, Data>::get(Key k)
{
    return search(k);
}

//добавление данных с заданным ключем
template<class Key, class Data>
void Tree<Key, Data>::put(Key k, Data d)
{
#ifdef TEST
    readings = 0;
#endif
    Node * new_node = new Node(k, d);
    if (size == 0){
        root = new_node;
#ifdef TEST
        readings++;
#endif
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
                    else {
                        current_note = current_note->left;
#ifdef TEST
                        readings++;
#endif
                    }
                else
                if (current_note->right == NULL) {
                    current_note->right = new_node;
                    break;
                }
                else {
                    current_note = current_note->right;
#ifdef TEST
                    readings++;
#endif
                }
        }
    }
    size++;
}
//Удаляет значение по заданому ключу
template<class Key, class Data>
void Tree<Key, Data>::remove(Key key)
{
#ifdef TEST
    readings = 0;
#endif
    if(key == 3986){
        int rec = 0;
    }
    Node * forBack = root;
    Node * forDelete = root;
    while (forDelete->key != key ){
        forBack = forDelete;
        if (key < forDelete->key)
            forDelete = forDelete->left;
        else
            forDelete = forDelete->right;
#ifdef TEST
        readings++;
#endif
        if (forDelete == NULL) {
            std::cout << "Key not found" << std::endl;
            return;
        }
    }
    if (forDelete->left == NULL && forDelete->right == NULL)
        if(forBack->left == forDelete)
            forBack->left = NULL;
        else
            forBack->right = NULL;
    else if (forDelete->left == NULL && forDelete->right != NULL) {
        if(forBack->left == forDelete)
            forBack->left = forDelete->right;
        else
            forBack->right = forDelete->right;
        if (forDelete == root){
            root =  forDelete->right;
        }
    }
    else if (forDelete->right == NULL && forDelete->left != NULL) {
        if(forBack->left == forDelete)
            forBack->left = forDelete->left;
        else
            forBack->right = forDelete->left;
        if (forDelete == root){
            root =  forDelete->left;
        }
    }
    else {
        Iterator iterator(forDelete->right);
        Node *forChange;
        if (iterator.getNote()->right == NULL && iterator.getNote()->left == NULL) {
            forChange = forDelete->right;
            forDelete->right = NULL;
            if (forBack->left == forDelete)
                forBack->left = forChange;
            else
                forBack->right = forChange;
        } else {
            forChange = iterator.begin();
            Node *children = NULL;
            iterator.next();
            if (iterator.getNote()->left != forChange && iterator.getNote()->right != forChange) {
                children = iterator.getNote();
                do{
                    iterator.next();
                }
                while (iterator.getNote()->left != forChange &&  iterator.getNote()->left !=NULL);
            }
            iterator.getNote()->left = children;
        }
        forChange->left = forDelete->left;
        forChange->right = forDelete->right;
        if (forDelete == root) {
            root = forChange;
        }
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
template<class Key, class Data>
Data Tree<Key, Data>::search(Key key){
#ifdef TEST
    readings = 0;
#endif
    Node * forGet = root;
    while (forGet->key != key ){
        if (key < forGet->key)
            forGet = forGet->left;
        else
            forGet = forGet->right;
#ifdef TEST
        readings++;
#endif
        if (forGet == NULL) {
            std::cout << "Key not found" << std::endl;
            return NULL;
        }
    }
    return forGet->value;
};


#endif //LABA2BST_TREE_H
