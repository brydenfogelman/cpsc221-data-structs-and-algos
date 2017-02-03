/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new Queue::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0)
         {
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{ 
   return (myFront == 0); 
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value)
{
   Queue::NodePointer newptr = new Queue::Node(value);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
   if (!empty())
      return (myFront->data);
   else
   {
	return 0;
   }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

void Queue::move_to_front(const QueueElement & value) 
{
    if(!empty())
    {
        Queue::NodePointer ptr;
        Queue::NodePointer temp;

        // if the first element is already the front of the queue return
        if(front() == value) {
            return;
        }
	// if we want to move back to front, we can quickly perform this
	// also the loop below does not need to check the back case

        // find the location of the QueueElement
        for (ptr = myFront; ptr->next != 0; ptr = ptr->next)
        {
    		// if the next item in the queue has the value
            if(ptr->next->data == value) {
                // set the node to move as temp
                temp = ptr->next;
		
		// the case when we are looking at the back item;		
		if(temp->next == 0) {
			// swap front and back
			temp = myFront;
			myFront = myBack;
			myFront->next = temp;
			ptr->next = 0;
			myBack = ptr;
			return; 
		} else {
                	// close the queue where we took the value out
                	ptr->next = temp->next;
			temp->next = myFront;
			myFront = temp;
			return;
		}
            }
        }

        cerr << "*** The value does not exist in the queue ***\n";
        
    } else {
      cerr << "*** Queue is empty -- can't move a value ***\n";
    }

}

void Queue::merge_two_queues(Queue & q2)
{
  // if q2 is empty the result is q1
  if(q2.empty()) return;

  // create queue to hold contents of this queue
  Queue q1; 

  Queue::NodePointer q1ptr = 0; // always points to the smaller value
  Queue::NodePointer q2ptr = 0; // always points to the larger value
  
  // if the current queue is empty skip this part
  if(!empty()) {

  // add all the values of this queue to q1
  while(!empty())
   {
         q1.enqueue(front());
         dequeue();
    }

  Queue q3;

  // check which queue starts at a smaller value
  if(q1.myFront->data > q2.myFront->data) {
    // if q2 starts with a smaller value set it to q1ptr
    q1ptr = q2.myFront;
    q2ptr = q1.myFront;
  } else {
    // if q1 starts with a smaller value set it to q1ptr
    q1ptr = q1.myFront;
    q2ptr = q2.myFront;
  }
  } else {
	q2ptr = q2.myFront;
  }
  
  // Create new queue to hold results

  // for (q1ptr = myFront; q1ptr->next != 0; q1ptr = q1ptr->next)
  while(q1ptr != 0)
  {	
    // check which queue has a smaller value
    if(q1ptr->data > q2ptr->data) 
    {
      // since q2 has a smaller value, swap q1ptr and q2ptr
      Queue::NodePointer temp = q1ptr;

      q1ptr = q2ptr;

      // remove elements from q2 since we will be adding the q2 value later
      q2.dequeue();

      // set q2ptr to q1
      q2ptr = temp;
    } else {
      dequeue();
    }
    
    //currentFront->next = q1ptr;
    enqueue(q1ptr->data);    
    // point to the next value in q1ptr
    q1ptr = q1ptr->next;
  }

  // add leftover values in q2 that are greater then the largest value from q1
  while(q2ptr != 0) {
    q3.enqueue(q2ptr->data);

    // remove elements from q2
    q2.dequeue();
    
    q2ptr = q2ptr->next;
  }
  
}
