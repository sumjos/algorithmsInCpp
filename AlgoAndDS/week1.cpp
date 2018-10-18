#include "stdafx.h"
#include <iostream>

int w1p1() {
	int a = 0;
	int b = 0;
	std::cin >> a >> b;
	std::cout << a + b;
	return 0;
}

void w1p2() {
	long int count = 0, a = 0, b = 0, temp = 0;;

	std::cin >> count;
	while (count > 0) {
		std::cin >> temp;
		if (temp > a && a <= b) {
			a = temp;
		}
		else if (temp > b && b <= a) {
			b = temp;
		}
		count--;
	}
	std::cout << a * b;
}