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

#pragma once

#include "common.hpp"
/*** automatic conversions from non-eigen types (sequences) ***/

/* template to define custom converter from sequence/list or approriate length and type, to eigen's Vector
   - length is stored in VT::RowsAtCompileTime
	- type is VT::Scalar
*/

template <typename T>
bool pySeqItemCheck(PyObject* o, Py_ssize_t i) { return py::extract<T>(py::object(py::handle<>(PySequence_GetItem(o, i)))).check(); }

template <typename T>
T pySeqItemExtract(PyObject* o, Py_ssize_t i) { return py::extract<T>(py::object(py::handle<>(PySequence_GetItem(o, i))))(); }

template <class VT>
struct custom_VectorAnyAny_from_sequence {
    custom_VectorAnyAny_from_sequence() { py::converter::registry::push_back(&convertible, &construct, py::type_id<VT>()); }
    static void* convertible(PyObject* obj_ptr)
    {
        if (!PySequence_Check(obj_ptr) || (VT::RowsAtCompileTime != Eigen::Dynamic && (PySequence_Size(obj_ptr) != VT::RowsAtCompileTime)))
            return 0;
        // check that sequence items are convertible to scalars (should be done in other converters as well?!); otherwise Matrix3 is convertible to Vector3, but then we fail in *construct* very unclearly (TypeError: No registered converter was able to produce a C++ rvalue of type double from this Python object of type Vector3)
        Py_ssize_t len = PySequence_Size(obj_ptr);
        for (Py_ssize_t i = 0; i < len; i++)
            if (!pySeqItemCheck<typename VT::Scalar>(obj_ptr, i))
                return 0;
        return obj_ptr;
    }
    static void construct(PyObject* obj_ptr, py::converter::rvalue_from_python_stage1_data* data)
    {
        using storage_type = py::converter::rvalue_from_python_storage<VT>;
        void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;
        new (storage) VT;
        Py_ssize_t len;
        if (VT::RowsAtCompileTime != Eigen::Dynamic) {
            len = VT::RowsAtCompileTime;
        } else {
            len = PySequence_Size(obj_ptr);
            ((VT*)storage)->resize(len);
        }
        for (Py_ssize_t i = 0; i < len; i++)
            (*((VT*)storage))[i] = pySeqItemExtract<typename VT::Scalar>(obj_ptr, i);
        data->convertible = storage;
    }
};

template <class MT>
struct custom_MatrixAnyAny_from_sequence {
    custom_MatrixAnyAny_from_sequence() { py::converter::registry::push_back(&convertible, &construct, py::type_id<MT>()); }
    static void* convertible(PyObject* obj_ptr)
    {
        if (!PySequence_Check(obj_ptr))
            return 0;
        bool isFlat = !PySequence_Check(py::handle<>(PySequence_GetItem(obj_ptr, 0)).get());
        // mixed static/dynamic not handled (also not needed)
        BOOST_STATIC_ASSERT(
            (MT::RowsAtCompileTime != Eigen::Dynamic && MT::ColsAtCompileTime != Eigen::Dynamic)
            || (MT::RowsAtCompileTime == Eigen::Dynamic && MT::ColsAtCompileTime == Eigen::Dynamic));
        Py_ssize_t sz = PySequence_Size(obj_ptr);
        if (MT::RowsAtCompileTime != Eigen::Dynamic) {
            if (isFlat) {
                // flat sequence (first item not sub-sequence), must contain exactly all items
                if (sz != MT::RowsAtCompileTime * MT::ColsAtCompileTime)
                    return 0;
            } else {
                // contains nested sequences, one per row
                if (sz != MT::RowsAtCompileTime)
                    return 0;
            }
        };
        return obj_ptr;
        // other checks done in the construct function
        // FIXME: it may be too late to do it there, as overloads are chosen based on *convertible*
        // (at least a clear message should be given when py::extract fails there)
    }
    static void construct(PyObject* obj_ptr, py::converter::rvalue_from_python_stage1_data* data)
    {
        using storage_type = py::converter::rvalue_from_python_storage<MT>;
        void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;
        new (storage) MT;
        MT& mx = *(MT*)storage;
        Py_ssize_t sz = PySequence_Size(obj_ptr);
        bool isFlat = !PySequence_Check(py::handle<>(PySequence_GetItem(obj_ptr, 0)).get());
        if (MT::RowsAtCompileTime != Eigen::Dynamic) {
            // do nothing
        } else {
            // find the right size
            if (isFlat)
                mx.resize(sz, 1); // row vector, if flat
            else { // find maximum size of items
                Py_ssize_t rows = sz;
                Py_ssize_t cols = 0;
                for (Py_ssize_t i = 0; i < rows; i++) {
                    if (!PySequence_Check(py::handle<>(PySequence_GetItem(obj_ptr, i)).get()))
                        throw std::runtime_error("Some elements of the array given are not sequences");
                    Py_ssize_t cols2 = PySequence_Size(py::handle<>(PySequence_GetItem(obj_ptr, i)).get());
                    if (cols == 0)
                        cols = cols2;
                    if (cols != cols2)
                        throw std::runtime_error("Not all sub-sequences have the same length when assigning dynamic-sized matrix.");
                }
                mx.resize(rows, cols);
            }
        }
        if (isFlat) {
            if (sz != mx.rows() * mx.cols())
                throw std::runtime_error("Assigning matrix " + lexical_cast<string>(mx.rows()) + "x" + lexical_cast<string>(mx.cols()) + " from flat vector of size " + lexical_cast<string>(sz));
            for (int i = 0; i < sz; i++) {
                mx(i, 0) = pySeqItemExtract<typename MT::Scalar>(obj_ptr, i);
            }
        } else {
            for (Index row = 0; row < mx.rows(); row++) {
                if (row >= PySequence_Size(obj_ptr))
                    throw std::runtime_error("Sequence rows of size " + lexical_cast<string>(sz) + " too short for assigning matrix with " + lexical_cast<string>(mx.rows()) + " rows.");
                py::handle<> rowSeq(PySequence_GetItem(obj_ptr, row));
                if (!PySequence_Check(rowSeq.get()))
                    throw std::runtime_error("Element of row sequence not a sequence.");
                if (mx.cols() != PySequence_Size(rowSeq.get()))
                    throw std::runtime_error("Row " + lexical_cast<string>(row) + ": should specify exactly " + lexical_cast<string>(mx.cols()) + " numbers, has " + lexical_cast<string>(PySequence_Size(rowSeq.get())));
                for (Index col = 0; col < mx.cols(); col++) {
                    mx(row, col) = pySeqItemExtract<typename MT::Scalar>(rowSeq.get(), col);
                }
            }
        }
        data->convertible = storage;
    }
};

