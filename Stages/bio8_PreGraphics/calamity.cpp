extern int genSys::genEnd;

double randFactor = 0.1;

class meteor;

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
	
//	if(meteor[microbe->defaultY][microbe->defaultX])
//		microbe.weakness += microbe.meteorImpactEffect;
}

class meteor{
public:
	bool isActive;
	
	meteor(){
		meteor::isActive = true;
	}
	
	~meteor(){
	}
	
	void die(){
		isActive = false;
	}
};
