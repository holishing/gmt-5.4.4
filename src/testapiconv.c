/*--------------------------------------------------------------------
 *	$Id: testapiconv.c 19521 2017-12-27 22:38:24Z pwessel $
 *
 *	Copyright (c) 1991-2018 by P. Wessel, W. H. F. Smith, R. Scharroo, J. Luis and F. Wobbe
 *	See LICENSE.TXT file for copying and redistribution conditions.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation; version 3 or any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	Contact info: gmt.soest.hawaii.edu
 *--------------------------------------------------------------------*/
/*
 * Author:	Paul Wessel
 * Date:	7-JUN-2016
 * Version:	5 API
 *
 * Brief synopsis: testapiconv tests GMT_Convert_Data function.
 *
 */

#include "gmt_dev.h"
#include <string.h>

int main (int argc, char *argv[]) {
	unsigned int n = 0;
	void *API = NULL;
	struct GMT_DATASET *D = NULL, *D2 = NULL;
	struct GMT_TEXTSET *T = NULL;
	struct GMT_MATRIX *M = NULL;
	struct GMT_VECTOR *V = NULL;
	struct GMT_GRID **G = NULL;
	struct GMT_PALETTE **C = NULL;
	struct GMT_POSTSCRIPT **P = NULL;
	unsigned int flag[3] = {0, 0, 0};
	gmt_M_unused(argc);
	/*----------------------- Standard module initialization and parsing ----------------------*/

	/* 0. Initializing new GMT session */
	if ((API = GMT_Create_Session (argv[0], 2U, GMT_SESSION_NORMAL, NULL)) == NULL) exit (EXIT_FAILURE);

	/* Test reading several grid headers */
	
	if ((G = GMT_Read_Group (API, GMT_IS_GRID, GMT_IS_FILE, GMT_IS_SURFACE, GMT_CONTAINER_ONLY, NULL, "*.nc", &n, NULL)) == NULL) exit (EXIT_FAILURE);
	/* Then read grid data */
	if ((G = GMT_Read_Group (API, GMT_IS_GRID, GMT_IS_FILE, GMT_IS_SURFACE, GMT_DATA_ONLY, NULL, "*.nc", NULL, G)) == NULL) exit (EXIT_FAILURE);
	if (GMT_Destroy_Group (API, &G, n) != GMT_NOERROR) exit (EXIT_FAILURE);
	/* Test reading several CPTs */
	n = 0;
	if ((C = GMT_Read_Group (API, GMT_IS_PALETTE, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL, NULL, "*.cpt", &n, NULL)) == NULL) exit (EXIT_FAILURE);
	if (GMT_Destroy_Group (API, &C, n) != GMT_NOERROR) exit (EXIT_FAILURE);
#if 0
	/* Test reading several image files but allow for this to fail due to GDAL etc */
	n = 0;
	if ((I = GMT_Read_Group (API, GMT_IS_IMAGE, GMT_IS_FILE, GMT_IS_SURFACE, GMT_READ_NORMAL, NULL, "*.png", &n, NULL)) != NULL) {
	if (GMT_Destroy_Group (API, &I, n) != GMT_NOERROR) exit (EXIT_FAILURE);
	}
#endif
	/* Test reading several Postscript files */
	n = 0;
	if ((P = GMT_Read_Group (API, GMT_IS_POSTSCRIPT, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL, NULL, "*.ps", &n, NULL)) == NULL) exit (EXIT_FAILURE);
	if (GMT_Destroy_Group (API, &P, n) != GMT_NOERROR) exit (EXIT_FAILURE);
	
	/* 1. Read in two data tables; this DATASET is our starting point */

	if ((D = GMT_Read_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_READ_NORMAL, NULL, "[AB].txt", NULL)) == NULL) exit (EXIT_FAILURE);
	
	/* 2. Convert to textset with different modes.  First default mode */
	if ((T = GMT_Convert_Data (API, D, GMT_IS_DATASET, NULL, GMT_IS_TEXTSET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to text */
	if (GMT_Write_Data (API, GMT_IS_TEXTSET, GMT_IS_FILE, GMT_IS_NONE, GMT_WRITE_SET, NULL, "AB_txt.txt", T) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
		/* Convert back to dataset with different modes and save */
		if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
		if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "AB_data.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
		flag[2] = GMT_WRITE_TABLE; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
		if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "AB_dataT.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
		flag[2] = GMT_WRITE_SEGMENT; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
		if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "AB_dataS.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
		flag[2] = GMT_WRITE_TABLE_SEGMENT; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
		if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "AB_dataTS.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
		/* Write a matrix */
		flag[0] = 3; flag[2] = 0; if ((M = GMT_Convert_Data (API, D, GMT_IS_DATASET, NULL, GMT_IS_MATRIX, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to matrix */
		if (GMT_Write_Data (API, GMT_IS_MATRIX, GMT_IS_FILE, GMT_IS_POINT, GMT_WRITE_SET, NULL, "AB_dataM.txt", M) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
		/* Write a vector */
		if ((V = GMT_Convert_Data (API, D, GMT_IS_DATASET, NULL, GMT_IS_VECTOR, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to vector */
		if (GMT_Write_Data (API, GMT_IS_VECTOR, GMT_IS_FILE, GMT_IS_POINT, GMT_WRITE_SET, NULL, "AB_dataV.txt", V) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */

	memset (flag, 0, 3*sizeof(unsigned int));
	/* Now use  GMT_WRITE_TABLE */
	flag[2] = GMT_WRITE_TABLE; if ((T = GMT_Convert_Data (API, D, GMT_IS_DATASET, NULL, GMT_IS_TEXTSET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to text */
	if (GMT_Write_Data (API, GMT_IS_TEXTSET, GMT_IS_FILE, GMT_IS_NONE, GMT_WRITE_SET, NULL, "AB_txtT.txt", T) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	/* Convert back to dataset with different modes and save */
	flag[2] = 0; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "T_AB_data.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_TABLE; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "T_AB_dataT.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_SEGMENT; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "T_AB_dataS.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_TABLE_SEGMENT; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "T_AB_dataTS.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	
	memset (flag, 0, 3*sizeof(unsigned int));
	/* Now use  GMT_WRITE_SEGMENT */
	flag[2] = GMT_WRITE_SEGMENT; if ((T = GMT_Convert_Data (API, D, GMT_IS_DATASET, NULL, GMT_IS_TEXTSET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to text */
	if (GMT_Write_Data (API, GMT_IS_TEXTSET, GMT_IS_FILE, GMT_IS_NONE, GMT_WRITE_SET, NULL, "AB_txtS.txt", T) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	/* Convert back to dataset with different modes and save */
	flag[2] = 0; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "S_AB_data.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_TABLE; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "S_AB_dataT.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_SEGMENT; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "S_AB_dataS.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_TABLE_SEGMENT; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "S_AB_dataTS.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */

	memset (flag, 0, 3*sizeof(unsigned int));
	/* Now use  GMT_WRITE_TABLE_SEGMENT */
	flag[2] = GMT_WRITE_TABLE_SEGMENT; if ((T = GMT_Convert_Data (API, D, GMT_IS_DATASET, NULL, GMT_IS_TEXTSET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to text */
	if (GMT_Write_Data (API, GMT_IS_TEXTSET, GMT_IS_FILE, GMT_IS_NONE, GMT_WRITE_SET, NULL, "AB_txtTS.txt", T) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	/* Convert back to dataset with different modes and save */
	flag[2] = 0; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "TS_AB_data.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_TABLE; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "TS_AB_dataT.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_SEGMENT; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "TS_AB_dataS.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */
	flag[2] = GMT_WRITE_TABLE_SEGMENT; if ((D2 = GMT_Convert_Data (API, T, GMT_IS_TEXTSET, NULL, GMT_IS_DATASET, flag)) == NULL) exit (EXIT_FAILURE);	/* Convert to dataset */
	if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_PLP, GMT_WRITE_SET, NULL, "TS_AB_dataTS.txt", D2) != GMT_NOERROR)  exit (EXIT_FAILURE);	/* run module */

	/* 8. Destroy GMT session */
	if (GMT_Destroy_Session (API)) exit (EXIT_FAILURE);
}
