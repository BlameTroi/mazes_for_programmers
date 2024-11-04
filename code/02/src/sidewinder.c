/* sidewinder.c -- create a maze using the sidewinder approach */

/*
 * walk through all the cells in the passed grid and link neighboring
 * cells using the sidewinder algorithm.
 *
 * sidewinder traverses the grid starting at the south western corner
 * of the grid, linking horizontal runs of cells moving eastward (50%
 * chance) until either the eastern boundary is reached or a move
 * northward is rolled (50% chance).
 *
 * this closes the run. once cell in the run is picked at random and
 * linked to its northern neighbor. while this cell is linked, it is
 * not considered to have been visited.
 *
 * sidewinder advances to the next cell to the east of the end of the
 * run unless it is at the boundary, then it moves to the western most
 * cell of the next row to the north.
 *
 * this continues until the north eastern cornder of the grid is
 * reached.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"
#include "grid.h"

#include "sidewinder.h"

#include "txbrand.h"

grid *
sidewinder_on(grid *grid) {
	ASSERT_GRID(grid, "sidewinder_on not a grid");
	cell **run = malloc((grid->rows * grid->cols + 1) * sizeof(cell));
	for (int row = 0; row < grid->rows; row++) {
		memset(run, 0, (grid->rows * grid->cols + 1) * sizeof(cell));
		int cells = 0;
		for (int col = 0; col < grid->cols; col++) {
			cell *curr = grid_cell_at(grid, row, col);
			run[cells] = curr;
			cells += 1;
			bool at_eastern_boundary = curr->east == NULL;
			bool at_northern_boundary = curr->north == NULL;
			bool should_close_out = at_eastern_boundary ||
			(!at_northern_boundary && random_between(0, 1) == 0);
			if (should_close_out) {
				cell *member = run[random_between(0, cells-1)];
				cell_link(member, member->north, true);
				memset(run, 0, (grid->rows * grid->cols + 1) * sizeof(cell));
				cells = 0;
			} else
				cell_link(curr, curr->east, true);
		}
	}
	free(run);
	return grid;
}

/* sidewinder.c ends here */
