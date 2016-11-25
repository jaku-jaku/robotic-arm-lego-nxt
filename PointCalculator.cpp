#include<cstdlib>
#include<iostream>
#include <fstream>
#include<cmath>
#include <iomanip>

using namespace std;

int main ()
{
	ofstream lin ("linearFn.txt");
	ofstream quad ("quadraticFn.txt");
	ofstream cub ("cubicFn.txt");
	ofstream sinu ("sine.txt");
	
	int range = 50, interval = 2, minRange = 275, z = -10;
	float cubic = 0, quadratic = 0, linear = 0, sinY = 0;
	float sinAmp = (300-225)/2, sinTrans = 225 + sinAmp;
	
	for (int x = -range; x < range; x += interval){
		float cubic = x*x*x/999.0 - x + minRange;
		float quadratic = x*x/9.0 + minRange; 
		float linear = x;
		float sinY = sinAmp*sin (x)+sinTrans;
		
		lin <<x<<"\t"<<linear <<" "<<z<<"\t\t 0 0"<<endl;
		quad <<x<<"\t"<<quadratic <<z<<"\t\t 0 0"<<endl;
		cub <<x<<"\t"<<cubic <<" "<<z<<"\t\t 0 0"<<endl;
		sinu <<x<<"\t"<<sinY <<" "<<z<<"\t\t 0 0"<<endl;
	}
	
	lin.close();
	quad.close();
	cub.close();
	sinu.close ();
}

