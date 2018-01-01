char dispGrid[WORLD_SIZE][WORLD_SIZE];

void resetDisplay(){
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

void renderDisplay(){
	// Display Microbes
	for(int i = 0; i < genSys::genEnd; i++){
		microbe *micro = genSys::genA[i];
		if(!micro->isAlive)
			continue;
		if(dispGrid[micro->defaultY][micro->defaultX] == '*')
			dispGrid[micro->defaultY][micro->defaultX] += 1;
		else
			dispGrid[micro->defaultY][micro->defaultX] = '*';
	}
	// Display Meteors
	return;
}

void display(){
	resetDisplay();
	renderDisplay();
	displayGrid();
}
