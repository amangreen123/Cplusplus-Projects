//
// Created by aaron on 10/30/2020.
//

#include "Queue.h"
#include <iostream>
#include<cstdlib>
using namespace std;


Queue::Queue()// constructor when adding new node
{
    queueHead = NULL;
}




bool Queue::emptyQueue() const {
    return queueHead == NULL;
    //return queChar == 0;
}


//pushes
void Queue::enqueue(int queChar) {
    //QNode* temp = new QNode;
    //temp->item;
    //temp-> queuePt = NULL;
    QNode* qu = new QNode;
    qu ->item = queChar;
    qu ->tail = NULL;
    if(queueHead == NULL){
        queueHead = qu;
    }else{
        QNode* temp;
        temp = queueHead;
        while(temp ->tail != nullptr){
            temp = temp -> tail ;
        }
        temp -> tail = qu;
    }
}


//removes
int Queue::dequeue() {
    if (queueHead != nullptr) {
        QNode *tem = queueHead;
        queueHead = tem->tail;
        int item = tem->item;
        delete tem;
        return item;
    }
}

//size of Queue
int Queue::size() {
    int count = 0;

    if (emptyQueue()) {
        return 0;
    } else {
        QNode *temp;
        temp = queueHead;
        while (temp->tail != nullptr) {
            count++;
            temp = temp->tail;
        }
        return count;
    }
}

//element from the Queue
int Queue::Get(int i) {

    if (emptyQueue()){
        return 0;
    }else if (queueHead )
    {
        QNode* temp;
        temp = queueHead;

        for(int j = 0; j < i; j++){
            temp = temp->tail;
        }
        return temp->item;
    }
}

//swap two elements0
void Queue::swap(int a, int b)  {

    QNode* temp1;
    QNode* temp2;
    temp1 = queueHead;
    temp2 = queueHead;


    if (emptyQueue()){
        return;
    }else{
        QNode* temp;
        while(!(temp1->item == a) ){
            temp1 = temp1 -> tail;
        }

        while(!(temp2->item == b) ){
            temp2 = temp -> tail;
        }

        int tempValue = temp1->item;
        temp1->item = temp2->item;
        temp2->item = tempValue;
    }

    //starts with looping through till we find the node containing a
    //save a pointer to that node as temp1
    //do the same thing looping till you find the node containing b
    //save that as temp2
    //swap the item from temp1 and temp2
}
