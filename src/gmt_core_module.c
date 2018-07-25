/* $Id: gmt_core_module.c 19523 2017-12-27 23:20:32Z pwessel $
 *
 * Copyright (c) 2012-2018
 * by P. Wessel, W. H. F. Smith, R. Scharroo, J. Luis, and F. Wobbe
 * See LICENSE.TXT file for copying and redistribution conditions.
 */

/* gmt_core_module.c populates the external array of GMT core with
 * module parameters such as name, group, purpose and keys strings.
 * This file also contains the following convenience functions to
 * display all module purposes or just list their names:
 *
 *   void gmt_core_module_show_all (struct GMTAPI_CTRL *API);
 *   void gmt_core_module_list_all (void *API);
 *
 * These functions may be called by gmt --help and gmt --show-modules
 *
 * Developers of external APIs for accessing GMT modules will use this
 * function indirectly via GMT_Encode_Options to retrieve option keys
 * needed for module arg processing:
 *
 *   char * gmt_core_module_info (void *API, const char *module);
 *
 * DO NOT edit this file directly! Regenerate the file by running
 * 	gmt_make_module_src.sh core
 */
#include "gmt_dev.h"
#ifndef BUILD_SHARED_LIBS
#include "gmt_core_module.h"
#endif


/* Sorted array with information for all GMT core modules */

/* name, library, and purpose for each module */
struct Gmt_moduleinfo {
	const char *name;             /* Program name */
	const char *component;        /* Component (core, supplement, custom) */
	const char *purpose;          /* Program purpose */
	const char *keys;             /* Program option info for external APIs */
#ifndef BUILD_SHARED_LIBS
	/* gmt module function pointer: */
	int (*p_func)(void*, int, void*);
#endif
};

