/*
 *******************************************************************************
 *
 * vdm_csv.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

#ifndef _RBTOOLS_CSV_H_
#define _RBTOOLS_CSV_H_

#include <vdm_pl_types.h>

typedef struct VDM_CSV_t VDM_CSV_t;

typedef struct VDM_CSV_line_t {
	struct VDM_CSV_line_t *next;
	char **cells;
	VDM_CSV_t *csv;
	int idx;
} VDM_CSV_line_t;

struct VDM_CSV_t {
	char *file;
	int flags;
	VDM_CSV_line_t *titles;
	VDM_CSV_line_t *lines;
	int lcount; /* Count lines */
	int ccount; /* Count cols */
};

#define CSV_FL_NO_HEADERS 0x0001
#define CSV_FL_ALWAYS_QUOTE 0x0004

/* Read from file and allocate structure */
VDM_CSV_t *VDM_CSV_read(const char *filename, int flags);

/* Read from buffer and allocate structure */
VDM_CSV_t *VDM_CSV_read_buf(char *buf, int flags);

/* Free csv structure. Does not write to file */
VDM_CSV_t **VDM_CSV_free(VDM_CSV_t **csv);

int VDM_CSV_write(VDM_CSV_t *csv, const char *filename);

/* Count */
int VDM_CSV_lines(VDM_CSV_t *csv);
int VDM_CSV_cols(VDM_CSV_t *csv);

/* Data */
char *VDM_CSV_title(VDM_CSV_t *csv, int idx);
VDM_CSV_line_t *VDM_CSV_line(VDM_CSV_t *csv, int idx);
VDM_CSV_line_t *VDM_CSV_add_line(VDM_CSV_t *csv);
void VDM_CSV_remove_line(VDM_CSV_t *csv, int idx);
char *VDM_CSV_value(VDM_CSV_line_t *l, int idx);
int VDM_CSV_value_int(VDM_CSV_line_t *l, int idx, int inDefault);
void VDM_CSV_set_value(VDM_CSV_line_t *l, int idx, const char *value);
int VDM_CSV_col_id(VDM_CSV_t *csv, const char *col);
IBOOL VDM_CSV_value_bool(VDM_CSV_line_t *l, int idx);

#endif

