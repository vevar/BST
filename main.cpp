
//#include "Tree.h"
#include "Test.h"


using namespace std;
template <class Key, class Data>
Data Data_lrand(Tree<Key,Data> *tree)
{
    return rand() << 16 | rand();
}
template<class Key,class Data>
void inputTreeRandom(Tree<Key,Data>* tree, int n) {
    for (int i = 0; i < n; i++)
    {
        Key key = (Key)(rand() % 100);
        Data data = (Data)(rand() % 100);
        tree->put(key, data);
    }
}
template<class Key, class Data>
void menu(Tree<Key,Data>* tree){
    int numKey;
    bool flagMenu = true;
    do {
        cout << "Menu:" << endl;
        cout << "1  Random generator" << endl;
        cout << "2  Add element" << endl;
        cout << "3  Remove element" << endl;
        cout << "4  Get element" << endl;
        cout << "5  Get size of tree" << endl;
        cout << "6  Is tree empty?" << endl;
        cout << "7  Print of tree" << endl;
        cout << "8  Clear of tree" << endl;
        cout << "9  Test of labor intensity with random tree" << endl;
        cout << "0  Exit" << endl;
        cout << "Input command >>";
        cin >> numKey;
        Key key;
        Data data;
        int amountElements = 0;
        switch (numKey){
            case 1:
                tree->clear();
                cout << "Input amount of elements: ";
                cin >> amountElements;
                inputTreeRandom(*&tree, amountElements);
                break;
            case 2:
                cout << "Input key: ";
                cin >> key;
                cout << "Input data: ";
                cin >> data;
                tree->put(key, data);
                break;
            case 3:
                cout << "Input key:";
                cin >> key;
                tree->remove(key);
                break;
            case 4:
                cout << "Input key:";
                cin >> key;
                tree->get(key);
                break;
            case 5:
                cout << "Size of tree: " << tree->getSize() << endl;
                break;
            case 6:
                cout << "Answer: " << tree->isEmpty() << endl;
                break;
            case 7:
                cout << "Output o tree: " << endl;
                tree->print();
                break;
            case 8:
                tree->clear();
                cout << "Size of tree: " << tree->getSize() << endl;
                break;
            case 9:
                cout << "Input amount of element: ";
                cin >> amountElements;
                Test::test_randomTree(amountElements);
                break;
            case 0:
                flagMenu = false;
                break;
            default:
                cout << "Repeat please" << endl;
                break;
        }
    }while(flagMenu);
    cout << "Done!" <<endl;
};

int main(){
    Tree<int, double>* tree = new Tree<int, double>();
    menu(*&tree);
    return 0;
}
