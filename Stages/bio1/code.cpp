#include "microbe.cpp"

using namespace std;

void routine(){
	microbe adam;
	microbe olaf(adam);
	
	adam.report();
	
	gridUnit heaven;
	heaven.microPtr = &adam;
	heaven.temp = &adam;
	
	for(int i=0; i<10; i++){
		olaf.performLife(heaven);
		adam.performLife(heaven);
		adam.report();
	}
	
	olaf.report();
	
	cout << heaven.foodA << TAB << heaven.foodB << endl;
}

int main(){
	srand(time(NULL));
	
	routine();
	
	cout << endl;
	return 0xDEAD;
}
