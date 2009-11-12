/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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
#include "../include/space.h"
#include "../include/points.h"

Space::Space(const int & max, Cell * parent, bool debug)
        : Cell(parent, debug), max_points(max)
{
}

int Space::Count() const
{
    int total = 0;
    for (std::set<Cell *>::iterator i = this->children.begin(); i != this->children.end(); ++i)
        total += (*i)->Count();
    return total;
}

Cell* Space::RemovePoint(const Point & point)
{
#ifndef NDEBUG
#warning Stub!  Needs to be implemented!
    WARNING("Space::RemovePoint()", "Stub!  Needs to be implemented!");
#endif
}

Cell* Space::AddPoint(Point * point)
{
    bool inserted = false;
    for (std::set<Cell *>::iterator i = this->children.begin(); i != this->children.end(); ++i)
        if ((*i)->Contains(*point))
        {
            Cell * tmp = NULL;
            if ((tmp = (*i)->AddPoint(point)) != *i)
            {
                DEBUG("Tree has split!");
                delete (*i);
                this->children.erase(i++);
                this->children.insert(--i, tmp);
            }
            inserted = true;
            break;
        }
    if (!inserted)
    {
        Cell * tmp = NULL;
        tmp = new Points(this->max_points, this, this->debug);
        this->children.insert(tmp);
        tmp->AddPoint(point);
    }
    return this;
}

std::vector<std::vector<std::vector<double> > > Space::CalculatePotential(const std::vector<std::vector<double *> > & region)
{
    std::vector<std::vector<std::vector<double> > > tmp = this->Empty_3_Vector();
#ifndef NDEBUG
#warning Stub!  Needs to be implemented!
    WARNING("Space::CalculatePotential()", "Stub!  Needs to be implemented!");
#endif
    /**
     * @todo Actually calculate the potential!
     * @note We'll have a bunch of Cells within this one, so why not calculate the potential based on their findings?
     */
    for (std::set<Cell *>::iterator i = this->children.begin(); i != this->children.end(); ++i)
        tmp = (*i)->CalculatePotential(region);
    return tmp;
}
// kate: indent-mode cstyle; space-indent on; indent-width 4;