static struct Gmt_moduleinfo g_core_module[] = {
#ifdef BUILD_SHARED_LIBS
	{"blockmean", "core", "Block average (x,y,z) data tables by L2 norm", "<D{,>D}"},
	{"blockmedian", "core", "Block average (x,y,z) data tables by L1 norm (spatial median)", "<D{,>D}"},
	{"blockmode", "core", "Block average (x,y,z) data tables by mode estimation", "<D{,>D}"},
	{"filter1d", "core", "Time domain filtering of 1-D data tables", "<D{,>D},FD(1"},
	{"fitcircle", "core", "Find mean position and great [or small] circle fit to points on sphere", "<D{,>T},>DF"},
	{"gmt2kml", "core", "Convert GMT data tables to KML files for Google Earth", "<D{,>T},CC("},
	{"gmtconnect", "core", "Connect individual lines whose end points match within tolerance", "<D{,>D},CD),LT),QT)"},
	{"gmtconvert", "core", "Convert, paste, or extract columns from data tables", "<D{,>D}"},
	{"gmtdefaults", "core", "List current GMT default parameters", ""},
	{"gmtget", "core", "Get individual GMT default parameters", ">T}"},
	{"gmtinfo", "core", "Get information about data tables", "<D{,>T},>DC"},
	{"gmtlogo", "core", "Plot the GMT logo on maps", ">X}"},
	{"gmtmath", "core", "Reverse Polish Notation (RPN) calculator for data tables", "<D{,AD(=,TD(,>D}"},
	{"gmtread", "core", "Read GMT objects into external API", "-T-,<?{,>?}"},
	{"gmtregress", "core", "Linear regression of 1-D data sets", "<D{,>D}"},
	{"gmtselect", "core", "Select data table subsets based on multiple spatial criteria", "<D{,CD(=,FD(,LD(=,>D},GG("},
	{"gmtset", "core", "Change individual GMT default parameters", ""},
	{"gmtsimplify", "core", "Line reduction using the Douglas-Peucker algorithm", "<D{,>D}"},
	{"gmtspatial", "core", "Geospatial operations on lines and polygons", "<D{,DD(=f,ND(=,TD(,>D},>TD,>TI,>TN+r"},
	{"gmtvector", "core", "Operations on Cartesian vectors in 2-D and 3-D", "<D{,AD(,>D}"},
	{"gmtwhich", "core", "Find full path to specified files", ">T}"},
	{"gmtwrite", "core", "Write GMT objects from external API", "-T-,<?{,>?}"},
	{"grd2cpt", "core", "Make linear or histogram-equalized color palette table from grid", "<G{+,>C}"},
	{"grd2rgb", "core", "Write r/g/b grid files from a grid file, a raw RGB file, or SUN rasterfile", "<G{,CC("},
	{"grd2xyz", "core", "Convert grid file to data table", "<G{+,>D}"},
	{"grdblend", "core", "Blend several partially over-lapping grids into one larger grid", "<T{,GG}"},
	{"grdclip", "core", "Clip the range of grid values", "<G{,GG}"},
	{"grdcontour", "core", "Make contour map using a grid", "<G{,AT)=t,CC(,DDD,>X},G?(=1"},
	{"grdconvert", "core", "Convert between different grid formats", "<G{,>G}"},
	{"grdcut", "core", "Extract subregion from a grid", "<G{,GG}"},
	{"grdedit", "core", "Modify header or content of a grid", "<G{,ND(,GG}"},
	{"grdfft", "core", "Mathematical operations on grids in the wavenumber (or frequency) domain", "<G{+,GG},GDE"},
	{"grdfill", "core", "Interpolate across holes in a grid", "<G{,>G}"},
	{"grdfilter", "core", "Filter a grid in the space (or time) domain", "<G{,FG(=1,GG}"},
	{"grdgradient", "core", "Compute directional gradients from a grid", "<G{,GG},SG)"},
	{"grdhisteq", "core", "Perform histogram equalization for a grid", "<G{,GG},DT)"},
	{"grdimage", "core", "Project grids or images and plot them on maps", "<G{+,CC(,IG(,>X},>IA,<ID"},
	{"grdinfo", "core", "Extract information from grids", "<G{+,>T},>DC"},
	{"grdlandmask", "core", "Create a \"wet-dry\" mask grid from shoreline data base", "GG}"},
	{"grdmask", "core", "Create mask grid from polygons or point coverage", "<D{,GG}"},
	{"grdmath", "core", "Reverse Polish Notation (RPN) calculator for grids (element by element)", "<G(,=G}"},
	{"grdpaste", "core", "Join two grids along their common edge", "<G{2,GG}"},
	{"grdproject", "core", "Forward and inverse map transformation of grids", "<G{,GG}"},
	{"grdraster", "core", "Extract subregion from a binary raster and save as a GMT grid", "GG},TD)"},
	{"grdsample", "core", "Resample a grid onto a new lattice", "<G{,GG}"},
	{"grdtrack", "core", "Sample grids at specified (x,y) locations", "<D{,DD),E-<,GG(,>D},SD)=s"},
	{"grdtrend", "core", "Fit trend surface to grids and compute residuals", "<G{,DG),TG),WG)"},
	{"grdvector", "core", "Plot vector field from two component grids", "<G{2,CC(,>X}"},
	{"grdview", "core", "Create 3-D perspective image or surface mesh from a grid", "<G{,CC(,GG(,IG(,>X}"},
	{"grdvolume", "core", "Calculate grid volume and area constrained by a contour", "<G{,>D}"},
	{"greenspline", "core", "Interpolate using Green's functions for splines in 1-3 dimensions", "<D{,AD(=,ED),ND(,TG(,CD)=f,G?},GDN"},
	{"kml2gmt", "core", "Extract GMT table data from Google Earth KML files", "<T{,>D}"},
	{"makecpt", "core", "Make GMT color palette tables", ">C},ED(,TD("},
	{"mapproject", "core", "Forward and inverse map transformations, datum conversions and geodesy", "<D{,LD(=,>D},W-("},
	{"nearneighbor", "core", "Grid table data using a \"Nearest neighbor\" algorithm", "<D{,GG}"},
	{"project", "core", "Project table data onto lines or great circles, generate tracks, or translate coordinates", "<D{,>D},G-("},
	{"psbasemap", "core", "Plot base maps and frames", ">X},>DA"},
	{"psclip", "core", "Initialize or terminate polygonal clip paths", "<D{,>X},C-("},
	{"pscoast", "core", "Plot continents, countries, shorelines, rivers, and borders on maps", ">X},>DM,>TE+w-rR"},
	{"pscontour", "core", "Contour table data by direct triangulation", "<D{,AT)=t,CC(,ED(,DDD,G?(=1,>X}"},
	{"psconvert", "core", "Convert [E]PS file(s) to other formats using GhostScript", "<X{+,FI)"},
	{"pshistogram", "core", "Calculate and plot histograms", "<D{,>X},>D),>DI"},
	{"psimage", "core", "Place images or EPS files on maps", "<I{,>X}"},
	{"pslegend", "core", "Plot legends on maps", "<T{,>X}"},
	{"psmask", "core", "Clip or mask map areas with no data table coverage", "<D{,DDD,C-(,>X},LG)"},
	{"psrose", "core", "Plot a polar histogram (rose, sector, windrose diagrams)", "<D{,CD(,>X}"},
	{"psscale", "core", "Plot a gray-scale or color-scale on maps", "CC{,>X},ZD("},
	{"pssolar", "core", "Plot day-light terminators and other sunlight parameters", ">X},>DI,>DM"},
	{"psternary", "core", "Plot data on ternary diagrams", "<D{,>X},>DM,C-("},
	{"pstext", "core", "Plot or typeset text on maps", "<T{,>X}"},
	{"pswiggle", "core", "Plot z = f(x,y) anomalies along tracks", "<D{,>X}"},
	{"psxyz", "core", "Plot lines, polygons, and symbols in 3-D", "<D{,CC(,T-<,>X},S?(=2"},
	{"psxy", "core", "Plot lines, polygons, and symbols on maps", "<D{,CC(,T-<,>X},S?(=2"},
	{"sample1d", "core", "Resample 1-D table data using splines", "<D{,ND(,>D}"},
	{"spectrum1d", "core", "Compute auto- [and cross-] spectra from one [or two] time series", "<D{,>D},T-)"},
	{"sph2grd", "core", "Compute grid from spherical harmonic coefficients", "<D{,GG}"},
	{"sphdistance", "core", "Create Voronoi distance, node, or natural nearest-neighbor grid on a sphere", "<D{,ND(,QD(,GG},Q-("},
	{"sphinterpolate", "core", "Spherical gridding in tension of data on a sphere", "<D{,GG}"},
	{"sphtriangulate", "core", "Delaunay or Voronoi construction of spherical data", "<D{,>D},ND)"},
	{"splitxyz", "core", "Split xyz[dh] data tables into individual segments", "<D{,>D}"},
	{"surface", "core", "Grid table data using adjustable tension continuous curvature splines", "<D{,DD(,LG(=1,GG}"},
	{"trend1d", "core", "Fit a [weighted] [robust] polynomial [and/or Fourier] model for y = f(x) to xy[w] data", "<D{,>D}"},
	{"trend2d", "core", "Fit a [weighted] [robust] polynomial for z = f(x,y) to xyz[w] data", "<D{,>D}"},
	{"triangulate", "core", "Optimal (Delaunay) triangulation and gridding of Cartesian table data", "<D{,>D},GG)"},
	{"xyz2grd", "core", "Convert data table to a grid file", "<D{,SD),GG}"},
	{NULL, NULL, NULL, NULL} /* last element == NULL detects end of array */
#else
	{"blockmean", "core", "Block average (x,y,z) data tables by L2 norm", "<D{,>D}", &GMT_blockmean},
	{"blockmedian", "core", "Block average (x,y,z) data tables by L1 norm (spatial median)", "<D{,>D}", &GMT_blockmedian},
	{"blockmode", "core", "Block average (x,y,z) data tables by mode estimation", "<D{,>D}", &GMT_blockmode},
	{"filter1d", "core", "Time domain filtering of 1-D data tables", "<D{,>D},FD(1", &GMT_filter1d},
	{"fitcircle", "core", "Find mean position and great [or small] circle fit to points on sphere", "<D{,>T},>DF", &GMT_fitcircle},
	{"gmt2kml", "core", "Convert GMT data tables to KML files for Google Earth", "<D{,>T},CC(", &GMT_gmt2kml},
	{"gmtconnect", "core", "Connect individual lines whose end points match within tolerance", "<D{,>D},CD),LT),QT)", &GMT_gmtconnect},
	{"gmtconvert", "core", "Convert, paste, or extract columns from data tables", "<D{,>D}", &GMT_gmtconvert},
	{"gmtdefaults", "core", "List current GMT default parameters", "", &GMT_gmtdefaults},
	{"gmtget", "core", "Get individual GMT default parameters", ">T}", &GMT_gmtget},
	{"gmtinfo", "core", "Get information about data tables", "<D{,>T},>DC", &GMT_gmtinfo},
	{"gmtlogo", "core", "Plot the GMT logo on maps", ">X}", &GMT_gmtlogo},
	{"gmtmath", "core", "Reverse Polish Notation (RPN) calculator for data tables", "<D{,AD(=,TD(,>D}", &GMT_gmtmath},
	{"gmtread", "core", "Read GMT objects into external API", "-T-,<?{,>?}", &GMT_gmtread},
	{"gmtregress", "core", "Linear regression of 1-D data sets", "<D{,>D}", &GMT_gmtregress},
	{"gmtselect", "core", "Select data table subsets based on multiple spatial criteria", "<D{,CD(=,FD(,LD(=,>D},GG(", &GMT_gmtselect},
	{"gmtset", "core", "Change individual GMT default parameters", "", &GMT_gmtset},
	{"gmtsimplify", "core", "Line reduction using the Douglas-Peucker algorithm", "<D{,>D}", &GMT_gmtsimplify},
	{"gmtspatial", "core", "Geospatial operations on lines and polygons", "<D{,DD(=f,ND(=,TD(,>D},>TD,>TI,>TN+r", &GMT_gmtspatial},
	{"gmtvector", "core", "Operations on Cartesian vectors in 2-D and 3-D", "<D{,AD(,>D}", &GMT_gmtvector},
	{"gmtwhich", "core", "Find full path to specified files", ">T}", &GMT_gmtwhich},
	{"gmtwrite", "core", "Write GMT objects from external API", "-T-,<?{,>?}", &GMT_gmtwrite},
	{"grd2cpt", "core", "Make linear or histogram-equalized color palette table from grid", "<G{+,>C}", &GMT_grd2cpt},
	{"grd2rgb", "core", "Write r/g/b grid files from a grid file, a raw RGB file, or SUN rasterfile", "<G{,CC(", &GMT_grd2rgb},
	{"grd2xyz", "core", "Convert grid file to data table", "<G{+,>D}", &GMT_grd2xyz},
	{"grdblend", "core", "Blend several partially over-lapping grids into one larger grid", "<T{,GG}", &GMT_grdblend},
	{"grdclip", "core", "Clip the range of grid values", "<G{,GG}", &GMT_grdclip},
	{"grdcontour", "core", "Make contour map using a grid", "<G{,AT)=t,CC(,DDD,>X},G?(=1", &GMT_grdcontour},
	{"grdconvert", "core", "Convert between different grid formats", "<G{,>G}", &GMT_grdconvert},
	{"grdcut", "core", "Extract subregion from a grid", "<G{,GG}", &GMT_grdcut},
	{"grdedit", "core", "Modify header or content of a grid", "<G{,ND(,GG}", &GMT_grdedit},
	{"grdfft", "core", "Mathematical operations on grids in the wavenumber (or frequency) domain", "<G{+,GG},GDE", &GMT_grdfft},
	{"grdfill", "core", "Interpolate across holes in a grid", "<G{,>G}", &GMT_grdfill},
	{"grdfilter", "core", "Filter a grid in the space (or time) domain", "<G{,FG(=1,GG}", &GMT_grdfilter},
	{"grdgradient", "core", "Compute directional gradients from a grid", "<G{,GG},SG)", &GMT_grdgradient},
	{"grdhisteq", "core", "Perform histogram equalization for a grid", "<G{,GG},DT)", &GMT_grdhisteq},
	{"grdimage", "core", "Project grids or images and plot them on maps", "<G{+,CC(,IG(,>X},>IA,<ID", &GMT_grdimage},
	{"grdinfo", "core", "Extract information from grids", "<G{+,>T},>DC", &GMT_grdinfo},
	{"grdlandmask", "core", "Create a \"wet-dry\" mask grid from shoreline data base", "GG}", &GMT_grdlandmask},
	{"grdmask", "core", "Create mask grid from polygons or point coverage", "<D{,GG}", &GMT_grdmask},
	{"grdmath", "core", "Reverse Polish Notation (RPN) calculator for grids (element by element)", "<G(,=G}", &GMT_grdmath},
	{"grdpaste", "core", "Join two grids along their common edge", "<G{2,GG}", &GMT_grdpaste},
	{"grdproject", "core", "Forward and inverse map transformation of grids", "<G{,GG}", &GMT_grdproject},
	{"grdraster", "core", "Extract subregion from a binary raster and save as a GMT grid", "GG},TD)", &GMT_grdraster},
	{"grdsample", "core", "Resample a grid onto a new lattice", "<G{,GG}", &GMT_grdsample},
	{"grdtrack", "core", "Sample grids at specified (x,y) locations", "<D{,DD),E-<,GG(,>D},SD)=s", &GMT_grdtrack},
	{"grdtrend", "core", "Fit trend surface to grids and compute residuals", "<G{,DG),TG),WG)", &GMT_grdtrend},
	{"grdvector", "core", "Plot vector field from two component grids", "<G{2,CC(,>X}", &GMT_grdvector},
	{"grdview", "core", "Create 3-D perspective image or surface mesh from a grid", "<G{,CC(,GG(,IG(,>X}", &GMT_grdview},
	{"grdvolume", "core", "Calculate grid volume and area constrained by a contour", "<G{,>D}", &GMT_grdvolume},
	{"greenspline", "core", "Interpolate using Green's functions for splines in 1-3 dimensions", "<D{,AD(=,ED),ND(,TG(,CD)=f,G?},GDN", &GMT_greenspline},
	{"kml2gmt", "core", "Extract GMT table data from Google Earth KML files", "<T{,>D}", &GMT_kml2gmt},
	{"makecpt", "core", "Make GMT color palette tables", ">C},ED(,TD(", &GMT_makecpt},
	{"mapproject", "core", "Forward and inverse map transformations, datum conversions and geodesy", "<D{,LD(=,>D},W-(", &GMT_mapproject},
	{"nearneighbor", "core", "Grid table data using a \"Nearest neighbor\" algorithm", "<D{,GG}", &GMT_nearneighbor},
	{"project", "core", "Project table data onto lines or great circles, generate tracks, or translate coordinates", "<D{,>D},G-(", &GMT_project},
	{"psbasemap", "core", "Plot base maps and frames", ">X},>DA", &GMT_psbasemap},
	{"psclip", "core", "Initialize or terminate polygonal clip paths", "<D{,>X},C-(", &GMT_psclip},
	{"pscoast", "core", "Plot continents, countries, shorelines, rivers, and borders on maps", ">X},>DM,>TE+w-rR", &GMT_pscoast},
	{"pscontour", "core", "Contour table data by direct triangulation", "<D{,AT)=t,CC(,ED(,DDD,G?(=1,>X}", &GMT_pscontour},
	{"psconvert", "core", "Convert [E]PS file(s) to other formats using GhostScript", "<X{+,FI)", &GMT_psconvert},
	{"pshistogram", "core", "Calculate and plot histograms", "<D{,>X},>D),>DI", &GMT_pshistogram},
	{"psimage", "core", "Place images or EPS files on maps", "<I{,>X}", &GMT_psimage},
	{"pslegend", "core", "Plot legends on maps", "<T{,>X}", &GMT_pslegend},
	{"psmask", "core", "Clip or mask map areas with no data table coverage", "<D{,DDD,C-(,>X},LG)", &GMT_psmask},
	{"psrose", "core", "Plot a polar histogram (rose, sector, windrose diagrams)", "<D{,CD(,>X}", &GMT_psrose},
	{"psscale", "core", "Plot a gray-scale or color-scale on maps", "CC{,>X},ZD(", &GMT_psscale},
	{"pssolar", "core", "Plot day-light terminators and other sunlight parameters", ">X},>DI,>DM", &GMT_pssolar},
	{"psternary", "core", "Plot data on ternary diagrams", "<D{,>X},>DM,C-(", &GMT_psternary},
	{"pstext", "core", "Plot or typeset text on maps", "<T{,>X}", &GMT_pstext},
	{"pswiggle", "core", "Plot z = f(x,y) anomalies along tracks", "<D{,>X}", &GMT_pswiggle},
	{"psxyz", "core", "Plot lines, polygons, and symbols in 3-D", "<D{,CC(,T-<,>X},S?(=2", &GMT_psxyz},
	{"psxy", "core", "Plot lines, polygons, and symbols on maps", "<D{,CC(,T-<,>X},S?(=2", &GMT_psxy},
	{"sample1d", "core", "Resample 1-D table data using splines", "<D{,ND(,>D}", &GMT_sample1d},
	{"spectrum1d", "core", "Compute auto- [and cross-] spectra from one [or two] time series", "<D{,>D},T-)", &GMT_spectrum1d},
	{"sph2grd", "core", "Compute grid from spherical harmonic coefficients", "<D{,GG}", &GMT_sph2grd},
	{"sphdistance", "core", "Create Voronoi distance, node, or natural nearest-neighbor grid on a sphere", "<D{,ND(,QD(,GG},Q-(", &GMT_sphdistance},
	{"sphinterpolate", "core", "Spherical gridding in tension of data on a sphere", "<D{,GG}", &GMT_sphinterpolate},
	{"sphtriangulate", "core", "Delaunay or Voronoi construction of spherical data", "<D{,>D},ND)", &GMT_sphtriangulate},
	{"splitxyz", "core", "Split xyz[dh] data tables into individual segments", "<D{,>D}", &GMT_splitxyz},
	{"surface", "core", "Grid table data using adjustable tension continuous curvature splines", "<D{,DD(,LG(=1,GG}", &GMT_surface},
	{"trend1d", "core", "Fit a [weighted] [robust] polynomial [and/or Fourier] model for y = f(x) to xy[w] data", "<D{,>D}", &GMT_trend1d},
	{"trend2d", "core", "Fit a [weighted] [robust] polynomial for z = f(x,y) to xyz[w] data", "<D{,>D}", &GMT_trend2d},
	{"triangulate", "core", "Optimal (Delaunay) triangulation and gridding of Cartesian table data", "<D{,>D},GG)", &GMT_triangulate},
	{"xyz2grd", "core", "Convert data table to a grid file", "<D{,SD),GG}", &GMT_xyz2grd},
	{NULL, NULL, NULL, NULL, NULL} /* last element == NULL detects end of array */
#endif
};

