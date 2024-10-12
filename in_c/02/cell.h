/* cell.h -- provides a basic cell class for maze grids */

#ifndef CELL_H
#define CELL_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "txbabort_if.h"

/*
 * a cell in a maze grid
 */

#define CELL_TAG "CELL"
#define CELL_TAG_LEN 4
#define ASSERT_CELL(p, m) \
	abort_if(!(p) || memcmp((p), CELL_TAG, CELL_TAG_LEN) != 0, (m))
#define ASSERT_CELL_OR_NULL(p, m) \
	abort_if((p) && memcmp((p), CELL_TAG, CELL_TAG_LEN) != 0, (m))

typedef struct cell cell;
struct cell {
	char tag[CELL_TAG_LEN];
	int row;
	int col;
	cell *north;
	cell *east;
	cell *south;
	cell *west;
	cell *links[4]; /* n e s w */
};

/*
 * create a new cell instance
 */

cell *
create_cell(
	int row,
	int col
);

/*
 * link connected adjacent cells
 */

cell *
link_cell(
	cell *self,
	cell *other,
	bool both
);

/*
 * unlink (disconnect) adjacent cells
 */

cell *
unlink_cell(
	cell *self,
	cell *other,
	bool both
);

/*
 * are these cells linked?
 */

bool
linked_cell(
	cell *self,
	cell *other
);

/*
 * release a cell's storage and links
 */

cell *
destroy_cell(
	cell *self
);

#endif /* CELL_H */
/* cell.h ends here */
