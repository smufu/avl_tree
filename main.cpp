#include <iostream>
#include <fstream>
#include "baum.hpp"
#include "writer.hpp"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char const *argv[])
{
	Baum b;
	b.insert(5);
	for(int i=0;i<10;i++)
		if(i==5) continue;
		else b.insert(i);


	Writer w(b);
	w.dump();

	b.remove(5);
	w.dump();
	b.remove(1);
	cout << "ok" << endl;
	w.dump();
	ofstream ofdot("tree.dot");
	w.writeDot(ofdot);
	system("dot -Tpng tree.dot -o tree.png");
	//system("ristretto tree.png 2>/dev/null");

	return 0;
}