/* Pretty print all GMT core module names and their purposes for gmt --help */
void gmt_core_module_show_all (void *V_API) {
	unsigned int module_id = 0;
	char message[GMT_LEN256];
	struct GMTAPI_CTRL *API = gmt_get_api_ptr (V_API);
	GMT_Message (V_API, GMT_TIME_NONE, "\n===  GMT core: The main modules of the Generic Mapping Tools  ===\n");
	while (g_core_module[module_id].name != NULL) {
		if (module_id == 0 || strcmp (g_core_module[module_id-1].component, g_core_module[module_id].component)) {
			/* Start of new supplemental group */
			snprintf (message, GMT_LEN256, "\nModule name:     Purpose of %s module:\n", g_core_module[module_id].component);
			GMT_Message (V_API, GMT_TIME_NONE, message);
			GMT_Message (V_API, GMT_TIME_NONE, "----------------------------------------------------------------\n");
		}
		if (API->external || (strcmp (g_core_module[module_id].name, "gmtread") && strcmp (g_core_module[module_id].name, "gmtwrite"))) {
			snprintf (message, GMT_LEN256, "%-16s %s\n",
				g_core_module[module_id].name, g_core_module[module_id].purpose);
				GMT_Message (V_API, GMT_TIME_NONE, message);
		}
		++module_id;
	}
}

