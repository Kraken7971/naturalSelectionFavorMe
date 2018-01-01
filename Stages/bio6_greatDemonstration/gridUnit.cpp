#define WORLD_SIZE 32

class microbe;

class gridUnit{
public:
	double foodA;	// ENERGY
	double foodB;	// PROTEINS
	double conditions;
	
	// This can be fun
	bool isPoison = false;
	bool causeStirility = false;
	bool causeConstriction = false;
	
	microbe* microbePtr;
	microbe* lastMicrobePtr;
	
	gridUnit(){
		foodA = 1000;
		foodB = 1000;
		conditions = 29;
		microbePtr = NULL;
		lastMicrobePtr = NULL;
	}
	
	gridUnit(double qtyA, double qtyB = 100){
		gridUnit::foodA = qtyA;
		gridUnit::foodB = qtyB;
		microbePtr = NULL;
		lastMicrobePtr = NULL;
	}
};

gridUnit world[WORLD_SIZE][WORLD_SIZE];

void initGridSystem(){
	for(int i = 0; i < 17; i++)
		for(int j = 0; j < WORLD_SIZE; j++){			world[i][j].foodA = i*j;
			world[i][j].foodB = world[i][j].foodA = 100000;
			world[i][j].conditions = 3*i;
		}
	return;
}
