//
// Created by webve on 16.12.2017.
//
#ifndef TEST

#pragma once

#include <ctime>
#include "Tree.h"




class Test {
    typedef int KeyType;
    typedef int DataType;
    int readings_Add;
    int readings_Remove;
    int readings_Find;
public:
    static void test_randomTree(int n){
//        srand((time(0)));
        Tree<KeyType ,DataType> tree;
        KeyType arrayKeys[n];
        DataType data = (DataType)(rand() % (n*100));
        std::cout << "Labor intensity: " <<std::endl;
        for (int i = 0; i < n ; i++) {
            KeyType key = (KeyType )(rand() % (n*100));
            tree.put(key,data);
        }

        //Add
        double avgAdd = 0;
        for (int i = 0; i < n ; i++) {
            KeyType key = (KeyType )(rand() % (n*100));
            tree.put(key,data);
            arrayKeys[i] = key;
            avgAdd += tree.readings;
        }
        avgAdd /= (double)n;
        std::cout << "Add: " << avgAdd << std::endl;

        //Find
        double avgFind = 0;
        for (int i = 0; i < n; i++) {
            tree.get(arrayKeys[i]);
            avgFind += tree.readings;
        }
        avgFind /= (double)n;
        std::cout << "Find: " << avgFind << std::endl;

        //Remove
        double avgRemove = tree.readings / (double)n;
        for (int i = 0; i < n ; i++) {
            tree.remove(arrayKeys[i]);
            avgRemove += tree.readings;
        }
        avgRemove /= (double)n;
        std::cout << "Remove: " << avgRemove << std::endl;
    }
};


#endif //TEST
