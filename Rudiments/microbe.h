// BELIEF: The machine is immensly powerful. Fire away!
class microbe{
private:
	///							*** Attributes ***
	double gatherRate; // Includes conversion rate. dx/dt = k.[Qhi-Qlo]
	double shareRate;  // dx/dt = k.[Qhi/Max1 - Qlo/Max2]
	//netStrength = baseStrength + acquiredStrength. Combined attribute of defense, virility. Measure of survival.
	double baseStrength;// Entirely Genetic. Platform for acquiredStrength.
	double acquiredStrength; // Entirely environmental. Possibly negative. Seek to make it a function of food.
	
	/// 						*** Inventory ***
	double foodA;
	double foodB;
	double foodAMax;
	double foodBMax;
public:
	microbe();	// Adam's constructor
	
	microbe(const microbe &parent);		
};
