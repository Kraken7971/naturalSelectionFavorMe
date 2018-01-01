#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include "bellRand.cpp"
#include "gridUnit.cpp"

#define TAB '\t'

// Food_B is energy, Food_A is protein
#define SPLIT_COST_A 40.0
#define SPLIT_COST_B 20.0

using namespace std;
/*
1. No need for exclusive defence. That will complicate things. (Thinking on calamity resistance)
2. Allow major changes once in a blue moon. That will make things fun. (done)
3. Welcomed Bug. Excessive consumption causes weakness, corrosion and death.
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
		shareRate = 12;
		splitIndex = 2;

		baseStrength = 30;
		acquiredStrength = 0.0*baseStrength;
		
		foodA = 300;
		foodB = 500;
	}
	// REPRODUCTION FAVORED BY BJARNE
	microbe(microbe &parent){
		isAlive = true;
		
		double *travA = &parent.gatherRate;
		double *travB = &this->gatherRate;
		// From gatherRate to baseStrength
		for(int i = 0; i < 5; i++, travA++, travB++)
			*travB = *travA + ran(0);
		
		this->splitIndex = parent.splitIndex;// + ran(0)/20.0;
		
		// Bad Random Guards
		if(this->splitIndex < 0)
			splitIndex = 0;
		if(this->gatherRate < 0)
			gatherRate = 0;
		if(this->shareRate < 0)
			shareRate = 0;
			
		this->acquiredStrength = 0.0*baseStrength;

		// Implementation hack: Parent reduces its food Qty to the individual food Qty of an offspring.
		this->foodA = parent.foodA;
		this->foodB = parent.foodB;
	}
	
	~microbe(){}
	///						*** LIFE FUNCTIONS ***
	void shareFood(microbe&);
	bool collectFood(gridUnit&);
	
	// This is the major function to be performed in every cycle.
	void performLife(gridUnit& home){
		if(!isAlive)
			return;

		// Death by bad health
		if(baseStrength + acquiredStrength < 0){
			isAlive = false;
			// Degrade self to food.
			home.foodA += 30;
			home.foodB += 20;
			return;
		}
		
		home.microbePtr = this;
		
		collectFood(home);
		microbe* nearest = home.getNearest();
		
		if(nearest != NULL && nearest != this) {	// Residue Here.
			shareFood(*nearest);
		}
		// Food Consumption. Replace 5 by sustenence.
		foodA = foodA-5;
		foodB = foodB-5;

		if(foodA < 0)
			foodA = 0;
		if(foodB < 0)
			foodB = 0;

		// Death by hunger
		if(foodA == 0 || foodB == 0) {
			acquiredStrength -= 0.25 * baseStrength;    // baseStrength is proportional to sustenence.
		}
		// Death by destability
		else if(foodA > foodAMax || foodB > foodBMax) {
			acquiredStrength *= 0.9;
			foodA = foodAMax - 30;
			foodB = foodBMax - 30;
			home.foodA += 0.25*foodA;
			home.foodB += 0.25*foodB;
		}
		else {
			// Beautiful math at work.
			acquiredStrength = (0.1*foodA + 0.05*foodB) * (1 - acquiredStrength/(baseStrength+acquiredStrength));
		}
	}

	///						*** SUPPORT FUNCTIONS ***
	void report();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//############################################################################################################//
//############################################################################################################//
//############################################################################################################//
//############################################################################################################//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////GRAVEYARD OF CALLS////////////////////////////////////////////////////////


void microbe::report(){
	double *trav = &gatherRate;
	cout << "Alive" << TAB << "gather" << TAB << "share"
		 << TAB << "Splt" << TAB << "basStrn" << TAB << "acqStrn"
		 << TAB << "foodA" << TAB << "foodB" << endl;
	
	if(isAlive)
		cout << "Yes";
	else
		cout << "No";
	for(int i = 0; i < 7; i++, trav++)
		cout << TAB << setprecision(4) << *trav;
	cout << endl; 
}

void microbe::shareFood(microbe &nearest){
	double transit;
	// Food will transfer from lower to higher potential.

	// FoodA
	transit = shareRate * (nearest.foodA - this->foodA)/100;
	this->foodA += transit;
	nearest.foodA -= transit;
	// FoodB
	transit = shareRate * (nearest.foodB - this->foodB)/100;
	this->foodB += transit;
	nearest.foodB -= transit;
	
	return;
}

bool microbe::collectFood(gridUnit& home){
	bool collectedA = false, collectedB = false;
	double transit;
	
	if(home.foodA > this->foodA){	// Flow_back restriction.
		// Transit proportional to available_space, gatherRate, food_difference
		transit = 1.5*gatherRate * (home.foodA-this->foodA)/home.foodA * (this->foodAMax-this->foodA)/100.0;
		
		if(transit > foodAMax)
			transit = foodAMax-foodA;
			
		this->foodA += 0.9*transit;	// 0.1 is the penalty of collection.
		home.foodA -= transit;
		collectedA = true;
	}

	if(home.foodB > this->foodA){
		// Transit proportional to available_space, gatherRate, food_difference
		transit = 1.5*gatherRate * (home.foodB-this->foodB)/home.foodB * (this->foodBMax-this->foodB)/100.0;
		
		if(transit > foodBMax)
			transit = foodBMax-foodB;
			
		this->foodB += 0.9*transit;	// 0.1 is the penalty of collection.
		home.foodB -= transit;
		collectedB = true;
	}
		
	if(!collectedA || !collectedB)
		return 0;
	else
		return 1;
}
