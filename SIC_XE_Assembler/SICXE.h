#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <windows.h>
#include <typeinfo>
#include <format> 
#include <vector>

//������
//pass 1
extern void hashInit();
extern void hashTotxt();
extern bool BuildBTreeAndLoc();
extern bool FindHash(std::string keyword);
extern int FindFormat(std::string keyword);
extern bool FindBTree(std::string symbol);
extern void InsertBTree(std::string symbol, std::string loc);
extern void ShowBTree();
// pass 2
extern int FindOpCode(std::string ins); 
extern bool countOBC();
extern std::string FindBTree_LOC(std::string symbol);
extern void obpro();

//�����ܼ�
extern int rendom_number; //37�i�H�����N���
extern int prime;
extern int LOC;	
extern int START_LOC;
extern int PROGRAM_LEN;
