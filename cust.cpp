// cust.cpp
// Fong, Madison
// mnfong

#include <iostream>
#include <assert.h>
#include "cust.h"

using namespace std;

// Cust constructor
Cust::Cust(string nm, bool typ, int time, int items)
  : name(nm), isRobber(typ), arrivalTime(time), numberOfItems(items)
{
}

// Returns the customer's name
string Cust::getName()
{
  return name;
}

// Returns whether the customer is a robber or a shopper
bool Cust::getType()
{
  return isRobber;
}

// Returns the arrival time of the customer
int Cust::getArrivalTime()
{
  return arrivalTime;
}

// returns the number of items the customer is buying/stealing
int Cust::getNumberOfItems()
{
  return numberOfItems;
}

// Prints the customer's information
void Cust::print(ostream &os)
{
  if (isRobber == true)
    type = "robber";
  else
    type = "shopper";

  os << name << " " << type << " " << arrivalTime << " " << numberOfItems << endl;
}

// Prints the customer's enter statement
void Cust::printEntered(ostream &os, int clock)
{
  assert(clock == arrivalTime);
  os << clock << ": " << name << " entered store" << endl;
}

// Prints the customer's done shopping statement
void Cust::printDoneShopping(ostream &os, int clock)
{
  os << clock << ": " << name << " done shopping" << endl;
}

// Prints the customer's starting checkout statement
void Cust::printStartCheckout(ostream &os, int clock, int checkerNumber)
{
  os << clock << ": " << name << " started checkout with checker " << checkerNumber << endl;
}

// Prints the customer's stealing method statement
void Cust::printStole(ostream &os, int money, int items, int clock, int checkerNumber)
{
  if (items > 1)
    os << clock << ": " << name << " stole $" << money << " and " << items << " items from checker " << checkerNumber << endl;
  else
    os << clock << ": " << name << " stole $" << money << " and " << items << " item from checker " << checkerNumber << endl;
}

// Prints the customer's buying statement
void Cust::printBought(ostream &os, int money, int items, int clock, int checkerNumber)
{
  if (items > 1)
    os << clock << ": " << name << " paid $" << money << " for " << items << " items to checker " << checkerNumber << endl;
  else 
    os << clock << ": " << name << " paid $" << money << " for " << items << " item to checker " << checkerNumber << endl;
}
