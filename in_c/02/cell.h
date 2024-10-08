/* cell.h -- provides a basic cell class for maze grids */

#ifndef CELL_H
#define CELL_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

/*
 * a cell in a maze grid
 */

/* these macros (for various structures) validate pointer references. there are times
   that a null pointer might be valid, hence the assert-or-null variation.

   for reasons i don't understand, i can't get any variation of sizeof(something that
   gets the size of the tag field) to work, some error with an allegedly missing
   close paren. hard coding the length works. */

#define CELL_TAG "CELL"
#define CELL_TAG_LEN 4
#define ASSERT_CELL(p) assert((p) && memcmp((p), CELL_TAG, CELL_TAG_LEN) == 0)
#define ASSERT_CELL_OR_NULL(p) assert((p) == NULL || memcmp((p), CELL_TAG, CELL_TAG_LEN) == 0)

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
