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

   Signed: Aaron Tobias Date: 02/04/2021


   COPYRIGHT (C) 2021 Aaron Tobias. All Rights Reserved.
   Project #: 1 - List
   Author Aaron Tobias, adt27
   version 1.01 2021-02-04
   Files:   TripleList.cpp
            TripleList.hpp
            Compare.cpp


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
//Timer stuff
#include "Complexity_Timer.hpp"
#include "Complexity_Recorder.hpp"
//IO stuff
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <iterator>

//Structure stuff
#include "TripleList.hpp"
#include <vector>
#include <list>
#include <set>

//timer
timer tmr;

// experiment will involve timing of 3 algorithms and that the number of "trials" will be 7.
// By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median.
// (The median computation is done in class recorder.)
// The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.

const int number_of_structures = 4;
const int number_of_trials = 7;

// NOTICE factor is going to influence the "extra" time
const int factor = 100;

const char *insheads[number_of_structures] =
    {"| TripleList ins ",
     "|   vector ins   ",
     "|  STL list ins  ",
     "|   STL set ins  "};

const char *popheads[number_of_structures] =
    {"| TripleList pop ",
     "|   vector pop   ",
     "|  STL list pop  ",
     "|  STL set erase "};

int main()
{
    enum Structure
    {
        triple,
        vector,
        list,
        set
    };
    std::ofstream ofs("results.txt");
    std::vector<recorder<timer>> remStats(number_of_structures); //to hold measurements
    std::vector<recorder<timer>> insStats(number_of_structures); //to hold measurements
    //set up structures
    TripleList T;
    std::set<int> S;
    std::list<int> L;
    std::vector<int> V;

    int NIter, Nmin, Nmax, N, r;
    Nmin = 1;    // smallest sequence
    Nmax = 1000; // largest sequence

    int FACTOR = 100;
    int repetitions = std::max(32 / Nmin, 1);
    //Tests: push linear, insert random, pop linear, remove random
    // Test Push Linear Header
    std::cout << "_____";
    for (int i = 0; i < number_of_structures; ++i)
    {
        std::cout << insheads[i];
        ofs << insheads[i];
    }

    std::cout << std::endl;
    ofs << std::endl;

    std::cout << "Size ";
    for (int i = 0; i < number_of_structures; ++i)
    {
        std::cout << "|      Time      ";
        ofs << "|      Time      ";
    }
    std::cout << std::endl
              << std::flush;
    ofs << std::endl;
    //Test Push Linear record
    for (NIter = Nmin; NIter <= Nmax; NIter *= 2) //Set the num of elements
    {
        for (r = 0; r < repetitions; ++r)
        {

            N = NIter * FACTOR;                            //total elements = num of elements * factor
            for (int i = 0; i < number_of_structures; ++i) //for each structure
            {
                tmr.restart(); //start timer
                switch (Structure(i))
                {
                case triple:
                    std::cout << "T Got here " + std::to_string(r) << std::endl;
                    for (int i = 0; i < N; ++i)
                        T.insert(i);
                    tmr.stop();
                    T.clear();
                    break;
                case vector:
                    std::cout << "V Got here " + std::to_string(r) << std::endl;
                    for (int i = 0; i < N; ++i)
                        V.push_back(i);
                    tmr.stop();
                    V.clear();
                    break;
                case list:
                    std::cout << "L Got here " + std::to_string(r) << std::endl;
                    for (int i = 0; i < N; ++i)
                        L.push_back(i);
                    tmr.stop();
                    L.clear();
                    break;
                case set:
                    std::cout << "S Got here " + std::to_string(r) << std::endl;
                    for (int i = 0; i < N; ++i)
                        S.insert(i);
                    tmr.stop();
                    S.clear();
                    break;

                }
                insStats[i].recordms(tmr);
            }
        }

        std::cout << std::endl;
        ofs << std::endl;
        std::cout << std::setw(4) << NIter << std::flush;
        ofs << std::setw(4) << NIter;
        for (int i = 0; i < number_of_structures; ++i)
        {
            insStats[i].reportms(std::cout, repetitions);
            insStats[i].reportms(ofs, repetitions);
        }
        std::cout << std::endl;
        ofs << std::endl;
    }
    //Test Remove Linear Header
    std::cout << "_____";
    for (int i = 0; i < number_of_structures; ++i)
    {
        std::cout << popheads[i];
        ofs << popheads[i];
    }
    std::cout << std::endl;
    ofs << std::endl;

    std::cout << "Size ";
    for (int i = 0; i < number_of_structures; ++i)
    {
        std::cout << "|      Time      ";
        ofs << "|      Time      ";
    }
    std::cout << std::endl;
    ofs << std::endl;
    for (NIter = Nmin; NIter <= Nmax; NIter *= 2) //Set the num of elements
    {

        N = NIter * FACTOR;                            //total elements = num of elements * factor
        for (int i = 0; i < number_of_structures; ++i) //for each structure
        {
            tmr.stop();
            remStats[i].recordms(tmr);

            tmr.restart();
            switch (Structure(i))
            {
            case triple:
                for (int i = 0; i < N; ++i)
                    T.popMax();
                break;
            case vector:
                for (int i = 0; i < N; ++i)
                    V.pop_back();
                break;
            case list:
                for (int i = 0; i < N; ++i)
                    L.pop_back();
                break;
            case set:
                for (int i = 0; i < N; ++i)
                    S.erase(prev(S.end()));
                break;
            }
            tmr.stop();
            remStats[i].record(tmr);
        }
        // stats[i].report(std::cout, repetitions);
        // stats[i].report(ofs, 1);
        // Reporting info

        //Insert Tests

        //output size

        for (int i = 0; i < number_of_structures; ++i)
        {
            remStats[i].reportms(std::cout, repetitions);
            remStats[i].reportms(ofs, repetitions);
        }
        std::cout << std::endl;
        ofs << std::endl;
    }
}