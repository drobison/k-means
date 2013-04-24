// Author	David Robison
// Date		4/20/2013

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

ifstream infile;
ofstream outfile;

double x[1000], y[1000], assignedto[1000];
double centroidx[10], centroidy[10];
double oldcentroidx[10], oldcentroidy[10];
int k = 2;				// k = number of centroids
int centroidcount[10];
int dataCount = 0;

double calculateDistance(double x, double y, double x1, double y1);
void assignCentroid(double x, double y, int point);
void calculateNewCentroid();

int main()
{
	string input = "input.txt";
	string output = "output.txt";

	dataCount = 0;

	outfile.open(output.c_str());

	// Read in input.
	infile.open(input.c_str());
	if (!infile)
	{
		cout << "Unable to open input."<< endl;
	}
	while(!infile.eof())		
	{
		infile >> x[dataCount] >> y[dataCount];
		dataCount++;
	}

	infile.close();

	// Chose initial centroids.  Hard coding for testing but can/should be random per requirements.
	for( int i=0; i<k; i++)
	{
		centroidx[i] = x[i];
		centroidy[i] = y[i];

		// For debugging
		cout << "Centroid " << i << ": [" << centroidx[i] << ", " << centroidy[i] << "]" << endl;
		outfile << "Centroid " << i << ": [" << centroidx[i] << ", " << centroidy[i] << "]" << endl;
	}

	// Assign points to centroids based on closest mean
	for( int i=0; i<dataCount; i++)
	{
		assignCentroid( x[i], y[i], i );
	}

	//for( int i=0; i<k; i++)
	//{
	//	cout << centroidcount[i] << endl;
	//}
	// Open output

	for( int i=0; i<4; i++)
	{
		calculateNewCentroid();
		for( int i=0; i<dataCount; i++)
		{
			assignCentroid( x[i], y[i], i );
		}
	}

	outfile.close();

	cin >> x[0];
}

double calculateDistance(double x, double y, double x1, double y1)
{
	double part1 = (x - x1) * (x - x1);
	double part2 = (y - y1) * (y - y1);
	double answer = sqrt(part1+part2);

	return answer;
}

void assignCentroid(double x, double y, int point)
{
	double smallest = 999;
	int chosenCentroid = 999;

	for( int i=0; i<k; i++)
	{
		double distanceToCentroid = calculateDistance(x, y, centroidx[i], centroidy[i]);
		
		if( distanceToCentroid < smallest )
		{
			smallest = distanceToCentroid;
			chosenCentroid = i;
		}
	}
	assignedto[point] = chosenCentroid;
	centroidcount[chosenCentroid]++;
}

void calculateNewCentroid()
{
	for( int i=0; i<k; i++)
	{
		cout << endl;
		outfile << endl;

		oldcentroidx[i] = centroidx[i];
		oldcentroidy[i] = centroidy[i];

		double xsum = 0;
		double ysum = 0;
		double count = 0;

		for( int j=0; j < dataCount; j++)
		{
			if(assignedto[j] == i)
			{
				xsum += x[j];
				ysum += y[j];
				count++;
			}
		}
		centroidx[i] = xsum / count;
		centroidy[i] = ysum / count;

		double movement = calculateDistance(oldcentroidx[i], oldcentroidy[i], centroidx[i], centroidy[i]);

		cout << "Centroid " << i << ": [" << centroidx[i] << ", " << centroidy[i] << "]" << endl;
		outfile << "Centroid " << i << ": [" << centroidx[i] << ", " << centroidy[i] << "]" << endl;
		cout << "Centroid moved " << movement << endl;
	}
}