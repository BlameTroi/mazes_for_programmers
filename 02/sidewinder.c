/* sidewinder.c -- create a maze using the sidewinder approach */

/*
 * walk through all the cells in the passed grid and link neighboring
 * cells using the sidewinder algorithm.
 */

#include <stdbool.h>
#include <stddef.h>

#include "cell.h"
#include "grid.h"
#include "txbrand.h"

grid *
sidewinder_on(grid *grid) {
	ASSERT_GRID(grid);
	cell *run[grid->rows * grid->cols + 1];
	for (int row = 0; row < grid->rows; row++) {
		memset(run, 0, sizeof(run));
		int cells = 0;
		for (int col = 0; col < grid->cols; col++) {
			cell *curr = cell_in_grid_at(grid, row, col);
			run[cells] = curr;
			cells += 1;
			bool at_eastern_boundary = curr->east == NULL;
			bool at_northern_boundary = curr->north == NULL;
			bool should_close_out =
				at_eastern_boundary ||
				(!at_northern_boundary && random_between(0, 1) == 0);
			if (should_close_out) {
				cell *member = run[random_between(0, cells-1)];
				link_cell(member, member->north, true);
				memset(run, 0, sizeof(run));
				cells = 0;
			} else
				link_cell(curr, curr->east, true);
		}
	}
	return grid;
}

/* sidewinder.c ends here */
