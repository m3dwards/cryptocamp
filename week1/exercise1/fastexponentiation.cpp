#include <iostream>
#include <format>


int fastExponentiation(int base, int exponent) {
	if (exponent == 0) {
		return 1;
	}
	if (exponent % 2 == 0) {
		return fastExponentiation(base * base, exponent / 2);
	}
	return base * fastExponentiation(base, exponent - 1);
}

int main() {
	std::cout << "Welcome to Fast Exponentiation!" << std::endl;
	int base, exponent;
	std::cout << "Enter base: ";
	std::cin >> base;
	std::cout << "Enter exponent: ";
	std::cin >> exponent;
	int result = fastExponentiation(base, exponent);
	std::cout << std::format("{} ^ {} = {}", base, exponent, result) << std::endl;
}
