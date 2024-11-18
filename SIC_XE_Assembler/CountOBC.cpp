#include "SICXE.h"
using namespace std;

bool countOBC() {
	ifstream myfile;
	myfile.open("..\\PASS1.txt");
	string instruction;
	while (getline(myfile, instruction)){
		if (!instruction.empty() && instruction.back() == '\n') {
			instruction.pop_back();
		}
		vector<string> split_ins;
		istringstream split_string(instruction);
		for (int i = 0; i < 5; i++) {
			string temp;
			split_string >> temp;
			if (temp == "") {
				cout << i << endl;
			}
			split_ins.push_back(temp);
		}
	}
	myfile.close();
	return true;
}
