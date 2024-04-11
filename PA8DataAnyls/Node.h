#pragma once
#include "config.h"
 
class Node {
private:

protected:
	std::string mData;
	Node* mpLeft;
	Node* mpRight;

public:
	Node(std::string nData) {
		mData = nData;
		mpLeft = nullptr;
		mpRight = nullptr;
	}
	virtual ~Node() {

	}
	//setters
	void setData(std::string nData) {
		this->mData = nData;
	}
	void setLeft(Node* nNode) {
		this->mpLeft = nNode;
	}
	void setRight(Node* nNode) {
		this->mpRight = nNode;
	}
	//getters
	std::string getData() {
		return this->mData;
	}
	Node*& getLeft() {
		return this->mpLeft;
	}
	Node*& getRight() {
		return this->mpRight;
	}
	virtual int getUnits() = 0;

	//print
	virtual void printData() const = 0;
};