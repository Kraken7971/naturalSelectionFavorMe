#include <iostream>
#include <iomanip>
#include <ctime>
#include "bellRand.cpp"
#include "food.cpp"

#define TAB '\t'

using namespace std;
/*
1. No need for exclusive defence. That will complicate things. (Thinking on calamity resistance)
2. Allow major changes once in a blue moon. That will make things fun.
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
	
	///							*** Behavior ***
	double attackTendency;
public:
	// Adam. Victim 0 of creation.
	microbe(){
		gatherRate = 10;
		shareRate = 9;
		splitIndex = 2;
		
		baseStrength = 30;
		acquiredStrength = 0.2*(foodA+foodB) + 0.2*baseStrength;
		
		foodA = 3;
		foodB = 5;
	}
	// REPRODUCTION FAVORED BY BJARNE
	microbe(microbe &parent){
		double *travA = &parent.gatherRate;
		double *travB = &this->gatherRate;
		// From gatherRate to baseStrength
		for(int i = 0; i < 5; i++, travA++, travB++)
			*travB = *travA + ran(0);
		
		this->splitIndex = parent.splitIndex + ran(0)/10.0;
		
		if(this->splitIndex < 0)
			splitIndex = 0;
		if(this->gatherRate < 0)
			gatherRate = 0;
		if(this->shareRate < 0)
			shareRate = 0;
			
		this->acquiredStrength = 0.2*(foodA+foodB) + 0.2*baseStrength;
		this->foodA = parent.foodA / int(parent.splitIndex);
		this->foodB = parent.foodB / int(parent.splitIndex);
	}
	
	~microbe(){}
	///			*** LIFE FUNCTIONS ***
	//void gatherFoor(food& food
	
	///			*** SUPPORT FUNCTIONS ***
	void report(){
		double *trav = &gatherRate;
		cout << "Rep." << TAB << "gather" << TAB << "share"
			 << TAB << "Splt" << TAB << "basStrn" << TAB
			 << "acqStrn" << TAB << "foodA" << TAB << "foodB"
			 << endl;
	
		for(int i = 0; i < 7; i++, trav++)
			cout << TAB << setprecision(4) << *trav;
		cout << endl; 
	}
};
