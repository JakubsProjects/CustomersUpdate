/*main.cpp*/

//
// Banking program in modern C++.
//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "customer.h"

using namespace std;

void printCustomers(vector<Customer>& C) {

	for (auto& c : C) {

		cout << " " << c.GetName() << " " << "(" << c.GetID() << "): $" << c.GetBalance() << endl;
	}

}
void SortByBalance(vector<Customer>& customers) {

	sort(customers.begin(), customers.end(),
		[](Customer& c1, Customer& c2) {

		if (c1.GetBalance() > c2.GetBalance()) {
			return true;
		}
		else if (c1.GetBalance() < c2.GetBalance()) {
			return false;
		}
		else {
			if (c1.GetName() < c2.GetName()) {
				return true;
			}
			else {
				return false;
			}

		}

	}
	);
	cout << ">> Customers after:" << endl;
	printCustomers(customers);
}

void sortFunction(vector<Customer>& customers) {

	sort(customers.begin(), customers.end(),
		[](Customer& c1, Customer& c2) {

		if (c1.GetName() < c2.GetName()) {
			return true;
		}
		else {
			return false;
		}

	}
	);

	cout << ">> Customers before:" << endl;

	printCustomers(customers);

}

bool idValid(string ID, vector<Customer> customers) {
	for (auto& c : customers) {
		if (c.GetID() == stoi(ID)) {
			return true;
		}
	}
	return false;
}

bool balanceValid(string Balance, vector<Customer> customers) {
	for (auto& b : customers) {
		if (b.CheckBalance(stod(Balance)) > 0.0) {
			return true;
		}
	}

	return false;
}


void ParseTrans(vector<Customer>& customers, string file) {
	ifstream customerFile(file);
	string ID, line;
	string Balance;

	cout << ">> Processing..." << endl;
	while (getline(customerFile, line)) {
		stringstream ss(line);
		getline(ss, ID, ',');
		getline(ss, Balance);

		double newBalance = 0;

		for (auto& c : customers) {
			newBalance = stod(Balance) + c.GetBalance();

			if (c.GetID() == stoi(ID)) {
				if (newBalance >= 0.0) {
					c.SetBalance(stod(Balance));

				}
				else {
					cout << " **Rejected Tx: " << ID << "," << std::setprecision(2) << stod(Balance) << endl;
				}

			}
		}

		int validid = idValid(ID, customers);

		if (validid == false) {
			cout << std::setprecision(2) << " **Invalid Tx: " << stod(ID) << "," << stod(Balance) << endl;
		}
	}

	SortByBalance(customers);
}


void ParseCust(vector<Customer>& customers, string file) {
	ifstream customerFile(file);
	string line, Name;
	string ID;
	string Balance;

	while (getline(customerFile, line)) {
		stringstream ss(line);

		getline(ss, Name, ',');
		getline(ss, ID, ',');
		getline(ss, Balance);

		Customer C(Name, stod(ID), stod(Balance));

		customers.push_back(C);

		//cout << "Printing Customer" << C.GetName() << " " << C.GetID() << " " << C.GetBalance() << endl;
	}

	sortFunction(customers);

}


int main()
{

	string  customerFilename, transactionsFilename;

	cin >> customerFilename;
	cout << customerFilename << endl;

	cin >> transactionsFilename;
	cout << transactionsFilename << endl;

	ifstream  custFile(customerFilename);
	ifstream  txFile(transactionsFilename);

	cout << std::fixed;
	cout << std::setprecision(2);

	if (!custFile.good())
	{
		cout << "**ERROR: cannot open customers file: '" << customerFilename << "'" << endl;
		return -1;
	}
	if (!txFile.good())
	{
		cout << "**ERROR: cannot open transactions file: '" << transactionsFilename << "'" << endl;
		return -1;
	}

	// 
	// TODO
	//

	vector<Customer> customers;

	ParseCust(customers, customerFilename);

	ParseTrans(customers, transactionsFilename);

	//system("PAUSE");

	return 0;
}
