#!/bin/bash
#	$Id: GMT_tut_8.sh 18314 2017-06-03 03:26:22Z pwessel $
#
gmt psxy @tut_data.txt -R0/6/0/6 -Jx1i -Baf -P -K -Wthinner > GMT_tut_8.ps
gmt psxy tut_data.txt -R -J -O -W -Si0.2i >> GMT_tut_8.ps
