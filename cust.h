// cust.h
// Fong, Madison
// mnfong

#ifndef CUST_H
#define CUST_H

#include <iostream>

using namespace std;

class Cust
{
  // Private variables that make up a customer
  private:
    string name;
    string type;
    bool isRobber;
    int arrivalTime;
    int numberOfItems;

  // Constructor that builds the customer
  // Functions that the customer can use
  public:
    Cust(string nm, bool typ, int time, int items);
    string getName();
    bool getType();
    int getArrivalTime();
    int getNumberOfItems();
    void print(ostream &os);
    void printEntered(ostream &os, int clock);
    void printDoneShopping(ostream &os, int clock);
    void printStartCheckout(ostream &os, int clock, int checkerNumber);
    void printStole(ostream &os, int money, int items, int clock, int checkerNumber);
    void printBought(ostream &os, int money, int items, int clock, int checkerNumber);

};

#endif
