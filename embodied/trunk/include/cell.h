/*
    Abstract interface for a Cell.
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

#ifndef CELL_H
#define CELL_H

#include <vector>
#include <map>

class Point;

enum CELL_SIDE {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

class Cell
{
    public:
        /**
         * @brief Constructor.
         * @param parent The parent Cell.
         */
        Cell(Cell * parent = NULL, bool debug = false);

        /**
         * @brief Constructor.
         * @param neighbours The neighbors of this Cell.
         * @param parent The parent Cell.
         */
        Cell(std::map<CELL_SIDE, Cell *> neighbours, Cell * parent = NULL, bool debug = false);

        /**
         * @brief Calculate the potential of the Cell.
         * @param region The region to calculate.
         * @return A three dimensional vector of potential points.
         */
        virtual std::vector<std::vector<std::vector<double> > > CalculatePotential(const std::vector<std::vector<double *> > & region) = 0;

        /**
         * @brief Add a Point to the Cell.
         * @param point Point to add to this cell.
         * @return A pointer to the cell the point was added to.
         */
        virtual Cell * AddPoint(Point * point) = 0;

        /**
         * @brief Remove a Point from the Cell.
         * @param point Point to remove from this cell.
         * @return A pointer to the cell the point was removed from.
         */
        virtual Cell * RemovePoint(const Point & point) = 0;

        /**
         * @brief Count of the number of Points in this Cell.
         * @return The number of Points in this Cell.
         */
        virtual int Count() const = 0;

        /**
         * @brief Return an empty rank 3 vector.
         * @return An empy rank 3 vector.
         */
        std::vector<std::vector<std::vector<double> > > Empty_3_Vector();

        /**
         * @brief Return the Cell's region.
         * @return The region the Cell encompasses.
         */
        std::vector<std::vector<std::vector<double> > > GetRegion() const;

        /**
         * @brief Set the Cell's region.
         * @param region The Cell's new region.
         */
        void SetRegion(const std::vector<std::vector<std::vector<double> > > & region);

        /**
         * @brief Determines if a Cell contains a Point.
         * @param point The Point to check for containment.
         * @return true if the Point lies in the region of this Cell.
         */
        bool Contains(const Point & point) const;

    protected:
        std::map<CELL_SIDE, Cell *> neighbours;
        Cell *parent;
        std::vector<std::vector<double *> > region;
        bool debug;
};

#endif // CELL_H
