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

#include "../include/point.h"

Point::Point(double mass, double x, double y, double z)
        : mass(mass), x(x), y(y), z(z)
{
}

bool Point::operator==(const Point & that) const
{
    return this->x == that.x && this->y == that.y && this->z == that.z;
}

boost::tuple<double, double, double> Point::GetPosition() const
{
    return boost::tuple<double, double, double>(this->x, this->y, this->z);
}

std::istream & operator>>(std::istream & in, Point & that)
{
    in >> that.mass >> that.x >> that.y >> that.z;
}
// kate: indent-mode cstyle; space-indent on; indent-width 4;
