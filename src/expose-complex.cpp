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

void expose_complex()
{
#ifdef _COMPLEX_SUPPORT
    py::class_<Vector2cf>("Vector2cf", "/*TODO*/", py::init<>()).def(VectorVisitor<Vector2cf>());
    py::class_<Vector2cd>("Vector2cd", "/*TODO*/", py::init<>()).def(VectorVisitor<Vector2cd>());
    py::class_<Vector3cf>("Vector3cf", "/*TODO*/", py::init<>()).def(VectorVisitor<Vector3cf>());
    py::class_<Vector3cd>("Vector3cd", "/*TODO*/", py::init<>()).def(VectorVisitor<Vector3cd>());
    py::class_<Vector6cf>("Vector6cf", "/*TODO*/", py::init<>()).def(VectorVisitor<Vector6cf>());
    py::class_<Vector6cd>("Vector6cd", "/*TODO*/", py::init<>()).def(VectorVisitor<Vector6cd>());
    py::class_<VectorXcf>("VectorXcf", "/*TODO*/", py::init<>()).def(VectorVisitor<VectorXcf>());
    py::class_<VectorXcd>("VectorXcd", "/*TODO*/", py::init<>()).def(VectorVisitor<VectorXcd>());

    py::class_<Matrix3cf>("Matrix3cf", "/*TODO*/", py::init<>()).def(MatrixVisitor<Matrix3cf>());
    py::class_<Matrix3cd>("Matrix3cd", "/*TODO*/", py::init<>()).def(MatrixVisitor<Matrix3cd>());
    py::class_<Matrix6cf>("Matrix6cf", "/*TODO*/", py::init<>()).def(MatrixVisitor<Matrix6cf>());
    py::class_<Matrix6cd>("Matrix6cd", "/*TODO*/", py::init<>()).def(MatrixVisitor<Matrix6cd>());
    py::class_<MatrixXcf>("MatrixXcf", "/*TODO*/", py::init<>()).def(MatrixVisitor<MatrixXcf>());
    py::class_<MatrixXcd>("MatrixXcd", "/*TODO*/", py::init<>()).def(MatrixVisitor<MatrixXcd>());
    ;
#endif
}
