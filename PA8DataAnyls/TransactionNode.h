#pragma once
#include "Node.h"

class TransactionNode : public Node {
private:
	int mUnits;

public:
	TransactionNode(std::string nData, int nUnits) : Node(nData) {
		this->mUnits = nUnits;
	}
	~TransactionNode() {

	}
	//setters
	void setUnits(int nUnits) {
		this->mUnits = nUnits;
	}
	//getters
	int getUnits() {
		return this->mUnits;
	}

	//print data function needs to be one line for the tree print function
	void printData() const override {
		std::cout << this->mData << " <-> " << this->mUnits;
	}
};