#include <stdio.h>
#include <stdlib.h>
#include "teams.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Incorrent number of arguments");
		return 1;
	}

	TeamList* football = NULL;
	const char* file_name = argv[1];

	football = malloc(sizeof(TeamList));
	football->count = team_amount(file_name);
	football->teams = malloc(football->count * sizeof(Team));

	read_file(football, file_name);

	TeamList* winners = find_winner(football);

	print_results(winners);

	free(winners->teams);
	free(winners);
	free(football->teams);
	free(football);

	return 0;
}