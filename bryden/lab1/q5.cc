#include <cstdlib> // for atoi
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
 // srand(1);
 int num_to_guess = rand() % 100 + 1; 
 // std::cout << num_to_guess << std::endl;
 int guess;

 while(1) {
  std::cout << "Enter a guess between 1 and 100 (enter -1 to quit):" << std::endl;
  std::cin >> guess;
  if(guess == -1) {
    std::cout << "User has quit the game" << std::endl;
    break;
   }
  if( guess > 100 || guess < 1) {
   std::cout << "Guess must be between 1 and 100!" << std::endl;
   continue;
  }
  if(num_to_guess == guess) {
   std::cout << "You guessed right!" << std::endl;
   break;
  }
 } 
} 
