#include <iostream>

#include "string_bst.hpp"
#include "max_heap.hpp"
#include "text_item.hpp"
#include "util.hpp"

using namespace std;

//--- PART 1A: Implementation and testing of heap insert
void heap_insert_tests(max_heap &hp) {
	text_item temp;
	std::string word = "item";

	int N = 10;
	int test_arr[10] = {10,5,15,30,35,50,25,20,40,45};

	// NOTE: create a custom heap instead of using a random number generator
	// int random_num;
	// long int seed = long(time(0));    // seed for random number generator
	// srand(seed);
	
	//--- Testing insert functionality
	std::cout << "*** TESTING BASIC INSERT ***" << std::endl;

	for (int i = 0 ; i < N; i++) {
		string text = word;
		text += std::to_string(i+1);
		std::cout << "adding " << text << ",  with number " << test_arr[i] << " to heap" << std::endl;
		hp.insert(text_item{text, test_arr[i]});	
		temp = hp.top();
		std::cout << "Top of heap is: " << temp << std::endl;		
	}
	
	//--- Specific insert functionality that should be tested:
	// insert without any swap_ups needed
	cout << endl;
	cout << "*** NO SWAP UPS ***" << endl;

	text_item test1 = text_item{"test1", 0};
	hp.insert(test1);
	std::cout << "adding " << "test1" << ",  with number " << 0 << " to heap" << std::endl;
	
	// helper function created in max_heap to print heap
	hp.print_heap();

		
	// insert with a swap_up / multiple swap_ups
	cout << endl;
	cout << "*** MULTIPLE SWAP UPS ***" << endl;

	text_item test2 = text_item{"test2", 38};
	hp.insert(test2);
	std::cout << "adding " << "test2" << ",  with number " << 38 << " to heap" << std::endl;

	// helper function created in max_heap to print heap
	hp.print_heap();
}

//--- PART 1B: Implementation and testing of heap delete
void heap_delete_tests(max_heap &hp) {
	text_item temp;

	hp.print_heap();
	
	//--- Testing deleteMax functionality
	std::cout << "*** TESTING DELETEMAX ***" << std::endl;
	//--- This does not fully test delete_max functionality.
	if (hp.size() > 1) {
		temp = hp.delete_max();
		std::cout << "Item returned from heap delete: "<< temp << std::endl;
		temp = hp.top();
		std::cout << "Top of heap is now: " << temp << std::endl;	
	}

	hp.print_heap();
	
	//--- Specific insert functionality that should be tested:
	
	// remove_max works when swap_down with left child
	cout << endl;
	cout << "*** SWAP DOWN WITH LEFT CHILD ***" << endl;
		
	// remove_max works when swap_down with right child
	cout << endl;
	cout << "*** SWAP DOWN WITH RIGHT CHILD ***" << endl;
		
	// remove_max on an empty heap (should throw exception similar to top())
	cout << endl;
	cout << "*** EMPTY HEAP ***" << endl;

	// delete until empty
	while(hp.size() > 1) {
		temp = hp.delete_max();
	}

	cout << "Current size of heap: " << hp.size() << endl;
	try {
		temp = hp.delete_max();
	} catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	
		
}

//--- PART 2: Implementation and testing of BST word_frequency
void tree_tester(string_bst const &tree) {
	std::cout << std::endl << "BEGINNING TESTS FOR PART 2" << std::endl;
	string to_find = "difficult";
	int num_times = 0;
	//--- Testing word_frequency functionality
	//--- This does not fully test word_frequency functionality.
	if (tree.size() > 1) {
	  num_times = tree.word_frequency(to_find);
	  std::cout << "Found: "<< to_find << 
	    " in the input file " << num_times 
		    << " time(s)." << std::endl;
	}

	//tree.display();
	
	//--- Specific word_frequency functionality that should be tested:
	
	// can search through both left and right subtrees if not found at current node
	to_find = "bee";
	if (tree.size() > 1) {
		num_times = tree.word_frequency(to_find);
		std::cout << "Found: "<< to_find << 
			" in the input file " << num_times 
			<< " time(s)." << std::endl;
	}

	to_find = "then";
	if (tree.size() > 1) {
		num_times = tree.word_frequency(to_find);
		std::cout << "Found: "<< to_find << 
			" in the input file " << num_times 
			<< " time(s)." << std::endl;
	}
	
	// returns 0 if word is not found
	to_find = "ajsogneislasd";
	if (tree.size() > 1) {
	
	        num_times = tree.word_frequency(to_find);
		std::cout << "Found: "<< to_find << 
			" in the input file " << num_times 
			<< " time(s)." << std::endl;
	}
			
}

