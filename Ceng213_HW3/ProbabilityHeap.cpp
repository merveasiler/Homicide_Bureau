#include "ProbabilityHeap.h"

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::initialize() {
	capacity = 3;	// 2+1
	heapSize = 0;
	keyArray.resize(capacity);
}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::percolateDown(int hole) {
	int child;
	Key k = keyArray[hole];
	Probability p = getProbability(k);

	for (; hole * 2 <= heapSize; hole = child)
	{
		child = hole * 2;
		if (child != heapSize && getProbability(keyArray[child + 1]) > getProbability(keyArray[child]))
			child++;
		if (getProbability(keyArray[child]) > p) {
			keyArray[hole] = keyArray[child];
			heapIndexHash.insert(keyArray[child], hole);		// it updates the current bucket where the key is in
		}
		else
			break;
	}

	keyArray[hole] = k;
	heapIndexHash.insert(k, hole);								// it updates the current bucket where the key is in

}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::percolateUp(int hole) {

	Key k = keyArray[0];
	Probability p = getProbability(k);

	for (; p > getProbability(keyArray[hole / 2]); hole /= 2) {
		keyArray[hole] = keyArray[hole / 2];
		heapIndexHash.insert(keyArray[hole / 2], hole);		// it updates the current bucket where the key is in
	}

	keyArray[hole] = k;
	heapIndexHash.insert(k, hole);							// it updates the current bucket where the key is in

}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::resizeKeyArray() {
	for (int i = 0; i < 15; i++)
		if (capacity - 1 == primeNumbers[i]) {
			capacity = primeNumbers[i + 1] + 1;
			break;
		}
	vector<Key> tempKeyArray = keyArray;
	tempKeyArray.resize(capacity);
	for (int i = 1; i <= heapSize; i++)
		tempKeyArray[i] = keyArray[i];
	keyArray.resize(capacity);
	keyArray = tempKeyArray;
}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::insert(const Key& key, const Probability& probability) {

	if (getProbability(key) != SUSPECT_NOT_ON_HEAP)
		return;		// it is already inserted

	probabilityHash.insert(key, probability);
	heapIndexHash.insert(key, 0);	// later it will be updated inside percolateUp()

	// percolate up
	if (heapSize + 1 == capacity)
		resizeKeyArray();

	keyArray[0] = key;	// temporarily hold there
	heapSize++;
	percolateUp(heapSize);

}

template<class Key, class Probability>
const Key ProbabilityHeap<Key, Probability>::deleteMax() {

	if (heapSize == 0)
		return HEAP_EMPTY;

	Key maxKey = keyArray[1];
	keyArray[1] = keyArray[heapSize];
	heapSize--;
	percolateDown(1);

	probabilityHash.remove(maxKey);
	heapIndexHash.remove(maxKey);
	return maxKey;

}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::updateProbability(const Key& key, const Probability& newProbability) {

	if (getProbability(key) == SUSPECT_NOT_ON_HEAP)
		return;

	Probability oldProbability = getProbability(key);
	probabilityHash.insert(key, newProbability);	// it updates the current bucket where the key is in

	if (oldProbability < newProbability)
		percolateUp(heapIndexHash.find(key)->getValue());
	else if (oldProbability > newProbability)
		percolateDown(heapIndexHash.find(key)->getValue());

}

template<class Key, class Probability>
const Probability& ProbabilityHeap<Key, Probability>::getProbability(const Key& key) const {
	const HashTableItem<Key, Probability>* item = probabilityHash.find(key);
	if (item == NULL)
		return SUSPECT_NOT_ON_HEAP;
	return item->getValue();
}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::print() {

}