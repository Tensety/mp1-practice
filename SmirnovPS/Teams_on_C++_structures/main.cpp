#include <iostream>
#include "teams.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Incorrect number of arguments" << endl;
		return 1;
	}

	TeamList football(argv[1]);

	TeamList winners;
	winners = football.find_winner();

	cout << winners;
	return 0;
}