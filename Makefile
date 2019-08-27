##############################################################################
#
#    file                 : Makefile
#    created              : seg mar 11 20:01:53 WET 2019
#    copyright            : (C) 2002 Guilherme Gomes
#
##############################################################################
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
##############################################################################

ROBOT       = rrtcar
MODULE      = ${ROBOT}.so
MODULEDIR   = drivers/${ROBOT}
SOURCES     = ${ROBOT}.cpp heuristics.h rrt.cpp state.cpp dwindow.cpp spline.cpp trackdesc.cpp pathfinder.cpp mycar.cpp

SHIPDIR     = drivers/${ROBOT}
SHIP        = ${ROBOT}.xml logo.rgb
SHIPSUBDIRS = 1 2 3 4 5 6 7 8 9 10

PKGSUBDIRS  = ${SHIPSUBDIRS}
src-robots-rrtcar_PKGFILES = $(shell find * -maxdepth 0 -type f -print)
src-robots-rrtcar_PKGDIR   = ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}
