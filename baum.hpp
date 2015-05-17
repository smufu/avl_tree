#ifndef _BAUM
#define _BAUM
#include "plotable.hpp"
#include <string>
#include <vector>
using namespace std;

class Node {
private:
	Node* left;
	Node* right;
	int data;
public:
	Node(int);
	~Node();
	void disconnect();
	operator int();
	void setLeft(Node*);
	void setRight(Node*);
	Node* getLeft();
	Node* getRight();
	bool hasLeft();
	bool hasRight();
	unsigned int getHeight();
};
class Cursor;
class Baum: virtual public Plotable {
private:
	Node* root;
	void rotate(Node*&, bool left);
public:
	Baum();  // non virtual sp don't extend this class!
	~Baum(); // non virtual so don't extend this class!
	void insert(int);
	
	/**
	 * @brief removes value from tree
	 * @param i value to be removed
	 */
	void remove(int i);
	/**
	 * @brief checks if tree contains given element
	 * @param i value to search for
	 * @return true if i was found else flase
	 */
	bool contains(int i);
	//Cursor get(int);
	virtual void* getRootNode();
	virtual string getNodeName(void*);
	virtual string getNodeValue(void*);
	virtual bool hasNodeValue(void* node);
	virtual vector<void*> getNodes(void* node);
};

class Cursor {
private:
	//Node n*
	bool left;
public:
	void getData() {
	}
	void setData(int data) {

	}
};
#endif