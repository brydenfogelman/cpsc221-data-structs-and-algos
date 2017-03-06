#include <iostream>
#include <string>
#include <map>
using namespace std;
#include <time.h>
#include <map>
#include "LQueue.h"

int main(void)
{
	// Deafults
	int landingTime = 2;
	int takeoffTime = 3;
	int landingRate = 10;
	int takeoffRate = 12;
	int priorityRate = 3;
	int duration = 120;

	cout << "################################" << endl;
	cout << "WELCOME TO PLANE SIMULATION 2017" << endl;
	cout << "################################" << endl;
	cout <<"Winner of over 7 game of the year awards!" << endl;
	cout <<"10/10 - IGN" << endl;
	cout <<"Truly a masterpeice - Gamespot" <<endl;
	cout << endl;

	cout << "INPUT VALUES: " << endl;
	cout << "Time it takes a plane to land: ";
	cin >> landingTime;

	cout << "Time it takes a plane to takeoff: ";	
	cin >> takeoffTime;

	cout << "Landing Rate: ";
	cin >> landingRate;

	cout << "Takeoff Rate: ";
	cin >> takeoffRate;

	cout << "Priority Rate: ";
	cin >> priorityRate;

	cout << "Time to run simulation: ";
	cin >> duration;


	

	// PLANE
	int planeNum = 1000;
	int currentPlane; // value for the plane that is being dequeued

	// QUEUE
	Queue landingQ;
	int sizeLandingQ = 0;

	Queue takeoffQ;
	int sizeTakeoffQ = 0;

	// RUNWAY
	bool runwayFree = true;

	// string action;
	int runwayWait;

	// STATISTICS

	// create map to keep track of arrival and landing times
	map<int,int> times;

	int totalPlanesLanded = 0;
	int totalPlanesTakeoff = 0;

	int avgPlanesLanding = 0;
	int avgPlanesTakeoff = 0;

	double avgMinLanding = 0;
	double avgMinTakeoff = 0;

	int maxLanding = 0;
	int maxTakeoff = 0;


	// SETUP
	// seed random number
	srand(time(NULL));

	// time
	int min = 0;

	// when all queues are empty and the inputted duration has elasped, end the program
	while(true)
	{
		cout << "TIME " << min << endl;
		
		// only recieve requests for designated duration
		if(min <= duration)
		{
			// landing request
			if(rand() % 60 < landingRate){
				sizeLandingQ++;
				cout << "---- ADDED TO LANDING QUEUE----" << endl;
				cout << "\tPlane " << planeNum << " wants to land; added to landing queue; " << sizeLandingQ << " in queue" << endl;
				landingQ.enqueue(planeNum);

				// priority landing
				if(rand() % 60 < priorityRate)
				{
					cout << "---- PLANE GIVEN PRIORITY ---- " << endl;
					cout << "\tPlane given priority landing and moved to front of queue" << endl;
					landingQ.move_to_front(planeNum);
				}

				// record time when plane arrived
				times[planeNum] = min;
			}
			// takeoff request
			if(rand() % 60 < takeoffRate){
				sizeTakeoffQ++;
				cout << "---- ADDED TO TAKEOFF QUEUE----" << endl;
				cout << "\tPlane " << planeNum << " wants to takeoff; added to takeoff queue; " << sizeTakeoffQ << " in queue" << endl;
				takeoffQ.enqueue(planeNum);

				// record time when plane arrived
				times[planeNum] = min;
			}
		}

		// if the landing queue has a plane, land it
		if(runwayFree && !landingQ.empty()) {
			// get current plane number
			currentPlane = landingQ.front();

			// increment statistics
			totalPlanesLanded++;
			sizeLandingQ--;
			avgMinLanding += min - times[currentPlane];

			cout << "---- PLANE LANDING ON RUNWAY ----" << endl;
			cout << "\tLanding plane " << currentPlane << endl;
			cout << "\tLanding: " << sizeLandingQ << " in queue" << endl;
			cout << "\tTime spent waiting (min) to start land: " << min - times[currentPlane] << endl;
			
			// remove plane from dequeue
			landingQ.dequeue();

			// set the time it takes for plane to land
			runwayWait = landingTime;

			// runway is now busy
			runwayFree = false;
		}

		// if take off queue has a plane, fly it out
		if(runwayFree && !takeoffQ.empty()) {
			// get current plane number
			currentPlane = takeoffQ.front();

			// increment statistics
			totalPlanesTakeoff++;
			sizeTakeoffQ--;
			avgMinTakeoff += min - times[currentPlane];

			cout << "---- PLANE TAKING OFF ON RUNWAY ----" << endl;
			cout << "\tTakeoff: " << sizeTakeoffQ << " in queue" << endl;
			cout << "\tTakeoff plane " << takeoffQ.front() << endl;
			cout << "\tTime spent waiting (min) to start takeoff: " << min -times[currentPlane] << endl;

			// remove plane from takeoff queue
			takeoffQ.dequeue();
			
			// set the time it takes for a plane to takeoff
			runwayWait = takeoffTime;

			// runway is now busy
			runwayFree = false;

		}

		// whatever plane was in the the runway is now out
		if(runwayWait == 0) {
			cout << "---- RUNWAY FREE ----" << endl;
			runwayFree =  true;
		// plane is still on runway
		} else {
			runwayWait--;
		}

		// next plane
		planeNum++;

		// next minute
		min++;

		// statistics
		avgPlanesLanding += sizeLandingQ;
		avgPlanesTakeoff += sizeTakeoffQ;

		// set max queue sizes
		if(sizeLandingQ > maxLanding) maxLanding = sizeLandingQ;
		if(sizeTakeoffQ > maxTakeoff) maxTakeoff = sizeTakeoffQ;

		if(landingQ.empty() && takeoffQ.empty() && (min > duration)) break;

	}
	cout << "\n\nSTATISTICS" << endl;
	cout << "Average time waiting in landing queue: " << (avgMinLanding / totalPlanesLanded) << endl;
	cout << "Max planes in landing queue: " << maxLanding << endl;
	cout << "Average time waiting in takeoff queue: " << (avgMinTakeoff / totalPlanesTakeoff) << endl;
	cout << "Max planes in takeoff queue: " << maxTakeoff << endl;

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
