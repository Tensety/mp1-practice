#include <stdio.h>
#include <stdlib.h>
#include "teams.h"

int main() {
	char file_name[64];
	printf("Enter file name: ");
	scanf("%s", file_name);
	int count = team_amount(file_name);

	Team* teams = (Team*)malloc(count * sizeof(Team));
	read_file(count, teams, file_name);

	find_winner(teams, count);

	free(teams);

	return 0;
}