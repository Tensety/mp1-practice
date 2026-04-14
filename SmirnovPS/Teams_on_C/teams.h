#ifndef TEAMS_H
#define TEAMS_H

typedef struct {
	char name[64];
	char city[64];
	int games_played;
	int points;
	int players;
} Team;

int team_amount(const char* file_name);
void read_file(int count, Team* teams, const char* file_name);
void find_winner(Team* teams, int count);

#endif