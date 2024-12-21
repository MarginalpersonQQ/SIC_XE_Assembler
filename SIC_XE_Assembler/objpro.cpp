#include "SICXE.h"
using namespace std;
struct pro {
	string loc;
	string obc;
};
pro s[100];
int i = 0;
void obpro() {
	ifstream myfile;
	ofstream writefile;
	string line;
	string proName, Tcount = "";
	int count = 0;
	myfile.open("..\\PASS2.txt");
	writefile.open("..\\object program.txt");
	getline(myfile, line);
	string temp[5] = {};
	istringstream data(line);
	data >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];
	proName = temp[1];
	//輸出H行
	cout << "H" << "^" << proName << "^" << setfill('0') << setw(6) << START_LOC << "^" << setfill('0') << setw(6) << PROGRAM_LEN << endl;
	writefile << "H" << "^" << proName << "^" << setfill('0') << setw(6) << hex << START_LOC << "^" << setfill('0') << setw(6) << hex << PROGRAM_LEN << endl;
	while (getline(myfile, line)) {
		istringstream data(line);
		data >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];
		if (temp[2] == "END") {
			cout << setfill('0') << setw(2) << count << Tcount << endl;
			writefile << setfill('0') << setw(2) << count << Tcount << endl;
			break;
		}
		else if (temp[2] == "RESW" || temp[2] == "RESB") { // 判斷是否要換行
			if (count != 0) {
				cout << count << Tcount << endl;
				writefile << count << Tcount << endl;
				count = 0;
				Tcount = "";
			}
		}
		else if (count <= 30 && temp[4] != "NULL") {
			if (count == 0) {  //一開始輸出T
				cout << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
				writefile << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
			}
			count += (int)temp[4].length() / 2;
			if (count >= 30) {
				count -= (int)temp[4].length() / 2;
				cout << count << Tcount << endl;
				writefile << count << Tcount << endl;
				count = (int)temp[4].length() / 2;
				Tcount = "";
				cout << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
				writefile << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
			}
			Tcount = Tcount + "^" + temp[4];
		}
		if (temp[2] == "+JSUB") { // 計算 relocate並記錄
			s[i].loc = temp[0];
			i++;
		}
	}
	for (int j = 0; j < i; j++) { // 輸出relocate
		cout << "M^" << setfill('0') << setw(6) << stoi(s[j].loc, nullptr, 16) + 1 << "^05" << endl;
		writefile << "M^" << setfill('0') << setw(6) << stoi(s[j].loc, nullptr, 16) + 1 << "^05" << endl;
	}
	cout << "E" << "^" << setfill('0') << setw(6) << START_LOC << endl;
	writefile << "E" << "^" << setfill('0') << setw(6) << hex << START_LOC << endl;
	myfile.close();
	writefile.close();
}