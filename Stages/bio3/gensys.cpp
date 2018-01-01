microbe** genA;
microbe** genB;
int genEnd;
extern double randFactor;

//								*** ONE TIMERS ***
void initGenerationSystem(){
	delete genA;
	delete genB;
	genA = new microbe*[100000000];
	genB = new microbe*[100000000];
	
	for(int i=0; i<1000; i++)
		genB[i] = genA[i] = NULL;
}

void insertMicrobe(microbe* microbe){
	genA[genEnd++] = microbe;
}

//								*** MAIN ACTION ***
void split(microbe* microbePtr, int &genAIndex, int &genBIndex){
	// I forbid the dead from procreating
	if(!microbePtr->isAlive){
		genAIndex++;
		return;
	}
		
	// Figure an optimal split index on the basis of food and split index
	int optimalSplit = microbePtr->foodA/SPLIT_COST_A < microbePtr->foodB/SPLIT_COST_B?
						microbePtr->foodA/SPLIT_COST_A:microbePtr->foodB/SPLIT_COST_B;
	if(optimalSplit > microbePtr->splitIndex)
		optimalSplit = microbePtr->splitIndex;// Integer truncation is automatic
	
	// Populate the other array
	for(int i = 0; i < optimalSplit; i++)
		genB[genBIndex++] = new microbe(*genA[genAIndex]);
	
	// Very important
	delete microbePtr;
	genAIndex++;
}

void getNewGeneration(){
	microbe** temp;
	int genAIndex = 0, genBIndex = 0;
	
	while(genAIndex < genEnd){
		split(genA[genAIndex], genAIndex, genBIndex);	//Split increments
	}
	
	genEnd = genBIndex;
	
	// Flip the arrays.
	temp = genB;
	genB = genA;
	genA = temp;
}

void getGenerationReport(){
	static int number = 0;
	int i, deadCount;
	double gatherRate, shareRate, splitIndex, baseStrength;
	gatherRate = shareRate = splitIndex = baseStrength = 0.0;
	
	for(i = deadCount = 0; i < genEnd; i++){
		if(genA[i]->isAlive == false){
			deadCount++;
			continue;
		}
		gatherRate += genA[i]->gatherRate;
		shareRate += genA[i]->shareRate;
		splitIndex += genA[i]->splitIndex;
		baseStrength += genA[i]->baseStrength;
	}
	
	i = i-deadCount;
		
	cout << "GenRep." << TAB << "Gather" << TAB << "Share" << TAB
		 << "Split" << TAB << "BaseStrn" << endl;
	
	cout << ++number << TAB << gatherRate/i << TAB << shareRate/i
		 << TAB << splitIndex/i << TAB << baseStrength/i;
	if(number > 20)
		randFactor = 0.5;
	else
		randFactor = 0.01;
	cout << endl;
}
