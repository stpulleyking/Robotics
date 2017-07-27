//============================================================================
// Name        : Matrix.cpp
// Author      : Mateusz Fraszczynski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../include/matrix.h"

using namespace std;

void test(void);

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	test();
	return 0;
}

void test() {
	matrix Eva(1,2);
	//matrix Adam;

	cout << "Eva dimensionX: " << (int) Eva.verifyMatrixDimensionX() << " Eva dimensionY: " << (int) Eva.verifyMatrixDimensionY() << endl;
	//cout << "Adam dimensionX: " << (int) Adam.verifyMatrixDimensionX() << " Adam dimensionY: " << (int) Adam.verifyMatrixDimensionY() << endl;

	//cout << "Eva CapacityX: " << (int) Eva.verifyMatrixCapacityX() << " Eva CapacityY: " << (int) Eva.verifyMatrixCapacityY() << endl;
	//cout << "Adam CapacityX: " << (int) Adam.verifyMatrixCapacityX() << " Adam CapacityY: " << (int) Adam.verifyMatrixCapacityY() << endl;

	//Eva.addRow(5);
	Eva.addRow();
	Eva.addColumn();
	Eva.addRow();
	Eva.addColumn();
	//Eva.addColumn();
	//Eva.addColumn();
	//Adam.addColumn(7);
	int tab[3] = {4,5,6};
	Eva.fillRowWithData(tab, 1);
	cout << "Eva dimensionX: " << (int) Eva.verifyMatrixDimensionX() << " Eva dimensionY: " << (int) Eva.verifyMatrixDimensionY() << endl;
	//cout << "Adam dimensionX: " << (int) Adam.verifyMatrixDimensionX() << " Adam dimensionY: " << (int) Adam.verifyMatrixDimensionY() << endl;

	//cout << "Eva CapacityX: " << (int) Eva.verifyMatrixCapacityX() << " Eva CapacityY: " << (int) Eva.verifyMatrixCapacityY() << endl;
	//cout << "Adam CapacityX: " << (int) Adam.verifyMatrixCapacityX() << " Adam CapacityY: " << (int) Adam.verifyMatrixCapacityY() << endl;

}
