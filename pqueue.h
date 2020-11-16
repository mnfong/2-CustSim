//pqueue.h
//Fong, Madison
//mnfong

#include <iostream>
#include "cust.h"

#ifndef PQUEUE_H
#define PQUEUE_H

using namespace std;

class Pqueue
{
  // Constructor and deconstructor for the priority queue
  // Functions that the priority queue can use
  public:
    Pqueue();
    ~Pqueue();

    bool empty();
    void enqueue(Cust *customer, int prty);
    Cust* dequeue();
    int first_priority();
    int length();

  // Creates the node that holds a customer, the customer's priority, and the next node
  private:
    class Node
    {
      public:
        Node(Cust value, int priority, Node *next)
        {
          m_value = value; m_priority = priority; m_next = next;
        }
        Cust m_value{"", false, 0, 0};
        int m_priority;
        Node *m_next;
    };
    Node *front;
    int m_length;

};

#endif
