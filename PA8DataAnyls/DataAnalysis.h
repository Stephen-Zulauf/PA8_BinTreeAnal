#pragma once

#include "BST.h"

class DataAnalysis {
private:
	BST mTreeSold;
	BST mTreePurchased;
	std::ifstream mCsvStream;

	bool openCSV() {
		mCsvStream.open("data.csv");
		if (mCsvStream.is_open()) {
			return true;
		}
		else {
			std::cout << "ERR: BST failed to open file" << std::endl;
			return false;
		}

	}
	bool insertToTree(int nUnits, std::string type, std::string transField) {
		Node* temp;
		temp = new TransactionNode(type, nUnits);
		if (temp) {
			if (transField == "Sold") {
				bool result = mTreeSold.insert(temp);
				if (result) {
					return true;
				}
				else {
					std::cout << "ERR: BST Failed to insert node" << std::endl;
					return false;
				}
			}
			else if (transField == "Purchased") {
				bool result = mTreePurchased.insert(temp);
				if (result) {
					return true;
				}
				else {
					std::cout << "ERR: BST Failed to insert node" << std::endl;
					return false;
				}
			}
			std::cout << "ERR: BST Wrong Transaction field" << std::endl;
			return false;
		}
		else {
			std::cout << "ERR: BST Failed to create node" << std::endl;
			return false;
		}
		
	}
	bool seperateFileLine(std::string& buffer) {
		std::string buffCopy = buffer;
		size_t pos = 0;
		std::string delim = ",";

		int units = 0;
		std::string type;
		std::string trans;

		//get units
		pos = buffCopy.find(delim);
		units = stoi(buffCopy.substr(0, pos));
		buffCopy.erase(0, pos + delim.length());

		//get type
		pos = buffCopy.find(delim);
		type = buffCopy.substr(0, pos);
		buffCopy.erase(0, pos + delim.length());

		//get transaction type
		pos = buffCopy.find(delim);
		trans = buffCopy.substr(0, pos);
		buffCopy.erase(0, pos + delim.length());

		bool result = insertToTree(units, type, trans);
		if (result) {
			return true;
		}
		else {
			std::cout << "ERR: BST failed to seperate line---->" << std::endl;
			std::cout << "ERR: units: " << units << std::endl;
			std::cout << "ERR: type: " << type << std::endl;
			std::cout << "ERR: Transaction: " << trans << std::endl;
			return false;
		}
	}
	void readFile() {
		//buffer to write to
		std::string buffer;
		//open csv file
		if (openCSV()) {
			//remove header
			std::getline(mCsvStream, buffer);
			//use getline for each line and send buffer to seperatefileline
			while (mCsvStream.good()) {

				std::getline(mCsvStream, buffer);
				seperateFileLine(buffer);

			}
		}
		else {
			std::cout << "ERR: BST Failed to open csv file" << std::endl;
		}
		
		
	}
	//this recursivly prints a tree to the command prompt
	//adapated from:
	// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
	void printTree(const std::string& prefix, Node* node, bool isLeft) {
		if (node != nullptr)
		{
			std::cout << prefix;

			std::cout << (isLeft ? "|---" : "L---");

			// print the value of the node
			node->printData();
			std::cout << std::endl;

			// enter the next tree level - left and right branch
			printTree(prefix + (isLeft ? "|   " : "    "), node->getLeft(), true);
			printTree(prefix + (isLeft ? "|   " : "    "), node->getRight(), false);
		}
	}
	void printTrends() {
		//this uses pointers as a static value in the recursive search functions
		//needs error checking but :)
		int temp = 0;
		Node* result = nullptr;

		mTreeSold.findLargest(mTreeSold.getRoot(), &temp, &result);
		int tSoldUnits = result->getUnits();
		std::string tSold = result->getData();

		temp = mTreeSold.getRoot()->getUnits();
		mTreeSold.findSmallest(mTreeSold.getRoot(), &temp, &result);
		int lSoldUnits = result->getUnits();
		std::string lSold = result->getData();

		temp = 0;
		mTreePurchased.findLargest(mTreePurchased.getRoot(), &temp, &result);
		int tPurchUnits = result->getUnits();
		std::string tPurch = result->getData();

		temp = mTreePurchased.getRoot()->getUnits();
		mTreePurchased.findSmallest(mTreePurchased.getRoot(), &temp, &result);
		int lPurchUnits = result->getUnits();
		std::string lPurch = result->getData();

		std::cout << "----Top Seller---" << std::endl;
		std::cout << "-Type:  " << tSold << "-" << std::endl;
		std::cout << "-Units:  " << tSoldUnits << "-" << std::endl;

		std::cout << "----Least Sold---" << std::endl;
		std::cout << "-Type:  " << lSold << "-" << std::endl;
		std::cout << "-Units:  " << lSoldUnits << "-" << std::endl;

		std::cout << "----Top Purchased---" << std::endl;
		std::cout << "-Type:  " << tPurch << "-" << std::endl;
		std::cout << "-Units:  " << tPurchUnits << "-" << std::endl;

		std::cout << "----Least Purchased---" << std::endl;
		std::cout << "-Type:  " << lPurch << "-" << std::endl;
		std::cout << "-Units:  " << lPurchUnits << "-" << std::endl;
		std::cout << "----------------------" << std::endl;
	}
	//print header and menu
	void printMenu() {
		system("cls");
		std::cout << "           _   _          _  __     ______________ _____  " << std::endl;
		std::cout << "     /\\   | \\ | |   /\\   | | \\ \\   / /___  /  ____|  __ \\" << std::endl;
		std::cout << "    /  \\  |  \\| |  /  \\  | |  \\ \\_/ /   / /| |__  | |__) |" << std::endl;
		std::cout << "   / /\\ \\ | . ` | / /\\ \\ | |   \\   /   / / |  __| |  _  /" << std::endl;
		std::cout << "  / ____ \\| |\\  |/ ____ \\| |____| |   / /__| |____| | \\ \\ " << std::endl;
		std::cout << " /_/    \\_\\_| \\_/_/    \\_\\______|_|  /_____|______|_|  \\_\\" << std::endl;
		std::cout << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << "| 1) Print Sales Tree     " << "|" << std::endl;
		std::cout << "| 2) Print Purchases Tree " << "|" << std::endl;
		std::cout << "| 3) Print Trends         " << "|" << std::endl;
		std::cout << "| 4) Exit                 " << "|" << std::endl;
		std::cout << "---------------------------------" << std::endl;
	}

public:
	//function to run in main
	void runAnalysis() {

		std::string buffer;
		int choice = 0;

		readFile();

		printMenu();

		while (choice != 4) {
			std::cin >> buffer;
			choice = stoi(buffer);

			switch (choice) {
			case 1:
				//print sales tree
				printTree("", mTreeSold.getRoot(), false);
				std::cout << "enter 1 to exit" << std::endl;
				choice = 0;
				while (choice != 1) {
					std::cin >> buffer;
					choice = stoi(buffer);
				}
				printMenu();
				choice = 0;
				break;
			case 2:
				//print purchase tree
				printTree("", mTreePurchased.getRoot(), false);
				std::cout << "enter 1 to exit" << std::endl;
				choice = 0;
				while (choice != 1) {
					std::cin >> buffer;
					choice = stoi(buffer);
				}
				printMenu();
				choice = 0;
				break;
			case 3:
				printTrends();
				std::cout << "enter 1 to exit" << std::endl;
				choice = 0;
				while (choice != 1) {
					std::cin >> buffer;
					choice = stoi(buffer);
				}
				printMenu();
				choice = 0;
				break;
			case 4:
				std::cout << "GoodBye :)" << std::endl;
			}
		}

	}
	
};