#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include "bellRand.cpp"
#include "gridUnit.cpp"

#define OFF_THE_EDGE (int(defaultX) >= WORLD_SIZE || int(defaultY) >= WORLD_SIZE || int(defaultX) < 0 || int(defaultY) < 0)
#define TAB '\t'

// Food_B is energy, Food_A is protein
#define SPLIT_COST_A 20.0
#define SPLIT_COST_B 15.0

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

	double baseStrength;// Entirely Genetic.
	double weakness;
	double meteorImpactEffect;
	
	///							*** Inventory ***
	double foodA;
	double foodB;
	double foodAMax = 100;
	double foodBMax = 100;
	
public:
	///							*** Status ***
	double defaultX;
	double defaultY;
	bool isAlive;
	// Adam. Victim 0 of creation.
	microbe(){
		isAlive = true;
		
		gatherRate = 12;
		shareRate = 12;
		splitIndex = 2;

		baseStrength = 30;
		weakness =  0;
		
		meteorImpactEffect = 30;
		foodA = 30;
		foodB = 50;
	}
	// REPRODUCTION FAVORED BY BJARNE
	microbe(microbe &parent){
		isAlive = true;
		
		double *travA = &parent.gatherRate;
		double *travB = &this->gatherRate;
		// From gatherRate to baseStrength
		for(int i = 0; i < 4; i++, travA++, travB++)
			*travB = *travA + ran(0);
		
		this->weakness = 0;
		this->splitIndex = parent.splitIndex + ran(0)/25.0;
		this->meteorImpactEffect = parent.meteorImpactEffect + ran(0);
		
		// Bad Random Guards
		if(this->splitIndex < 0)
			splitIndex = 0;
		if(this->gatherRate < 0)
			gatherRate = 0;
		if(this->shareRate < 0)
			shareRate = 0;
		if(this->meteorImpactEffect < 0)
			meteorImpactEffect = 0;

		// Implementation hack: Parent reduces its food Qty to the individual food Qty of an offspring.
		this->foodA = parent.foodA;
		this->foodB = parent.foodB;

        // Placing Mechanism
        this->defaultX = parent.defaultX + 0.8*ran(0);
        this->defaultY = parent.defaultY + 0.8*ran(0);
        
        // Death because he fell of the edge of the world.
        if(OFF_THE_EDGE)
        	die();
	}
	
	~microbe(){}
	///						*** LIFE FUNCTIONS ***
	void shareFood(microbe*, int);
	void die();
	bool collectFood(gridUnit&);
	
	// This is the major function to be performed in every cycle.
	void performLife(gridUnit& home){
		if(!isAlive)
           return;
		// Death by bad health
		if(baseStrength+weakness < 0){
			die();
			return;
		}
		
		home.microbePtr = this;
		
		collectFood(home);

//						*** SHARING MECHANICS FOLLOW ***
		microbe* nearest[2];
		nearest[0] = nearest[1] = this;
		
		for(int itr = 0; itr < 2; itr++)
		for(int i = -2 ; i <= 2; i++){
			for(int j = -2; j <= 2; j++){
				if(i==0 && j==0)
					continue;
				// Guards against sharing off the edge
				if(defaultY+i >= WORLD_SIZE || defaultY+i < 0)
					continue;
				if(defaultX+j >= WORLD_SIZE || defaultX+j < 0)
					continue;
				// Provisional sharer decision			
				microbe* temp = world[int(defaultY+i)][int(defaultX+j)].lastMicrobePtr;
				if(temp != NULL && itr == 0 && temp->foodA > nearest[itr]->foodA)
					nearest[itr] = temp;
				if(temp != NULL && itr == 1 && temp->foodB > nearest[itr]->foodB)
					nearest[itr] = temp;
		  	}
		}
		
		if(nearest[0] != this) {
			shareFood(nearest[0], 0);
		}
		if(nearest[1] != this) {
			shareFood(nearest[1], 1);
		}
		// Food Consumption. Replace 2 by sustenence.
		foodA = foodA-2;
		foodB = foodB-2;

		if(foodA < 0)
			foodA = 0;
		if(foodB < 0)
			foodB = 0;

		// Death by hunger
		if(foodA <= 0 || foodB <= 0) {
			weakness += 5;
		}
		// Death by destability
		else if(foodA > foodAMax || foodB > foodBMax) {
			weakness += 5;
			foodA = foodAMax - 30;
			foodB = foodBMax - 30;
			home.foodA += 0.25*foodA;
			home.foodB += 0.25*foodB;
		}
		
		// Recover from weakness
		if(foodA > 5 && foodB > 5 && weakness > 0)
			weakness--;
		
		// For home might change from turn to turn
		home.lastMicrobePtr = home.microbePtr;
		home.microbePtr = NULL;
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
		 << TAB << "Splt" << TAB << "basStrn" << TAB <<"weakness"
		 << TAB << "foodA" << TAB << "foodB" << endl;
	
	if(isAlive)
		cout << "Yes";
	else
		cout << "No";
	for(int i = 0; i < 7; i++, trav++)
		cout << TAB << setprecision(3) << *trav;
	cout << endl; 
}

void microbe::shareFood(microbe *nearest, int type){
	double transit;
	// Food will transfer from lower to higher potential.

	// FoodA
	if(type == 0){
		transit = shareRate * (nearest->foodA - this->foodA)/100;
		// Canabalism
		if(transit > nearest->foodA){
			transit = nearest->foodA;
			nearest->die();
		}
		// Transition
		this->foodA += transit;
		nearest->foodA -= transit;
		return;
	}
	// FoodB
	if(type == 1){
		transit = shareRate * (nearest->foodB - this->foodB)/100;
		// Canabalism
		if(transit > nearest->foodB){
			transit = nearest->foodB;
			nearest->die();
		}
		// Transition
		this->foodB += transit;
		nearest->foodB -= transit;
		return;
	}
	
	return;
}

bool microbe::collectFood(gridUnit& home){
	bool collectedA = false, collectedB = false;
	double transit;
	
	if(home.foodA > this->foodA && home.foodA > 0){	// Flow_back restriction.
		// Transit proportional to available_space, gatherRate, food_difference
		transit = 1.0*gatherRate * (home.foodA-this->foodA)/home.foodA * (this->foodAMax-this->foodA)/100.0;
		
		// Avoid negative harvest
		if(home.foodA - transit < 0)
			transit = home.foodA;
		
		// Condition caused by an immense gather rate
		if(transit > foodAMax)
			transit = foodAMax-foodA;
			
		this->foodA += 0.9*transit;	// 0.1 is the penalty of collection.
		home.foodA -= transit;
		collectedA = true;
	}

	if(home.foodB > this->foodB && home.foodB > 0){
		// Transit proportional to available_space, gatherRate, food_difference
		transit = 1.0*gatherRate * (home.foodB-this->foodB)/home.foodB * (this->foodBMax-this->foodB)/100.0;

		// Avoid mining negative food
		if(home.foodB - transit < 0)
			transit = home.foodB;
		
		// Condition caused by an immense gather rate
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

void microbe::die(){
	this->isAlive = false;
	// Degrade self to food
	if(!OFF_THE_EDGE){
		world[int(defaultY)][int(defaultX)].foodA += 15.0;
		world[int(defaultY)][int(defaultX)].foodB += 12.0;
	}
	return;
}
