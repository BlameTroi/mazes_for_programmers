/* grid.c -- provides a basic grid 'class' for mazes */

#include "txbabort_if.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cell.h"
#include "grid.h"

#define TXBMISC_IMPLEMENTATION
#include "txbmisc.h"

#define TXBSB_IMPLEMENTATION
#include "txbsb.h"

#include "txbrand.h"

/*
 * map row and column to index in list of cells.
 */

static
int
index_of_cell(
	grid *self,
	int row,
	int col
) {
	ASSERT_GRID(self, "index_of_cell not a grid");
	abort_if(row < 0 || row >= self->rows, "index_of_cell out of bounds row");
	abort_if(col < 0 || col >= self->cols, "index_of_cell out of bounds col");
	return row * self->cols + col;
}

/*
 * create a new empty grid of a particular size.
 */

grid *
grid_create(
	int rows,
	int cols
) {
	if (rows < 1 || cols < 1)
		return NULL;

	grid *self = malloc(sizeof(grid));
	memset(self, 0, sizeof(grid));
	memcpy(self->tag, GRID_TAG, GRID_TAG_LEN);

	self->rows = rows;
	self->cols = cols;
	self->num_cells = self->rows * self->cols;

	/* space for all the cells */
	self->cells = malloc(self->num_cells *sizeof(cell *));
	memset(self->cells, 0, self->num_cells *sizeof(cell *));

	/* create all the cells at first */
	for (int row = 0; row < self->rows; row++) {
		for (int col = 0; col < self->cols; col++)
			self->cells[index_of_cell(self, row, col)] = cell_create(row, col);
	}

	/* assign neighbors */
	for (int i = 0; i < self->num_cells; i++) {
		cell *curr = self->cells[i];
		int r = self->cells[i]->row;
		int c = self->cells[i]->col;
		curr->north = grid_cell_at(self, r-1, c);
		curr->east = grid_cell_at(self, r, c+1);
		curr->south = grid_cell_at(self, r+1, c);
		curr->west = grid_cell_at(self, r, c-1);
	}

	return self;
}

/*
 * release the grid and cells.
 */

grid *
grid_destroy(grid *self) {
	ASSERT_GRID(self, "destroy_grid not a grid");
	for (int i = 0; i < self->num_cells; i++)
		cell_destroy(self->cells[i]);
	memset(self, 253, sizeof(grid));
	free(self);
	return NULL;
}

/*
 * a string representation of a grid, printable.
 */

const char *
grid_to_string(
	grid *self
) {
	sbcb *sb = sb_create_string("+");
	for (int col = 0; col < self->cols; col++)
		sb_puts(sb, "---+");
	sb_putc(sb, '\n');

	for (int row = 0; row < self->rows; row++) {
		sbcb *top = sb_create_string("|");
		sbcb *bottom = sb_create_string("+");
		for (int col = 0; col < self->cols; col++) {
			cell *curr = grid_cell_at(self, row, col);
			char *east_boundary = cell_linked_p(curr, curr->east) ? "    " : "   |";
			sb_puts(top, east_boundary);
			char *south_boundary = cell_linked_p(curr,
					curr->south) ? "   +" : "---+";
			sb_puts(bottom, south_boundary);
		}
		sb_puts(sb, sb_to_string(top));
		sb_putc(sb, '\n');
		sb_puts(sb, sb_to_string(bottom));
		sb_putc(sb, '\n');
		sb_destroy(top);
		sb_destroy(bottom);
	}

	const char *res = sb_to_string(sb);
	sb_destroy(sb);
	return res;
}

/*
 * return the cell at a location in the grid. if the location is
 * out of bounds, returns NULL.
 */

cell *
grid_cell_at(grid *self, int row, int col) {
	ASSERT_GRID(self, "cell_in_grid_at not a grid");
	if (row < 0 || row >= self->rows || col < 0 || col >= self->cols)
		return NULL;
	return self->cells[index_of_cell(self, row, col)];
}

/*
 * return a random cell from the grid.
 */

cell *
grid_random_cell(grid *self) {
	ASSERT_GRID(self, "random_cell_in_grid not a grid");
	return self->cells[random_between(0, self->num_cells)];
}

/* grid.c ends here */
