/*
   ACADEMIC INTEGRITY PLEDGE

   - I have not used source code obtained from another
     student nor any other unauthorized source, either
     modified or unmodified. Any source code used for
     testing that is another student's has been
     appropriately documented

   - All source code and documentation used in my program
     is either my original work or was derived by me from
     the source code published in the textbook for this
     course or presented in class. Other sources are acknowledged
     without transcribing code verbatim

   - I have not discussed coding details about this project
     with anyone other than my instructor, TA, and my immediate
     project team. I understand that I may discuss the concepts
     of this program with other students and that another student
     may help me debug my program so long as neither of us writes
     anything during the discussion or modifies any computer file
     during the discussion.

   - I have violated neither the spirit nor letter of these
     restrictions.

   Signed: student name Date: xx/xx/xxxx


   COPYRIGHT (C) 2021 student name. All Rights Reserved.
   Project #: XXXXXXXXXXXXXXXXXXXXXX
   author student name, uanetid
   version 1.01 xxxx-xx-xx
   Files: xxxxx-xxxx.cxx


   COPYRIGHT (C) 2018 Will Crissey, Jr. All rights reserved.
   DS316 Sample Project example.
   Author.  Will Crissey, Jr.
   Version. 1.02 06.03.2018.
   Files: DS316_Project_Standard_Code_Example.cpp
          Complexity_Timer.hpp
          Complexity_Recorder.hpp


This program and the utility implementations are useful for measurements of run times.

In this example we will measure the runtimes of a homegrown coded sort algorithm, the Quicksort, against
some of the sorts from the Standard Template Library

The value for our Data Structures class is to have an example of measuring runtime complexity

Note that this program uses three different algorithms (for sorting) as an example.
To use it for other algorithms, the parameters in the template function (Container) will need to be changed.

Also note that this is consolidated for the sake of simplicity. Your code will likely need to be in multiple files

Acknowledgments and special thanks to Dr. David Musser, retired Professor of Computer Science
His wisdom includes a 37-year career combining academic, industry, and research-institute positions, including almost 20 years at Rensselaer.
Coding modifications included the original work with permission: copyright (c) 1997 Rensselaer Polytechnic Institute

 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <limits>
#include <fstream>
#include <iterator>
#include <algorithm>    // std::random_shuffle

#include "Complexity_Timer.hpp"
#include "Complexity_Recorder.hpp"


// i left this here b/c i was lazy
using namespace std;

// timer
timer timer1;

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

// experiment will involve timing of 3 algorithms and that the number of "trials" will be 7.
// By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median.
// (The median computation is done in class recorder.)
// The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.

const int number_of_algorithms = 3;
const int number_of_trials = 7;

// NOTICE factor is going to influence the "extra" time
const int factor = 5000;

// Function prototypes
void quickSort(std::vector<int> &, int, int, int &);
int partition(std::vector<int> &, int, int);

// This template function is to specify which algorithms are used in the timing experiment
template <class container>
inline void algorithm(int k, container &x, int BigK, int &recurse)
{
    switch (k)
    {
        case 0: stable_sort(x.begin(), x.end());
            break;
        case 1: sort(x.begin(), x.end());
            break;
        case 2: quickSort(x, 0, x.size(), recurse);
    }
}

// STABLE SORT: sorts the elements in the range [first,last), like sort, but preserves the relative order of the elements with equivalent values-from STL
// SORT: (the Quicksort algorithm, using the median-of-3 method of choosing pivot elements for partitioning)-from STL
// Quick sort: Our user written sorting algorithm

const char* headings[number_of_algorithms] =
{"| stable sort    ",
 "|      sort      ",
 "| my quick sort  "};

int main()
{
    int N0, N1, N2, N, K, recurse = 0;
    N1 = 1;    // smallest sequence
    N2 = 1000; // largest sequence

// for our outputting of the results
    ofstream ofs("results.txt");

// this is going to hold the measurements
    vector<recorder<timer> > stats(number_of_algorithms);

// The "U" is the type for the vectors x and y (poorly named, i know). Using the largest sequence multiplied by factor to allocate memory
    vector<U> x, y;
    x.reserve(N2*factor);
    y.reserve(N2*factor);


// The times are taken for short computations by repeating those computations a number of times
// (controlled by the variable repetitions), so that they take long enough to register nonzero times.
// In our example where N1 = 1(meaning a sequence of length 1,000 (or, more generally, 1 * factor),
// then the time will be computed for executing the algorithm 32 times
   int repetitions = max(32/N1, 1);

    cout << "____";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << headings[i];
    cout << endl;

    cout << "Size";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << "|      Time      ";
    cout << endl;



    for (N0 = N1; N0 <= N2; N0 *= 2)
    {

        N = N0 * factor;

        K = N/2;

        for (int i = 0; i < N; ++i)
            x.push_back(i);

        cout << setw(4) << N0 << flush;
        ofs << setw(4) << N0;

        int p;

        for (int i = 0; i < number_of_algorithms; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

            random_shuffle(x.begin(), x.end());
            y = x;

// Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
// (The repetitions factor is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_algorithms; ++i)
            {
               timer1.restart();
               for (int k = 0; k < repetitions; ++k)
               {
                 x = y;
                 algorithm(i, x, K, recurse);
               }
               timer1.stop();
               stats[i].record(timer1);
            }
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            stats[i].report(cout, repetitions);
            stats[i].report(ofs, repetitions);
        }

        cout << endl;
        ofs << endl;

        x.erase(x.begin(), x.end());

        if (repetitions > 1)
            repetitions /= 2;

// Notice we restore the input sequence before each call of the algorithm; b/c these algorithms typically
//  would perform differently on already-sorted sequences than on random ones.

    }
// the number of recursions reveals the call stack implications
    cout << endl;
    cout << "Number of quicksort recursions: " << recurse << endl;
    return 0;

}

// Sorting Benchmarks
// the reason were interested more in comparisons with sorts
// is b/c the amount of work they do is proportional to the amount of comparisons
// swaps are more of a constant activity.
//   ...Now for almost any sort I do this for (instrumented sort) the counts
// are more than they need to be. None reflect their magnitudes and complexities



// Precondition: as argument need the address of the vector. Also, p is the starting point and r is the size.
// Postcondition: this function will not return the sorted object and is exclusively used for timing

// The quicksort recursive function

void quickSort(std::vector<int> &input, int p, int r, int &recurse)
{
    recurse++;
    if ( p < r )
    {
        int j = partition(input, p, r);
        quickSort(input, p, j-1, recurse);
        quickSort(input, j+1, r, recurse);
    }
}


// The partition function
int partition(std::vector<int> &input, int p, int r)
{

    int pivot = input[r];

    while ( p < r )
    {
        while ( input[p] < pivot )
            p++;

        while ( input[r] > pivot )
            r--;

        if ( input[p] == input[r] )
            p++;
        else if ( p < r )
        {
            int tmp = input[p];
            input[p] = input[r];
            input[r] = tmp;
        }
    }

    return r;
}


