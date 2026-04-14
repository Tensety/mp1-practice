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
void find_winner(std::vector<Team>& teams);

#endif