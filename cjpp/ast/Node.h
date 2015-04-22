#include <iostream>

class Node {
public:
    virtual ~Node() {}
    virtual Node *clone () = 0;
    virtual int value () = 0;
};