/* sidewinder_demo.c -- create a maze using the sidewinder approach. */

/*
 * creates a maze using the sidewinder algorithm. optional
 * parameters are rows columns and a switch to use a true
 * random number generator instead of rand().
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"
#include "sidewinder.h"

#include "txbrand.h"

void
usage(
	int argc,
	char **argv,
	char *errmsg
) {
	fprintf(stderr, "\ngenerate and display a maze map.\nusage:\n\n");
	fprintf(stderr, "%s [rows columns] [-r]\n\n", argv[0]);
	fprintf(stderr, "where optional [rows columns] are the maze dimensions.\n");
	fprintf(stderr, "and optional [-r] uses a non-deterministic random number\n");
	fprintf(stderr, "generator instead of the default rand().\n");
	if (errmsg)
		fprintf(stderr, "\nerror: %s\n\n", errmsg);
}

bool
any_help_argument(
	int argc,
	char **argv
) {
	for (int i = 1; i < argc; i++)
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
			return true;
	return false;
}

bool
handle_arguments(
	int argc,
	char **argv,
	int *rows,
	int *cols,
	int *gen
) {
	if (argc == 1)
		return true;

	if (argc > 4 || any_help_argument(argc, argv)) {
		usage(argc, argv, NULL);
		return false;
	}

	if (argc == 2 || argc == 4) {
		if (strcmp(argv[argc - 1], "-r") == 0)
			*gen = RAND_RANDOM;
		else {
			char errmsg[256];
			snprintf(errmsg, 256, "unknown argument '%s'", argv[argc - 1]);
			usage(argc, argv, errmsg);
			return false;
		}
	}

	if (argc == 2)
		return true;

	char *scan_row = NULL;
	char *scan_col = NULL;
	*rows = strtol(argv[1], &scan_row, 10);
	*cols = strtol(argv[2], &scan_col, 10);
	if (scan_row == argv[1] || scan_row[0] != '\0' ||
	scan_col == argv[2] || scan_col[0] != '\0') {
		char errmsg[256];
		snprintf(errmsg, 256, "arguments must be row and column counts, found '%s %s'",
			argv[1], argv[2]);
		usage(argc, argv, errmsg);
		return false;
	}

	return true;
}

int
main(
	int argc,
	char **argv
) {
	int rows = 8;
	int cols = 8;
	int gen = RAND_DEFAULT;

	if (!handle_arguments(argc, argv, &rows, &cols, &gen))
		return EXIT_FAILURE;

	set_random_generator(gen);
	grid *grid = grid_create(rows, cols);
	sidewinder_on(grid);
	char *s = grid_to_string(grid);
	printf("\n%s\n", s);
	free(s);
	grid_destroy(grid);

	return EXIT_SUCCESS;
}

/* sidewinder_demo.c ends here */
