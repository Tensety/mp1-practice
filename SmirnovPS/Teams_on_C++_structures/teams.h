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

struct TeamList {
	int count;
	Team* teams;

	TeamList();
	TeamList(const std::string& file_name);
	TeamList(const TeamList& list);
	~TeamList();

	const TeamList& operator = (const TeamList& list);
	TeamList find_winner() const;
	friend std::ostream& operator << (std::ostream& out, const TeamList& List);
};

#endif