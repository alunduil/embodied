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

#include "../include/embodied.h"
#include "../include/cell.h"
#include "../include/points.h"
#include "../include/point.h"

Embodied::Embodied(int argc, char *argv[])
:space(NULL)
{
    using namespace boost::program_options;
    std::string usage;
    usage += "Usage: "; usage += argv[0]; usage += " [options] [region]";
    options_description description(usage);
    variables_map variables;
    try
    {
        variables = this->parseOptions(argc, argv, &description);
    }
    catch (...)
    {
        throw new EmbodiedArgumentError(usage, description);
    }
    if (variables.count("help") > 0) throw new EmbodiedArgumentError(usage, description);
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
    this->space = new Points(variables["maxpoints"].as<int>());
    for (std::vector<Point *>::iterator i = points.begin(); i != points.end(); ++i)
        this->space->AddPoint(**i);
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
    ("filename,f", value<std::vector<std::string> >(), "The files to read points from.")
    ("maxpoints,m", value<int>(), "The maximum points in a leaf node.")
    ("output,o", value<std::string>(), "The output filename.")
    ("region,r", value<std::string>(), "The region of interest.  This is specified as ((x1, y1), (x2, y2)), where x1 can equal x2 and y1 can equal y2.")
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
    return space->CalculatePotential();
}

EmbodiedError::EmbodiedError(const std::string &message)
:message(message)
{
}

std::string EmbodiedError::GetMessage() const
{
    return this->message;
}

EmbodiedArgumentError::EmbodiedArgumentError(const std::string &message, const boost::program_options::options_description &description)
:EmbodiedError(message), description(description)
{
}

boost::program_options::options_description EmbodiedArgumentError::GetDescription() const
{
    return this->description;
}
