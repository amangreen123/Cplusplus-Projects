//
// Created by aaron on 10/30/2020.
//

#ifndef ASSINGMENT3_QUEUE_H
#define ASSINGMENT3_QUEUE_H

#endif //ASSINGMENT3_QUEUE_H

using namespace std;


class Queue {

private:

    struct QNode {
        int item;
        QNode* tail;
    };
    QNode* queueHead;



public:
    Queue();
    int dequeue();
    int Get(int i);
    int size();
    void swap(int a,int b);
    void enqueue( int item);
    bool emptyQueue() const;
};
