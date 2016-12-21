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

void expose_boxes()
{
    py::class_<AlignedBox3f>("AlignedBox3f", "Axis-aligned box object, defined by its minimum and maximum corners", py::init<>())
        .def(AabbVisitor<AlignedBox3f>());
    py::class_<AlignedBox3d>("AlignedBox3d", "Axis-aligned box object, defined by its minimum and maximum corners", py::init<>())
        .def(AabbVisitor<AlignedBox3d>());

    py::class_<AlignedBox2f>("AlignedBox2f", "Axis-aligned box object in 2d, defined by its minimum and maximum corners", py::init<>())
        .def(AabbVisitor<AlignedBox2f>());
    py::class_<AlignedBox2d>("AlignedBox2d", "Axis-aligned box object in 2d, defined by its minimum and maximum corners", py::init<>())
        .def(AabbVisitor<AlignedBox2d>());
}
