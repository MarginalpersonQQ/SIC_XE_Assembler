#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <windows.h>
#include <typeinfo>

//������
extern void hashInit();
extern void hashTotxt();
extern void BuildBT();
extern bool FindHash(std::string keyword);
extern int FindOpCode();
extern int FindFormat(std::string& sour);
extern bool FindBTree(std::string symbol);
extern void InsertBTree(string symbol, string loc);
//�����ܼ�
extern int rendom_number; //37�i�H�����N���
extern int prime;
extern int LOC;