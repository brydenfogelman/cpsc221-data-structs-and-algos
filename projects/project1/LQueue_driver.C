/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
using namespace std;
	

void print(Queue q)
{ q.display(cout); }

int main(void)
{
   Queue q1;
   cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

   cout << "How many elements to add to the queue? ";
   int numItems;
   cin >> numItems;
   for (int i = 1; i <= numItems; i++) 
      q1.enqueue(100*i);

   cout << "Contents of queue q1 (via  print):\n";
   print(q1); 
   cout << endl;

   Queue q2;
   q2 = q1;
   cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
   print(q2); 
   cout << endl;

   cout << "Queue q2 empty? " << q2.empty() << endl;

   cout << "Front value in q2: " << q2.front() << endl;

   while (!q2.empty())
   {
     cout << "Remove front -- Queue contents: ";
     q2.dequeue();
     q2.display(cout);
   }
   cout << "Queue q2 empty? " << q2.empty() << endl;
   cout << "Front value in q2?" << endl << q2.front() << endl;
   cout << "Trying to remove front of q2: " << endl;
   q2.dequeue();
   //system("PAUSE");
   cout << endl;

   cout << "###########################" << endl;
   cout << "Test move_to_front function\n" << endl;
  Queue q3;
  for (int i = 1; i <= 5; i++) 
      q3.enqueue(100*i);

  cout << "Contents of queue q3 (via  print):\n";
  print(q3); 
  cout << endl;

  cout << "Move Queue Element 200 to front:\n";
  q3.move_to_front(200);
  cout << endl;

  cout << "Front value in q3?" << endl << q3.front() << endl;

  cout << "Trying to moving value that is already front:\n";
  q3.move_to_front(200);
  cout << "Front value in q3?" << endl << q3.front() << endl;

  cout << "Trying moving value not in queue:\n";
  q3.move_to_front(600);
  cout << endl;

  while (!q3.empty())
   {
     q3.dequeue();
   }

   cout << "Queue q3 empty? " << q3.empty() << endl;
   cout << "Trying moving item in empty queue: " << endl;
   q3.move_to_front(100);
   cout << endl;

   cout << "###########################" << endl;
   cout << "Test move_to_front function\n" << endl;

   Queue q4, q5;
  for (int i = 1; i <= 5; i++) 
  {
      q4.enqueue(i+2);
      q5.enqueue(i);
  }

  cout << "Contents of queue q4 (via  print):\n";
  print(q4);
  cout << endl;
  cout << "Contents of queue q5 (via  print):\n";
  print(q5); 
  cout << endl;

  cout << "Merge q4 and q5:\n";
  q4.merge_two_queues(q5);
  cout << endl;
  cout << "Contents of queue q4 (via  print):\n";
  print(q4);
  cout << endl;
  cout << "Contents of queue q5 (via  print):\n";
  print(q5); 
  cout << endl;

   return 0;
}
