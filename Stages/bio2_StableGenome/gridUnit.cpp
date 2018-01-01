#define FOOD 0
#define TRAV 1

class microbe;

extern void* globe;

class gridUnit{
public:
	int x, y;
	double foodA;	// AirLike
	double foodB;	// FoodLike
	
	// This can be fun
	bool isPoison = false;
	bool causeStirility = false;
	bool causeConstriction = false;
	
	microbe* microbePtr;
	
	gridUnit(){
		foodA = (0.8+bellRandom(0))*1000;
		foodB = (0.8+bellRandom(0))*1000;
		microbePtr = NULL;
	}
	
	gridUnit(double qtyA, double qtyB = 100){
		gridUnit::foodA = qtyA;
		gridUnit::foodB = qtyB;
		microbePtr = NULL;
	}
	
	void setLocus(int x, int y){
		this->x = x;
		this->y = y;
	
	}
	
	///								*** SUPPORT ***
	microbe* getNearest(){
		return (microbe*)globe;
	}
};
