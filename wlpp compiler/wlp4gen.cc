#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
using namespace std;

string label_generater(string s, string * function_name, map<string, map<string, pair<string, int> > > * symbol_tables){
	int n = symbol_tables->at(*function_name).at((*function_name) + s).second;
	symbol_tables->at(*function_name).at((*function_name) + s).second += 1;
	string f;
	stringstream convert;
	convert << n;
	f = convert.str();
	string res = (*function_name) + s + f;
	return res;
}

void representation(string s, string * function_name, map<string, map<string, pair<string, int> > > * symbol_tables) {
	int n = symbol_tables->at(*function_name).at(s).second;
		cout << "lw $3, "<< n << "($29)" << endl;
}

void push(){
	cout << "sw $3, -4($30)" << endl;
	cout << "sub $30, $30, $4" << endl;
}
void pop(){
	cout << "add $30, $30, $4" << endl;
	cout << "lw $5, -4($30)" << endl;
}


void code(string * s, string * function_name, map<string, map<string, pair<string, int> > > * symbol_tables, int * n){
	//cout << *s << endl;
	if (*s == "procedures main"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
	else if(*s == "main INT WAIN LPAREN dcl COMMA dcl RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE"){
		cout << "wain:" << endl;
		cout << "sw $31, -4($30)" << endl;
		cout << "sub $30, $30, $4" << endl;
		*function_name = "wain";
		map<string, pair<string, int> > labels;
		string la = "label";
		labels.insert(make_pair(((*function_name)+"loop"), make_pair(la, 0)));
		labels.insert(make_pair(((*function_name)+"else"), make_pair(la, 0)));
		labels.insert(make_pair(((*function_name)+"done"), make_pair(la, 0)));
		labels.insert(make_pair(((*function_name)+"quit"), make_pair(la, 0)));
		symbol_tables->insert(make_pair("wain",labels));
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);//dcl
		string atype = symbol_tables->at(*function_name).at(s->substr(3)).first;
		cout << "sw $1, " << *n - 4 << "($29)" << endl;
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);//dcl
		cout << "sw $2, " << *n - 4 << "($29)" << endl;
		if (atype == "int"){
			cout << "add $2, $0, $0" << endl;
			cout << "lis $5" << endl;
			cout << ".word init" << endl;
			cout << "jalr $5" << endl;
			cout << "lw $2, " << *n - 4 << "($29)" << endl;
		}
		else if (atype == "int*"){
			cout << "lis $5" << endl;
			cout << ".word init" << endl;
			cout << "jalr $5" << endl;
			cout << "lw $2, " << *n - 4 << "($29)" << endl;
		}
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);//dcls
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);//statements
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);//expr
		getline(cin, *s);
		getline(cin, *s);
		cout << "add $30, $30, $4" << endl;
		cout << "lw $31, -4($30)" << endl;
		cout << "jr $31" << endl;
	}
	else if (*s == "type INT"){
		getline(cin, *s);
		getline(cin, *s);
		symbol_tables->at(*function_name).insert(make_pair(s->substr(3), make_pair("int", *n)));
		*n += 4;
	}
	else if (*s == "type INT STAR"){
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		symbol_tables->at(*function_name).insert(make_pair(s->substr(3), make_pair("int*", *n)));
		*n += 4;
	}
	else if (*s == "dcls"){
		
	}
	else if (*s == "dcl type ID"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
	else if (*s == "statements"){
		
	}
	else if (*s == "expr term"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
	else if (*s == "term factor"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
	else if (*s == "factor ID"){
		getline(cin, *s);
		representation(s->substr(3), function_name, symbol_tables);
		*s = symbol_tables->at(*function_name).at(s->substr(3)).first;
	}
	else if (*s == "factor LPAREN expr RPAREN") {
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		string temp = *s;
		getline(cin, *s);
		*s = temp;
	}
	else if (*s == "expr expr PLUS term"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		string expr_type = *s;
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		string term_type = *s;
		pop();
		if (expr_type == "int*"){
			cout << "add $3, $3, $3" << endl;
			cout << "add $3, $3, $3" << endl;
			*s = "int*";
		}
		else {
			if (term_type == "int"){
				*s = "int";
			}
			else {
				cout << "add $5, $5, $5" << endl;
				cout << "add $5, $5, $5" << endl;
				*s = "int*";
			}
		}
		cout << "add $3, $3, $5" << endl;
	}
	else if (*s == "expr expr MINUS term"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		string expr_type = *s;
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		string term_type = *s;
		pop();
		if (expr_type == "int*"){
			if (term_type == "int*"){
				cout << "sub $3, $5, $3" << endl;
				cout << "div $3, $4" << endl;
				cout << "mflo $3" << endl;
				*s = "int";
			}
			else {
				cout << "add $3, $3, $3" << endl;
				cout << "add $3, $3, $3" << endl;
				cout << "sub $3, $5, $3" << endl;
				*s = "int*";
			}
		}
		else {
			*s = "int";
			cout << "sub $3, $5, $3" << endl;
		}
	}
	else if (*s == "term term STAR factor"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "mult $3, $5" << endl;
		cout << "mflo $3" << endl;
		*s = "int";
	}
	else if (*s == "term term SLASH factor"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "div $5, $3" << endl;
		cout << "mflo $3" << endl;
		*s = "int";
	}
	else if (*s == "term term PCT factor"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "div $5, $3" << endl;
		cout << "mfhi $3" << endl;
		*s = "int";
	}
	else if (*s == "factor NUM") {
		getline(cin, *s);
		cout << "lis $3" << endl;
		cout << ".word " << s->substr(4) << endl;
		*s = "int";
	}
	else if (*s == "statements statements statement"){
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
	else if (*s == "statement PRINTLN LPAREN expr RPAREN SEMI") {
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		cout << "sw $1, -4($30)" << endl;
		cout << "sub $30, $30, $4" << endl;
		cout << "add $1, $3, $0" << endl;
		cout << "lis $5" << endl;
		cout << ".word print" << endl;
		cout << "jalr $5" << endl;
		cout << "add $30, $30, $4" << endl;
		cout << "lw $1, -4($30)" << endl;
		getline(cin, *s);
		getline(cin, *s);
	}
	else if (*s == "dcls dcls dcl BECOMES NUM SEMI") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		getline(cin, *s);
		getline(cin, *s);
		if (*s == "type INT") {
			getline(cin, *s);
			getline(cin, *s);
			symbol_tables->at(*function_name).insert(make_pair(s->substr(3), make_pair("int", *n)));
			*n += 4;
		}
		else if (*s == "type INT STAR") {
			getline(cin, *s);
			getline(cin, *s);
			getline(cin, *s);
			symbol_tables->at(*function_name).insert(make_pair(s->substr(3), make_pair("int*", *n)));
			*n += 4;
		}
		getline(cin, *s);
		getline(cin, *s);
		cout << "lis $3" << endl;
		cout << ".word " << s->substr(4) << endl;
		cout << "sw $3, " << ((*n) - 4) << "($29)" << endl;
		getline(cin, *s);
	}
	else if (*s == "statement lvalue BECOMES expr SEMI") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "sw $3, 0($5)" <<endl;
		getline(cin, *s);
	}
	else if (*s == "lvalue ID") {
		getline(cin, *s);
		int posi = (symbol_tables->at(*function_name).at(s->substr(3)).second);
		cout << "lis $3" << endl;
		cout << ".word " << posi << endl;
		cout << "add $3, $3, $29" << endl;
		*s = symbol_tables->at(*function_name).at(s->substr(3)).first;
	}
	else if (*s == "lvalue LPAREN lvalue RPAREN") {
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		string temp = *s;
		getline(cin, *s);
		*s = temp;
	}
	else if (*s == "test expr LT expr") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "slt $3, $5, $3" << endl;
	}
	else if (*s == "statement WHILE LPAREN test RPAREN LBRACE statements RBRACE"){
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		string loop = label_generater("loop", function_name, symbol_tables);
	//	string dothis = label_generater("dothis", function_name, symbol_tables);
		string quit = label_generater("quit", function_name, symbol_tables);
		cout << loop <<":" <<endl;
		code(s, function_name, symbol_tables, n);
		cout << "beq $3, $0, " << quit << endl;
	//	cout << "bne $3, $0, " << dothis << endl;
	//	cout << "lis $5" << endl;
	//	cout << ".word " << quit << endl;
	//	cout << "jr $5" << endl;
	//	cout << dothis << endl;
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	//	cout << "lis $5" << endl;
	//	cout << ".word " << loop << endl;
	//	cout << "jr $5" << endl;
		cout << "beq $0, $0, " << loop << endl;
		cout << quit <<":" <<endl;
		getline(cin, *s);
	}
	else if (*s == "test expr EQ expr") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "slt $6, $5, $3" << endl;
		cout << "slt $7, $3, $5" << endl;
		cout << "add $3, $6, $7" << endl;
		cout << "lis $5" << endl;
		cout << ".word 1" << endl;
		cout << "sub $3, $5, $3" << endl;
	}
	else if (*s == "test expr NE expr") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "slt $6, $5, $3" << endl;
		cout << "slt $7, $3, $5" << endl;
		cout << "add $3, $6, $7" << endl;
	}
	else if (*s == "test expr LE expr") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "slt $3, $3, $5" << endl;
		cout << "lis $5" << endl;
		cout << ".word 1" << endl;
		cout << "sub $3, $5, $3" << endl;
	}
	else if (*s == "test expr GE expr") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "slt $3, $5, $3" << endl;
		cout << "lis $5" << endl;
		cout << ".word 1" << endl;
		cout << "sub $3, $5, $3" << endl;
	}
	else if (*s == "test expr GT expr") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		pop();
		cout << "slt $3, $3, $5" << endl;
	}
	else if (*s == "statement IF LPAREN test RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE"){
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		string elsedo = label_generater("else", function_name, symbol_tables);
		string done_ = label_generater("done", function_name, symbol_tables);
		code(s, function_name, symbol_tables, n);
		cout << "beq $3, $0, " << elsedo << endl;
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		cout << "beq $0, $0, " << done_ << endl;
		cout << elsedo << ":" << endl;
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		cout << done_ << ":" << endl;
		getline(cin, *s);
	}
	else if (*s == "factor NULL") {
		getline(cin, *s);
		cout << "add $3, $11, $0" << endl;
		*s = "int*";
	}
	else if (*s == "dcls dcls dcl BECOMES NULL SEMI") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		getline(cin, *s);
		getline(cin, *s);
		if (*s == "type INT") {
			getline(cin, *s);
			getline(cin, *s);
			symbol_tables->at(*function_name).insert(make_pair(s->substr(3), make_pair("int", *n)));
			*n += 4;
		}
		else if (*s == "type INT STAR") {
			getline(cin, *s);
			getline(cin, *s);
			getline(cin, *s);
			symbol_tables->at(*function_name).insert(make_pair(s->substr(3), make_pair("int*", *n)));
			*n += 4;
		}
		getline(cin, *s);
		getline(cin, *s);
		cout << "lis $3" << endl;
		cout << ".word 0" << endl;
		cout << "sw $3, " << ((*n) - 4) << "($29)" << endl;
		getline(cin, *s);
	}
	else if (*s == "factor AMP lvalue") {
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		*s = "int*";
	}
	else if (*s == "factor STAR factor") {
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		cout << "lw $3, 0($3)" << endl;
		*s = "int";
	}
	else if (*s == "lvalue STAR factor") {
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		*s = "int";
	}
	else if (*s == "factor NEW INT LBRACK expr RBRACK") {
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		cout << "add $1, $3, $0" << endl;
		cout << "sw $31, -4($30)" << endl;
		cout << "sub $30, $30, $4" << endl;
		cout << "lis $5" << endl;
		cout << ".word new" << endl;
		cout << "jalr $5" << endl;
		cout << "add $30, $30, $4" << endl;
		cout << "lw $31, -4($30)" << endl;
		cout << "bne $0, $3, 1" << endl;
		cout << "add $3, $11, $0" << endl;
		getline(cin, *s);
		*s = "int*";
	}
	else if (*s == "statement DELETE LBRACK RBRACK expr SEMI") {
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		string quit = label_generater("quit", function_name, symbol_tables);
		code(s, function_name, symbol_tables, n);
		cout << "beq $3, $11, " << quit << endl;
		cout << "add $1, $3, $0" << endl;
		cout << "sw $31, -4($30)" << endl;
		cout << "sub $30, $30, $4" << endl;
		cout << "lis $5" << endl;
		cout << ".word delete" << endl;
		cout << "jalr $5" << endl;
		cout << "add $30, $30, $4" << endl;
		cout << "lw $31, -4($30)" << endl;
		cout << quit << ":" << endl;
		getline(cin, *s);
	}
	else if (*s == "procedures procedure procedures") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
	else if (*s == "procedure INT ID LPAREN params RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE") {
		getline(cin, *s);
		getline(cin, *s);
		*function_name = s->substr(3);
		map<string, pair<string, int> > labels;
		string la = "label";
		labels.insert(make_pair(((*function_name) + "loop"), make_pair(la, 0)));
		labels.insert(make_pair(((*function_name) + "else"), make_pair(la, 0)));
		labels.insert(make_pair(((*function_name) + "done"), make_pair(la, 0)));
		labels.insert(make_pair(((*function_name) + "quit"), make_pair(la, 0)));
		symbol_tables->insert(make_pair(*function_name, labels));
		cout << *function_name << ":" << endl;
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		cout << "sw $1, -4($30)" << endl;
		cout << "sw $2, -8($30)" << endl;
		cout << "sw $5, -12($30)" << endl;
		cout << "sw $31, -16($30)" << endl;
		cout << "lis $5" << endl;
		cout << ".word 16" << endl;
		cout << "sub $30, $30, $5" << endl;
		getline(cin, *s);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		getline(cin, *s);
		getline(cin, *s);
		cout << "lis $5" << endl;
		cout << ".word 16" << endl;
		cout << "add $30, $30, $5" << endl;
		cout << "lw $1, -4($30)" << endl;
		cout << "lw $2, -8($30)" << endl;
		cout << "lw $5, -12($30)" << endl;
		cout << "lw $31, -16($30)" << endl;
		cout << "jr $31" << endl;
	}
	else if (*s == "params") {

	}
	else if (*s == "factor ID LPAREN RPAREN") {
		getline(cin, *s);
		cout << "lis $5" << endl;
		cout << ".word " << s->substr(3) << endl;
		cout << "jalr $5" << endl;
		getline(cin, *s);
		getline(cin, *s);
		*s = "int";
	}
	else if (*s == "params paramlist") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		int number_of_params = symbol_tables->at("plist").at("plist").second;
		int temp = *n;
		while (number_of_params > 0) {
			pop();
			temp -= 4;
			cout << "sw $5, " << temp << "($29)"<< endl;
			number_of_params -= 1;
		}
		symbol_tables->at("plist").at("plist").second = 0;
	}
	else if (*s == "paramlist dcl") {
		symbol_tables->at("plist").at("plist").second += 1;
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
	else if (*s == "paramlist dcl COMMA paramlist") {
		symbol_tables->at("plist").at("plist").second += 1;
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
	else if (*s == "factor ID LPAREN arglist RPAREN"){
		getline(cin, *s);
		string f_n = s->substr(3);
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		cout << "lis $5" << endl;
		cout << ".word " << f_n << endl;
		cout << "jalr $5" << endl;
		getline(cin, *s);
		*s = "int";
	}
	else if (*s == "arglist expr") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
	}
	else if (*s == "arglist expr COMMA arglist") {
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
		push();
		getline(cin, *s);
		getline(cin, *s);
		code(s, function_name, symbol_tables, n);
	}
}


int main() {
	string s;
	int n;
	string function_name;
	map<string, map<string,pair<string, int> > > symbol_tables;
	map<string, pair<string, int> > para;
	string la = "plist";
	para.insert(make_pair(("plist"), make_pair(la, 0)));
	symbol_tables.insert(make_pair("plist", para));
	getline(cin, s);
	getline(cin, s);
	n = 7000 * 4;
	cout << ".import print" << endl;
	cout << ".import init" << endl;
	cout << ".import new" << endl;
	cout << ".import delete" << endl;
	cout << "lis $29" << endl;
	cout << ".word " << n << endl;
	cout << "sub $29, $30, $29" << endl;
	cout << "lis $4" << endl;
	cout << ".word 4" << endl;
	cout << "lis $11" << endl;
	cout << ".word 1" << endl;
	cout << "lis $5" << endl;
	cout << ".word wain" << endl;
	cout << "jr $5" << endl;
	n = 0;
	getline(cin, s);
	code(&s, &function_name, &symbol_tables, &n);
}
