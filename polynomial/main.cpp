#include <iostream>
#include <string>
#include "linked_LS.hpp"
#include "polynomial.hpp"

int main (int argc, char *argv[]) {
	polynomial ls("3z^2+3x^9-3x^5");
	std::cout<<"\n"<<ls;

	return 0;
}
