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
	cout << "START LOC:" << hex << START_LOC << "\tPROGRAM LENGTH:" << hex << PROGRAM_LEN << endl;
}

void pass2() {
	cout << "=========================================" << endl;
	cout << "Start Pass 2\n" << endl;
	if (countOBC()) {
		cout << "OBC is counted." << endl;
	}
	else {
		cout << "\nOBC is not counted\n" << endl;
	}
	cout << "\nPass 2 completed!!" << endl;
	//object program
	cout << "==========================================" << endl;
	cout << "Start Object Program\n" << endl;
	obpro();
	cout << "\nObject Program completed!!" << endl;
}

int main() {
	//pass 1	
	pass1();
	system("pause");
	//pass 2
	pass2();
	system("pause");
	//Object Program
	return 0;
}
