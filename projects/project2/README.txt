Readme file for CPSC 221 Project 2:

Students:

Alexander Jaffray: 
  Student Number: 18175133
  CS userid: y5c9
	  
Bryden Fogelman:
  Student Number: 36294130
  CS userid: j6b9

Files:

	--Makefile:  Properly formatted and written make file for project

	--main.cpp:  File containing primary testing  

	--max_heap.cpp:  File containing data structure and methods for max heap

	--string_bst.cpp:  File containing data structure and methods for max heap

	--util.cpp:  File containing utility methods

	--text_item.cpp:  File containing text item data structure

	--sample1.txt, sample2.txt, beemovie.txt:  sample text files
	
	--output.txt:  output of test files 


New functions:

max_heap::print_heap(int node, int d)

We have implemented a print_heap function to display results when testing.
This function is just used for testing and makes it easier to debug and 
explain results. In practice we would want to use asserts but for the purpose
of this project, printing the heap is more useful. The code for this
function is the same as what was used in the binaryHeap lab.

max_heap.cpp & max_heap.hpp were modified to accomodate this function.
