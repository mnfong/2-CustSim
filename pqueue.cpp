//pqueue.cpp
//Fong, Madison
//mnfong

#include <iostream>
#include "pqueue.h"

using namespace std;

// Default constructor
Pqueue::Pqueue()
{
  front = NULL;
  m_length = 0;
}

// Deconstructor
Pqueue::~Pqueue()
{
  while (front != NULL)
  {
    Node *tmp = front;
    front = front -> m_next;
    m_length--;
    delete tmp;
  }
}

// Returns if the priority queue is empty
bool Pqueue::empty()
{
  return (m_length == 0);
}

// Returns the priority of the first customer in the queue
int Pqueue::first_priority()
{
  if (m_length == 0)
    return -1;
  return front -> m_priority;
}

// Adds a customer to the queue based on their priority and creates a node using them
void Pqueue::enqueue(Cust *customer, int prty)
{
  Node *tmp;
  Node *ptr;

  tmp = new Node(*customer, prty, NULL);

  if (front == NULL || prty < front -> m_priority)
  {
    tmp->m_next = front;
    front = tmp;
    m_length++;
    return;
  }
  else
  {
    ptr = front;
    while (ptr->m_next != NULL && prty >= ptr->m_next->m_priority)
    {
      ptr = ptr->m_next;
    }

    tmp->m_next = ptr->m_next;
    ptr->m_next = tmp;

  }
  m_length++;
}

// Removes a node from the queue and returns the customer
Cust *Pqueue::dequeue()
{
  if (m_length == 0)
    return NULL;
  else
  {
    Cust &tmp = front -> m_value;
    front = front -> m_next;
    m_length--;
    return &tmp;
  }
}

// Returns the length of the priority queue
int Pqueue::length()
{
  return m_length;
}
