#!/bin/bash
#	$Id: GMT_App_K_4.sh 15178 2015-11-06 10:45:03Z fwobbe $
#
gmt pscoast -Rk-100/100/-100/100 -JE130.35/-0.2/3.5i -P -Dh -A1 \
	-Gburlywood -Sazure -Wthinnest -N1/thinnest,- -B30mg10m -BWSne -K > GMT_App_K_4.ps
gmt psbasemap -R -J -O -Dg130.35/-0.2+w40k+jCM -F+pthicker >> GMT_App_K_4.ps
