#define FOOD 0
#define TRAV 1

class microbe;

class gridUnit{
public:
	int x, y;
	double foodA;	// AirLike
	double foodB;	// FoodLike
	
	// This can be fun
	bool isPoison = false;
	bool causeStirility = false;
	bool causeConstriction = false;
	
	microbe* microPtr;
	microbe* temp;
	
	gridUnit(){
		foodA = 1000;
		foodB = 1000;
	}
	
	gridUnit(int qtyA, int qtyB = 100){
		gridUnit::foodA = qtyA;
		gridUnit::foodB = qtyB;
	}
	
	///								*** SUPPORT ***
	microbe* getNearest(){
		return temp;
	}
};
