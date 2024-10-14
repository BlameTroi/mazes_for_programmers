/* grid.h -- provides a basic grid 'class' for mazes */

#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "txbabort_if.h"

#include "cell.h"

#define GRID_TAG "GRID"
#define GRID_TAG_LEN 4
#define ASSERT_GRID(p, m) \
	abort_if(!(p) || memcmp((p), GRID_TAG, GRID_TAG_LEN) != 0, (m))
#define ASSERT_GRID_OR_NULL(p, m) \
	abort_if((p) && memcmp((p), GRID_TAG, GRID_TAG_LEN) != 0, (m))

/* a grid holds cells */
typedef struct grid grid;
struct grid {
	char tag[4];
	int rows;
	int cols;
	int num_cells;
	cell **cells;
};

/*
 * create a new empty grid.
 */

grid *
grid_create(
	int rows,
	int cols
);

/*
 * release grid resources.
 */

grid *
grid_destroy(
	grid *self
);

/*
 * return a specific cell from the grid.
 */

cell *
grid_cell_at(
	grid *self,
	int row,
	int col
);

/*
 * return a random cell from the grid.
 */

cell *
grid_random_cell(
	grid *self
);

/*
 * string representation of the grid.
 */

const char *
grid_to_string(
	grid *self
);

#endif /* GRID_H */
/* grid.h ends here */
