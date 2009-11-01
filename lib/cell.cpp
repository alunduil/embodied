/*
    The abstract Cell
    Copyright (C) 2009 Alex Brandt

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "../include/cell.h"
#include "../include/point.h"

Cell::Cell(Cell * parent, bool debug)
        : parent(parent), debug(debug)
{
}

std::vector<std::vector<std::vector<double> > > Cell::Empty_3_Vector()
{
    std::vector<double> innermost;
    std::vector<std::vector<double> > inner;
    std::vector<std::vector<std::vector<double> > > tmp;
    tmp.push_back(inner);
    tmp.back().push_back(innermost);
    return tmp;
}

bool Cell::Contains(const Point & point) const
{
    double x = boost::get<0>(point.GetPosition());
    double y = boost::get<1>(point.GetPosition());
    double z = boost::get<2>(point.GetPosition());
}
// kate: indent-mode cstyle; space-indent on; indent-width 4;
