#include <iostream>
#include <ctime>
using namespace std;
/*
1. No need for exclusive defence. That will complicate things.
2. Allow major changes once in a blue moon. That will make things fun.
*/
class microbe{
private:
	///							*** Attributes ***
	double gatherRate;	// Includes conversion rate. dx/dt = k.[Qhi-Qlo]
	double shareRate;	// dx/dt = k.[Qhi/Max1 - Qlo/Max2]
	double splitIndex;	// Birth Rate. Default 2.
	//netStrength = baseStrength + acquiredStrength. Combined attribute of defense, virility. Measure of survival.
	double baseStrength;// Entirely Genetic. Platform for acquiredStrength.
	double acquiredStrength; // Entirely environmental. Possibly negative. Seek to make it a function of food.

	//							*** Inventory ***
	double foodA;
	double foodB;
	double foodAMax = 100;
	double foodBMax = 100;
	
	//							*** Behavior ***
	double attackTendency;
public:
	microbe(){
		gatheRate = 10;
		shareRate = 9;
		splitIndex = 2;
		
		baseStrength = 30;
		acquiredStrength = 0;
		
		foodA = 3;
		foodB = 5;
	}
	// REPRODUCTION FAVORED BY BJARNE
	microbe(microbe &parent){
		double rand = (double)(rand()%100);
	}
};

int main(){
	srand(time(NULL));

	cout << "Hello World" << endl;
	return 0xDEAD;
}
