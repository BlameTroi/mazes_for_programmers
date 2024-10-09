/* cell.c -- provides a basic cell class for maze grids */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"

/*
 * create a new cell for position row, col in a grid.
 */

cell *
create_cell(int row, int col) {
	cell *self = malloc(sizeof(cell));
	memset(self, 0, sizeof(cell));
	memcpy(self->tag, CELL_TAG, sizeof(self->tag));
	self->row = row;
	self->col = col;
	self->north = NULL;
	self->east = NULL;
	self->south = NULL;
	self->west = NULL;
	for (int i = 0; i < 4; i++)
		self->links[i] = NULL;
	return self;
}

/*
 * link another cell to this cell in both cell's linked cells lists.
 * linked means the cells are connected, you can move from one to the
 * other.
 *
 * quietly returns if the other cell is already linked or is NULL.
 *
 * should these also be managed by directions like neighbors? the
 * ruby implementation is a bit off to me.
 */


cell *
link_cell(cell *self, cell *other, bool both) {
	ASSERT_CELL(self);
	ASSERT_CELL_OR_NULL(other);
	if (other == NULL)
		return self;
	int p = -1;
	for (int i = 0; i < 4; i++) {
		if (self->links[i] == other)
			return self;
		if (self->links[i] == NULL && p == -1)
			p = i;
	}
	self->links[p] = other;
	if (both)
		link_cell(other, self, false);
	return self;
}

/*
 * is there an open path from one cell to the other?
 */

bool
linked_cell(cell *self, cell *other) {
	ASSERT_CELL(self);
	ASSERT_CELL_OR_NULL(other);
	if (other == NULL)
		return false;
	for (int i = 0; i < 4; i++)
		if (other == self->links[i])
			return true;
	return false;
}
/*
 * unlink another cell from this cell in both cell's link lists.
 *
 * it is an error to attempt to unlink a cell that is not linked.
 */

cell *
unlink_cell(cell *self, cell *other, bool both) {
	ASSERT_CELL(self);
	ASSERT_CELL(other);
	int p = -1;
	for (int i = 0; i < 4; i++) {
		if (self->links[i] == other) {
			p = i;
			break;
		}
	}
	assert(p != -1);
	self->links[p] = NULL;
	if (both)
		unlink_cell(other, self, false);
	return self;
}

/*
 * return a null terminated list of any neighboring cells.
 * the caller must release this list.
 */

cell **
get_cell_neighbors(cell *self) {
	ASSERT_CELL(self);
	cell **list = malloc(sizeof(cell *) * 5);
	memset(list, 0, sizeof(cell *) * 5);
	int i = 0;
	if (self->north != NULL) {
		list[i] = self->north;
		i += 1;
	}
	if (self->east != NULL) {
		list[i] = self->east;
		i += 1;
	}
	if (self->south != NULL) {
		list[i] = self->south;
		i += 1;
	}
	if (self->west != NULL) {
		list[i] = self->west;
		i += 1;
	}
	return list;
}

/*
 * unlink any cells linked to this cell and then release this
 * cell's storage.
 */

cell *
destroy_cell(cell *self) {
	assert(self && memcmp(self->tag, CELL_TAG, 4) == 0);
	for (int i = 0; i < 4; i++) {
		if (self->links[i] != NULL) {
			unlink_cell(self, self->links[i], true);
			self->links[i] = NULL;
		}
	}
	memset(self, 253, sizeof(cell));
	free(self);
	return NULL;
}

/* cell.c ends here */
