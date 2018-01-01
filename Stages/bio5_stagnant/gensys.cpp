#define GEN_SIZE 10000000

namespace genSys{
microbe** genA;
microbe** genB;

int genEnd;

//								*** ONE TIMERS ***
void initGenerationSystem(){
	delete genA;
	delete genB;
	genA = new microbe*[GEN_SIZE];
	genB = new microbe*[GEN_SIZE];
	
	for(int i=0; i<GEN_SIZE; i++)
		genB[i] = genA[i] = NULL;
}

void insertMicrobe(microbe* microbe){
	genA[genEnd++] = microbe;
}

//								*** MAIN ACTION ***
void split(microbe* microbePtr, int &genAIndex, int &genBIndex){
	// I forbid the dead and sterile from procreating
	if(!microbePtr->isAlive || microbePtr->splitIndex < 1){
		genAIndex++;
		return;
	}
		
	// Figure an optimal split index on the basis of food and split index
	int optimalSplit = microbePtr->foodA/SPLIT_COST_A < microbePtr->foodB/SPLIT_COST_B?
						microbePtr->foodA/SPLIT_COST_A:microbePtr->foodB/SPLIT_COST_B;
	if(optimalSplit > microbePtr->splitIndex)
		optimalSplit = microbePtr->splitIndex;// Integer truncation is automatic
	
	
	// Consume Food For Reproduction
	microbePtr->foodA -= SPLIT_COST_A*(optimalSplit - 1);
	microbePtr->foodB -= SPLIT_COST_B*(optimalSplit - 1);
	
	// Assume the amount of food that each of the child my cary
	microbePtr->foodA = microbePtr->foodA/(double)(optimalSplit);
	microbePtr->foodB = microbePtr->foodB/(double)(optimalSplit);
	// Populate the other array
	for(int i = 0; i < optimalSplit; i++)
		genB[genBIndex++] = new microbe(*genA[genAIndex]);
	
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
	
	delete[] genB;
	genB = new microbe*[GEN_SIZE];
}

void getGenerationReport(){
	static int number = 0;
	
	int i;
	double gatherRate, shareRate, splitIndex, baseStrength;
	gatherRate = shareRate = splitIndex = baseStrength = 0.0;
	
	for(i = 0; i < genEnd; i++){
		gatherRate += genA[i]->gatherRate;
		shareRate += genA[i]->shareRate;
		splitIndex += genA[i]->splitIndex;
		baseStrength += genA[i]->baseStrength;
	}
		
	cout << "GenRep." << TAB << "Gather" << TAB << "Share" << TAB
		 << "Split" << TAB << "BaseStrn" << endl;
	
	cout << ++number << TAB << gatherRate/i << TAB << shareRate/i
		 << TAB << splitIndex/i << TAB << baseStrength/i;
	cout << endl;
}


};
