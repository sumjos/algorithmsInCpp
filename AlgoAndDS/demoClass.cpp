#include "stdafx.h"
#include <iostream>
#include "SelfStudyFunctions.h"

void demoClass::printVal() {
	std::cout << "Value = " << n << "\n";
}

demoClass::demoClass() {
	n = 2;
}