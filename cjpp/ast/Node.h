#include <iostream>

class Node {
public:
    virtual ~Node() {}
    //virtual Node *clone () = 0;
    //virtual int value () = 0;
};

class Statement : public Node {

};

class Expression : public Node {

};


class Identifier : public Node {
public:
    char* name;
    
    Identifier(char* name) : name(name)
    {}	
};

