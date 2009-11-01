#!/bin/python
# -*- coding: utf-8 -*-

############################################################################
#    Copyright (C) 2009 by Alex Brandt <alunduil@alunduil.com>             #
#                                                                          #
#    This program is free software; you can redistribute it and#or modify  #
#    it under the terms of the GNU General Public License as published by  #
#    the Free Software Foundation; either version 2 of the License, or     #
#    (at your option) any later version.                                   #
#                                                                          #
#    This program is distributed in the hope that it will be useful,       #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#    GNU General Public License for more details.                          #
#                                                                          #
#    You should have received a copy of the GNU General Public License     #
#    along with this program; if not, write to the                         #
#    Free Software Foundation, Inc.,                                       #
#    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
############################################################################

import optparse
import random
import sys

class Generator:
    def __init__(self):
        self._options, self._arguments = self._parseOptions()

    def _parseOptions(self):
        description_list = [
            "%prog creates files of random points appropriate for the ",
            "embodied utility."
            ]
        parser = optparse.OptionParser(usage="usage: %prog [options]",
            version="%prog 1.0", description="".join(description_list))

        num_points_list = "The number of points to put in the output."
        parser.add_option('--number', '-n', type="int",
            default=random.randint(500, 1000),
            help=num_points_list)

        max_point_size_list = "The maximum size of a float to add as a coordinate."
        parser.add_option('--max-float', '-M', type="float",
            default=random.uniform(500, 1000),
            help=max_point_size_list)

        min_point_size_list = "The minimum size of a float to add as a coordinate."
        parser.add_option('--min-float', '-m', type="float",
            default=random.uniform(-1000, -500),
            help=min_point_size_list)

        return parser.parse_args()

    def GeneratePoints(self):
        points = []
        for i in range(self._options.number):
            points.append(self._generatePoint())
        return points

    def _generatePoint(self):
        point = ""
        for i in range(4):
            point += str(random.uniform(self._options.min_float, self._options.max_float))
            point += " "
        return point

if __name__ == "__main__":
    foo = Generator()
    for point in foo.GeneratePoints():
        print point
