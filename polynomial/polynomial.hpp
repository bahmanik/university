#include <ostream>
#include <string>
#include "linked_LS.hpp"
#pragma once

bool is_coef(char C){
	if (C <= '9' && C >= '1') {
		return true;
	}
	return false;
}

bool is_vari(char C){
	if (C <= 'z' && C >= 'a') {
		return true;
	}

	if (C <= 'Z' && C >= 'A') {
		return true;
	}

	return false;
}

class term {
public:
	term(std::string);
	friend std::ostream& operator<<(std::ostream& out, term& Term);
	friend bool operator<(term rhs, term lfs);
	friend bool operator>(term rhs, term lfs);
	friend bool operator<=(term rhs, term lfs);
	friend bool operator>=(term rhs, term lfs);
	friend bool operator==(term rhs, term lfs);
	term(){
		Sign = '+';
		Coef = 1;
		Var = '0';
		Pow = 1;
	}
private:
	char Sign;
	double Coef;
	char Var;
	double Pow;
};

bool operator<(term rhs, term lfs){
	return rhs.Pow < lfs.Pow;
}

bool operator>(term rhs, term lfs){
	return rhs.Pow > lfs.Pow;
}

bool operator<=(term rhs, term lfs){
	return rhs.Pow <= lfs.Pow;
}

bool operator>=(term rhs, term lfs){
	return rhs.Pow >= lfs.Pow;
}

bool operator==(term rhs, term lfs){
	return rhs.Pow >= lfs.Pow;
}

std::ostream& operator<<(std::ostream& out, term& Term){
	out << Term.Sign << Term.Coef << Term.Var << '^' << Term.Pow;
	return out;
}

term::term(std::string Term) {
	// some empty string to store the values
	std::string sign = "";
	std::string coef = "";
	std::string vari = "";
	std::string pow = "";
	
	// cheaking if the coef has ended
	bool EC =  false;
	
	int len = Term.length();
	for (char C : Term) {
		
		if(C == '+' || C == '-')
		{
			sign += C;
		}
		else if (is_coef(C) && !EC) {
			coef += C;
		}

		else if (is_vari(C)) {
			EC = true;
			vari += C;
		}
		else {
			EC = true;
			if (C == '^') continue;
			pow += C;
		}
	}

	Sign = sign == "" ? '+' : sign[0];
	Coef = std::stod(coef);
	Var = vari == "" ? '\0' : vari[0];
	Pow = pow == "" ? Pow = 1 : std::stoi(pow);
}


class polynomial {
public:
	linked_LS<term> term_list;
	polynomial(std::string Pol);

};

polynomial::polynomial(std::string Pol) {
	int len = Pol.length();
	int start = 0;
	for (int i = 0; i < len; i++) {
		if (Pol[i] == '+' || Pol[i] == '-') {
			term temp(Pol.substr(start, i - start));
			term_list.insert_S(temp);
			start = i+1;
		}
	}
	term temp(Pol.substr(start, len-1));
	term_list.insert_S(temp);
}

std::ostream& operator << (std::ostream& out, polynomial& poli){
	out<<poli.term_list;
	return  out;
}
