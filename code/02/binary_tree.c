/* binary_tree.c -- create a maze by going either north or east from the current cell. */

/*
 * walk through all the cells in the passed grid and link one of the
 * north or east neighboring cells to the current cell. if there is no
 * such neighbor, no link is made.
 */

#include <stdbool.h>
#include <stddef.h>

#include "cell.h"
#include "grid.h"

#include "binary_tree.h"

#include "txbrand.h"

grid *
binary_tree_on(
	grid *grid
) {
	ASSERT_GRID(grid, "binary_tree_on not a grid");
	/* need an interator, but for now ... */
	for (int i = 0; i < grid->num_cells; i++) {
		cell *neighbors[3] = {NULL, NULL, NULL};
		int n = 0;
		if (grid->cells[i]->north != NULL) {
			neighbors[n] = grid->cells[i]->north;
			n += 1;
		}
		if (grid->cells[i]->east != NULL) {
			neighbors[n] = grid->cells[i]->east;
			n += 1;
		}
		if (n != 0) {
			int k = random_between(0, n-1);
			cell_link(grid->cells[i], neighbors[k], true);
		}
	}
	return grid;
}

/* binary_tree.c ends here */
