#!/bin/bash
#	$Id: GMT_App_O_4.sh 15178 2015-11-06 10:45:03Z fwobbe $
#
#	Makes Fig 4 for Appendix O (labeled lines)
#
gmt pscoast -R50/160/-15/15 -JM5.3i -Gburlywood -Sazure -A500 -K -P > GMT_App_O_4.ps
gmt grdcontour geoid.nc -J -O -B20f10 -BWSne -C10 -A20+d+f8p -GLZ-/Z+ -S10 -T+lLH >> GMT_App_O_4.ps
