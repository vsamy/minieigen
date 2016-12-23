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

#include "stlVisitor.hpp"

void expose_stl_vectors()
{
    py::class_<vectorOfTripletf>("vectorOfTripletf", "*TODO*", py::init<>())
        .def(STLVectorVisitor<vectorOfTripletf, Index, Index, float>());
    py::class_<vectorOfTripletd>("vectorOfTripletd", "*TODO*", py::init<>())
        .def(STLVectorVisitor<vectorOfTripletd, Index, Index, double>());
}