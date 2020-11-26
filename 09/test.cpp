#include <bitset>
#include <string>
#include <iostream>
int main(){
	std::bitset<10> a;
	a.set(2);
	std::cout << a.to_string() << "\n";
	return 0;
}