// create AlignedBoxNr from tuple of 2 Vector3r's
template <class AlignedBoxNT, class VectorT>
struct custom_alignedBoxNT_from_seq {
    custom_alignedBoxNT_from_seq()
    {
        py::converter::registry::push_back(&convertible, &construct, py::type_id<AlignedBoxNT>());
    }
    static void* convertible(PyObject* obj_ptr)
    {
        if (!PySequence_Check(obj_ptr))
            return 0;
        if (PySequence_Size(obj_ptr) != 2)
            return 0;
        if (!pySeqItemCheck<VectorT>(obj_ptr, 0) || !pySeqItemCheck<VectorT>(obj_ptr, 1))
            return 0;
        return obj_ptr;
    }
    static void construct(PyObject* obj_ptr, py::converter::rvalue_from_python_stage1_data* data)
    {
        using storage_type = py::converter::rvalue_from_python_storage<AlignedBoxNT>;
        void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;
        new (storage) AlignedBoxNT(pySeqItemExtract<VectorT>(obj_ptr, 0), pySeqItemExtract<VectorT>(obj_ptr, 1));
        data->convertible = storage;
    }
};

template <class QuaternionT>
struct custom_Quaternion_from_axisAngle_or_angleAxis {
    typedef typename QuaternionT::Scalar Scalar;
    typedef Eigen::Matrix<Scalar, 3, 1> Vector3;
    typedef Eigen::AngleAxis<Scalar> AngleAxis;
    custom_Quaternion_from_axisAngle_or_angleAxis()
    {
        py::converter::registry::push_back(&convertible, &construct, py::type_id<QuaternionT>());
    }
    static void* convertible(PyObject* obj_ptr)
    {
        if (!PySequence_Check(obj_ptr))
            return 0;
        if (PySequence_Size(obj_ptr) != 2)
            return 0;
        py::object a(py::handle<>(PySequence_GetItem(obj_ptr, 0))), b(py::handle<>(PySequence_GetItem(obj_ptr, 1)));
        // axis-angle or angle-axis
        if ((py::extract<Vector3>(a).check() && py::extract<Scalar>(b).check()) || (py::extract<Scalar>(a).check() && py::extract<Vector3>(b).check()))
            return obj_ptr;
        return 0;
    }
    static void construct(PyObject* obj_ptr, py::converter::rvalue_from_python_stage1_data* data)
    {
        using storage_type = py::converter::rvalue_from_python_storage<QuaternionT>;
        void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;
        py::object a(py::handle<>(PySequence_GetItem(obj_ptr, 0))), b(py::handle<>(PySequence_GetItem(obj_ptr, 1)));
        if (py::extract<Vector3>(py::object(a)).check())
            new (storage) QuaternionT(AngleAxis(py::extract<Scalar>(b)(), py::extract<Vector3>(a)().normalized()));
        else
            new (storage) QuaternionT(AngleAxis(py::extract<Scalar>(a)(), py::extract<Vector3>(b)().normalized()));
        data->convertible = storage;
    }
};
