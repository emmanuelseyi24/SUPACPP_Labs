//Written by Odusina Emmanuel on 20-Nov-2025
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>
 
#include "CustomFunction.h" 
  
using namespace std;    

int main() {
    string inputfile = "/workspaces/SUPACPP_Labs/Exercises/Lab1and2/input2D_float.txt";
    string inputfile_error = "/workspaces/SUPACPP_Labs/Exercises/Lab1and2/error2D_float.txt";

    fstream outputfile("dataout.txt", ios::out);
    fstream outputfile2("fitInfo.txt", ios::out);

    vector<float> datax, datay, magnitude, errorX, errorY, xPowYint;
    vector<int>yint;

    // readData from the customfile
    readData(inputfile, datax, datay, yint, magnitude, xPowYint);
    readDataERR(inputfile_error, errorX, errorY);

    if (datax.empty() || errorX.empty()) return -1;

    cout << inputfile << " and " << inputfile_error <<   " are opened." << endl;

    char again;
    do {
 
    int n;
    howmany();
    cin >> n;

    if (n < 0) {
        cout << " What do you mean? Negative data points ?"<<endl;
        continue;
    }

    if (n > datax.size()) {
        cout << " The data does not contain that many points." << endl;
        cout << "It will use only 5 points in the data " << endl; //<< datax.size() << " points." << endl;
        n = 5;
    }

    cout << " Here are the first " << n << " points: " << endl;
    printData(n, datax, datay, yint, magnitude, xPowYint, outputfile, outputfile2);
    //printDataMag(n, datax, datay, magnitude); //Overload 1
    //printDataPow(n, datax, datay, convY); //Overload 2

vector<float> xSubset(datax.begin(), datax.begin() + n);
vector<float> ySubset(datay.begin(), datay.begin() + n);
vector<float> eSubset(errorX.begin(), errorX.begin() + n);

float slope = 0, intercept = 0, chi2 = 0;
leastSquares(xSubset, ySubset, eSubset, slope, intercept, chi2);

cout << " Least squares fit:  y = " << slope << "x + " << intercept << endl;
cout << " Chi2 = " << chi2 << endl;

// Writes fit functions and other info.
outputfile2 << " --------------------------------------" << endl;
outputfile2 << "# Least squares fit for << " << n << " data points :  y = " << slope << "x + " << intercept << endl;
outputfile2 << "# Chi2 = " << chi2 << endl;
outputfile2 << " --------------------------------------" << endl;

cout << " Do you want to try another number of data points? (y/n): ";
cin >> again;

}while (again == 'y' || again == 'Y');

outputfile.close();
outputfile2.close();

cout << " Check for your files. Bye. " << endl;;

return 0;
}   
