#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "teams.h"

using namespace std;

vector<Team> read_file(const string& file_name) {
	vector<Team> football;
	ifstream file(file_name);

	if (!file.is_open()) {
		cout << "Didn't find file: " << file_name << endl;
		return football;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string temp;
		Team t;

		if (getline(ss, t.name, ';') &&
			getline(ss, t.city, ';') &&
			getline(ss, temp, ';'))  t.games_played = stoi(temp); 
		if (getline(ss, temp, ';'))  t.points = stoi(temp);
		if (getline(ss, temp, ';'))  t.players = stoi(temp);

		football.push_back(t);
	}

	file.close();
	return football;
}

vector<Team> find_winner(const vector<Team>& football) {
	vector<Team> winners;
	int mx = football[0].points;

	for (int i = 1; i < football.size(); i++)
		if (football[i].points > mx)
			mx = football[i].points;


	for (int i = 0; i < football.size(); i++)
		if (football[i].points == mx)
			winners.push_back(football[i]);

	return winners;
}

void print_results(const vector<Team>& winners) {
	if (winners.size() == 1) 
		cout << "WINNER: "
			<< winners[0].name << "; "
			<< winners[0].city << "; "
			<< winners[0].games_played << "; "
			<< winners[0].points << "; "
			<< winners[0].players << ";" << endl;
	else {
		cout << "WINNERS:" << endl;
		for (int i = 0; i < winners.size(); i++) {
			cout << i + 1 << "."
				<< winners[i].name << "; "
				<< winners[i].city << "; "
				<< winners[i].games_played << "; "
				<< winners[i].points << "; "
				<< winners[i].players << ";" << endl;
		}
	}
}