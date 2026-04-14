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


void read_file(int count, Team* teams, char* file_name) {
	char buf[2048];
	FILE* file = fopen(file_name, "r");

	int i;
	for (i = 0; i < count; i++) {
		fgets(buf, sizeof(buf), file);
		buf[strcspn(buf, "\n")] = "\0";

		char* next_token = NULL;

		strcpy(teams[i].name, strtok_s(buf, ";", &next_token));
		strcpy(teams[i].city, strtok_s(NULL, ";", &next_token));
		teams[i].games_played = atoi(strtok_s(NULL, ";", &next_token));
		teams[i].points = atoi(strtok_s(NULL, ";", &next_token));
		teams[i].players = atoi(strtok_s(NULL, ";", &next_token));
	}
	fclose(file);
}


void find_winner(Team* teams, int count) {
	int i, j, mx = 0;
	for (i = 0; i < count - 1; i++) {
		mx = i;

		for (j = i + 1; j < count; j++)
			if (teams[j].points > teams[mx].points)
				mx = j;

		if (mx != i) {
			Team temp = teams[i];
			teams[i] = teams[mx];
			teams[mx] = temp;
		}
	}

	printf("\nWINNER: 1. %s; %s; %d; %d; %d\n\n",
		teams[0].name,
		teams[0].city,
		teams[0].games_played,
		teams[0].points,
		teams[0].players
	);

	for (i = 1; i < count; i++)
		printf("%d. %s; %s; %d; %d; %d\n",
			i + 1,
			teams[i].name,
			teams[i].city,
			teams[i].games_played,
			teams[i].points,
			teams[i].players
		);
}