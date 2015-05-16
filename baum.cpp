#include "baum.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>// for debug
using namespace std;

Baum::Baum() {
	root = new Node(0);
}
Baum::~Baum() {
	delete root;
}
void Baum::insert(int data) {
	if(!root->hasLeft()) {
		root->setLeft(new Node(data));
		return;
	}
	Node* n = root->getLeft();
	while(true) {
		if(data < *n) {
			if(n->hasLeft())
				n = n->getLeft();
			else {
				n->setLeft(new Node(data));
				return;
			}
		} else if(data > *n) {
			if(n->hasRight())
				n = n->getRight();
			else {
				n->setRight(new Node(data));
				return;
			}
		} else throw logic_error("value musst be unique");
	}
}
void Baum::remove(int data) {
	if(!root->hasLeft())
		throw length_error("tree is empty");
	Node* n = root->getLeft();
	Node* prev = root;
	bool dir_left = true;
	while(true) {
		if(*n == data) {
			cout << "deleting " << *n << " prev is " << *prev << endl;
			Node* bkup_left = n->getLeft();
			Node* bkup_right = n->getRight();
			Node* bkp = nullptr;
			n->disconnect();
			delete n;
			n = nullptr;
			cout << "node was deleted" << endl;

			unsigned int height_left = 0;
			unsigned int height_right = 0;
			
			if(bkup_left != nullptr)
				height_left = bkup_left->getHeight();
			if(bkup_right != nullptr)
				height_right = bkup_right->getHeight();
			
			if(bkup_right == nullptr && bkup_left == nullptr)
				return;

			if(height_left <= height_right) {
				cout << "right tree is deeper searching for smallest item" << endl;
				Node* min = bkup_right;
				Node* m_prev = prev;

				// minimum finden
				while(min->hasLeft()) {
					m_prev = min;
					//dir_left = true;
					min = min->getLeft();
				}

				bkp = min->getRight();
				m_prev->setLeft(nullptr);
				min->disconnect();
				cout << "deleted node is now smallest item of right tree" << endl;
				n = min;
			} else {
				cout << "left tree is deeper searching for biggest item" << endl;
				Node* max = bkup_left;
				Node* m_prev = prev;

				// maximum finden
				while(max->hasRight()) {
					m_prev = max;
					//dir_left = false;
					max = max->getRight();
				}
				
				bkp = max->getLeft();
				m_prev->setRight(nullptr);
				max->disconnect();
				cout << "deleted node is now biggest item of left tree" << endl;
				n = max;
			}
			/*if(dir_left)
				prev->setLeft(bkp);
			else
				prev->setRight(bkp);
			*/
			cout << "setting children of the node who replaces the deleted one" << endl;
			n->setLeft(bkup_left);
			cout << "left child is old left tree" << endl;
			n->setRight(bkup_right);
			cout << "right child is old right tree" << endl;
			cout << "setting link in parent node to current node" << endl;
			if(dir_left)
				prev->setLeft(n);
			else
				prev->setRight(n);
			cout << "done" << endl;
			return;
		} else if(data < *n) {
			prev = n;
			n = n->getLeft();
			dir_left = true;
		} else {
			prev = n;
			n = n->getRight();
			dir_left = false;
		}
		if(n == nullptr)
			throw logic_error("can't delete non existend value");
	}
}
bool Baum::contains(int data) {
	Node* n = root->getLeft();
	while(true) {
		if(*n == data)
			return true;
		if(*n < data) {
			if(n->hasLeft())
				n = n->getLeft();
			else
				return false;
		}
		if(*n > data) {
			if(n->hasRight())
				n = n->getRight();
			else
				return false;
		}	
	}
}
/*
Cursor Baum::get(int) {
	//TODO: implement Baum::get(int)
}*/
void* Baum::getRootNode() {
	return root->getLeft();
}
string Baum::getNodeName(void* node) {
	Node* n = (Node*)node;
	return to_string((int)*n);
}
string Baum::getNodeValue(void* node) {
	return getNodeName(node);
}
bool Baum::hasNodeValue(void* node) {
	return true;
}
vector<void*> Baum::getNodes(void* node) {
	Node* n = (Node*) node;
	vector<void*> v;
	if(n->hasLeft())
		v.push_back((void*) n->getLeft());
	if(n->hasRight())
		v.push_back((void*) n->getRight());
	return v;
}

Node::Node(int data) {
	left = nullptr;
	right = nullptr;
	this->data = data;
}
Node::~Node() {
	// it is ok to delete null pointers ;)
	if(left != nullptr)
		delete left;
	if(right != nullptr)
		delete right;
	left = right = nullptr;
}
void Node::disconnect() {
	left = right = nullptr;
}
Node::operator int() {
	return data;
}
void Node::setLeft(Node* left) {
	this->left = left;
}
void Node::setRight(Node* right) {
	this->right = right;
}
Node* Node::getLeft() {
	return left;
}
Node* Node::getRight() {
	return right;
}
bool Node::hasLeft() {
	return left!=nullptr;
}
bool Node::hasRight() {
	return right!=nullptr;
}
unsigned int Node::getHeight() {
	if(!hasLeft() && !hasRight())
		return 0;
	unsigned int h_left, h_right;
	h_left = h_right = 0;
	if(hasLeft())
		h_left = left->getHeight();
	if(hasRight())
		h_right = right->getHeight();
	if(h_left > h_right)
		return h_left+1;
	else
		return h_right+1;
}