/* Produce single list on stdout of all GMT core module names for gmt --show-modules */
void gmt_core_module_list_all (void *V_API) {
	unsigned int module_id = 0;
	struct GMTAPI_CTRL *API = gmt_get_api_ptr (V_API);
	while (g_core_module[module_id].name != NULL) {
		if (API->external || (strcmp (g_core_module[module_id].name, "gmtread") && strcmp (g_core_module[module_id].name, "gmtwrite")))
			printf ("%s\n", g_core_module[module_id].name);
		++module_id;
	}
}

/* Lookup module id by name, return option keys pointer (for external API developers) */
const char *gmt_core_module_info (void *API, char *candidate) {
	int module_id = 0;
	gmt_M_unused(API);

	/* Match actual_name against g_module[module_id].name */
	while (g_core_module[module_id].name != NULL &&
	       strcmp (candidate, g_core_module[module_id].name))
		++module_id;

	/* Return Module keys or NULL */
	return (g_core_module[module_id].keys);
}
	
#ifndef BUILD_SHARED_LIBS
/* Lookup static module id by name, return function pointer */
void *gmt_core_module_lookup (void *API, const char *candidate) {
	int module_id = 0;
	size_t len = strlen (candidate);
	gmt_M_unused(API);

	if (len < 4) return NULL;	/* All candidates should start with GMT_ */
	/* Match actual_name against g_module[module_id].name */
	while (g_core_module[module_id].name != NULL &&
	       strcmp (&candidate[4], g_core_module[module_id].name))
		++module_id;

	/* Return Module function or NULL */
	return (g_core_module[module_id].p_func);
}
#endif
