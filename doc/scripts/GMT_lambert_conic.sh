#!/bin/bash
#	$Id: GMT_lambert_conic.sh 11490 2013-05-16 06:26:21Z pwessel $
#
gmt gmtset MAP_FRAME_TYPE FANCY FORMAT_GEO_MAP ddd:mm:ssF MAP_GRID_CROSS_SIZE_PRIMARY 0.05i
gmt pscoast -R-130/-70/24/52 -Jl-100/35/33/45/1:50000000 -Bag -Dl -N1/thick,red -N2/thinner \
	-A500 -Gtan -Wthinnest,white -Sblue -P > GMT_lambert_conic.ps
