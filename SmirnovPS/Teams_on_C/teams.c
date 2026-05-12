#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"

int team_amount(const char* file_name) {
	char buf[2048];
	int count = 0;

	FILE* file = fopen(file_name, "r");
	if (!file) {
		printf("Didn't find file: %s\n", file_name);
		return 1;
	}

	while (fgets(buf, sizeof(buf), file) != NULL)
		count++;

	fclose(file);
	return count;
}


void read_file(TeamList* football, const char* file_name) {
	char buf[2048];
	int i;
	FILE* file = fopen(file_name, "r");

	if (!file) {
		printf("Didn't find file: %s\n", file_name);
		return 1;
	}

	for (i = 0; i < football->count; i++) {
		char* next_token = NULL;
		fgets(buf, sizeof(buf), file);
		buf[strcspn(buf, "\n")] = "\0";
		strcpy(football->teams[i].name, strtok_s(buf, ";", &next_token));
		strcpy(football->teams[i].city, strtok_s(NULL, ";", &next_token));
		football->teams[i].games_played = atoi(strtok_s(NULL, ";", &next_token));
		football->teams[i].points = atoi(strtok_s(NULL, ";", &next_token));
		football->teams[i].players = atoi(strtok_s(NULL, ";", &next_token));
	}
	fclose(file);
}


TeamList* find_winner(TeamList* football) {
	int i, j = 0, count_win = 0, mx = football->teams[0].points;
	
	for (i = 1; i < football->count; i++)
		if (football->teams[i].points > mx)
			mx = football->teams[i].points;

	for (i = 0; i < football->count; i++)
		if (football->teams[i].points == mx)
			count_win++;

	TeamList* winners = malloc(sizeof(TeamList));
	winners->teams = malloc(count_win * sizeof(Team));
	winners->count = count_win;

	for (i = 0; i < football->count; i++) {
		if (football->teams[i].points == mx) {
			strcpy(winners->teams[j].name, football->teams[i].name);
			strcpy(winners->teams[j].city, football->teams[i].city);
			winners->teams[j].games_played = football->teams[i].games_played;
			winners->teams[j].points = football->teams[i].points;
			winners->teams[j].players = football->teams[i].players;
			j++;
		}
	}

	return winners;
}

void print_results(TeamList* winners) {
	int i;
	if (winners->count == 1)
		printf("WINNER: %s; %s; %d; %d; %d;\n\n",
			winners->teams[0].name,
			winners->teams[0].city,
			winners->teams[0].games_played,
			winners->teams[0].points,
			winners->teams[0].players
		);
	else {
		printf("WINNERS:\n");
		for (i = 0; i < winners->count; i++)
			printf("%d. %s; %s; %d; %d; %d;\n",
				i + 1,
				winners->teams[i].name,
				winners->teams[i].city,
				winners->teams[i].games_played,
				winners->teams[i].points,
				winners->teams[i].players
			);
	}
}