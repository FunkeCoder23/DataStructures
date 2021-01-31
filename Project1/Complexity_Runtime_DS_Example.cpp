/*
This program and the utility programs are useful for measurements of run times.

In this example we will measure the runtimes of homegrown coded sort algorithms

The value for our Data Structures class is to have an example of measuring runtime complexity

Note that this program uses three different algorithms (for sorting) as an example.
To use it for other algorithms, the parameters in the template function (Container) will need to be changed
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>    // std::random_shuffle
#include "Complexity_Timer.hpp"
#include "Complexity_Recorder.hpp"
#include <vector>
#include <list>

// i left this here b/c i don't want to expend energy
using namespace std;

// timer
timer timer1;

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

//experiment will involve timing of 3 structures and that the number of "trials" will be 7. By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median. (The median computation is done
// in class recorder.) The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.
const int number_of_structures = 3;
const int number_of_trials = 7;

// FACTOR is &&&&&
const int FACTOR = 100;  // <==== this will influence the N (size of the problem)


// user written linked list (above) - LL - insert and delete node by node
// stl list - the list from the STL
// stl vector  - the vector from the STL

const char* headings[number_of_structures] =
{"| user list del ",
 "| vector erase   ",
 "| STL list erase "};

// The simple linked list structure with options for the experiment
// Very limited - your code would be bigger and way better
// it is simply inserting stuff, then removing stuff in a range

class LL
{
private:
   // Declare a structure for the list
   struct ListNode
   {
      int value;           // The value in this node
      struct ListNode *next;  // To point to the next node
   };

   ListNode *head;            // List head pointer

public:
   // Constructor
   LL()
      { head = nullptr; }

   // Destructor
   ~LL();

   // Linked list operations
   void appendNode(int);
   void deleteNode(int);
};


int main()
{
  int N0, N1, N2, N, K;
  N1 = 1;    // smallest sequence
  N2 = 1000;  // largest sequence

  // for our outputting of the results
  ofstream ofs("results.txt");

  // this is going to hold the measurements
  vector<recorder<timer> > stats(number_of_structures);

  // The "U" is the type for the vectors x and y, STD lists with better names
  // Using the largest sequence multiplied by factor to allocate memory
  // load everything
  // STL lists
  vector<U> x, y;
  list<U> mySTList, otSTList;
  // our list
  LL myList;

  // The times are taken for short computations by repeating those computations a number of times
  // (controlled by the variable repetitions), so that they take long enough to register nonzero times.
  // In our example where N1 = 1(meaning a sequence of length 1,000 (or, more generally, 1 * factor),
  // then the time will be computed for executing the algorithm 32 times
  int repetitions = max(32/N1, 1);

  cout << "____";
  for (int i = 0; i < number_of_structures; ++i)
    cout << headings[i];
  cout << endl;

  cout << "Size";
  for (int i = 0; i < number_of_structures; ++i)
    cout << "|      Time     ";
  cout << endl;


  for (N0 = N1; N0 <= N2; N0 *= 2)
  {

      N = N0 * FACTOR;

      K = N/2;

      // load them up
      for (int i = 0; i < N; ++i)
          x.push_back(i);

      for (int i = 0; i < N; ++i)
      {
        mySTList.push_back(i);
      }
      for (int i = 0; i < N; ++i)
      {
        myList.appendNode(i);
      }
      cout << setw(4) << N0 << flush;
      ofs << setw(4) << N0;

      int k = 0;

      for (int i = 0; i < number_of_structures; ++i)
          stats[i].reset();

      for (int j = 0; j < number_of_trials; ++j)
      {

  // Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
  // (The repetitions FACTOR is divided out when the time is later reported on the output stream.)
          for (int i = 0; i < number_of_structures; ++i)
          {
             timer1.restart();
             for (k = 0; k < repetitions; ++k)
             {
               x = y;
               if (i == 0)
               {
                 for (int n = 0; n < N; ++n)
                  {
                    myList.deleteNode(n);
                  }
               }
               else if (i == 2)
               {
                 x.erase(x.begin(), x.end());
               }
               else
               {
                 mySTList.erase(mySTList.begin(), mySTList.end());
               }
             }
             timer1.stop();
             stats[i].record(timer1);
             //
             // Notice here we restore because the operation we are testing removes everything
             // To test more operation (like a search), we would like to comment this section
             // ------------------------------------------------------------------------------
             if (i == 0)
               y = x;  // poorly named vectors
             else if (i == 1)
               otSTList = mySTList;  // lists
             else
             {
               // our LL
               for (int z = 0; z < N; ++z)
               {
                 myList.appendNode(z);
               }
             }
             // ------------------------------------------------------------------------------

          }
      } // end of trials loop

      for (int i = 0; i < number_of_structures; ++i)
      {
          stats[i].report(cout, repetitions);
          stats[i].report(ofs, repetitions);
      }

      cout << endl;
      ofs << endl;

      x.erase(x.begin(), x.end());

      if (repetitions > 1)
          repetitions /= 2;
  }

  return 0;

}

//**************************************************
// This is just one operation                      *
// of the homegrown linked list where we would     *
// likely have a lot more                          *
//**************************************************
// here is the user written code for the Linked List (scaled down)
void LL::appendNode(int intVar)
{
   ListNode *newNode;  // To point to a new node
   ListNode *nodePtr;  // To move through the list

   // Allocate a new node and store num there.
   newNode = new ListNode;
   newNode->value = intVar;
   newNode->next = nullptr;

   // If there are no nodes in the list
   // make newNode the first node.
   if (!head)
      head = newNode;
   else  // Otherwise, insert newNode at end.
   {
      // Initialize nodePtr to head of list.
      nodePtr = head;

      // Find the last node in the list.
      while (nodePtr->next)
         nodePtr = nodePtr->next;

      // Insert newNode as the next node.
      nodePtr->next = newNode;
   }
}

void LL::deleteNode(int intVar)
{
   ListNode *nodePtr;       // To traverse the list
   ListNode *previousNode;  // To point to the previous node

   // If the list is empty, do nothing.
   if (!head)
      return;

   // Determine if the first node is the one.
   if (head->value == intVar)
   {
      nodePtr = head->next;
      delete head;
      head = nodePtr;
   }
   else
   {
      // Initialize nodePtr to head of list
      nodePtr = head;

      // Skip all nodes whose value member is
      // not equal to intVar.
      while (nodePtr != nullptr && nodePtr->value != intVar)
      {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If nodePtr is not at the end of the list,
      // link the previous node to the node after
      // nodePtr, then delete nodePtr.
      if (nodePtr)
      {
         previousNode->next = nodePtr->next;
         delete nodePtr;
      }
   }
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
// pre: n/a                                        *
// post: destroyed object                          *
//**************************************************

LL::~LL()
{
   ListNode *nodePtr;   // To traverse the list
   ListNode *nextNode;  // To point to the next node

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
