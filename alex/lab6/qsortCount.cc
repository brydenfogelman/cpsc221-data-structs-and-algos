#include <iostream>
#include <ctime>
#include <cstdlib>

int * x;

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
		if (x[i] < x[a])
			swap(x[++m], x[i]);
	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

int qc(int n) {
  if(n==0) return 0;
  int comps = 0;
  int m = 0;
  int i;
  // in-place partition:
  for (i = 0; i < n; i++) {
    
    if(i%2 == 0){
      m++;
      comps++;
    }
  }

  comps+=qc(m-1);
  comps+=qc(n-m);

  return comps;
}

#define NN 1000

int main(int argc, char *argv[]) {
	srand(time(0));

	// change the following code
	x = new int[NN];
	for (int i=0; i<NN; ++i) {
		x[i] = rand() % NN;
	}
	
	std::cout << std::endl;

	std::cout << qc(NN) <<std::endl;

	delete[] x;
	return 0;
}

