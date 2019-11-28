#pragma once
/*
File Included: AirportSimulationHeader.h

Class Provided: Plane

   Private Member Variables:
      int priority = -1;
         priority set by constructor, 1 is top priority for landing, 0 is least priority for takeoff

      double timeStamp;
         the time when a request was made by this plane

   Public Member Functions:

   Plane()
      PreCondition: none
      PostCondition: priority = -1, timeStamp set to 0

   Plane(double time, int n)
      PreCondition: none
      PostCondition: timeStamp class variable set to time parametere, priority set to n

   int GetPriority()
      PreCondition: none
      PostCondition: returns the planes priority variable

   double GetTimeStamp()
      PreCondition: none
      PostCondition: returns the value of timeStamp variable

Class Provided: Runway

   Private Member Variables:

      bool available = true;
         tells us if runway is available for either landing or departure

      int currentTime = 0;
         to keep track of how long an action has been taking on this runway

      int landingsComplete = 0;
         how many landings we've completed

      int takeoffsComplete = 0;
         how many takeoffs we've completed

      Plane plane;
         holds onto whatever plane is taking up the runway

   Public Member Functions:

      void IncrementTime()
      PreCondition: this runway is currently in use by a plane, i.e. available equals false
      PostCondition: currentTime incremeneted by 1, if it reaches 15, then the runway is cleared, setting available to true

      bool Available()
      PreCondition: none
      PostCondition: returns whether or not the runway is available for a request

      void UseRunway(Plane p)
      PreCondition: variable passed in is a Plane object
      PostCondition: availability set to false, plane class variable set to p passed in

      int TakeOffsCompleted()
      PreCondition: none
      PostCondition: returns how many takeOffs this runway has completed

      int LandingsCompleted()
      PreCondition: none
      PostCondition: returns how many landins this runway has completed

Class Provided: Queue

   Private Member Variables:
   
      Item *p;
         used to point to a dynamic array of type Item

      int startSize = 5;
         the size that the dynamic array "p" starts at

      int currentSize = 5;
         the current size of the dynami array "p", increments by 10 when needed

      int size = 0;
         keeps track of how many elements we have in our dynamic array 

      int first = 0;
         keeps track of which element is first in line

      int last = 0;
         keeps track of which element is last in line

   Public Member Functions:
   
      Queue()
         PreCondition: none
         PostCondition: default constructor, starts p dynamic array with size "startSize"

      void Push(Item n)
         PreCondition: n passed in is of the correct data type
         PostCondition: n added to the back of the queue, top pointer incremented by 1

      void Pop()
         PreCondition: an element exists in our Queue
         PostCondition: the front element is removed from the queue

      Item& Front()
         PreCondition: an element exists in our queue
         PostCondition: returns a reference to the Item at the front of the queue

      void IncreaseSize()
         PreCondition: variable last is greater than currentSize - 5, meaning we need to make more space
         PostCondition: currentSize incremented by 10, values in our queue copied over to a 10 space larger Item array, old array dynamically deleted

      int GetSize()
         PreCondition: none
         PostCondition: returns how many elements are in our queue

Class Provided: Averager

   Private Member Variables:

      double *top;
         points to a double dynamic array, also keeps track of the top element in this stack

      int startSize = 5;
         the size that we start out stack at

      int currentSize = 5;
         keeps track of the size our dynamic array may eventually change to

      int size = 0;
         how many elements we have in our stack

   Public Member Functions:
      Averager()
         PreCondition: none
         PostCondition: default constructor, points our dynamic array pointer, top, to a dynamic double array of startSize

      void Push(double n)
         PreCondition: n is a double value
         PostCondition: calls IncreaseSize() if we are running out of room, adds variable passed in to the top of the stack

      void Pop()
         PreCondition: an element exists in our stack
         PostCondition: the top element in our stack is removed

      double Top()
         PreCondition: an element exists in our stack
         PostCondition: returns the value of the double on the top of our stack

      void IncreaseSize()
         PreCondition: size + 2 > currentSize, meaning we are running out of room.
         PostCondition: values of our dynamic array copied over to a new larger dynamic double array, old array deleted

      double GetAverage()
         PreCondition: none
         PostCondition: if no elements exists in our stack, returns 0,
                        else returns the sum of all elements in stack divided by the amount of elements

*/

//keeps track if it is a takeoff plane or a landing plane, and when it made it's request
class Plane {
private:
   int priority = -1;
   double timeStamp;
public:
   Plane() { timeStamp = 0; }
   //n must be 0 or 1, if 0, then this is a plane taking off, if 1, then requsting landing
   Plane(double time, int n) { timeStamp = time; priority = n; }
   int GetPriority() { return priority; }
   double GetTimeStamp() { return timeStamp; } // to be used by averager
};

//keeps track if runways are available, and how many takeoffs and landings completed
class Runway {
private:
   bool available = true; //tells us if runway is available for either landing or departure
   int currentTime = 0; //to keep track of how long an action has been taking on this runway
   int landingsComplete = 0; //how many landings we've completed
   int takeoffsComplete = 0; //how many takeoffs we've completed
   Plane plane;
public:
   void IncrementTime();

   bool Available() { return available; }

   void UseRunway(Plane p);

   int TakeOffsCompleted() { return takeoffsComplete; }

   int LandingsCompleted() { return landingsComplete; }
};


template<class Item>
class Queue {
private:
   Item *p;
   int startSize = 5, currentSize = 5, size = 0;
   int first = 0, last = 0;
public:

   Queue() { p = new Item[startSize]; }

   void Push(Item n);

   void Pop() { first++; size--; }

   Item& Front() { return p[first]; }

   void IncreaseSize();

   int GetSize() { return size; }
};

//create one for takeoff and one for landing wait times
//takes care of averaging the time spent in Queues and thats it
class Averager {
private:
   double *top;
   int startSize = 5, currentSize = 5, size = 0;
public:
   Averager() { top = new double[startSize]; }

   void Push(double n);

   void Pop() { top--; size--; }

   double Top();

   void IncreaseSize();

   double GetAverage();
};

#include "ClassImplementations.h"