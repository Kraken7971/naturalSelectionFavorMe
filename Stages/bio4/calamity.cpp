extern int genSys::genEnd;

double randFactor = 0.2;

void calamityCheck(microbe &microbe, int& toll){
	// Random accidental death
	double popFactor = randFactor * (double)(genSys::genEnd/10000);
	if((double)random()/RAND_MAX < popFactor){
		microbe.isAlive = false;
		++toll;
		return;
	}
	
	// Death due to environmental constraint. Cause: Weakness
	if(microbe.baseStrength < 29){
		microbe.isAlive = false;
		++toll;
		return;
	}
}
