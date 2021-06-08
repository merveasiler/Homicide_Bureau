#ifndef PROBABILITYHEAP_H_
#define PROBABILITYHEAP_H_

#include "HashTable.h"

template<class Key, class Probability>
class ProbabilityHeap {

public:	// DO NOT CHANGE THIS PART.

	ProbabilityHeap(Key heap_empty, Probability suspect_not_on_heap)
		: HEAP_EMPTY(heap_empty), SUSPECT_NOT_ON_HEAP(suspect_not_on_heap) {
		initialize();	// You can do initializations inside initialize() method.
	};

	// Should be called for adding suspects to the heap.
	// The method will not have no effect if the suspect is already on the heap. 
	void insert(const Key& key, const Probability& probability);

	// NOTE: This method is expected to return HEAP_EMPTY, 
	// if the heap is empty
	const Key deleteMax();

	// Will update the probability value of the suspect if it is on the heap
	// will not effect the heap otherwise. 
	void updateProbability(const Key& key, const Probability& newProbability);

	// NOTE: This method is expected to return SUSPECT_NOT_ON_HEAP, 
	// if the item with the key is not on the heap
	const Probability& getProbability(const Key& key) const;

	// NOTE: print method will not be tested, you may use for debugging purposes.
	void print();

private:

	int capacity;
	const Key HEAP_EMPTY;
	const Probability SUSPECT_NOT_ON_HEAP;
	void initialize();	// You can do initializations inside initialize() method.

	// NOTE: You may add private members or method declarations under this line

	HashTable<Key, Probability> probabilityHash;	// holds [key : probability] pair
	HashTable<Key, int> heapIndexHash;				// holds [key : heap index] pair
	int heapSize;
	vector<Key> keyArray;

	void percolateDown(int hole);
	void percolateUp(int hole);
	void resizeKeyArray();

};

#endif