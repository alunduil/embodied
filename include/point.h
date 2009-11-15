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

#ifndef POINT_H
#define POINT_H

#include <vector>
#include <istream>

class Point
{
    public:
        /**
         * @brief Constructor.
         * @param mass The mass of the point.
         * @param x The x-coordinate of the point.
         * @param y The y-coordinate of the point.
         * @param z The z-coordinate of the point.
         */
        Point(double mass, double x, double y, double z);

        /**
         * @brief Change Position.
         * @param x The x-coordinate of the point.
         * @param y The y-coordinate of the point.
         * @param z The z-coordinate of the point.
         */
        void SetPosition(const double & x, const double & y, const double & z);

        /**
         * @brief Get the Position.
         * @return A 3-tuple with the point's coordinate.
         */
        std::vector<double> GetPosition() const;

        /**
         * @brief Change the Mass.
         * @param mass The mass of the point.
         */
        void SetMass(const double & mass);

        /**
         * @brief Get the Mass.
         * @return The mass of the point.
         */
        double GetMass() const;

        /**
         * @brief Check if this point equals the other point.
         * @param that The point to check for equivalence to this one.
         * @return bool true if they are at the same position; false otherwise.
         * @note This will lead to possible bugs where when a point is transitioning
         *   from one Cell to another the point that this one is sharing a position
         *   with (highly unlikely I know) will possibly get removed from the Cell
         *   when it shouldn't and just disappear.  So if you see disappearing Points
         *   check here first!  See if this is the case and then think of a better
         *   way of doing this.  Basically, solve collisions for me :).
         */
        bool operator==(const Point & that) const;

        /**
         * @brief Stream extraction operator.
         * @param in The input stream to read from.
         * @param that That Point to read into.
         * @return A reference to the input stream.
         */
        friend std::istream & operator>>(std::istream & in, Point & that);

        /**
         * @brief Stream insertion operator.
         * @param out The output stream to print to.
         * @param that That Point to print.
         * @return A reference to the output stream.
         */
        friend std::ostream & operator<<(std::ostream & out, const Point & that);

    private:
        double x, y, z;
        double mass;
};

#endif // POINT_H
// kate: indent-mode cstyle; space-indent on; indent-width 4;
