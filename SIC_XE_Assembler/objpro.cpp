#include "SICXE.h"
using namespace std;
struct pro {
	string loc;
	string obc;
};
//321646
//654654
pro s[100];
int i = 0;
void obpro() {
	ifstream myfile;
	string line;
	string proName,Tcount  = "";
	int count = 0;
	myfile.open("..\\PASS2.txt");
	getline(myfile, line);
	string temp[5] = {};
	istringstream data(line);
	data >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];
	proName = temp[1];
	cout << "H" << "^" << proName << "^" << setfill('0') << setw(6) << START_LO << "^" << setfill('0') << setw(6) << PROGRAM_LEN << endl;
	while (getline(myfile, line))
	{
		istringstream data(line);
		data >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];
		if (temp[2] == "END") {
			cout << setfill('0') << setw(2) << count << Tcount << endl;
			break;
		}

		if (count <= 27 && temp[4] != "NULL") {
			if (count == 0) {
				cout << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
				Tcount = Tcount + "^" + temp[4];
				count += temp[4].length() / 2;
			}
			else if (count == 27 && ((temp[4].length() / 2 == 4))) {
				cout << count << Tcount << endl;
				count = 4;
				Tcount = "^" + temp[4];
				cout << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
			}
			else {
				Tcount = Tcount + "^" + temp[4];
				count += temp[4].length() / 2;
			}
		}
		else if (temp[2] == "RESW" || temp[2] == "RESB") {
			if (count != 0) {
				cout << count << Tcount << endl;
				count = 0;
				Tcount = "";
			}
		}
		else if (count > 27) {
			if (count == 28 && ((temp[4].length() / 2 == 2))) {
				Tcount = Tcount + "^" + temp[4];
				count += temp[4].length() / 2;
			}
			else if (count == 28 && ((temp[4].length() / 2 == 1))) {
				Tcount = Tcount + "^" + temp[4];
				count += temp[4].length() / 2;
			}
			else if (count == 29 && ((temp[4].length() / 2 == 1))) {
				Tcount = Tcount + "^" + temp[4];
				count += temp[4].length() / 2;
			}
			else {
				cout << count << Tcount << endl;
				count = temp[4].length() / 2;
				Tcount = "^" + temp[4];
			}
			cout << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
		}
		if (temp[4].length() == 8) {
			s[i].loc = temp[0];
			i++;
		}
	}
	for (int j = 0 ; j < i ; j++) {
		cout << "M^" << setfill('0') << setw(6) << stoi(s[j].loc, nullptr, 16) +1<< "^05" << endl;
	}
	cout << "E" << "^" << setfill('0') << setw(6) << START_LO << endl;
	myfile.close();
}