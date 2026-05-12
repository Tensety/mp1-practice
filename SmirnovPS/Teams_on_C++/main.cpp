#include <iostream>
#include <vector>
#include "teams.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Incorrect number of arguments" << endl;
		return 1;
	}

	string file_name = argv[1];

	vector<Team> football = read_file(file_name);

	if (football.empty()) {
		cout << "No teams found!" << endl;
		return 1;
	}

	vector<Team> winners = find_winner(football);

	print_results(winners);

	return 0;
}