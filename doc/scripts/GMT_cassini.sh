#!/bin/bash
#	$Id: GMT_cassini.sh 15178 2015-11-06 10:45:03Z fwobbe $
#
gmt pscoast -R7:30/38:30/10:30/41:30r -JC8.75/40/2.5i -Bafg -LjBR+c40+w100+f+o0.15i/0.2i -Dh -Gspringgreen \
	-Sazure -Wthinnest -Ia/thinner -P --FONT_LABEL=10p > GMT_cassini.ps
