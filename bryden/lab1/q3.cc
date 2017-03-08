#include <iostream> 
#include <vector>

void fill_array(int, int);

int N = 10;
std::vector<int> globalArray(N);

int main(void) {
  fill_array(0,5);
  for(int i = 0; i < N; i++) {
    std::cout << globalArray[i] << std::endl;
}
}

void fill_array(int startNum, int inc) {
  for(int i = 0; i < N; i++) {
    globalArray[i] = startNum + i *  inc;
  }
}
