#include "microbe.cpp"
#include "gensys.cpp"
#include "calamity.cpp"
#include "display.cpp"
#include <SFML/Graphics.hpp>

using namespace sf;

/*
DESIGN PHILOSOPHY
1. The only thing that connects a microbe to the grid is performLife(home);
   That would allow multiple microbes to live off of a single grid unit.
*/

void routine(RenderWindow& window){
	int garbage = 0;	// Toll Collector
	microbe* adam = new microbe;
	
	adam->defaultX = 15;
	adam->defaultY = 21;
	
	// Place first microbe in the world
	genSys::insertMicrobe(adam);
	

	
	// Five turns of life
	while(cin.get()!='x'){
		garbage = 0;
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
		
		
		cout << "Generation Populace: " << genSys::genEnd << endl;
		cout << endl << endl << TAB << TAB << "BEAUTY FOLLOWS" << endl;
		
	}
	
	double remA = 0, remB = 0;
	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++){
			cout << i << TAB << j << TAB << world[i][j].foodA << endl;
			remA += world[i][j].foodA;
			remB += world[i][j].foodB;
		}
	cout << remA/1024.0 << TAB << remB/1024.0;
}

int main(){
	srand(0);
	resetDisplay();
	initGridSystem();
	genSys::initGenerationSystem();
	
	RenderWindow window(VideoMode(320, 320), "My window");
	
	cout << "Generation & Grid systems are up" << endl
		 << "Initiating routine..." << ran(0) << endl;
	routine(window);
	
	cout << endl;
	return 0xDEAD;
}
