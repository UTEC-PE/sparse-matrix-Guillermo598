#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node {
public:
    int x, y;
    T data;
    Node* next;
    Node* down;

    Node(T data) :  data(data){
        next = down = nullptr;
    };

    Node(int x, int y, T data) : x(x), y(y), data(data){
        next = down = nullptr;
    };

    void killSelf(){
        if (down)
            down -> killSelf();
        delete this;
    }


};

#endif