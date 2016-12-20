#include "converters.hpp"
void expose_converters()
{
    custom_VectorAnyAny_from_sequence<VectorXf>();
    custom_VectorAnyAny_from_sequence<VectorXd>();
    custom_VectorAnyAny_from_sequence<Vector6f>();
    custom_VectorAnyAny_from_sequence<Vector6d>();
    custom_VectorAnyAny_from_sequence<Vector6i>();
    custom_VectorAnyAny_from_sequence<Vector3f>();
    custom_VectorAnyAny_from_sequence<Vector3d>();
    custom_VectorAnyAny_from_sequence<Vector3i>();
    custom_VectorAnyAny_from_sequence<Vector2f>();
    custom_VectorAnyAny_from_sequence<Vector2d>();
    custom_VectorAnyAny_from_sequence<Vector2i>();
    custom_alignedBoxNT_from_seq<AlignedBox2f, Vector2f>();
    custom_alignedBoxNT_from_seq<AlignedBox2d, Vector2d>();
    custom_alignedBoxNT_from_seq<AlignedBox3f, Vector3f>();
    custom_alignedBoxNT_from_seq<AlignedBox3d, Vector3d>();
    custom_Quaternion_from_axisAngle_or_angleAxis<Quaternionf>();
    custom_Quaternion_from_axisAngle_or_angleAxis<Quaterniond>();

    custom_MatrixAnyAny_from_sequence<Matrix3f>();
    custom_MatrixAnyAny_from_sequence<Matrix3d>();
    custom_MatrixAnyAny_from_sequence<Matrix6f>();
    custom_MatrixAnyAny_from_sequence<Matrix6d>();
    custom_MatrixAnyAny_from_sequence<MatrixXf>();
    custom_MatrixAnyAny_from_sequence<MatrixXd>();

#ifdef _COMPLEX_SUPPORT
    custom_VectorAnyAny_from_sequence<Vector2cf>();
    custom_VectorAnyAny_from_sequence<Vector2cd>();
    custom_VectorAnyAny_from_sequence<Vector3cf>();
    custom_VectorAnyAny_from_sequence<Vector3cd>();
    custom_VectorAnyAny_from_sequence<Vector6cf>();
    custom_VectorAnyAny_from_sequence<Vector6cd>();
    custom_VectorAnyAny_from_sequence<VectorXcf>();
    custom_VectorAnyAny_from_sequence<VectorXcd>();
    custom_MatrixAnyAny_from_sequence<Matrix3cf>();
    custom_MatrixAnyAny_from_sequence<Matrix3cd>();
    custom_MatrixAnyAny_from_sequence<Matrix6cf>();
    custom_MatrixAnyAny_from_sequence<Matrix6cd>();
    custom_MatrixAnyAny_from_sequence<MatrixXcf>();
    custom_MatrixAnyAny_from_sequence<MatrixXcd>();
#endif
}
