#include "SICXE.h"
using namespace std;


void pass1() {
	cout << "Start Pass1\n" << endl;
	cout << "Starting Hash...\n" << endl;
	hashInit();
	cout << "\nHash End!!!\n" << endl;
	hashTotxt();
	cout << "Hash Out Put to \"HashTable.csv\"!!!" << "\n" << endl;
	cout << "Start Build Binary Tree...\n" << endl;
	cout << format("Loc\tSymbol\tOpcode\tStatment") << endl;
	BuildBTreeAndLoc();
	cout << "\nBuild Completed!\n" << endl;
	ShowBTree();
	cout << endl;
}

void pass2() {
	cout << "Pass2 To Be Continued..." << endl;
}

int main() {
	//pass 1
	pass1();
	pass2();
	system("pause");
	return 0;
}
