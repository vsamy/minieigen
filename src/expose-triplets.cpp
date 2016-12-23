// This file is part of minieigen.

// minieigen is free software: you can redistribute it and/or
// modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// minieigen is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with minieigen.  If not, see
// <http://www.gnu.org/licenses/>.

#include "visitors.hpp"

void expose_triplets()
{
    py::class_<Tripletf>("Tripletf", "Define an Eigen::Triplet of float",py::init<>())
        .def(TripletVisitor<Tripletf, float>());
    py::class_<Tripletd>("Tripletd", "Define an Eigen::Triplet of double", py::init<>())
        .def(TripletVisitor<Tripletd, double>());
}