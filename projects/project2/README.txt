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

	--runway.C:  Contains the simulation code for Part 2.  
	  	      This is the primary source file for the airport simulation program 

	--LQueue.h:  Header file for Queue implementation

	--LQueue.C:  File defining Queue data structure and implementation

	--LQueue_driver.C:  Test Code for LQueue data structure
	
	--sampleOutput2.txt:  Sample output from ./runway


New functions:

max_heap::print_heap(int node, int d)

We have implemented a print_heap function to display results when testing.
This function is just used for testing and makes it easier to debug and 
explain results. In practice we would want to use asserts but for the purpose
of this project, printing the heap is more useful. The code for this
function is the same as what was used in the binaryHeap lab.

max_heap.cpp & max_heap.hpp were modified to accomodate this function.
