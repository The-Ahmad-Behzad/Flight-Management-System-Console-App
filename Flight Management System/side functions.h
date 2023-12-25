#pragma once
#include <iostream>
#include <string>
#include <fstream> 
#include <conio.h>
using namespace std;
int checkIfExists(string toBeFound, string filename, bool& found) {
	ifstream fin2(filename);
	found = false;
	int i;
	for (i = 0; !fin2.eof(); i++) {
		string Uname;
		fin2 >> Uname;
		if (toBeFound == Uname) {
			found = true;
			break;
		}
	}
	fin2.close();
	return i;
}
void createPassword(string pwd, bool& hasUpperCase, bool& hasLowerCase, bool& hasNumeric, bool& hasSpecialChar) {
	hasUpperCase = false, hasLowerCase = false, hasNumeric = false, hasSpecialChar = false;
	if (pwd.length() != 8) {
		cout << "Incorrect length. Password must be 8 characters long." << endl << endl;
		return;
	}
	else {
		for (int i = 0; i < pwd.length(); i++) {
			const char* specialChars = "-_.#";
			for (int j = 0; j < strlen(specialChars); j++) {
				if (pwd[i] == specialChars[j]) {
					hasSpecialChar = true;
					break;
				}
			}
			const char* digits = "0123456789";
			for (int j = 0; j < 10; j++) {
				if (pwd[i] == digits[j]) {
					hasNumeric = true;
					break;
				}
			}
			if (isalpha(pwd[i]) && toupper(pwd[i]) == pwd[i]) {
				hasUpperCase = true;
			}
			if (isalpha(pwd[i]) && tolower(pwd[i]) == pwd[i]) {
				hasLowerCase = true;
			}
		}
	}
}