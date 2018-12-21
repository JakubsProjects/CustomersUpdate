#pragma once
#pragma once
/*customer.h*/

//
// Customer class for banking program in modern C++.
//
// << Jakub Glebocki >>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#pragma once

#include <iostream>
#include <string>

using namespace std;


class Customer
{
private:
	string Name;
	int ID;
	double Balance;

public:
	Customer(string name, int id, double balance) :
		Name(name), ID(id), Balance(balance)
	{ }

	/////////GETTERS
	string GetName() {
		return Name;
	}

	int GetID() {
		return ID;
	}

	double GetBalance() {
		return Balance;
	}

	//////// SETTERS
	void SetBalance(double updatebalance) {
		Balance = Balance + updatebalance;
	}

	double CheckBalance(double updatebalance) {
		Balance = Balance + updatebalance;
		return Balance;
	}

};
