#include <iostream>
#include <ctime>
#include <cstdlib>

int * x;
int comp = 0;

void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint(int a, int b) {
	return a + (rand() % (b - a + 1));
}

void quicksort(int a, int b) {
	if (a >= b) return;
	int p = randint(a,b); // pivot
	swap(x[a], x[p]);
	int m = a;
	int i;
	// in-place partition:
	for (i = a+1; i <= b; i++) {
		comp++;
		if (x[i] < x[a])
			swap(x[++m], x[i]);
	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

#define NN 200

int main(int argc, char *argv[]) {
	srand(time(0));

	// change the following code
	x = new int[NN];
	for (int i=0; i<NN; ++i) {
		x[i] = rand() % NN;
	}
	int comp_avg = 0;
	for (int j=0; j<100; j++){
		comp = 0;	
		quicksort(0, NN-1);
		comp_avg += comp;
		std::cout << comp << " ";
	}
	
	std::cout << std::endl;
	std::cout << "Average comparison " << comp_avg / 100 << std::endl;
	/*
	for (int i=0; i<NN; ++i) {
		std::cout << x[i] << " ";
	}
	std::cout << std::endl;
	*/
	delete[] x;
	return 0;
}

