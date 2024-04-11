#pragma once

#include "TransactionNode.h"

class BST {
private:
	Node* mpRoot;
	void destroyTree(Node* start) {
		if (start == nullptr) {
			return;
		}
		destroyTree(start->getLeft());
		destroyTree(start->getRight());
		delete start;
	}
	bool insert(Node*& start, Node*& nNode) {
		if (mpRoot == nullptr) {
			mpRoot = nNode;
		}
		else if (start->getUnits() < nNode->getUnits()) {
			if (start->getLeft() == nullptr) {
				start->setLeft(nNode);
			}
			else {
				insert(start->getLeft(), nNode);
			}
		}
		else if (start->getUnits() > nNode->getUnits()) {
			if (start->getRight() == nullptr) {
				start->setRight(nNode);
			}
			else {
				insert(start->getRight(), nNode);
			}
		}
		return true;
	}
	void inOrderTraversal(Node* start) {
		if (start == nullptr) {
			return;
		}
		destroyTree(start->getLeft());
		start->printData();
		destroyTree(start->getRight());
		
	}

public:
	BST() {
		this->mpRoot = nullptr;
	}
	~BST() {
		destroyTree(this->getRoot());
	}
	//setters
	void setRoot(Node* nRoot) {
		this->mpRoot = nRoot;
	}
	//getters
	Node* getRoot() {
		return this->mpRoot;
	}
	//members
	bool insert(Node* nNode) {
		if (insert(this->mpRoot, nNode)) {
			return true;
		}
		else {
			return false;
		}
	}
	void inOrderTraversal() {
		inOrderTraversal(this->mpRoot);
	}
	//largest value needs to be set to 0 before calling function
	void findLargest(Node* start, int* largest, Node** end) {

		if (start == nullptr) {
			return;
		}
		findLargest(start->getLeft(),largest,end);
		findLargest(start->getRight(), largest, end);
		if (start->getUnits() > *largest) {
			*largest = start->getUnits();
			*end = start;
		}
	}
	//largest value needs to be set to root units before calling function
	void findSmallest(Node* start, int* largest, Node** end) {
		
		if (start == nullptr) {
			return;
		}
		
		findSmallest(start->getLeft(), largest, end);
		findSmallest(start->getRight(), largest, end);
		if (start->getUnits() < *largest) {
			*largest = start->getUnits();
			*end = start;
		}
	}
	
};