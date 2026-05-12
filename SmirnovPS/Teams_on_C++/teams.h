#ifndef TEAMS_H
#define TEAMS_H

#include <string>
#include <vector>

struct Team {
	std::string name;
	std::string city;
	int games_played;
	int points;
	int players;
};

std::vector<Team> read_file(const std::string& file_name);
std::vector<Team> find_winner(const std::vector<Team>& football);
void print_results(const std::vector<Team>& winners);

#endif