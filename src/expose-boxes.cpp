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
