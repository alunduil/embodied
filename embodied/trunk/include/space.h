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

#ifndef SPACE_H
#define SPACE_H

#include <set>

#include <../include/cell.h>

class Space : public Cell
{
    public:
        /**
         * @brief Constructor.
         * @param max The maximum number of Points in child Points sets.
         * @param parent The parent of this Cell.
         */
        Space(const int & max, Cell * parent = NULL, bool debug = false);

        /**
         * @brief Count the number of particles in this Space.
         * @return The number of points in this Space.
         */
        virtual int Count() const;

        /**
         * @brief Remove the Point from the Space.
         * @param point The point to remove.
         * @return A pointer to the resulting Cell.
         */
        virtual Cell* RemovePoint(const Point& point);

        /**
         * @brief Add the Point to the Space.
         * @param point The point to add.
         * @return A pointer to the resulting Cell.
         */
        virtual Cell* AddPoint(Point * point);

        /**
         * @brief Calculate the Potential for this Space.
         * @param region The region to calculate the potential for.
         * @return The potential field for this Space.
         */
        virtual std::vector<std::vector<std::vector<double> > > CalculatePotential(const std::vector<std::vector<double *> > & region);

    private:
        int max_points;
        std::set<Cell *> children;
};

#endif // SPACE_H
// kate: indent-mode cstyle; space-indent on; indent-width 4;
