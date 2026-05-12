#ifndef TEAMS_H
#define TEAMS_H

#define MAX_LEN 64

typedef struct {
	char name[MAX_LEN];
	char city[MAX_LEN];
	int games_played;
	int points;
	int players;
} Team;

typedef struct {
	int count;
	Team* teams;
} TeamList;

int team_amount(const char* file_name);
void read_file(TeamList* football, const char* file_name);
TeamList* find_winner(TeamList* football);
void print_results(TeamList* winners);

#endif