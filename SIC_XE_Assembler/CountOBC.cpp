#include "SICXE.h"
using namespace std;

string Base = "0";
string A = "0", B = "3", X = "1", S = "4", T = "5", F = "6", L = "2", PC = "8", SW = "9";
string findRegister(char word) {
	switch (word) {
		case 'A':
			return A;
			break;
		case 'B':
			return B;
			break;
		case 'X':
			return X;
			break;
		case 'S':
			return S;
			break;
		case 'T':
			return T;
			break;
		case 'F':
			return F;
			break;
		case 'L':
			return L;
			break;
		case 'PC':
			return PC;
			break;
		case 'SW':
			return SW;
			break;
		default:
			return 0;
	}
}


bool countOBC() {
	ifstream myfile;
	ofstream writefile;
	myfile.open("..\\PASS1.txt");
	writefile.open("..\\PASS2.txt");
	string instruction;
	string BASE;
	while (getline(myfile, instruction)){
		int status = 0;
		int x = 0, b = 0, p = 0, e = 0;
		int opcode = -1;
		int format;
		bool e_on_flag = false;
		bool load_base_flag = false;
		if (!instruction.empty() && instruction.back() == '\n'){
			instruction.pop_back();
		}
		vector<string> split_ins;
		istringstream split_string(instruction);
		for (int i = 0; i < 4; i++){
			string temp;
			split_string >> temp;
			split_ins.push_back(temp);	
		}
		// split_ins => LOC,SYMBOL,OP,INS
		if (split_ins[2] != "END") {
			if (split_ins[2] != "BASE") {
				if (split_ins[2] != "RESW" and split_ins[2] != "RESB") {
					if (split_ins[2] != "START") {
						if (split_ins[2] == "WORD") {
							int temp = stoi(split_ins[3]);
							cout << std::format("{}\t{}\t{}\t{}\t{:x}", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp) << endl;
							writefile << std::format("{} {} {} {} {:x}\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp);
						}
						else if (split_ins[2] == "BYTE") {
							string temp = "";
							if (split_ins[3][0] == 'c') {
								for (size_t i = 1; i < split_ins[3].length(); i++) {
									if (split_ins[3][i] != '\'') {
										std::stringstream ss;
										ss << std::hex << std::uppercase << int(split_ins[3][i]);
										temp += ss.str();
									}
								}
							}
							else if(split_ins[3][0] == 'x'){
								for (int i = 1; i < split_ins[3].length(); i++) {
									if (split_ins[3][i] != '\'') {
										temp += split_ins[3][i];
									}
								}
							}
							cout << std::format("{}\t{}\t{}\t{}\t{}", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp) << endl;
							writefile << std::format("{} {} {} {} {}\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp);
						}
						else if (split_ins[2] == "RSUB") {
							string temp = "4f0000";
							cout << std::format("{}\t{}\t{}\t{}\t{}", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp) << endl;
							writefile << std::format("{} {} {} {} {}\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp);
						}
						else {
							opcode = FindOpCode(split_ins[2]);
							format = FindFormat(split_ins[2]);
							if (format == 2) {
								string temp = "";
								stringstream ss;
								if (split_ins[3].length() > 1) {
									string a = findRegister(split_ins[3][0]);
									string b = findRegister(split_ins[3][2]);
									temp = a + b;
								}
								else{
									string a = findRegister(split_ins[3][0]);
									temp = a + "0";
								}
								ss << hex <<opcode;
								temp = ss.str() + temp;
								cout << std::format("{}\t{}\t{}\t{}\t{}", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp) << endl;
								writefile << std::format("{} {} {} {} {}\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp);
							}
							else if (split_ins[2][0] == '+') {// format 4
								string no_sign_ins;
								stringstream ss;
								string temp;
								int xbpe = 1;
								//§PÂ_ni
								if (split_ins[3][0] == '#') {
									status = 1;
									no_sign_ins = split_ins[3].substr(1);
								}
								else if (split_ins[3][0] == '@') {
									status = 2;
									no_sign_ins = split_ins[3].substr(1);
								}
								else {
									status = 3;
									no_sign_ins = split_ins[3];
								}
								//§PÂ_x
								if (split_ins[3][split_ins[3].length() - 1] == 'X') {
									xbpe += 8;
									no_sign_ins = no_sign_ins.substr(0, no_sign_ins.length() - 2);
								}
								opcode += status;
								ss << hex << opcode << xbpe;
								if (!FindBTree(no_sign_ins)) {
									try {
										stringstream aa;
										aa << hex << stoi(no_sign_ins);
										string temp2 = aa.str();
										temp = temp + ss.str() + "0" + temp2;
									}
									catch (...) { // ¿ù»~¾Þ§@½X
										cout << "\n---------------------------------------------------\n"
											<< "\tError : Error Operand!!\n\t\t" << no_sign_ins
											<< "\n---------------------------------------------------\n" << endl;
										break;
									}
								}
								else {
									string temp2 = FindBTree_LOC(no_sign_ins);
									temp2 = temp2.substr(2);
									temp = temp + ss.str() + "0" + temp2;
									
								}
								cout << std::format("{}\t{}\t{}\t{}\t{}", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp) << endl;
								writefile << std::format("{} {} {} {} {}\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp);
							}
							// split_ins => LOC,SYMBOL,OP,INS
							else {//format 3
								string no_sign_ins;
								stringstream ss;
								stringstream aa;
								string temp;
								int xbpe = 0;
								int disp;
								//§PÂ_ni
								if (split_ins[3][0] == '#') {
									status = 1;
									no_sign_ins = split_ins[3].substr(1);
								}
								else if (split_ins[3][0] == '@') {
									status = 2;
									no_sign_ins = split_ins[3].substr(1);
								}
								else {
									status = 3;
									no_sign_ins = split_ins[3];
								}
								//§PÂ_x
								if (split_ins[3][split_ins[3].length() - 1] == 'X') {
									xbpe += 8;
									no_sign_ins = no_sign_ins.substr(0, no_sign_ins.length() - 2);
								}
								opcode += status;
								//­pºâdisp¨Ã§PÂ_bp
								if (!FindBTree(no_sign_ins)) {
									disp = stoi(no_sign_ins, nullptr, 16);
								}
								else {
									int loc = stoi(FindBTree_LOC(no_sign_ins), nullptr, 16);
									int pc = stoi(split_ins[0], nullptr, 16) + 3;
									if (loc - pc < 2048 && loc - pc > -2049) {
										disp = loc - pc;
										xbpe += 2;
									}
									else {
										disp = loc - stoi(Base, nullptr, 16);
										xbpe += 4;
									}
								}
								ss << hex << opcode << xbpe;
								temp = ss.str();
								aa << hex << disp;
								string temp2 = aa.str();
								if (temp2.length() > 3) {
									temp2 = temp2.substr(temp2.length() - 3);
								}
								while (temp2.length() < 3) {
									temp2 = "0" + temp2;
								}
								temp += temp2;
								while (temp.length() < 6) {
									temp = "0" + temp;
								}
								cout << std::format("{}\t{}\t{}\t{}\t{}", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp) << endl;
								writefile << std::format("{} {} {} {} {}\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3], temp);
							}
						}
					}
					else {
						//split_ins[2] == "START"
						cout << std::format("{}\t{}\t{}\t{}\tNULL", split_ins[0], split_ins[1], split_ins[2], split_ins[3]) << endl;
						writefile << std::format("{} {} {} {} NULL\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3]);
					}
				}
				else {
					//split_ins == "RESW" or split_ins == "RESB"
					cout << std::format("{}\t{}\t{}\t{}\tNULL", split_ins[0], split_ins[1], split_ins[2], split_ins[3]) << endl;
					writefile << std::format("{} {} {} {} NULL\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3]);
				}
			}
			else {
				//split_ins == "BASE"
				Base = FindBTree_LOC(split_ins[3]).substr(2);
				cout << std::format("{}\t{}\t{}\t{}\tNULL", split_ins[0], split_ins[1], split_ins[2], split_ins[3]) << endl;
				writefile << std::format("{} {} {} {} NULL\n", split_ins[0], split_ins[1], split_ins[2], split_ins[3]);
			}
		}
		else {
			//split_ins == "END"
			cout << std::format("{}\t{}\t{}\t{}\tNULL", split_ins[0], split_ins[1], split_ins[2], split_ins[3]) << endl;
			writefile << std::format("{} {} {} {} NULL\n ", split_ins[0], split_ins[1], split_ins[2], split_ins[3]);
		}
	}
	myfile.close();
	writefile.close();
	return true;
}
