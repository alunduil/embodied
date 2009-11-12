/*
    Implementation for a collection of points.
    Copyright (C) 2009  Alex Brandt

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

#include <iostream>

#include "../include/output.h"
#include "../include/points.h"
#include "../include/space.h"
#include "../include/point.h"

Points::Points(const int & max, Cell * parent, bool debug)
        : Cell(parent, debug), max(max)
{
}

int Points::Count() const
{
    return this->points.size();
}

Cell* Points::RemovePoint(const Point& point)
{
    for (std::list<Point *>::iterator i = this->points.begin(); i != this->points.end(); ++i)
        if (**i == point) this->points.erase(i);
    if (this->points.size() == 0) return NULL;
    return this;
}

Cell* Points::AddPoint(Point* point)
{
    if (this->points.size() == this->max)
    {
        Space *tmp = new Space(this->max, this->parent);
        for (std::list<Point *>::iterator i = this->points.begin(); i != this->points.end(); ++i)
            tmp->AddPoint(*i);
        tmp->AddPoint(point);
        DEBUG("Tree has split!");
        return tmp;
    }
    this->points.push_back(point);
    return this;
}

std::vector<std::vector<std::vector<double> > > Points::CalculatePotential(const std::vector<std::vector<double *> > & region)
{
    std::vector<std::vector<std::vector<double> > > tmp = this->Empty_3_Vector();
#ifndef NDEBUG
#warning Stub!  Needs to be implemented!
    WARNING("Points::CalculatePotential()", "Stub!  Needs to be implemented!");
#endif
    /**
     * @todo Actually calculate the potential.
     */
    return tmp;
}
// kate: indent-mode cstyle; space-indent on; indent-width 4;
