/*
    Application to drive the many body problem.
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

#ifndef EMBODIED_H
#define EMBODIED_H

#include <boost/program_options.hpp>
#include <vector>

#include "../include/octtree.h"

class Point;

class Embodied
{
    public:
        /**
         * @brief Default Constructor.
         * @param argc Count of the arguments.
         * @param argv Vector of the arguments.
         */
        Embodied(int argc, char *argv[]);

        /**
         * @brief Calculate the potential for the points in our space.
         * @return A three dimensional vector of values corresponding to the potentials.
         */
        std::vector<std::vector<std::vector<double> > > CalculatePotential();

    private:
        OctTree * space;
        int max_points;
        std::vector<std::vector<double *> > region;
        bool debug;
        bool verbose;
        int nsteps;

        /**
         * @brief Parse Flag Options.
         * @param argc Count of the arguments.
         * @param argv Vector of the arguments.
         * @return options_description for the arguments passed.
         */
        boost::program_options::variables_map parseOptions(int argc, char *argv[], boost::program_options::options_description * description = new boost::program_options::options_description("Options: "));

        /**
         * @brief Parse Region of Interest Parameter.
         * @param roi The region of interest string.
         * @param description The description of the parameters.
         * @return 2 n-tuples (0 < n <= 3) of points to
         */
        std::vector<std::vector<double *> > regionOfInterest(const std::string &roi, const boost::program_options::options_description & description);

        /**
         * @brief Given a set of points calculate the region they cover.
         * @param points The set of points.
         * @return Two 3-tuples with the corners of our region.
         */
        std::vector<std::vector<double> > calculateRegion(const std::vector<Point *> & points);

        /**
         * @brief Read in points from istream passed.
         * @param in The input stream we are reading from.
         * @return Vector of points.
         */
        std::vector<Point *> readPoints(std::istream &in);

        /**
         * @brief Return an empty region of interest.
         * @return Two points that are both NULL for both values to denote an empty region.
         */
        std::vector<std::vector<double *> > emptyRegionOfInterest();
};

class EmbodiedError
{
    public:
        std::string GetMessage() const;
        EmbodiedError(const std::string & msg);
    private:
        std::string message;
};

class EmbodiedArgumentError : public EmbodiedError
{
    public:
        boost::program_options::options_description GetDescription() const;
        EmbodiedArgumentError(const std::string & msg, const boost::program_options::options_description & description);
    private:
        boost::program_options::options_description description;
};

#endif // EMBODIED_H
