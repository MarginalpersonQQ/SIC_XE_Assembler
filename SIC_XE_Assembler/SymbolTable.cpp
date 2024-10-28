#include "SICXE.h"
using namespace std;
int LOC = 0x0;

void BuildBT() {
	
	string line;
	ifstream myfile;
	myfile.open("..\\SICXE.txt");
	string stemp[3] = {};
	istringstream data(line);
	data >> stemp[0] >> stemp[1] >> stemp[2];
	
	if (stemp[1] == "START") {
		LOC = stoi(stemp[2], nullptr, 16);
	}
	else {
		LOC = 0x0;
	}
	stringstream ss;
	ss << std::hex << LOC; // 將數字轉為 16 進位格式
	InsertBTree(stemp[0], ss.str());
	while (getline(myfile, line))
	{
		string temp[3] = {};
		istringstream data(line);
		data >> temp[0] >> temp[1] >> temp[2];
		if (FindHash(temp[0])){
			temp[2] = temp[1];
			temp[1] = temp[0];
			temp[0] = " ";
		}
		
		if (temp[1] != "END") {
			if (temp[0] != ".") {
				if (temp[0] != " ") {
					if (FindBTree(temp[0])) {
						cout << "Duplicate Symbol Error." << endl;
					} 
					else {
						ss << std::hex << LOC; // 將數字轉為 16 進位格式
						InsertBTree(temp[0], ss.str());
					}
				}
			}
		}
		else {

			//LOC += FindFormat(temp[1]);
			break;
		}
		cout << LOC << "\t" << temp[0] << "\t" << temp[1] << "\t" << temp[2] << endl;
	}
}