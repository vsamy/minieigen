#include "visitors.hpp"
void expose_vectors()
{
    py::class_<VectorXf>("VectorXf", "Dynamic-sized float vector.\n\nSupported operations (``f`` if a float/int, ``v`` is a VectorX): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of X floats.", py::init<>())
        .def(VectorVisitor<VectorXf>());

    py::class_<VectorXd>("VectorXd", "Dynamic-sized double vector.\n\nSupported operations (``f`` if a float/int, ``v`` is a VectorX): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of X floats.", py::init<>())
        .def(VectorVisitor<VectorXd>());

    py::class_<Vector6f>("Vector6f", "6-dimensional vector of float.\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector6d): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of 6 floats.\n\nStatic attributes: ``Zero``, ``Ones``.", py::init<>())
        .def(VectorVisitor<Vector6f>());

    py::class_<Vector6d>("Vector6d", "6-dimensional vector of double.\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector6s): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of 6 floats.\n\nStatic attributes: ``Zero``, ``Ones``.", py::init<>())
        .def(VectorVisitor<Vector6d>());

    py::class_<Vector6i>("Vector6i", "6-dimensional float vector.\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector6i): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of 6 floats.\n\nStatic attributes: ``Zero``, ``Ones``.", py::init<>())
        .def(VectorVisitor<Vector6i>());

// broken
#if 0
		py::class_<Vector4r>("Vector4","4-dimensional float vector.\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector3): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of 4 floats.\n\nStatic attributes: ``Zero``, ``Ones``.",py::init<>())
			.def(VectorVisitor<Vector4r>())
		;
#endif

    py::class_<Vector3f>("Vector3f", "3-dimensional vector of float.\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector3f): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``, plus operations with ``Matrix3`` and ``Quaternion``.\n\nImplicit conversion from sequence (list, tuple, ...) of 3 floats.\n\nStatic attributes: ``Zero``, ``Ones``, ``UnitX``, ``UnitY``, ``UnitZ``.", py::init<>())
        .def(VectorVisitor<Vector3f>());

    py::class_<Vector3d>("Vector3d", "3-dimensional vector of double.\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector3d): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``, plus operations with ``Matrix3`` and ``Quaternion``.\n\nImplicit conversion from sequence (list, tuple, ...) of 3 floats.\n\nStatic attributes: ``Zero``, ``Ones``, ``UnitX``, ``UnitY``, ``UnitZ``.", py::init<>())
        .def(VectorVisitor<Vector3d>());
#ifndef EIGEN_DONT_ALIGN
    py::class_<Vector3fa>("Vector3fa", "3-dimensional vector of float; same as :obj:`Vector3`, but with alignment (``Eigen::AlignedVector3f``).\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector3f): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``, plus operations with ``Matrix3`` and ``Quaternion``.\n\nImplicit conversion from sequence (list, tuple, ...) of 3 floats.\n\nStatic attributes: ``Zero``, ``Ones``, ``UnitX``, ``UnitY``, ``UnitZ``.", py::init<>())
        .def(VectorVisitor<Vector3fa>());
    py::class_<Vector3da>("Vector3da", "3-dimensional vector of double; same as :obj:`Vector3`, but with alignment (``Eigen::AlignedVector3d``).\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector3d): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``, plus operations with ``Matrix3`` and ``Quaternion``.\n\nImplicit conversion from sequence (list, tuple, ...) of 3 floats.\n\nStatic attributes: ``Zero``, ``Ones``, ``UnitX``, ``UnitY``, ``UnitZ``.", py::init<>())
        .def(VectorVisitor<Vector3da>());
#endif

    py::class_<Vector3i>("Vector3i", "3-dimensional integer vector.\n\nSupported operations (``i`` if an int, ``v`` is a Vector3i): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*i``, ``i*v``, ``v*=i``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence  (list, tuple, ...) of 3 integers.\n\nStatic attributes: ``Zero``, ``Ones``, ``UnitX``, ``UnitY``, ``UnitZ``.", py::init<>())
        .def(VectorVisitor<Vector3i>());

    py::class_<Vector2f>("Vector2f", "3-dimensional vector of float.\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector3f): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of 2 floats.\n\nStatic attributes: ``Zero``, ``Ones``, ``UnitX``, ``UnitY``.", py::init<>())
        .def(VectorVisitor<Vector2f>());
    py::class_<Vector2d>("Vector2d", "3-dimensional vector of double.\n\nSupported operations (``f`` if a float/int, ``v`` is a Vector3d): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*f``, ``f*v``, ``v*=f``, ``v/f``, ``v/=f``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of 2 floats.\n\nStatic attributes: ``Zero``, ``Ones``, ``UnitX``, ``UnitY``.", py::init<>())
        .def(VectorVisitor<Vector2d>());
    py::class_<Vector2i>("Vector2i", "2-dimensional integer vector.\n\nSupported operations (``i`` if an int, ``v`` is a Vector2i): ``-v``, ``v+v``, ``v+=v``, ``v-v``, ``v-=v``, ``v*i``, ``i*v``, ``v*=i``, ``v==v``, ``v!=v``.\n\nImplicit conversion from sequence (list, tuple, ...) of 2 integers.\n\nStatic attributes: ``Zero``, ``Ones``, ``UnitX``, ``UnitY``.", py::init<>())
        .def(VectorVisitor<Vector2i>());
}
