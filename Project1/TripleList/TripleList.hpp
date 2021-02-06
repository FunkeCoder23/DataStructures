#ifndef TRIPLELIST_HPP
#define TRIPLELIST_HPP
/* TripleList is a 'Triple-Ended' List
*  It provides pointers to the head, tail, and middle
*  If I sort on insert, it *should* have a lower time complexity for insert/deletes
*  My hypothesis is that it will bring complexity down due to having a faux-binary search 
*/

class TripleList
{
private:
    // Declare a structure for the 'Triple-Ended' List
    struct LNode
    {
        int value;          // Value in the Lnode
        struct LNode *next; // Point to the next Lnode
        struct LNode *prev; // Point to prev Lnode
    };

    LNode *head;   //List head pointer
    LNode *tail;   //List tail pointer
    LNode *middle; //List mid pointer

    /*******
     * state provides the previous action done to the list
     * this allows us to have a consistent middle state without checking the entire list
     * H = add high or remove low element (logically the same effect on middle)
     * L = add low or remove high element ""
     *******/
    char state;
    int size;

    void updateMid(char);

public:
    // Constructor
    TripleList()
    {
        head = nullptr;
        tail = nullptr;
        middle = nullptr;
        size = 0;
        state = 'H';
    }

    // Destructor
    ~TripleList();

    // Linked list operations
    void clear();

    void remove(int);
    void removeMin();
    void removeMax();

    void insert(int);

    int getMin();
    int getMax();

    int popMin();
    int popMax();

    void print();
    void printRev();
    void printMid();

    void debug();

    int getSize() { return size; };
};

#endif