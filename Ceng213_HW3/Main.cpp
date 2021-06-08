#include "HashTable.h"
#include "HashTable.cpp"
#include "ProbabilityHeap.h"
#include "ProbabilityHeap.cpp"

int main() {

    string HEAP_EMPTY = "empty heap";
    ProbabilityHeap<string, float> suspectList(HEAP_EMPTY, -1);

    suspectList.insert("Gollum", 0.5);
    suspectList.insert("Gandalf", 0.4);
    suspectList.insert("Arwen", 0.8);
    cout << "Max Key: " << suspectList.deleteMax() << endl;
    suspectList.insert("Frodo", 0.3);
    suspectList.insert("Ew", 0.7);
    cout << "Max Key: " << suspectList.deleteMax() << endl;
    cout << "Max Key: " << suspectList.deleteMax() << endl;
    suspectList.insert("Arag", 0.3);
    suspectList.insert("Sauron", 0.5);
    cout << "Max Key: " << suspectList.deleteMax() << endl;
    cout << "Max Key: " << suspectList.deleteMax() << endl;
    cout << "Max Key: " << suspectList.deleteMax() << endl;
    cout << "Max Key: " << suspectList.deleteMax() << endl;

    cout << endl;
    return 0;
}