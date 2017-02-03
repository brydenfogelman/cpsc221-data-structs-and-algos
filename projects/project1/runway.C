#include <iostream>
using namespace std;
#include <time.h>
#include <map>
#include "LQueue.h"

int main(void)
{

  //Create variables to store simulation parameters
  int takeOffRate;
  int landingRate;
  int deIcingRate;
  int priorityRate;
  int takeOffTime;
  int landingTime;
  int timeLength;

  //Create variables to hold random values
  int landingRand;
  int takeOffRand;
  int deIcingRand;
  int priorityRand;

  //Declare the queues which will hold planes landing and taking off
  Queue landingQueue;
  Queue takeOffQueue;
  Queue deIcingQueue;
  
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
  int deIcingQueueSize = 0;
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
  
  cout<<"\t"<<"De-Icing Rate in planes per hour: ";
  cin>>deIcingRate;

  cout<<"\t"<<"Rate of emergency landings per hour: ";
  cin>>priorityRate;

  cout<<"\t"<<"Duration of Simulation: ";
  cin>>timeLength;

  //Seed random variable
  srand(time(NULL));

  //set time variable (time = i)
  int i = 0;

  //Complete flag for checking if no more planes to route
  bool complete = false;


  //General while loop for plane scheduling and manipulation.  Couts are for pretty output and will not be commented.
  while(!complete){
    
    cout<<"TIME: "<<i;

    //Checks if there is a plane taking off or landing and tracks wait time
    if(waitTime!=0){
      waitTime--;
      cout<<" | Runway Status: Busy"<<endl;
    }
    else{
      runwayFree = true;
      cout<<" | Runway Status: Open"<<endl;
    }

    //checks if the simulation will still be generating takeoff and landing requests. Assuming time in outline is inclusive
    if(i <= timeLength){
      
      //Creating random variables to determine requests
      landingRand = rand() % 60;
      
      //cout<<landingRand<<endl;
      takeOffRand = rand() % 60;

      deIcingRand = rand() % 60;

      priorityRand = rand() % 60;
      
      //checks if a new landing request is generated
      if(landingRand < landingRate){
	cout<<"\t"<<"Plane "<<planeNumber<<" requesting to land. Enqueuing to landing queue"<<endl;
	
	//adds plane to landing queue
	landingQueue.enqueue(planeNumber);
	landingQueueSize++;
	
	//compares size of queue to see if it is the longest
	if(landingQueueSize>maxLandingQueue){
	  maxLandingQueue = landingQueueSize;
	}
	
	//tracks time plane entered queue
	waitingMap[planeNumber] = i;
	
	//checks if priority landing, moves to front the desired plane
	if(priorityRand < priorityRate){
	   cout<<"\t"<<"Plane "<<planeNumber<<" given priority and moved to front of queue"<<endl;
	  landingQueue.move_to_front(planeNumber);

	 
	}
	//increments plane number
	planeNumber++;
	
      }

      //checks if takeoff request generated
      if(takeOffRand < takeOffRate){
	cout<<"\t"<<"Plane "<<planeNumber<<" requesting takeoff"<<endl;
	
	//deicing check. If it needs deicing add the plane to the deicing queue
	if(deIcingRand < deIcingRate){
	  cout<<deIcingRand<<" "<<deIcingRate<<endl;
	  deIcingQueue.enqueue(planeNumber);
	  deIcingQueueSize++;
	  cout<<"\t"<<"Plane "<<planeNumber<<" needs de-icing: sending to de-icing"<<endl;
	  
	}
	else{

	  //enqueues plane for takeoff if does not need deicing
	  cout<<"\t"<<"Plane "<<planeNumber<<" is enqueued for takeoff"<<endl;
	  takeOffQueue.enqueue(planeNumber);
	  takeOffQueueSize++;
	  
	  //checks the takeoffqueue size for max tracking
	  if(takeOffQueueSize > maxTakeOffQueue){
	    maxTakeOffQueue = takeOffQueueSize;
	  }
	}
	
	//tracks time plane entered queue
	waitingMap[planeNumber] = i;

	//increments plane number
	planeNumber++;
      }
      
      
    }
    

    //checks if the runway is free and proceeds if so
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

    //cout<<deIcingQueueSize<<endl;
    
    //merges deicing queue with takeoff queue if the size is greater than 3
    if(deIcingQueueSize > 3){
      cout<<"\t"<<"3 Planes have been de-iced.  Merging them to takeoff Queue"<<endl;
      deIcingQueueSize = 0;
      takeOffQueue.merge_two_queues(deIcingQueue);
      if(deIcingQueue.front()<1000){
	deIcingQueue.dequeue();
      }
      
    }
    
    //if there are still planes in the deicing queue and no new requests are being generated, merge deicing and takeoff
    if(i > timeLength && deIcingQueueSize!=0){
      cout<<"\t"<<"Merging remaining de-iced planes to takeoff Queue"<<endl;
      deIcingQueueSize = 0;
      takeOffQueue.merge_two_queues(deIcingQueue);
      
    }
    
    //check if every plane from simulation is dealt with and end the loop
    if(i > timeLength && takeOffQueue.empty() && landingQueue.empty() && deIcingQueue.empty()){

      //cout<<deIcingQueueSize<<endl;
      complete = true;
      
    }
    i++;

  }

  //calculates the average takeoff and landing times
  float averageTakeOffTime = (float)takeOffTotalTime/numTakeOffs;
  float averageLandingTime = (float)landingTotalTime/numLandings;
  
  //prints results
  
  cout<<"\n"<<"Simulation Finished! Statistics:"<<endl;
  cout<<"\t"<<"Average Waiting Time for Takeoff: "<<averageTakeOffTime<<" mins"<<endl;
  cout<<"\t"<<"Average Waiting Time for Landing: "<<averageLandingTime<<" mins"<<endl;
  cout<<"\t"<<"Maximum Length of Takeoff Queue: "<<maxTakeOffQueue<<endl;
  cout<<"\t"<<"Maximum Length of Landing Queue: "<<maxLandingQueue<<endl;
  cout<<endl;
  
  return 0; 

}
