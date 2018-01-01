#include "microbe.cpp"

#define WORLD_SIZE 32
using namespace std;

void * globe;

void routine(){
	gridUnit world[WORLD_SIZE][WORLD_SIZE];
	
	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++)
			world[i][j].setLocus(i, j);

	microbe adam;
	microbe olaf(adam);
	
	gridUnit hell(-1111, -1111);
	gridUnit heaven(101111, 100111);
	gridUnit purgutory(0, 0);
	
	globe = &adam;
	// Adam lives in heaven. Olaf, in purgutory.
	// Olaf has no food. Adam Shares.

	for(int i=0; i<30; i++){
		adam.performLife(heaven);
		olaf.performLife(purgutory);
	}

	cout << heaven.foodA << TAB << heaven.foodB << endl;
	adam.report();
	olaf.report();
}

int main(){
	srand(time(NULL));
	
	routine();
	
	cout << endl;
	return 0xDEAD;
}
