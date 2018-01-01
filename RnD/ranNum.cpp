#include <iostream>
#include <ctime>

#define	BELL_ITR int(bellRandom(0))
#define LINEAR_ITR int(((double)(random()) / RAND_MAX)*10.0)
#define TAB '\t'

using namespace std;

double bellRandom(int i){
	double r = ((double)(random()) / RAND_MAX)*10;
	double p = ((double)(random()) / RAND_MAX)*((double)(random()) / RAND_MAX)*10;
	
	if(p > r)
		return r;
	else if(i >= 5)
		return r/10.0;
	else
		return bellRandom(i+1);
}
// ------------------------------------------------- //
int main(){
	srand(time(NULL));
	int statArr[11] = {0};

	for(int i=0; i<99999; i++)
		statArr[BELL_ITR]++;

	for(int i=0; i < 11; i++){
		cout << i << TAB << double(statArr[i])/99999.99 << "%" << endl;
	}
	cout << endl;
}

