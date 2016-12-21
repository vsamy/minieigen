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

void expose_quaternion()
{
    py::class_<Quaternionf>("Quaternionf", "Quaternion representing rotation.\n\nSupported operations (``q`` is a Quaternion, ``v`` is a Vector3): ``q*q`` (rotation composition), ``q*=q``, ``q*v`` (rotating ``v`` by ``q``), ``q==q``, ``q!=q``.\n\nStatic attributes: ``Identity``.\n\n.. note:: Quaternion is represented as axis-angle when printed (e.g. ``Identity`` is ``Quaternion((1,0,0),0)``, and can also be constructed from the axis-angle representation. This is however different from the data stored inside, which can be accessed by indices ``[0]`` (:math:`x`), ``[1]`` (:math:`y`), ``[2]`` (:math:`z`), ``[3]`` (:math:`w`). To obtain axis-angle programatically, use :obj:`Quaternion.toAxisAngle` which returns the tuple.", py::init<>())
        .def(QuaternionVisitor<Quaternionf>());
    py::class_<Quaterniond>("Quaterniond", "Quaternion representing rotation.\n\nSupported operations (``q`` is a Quaternion, ``v`` is a Vector3): ``q*q`` (rotation composition), ``q*=q``, ``q*v`` (rotating ``v`` by ``q``), ``q==q``, ``q!=q``.\n\nStatic attributes: ``Identity``.\n\n.. note:: Quaternion is represented as axis-angle when printed (e.g. ``Identity`` is ``Quaternion((1,0,0),0)``, and can also be constructed from the axis-angle representation. This is however different from the data stored inside, which can be accessed by indices ``[0]`` (:math:`x`), ``[1]`` (:math:`y`), ``[2]`` (:math:`z`), ``[3]`` (:math:`w`). To obtain axis-angle programatically, use :obj:`Quaternion.toAxisAngle` which returns the tuple.", py::init<>())
        .def(QuaternionVisitor<Quaterniond>());
}
