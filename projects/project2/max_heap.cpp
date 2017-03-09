/*--- max_heap.cpp -----------------------------------------------
  This file implements hax_heap.hpp member functions.
-------------------------------------------------------------------------*/

#include "max_heap.hpp"
#include <stdexcept>

using namespace std;

max_heap::max_heap(int n){
	data = new text_item[n];
	numItems = 0;
	max_capacity = n;
}

max_heap::~max_heap()
{ 
	delete [] data;
}

bool max_heap::empty() const {
	return (numItems == 0);
}
bool max_heap::full() const {
	return (numItems == max_capacity);
}

int max_heap::size() const {
	return numItems;
}	

text_item& max_heap::top() {
	if (empty()) {
		throw std::logic_error("Heap is empty, can't access top!");
	}
	return data[0];
}

// Helper function used for testing. Explained in README.txt
void max_heap::print_heap(int node, int d) {
	if(empty()) return;

	d++;

	// right
	int right = 2 * node + 2;
	if(right < numItems) print_heap(right, d);

	for(int i = 0; i < d; i++){
	cout<<"  ";
	}

	cout<<data[node].freq<<" "<<endl;

	//left
	int left = 2 * node + 1;
	if(left < numItems) print_heap(left, d);

}


//--- You must comple the following functions: 
text_item max_heap::delete_max() {
	if (empty()) {
		throw std::logic_error("Cannot delete, heap is empty!");
	} else {

		// save the item to be deleted for the return
		text_item to_delete = data[0];
		
		// set root to last element
		data[0] = data[numItems-1];
		numItems--;

		// swap down starting at root to rebuild heap
		swap_down(0);

		// return deleted node
		return to_delete;
	}
}

void max_heap::swap_down(int i) {

	int leftChild = 2 * i + 1;
	int rightChild = 2 * i + 2;
	int max = i;
	
	// find who holds the max item if i's childrend
	if(leftChild < numItems && data[leftChild].freq > data[max].freq)
		max = leftChild;
	if(rightChild < numItems && data[rightChild].freq > data[max].freq)
		max = rightChild;

	// if the max has changed swap it then coutinue to recursively swapdown
	if(max != i) {
		text_item temp = data[i];
		data[i] = data[max];
		data[max] = temp;
		swap_down(max);
	}

}

void max_heap::insert(const text_item & item) {
	if (full()) {
		throw std::logic_error("Cannot insert, heap array is full!");
	} else {
		// if item set first value of array
		if(empty()) {
			data[0] = item;
			numItems++;
		} else {
			// add item to last position of array
			data[numItems] = item;
			// make sure heap behaves invariant
			swap_up(numItems);
			// increment num items
			numItems++;
		}
	}
}

void max_heap::swap_up(int i) {
	// make sure we can still access the array
	if(i >= 0) {
		text_item parent = data[(i-1)/2];
		text_item curr = data[i];

		// swap when curr node is greater then parent
		if(curr.freq > parent.freq) {
			// swap in array
			data[(i-1)/2] = curr;
			data[i] = parent;

			// recursively swap up with parent index
			swap_up((i-1)/2);
		
		}
	}
}
