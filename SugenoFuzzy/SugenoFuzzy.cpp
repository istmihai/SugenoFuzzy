// SugenoFuzzy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include <math.h>

using namespace std;
double e, de;
std::map<std::string, double> output
{
    {"PB",1},
    {"PS",0.5},
    {"Z",0},
    {"NS",-0.5},
    {"NB",-1}
};


float trampf(float a,float b,float c,float d,float e) {
    if (e < a)
    {
        return 0;
    }
    else if ((e >= a) && (e <= b))
    {
        return (e - a) / (b - a);
    }
    else if ((e > b) && (e < c))
    {
        return 1;
    }
    else if ((e >= c) && (e <= d))
    {
        return (d - e) / (d - c);
    }
    else
    {
        return 0;
    }
}

float trimf(float a, float b ,float c, float x) {
    if (x <= a) return 0;
    if (x >= a && x <= b) return (x - a) / (b - a);
    if (x >= b && x <= c) return (c - x) / (c - b);
    if (c <= x) return 0;
}

std::map<std::string, float> e_values;
std::map<std::string, float> de_values;

std::string baza_reguli[15][3] =
{ {"NB", "N", "NB"},
{"NB", "Z", "NS"} ,
{"NB", "P", "NS"} ,
{"NS", "N", "NB"} ,
{"NS", "Z", "NS"} ,
{"NS", "P", "NS"} ,
{"Z", "N", "NS"} ,
{"Z", "Z", "Z"} ,
{"Z", "P", "PS"} ,
{"PS", "N", "PS"} ,
{"PS", "Z", "PS"} ,
{"PS", "P", "PB"} ,
{"PB", "N", "PS"} ,
{"PB", "Z", "PB"} ,
{"PB", "P", "PB"}
};

void error_membershipFunctions() {
    e_values.insert({ "NB", trampf(-1, -1, -0.4, -0.01, e) });
    e_values.insert({ "NS", trimf(-0.4, -0.2,0, e) });
    e_values.insert({ "Z", trimf(-0.01,0,0.01,e) });
    e_values.insert({ "PS", trimf(0,0.1,0.3, e) });
    e_values.insert({ "PB", trampf(0.01, 0.2, 1, 1, e) });
}

void derivative_membershipFunctions() {
    de_values.insert({ "N", trimf(-1, -1, 0, de)});
    de_values.insert({ "Z", trimf(-1, 0,1, de) });
    de_values.insert({ "P", trimf(0, 1, 1, de) });

}

double defuzzication() {
    float e_value, de_value, output_value, den_sum = 0, num_sum = 0, intensity;
    for (int i = 0; i < 15; i++) {
        e_value = e_values.at(baza_reguli[i][0]);
        de_value = de_values.at(baza_reguli[i][1]);
        output_value = output.at(baza_reguli[i][2]);
      
        if (e_value > 0 && de_value > 0) {
            cout << baza_reguli[i][1] << endl;
            intensity = std::min(e_value, de_value);
            den_sum += intensity;
            num_sum += intensity * output_value;
        }
    }
    return num_sum / den_sum;
}

int main()
{
    e = -0.2774;
    de = 0.4088;
    error_membershipFunctions();
    derivative_membershipFunctions();
    cout << defuzzication();
  
   

}




