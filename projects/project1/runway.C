#include <iostream>
using namespace std;
#include <time.h>
#include <map>
#include "LQueue.C"

int main(void)
{

  //Create variables to store simulation parameters
  int takeOffRate;
  int landingRate;
  int takeOffTime;
  int landingTime;
  int timeLength;

  //Create variables to hold random values
  int landingRand;
  int takeOffRand;

  //Declare the queues which will hold planes landing and taking off
  Queue landingQueue;
  Queue takeOffQueue;
  
  //Runway Open Flag
  bool runwayFree = true;

  //Plane tracking and identification initial value
  int planeNumber = 1000;
  
  //Sets waiting time initial variable to 0
  int waitTime = 0;

  //Map to hold start times of take offs and landings
  map <int, int> waitingMap;

  //Values to hold the average time in queues and max length of queues
  int numTakeOffs = 0;
  int numLandings = 0;
  int takeOffTotalTime = 0;
  int landingTotalTime = 0;
  int landingQueueSize = 0;
  int takeOffQueueSize = 0;
  int maxLandingQueue = 0;
  int maxTakeOffQueue = 0;

  //Accept user input for all above variables:

  cout<<"\n"<<"Enter the following parameters for simulation (integers only):"<<endl;

  cout<<"\t"<<"Duration of Landing (minutes): ";
  cin>>landingTime;
  
  cout<<"\t"<<"Duration of Takeoff (minutes): ";
  cin>>takeOffTime;

  cout<<"\t"<<"Landing Rate in Planes per hour: ";
  cin>>landingRate;

  cout<<"\t"<<"Takeoff Rate in planes per hour: ";
  cin>>takeOffRate;

  cout<<"\t"<<"Duration of Simulation: ";
  cin>>timeLength;

  srand(time(NULL));
  int i = 0;
  bool complete = false;

  while(!complete){
    
    cout<<"TIME: "<<i;

    if(waitTime!=0){
      waitTime--;
      cout<<" | Runway Status: Busy"<<endl;
    }
    else{
      runwayFree = true;
      cout<<" | Runway Status: Open"<<endl;
    }

    if(i <= 120){
    
      landingRand = rand() % 60;
      
      //cout<<landingRand<<endl;
      takeOffRand = rand() % 60;
      
      //cout<<takeOffRand<<endl;
      
      if(landingRand < landingRate){
	cout<<"\t"<<"Plane "<<planeNumber<<" requesting to land. Enqueuing to landing queue"<<endl;
	landingQueue.enqueue(planeNumber);
	landingQueueSize++;
	
	if(landingQueueSize>maxLandingQueue){
	  maxLandingQueue = landingQueueSize;
	}
	
	waitingMap[planeNumber] = i;
	planeNumber++;
	
      }
      if(takeOffRand < takeOffRate){
	cout<<"\t"<<"Plane "<<planeNumber<<" requesting takeoff. Enqueueing to takeoff queue"<<endl;
	takeOffQueue.enqueue(planeNumber);
	takeOffQueueSize++;
	
	if(takeOffQueueSize > maxTakeOffQueue){
	  maxTakeOffQueue = takeOffQueueSize;
	}
	
	waitingMap[planeNumber] = i;
	planeNumber++;
	
      }
      
    }
    
    if(runwayFree){
      
      if(!landingQueue.empty()){
	
	//Dequeue plane from landing queue
	//Set wait timer to landing time
	cout<<"\t"<<"Plane "<<landingQueue.front()<<" LANDING after waiting "<<i - waitingMap[landingQueue.front()]<<" mins"<<endl;
	landingTotalTime+= i - waitingMap[landingQueue.front()];
	landingQueue.dequeue();
	landingQueueSize--;
	numLandings++;
	runwayFree = false;
	waitTime = landingTime;
		
      }
      else{
	
	//Dequeue plane from takeoff queue
	//Set wait timer to takeoff time
	
	if(!takeOffQueue.empty()){
	  cout<<"\t"<<"Plane "<<takeOffQueue.front()<<" TAKING OFF after waiting "<<i - waitingMap[takeOffQueue.front()]<<" mins"<<endl;
	  takeOffTotalTime+= i - waitingMap[takeOffQueue.front()];
	  takeOffQueue.dequeue();
	  takeOffQueueSize--;
	  numTakeOffs++;
	  runwayFree = false;
	  waitTime = takeOffTime;
	
	}	
      }
    }
    if(i > 120 && takeOffQueue.empty() && landingQueue.empty()){

      complete = true;
      
    }
    i++;

  }

  float averageTakeOffTime = (float)takeOffTotalTime/numTakeOffs;
  float averageLandingTime = (float)landingTotalTime/numLandings;

  cout<<"\n"<<"Simulation Finished! Statistics:"<<endl;
  cout<<"\t"<<"Average Waiting Time for Takeoff: "<<averageTakeOffTime<<" mins"<<endl;
  cout<<"\t"<<"Average Waiting Time for Landing: "<<averageLandingTime<<" mins"<<endl;
  cout<<"\t"<<"Maximum Length of Takeoff Queue: "<<maxTakeOffQueue<<endl;
  cout<<"\t"<<"Maximum Length of Landing Queue: "<<maxLandingQueue<<endl;
  cout<<endl;
  
  return 0; 
}
