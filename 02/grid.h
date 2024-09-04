/* grid.h -- provides a basic grid 'class' for mazes */

#ifndef GRID_H
#define GRID_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "cell.h"

#define GRID_TAG "CELL"
#define GRID_TAG_LEN 4
#define ASSERT_GRID(p) assert((p) && memcmp((p), GRID_TAG, GRID_TAG_LEN) == 0)
#define ASSERT_GRID_OR_NULL(p) assert((p) == NULL || memcmp((p), GRID_TAG, GRID_TAG_LEN) == 0)

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
create_grid(
	int rows,
	int cols
);

/*
 * release grid resources.
 */

grid *
destroy_grid(
	grid *self
);

/*
 * return a specific cell from the grid.
 */

cell *
cell_in_grid_at(
	grid *self,
	int row,
	int col
);

/*
 * return a random cell from the grid.
 */

cell *
random_cell_in_grid(
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
