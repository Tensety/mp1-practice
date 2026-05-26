#include <iostream>
#include <fstream>
#include <sstream>
#include "teams.h"

using namespace std;

Team::Team() {
	this->games_played = 0;
	this->points = 0;
	this->players = 0;
}

TeamList::TeamList() {
	this->count = 0;
	this->teams = nullptr;
}

TeamList::TeamList(const string& file_name) {
	this->count = 0;
	this->teams = nullptr;

	ifstream file(file_name);
	if (!file.is_open()) {
		cout << "Didn't find file: " << file_name << endl;
		return;
	}

	string line;
	while (getline(file, line))
		if (!line.empty())
			this->count++;

	if (this->count == 0) return;
	this->teams = new Team[this->count];

	file.clear();
	file.seekg(0);

	for (int i = 0; i < this->count; i++) {
		getline(file, line);
		stringstream ss(line);
		string temp;

		if (getline(ss, this->teams[i].name, ';') &&
			getline(ss, this->teams[i].city, ';') &&
			getline(ss, temp, ';')) {
			this->teams[i].games_played = stoi(temp);
		}
		if (getline(ss, temp, ';')) { this->teams[i].points = stoi(temp); }
		if (getline(ss, temp, ';')) { this->teams[i].players = stoi(temp); }
	}
	file.close();
}

TeamList::~TeamList() {
	delete[] this->teams;
}

TeamList::TeamList(const TeamList& list) {
	this->count = list.count;
	if (this->count != 0) {
		this->teams = new Team[this->count];
		for (int i = 0; i < this->count; i++)
			this->teams[i] = list.teams[i];
	}
	else
		this->teams = nullptr;
}

const TeamList& TeamList::operator = (const TeamList& list) {
	if (this == &list)
		return *this;

	delete[] this->teams;

	this->count = list.count;
	if (this->count > 0) {
		this->teams = new Team[this->count];
		for (int i = 0; i < this->count; i++)
			this->teams[i] = list.teams[i];
	}
	else
		this->teams = nullptr;
	return *this;
}

TeamList TeamList::find_winner() const {
	TeamList winners;
	if (this->count == 0) return winners;

	int win_count = 0, mx = this->teams[0].points;

	for (int i = 1; i < this->count; i++)
		if (this->teams[i].points > mx) { mx = this->teams[i].points; }

	for (int i = 0; i < this->count; i++)
		if (this->teams[i].points == mx) { win_count++; }

	winners.count = win_count;
	winners.teams = new Team[winners.count];

	int j = 0;
	for (int i = 0; i < this->count; i++) {
		if (this->teams[i].points == mx) {
			winners.teams[j] = this->teams[i];
			j++;
		}
	}

	return winners;
}

ostream& operator << (ostream& out, const TeamList& list) {
	if (list.count == 1)
		out << "WINNER: "
		<< list.teams[0].name << "; "
		<< list.teams[0].city << "; "
		<< list.teams[0].games_played << "; "
		<< list.teams[0].points << "; "
		<< list.teams[0].players << ";" << endl;
	else {
		out << "WINNERS:" << endl;
		for (int i = 0; i < list.count; i++)
			out << i + 1 << "."
			<< list.teams[i].name << "; "
			<< list.teams[i].city << "; "
			<< list.teams[i].games_played << "; "
			<< list.teams[i].points << "; "
			<< list.teams[i].players << ";" << endl;
	}
	return out;
}