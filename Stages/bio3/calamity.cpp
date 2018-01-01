int weaknessLimit = 28;
double randFactor = 0;

void calamityCheck(microbe &microbe, int& toll){
	// Random accidental death
	if((double)random()/RAND_MAX < randFactor){
		microbe.isAlive = false;
		++toll;
		return;
	}
	
	// Death due to environmental constraint. Cause: Weakness
	if(microbe.baseStrength + microbe.acquiredStrength < weaknessLimit){
		microbe.isAlive = false;
		++toll;
		return;
	}
}
