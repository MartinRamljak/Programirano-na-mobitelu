#include <iostream>
#include <math.h>

using namespace std;

double BestOfMDiesNSidesAvg(int n, int& nOg, int m)
{
	if(!n)
		return 0;
	else if(n!=nOg)
		return n*(pow(n,m) - pow(n-1,m)) + BestOfMDiesNSidesAvg(n-1,nOg,m);
	return (n*(pow(n,m) - pow(n-1,m)) + BestOfMDiesNSidesAvg(n-1,nOg,m))/pow(nOg,m);
}

int main(int argc, char *argv[])
{
	int n=0,m=2;
	cout<<"Koliko strana ima promatrana kocka:";
	cin>>n;
	cout<<"Koliko kocaka se baca:";
	cin>>m;
	cout<<"Prosjecna ocekivana vrijednost bacanja "<<m<<" "<<n<<"-stranih kocki i uzimanja veceg rezultata je: "<<endl<<BestOfMDiesNSidesAvg(n,n,m)<<endl<<"U usporedbi sa bacanjem jedne takve kocke gdje je ta vrijednost "<<(double)n*(n+1)/(2*n);
	return 0;
}