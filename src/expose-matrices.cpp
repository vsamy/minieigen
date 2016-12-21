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

void expose_matrices()
{
    py::class_<Matrix3f>("Matrix3f", "3x3 matrix of float.\n\nSupported operations (``m`` is a Matrix3f, ``f`` if a float/int, ``v`` is a Vector3f): ``-m``, ``m+m``, ``m+=m``, ``m-m``, ``m-=m``, ``m*f``, ``f*m``, ``m*=f``, ``m/f``, ``m/=f``, ``m*m``, ``m*=m``, ``m*v``, ``v*m``, ``m==m``, ``m!=m``.\n\nStatic attributes: ``Zero``, ``Ones``, ``Identity``.", py::init<>())
        .def(py::init<Quaternionf const&>((py::arg("q"))))
        .def(MatrixVisitor<Matrix3f>());
    py::class_<Matrix3d>("Matrix3d", "3x3 matrix of double.\n\nSupported operations (``m`` is a Matrix3d, ``f`` if a float/int, ``v`` is a Vector3d): ``-m``, ``m+m``, ``m+=m``, ``m-m``, ``m-=m``, ``m*f``, ``f*m``, ``m*=f``, ``m/f``, ``m/=f``, ``m*m``, ``m*=m``, ``m*v``, ``v*m``, ``m==m``, ``m!=m``.\n\nStatic attributes: ``Zero``, ``Ones``, ``Identity``.", py::init<>())
        .def(py::init<Quaterniond const&>((py::arg("q"))))
        .def(MatrixVisitor<Matrix3d>());
    py::class_<Matrix6f>("Matrix6f", "6x6 matrix of float. Constructed from 4 3x3 sub-matrices, from 6xVector6 (rows).\n\nSupported operations (``m`` is a Matrix6f, ``f`` if a float/int, ``v`` is a Vector6f): ``-m``, ``m+m``, ``m+=m``, ``m-m``, ``m-=m``, ``m*f``, ``f*m``, ``m*=f``, ``m/f``, ``m/=f``, ``m*m``, ``m*=m``, ``m*v``, ``v*m``, ``m==m``, ``m!=m``.\n\nStatic attributes: ``Zero``, ``Ones``, ``Identity``.", py::init<>())
        .def(MatrixVisitor<Matrix6f>());
    py::class_<Matrix6d>("Matrix6d", "6x6 matrix of double. Constructed from 4 3x3 sub-matrices, from 6xVector6 (rows).\n\nSupported operations (``m`` is a Matrix6d, ``f`` if a float/int, ``v`` is a Vector6d): ``-m``, ``m+m``, ``m+=m``, ``m-m``, ``m-=m``, ``m*f``, ``f*m``, ``m*=f``, ``m/f``, ``m/=f``, ``m*m``, ``m*=m``, ``m*v``, ``v*m``, ``m==m``, ``m!=m``.\n\nStatic attributes: ``Zero``, ``Ones``, ``Identity``.", py::init<>())
        .def(MatrixVisitor<Matrix6d>());
    py::class_<MatrixXf>("MatrixXf", "XxX (dynamic-sized) matrix of float. Constructed from list of rows (as VectorXf).\n\nSupported operations (``m`` is a MatrixXf, ``f`` if a float/int, ``v`` is a VectorXf): ``-m``, ``m+m``, ``m+=m``, ``m-m``, ``m-=m``, ``m*f``, ``f*m``, ``m*=f``, ``m/f``, ``m/=f``, ``m*m``, ``m*=m``, ``m*v``, ``v*m``, ``m==m``, ``m!=m``.", py::init<>())
        .def(MatrixVisitor<MatrixXf>());
    py::class_<MatrixXd>("MatrixXd", "XxX (dynamic-sized) matrix of double. Constructed from list of rows (as VectorXd).\n\nSupported operations (``m`` is a MatrixXd, ``f`` if a float/int, ``v`` is a VectorXd): ``-m``, ``m+m``, ``m+=m``, ``m-m``, ``m-=m``, ``m*f``, ``f*m``, ``m*=f``, ``m/f``, ``m/=f``, ``m*m``, ``m*=m``, ``m*v``, ``v*m``, ``m==m``, ``m!=m``.", py::init<>())
        .def(MatrixVisitor<MatrixXd>());
}
