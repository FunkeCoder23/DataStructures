#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "./TripleList.hpp"

int main()
{
    srand(time(NULL));
    TripleList list;
    for (int i = 0; i < 9; i++)
    {
        int r = i;
        //int r = std::rand() % 100;
        list.insert(r);
        list.debug();
    }

    list.remove(4);
    list.debug();

    list.remove(5);
    list.debug();

    list.remove(3);
    list.debug();

    list.remove(8);
    list.debug();

    list.remove(7);
    list.debug();

    int s = list.getSize();
    for (int i = 0; i < 1000; i++)
    {
        list.popMin();
        list.debug();
        list.popMax();
        list.debug();
    }
    list.remove(6);
    list.debug();
    list.removeMax();
    list.removeMin();
}