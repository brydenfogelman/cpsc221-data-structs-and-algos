#include <iostream>
using namespace std;
#include <time.h>
#include "LQueue.C"

int main(void)
{

  int takeOffRate;
  int landingRate;
  int takeOffTime;
  int landingTime;
  int timeLength;

  int landingRand;
  int takeOffRand;

  Queue landingQueue;
  Queue takeOffQueue;
  
  bool runwayFree = true;

  int planeNumber = 1000;
  int waitTime = 0;
  int activePlane;

  //Accept user input for all above variables:

  cout<<"Enter the following parameters for simulation (integers only):"<<endl;

  cout<<"Duration of Landing: ";
  cin>>landingTime;
  
  cout<<"Duration of Takeoff: ";
  cin>>takeOffTime;

  cout<<"Landing Rate in Planes per hour: ";
  cin>>landingRate;

  cout<<"Takeoff Rate in planes per hour: ";
  cin>>takeOffRate;

  cout<<"Duration of Simulation: ";
  cin>>timeLength;

  srand(time(NULL));

  for(int i = 0; i < timeLength; i++){
    
    cout<<"TIME: "<<i<<endl;

    if(waitTime!=0){
      waitTime--;
      cout<<"Runway Busy!!"<<endl;
    }
    else{
      runwayFree = true;
      cout<<"Runway Open!!"<<endl;
    }

    
    landingRand = rand() % 60;

    //cout<<landingRand<<endl;
    takeOffRand = rand() % 60;
    
    //cout<<takeOffRand<<endl;

    if(landingRand < landingRate){
      cout<<"Enqueuing Plane "<<planeNumber<<" to landing queue"<<endl;
      landingQueue.enqueue(planeNumber);
      planeNumber++;
      
    }
    if(takeOffRand < takeOffRate){
      cout<<"Enqueuing Plane "<<planeNumber<<" to take off queue"<<endl;
      takeOffQueue.enqueue(planeNumber);
      planeNumber++;
      
    }
    
    if(runwayFree){
      
      if(!landingQueue.empty()){
	
	//Dequeue plane from landing queue
	//Set wait timer to landing time
	cout<<"Plane "<<landingQueue.front()<<" LANDING"<<endl;
	landingQueue.dequeue();
	runwayFree = false;
	waitTime = landingTime;
		
      }
      else{
	
	//Dequeue plane from takeoff queue
	//Set wait timer to takeoff time
	
	if(!takeOffQueue.empty()){
	  cout<<"Plane "<<takeOffQueue.front()<<" TAKING OFF"<<endl;
	  takeOffQueue.dequeue();
	  runwayFree = false;
	  waitTime = takeOffTime;
	
	}	
      }
    }

    

  }

  return 0; 
}
