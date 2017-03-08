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

void max_heap::print_heap(int node=0, int d=0) {
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

	// for(int i = 0; i < numItems; i++) {
	// 	cout << data[i] << " ";
	// }
	// cout << endl;
}


//--- You must comple the following functions: 


text_item max_heap::delete_max() {
	if (empty()) {
		throw std::logic_error("Cannot delete, heap is empty!");
	} else {
		
		// set root to last element
		data[0] = data[numItems];
		numItems--;

		// swap down starting at 
		swap_down(0);

		return top();
	}
}

void max_heap::swap_down(int i) {

	int leftChild = 2 * i + 1;
	int rightChild = 2 * i + 2;
	int max = i;
	
	// find who holds the max item if i's childrend
	if(leftChild < max_capacity && data[leftChild].freq > data[max].freq)
		max = leftChild;
	if(rightChild < max_capacity && data[rightChild].freq > data[max].freq)
		max = rightChild;

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
		if(empty()) {
			data[0] = item;
			numItems++;
		} else {
			data[numItems] = item;
			swap_up(numItems);
			numItems++;
		}
	}
}

void max_heap::swap_up(int i) {
	if(i >= 0) {
		// ADD CODE HERE

		text_item parent = data[(i-1)/2];
		text_item curr = data[i];
		// cout << parent.freq << " " << curr.freq << endl;
		// swap when curr node is greater then parent
		if(curr.freq > parent.freq) {
			// swap in array
			data[(i-1)/2] = curr;
			data[i] = parent;
			// cout << data[(i-1)/2] << " " << data[i] << endl;
			swap_up((i-1)/2);
		
		}
	}
}
