#include <iostream>
#include <iomanip>
#include <ctime>
#include "bellRand.cpp"
#include "gridUnit.cpp"

#define TAB '\t'

#define SPLIT_COST_A 40.0
#define SPLIT_COST_B 20.0

using namespace std;
/*
1. No need for exclusive defence. That will complicate things. (Thinking on calamity resistance)
2. Allow major changes once in a blue moon. That will make things fun. (done)
*/

class microbe{
public:
	///							*** Attributes ***
	double gatherRate;	// Includes conversion rate. dx/dt = k.[Qhi-Qlo]
	double shareRate;	// dx/dt = k.[Qhi/Max1 - Qlo/Max2]
	double splitIndex;	// Birth Rate. Default 2.
	
	// netStrength = baseStrength + acquiredStrength. Combined attribute of defense, virility. Measure of survival.
	double baseStrength;// Entirely Genetic. Platform for acquiredStrength.
	double acquiredStrength; // Entirely environmental. Possibly negative. Seek to make it a function of food.

	///							*** Inventory ***
	double foodA;
	double foodB;
	double foodAMax = 100;
	double foodBMax = 100;
	
	///							*** Status ***
	bool isAlive;
public:
	// Adam. Victim 0 of creation.
	microbe(){
		isAlive = true;
		
		gatherRate = 10;
		shareRate = 9;
		splitIndex = 2;
		
		baseStrength = 30;
		acquiredStrength = 0.1*baseStrength;
		
		foodA = 3;
		foodB = 5;
	}
	// REPRODUCTION FAVORED BY BJARNE
	microbe(microbe &parent){
		ifAlive = true;
		
		double *travA = &parent.gatherRate;
		double *travB = &this->gatherRate;
		// From gatherRate to baseStrength
		for(int i = 0; i < 5; i++, travA++, travB++)
			*travB = *travA + ran(0);
		
		this->splitIndex = parent.splitIndex + ran(0)/10.0;
		this->gatherRate = 0;
		
		// Bad Random Guard
		if(this->splitIndex < 0)
			splitIndex = 0;
		if(this->gatherRate < 0)
			gatherRate = 0;
		if(this->shareRate < 0)
			shareRate = 0;
			
		this->acquiredStrength = 0.1*baseStrength;
		this->foodA = parent.foodA / int(parent.splitIndex);
		this->foodB = parent.foodB / int(parent.splitIndex);
	}
	
	~microbe(){}
	///			*** LIFE FUNCTIONS ***
	void shareFood(microbe&);
	bool collectFood(gridUnit&);
	
	// This the major function to be performed in every cycle.
	void performLife(gridUnit& home){
		if(!isAlive)
			return;
		if(baseStrength + acquiredStrength < 0){
			isAlive = false;
			return;
		}
		collectFood(home);
		microbe* nearest = home.getNearest();
		shareFood(*nearest);

		foodA = foodA-10;
		foodB = foodB-10;
		
		acquiredStrength = 0.1*baseStrength + 0.4*(foodA-30.0) + 0.2*(foodB-30);
	}

	
	///			*** SUPPORT FUNCTIONS ***
	void report();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////GRAVEYARD OF CALLS////////////////////////////////////////////////////////
void microbe::report(){
	double *trav = &gatherRate;
	cout << "Rep." << TAB << "gather" << TAB << "share"
		 << TAB << "Splt" << TAB << "basStrn" << TAB << "acqStrn"
		 << TAB << "foodA" << TAB << "foodB" << endl;
	
	for(int i = 0; i < 7; i++, trav++)
		cout << TAB << setprecision(4) << *trav;
	cout << endl; 
}

void microbe::shareFood(microbe &nearest){
	double transit = (shareRate/10.0) * (nearest.foodA - this->foodA);
	// Food will transfer from lower to higher potential.
	this->foodA += transit;
	nearest.foodA -= transit;
	
	// Done with food_A by now.
	transit = (shareRate/10.0) * (nearest.foodB- this->foodB);
	this->foodB += transit;
	nearest.foodB -= transit;
	
	return;
}

bool microbe::collectFood(gridUnit& home){
	bool collectedA = false, collectedB = false;
	double transit;
	
	if(home.foodA > this->foodA){	// Flow_back restriction.
		transit = (gatherRate/300.0) * (home.foodA - this->foodA);
		this->foodA += 0.9*transit;	// 0.1 is the penalty of collection.
		home.foodA -= transit;
		collectedA = true;
	}
	if(home.foodB > this->foodA){
		double transit = (gatherRate/300.0) * (home.foodB - this->foodB);
		this->foodB += 0.9*transit;	// 0.1 is the penalty of collection.
		home.foodB -= transit;
		collectedB = true;
	}
		
	if(!collectedA || !collectedB)
		return 0;
	else
		return 1;
}
