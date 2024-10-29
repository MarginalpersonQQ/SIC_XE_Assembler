#include "SICXE.h"
using namespace std;

int prime = 443;
int rendom_number = 37;

struct op_c{
    public:
        string op_n;
        int ft;
        int op_va;
};


op_c opt[59]={
   	{   "ADD", 3, 0x18},
	{  "ADDF", 3, 0x58},
	{  "ADDR", 2, 0x90},
	{   "AND", 3, 0x40},
	{ "CLEAR", 2, 0xB4},
	{  "COMP", 3, 0x28},
	{ "COMPF", 3, 0x88},
	{ "COMPR", 2, 0xA0},
	{   "DIV", 3, 0x24},
	{  "DIVF", 3, 0x64},
	{  "DIVR", 2, 0x9C},
	{   "FIX", 1, 0xC4},
	{ "FLOAT", 1, 0xC0},
	{   "HIO", 1, 0xF4},
	{     "J", 3, 0x3C},
	{   "JEQ", 3, 0x30},
	{   "JGT", 3, 0x34},
	{   "JLT", 3, 0x38},
	{  "JSUB", 3, 0x48},
	{   "LDA", 3, 0x00},
	{   "LDB", 3, 0x68},
	{  "LDCH", 3, 0x50},
	{   "LDF", 3, 0x70},
	{   "LDL", 3, 0x08},
	{   "LDS", 3, 0x6C},
	{   "LDT", 3, 0x74},
	{   "LDX", 3, 0x04},
	{   "LPS", 3, 0xD0},
	{   "MUL", 3, 0x20},
	{  "MULF", 3, 0x60},
	{  "MULR", 2, 0x98},
	{  "NORM", 1, 0xC8},
	{    "OR", 3, 0x44},
	{    "RD", 3, 0xD8},
	{   "RMO", 2, 0xAC},
	{  "RSUB", 3, 0x4C},
	{"SHIFTL", 2, 0xA4},
	{"SHIFTR", 2, 0xA8},
	{   "SIO", 1, 0xF0},
	{   "SSK", 3, 0xEC},
	{   "STA", 3, 0x0C},
	{   "STB", 3, 0x78},
	{  "STCH", 3, 0x54},
	{   "STF", 3, 0x80},
	{   "STI", 3, 0xD4},
	{   "STL", 3, 0x14},
	{   "STS", 3, 0x7C},
	{  "STSW", 3, 0xE8},
	{   "STT", 3, 0x84},
	{   "STX", 3, 0x10},
	{   "SUB", 3, 0x1C},
	{  "SUBF", 3, 0x5C},
	{  "SUBR", 2, 0x94},
	{   "SVC", 2, 0xB0},
	{    "TD", 3, 0xE0},
	{   "TIO", 1, 0xF8},
	{   "TIX", 3, 0x2C},
	{  "TIXR", 2, 0xB8},
	{    "WD", 3, 0xDC},
};


class node{
    public:
        string data;
        int format;
        int opcode;
        node *link = NULL;
};

class ha_sh{ 
    friend class node;
    public:
        ha_sh(){
            table=new node *[prime];
            for(int i=0;i< prime;i++){
                table[i]=NULL;
            }
        }
        void hash_table();
        void show_hash();
        node **table;
};

void ha_sh::hash_table(){
    node  *m;       
    node  *la;     
    int ind;         
    int collision_count = 0;
     
    for(int i=0; i < 59; i++){
        ind = 0;
        for(int j = 0; j < opt[i].op_n.length(); j++){
            
            ind = (ind * rendom_number + (opt[i].op_n[j] - 'A' + 1));         //(opt[i].op_n[j] - 'A' + 1)計算ASCII。
        }
        ind %= prime;

        
        if(table[ind] == NULL){
            table[ind] = new node;
            table[ind]->data = opt[i].op_n;
            table[ind]->format = opt[i].ft;
            table[ind]->opcode = opt[i].op_va;
        }
        else {
        	collision_count++;
            la = new node;
            m = table[ind]->link;//null
            la->data = opt[i].op_n;
            la->format = opt[i].ft;
            la->opcode = opt[i].op_va;
            table[ind]->link = la;
            la->link = m;
        }
    }
    cout << "Total collisions: " << collision_count << endl;
}


void ha_sh::show_hash(){
    node *temp;
   
    for(int i = 0; i < prime; i++){
        temp = table[i];  
        while(temp != NULL){
            if (temp->link != NULL){
                cout << temp->data << "\t" << temp->format << "\t" << std::setw(2) << setfill('0') << hex << temp->opcode << " -> ";
            }
            else {
                cout << temp->data << "\t" << temp->format << "\t" << std::setw(2) << setfill('0') << hex << temp->opcode << endl;
            }
            temp = temp->link;
        }
        
    }
}

ha_sh hashTable;

void hashInit() {
    
    hashTable.hash_table();
    // hashTable.show_hash();

}

void hashTotxt() {
    ofstream myfile;
    myfile.open("..\\HashTable.csv");
    node* temp;
    for (int i = 0; i < prime; i++) {
        temp = hashTable.table[i];
        while (temp != NULL) {
            if (temp->link != NULL) {
                myfile << temp->data << "," << temp->format << "," << std::setw(2) << setfill('0') << hex << temp->opcode << "," <<" -> " << ",";
            }
            else {
                myfile << temp->data << "," << temp->format << "," << std::setw(2) << setfill('0') << hex << temp->opcode << "\n";
            }
            temp = temp->link;
        }
    }
    myfile.close();
}

bool FindHash(string keyword){
    int num = 0;
    if (keyword[0] == '+' || keyword[0] == '@' || keyword[0] == '#') {
        keyword = keyword.substr(1);
    }
    for (int j = 0; j < keyword.length(); j++) {
        num = (num * rendom_number + (keyword[j] - 'A' + 1));         //(opt[i].op_n[j] - 'A' + 1)計算ASCII。
    }
    num %= prime;
    node *x = hashTable.table[num];
    if (x != NULL) {
        while (x != NULL) {  
            if (x->data == keyword) {  
                return true;  
            }
            x = x->link;  
        }
    }
    return false;  
}

int FindFormat(string& sour){
    int plus = 0;
    string target;
    if (sour[0] == '+'){
        plus += 1;
		for (int i = 1; i < sour.length(); i++) {
			target += sour[i];
		}
    }
	for (auto& operation : opt) {
		if (operation.op_n == target||operation.op_n == sour) {
			return operation.ft+plus;  // 返回找到的格式
		}
	}
	return 0; 
}

int FindOpCode() {
    return 0;
}

