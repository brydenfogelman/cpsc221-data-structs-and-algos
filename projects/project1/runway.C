#include <iostream>
#include <string>
#include <map>
using namespace std;

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

	return 0;
}