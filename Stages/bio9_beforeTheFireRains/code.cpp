#include "microbe.cpp"
#include "gensys.cpp"
#include "calamity.cpp"
#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;
using namespace genSys;

/*
DESIGN PHILOSOPHY
1. The only thing that connects a microbe to the grid is performLife(home);
   That would allow multiple microbes to live off of a single grid unit.
*/

void routine(){
	int garbage = 0;	// Toll Collector
	clock_t then;
	double max;
	
	microbe* adam = new microbe;
	
	adam->defaultX = 15;
	adam->defaultY = 21;
	
	// Place first microbe in the world
	insertMicrobe(adam);
	
	//////////////////////////////SFML MAGIC FOLLOWS. MAY THE HANDS OF THE CARELESS BURN//////////////////////////
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(1344, 768), "My window", Style::Default, settings);
	
	CircleShape circle(5);

	
	// Five turns of life
	while(window.isOpen()){
//		sleep(milliseconds(100));
		Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear(Color::Black);
		
		then = clock();
		
		garbage = 0;
		for(int j = 0; j < 5; j++)
			for(int i = 0; i < genEnd; i++){
				microbe *micro = genA[i];
				if(!micro->isAlive)
					continue;
				calamityCheck(*micro, garbage);
				micro->performLife(world[int(micro->defaultY)][int(micro->defaultX)]);
			}
		
		getNewGeneration();
		getGenerationReport();
		
		/////////////////////////////// THE CURSED DRAWING PART ///////////////////////////////////////////
		window.clear();
		for(int i = 0; i < genEnd; i++){	
			microbe* micro = genA[i];
			circle.setPosition(micro->defaultX*42, micro->defaultY*24);
			if(!micro->isAlive){
				circle.setFillColor(Color(0, 0, 255, 90));
				circle.setOutlineThickness(2);
				window.draw(circle);
				continue;
			}
			unsigned colorByStrength = ((micro->baseStrength-30) / 30.0) * 255;
			unsigned colorBySplit = ((micro->splitIndex) / 5.0) * 255;
			unsigned colorByGather = ((micro->gatherRate-12) / 28) * 255;
			circle.setFillColor(Color(colorByStrength, colorBySplit, colorByGather, 90));
			circle.setOutlineThickness(0);
			window.draw(circle);
		} 
		
		while(double(clock()) - double(then) < 10000);
		window.display();
			
		if(genEnd == 0)
			break;
		cout << "Generation Populace: " << genEnd << endl;		
	}
	
	double remA = 0, remB = 0;
	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++){
			remA += world[i][j].foodA;
			remB += world[i][j].foodB;
		}
		
	cout << remA/1024.0 << TAB << remB/1024.0 << endl;
}

int main(){
	srand(0);
	initGridSystem();
	initGenerationSystem();
	
	cout << "Generation & Grid systems are up" << endl
		 << "Initiating routine..." << ran(0) << endl;
	routine();
	
	cout << endl;
	return 0xDEAD;
}
