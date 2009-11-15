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

#include <boost/lexical_cast.hpp>
#include <ctype.h>

#include "../include/point.h"

Point::Point(double mass, double x, double y, double z)
        : mass(mass), x(x), y(y), z(z)
{
}

bool Point::operator==(const Point & that) const
{
    return this->x == that.x && this->y == that.y && this->z == that.z;
}

std::vector<double> Point::GetPosition() const
{
    std::vector<double> ret;
    ret.push_back(this->x);
    ret.push_back(this->y);
    ret.push_back(this->z);
    return ret;
}

double Point::GetMass() const
{
    return this->mass;
}

void Point::SetMass(const double & mass)
{
    this->mass = mass;
}

void Point::SetPosition(const double & x, const double & y, const double & z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

std::istream & operator>>(std::istream & in, Point & that)
{
    in >> that.mass >> that.x >> that.y >> that.z;
    /**
     * @note This seems like a terrible dirty hack!
     */
    while (!std::isdigit(in.peek()) && !in.eof()) in.get();
    return in;
}

std::ostream & operator<<(std::ostream & out, const Point & that)
{
    return out << "m: " << that.mass << " r: < " << that.GetPosition()[0] << ", " << that.GetPosition()[1] << ", " << that.GetPosition()[2] << ">";
}
// kate: indent-mode cstyle; space-indent on; indent-width 4;
