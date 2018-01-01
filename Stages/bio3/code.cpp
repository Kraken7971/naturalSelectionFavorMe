#include "microbe.cpp"
#include "gensys.cpp"
#include "calamity.cpp"

#define WORLD_SIZE 32
using namespace std;

void routine(){
	// make adam
	insertMicrobe(new microbe);
	
	getGenerationReport();
	while(cin.get() != 'x'){
		int toll = 0;
		cout << endl << endl << "\t\t*** New Generation ***" << endl << endl;
		getNewGeneration();
		getGenerationReport();
		
		for(int i = 0; i < genEnd; i++)
			calamityCheck(*genA[i], toll);
		cout << "Post Natal deaths in generation: " << toll << "/" << genEnd
			<< ": " << 100.0*(double(toll)/genEnd) << "%";
	}
}

void _routine(){
	gridUnit world[WORLD_SIZE][WORLD_SIZE];
	
	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++)
			world[i][j].setLocus(i, j);

	microbe adam;
	microbe olaf(adam);
	
	gridUnit hell(-1111, -1111);
	gridUnit heaven(11111, 10111);
	gridUnit purgutory(0, 0);
	
	// Adam lives in heaven. Olaf, in purgutory.
	// Olaf has no food. Adam Shares.

//	for(int i=0; i<10; i++){
//		adam.performLife(heaven);
//		olaf.performLife(purgutory);
//	}

	cout << heaven.foodA << TAB << heaven.foodB << endl;
	adam.report();
	olaf.report();
}

int main(){
	srand(time(NULL));
	
	initGenerationSystem();
	cout << "Generation system is up" << endl
		 << "Initiating routine..." << endl;
	routine();
	
	cout << endl;
	return 0xDEAD;
}
