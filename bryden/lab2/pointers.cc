#include <iostream>
using namespace std;

int main () {
  int x = 5, y = 15;
  int * p1, *p2;
		// value of	x	y	p1	p2
		//		5	15	uninit	uninit
  p1 = &x;
                // p1 now points to the address of x
                // x = 5, y = 15, p1 = address of x, p2 = uninit
  p2 = &y;
                // p2 now points to the address of y
     		// x = 5 y = 15, p1 = address of x, p2 = address of y
  *p1 = 6;
                // set the value at the address of x to 6
		// x = 6, y = 15, p1 = address of x, p2 = address of y
  *p1 = *p2;
                // set the value at the address of x to the vale at the address of y
		// x = 15, y = 15, p1 = address of x, p2 = address of y
  p2 = p1;
                // sets p2 to have the same address as p1
		// x = 15, y = 15, p1 = address of x, p2 = address of x
  *p1 = *p2+10;
                // set the value of x using the value of y
		// x = 25, y = 15, p1 = address of x, p2 = address of x
  cout << "x " << x << " y " << y << " p1 " << p1 << " p2 " << p2 << endl;
  return 0;
}
