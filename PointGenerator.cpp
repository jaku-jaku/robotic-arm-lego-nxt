#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>


using namespace std;

void writePoints(ofstream& output, int x0, int y0, int x1, int y1);

int main()
{
	ofstream outputFile;
	int x0;
	int y0;
	int x1; 
	int y1;
	int rise;
	int run;
	double b;
	double slope;
	outputFile.open("test.txt");
	cout << "Your intial x ";
	cin >> x0;
	cout << "Your initial y";
	cin >> y0;
	
	cout << "Your final x: ";
	cin >> x1;
	cout << "Your final y: ";
	cin >> y1;
	
	rise = y1-y0;
	run = x1 - x0;
	slope = rise/run;
	b = y0 - slope * x0;
	
	for (int i = 0; i < (x1 - x0); i += 5)
	{
		outputFile << x0 + i
					<< " " << (slope * (x0 + i) + b)
					<< " " << -20
					<< " " << 0 << endl;
					
	}
	cout << "Your inputs are: " << x1 - x0;
	outputFile.close();
}

void writePoints(ofstream& output, int x0, int y0, int x1, int y1)
{
	int rise;
	int run;
	int slope;
	int b;
	rise = y1-y0;
	run = x1 - x0;
	slope = rise/run;
	b = y0 - slope * x0;
	
	for (int i = 0; i < (x1 - x0); i++)
	{
		output << x0 + i
					<< " " << (slope * (x0 + i) + b)
					<< " " << -5
					<< " " << 0 << endl;
					
	}
	cout << "Your inputs are: " << x1 - x0;
	
}
