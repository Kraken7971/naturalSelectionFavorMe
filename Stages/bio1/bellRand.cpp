double bellRandom(int i){
	double r = ((double)(random()) / RAND_MAX) * 5.0;
	double p = ((double)(random()) / RAND_MAX) * ((double)(random()) / RAND_MAX) * 5.0;
	
	if(p > r)
		return r;
	else if(i >= 5)
		return r/10.0;
	else
		return bellRandom(i+1);
}

double ran(int i){
	int sign = random() & 1;
	if(sign == 0)
		sign = -1;
	else
		sign = 1;
	return sign*bellRandom(i);
}
