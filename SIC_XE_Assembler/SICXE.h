#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <windows.h>
#include <typeinfo>

//办ㄧ计
extern void hashInit();
extern void hashTotxt();
extern void BuildBT();
extern bool FindHash(std::string keyword);
extern int FindOpCode();
extern int FindFormat(std::string& sour);
extern bool FindBTree(std::string symbol);
extern void InsertBTree(string symbol, string loc);
//办跑计
extern int rendom_number; //37ヴ種借计
extern int prime;
extern int LOC;