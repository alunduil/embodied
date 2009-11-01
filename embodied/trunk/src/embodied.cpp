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
#include <fstream>
#include <boost/regex.hpp>
#include <cstdio>

#include "../include/embodied.h"
#include "../include/cell.h"
#include "../include/points.h"
#include "../include/point.h"
#include "../include/output.h"

Embodied::Embodied(int argc, char *argv[])
        : space(NULL), max_points(50), debug(false), verbose(false)
{
    using namespace boost::program_options;
    std::string usage;
    usage += "Usage: ";
    usage += argv[0];
    usage += " [options] [((x1,y1,z1),(x2,y2,z2))]";
    options_description description(usage);
    variables_map variables;
    try
    {
        variables = this->parseOptions(argc, argv, &description);
    }
    catch (...)
    {
        throw EmbodiedArgumentError("", description);
    }

    if (variables.count("help") > 0) throw EmbodiedArgumentError("", description);

    if (variables.count("output") > 0 && !std::freopen(variables["output"].as<std::string>().c_str(), "a", stdout))
    {
        std::string output("Could not re-open stdout on file: ");
        output += variables["output"].as<std::string>();
        throw EmbodiedArgumentError(output, description);
    }

    this->debug = variables.count("debug") > 0;
    this->verbose = variables.count("verbose") > 0;

    std::vector<Point *> points;
    if (variables.count("filename") < 1) points = this->readPoints(std::cin);
    for (int i = 0; i < variables.count("filename"); ++i)
    {
        std::ifstream file(variables["filename"].as<std::vector<std::string> >()[i].c_str());
        std::vector<Point *> tmp = this->readPoints(file);
        for (std::vector<Point *>::iterator j = tmp.begin(); j != tmp.end(); ++j)
            points.push_back(*j);
        file.close();
    }
    if (variables.count("maxpoints") > 0) this->max_points = variables["maxpoints"].as<int>();
    this->space = new Points(this->max_points, NULL, this->debug);
    for (std::vector<Point *>::iterator i = points.begin(); i != points.end(); ++i)
    {
        Cell *tmp = NULL;
        if ((tmp = this->space->AddPoint(*i)) != this->space)
        {
            VERBOSE("Tree has split!");
            delete this->space;
            this->space = tmp;
        }
    }

#ifndef NDEBUG
    DEBUG(variables["region"].as<std::string>());
#endif
    this->region = (variables.count("region") > 0) ? regionOfInterest(variables["region"].as<std::string>(), description) : this->emptyRegionOfInterest();
}

std::vector<std::vector<double *> > Embodied::emptyRegionOfInterest()
{
    std::vector<std::vector<double *> > tmp;
    std::vector<double *> empty;
    empty.push_back((double *)NULL);
    empty.push_back((double *)NULL);
    empty.push_back((double *)NULL);
    tmp.push_back(empty);
    tmp.push_back(empty);
    return tmp;
}

std::vector<std::vector<double *> > Embodied::regionOfInterest(const std::string & roi, const boost::program_options::options_description & description)
{
    std::vector<std::vector<double *> > tmp = this->emptyRegionOfInterest();
    /**
     * @note
     *   Input Examples:
     *   ((.,.,.),(.,.,.))
     *   ((-300.400,-300.200,-420.520),(-52.502,-44.535,432.52))
     *   ((-1,1,.), (-1,1,.))
     *
     *  This leads us to this regular expression:
     *    \\(\\W*?\\(\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?,\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?\\)\\W*?,\\W*?\\(\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?,\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?\\)\\W*?\\)
     * @todo Simplify the above regular expression through some DFA analysis.
     */
    boost::regex expression("\\(\\W*?\\(\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?,\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?,\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?\\)\\W*?,\\W*?\\(\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?,\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?,\\W*?(-?\\d+(?:\\.\\d+)?|\\.)\\W*?\\)\\W*?\\)");
    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
#ifndef NDEBUG
    DEBUG(expression);
#endif
    if (boost::regex_search(roi.begin(), roi.end(), what, expression, flags))
    {
#ifndef NDEBUG
        DEBUG(what[1]);
        DEBUG(what[2]);
        DEBUG(what[3]);
        DEBUG(what[4]);
        DEBUG(what[5]);
        DEBUG(what[6]);
#endif
        tmp[0][0] = (what[1].str() == ".") ? NULL : new double(boost::lexical_cast<double>(what[1]));
        tmp[0][1] = (what[2].str() == ".") ? NULL : new double(boost::lexical_cast<double>(what[2]));
        tmp[0][2] = (what[3].str() == ".") ? NULL : new double(boost::lexical_cast<double>(what[3]));
        tmp[1][0] = (what[4].str() == ".") ? NULL : new double(boost::lexical_cast<double>(what[4]));
        tmp[1][1] = (what[5].str() == ".") ? NULL : new double(boost::lexical_cast<double>(what[5]));
        tmp[1][2] = (what[6].str() == ".") ? NULL : new double(boost::lexical_cast<double>(what[6]));
    }
    else throw EmbodiedArgumentError("Improperly formed region string!", description);
#ifndef NDEBUG
    DEBUG(tmp[0][0]);
    DEBUG(tmp[0][1]);
    DEBUG(tmp[0][2]);
    DEBUG(tmp[1][0]);
    DEBUG(tmp[1][1]);
    DEBUG(tmp[1][2]);
#endif
    return tmp;
}

std::vector<Point *> Embodied::readPoints(std::istream & in)
{
    Point point(0, 0, 0, 0);
    std::vector<Point *> tmp;
    while (!in.eof())
    {
        in >> point;
        tmp.push_back(&point);
    }
    return tmp;
}

boost::program_options::variables_map Embodied::parseOptions(int argc, char *argv[], boost::program_options::options_description *description)
{
    using namespace boost::program_options;
    description->add_options()
    ("help,h", "Print this help.")
    ("debug,d", "Turn on the debugging output.")
    ("verbose,v", "Turn on verbose output.")
    ("filename,f", value<std::vector<std::string> >(), "The FILENAMEs to read points from.")
    ("maxpoints,m", value<int>(), "The MAXIMUM points in a leaf node.")
    ("output,o", value<std::string>(), "The filename to OUTPUT to.")
    ("region,r", value<std::string>(), "The REGION of interest.  This is specified as ((x1, y1), (x2, y2)), where x1 can equal x2 and y1 can equal y2.  Also, any of the values passed may be represented by a '.' to indicate that this bound should be determined from the positions of the Points.")
    ;

    positional_options_description positional_arguments;
    positional_arguments.add("region", 1);

    variables_map variables;
    store(command_line_parser(argc, argv).options(*description).positional(positional_arguments).run(), variables);
    notify(variables);
    return variables;
}

std::vector<std::vector<std::vector<double> > > Embodied::CalculatePotential()
{
    if (!space) throw EmbodiedError("We are outside of space!  Where are we?");
    return space->CalculatePotential(this->region);
}

EmbodiedError::EmbodiedError(const std::string &message)
        : message(message)
{
}

std::string EmbodiedError::GetMessage() const
{
    return this->message;
}

EmbodiedArgumentError::EmbodiedArgumentError(const std::string &message, const boost::program_options::options_description &description)
        : EmbodiedError(message), description(description)
{
}

boost::program_options::options_description EmbodiedArgumentError::GetDescription() const
{
    return this->description;
}
// kate: indent-mode cstyle; space-indent on; indent-width 4;
