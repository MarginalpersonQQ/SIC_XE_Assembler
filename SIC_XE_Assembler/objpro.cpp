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
	string proName,Tcount  = "";
	int count = 0;
	myfile.open("..\\PASS2.txt");
	writefile.open("..\\object program.txt");
	getline(myfile, line);
	string temp[5] = {};
	istringstream data(line);
	data >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];
	proName = temp[1];
	//��XH��
	cout << "H" << "^" << proName << "^" << setfill('0') << setw(6) << START_LOC << "^" << setfill('0') << setw(6) << PROGRAM_LEN << endl;
	writefile << "H" << "^" << proName << "^" << setfill('0') << setw(6) << hex << START_LOC << "^" << setfill('0') << setw(6) <<hex<< PROGRAM_LEN << endl;
	while (getline(myfile, line))
	{
		istringstream data(line);
		data >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];
		if (temp[2] == "END") {
			cout << setfill('0') << setw(2) << count << Tcount << endl;
			writefile << setfill('0') << setw(2) << count << Tcount << endl;
			break;
		}
		if (count <= 27 && temp[4] != "NULL") {
			if (count == 0) {  //�@�}�l��XT
				cout << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
				writefile << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
				Tcount = Tcount + "^" + temp[4];
				count += (int)temp[4].length() / 2;
			}
			else if (count == 27 && temp[4].length() / 2 == 4) {  //format 4 ���ɪ��׬�27 + 4 > 30
				cout << count << Tcount << endl;
				writefile << count << Tcount << endl;
				count = 4;
				Tcount = "^" + temp[4];
				cout << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^"; //���s���@��
				writefile << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
			}
			else { // format 3
				Tcount = Tcount + "^" + temp[4];
				count += (int)temp[4].length() / 2;
			}
		}
		else if (temp[2] == "RESW" || temp[2] == "RESB") { // �P�_�O�_�n����
			if (count != 0) {
				cout << count << Tcount << endl;
				writefile << count << Tcount << endl;
				count = 0;
				Tcount = "";
			}
		}
		else if (count > 27) { // �W�L 30 ���B�z�覡
			if (count == 28 && ((temp[4].length() / 2 == 2) || (temp[4].length() / 2 == 1))) { //format 4
				Tcount = Tcount + "^" + temp[4];
				count += (int)temp[4].length() / 2;
			}
			else if (count == 29 && ((temp[4].length() / 2 == 1))) {
				Tcount = Tcount + "^" + temp[4];
				count += (int)temp[4].length() / 2;
			}
			else {
				cout << count << Tcount << endl;
				writefile << count << Tcount << endl;
				count = (int)temp[4].length() / 2;
				Tcount = "^" + temp[4];
			}
			cout << "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
			writefile<< "T^" << setfill('0') << setw(6) << stoi(temp[0], nullptr, 16) << "^";
		}
		if (temp[4].length() == 8) { // �p�� relocate�ðO��
			s[i].loc = temp[0];
			i++;
		}
	}
	for (int j = 0 ; j < i ; j++) { // ��Xrelocate
		cout << "M^" << setfill('0') << setw(6) << stoi(s[j].loc, nullptr, 16) +1 << "^05" << endl;
		writefile << "M^" << setfill('0') << setw(6) << stoi(s[j].loc, nullptr, 16) + 1 << "^05" << endl;
	}
	cout << "E" << "^" << setfill('0') << setw(6) << START_LOC << endl;
	writefile << "E" << "^" << setfill('0') << setw(6) << START_LOC << endl;
	myfile.close();
	writefile.close();
}