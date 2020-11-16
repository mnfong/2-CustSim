// sim.cpp
// mnfong
// Fong, Madison

#include "pqueue.h"
#include "cust.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


// Makes a checker
struct Checker
{

  Cust *current = NULL;
  int moneyAmount = 250;
  int timeDoneWCustomer = 0;
  bool onBreak = false;
  int timeBreak = 0;

};

// Identifies if the str is a number and is greater than 0
bool legal_int(char *str)
{
  for (int count = 0; count < strlen(str); count++)
  {

    if (!isdigit(str[count]))
    {
      return false;
    }

  }

  return true;
}

// The simulation for the store
void run_simulation(Pqueue &arrivingQueue, int num_checkers, int break_duration, ostream &os)
{

  // Variables used in the simulation
  int numCustomers = arrivingQueue.length();
  Checker *checkers = new Checker[num_checkers];
  Pqueue shoppingQueue;
  Pqueue checkerQueue;


  // Continues to run until there are no more customers
  for (int time = 1; numCustomers > 0; time++)
  {

    // Checks which customers are arriving at the same time and adds them to the shopping queue
    while (arrivingQueue.length() > 0)
    {
      int priorityA = arrivingQueue.first_priority();
      if (time == priorityA)
      {
        Cust *customer = arrivingQueue.dequeue();
        customer -> printEntered(os, time);
        int timeDoneShopping = ((customer -> getNumberOfItems()) * 2) + time;
        shoppingQueue.enqueue(customer, timeDoneShopping);
      }
      else
        break;

    }

    // Checks which customers are done shopping and adds them to the checker queue
    while (shoppingQueue.length() > 0)
    {
      int priorityS = shoppingQueue.first_priority();
      if (time == priorityS)
      {
        Cust *customer = shoppingQueue.dequeue();
        customer -> printDoneShopping(os, time);
        checkerQueue.enqueue(customer, 0);
      }
      else
      {
        break;
      }

    }

    // T04 TEST CAUSING PROBLEMS ON ITS LINE 76 OUTPUT
    // The customer checks out or steals and the checker/register is updated
    for (int i = 0; i < num_checkers; ++i)
    {

      if (checkers[i].current != NULL)
      {
        if (time == checkers[i].timeDoneWCustomer)
        {
          if (checkers[i].current -> getType() == true)
          {
            checkers[i].current -> printStole(os, checkers[i].moneyAmount, checkers[i].current -> getNumberOfItems(), time, i);
            checkers[i].moneyAmount = 0;
            if (break_duration > 0)
              checkers[i].onBreak = true;
            checkers[i].timeBreak = time + break_duration;

          }

          if (checkers[i].current -> getType() == false)
          {
            int moneyAdded = 3 * checkers[i].current -> getNumberOfItems();
            checkers[i].moneyAmount += moneyAdded;
            checkers[i].current -> printBought(os, moneyAdded, checkers[i].current -> getNumberOfItems(), time, i);

          }

          Cust *tmp = checkers[i].current;
          checkers[i].current = NULL;
          delete tmp;
          --numCustomers;
        }
      }

    }

    // If a checker has no customer (NULL), assigns a customer to that checker
    for (int i = 0; i < num_checkers; i++)
    {
      if (checkers[i].onBreak)
      {
        if (time == checkers[i].timeBreak)
        {
          checkers[i].onBreak = false;
        }
      }
      if (checkerQueue.length() > 0)
      {

        if ((checkers[i].current == NULL) && (!checkers[i].onBreak))
        {
          checkers[i].current = checkerQueue.dequeue();

          if (checkers[i].current -> getType() == true)
          {
            checkers[i].timeDoneWCustomer = time + 7;

          }

          else if (checkers[i].current -> getType() == false)
          {
            checkers[i].timeDoneWCustomer = checkers[i].current -> getNumberOfItems() + time;

          }

          checkers[i].current -> printStartCheckout(os, time, i);

        }
      }
    }

    // Prints out the amount of money each checker has and the time the simulation ended
    if (numCustomers == 0)
    {
      for (int i = 0; i < num_checkers; ++i)
      {
        os << "registers[" << i << "] = $" << checkers[i].moneyAmount << endl;
      }
      os << "time = " << time + 1 << endl;
    }
  }
}

int main(int argc, char *argv[])
{
  // Variables used main()
  ifstream inputFile(argv[3]);
  ofstream outputFile(argv[4]);
  Pqueue arrivingQueue;

  // Error checking # of command arguments, # of checkers, break duration, and if the input and output files open
  if (argc != 5)
  {
    cerr << "Error: invalid number of command line arguments." << endl;
    return 1;
  }

  if (!legal_int(argv[1]))
  {
    cerr << "Error: invalid number of checkers specified." << endl;
    return 1;
  }

  else if (atoi(argv[1]) <= 0)
  {
    cerr << "Error: invalid number of checkers specified." << endl;
    return 1;
  }

  if (!legal_int(argv[2]))
  {
    cerr << "Error: invalid checker break duration specified." << endl;
    return 1;
  }

  else if (atoi(argv[2]) < 0)
  {
    cerr << "Error: invalid checker break duration specified." << endl;
    return 1;
  }

  if (!inputFile)
  {
    cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
    return 1;
  }

  if (!outputFile)
  {
    cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
    return 1;
  }

  int count = 1;
  string input = "";
  char c;
  string name = "";
  bool type = false;
  int arrivalTime = 0;
  int numberOfItems = 0;

  while (inputFile.get(c))
  {
    if (!isspace(c))
    {
      input += c;
    }
    else
    {
      if (count == 1)
      {
        name = input;
        ++count;
      }
      else if (count == 2)
      {
        if (input == "robber")
        {
          type = true;
        }
        else
        {
          type = false;
        }
        ++count;
      }
      else if (count == 3)
      {
        arrivalTime = stoi(input);
        ++count;
      }
      else if (count == 4)
      {
        numberOfItems = stoi(input);
        count = 1;
        Cust *customer = new Cust(name, type, arrivalTime, numberOfItems);
        arrivingQueue.enqueue(customer, arrivalTime);
      }
      input = "";
    }
  }

  inputFile.close();

  // Calls the simulaton
  run_simulation(arrivingQueue, atoi(argv[1]), atoi(argv[2]), outputFile);

  outputFile.close();
}
