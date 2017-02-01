// linked_list.cc -- functions for linked_list lab (cs221) 
#include "linked_list.h"

/**
 * Inserts a new Node (with key=newKey) at the head of the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: newKey is the value for the key in the new Node 
 * POST: the new Node is now the head of the linked_list
 */ 
void insert(Node*& head, int newKey) {
  Node * curr = new Node;
  curr->key  = newKey;
  curr->next = head;

  head = curr;
}

/**
 * Print the keys of a linked_list in order, from head to tail 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
void print(Node* head) {
  std::cout << "[";
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    std::cout << curr->key;
    if (curr->next != NULL) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

/** 
 * Returns the size (number of Nodes) of the linked_list  
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
int size(Node* head){ 
  if (! head) return 0; 
  return 1 + size(head->next); 
}

/**
 * Copies the keys in a linked list to a vector.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * POST: a new vector<int> containing the keys in the correct order has been returned.  
 */ 
std::vector<int> to_vector(Node* head) {
  std::vector<int> result;
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    result.push_back(curr->key); 
  }
  return result; 
}

/** 
 * Delete the last Node in the linked_list
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * POST: the last Node of the linked_list has been removed
 * POST: if the linked_list is now empty, head has been changed
 * POST: else head remains the first Node in the linked_list
 */
void delete_last_element(Node*& head){

  Node* interim = head;
  Node* curr = head;
  
  //Check if there are elements in the list
  if(head!=NULL){
    //Iterate through the list so that the result is the temporary variable containing the second last node in the list
    while(curr->next!=NULL){ 
      interim = curr; 
      curr = curr->next;
    }
    //If the second last node in the list is not NULL, then dereference the next of interim (the last node in the list)
    //if(interim!=NULL){
    interim->next = NULL;
      //}
    //If there is only one node in the list, dereference it (deleting it)
    if(interim == curr && head == interim){
      head = NULL;
    }
  
  }
}

/**
 * Removes an existing Node (with key=oldKey) from the linked_list. 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value of the key in the Node to be removed 
 * PRE: if no Node with key=oldKey exists, the linked_list has not changed 
 * POST: if a Node with key=oldKey was found, then it was deleted
 * POST: other Nodes with key=oldKey might still be in the linked_list
 * POST: head is the new first Node of the linked_list, if updated
 */ 
void remove(Node*& head, int oldKey) {
  // ******** WRITE YOUR CODE HERE ********
  if(size(head) == 0) return;

  Node* interim;
  if(head->key == oldKey){
    interim = head->next;
    head = interim;
  }
  // ******** WRITE YOUR CODE HERE ********
  for (Node* curr = head; curr != NULL; curr = curr->next){
    if (curr->next->key == oldKey) {
      
      interim = curr->next;
      curr->next = interim->next;
      
      delete interim;
      return;
      
      
    }
  }  
}

/**
 * Insert a new Node (with key=newKey) after an existing Node (with key=oldKey)
 * If there is no existing Node with key=oldKey, then no action.
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value to look for (in the key of an existing Node)  
 * PRE: newKey is the value of the key in the new Node (that might be inserted) 
 * POST: if no Node with key=oldKey was found, then the linked_list has not changed
 * POST: else a new Node (with key=newKey) is right after the Node with key = oldKey.
 */
void insert_after(Node* head, int oldKey, int newKey){
  // ******** WRITE YOUR CODE HERE ********
  if(size(head) == 0) return;
  
  Node * temp;
  for (Node* curr = head; curr != NULL; curr = curr->next){
    if(curr->key == oldKey) {
      temp = curr->next;
      Node * newNode = new Node;
      newNode->key = newKey;
      curr->next = newNode;
      newNode->next = temp; 	
    }         
  }
}

/** 
 * Create a new linked_list by merging two existing linked_lists. 
 * PRE: list1 is the first Node in a linked_list (if NULL, then it is empty)
 * PRE: list2 is the first Node in another linked_list (if NULL, then it is empty)
 * POST: A new linked_list is returned that contains new Nodes with the keys from 
 * the Nodes in list1 and list2, starting with the key of the first Node of list1, 
 * then the key of the first Node of list2, etc. 
 * When one list is exhausted, the remaining keys come from the other list.
 * For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
 */
Node* interleave(Node* list1, Node* list2){
  // ******** WRITE YOUR CODE HERE ********
  Node *interim, *start, *temp1, *temp2;
  
  //sets dummy variables for the lists
  temp1 = list1;
  temp2 = list2;

  //if there is a first element in list 1, proceed
  if(temp1!=NULL){
    
    //set up head of the new linked list
    start = new Node;
    start->key = temp1->key; //copy data from the first element in list 1 to the head
    temp1 = temp1->next; //Move the current node in list 1 to the next node
    interim = start; //set the temporary iterating node to the head of the new list
    
    while(temp1!=NULL || temp2!=NULL){ //Iterating through the linkedLists while there are still Nodes
      if(temp2!=NULL){ //Since we have already set the first element of list1 as the head, we start with list2;
	interim->next = new Node; //create a new Node in the list (as next node)
	interim->next->key = temp2->key; //sets data of the new node to that of the node from list 2 which is to be added to the new list
	temp2 = temp2->next; //Advances along list 2
	interim = interim->next; //Advances the temporary iterating node
      }
      if(temp1!=NULL){
	interim->next = new Node;
	interim->next->key = temp1->key;
	temp1 = temp1->next;
	interim = interim->next;
      }
    }
  }
  else{ //If the first list is null then we just set the new head to point to the head of list 2
    start = temp2;
  }
  
  return start;  //Returns the new list
  
}

