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

#ifndef POINTS_H
#define POINTS_H

#include <list>

#include <../include/cell.h>

class Points : public Cell
{
    public:
        /**
         * @brief Constructor.
         * @param max The maximum points in this set.
         */
        explicit Points(const int &max, Cell * parent = NULL);

        /**
         * @brief Count of the number of points in this set.
         * @return The number of points in the set.
         */
        virtual int Count() const;

        /**
         * @brief Remove the specified point from this set.
         * @param point The point to remove.
         * @return The Cell we are after this removal.
         */
        virtual Cell* RemovePoint(const Point& point);

        /**
         * @brief Add the specified point to this set.
         * @param point The point to add.
         * @return The Cell we after this removal.
         */
        virtual Cell* AddPoint(const Point& point);

        /**
         * @brief Calculate the potential of this set.
         * @return The potential array for our points.
         */
        virtual std::vector<std::vector<std::vector<double> > > CalculatePotential();

    private:
        std::list<Point *> points;
        int max;
};

#endif // POINTS_H
