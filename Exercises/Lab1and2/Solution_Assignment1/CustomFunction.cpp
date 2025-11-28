#include "CustomFunction.h"
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
 
void howmany() {
    cout << "How many data points do you want to print? ";
}

//magnitude of two points function
float mag(float x, float y) {
    return sqrt(x*x + y*y);
}

//converts float to integer function
int conv(float y) {
    return static_cast<int>(std::round(y)); 
}

//recursive power function
float recurs(float x, int yint) {
        if (yint == 0) return 1.0f;
        if (yint == 1) return x;
    return x * recurs(x, yint - 1);
}

// read-in data funtion
void readData(const std::string &file,
              std::vector<float> &x,
              std::vector<float> &y,
              std::vector<int> &yint,
              std::vector<float> &magnitude,
            std::vector<float> &xpowYint)
{
    ifstream datain(file);
    if (!datain.is_open()) {
        cout << "Cannot open " << file << endl;
        return;
    }

    string line;
    while (getline(datain, line)) {
        for (char &c : line)
            if (c == ',') c = ' ';

        stringstream ss(line);

        float a, b;
        if (ss >> a >> b) {
            x.push_back(a);
            y.push_back(b);
            magnitude.push_back(mag(a, b));
            yint.push_back(conv(b));
            xpowYint.push_back(recurs(a,conv(b)));
        }
    }
}
//read-in error data function
void readDataERR(const std::string &file,
              std::vector<float> &x,
              std::vector<float> &y)
{
    ifstream datain(file);
    if (!datain.is_open()) {
        cout << "Cannot open " << file << endl;
        return;
    }

    string line;
    while (getline(datain, line)) {
        for (char &c : line)
            if (c == ',') c = ' ';

        stringstream ss(line);

        float a, b;
        if (ss >> a >> b) {
            x.push_back(a);
            y.push_back(b);
        }
    }
}

//Print all
void printData(int n,
               const std::vector<float> &x,
               const std::vector<float> &y,
               const std::vector<int> &yint,
               const std::vector<float> &magnitude,
               const std::vector<float> &xPowYint,
               std::ostream &out, std::ostream &out2)
{
    for (int i = 0; i < n; i++) {
        cout << " Points " << x[i] << " and " << y[i]
             << " has magnitude " << magnitude[i] << ". Y to a whole number = " << yint[i] << ", and recursive power x^y = " << xPowYint[i] << "."<< endl;

        out << x[i] << " " << y[i] << "   " << magnitude[i] << "   " << yint[i] <<"   " << xPowYint[i] <<endl;
        // Writes fit functions and other info.

    }  
}



/* OVERLOAD NOT NEEDED SINCE ALL THE DATA ARE IN A SINGLE FILE. CHECK README
//magnitude overload
void printDataMag(int n,
               const std::vector<float> &x,
               const std::vector<float> &y,
               const std::vector<float> &magnitude)
{
    for (int i = 0; i < n; i++) {
        cout << " The magnitude of the data point in this row: " << magnitude[i] << endl;
    }
}

//power overload
void printDataPow(int n,
               const std::vector<float> &x,
               const std::vector<float> &y,
               const std::vector<int> &convY,
               const std::vector<float> &xPowYint))
{
    for (int i = 0; i < n; i++) {
           cout  << " The data point " << y[i] << " in whole number = " <<  convY[i] << " and the recursive power with x = " << xPowYint <<  endl;
           }
}
*/



//least square function
void leastSquares(const std::vector<float> &x,
                  const std::vector<float> &y,
                  const std::vector<float> &errors,
                  float &m, float &b, float &chiSquare)
{
    int n = x.size();
    if (n == 0) {
        m = 0;
        b = 0;
        chiSquare = 0;
        return;
    }

    //Parammeters
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumW = 0;

    for (int i = 0; i < n; i++) {

        float w = 1.0; //introducing a weight to be replaced by the error data
        if (i < errors.size() && errors[i] != 0) w = 1.0 / (errors[i] * errors[i]);

        sumW += w;
        sumX  += w * x[i];
        sumY  += w * y[i];
        sumXY += w * x[i] * y[i];
        sumX2 += w * x[i] * x[i];
    }
    
    // Avoid dividing by zero
    float avoidzero = sumW * sumX2 - (sumX * sumX);

    if (avoidzero == 0) {m = 0; b = sumY / sumW;return;}  

    m = (sumW * sumXY - sumX * sumY) / avoidzero;
    b = (sumY * sumX2 - sumX * sumXY) / avoidzero;

// chi-square function
    chiSquare = 0;
    for (int i = 0; i < n; i++) {
        float diff = y[i] - (m * x[i] + b);
        float sigma2 = 1.0;
        if (i < errors.size() && errors[i] != 0) sigma2 = errors[i] * errors[i];
        chiSquare += (diff * diff) / sigma2;
    }
}
