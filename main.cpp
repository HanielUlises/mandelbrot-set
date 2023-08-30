#include "mandelbrot.h"

int main(int argc, char* []) {
	std::cout << "Started program" << std::endl;
	std::cout << "Press escape to close the program" << std::endl;
	mandelbrot newSet;
	newSet.display();
	std::cout << "Closing program... ";


	return 0;
}