#define WORLD_SIZE 32

class microbe;

class gridUnit{
public:
	int x, y;
	double foodA;	// ENERGY
	double foodB;	// PROTEINS
	
	// This can be fun
	bool isPoison = false;
	bool causeStirility = false;
	bool causeConstriction = false;
	
	microbe* microbePtr;
	microbe* lastMicrobePtr;
	
	gridUnit(){
		foodA = 1000;
		foodB = 1000;
		microbePtr = NULL;
		lastMicrobePtr = NULL;
	}
	
	gridUnit(double qtyA, double qtyB = 100){
		gridUnit::foodA = qtyA;
		gridUnit::foodB = qtyB;
		microbePtr = NULL;
		lastMicrobePtr = NULL;
	}
	
	void setLocus(int x, int y){
		this->x = x;
		this->y = y;
	}
	
	///								*** SUPPORT ***
	microbe* getNearest(){
		return NULL;
	}
};

gridUnit world[WORLD_SIZE][WORLD_SIZE];

void initGridSystem(){
	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++)
			world[i][j].setLocus(i, j);
}
