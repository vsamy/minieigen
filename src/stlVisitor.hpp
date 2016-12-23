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

#include <common.hpp>
#include <vector>

template <typename STLVector, typename... ConstructorParams>
class STLVectorVisitor : public py::def_visitor<STLVectorVisitor<STLVector>>{
public:
    friend class def_visitor_access;
    typedef typename STLVector::value_type STLType;
    template <class PyClass>
    void visit(PyClass& cl) const
    {
        cl
            .def("__len__", &STLVectorVisitor::__len__)
            .def("__getitem__", &STLVectorVisitor::__getitem__, py::return_internal_reference<>())
            .def("__setitem__", &STLVectorVisitor::__setitem__, py::with_custodian_and_ward<1,3>())
            .def("__iter__", py::iterator<STLVector>())
            .def("reserve", &STLVector::reserve)
            .def("append", &STLVectorVisitor::append, py::with_custodian_and_ward<1,2>())
            .def("buildAndAppend", &STLVectorVisitor::buildAndAppend) // Pas sûr que ça marche.
            .def("clear", &STLVector::clear);
    }
private:
    static size_t __len__(const STLVector& vector) { return vector.size(); }
    static const STLType& __getitem__(const STLVector& vector, Index i) { 
        IDX_CHECK(i, vector.size());
        return vector[i];
    }
    static void __setitem__(STLVector& vector, Index i, const STLType& v) { 
        if (i < 0)
            i += vector.size(); // Allow to call vec[-1] in python side.
        IDX_CHECK(i, vector.size());
        vector[i] = v;
    }
    static void append(STLVector& vector, const STLType& v) { vector.push_back(v); }
    static void buildAndAppend(STLVector& vector, ConstructorParams... params) { vector.emplace_back(params...); }
};