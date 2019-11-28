#pragma once
//Runway Implementations
void Runway::IncrementTime() {
   if (!available) //a plane is taking up the runway
      currentTime++;
   if (currentTime >= 15) { //takeoff or landing complete
      available = true;
      currentTime = 0;
      if (plane.GetPriority() == 1) {
         landingsComplete++;
      }
      else if (plane.GetPriority() == 0) {
         takeoffsComplete++;
      }
   }
}

void Runway::UseRunway(Plane p) {
   available = false;
   plane = p;
}
//end RunWay Implementations

//Queue Implementations
template<class Item>
void Queue<Item>::IncreaseSize() {
   Item *temp = new Item[currentSize + 10];

   for (int i = 0; i < currentSize; i++) {
      *temp = *p;
      p++;
      temp++;
   }
   for (int i = 0; i < currentSize; i++) {
      p--;
      temp--;
   }
   delete[] p;
   p = temp;
   currentSize += 10;
}

template<class Item>
void Queue<Item>::Push(Item n) {
   if (last > currentSize - 5)
      IncreaseSize();
   p[last] = n;
   last++;
   size++;
}
//end Queue Implementations

//Averager Implementations
double Averager::Top() {
   top--;
   double temp = *top;
   top++;
   return temp;
}

void Averager::IncreaseSize() {
   double *temp = new double[currentSize + 10];
   top--;
   for (int i = 0; i < size - 1; i++) {
      top--;
   }
   for (int i = 0; i < size; i++) {
      *temp = *top;
      top++;
      temp++;
   }
   for (int i = 0; i < size; i++) {
      temp--;
      top--; //go back down for deletion
   }
   delete[] top;
   top = temp;
   for (int i = 0; i < size; i++) {
      top++;
   }
   currentSize += 10;
}

double Averager::GetAverage() {
   top--;
   double toReturn = 0;
   for (int i = 0; i < size; i++) {
      toReturn += *top;
      top--;
   }
   if (size == 0)
      return 0;
   else
      return toReturn / size;
}

void Averager::Push(double n) {
   size++;
   *top = n;
   top++;
   if (size + 2 > currentSize)
      IncreaseSize();
}
//end Averager Implementations

//non-class functions

//landing being requested at a probability of 10%
bool LandingRequest() {
   double probability = 10;
   probability = 1 / probability;
   return(rand() < probability * RAND_MAX);
}

//takeoff being requested at a probability of 10%
bool TakeOffRequest() {
   double probability = 10;
   probability = 1 / probability;
   return(rand() < probability * RAND_MAX);
}
//end non-class functions
