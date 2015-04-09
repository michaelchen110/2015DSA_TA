#include <iostream>

using namespace std;

int &sub(int &a, int &b) {
	int c = a - b;
	return c;
}

void func(){
		
}

int main(){
	int a = 10;
	int b = 5;
	int x = 9;
	int y = 7;
	int &c = sub(a, b);
	cout << c << endl;
	int &d = sub(x, y);
	cout << c << endl;
	func();
	cout << c << endl;
}
