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

#include <boost/tuple/tuple.hpp>
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
        void SetPosition(double x, double y, double z);

        /**
         * @brief Get the Position.
         * @return A 3-tuple with the point's coordinate.
         */
        boost::tuple<double, double, double> GetPosition() const;

        /**
         * @brief Change the Mass.
         * @param mass The mass of the point.
         */
        void SetMass(double mass);

        /**
         * @brief Get the Mass.
         * @return The mass of the point.
         */
        double GetMass() const;

        /**
         * @brief Stream extraction operator.
         * @param in The input stream to read from.
         * @param that That Point to read into.
         * @return A reference to the input stream.
         */
        friend std::istream & operator>>(std::istream & in, Point & that);

    private:
        double x, y, z;
        double mass;
};

#endif // POINT_H
