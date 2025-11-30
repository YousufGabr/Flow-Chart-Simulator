#include "HelperFn.h"
#include<iostream>
#include<string>
using namespace std;

bool IsValue(string input)
{

	int dots = 0;
	int start = 0;

	if ((input[start] == '+') || (input[start] == '-'))start++; //check if first element is + or - and skip if true

	for (int i = start; i < input.size(); i++)
	{
		if ((input[i] >= '0') && (input[i] <= '9')) //check if it is a normal digit 
			continue;
		else if (input[i] == '.') //check if is a dot 
		{
			dots++;
			if (dots > 1) return false;  //check if there is two consecutive dots 
		}
		else return false;
	}
	if (dots == input.size()) return false; //check if the string is only dots or e which is invalid


	return true;
}

bool IsVariable(string input)
{


	if (!((input[0] >= 'a' && input[0] <= 'z') || (input[0] >= 'A' && input[0] <= 'Z') || (input[0] == '_'))) return false;

	for (int i = 1; i < input.size(); i++) //checks every element if it is valid or not
	{
		if (!((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] == '_') || (input[i] >= '0') && (input[i] <= '9'))) return false;
	}

	return true;
}

string doubleToString(double value) {
	string s = to_string(value);

	// Remove trailing zeros
	s.erase(s.find_last_not_of('0') + 1, string::npos);

	// If last character is a decimal point, remove it
	if (s.back() == '.')
		s.pop_back();

	return s;
}



OpType ValueOrVariable(string input)
{
	if (IsValue(input)) return VALUE_OP;
	if (IsVariable(input)) return VARIABLE_OP;
	return INVALID_OP;
}
