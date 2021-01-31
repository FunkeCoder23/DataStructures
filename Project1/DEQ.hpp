class DEQ
{
private:
    // Declare a structure for the Double Ended Queues
    struct QNode
    {
        int value;          // Value in the Qnode
        struct QNode *next; // Point to the next Qnode
        struct QNode *prev; // Point to prev Qnode
    };

    QNode *head; //Q head pointer
    QNode *tail; //Q tail pointer

public:
    // Constructor
    DEQ()
    {
        head = nullptr;
        tail = nullptr;
    }

    // Destructor
    ~DEQ();

    // Linked list operations
    void pop(int);
    void popFront(int);
    void append(int);
    void prepend(int);
};
