#ifndef TEAMS_H
#define TEAMS_H

#include <string>
#include <iostream>

class Team {
private:
	std::string name;
	std::string city;
	int games_played;
	int points;
	int players;

	friend class TeamList;
	friend std::ostream& operator << (std::ostream& out, const TeamList& list);

public:
	Team();
};

class TeamList {
private:
	int count;
	Team* teams;

public: 
	TeamList();
	TeamList(const std::string& file_name);
	TeamList(const TeamList& list);
	~TeamList();

	const TeamList& operator = (const TeamList& list);
	TeamList find_winner() const;
	friend std::ostream& operator << (std::ostream& out, const TeamList& list);
};

#endif