//--- PART 3: Implementation and testing of word frequency analysis
void overall_most_freq(max_heap hp) {
	std::cout << "*** Top 5 most frequent words: ***" << std::endl;

	// make sure only 5 words are printed
	int count = 0;

	// print while the heap has items and at most 5
	while(hp.size() > 1 && count < 5) {
		std::cout << hp.top() << std::endl;
		count++;

		// delete max will cause the tree to be restructured with the
		// next most frequent node as root
		hp.delete_max();
	}

}

void at_least_length(max_heap hp, size_t num_letters) {
	cout << "*** Top 5 most frequent words with at least " 
		<< num_letters << " letters ***" << std::endl;
		
	// make sure only 5 words are printed
	int count = 0;

	// create temp variable for text_item
	text_item temp;

	// print while the heap has items and at most 5
	while(hp.size() > 1 && count < 5) {
		// get current most frequent node
		temp = hp.top();

		// if the string length is equal to the input specified then print
		if(temp.word.size() >= num_letters) {
			std::cout << temp << std::endl;
			count++;
		}

		// delete max will cause the tree to be restructured with the
		// next most frequent node as root
		hp.delete_max();
	}
	
}

void starts_with(max_heap hp, char starts_with_letter) {
	cout << "*** Top 5 most frequent words that begin with " 
		<< starts_with_letter << " ***" << std::endl;

	// make sure only 5 words are printed
	int count = 0;

	// create temp variable for text_item
	text_item temp;

	// print while the heap has items and at most 5
	while(hp.size() > 1 && count < 5) {
		// get current most frequent node
		temp = hp.top();

		if(temp.word[0] == starts_with_letter) {
			std::cout << temp << std::endl;
			count++;
		}

		// delete max will cause the tree to be restructured with the
		// next most frequent node as root
		hp.delete_max();
	}

}

void heap_tester() {	
	text_item temp;
	int heap_size = 10; //feel free to create heaps of other sizes when testing
	
	cout << "How many items should be added to heap? ";
	cin >> heap_size;
	if(heap_size < 12) {
		heap_size = 12;
		cout << "Heap size must be at least 12. Now size set to 12" << endl;
	}

	max_heap hp(heap_size);
	std::cout << "Created heap of size " << heap_size << std::endl;
		
	//--- Testing heap size and top
	std::cout << "Current number of items in heap is: " << hp.size() << std::endl;
	try {
		temp = hp.top(); //should throw and exception without items in heap
		std::cout << "Top of heap is: " << temp << std::endl;	
	} catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	// PART 1A:
	std::cout << std::endl << "BEGINNING TESTS FOR PART 1A" << std::endl;
	heap_insert_tests(hp);
	// PART 1B:
	std::cout << std::endl << "BEGINNING TESTS FOR PART 1B" << std::endl;
	heap_delete_tests(hp);
}

//Part 4

void text_analysis_tester(string_bst &tree) {
	std::cout << std::endl << "BEGINNING TESTS FOR PART 3" << std::endl;
	overall_most_freq(copy_to_heap(tree));
	std::cout << std::endl;
	at_least_length(copy_to_heap(tree), 6); // change the 8 to test other string-lengths
	std::cout << std::endl;
	starts_with(copy_to_heap(tree), 'v'); // change the 'c' to test words that starts_with_letter
											// with different characters
}

int main(int argc, char* argv[]) {
	
	//--- Part 1: max_heap implementation
	heap_tester(); 
	
	//--- Part 2: string_bst implementation
	string_bst tree;
	load_bst("sample2.txt", tree); // create a bst from an input file.
	tree_tester(tree);			//sample2.txt contains a much bigger file
	
	//--- Part 3: word frequency analysis of text files
	text_analysis_tester(tree);

}
