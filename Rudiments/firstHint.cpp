#include <iostream>
#include <ctime>
#include <unistd.h>

#define SIZE 1000
#define arrSize(i) sizeof(i)/sizeof(i[0][0])

using namespace std;

class bacteria{
private:
	double rSign(){
		if(random%2)
			return  1.00;
		else
			return -1.00;
	}
public:
	static int count;
	
	double attack;
	double immunity;
	double lifeSpan;
	double strength;
	
	bacteria(){
		attack = random()%100;
		strength = random()%100;
		immunity = random()%100;
		lifeSpan = random()%100;
	}
	
	bacteria(const bacteria &parent){
		
		this->attack = parent.attack + rSign()*(parent.attack/100.0);
		this->immunity = parent.immunity + rSign()*(parent.immunity/100.0);
		this->lifeSpan = parent.lifeSpan + rSign()*(parent.lifeSpan/100.0);
		this->strength = parent.strength + rSign()*(parent.strength/100.0);
	}
}

class calamity{
public:
	double attack;
	double immunity;
	double lifeSpan;
	double strength;
	
	calamity(double a, double b, double c, double d){
		attack = a;
		immunity = b;
		lifeSpan = c;
		strength = d;
	}
}
	
bacteria *godEye[SIZE];
int bacteria::count = 0;

void display(){
	system("clear");
	for(int i=0; i<LENGTH; i++){
		for(int j=0; j<WIDTH; j++)
			cout << bacteriaGrid[i][j];
		cout << endl;
	}
}

void nextTurn(){
	for(int i=0; i<bacteria::count && i<SIZE; i++){
		if(godEye[i]->lifeSpan <= 0)
			delete godEye[i];
		else
			godEye[i]->lifeSpan -= 10;
	}
}

int main(){
	srand(time(NULL));
	// operations
}
