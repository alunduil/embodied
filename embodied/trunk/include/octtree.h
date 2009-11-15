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

#ifndef OCTTREE_H
#define OCTTREE_H

#include <vector>

#include "../include/point.h"

class OctTree
{
    public:
        /**
         * @brief Cosntructor.
         * @param region The region this tree covers.
         */
        OctTree(const std::vector<std::vector<double> > & region, const double & distance, const bool & verbose, const bool & debug);

        /**
         * @brief Insert a point into the tree.
         * @param point The point to insert into the tree.
         */
        void Insert(const Point & point);

        /**
         * @brief Calculate the Potential.
         * @param region The region to calculate the potential for.
         * @param steps The number of steps in each direction to calculate for.
         */
        std::vector<std::vector<std::vector<double> > > CalculatePotential(std::vector< std::vector< double * > >& region, const int& steps);
    private:

        struct Node
        {
            Point * CenterApproximation;
            double Density;
            Node * Children[8];
            int ChildCount;
            std::vector<std::vector<double> > Region;
        };

        Node * root;
        bool debug;
        bool verbose;
        double dist;

        /**
         * @brief Insert a point into the tree rooted at n.
         * @param point The point to insert into the tree.
         * @param n The node to start inserting at.
         */
        void insert(const Point& point, OctTree::Node* n);

        /**
         * @brief Determine if a point is contained in a region.
         * @param point The point to check.
         * @param region The region to check against.
         * @return True if the point is in the region.
         */
        bool contained(const Point & point, const std::vector<std::vector<double> > & region);

        /**
         * @brief Find the center of the region.
         * @param region The region to find the center of.
         * @return A 3-tuple with the center of the region.
         */
        std::vector<double> center(const std::vector<std::vector<double> > & region);

        /**
         * @brief Find the volume of the region.
         * @param region The region to find the volume of.
         * @return The volume of the region.
         */
        double volume(const std::vector<std::vector<double> > & region);

        /**
         * @brief Calculate the subregion of a region.
         * @param region The region to split.
         * @param i The region to get.
         */
        std::vector<std::vector<double> > subRegion(const std::vector<std::vector<double> > & region, const int & i);

        /**
         * @brief Add a new node for the point.
         * @param point The point to add.
         */
        Node * addPoint(const Point& point);

        /**
         * @brief Print the prefix traversal of the tree.
         * @param node The start Node to print from.
         */
        std::string print(Node * node);

        /**
         * @brief The magnitude of the vector passed.
         * @param dim The number of elements in k.
         * @param k The vector to get the magnitude of.
         * @return The magnitude of the vector k.
         */
        double magnitude(size_t dim, double * k);

        /**
         * @brief The function to integrate.
         * @param dim The number of elements in point and mass.
         * @param point The point to calculate at.
         * @param mass The point of mass.
         * @return The result of our Legendre Polynomial expansion of 1/|r-r_o|.
         */
        double integrand(size_t dim, double * point, double * mass);

        /**
         * @brief Calculate the potential on a point due to a node.
         * @param dim The number of elements in point.
         * @param point The point of interest.
         * @param n The node to start at.
         * @return The result of all masses on this point.
         */
        double calculatePotential(size_t dim, double * point, Node * n);

        /**
         * @brief Find the distance between two vectors.
         * @param dim The number of elements in the vectors.
         * @param k The point to start at.
         * @param l The point to finish at.
         * @return The distance between k and l.
         */
        double distance(size_t dim, double * k, double * l);
};

#endif // OCTTREE_H
// kate: indent-mode cstyle; space-indent on; indent-width 4;
