#!/bin/bash
#	$Id: GMT_App_K_5.sh 11490 2013-05-16 06:26:21Z pwessel $
#
gmt pscoast -Rk-20/20/-20/20 -JE130.35/-0.2/3.5i -P -Df -Gburlywood \
	-Sazure -Wthinnest -N1/thinnest,- -B10mg2m -BWSne > GMT_App_K_5.ps
