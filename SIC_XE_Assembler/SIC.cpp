#include "SICXE.h"
using namespace std;

int main() {
	cout << "Starting Hash...\n" << endl;
	hashInit();
	cout << "Hash End!!!\n" << endl;
	hashTotxt();
	cout << "Hash Out Put to \"HashTable.csv\"!!!" << "\n"  << endl;
	cout << "Start Build Binary Tree...\n" << endl;
	cout << format("Loc\tSymbol\tOpcode\tStatment") << endl;
	BuildBTreeAndLoc();
	cout << "Build Completed." << endl;
	ShowBTree();
	return 0;
}