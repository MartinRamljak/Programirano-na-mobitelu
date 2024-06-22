#include <iostream>
#include <math.h>

using namespace std;

double BestOfTwoDiesAvg(int n, int& nOriginal)
{
	
	if(!n)
		return 0;
	if(n!=nOriginal)
		return n*((n-1)*2+1) + BestOfTwoDiesAvg(n-1,nOriginal);
	return (n*((n-1)*2+1) + BestOfTwoDiesAvg(n-1,nOriginal))/pow(nOriginal,2);
	
}

int main(int argc, char *argv[])
{
	int n=0;
	cout<<"Koliko strana ima promatrana kocka:";
	cin>>n;
	cout<<"Koliko kocaka se baca:";
	cin>>m;
	cout<<"Prosjecna ocekivana vrijednost bacanja dvaju "<<n<<"-stranih kocke i uzimanja veceg rezultata je: "<<endl<<BestOfTwoDiesAvg(n,n);
}