#include <iostream>
#include "container.h"

using namespace std;

int main() {
	try {
		int step; cin >> step;
		int* a1 = new int(1);
		int* a2 = new int(2);
		int* a3 = new int(3);
		Container<int*> c(1, step);
		c.push(a2);
		c.push(a1);
		cout << c << endl;
		cout << c.find(a3) << "\n";
		c.remove(a1);
		cout << c << endl;
		Container<int> t(10, step);
		t.push(76); t.push(99); t.push(6354); t.push(111); t.push(14122007);
		cout << t << endl;
		Container<int> z(15, step + 15);
		z.push(67); z.push(76); z.push(2222);
		Container<Container<int>*> C(10, step);
		C.push(&t); C.push(&z);
		cout << C << endl;
	}
	catch (const exception& ex) {
		cout << ex.what() << endl;
	}
	return 0;
}