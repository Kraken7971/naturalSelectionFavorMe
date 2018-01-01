#include "microbe.cpp"
#include "gensys.cpp"
#include "calamity.cpp"

/*
DESIGN PHILOSOPHY
1. The only thing that connects a microbe to the grid is performLife(home);
   That would allow multiple microbes to live off of a single grid unit.
*/

char dispGrid[WORLD_SIZE][WORLD_SIZE];

void initDisplay(){
	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++)
			dispGrid[i][j] = ' ';
	return;
}

void displayGrid(){
	for(int i = 0; i < WORLD_SIZE; i++){
		for(int j = 0; j < WORLD_SIZE; j++)
			cout << dispGrid[i][j] << " ";
		cout << endl;
	}
	return;
}

void routine(){
	int garbage = 0;	// Toll Collector
	microbe* adam = new microbe;
	
	adam->defaultX = 15;
	adam->defaultY = 18;
	
	// Place first microbe in the world
	genSys::insertMicrobe(adam);
	
	// Five turns of life
	while(cin.get()!='x'){
		garbage = 0;
		initDisplay();
		for(int j = 0; j < 5; j++)
			for(int i = 0; i < genSys::genEnd; i++){
				microbe *micro = genSys::genA[i];
				if(!micro->isAlive)
					continue;
				calamityCheck(*micro, garbage);
				micro->performLife(world[micro->defaultY][micro->defaultX]);
			}
		genSys::getNewGeneration();
		genSys::getGenerationReport();
		
		for(int i = 0; i < genSys::genEnd; i++){
			microbe *micro = genSys::genA[i];
			if(!micro->isAlive)
				continue;
			if(dispGrid[micro->defaultY][micro->defaultX] == '*')
				dispGrid[micro->defaultY][micro->defaultX] += 1;
			else
				dispGrid[micro->defaultY][micro->defaultX] = '*';
		}
			
		cout << "Generation Populace: " << genSys::genEnd << endl;
		cout << endl << endl << TAB << TAB << "BEAUTY FOLLOWS" << endl;
		displayGrid();
		
	}
	
	double remA = 0, remB = 0;
	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++){
			remA += world[i][j].foodA;
			remB += world[i][j].foodB;
		}
	cout << remA/1024.0 << TAB << remB/1024.0;
}

int main(){
	srand(0);
	initDisplay();
	initGridSystem();
	genSys::initGenerationSystem();
	
	cout << "Generation & Grid systems are up" << endl
		 << "Initiating routine..." << ran(0) << endl;
	routine();
	
	cout << endl;
	return 0xDEAD;
}
