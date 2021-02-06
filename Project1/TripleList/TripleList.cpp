#include "TripleList.hpp"
#include <iostream>
#include <bits/stdc++.h>

void TripleList::debug()
{
   if (size == 0 || !head)
   {
      std::cout << "Empty List" << std::endl;
      return;
   }
   std::cout << "State: " << state << std::endl;
   std::cout << "Size: " << size << std::endl;
   std::cout << "Head: " << head->value << std::endl;
   printMid();
   std::cout << "Tail: " << tail->value << std::endl;
   std::cout << "List: ";
   print();

   LNode *nodePtr = head;
   for (int i = 0; i < size / 2; i++)
   {
      nodePtr = nodePtr->next;
   }
   std::cout << std::endl;
}

/**
 * private void UpdateMid(currState)
 * Updates where the middle is
 */
void TripleList::updateMid(char currState)
{
   //if size is odd, move the middle
   if (size % 2)
   {
      //
      if (state == 'L' && currState == 'L')      // if last moves were insert low (or remove high)
         middle = middle->prev;                  // move the middle left
      else if (state == 'H' && currState == 'H') // else if the last moves were insert high (or remove low)
         middle = middle->next;                  // move the middle right
   }
   state = currState;
}

/**
* Destructor                                      
* This function deletes every node in the list.   
* pre: n/a                                        
* post: destroyed object                          
**/
TripleList::~TripleList()
{
   LNode *nodePtr;  // To traverse the list
   LNode *nextNode; // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != nullptr)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}

/**
 * clear                                  
 * This function deletes every node in the list.   
 * pre: n/a                                        
 * post: destroyed object                          
 **/
void TripleList::clear()
{
   LNode *nodePtr;  // To traverse the list
   LNode *nextNode; // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != nullptr)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
   head = nullptr;
   tail = nullptr;
   middle = nullptr;
}

/**************************************
 * TripleList::insert(int num)
 * inserts num into sorted list
 * 
 * inputs:
 *    num: num to be inserted
 * 
 * outputs:
 *    void
 **************************************/
void TripleList::insert(int num)
{
   char currState;
   LNode *newNode; // To point to a new node
   LNode *nodePtr; // To move through the list

   size += 1; //increment size

   // Allocate a new node and store num there.
   newNode = new LNode;
   newNode->value = num;
   newNode->next = nullptr;
   newNode->prev = nullptr;

   // If there are no nodes in the list
   // make newNode N the first node.
   if (!head)
   {
      //set head, tail, middle to newNode N
      head = newNode;
      tail = newNode;
      middle = newNode;
      state = 'H'; //set state to inserted high
      return;
   }
   else // Otherwise, insert newNode N sorted.
   {
      // if smallest element
      if (num <= head->value)
      {
         nodePtr = head;          // temp = old head (N+1)
         newNode->next = nodePtr; // N -> next = N+1
         nodePtr->prev = newNode; // N+1 -> prev = N
         head = newNode;          // head = N
         currState = 'L';         // current state: inserted Low
      }
      // if largest element
      else if (num >= tail->value)
      {
         nodePtr = tail;          // temp = old tail (N-1)
         newNode->prev = nodePtr; // N -> prev = N-1
         nodePtr->next = newNode; // N-1 -> next = N
         tail = newNode;          // tail = N
         currState = 'H';         // current state: inserted High
      }
      // if smaller than middle
      else if (num <= middle->value)
      {
         nodePtr = middle->prev; //temp = M-1
         while (num < nodePtr->value)
         {
            nodePtr = nodePtr->prev; //temp = N-1
         }
         //insert new node after this node
         newNode->prev = nodePtr;       // N -> prev = N-1
         newNode->next = nodePtr->next; // N -> next = N+1
         nodePtr->next = newNode;       // N-1 -> next=N
         nodePtr = newNode->next;       // temp = N+1
         nodePtr->prev = newNode;       // N+1 -> prev = N
         currState = 'L';
      }
      //if greater than middle
      else
      {
         nodePtr = middle; //temp = M
         while (num > nodePtr->value)
         {
            nodePtr = nodePtr->next; //temp = N+1
         }
         //insert new node before this node
         newNode->next = nodePtr;       // N -> next = N+1
         newNode->prev = nodePtr->prev; // N -> prev = N-1
         nodePtr->prev = newNode;       // N+1 -> prev = N
         nodePtr = newNode->prev;       // temp = N-1
         nodePtr->next = newNode;       // N-1 -> next = N
         currState = 'H';
      }

      updateMid(currState);
      //
   }
}

/**
 * print()
 * prints list in ascending order
 */
void TripleList::print()
{
   LNode *nodePtr;
   nodePtr = head;
   while (nodePtr != nullptr)
   {
      std::cout << nodePtr->value << ',';
      nodePtr = nodePtr->next;
   }
   std::cout << std::endl;
}
/**
 * printRev()
 * prints list in descending order
 */
void TripleList::printRev()
{
   LNode *nodePtr;
   nodePtr = tail;
   while (nodePtr != nullptr)
   {
      std::cout << nodePtr->value << ',';
      nodePtr = nodePtr->prev;
   }
   std::cout << std::endl;
}
void TripleList::printMid()
{
   std::cout << "Middle: " << middle->value << std::endl;
}

/**
 * remove(int)
 * removes int from list
 */
void TripleList::remove(int num)
{

   // If the list is empty, do nothing.
   if (!head)
      return;
   size -= 1;
   LNode *nodePtr; // To traverse the list
   if (size == 0)  //if last element
   {

      nodePtr = head;
      delete nodePtr;
      head = nullptr;
      tail = nullptr;
      middle = nullptr;
      return;
   }

   LNode *previousNode; // To point to the previous node
   char currState;

   // Determine if the first node is the one.
   if (head->value == num)
   {

      nodePtr = head;       // temp = head
      head = head->next;    // head is now N+1
      head->prev = nullptr; // head has no prev
      delete nodePtr;       // remove old head (min)
      updateMid('H');       // update middle (remove low ≡ add high)
      //
   }
   // Determine if the last node is the one.
   else if (tail->value == num)
   {

      nodePtr = tail;       // temp = old tail
      tail = tail->prev;    // tail is now N-1
      tail->next = nullptr; // tail has no next
      delete nodePtr;       // remove old tail (max)
      updateMid('L');       // update middle (remove high ≡ add low)
   }
   // Determine if the middle node is the one.
   else if (middle->value == num)
   {

      //
      nodePtr = middle->next;       // temp1 = M+1
      previousNode = middle->prev;  // temp2 = M-1
      previousNode->next = nodePtr; // M-1 -> next = M+1
      nodePtr->prev = previousNode; // M+1 -> prev = M-1
      delete middle;                // delete the middle (M)
      if (state == 'L')
      {

         middle = previousNode; // middle becomes M-1
         state = 'H';           // state alternates to avoid moving middle TEST_THIS
      }
      else
      {

         middle = nodePtr; // middle becomes M-1
         state = 'L';      // state alternates to avoid moving middle TEST_THIS
      }
   }
   // Determine whether to search left or right of middle
   else
   {

      bool greater = num > middle->value; //check if num is greater or less than middle
      // Initialize nodePtr to left of middle
      nodePtr = greater ? middle->next : middle->prev; // if num>middle go right (towards next)
      currState = greater ? 'L' : 'H';                 //set currstate to 'L' if removing greater than middle, else 'H'

      // Skip all nodes whose value member is
      // not equal to intVar.

      while (nodePtr != nullptr && nodePtr->value != num)
      {
         nodePtr = greater ? nodePtr->next : nodePtr->prev; // if num>middle go right (towards next)
      }

      // If nodePtr is not at the end of the list,
      // link the previous node to the node after
      // nodePtr, then delete nodePtr.
      if (nodePtr)
      {

         if (greater) //traversing right, prev=N-1
         {

            previousNode = nodePtr->prev;
            previousNode->next = nodePtr->next; // N-1 -> next = N+1
            previousNode = nodePtr->next;       // temp = N+1
            previousNode->prev = nodePtr->prev; // N+1 -> prev = N-1
         }
         else //traversing left, prev=N+1
         {
            previousNode = nodePtr->next;
            previousNode->prev = nodePtr->prev; // N+1 -> prev = N-1
            previousNode = nodePtr->prev;       // temp = N+1
            previousNode->next = nodePtr->next; // N-1 -> next = N+1
         }

         delete nodePtr; // delete node N
      }

      updateMid(currState);

      //
   }
}

/**
 * removeMin()
 * removes smallest element on list
 */
void TripleList::removeMin()
{
   if (!head) //empty list
      return;
   size -= 1;     // update size
   if (size == 0) //last element
   {
      delete head;
      head = nullptr;
      tail = nullptr;
      middle = nullptr;
      return;
   }
   else
   {
      LNode *nodePtr;       // temp node
      nodePtr = head;       // temp = head
      head = head->next;    // head is now N+1
      head->prev = nullptr; // head has no prev
      delete nodePtr;       // remove old head (min)
      updateMid('H');       // update middle (remove low ≡ add high)
   }
}

/**
 * removeMax()
 * removes the largest element on list
 **/
void TripleList::removeMax()
{
   if (!head) //empty list
      return;
   size -= 1;     // update size
   if (size == 0) //last element
   {
      delete head;
      head = nullptr;
      tail = nullptr;
      middle = nullptr;
      return;
   }
   else
   {
      LNode *nodePtr;       // temp node
      nodePtr = tail;       // temp = old tail
      tail = tail->prev;    // tail is now N-1
      tail->next = nullptr; //tail has no next
      delete nodePtr;       // remove old tail (max)
      updateMid('L');       // update middle (remove high ≡ add low)
   }
   //
}

/**
 * getMin()
 * returns int containing smallest element
 **/
int TripleList::getMin()
{
   if (size == 0)
      return INT_MAX;
   return head->value;
}

/** 
 * getMax()
 *  returns int containing largest element
 **/
int TripleList::getMax()
{
   if (size == 0)
      return INT_MIN;
   return tail->value;
}

/**
 * popMin()
 * removes smallest element and returns its value
 **/
int TripleList::popMin()
{
   if (!head) //empty list
      return INT_MAX;
   size -= 1;     // update size
   if (size == 0) //last element
   {
      int val = head->value;
      delete head;
      head = nullptr;
      tail = nullptr;
      middle = nullptr;
      return val;
   }
   else
   {
      LNode *nodePtr;        // temp node
      nodePtr = head;        // temp = head
      int val = head->value; //get min value
      head = head->next;     // head is now N+1
      head->prev = nullptr;  // head has no prev
      delete nodePtr;        // remove old head (min)
      updateMid('H');        // update middle (remove low ≡ add high)
      return val;
   }
}

/**
 * popMax()
 * removes largest elemeent and returns its value
 **/
int TripleList::popMax()
{
   if (!head) //empty list
      return INT_MIN;
   size -= 1;     // update size
   if (size == 0) //last element
   {
      int val = head->value;
      delete head;
      head = nullptr;
      tail = nullptr;
      middle = nullptr;
      return val;
   }
   else
   {
      LNode *nodePtr;           // temp node
      nodePtr = tail;           // temp = old tail
      int val = nodePtr->value; //get value
      tail = tail->prev;        // tail is now N-1
      tail->next = nullptr;     //tail has no next
      delete nodePtr;           // remove old tail (max)
      updateMid('L');           // update middle (remove high ≡ add low)
      return val;
   }
}