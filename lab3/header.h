#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

vector<string> fragmentationAND(string);

vector<string> fragmentationAND2(string);

string checkAreNeighboursSDNF(string, string);

vector<string> fragmentationOR(string);

string gluingSDNF(string);

string reverse(string);

bool find(vector<string>, string);

bool checkExcess(vector<string>, int);

string toTDF(string);

string checkAreNeighboursSKNF(string, string);

string gluingSKNF(string);

bool checkExcess2(vector<string>, int);

string toTKF(string);

bool isInclude(string, string);

string MCClassSDNF(string, string);

bool isInclude2(string, string);

string MCClassSKNF(string, string);

vector<vector<int>> makeDiagram(int);

int GrayCode(unsigned int);

string twoten(int, int);

bool isInclude3(string, string);

string FindTDF(string, string);

vector<string> normal(vector<string>);

string WeichCarno(string, int);

bool isInclude4(string, string);

string FindTKF(string, string);

vector<string> normal2(vector<string>);

string WeichCarno2(string, int);

#endif
