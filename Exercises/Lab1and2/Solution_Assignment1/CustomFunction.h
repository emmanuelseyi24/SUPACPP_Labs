#ifndef CUSTOMFUNCTION_H
#define CUSTOMFUNCTION_H
     
#include <vector>
#include <string>
#include <iostream> 
    
void howmany();                    
float mag(float x, float y);       

void readData(const std::string &file,
              std::vector<float> &x,
              std::vector<float> &y,
              std::vector<int> &yint,
              std::vector<float> &magnitude,
              std::vector<float> &xPowYint);

void readDataERR(const std::string &file,
              std::vector<float> &x,
              std::vector<float> &y);

//all
void printData(int n,
               const std::vector<float> &x,
               const std::vector<float> &y,
               const std::vector<int> &yint,
               const std::vector<float> &mag,
               const std::vector<float> &xPowYint,
               std::ostream &out, std::ostream &out2);


/*
//magnitude               
void printDataMag(int n,
               const std::vector<float> &x,
               const std::vector<float> &y,
               const std::vector<float> &magnitude);


//power               
void printDataPow(int n,
               const std::vector<float> &x,
               const std::vector<float> &y,
               const std::vector<int> &convY,
               const std::vector<float> &xPowYint);
*/


//least square
void leastSquares(const std::vector<float> &x,
                  const std::vector<float> &y,
                  const std::vector<float> &e,
                  float &m, float &b, float &chi2);

#endif

