extern int genSys::genEnd;

double randFactor = 0.2;


void calamityCheck(microbe &microbe, int& toll){
	// Random accidental death
	double popFactor = randFactor * (double)(genSys::genEnd/10000);
	if((double)random()/RAND_MAX < popFactor){
		microbe.die();
		++toll;
		return;
	}
	
	// Death due to environmental constraint.
	if(microbe.baseStrength + microbe.weakness < world[microbe.defaultY][microbe.defaultX].conditions){
		microbe.die();
		++toll;
		return;
	}
}
