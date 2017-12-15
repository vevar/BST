#include "iostream"
#include "Tree.h"

using namespace std;

template<class Key,class Data>
void inputTreeRandom(Tree<Key,Data>* tree, int n) {
    for (int i = 0; i < n; i++)
    {
        Key key = (int)(rand() % 100);
        Data data = (int)(rand() % 100);
        tree->put(key, data);
    }
}

int main(){
    Tree<int, double>* tree = new Tree<int, double>();
    inputTreeRandom(*&tree, 50);
    Tree<int, double>::Iterator iterator(&*tree);
//    tree->remove(69);
    tree->print();
//    cout << iterator.begin()->value<<endl;
//    tree->clear();
    return 0;
}
