/* grid.c -- provides a basic grid 'class' for mazes */

#include <assert.h>
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

#define TXBRAND_IMPLEMENTATION
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
	ASSERT_GRID(self);
	assert(row >= 0 && row < self->rows);
	assert(col >= 0 && col < self->cols);
	return row * self->cols + col;
}

/*
 * create a new empty grid of a particular size.
 */

grid *
create_grid(
	int rows,
	int cols
) {
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
			self->cells[index_of_cell(self, row, col)] = create_cell(row, col);
	}

	/* assign neighbors */
	for (int i = 0; i < self->num_cells; i++) {
		cell *curr = self->cells[i];
		int r = self->cells[i]->row;
		int c = self->cells[i]->col;
		curr->north = cell_in_grid_at(self, r-1, c);
		curr->east = cell_in_grid_at(self, r, c+1);
		curr->south = cell_in_grid_at(self, r+1, c);
		curr->west = cell_in_grid_at(self, r, c-1);
	}

	return self;
}

/*
 * release the grid and cells.
 */

grid *
destroy_grid(grid *self) {
	ASSERT_GRID(self);
	for (int i = 0; i < self->num_cells; i++)
		destroy_cell(self->cells[i]);
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
			cell *curr = cell_in_grid_at(self, row, col);
			char *east_boundary = linked_cell(curr, curr->east) ? "    " : "   |";
			sb_puts(top, east_boundary);
			char *south_boundary = linked_cell(curr,
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
cell_in_grid_at(grid *self, int row, int col) {
	ASSERT_GRID(self);
	if (row < 0 || row >= self->rows || col < 0 || col >= self->cols)
		return NULL;
	return self->cells[index_of_cell(self, row, col)];
}

/*
 * return a random cell from the grid.
 */

cell *
random_cell_in_grid(grid *self) {
	ASSERT_GRID(self);
	return self->cells[random_between(0, self->num_cells)];
}

/* grid.c ends here */
