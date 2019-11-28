#include <iostream>
#include <string>
#include "AirportSimulationHeader.h"
using namespace std;

int main() {
   //create two runways
   Runway runwayOne = Runway();
   Runway runwayTwo = Runway();

   //create two averagers, one for time spent in landQueue and other for time spent in takeoffQueue
   Averager landAverager = Averager();
   Averager takeoffAverager = Averager();

   //create two queues, one for takeoff and one for landing
   Queue<Plane> takeoffQueue = Queue<Plane>();
   Queue<Plane> landingQueue = Queue<Plane>();

   //start simulation
   for (int i = 0; i < 121; i++) {
      //increment a minute of operation for each runway, IncrementTime() does not increment unless there is a plane there
      runwayOne.IncrementTime();
      runwayTwo.IncrementTime();

      //checks if anyone is waiting in the landing queue first, prioritizing the landing planes over take off
      if (landingQueue.GetSize() != 0) {
         if (runwayOne.Available()) { //if either runway is available, we pop a plane out of the landing queue,
                                      //and push how long they were waiting into the landing plane average wait time
            Plane plane = landingQueue.Front();
            runwayOne.UseRunway(plane);
            landAverager.Push(i - plane.GetTimeStamp());//i = currentTime, currentTime - planes timestamp = how long they were in Queue
            landingQueue.Pop();
         }
         if (runwayTwo.Available() && landingQueue.GetSize() != 0) { //we check again if the landing Queue is empty because it may
                                                                     //still not be empty after popping one out for the first runway
            Plane plane = landingQueue.Front();
            runwayTwo.UseRunway(plane);
            landAverager.Push(i - plane.GetTimeStamp());
            landingQueue.Pop();
         }
      }

      //checks if anyone is waiting in the takeoff queue
      if (takeoffQueue.GetSize() != 0) {
         if (runwayOne.Available()) {//if either runway is available, we pop a plane out of the landing queue,
                                     //and push how long they were waiting into the landing plane average wait time
            Plane plane = takeoffQueue.Front();
            runwayOne.UseRunway(plane);
            takeoffAverager.Push(i - plane.GetTimeStamp()); //i = currentTime, currentTime - planes timestamp = how long they were in Queue
            takeoffQueue.Pop();
         }
         if (runwayTwo.Available() && takeoffQueue.GetSize() != 0) { //check if anyone is still waiting for takeoff 
            Plane plane = takeoffQueue.Front();
            runwayOne.UseRunway(plane);
            takeoffAverager.Push(i - plane.GetTimeStamp());
            takeoffQueue.Pop();
         }
      }

      //i % 5 checks for a request every 5 minutes
      if (i % 5 == 0) {
         bool requestMade = false;
         while (!requestMade) { //will keep checking requests until one is made
            if (LandingRequest()) {
               requestMade = true;
               Plane plane = Plane(i, 1); //i is timestamp the plane made the request, 1 means it is a landing plane
               if (runwayOne.Available()) {
                  runwayOne.UseRunway(plane); //add plane to runway if available
               }
               else if (runwayTwo.Available()) {
                  runwayTwo.UseRunway(plane); //add plane to runway if available
               }
               else {
                  landingQueue.Push(plane); //no runways available, so we push the plane into the landingQueue
               }
            }
            if (TakeOffRequest() && !requestMade) {
               requestMade = true;
               Plane plane = Plane(i, 0); //i is timestamp the plane made the request, 0 means it is a landing plane
               if (runwayOne.Available()) {
                  runwayOne.UseRunway(plane); //add plane to runway if available
               }
               else if (runwayTwo.Available()) {
                  runwayTwo.UseRunway(plane); //add plane to runway if available
               }
               else {
                  takeoffQueue.Push(plane); //no runways available, so we push the plane into the landingQueue
               }
            }
         }
      }
   }
   int takeOffCompleted = runwayOne.TakeOffsCompleted() + runwayTwo.TakeOffsCompleted(); //add up take offs completed
   int landingsCompleted = runwayOne.LandingsCompleted() + runwayTwo.LandingsCompleted(); //add up landings completed

   cout << "Running Airport simulation for 120 minutes, prioritizing landing requests over takeoff requests." << endl;
   cout << "Number of landings completed: " << landingsCompleted << endl;
   cout << "Number of takeoffs completed: " << takeOffCompleted << endl;
   cout << "Number of planes left in landing queue: " << landingQueue.GetSize() << endl;
   cout << "Number of planes left in takeoff queue: " << takeoffQueue.GetSize() << endl;
   cout << "Average wait time for landing queue: " << landAverager.GetAverage() << " minutes." << endl;
   cout << "Average wait time for take off queue: " << takeoffAverager.GetAverage() << " minutes." << endl;
   system("pause");
   return 0;
   
}