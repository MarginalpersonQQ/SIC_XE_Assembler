#include "SICXE.h"
using namespace std;
int LOC = 0x0;

bool BuildBTreeAndLoc() {
	ofstream writefile;
	writefile.open("..\\PASS1.txt");
	string line;
	ifstream myfile;
	myfile.open("..\\SICXE.txt");
	string stemp[3] = {};
	istringstream data(line);
	data >> stemp[0] >> stemp[1] >> stemp[2];
	
	if (stemp[1] != "START") {
		LOC = 0x0;
	}
	stringstream ss;

	while (getline(myfile, line))
	{	
		if (line.length() <= 1) {
			continue;
		}
		string temp[3] = {};
		istringstream data(line);
		data >> temp[0] >> temp[1] >> temp[2];
		
		if (temp[1] == "START") {
			cout << "\t" << temp[0] << "\t" << temp[1] << "\t" << temp[2] << endl;
			writefile << format("NULL {} {} {}\n", temp[0], temp[1], temp[2]);
			LOC = stoi(temp[2], nullptr, 16);
			string x = format("{:#x}", LOC);
			InsertBTree(temp[0], x);
			continue;
		}
		if (FindHash(temp[0]) || temp[0] == "BASE" || temp[0] == "END") {
			temp[2] = temp[1];
			temp[1] = temp[0];
			temp[0] = " ";
		}
		
		if (temp[1] != "END") {
			if (temp[0] != ".") {	
				if (temp[0] != " ") {
					if (FindBTree(temp[0])) {
						cout << "Duplicate Symbol Error." << temp[0] << endl;
						return false;
					}
					else {
						string x = format("{:#x}", LOC);
						InsertBTree(temp[0], x);
					}
				}
				if (temp[1] != "BASE") {
					cout << hex << LOC << "\t" << temp[0] << "\t" << temp[1] << "\t" << temp[2] << endl;
					if (temp[0] == " ") {
						temp[0] = "NULL";
					}
					if (temp[1] == "RSUB") {
						temp[2] = "NULL";
					}
					writefile << format("{:#X} {} {} {}\n", LOC, temp[0], temp[1], temp[2]);
				}
				if (FindHash(temp[1])){
					int format = FindFormat(temp[1]);
					LOC += format;
				}
				else if (temp[1] == "WORD") {
					LOC += 0x3;
				}	
				else if (temp[1] == "RESW") {
					int x = stoi(temp[2], nullptr, 10);
					LOC += (3 * x);
				}
				else if (temp[1] == "RESB") {
					int x = stoi(temp[2], nullptr, 10);
					LOC += x;
				}
				else if (temp[1] == "BYTE") {
					if (temp[2][0] == 'x') {
						string command = temp[2].substr(1);
						LOC += (int)((command.length() - 2) / 2);
					}
					else if (temp[2][0] == 'c') {
						string command = temp[2].substr(1);
						LOC += (int)(command.length() - 2);
					}
				}
				else if (temp[1] == "BASE") {
					cout << "\t\t" << temp[1] << "\t" << temp[2] << endl;
					writefile << format("NULL NULL {} {}\n", temp[1], temp[2]);
				}
				else {
					cout << "error command " << temp[1] << endl;
				}
				
			}
		}
		else{
			cout << "\t" << temp[0] << "\t" << temp[1] << "\t" << temp[2] << endl;
			if (temp[0] == " ") {
				temp[0] = "NULL";
			}
			writefile << format("NULL {} {} {}\n", temp[0], temp[1], temp[2]);
			break;
		}
	}
	myfile.close();
	writefile.close();
	return true;
}