#pragma once
// common types, funcs, includes; should be included by all other files

// BEGIN workaround for
// * http://eigen.tuxfamily.org/bz/show_bug.cgi?id=528
// * https://sourceforge.net/tracker/index.php?func=detail&aid=3584127&group_id=202880&atid=983354
// (only needed with gcc <= 4.7)
#include <stdlib.h>
#include <sys/stat.h>
// END workaround

#include <Eigen/Core>
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include <Eigen/SVD>

#include <unsupported/Eigen/AlignedVector3>

// integral type for indices, to avoid compiler warnings with int
typedef Eigen::Matrix<int, 1, 1>::Index Index;

/* exposed types */
typedef Eigen::Matrix<int, 2, 1> Vector2i;
typedef Eigen::Matrix<float, 2, 1> Vector2f;
typedef Eigen::Matrix<double, 2, 1> Vector2d;
typedef Eigen::Matrix<int, 3, 1> Vector3i;
typedef Eigen::Matrix<float, 3, 1> Vector3f;
typedef Eigen::Matrix<double, 3, 1> Vector3d;
typedef Eigen::AlignedVector3<float> Vector3fa;
typedef Eigen::AlignedVector3<double> Vector3da;
typedef Eigen::Matrix<float, 4, 1> Vector4f;
typedef Eigen::Matrix<double, 4, 1> Vector4d;
typedef Eigen::Matrix<int, 6, 1> Vector6i;
typedef Eigen::Matrix<float, 6, 1> Vector6f;
typedef Eigen::Matrix<double, 6, 1> Vector6d;
typedef Eigen::Matrix<float, 3, 3> Matrix3f;
typedef Eigen::Matrix<double, 3, 3> Matrix3d;
typedef Eigen::Matrix<float, 6, 6> Matrix6f;
typedef Eigen::Matrix<double, 6, 6> Matrix6d;

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXf;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
typedef Eigen::Matrix<float, Eigen::Dynamic, 1> VectorXf;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1> VectorXd;

typedef Eigen::Quaternion<float> Quaternionf;
typedef Eigen::Quaternion<double> Quaterniond;
typedef Eigen::AngleAxis<float> AngleAxisf;
typedef Eigen::AngleAxis<double> AngleAxisd;
typedef Eigen::AlignedBox<float, 3> AlignedBox3f;
typedef Eigen::AlignedBox<double, 3> AlignedBox3d;
typedef Eigen::AlignedBox<float, 2> AlignedBox2f;
typedef Eigen::AlignedBox<double, 2> AlignedBox2d;

#define _COMPLEX_SUPPORT

#ifdef _COMPLEX_SUPPORT
#include <complex>
using std::complex;
typedef Eigen::Matrix<complex<float>, 2, 1> Vector2cf;
typedef Eigen::Matrix<complex<double>, 2, 1> Vector2cd;
typedef Eigen::Matrix<complex<float>, 3, 1> Vector3cf;
typedef Eigen::Matrix<complex<double>, 3, 1> Vector3cd;
typedef Eigen::Matrix<complex<float>, 6, 1> Vector6cf;
typedef Eigen::Matrix<complex<double>, 6, 1> Vector6cd;
typedef Eigen::Matrix<complex<float>, Eigen::Dynamic, 1> VectorXcf;
typedef Eigen::Matrix<complex<double>, Eigen::Dynamic, 1> VectorXcd;
typedef Eigen::Matrix<complex<float>, 3, 3> Matrix3cf;
typedef Eigen::Matrix<complex<double>, 3, 3> Matrix3cd;
typedef Eigen::Matrix<complex<float>, 6, 6> Matrix6cf;
typedef Eigen::Matrix<complex<double>, 6, 6> Matrix6cd;
typedef Eigen::Matrix<complex<float>, Eigen::Dynamic, Eigen::Dynamic> MatrixXcf;
typedef Eigen::Matrix<complex<double>, Eigen::Dynamic, Eigen::Dynamic> MatrixXcd;
#endif

#include <string>
using std::string;
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <boost/python.hpp>
namespace py = boost::python;
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <boost/static_assert.hpp>

/**** double-conversion helpers *****/
#include "double-conversion/double-conversion.h"

static double_conversion::DoubleToStringConverter doubleToString(
    double_conversion::DoubleToStringConverter::NO_FLAGS,
    "inf", /* infinity symbol */
    "nan", /* NaN symbol */
    'e', /*exponent symbol*/
    -5, /* decimal_in_shortest_low: 0.0001, but 0.00001->1e-5 */
    7, /* decimal_in_shortest_high */
    /* the following are irrelevant for the shortest representation */
    6, /* max_leading_padding_zeroes_in_precision_mode */
    6 /* max_trailing_padding_zeroes_in_precision_mode */
    );

/* optionally pad from the left */
static inline string doubleToShortest(double d, int pad = 0)
{
    /* 32 is perhaps wasteful */
    /* it would be better to write to the string's buffer itself, not sure how to do that */
    char buf[32];
    double_conversion::StringBuilder sb(buf, 32);
    doubleToString.ToShortest(d, &sb);
    string ret(sb.Finalize());
    if (pad == 0 || (int)ret.size() >= pad)
        return ret;
    return string(static_cast<size_t>(pad) - ret.size(), ' ') + ret; // left-padded if shorter
}

/* generic function to print numbers, via lexical_cast plus padding -- used for ints */
template <typename T>
string num_to_string(const T& num, int pad = 0)
{
    string ret(lexical_cast<string>(num));
    if (pad == 0 || (int)ret.size() >= pad)
        return ret;
    return string(static_cast<size_t>(pad) - ret.size(), ' ') + ret; // left-pad with spaces
}

// for doubles, use the shortest representation
static inline string num_to_string(const double& num, int pad = 0) { return doubleToShortest(num, pad); }

#ifdef _COMPLEX_SUPPORT
// for complex numbers (with any scalar type, though only doubles are really used)
template <typename T>
string num_to_string(const complex<T>& num, int pad = 0)
{
    string ret;
    // both components non-zero
    if (num.real() != 0 && num.imag() != 0) {
        // don't add "+" in the middle if imag is negative and will start with "-"
        string ret = num_to_string(num.real(), /*pad*/ 0) + (num.imag() > 0 ? "+" : "") + num_to_string(num.imag(), /*pad*/ 0) + "j";
        if (pad == 0 || (int)ret.size() >= pad)
            return ret;
        return string(static_cast<size_t>(pad) - ret.size(), ' ') + ret; // left-pad with spaces
    }
    // only imaginary is non-zero: skip the real part, and decrease padding to accomoadate the trailing "j"
    if (num.imag() != 0) {
        return num_to_string(num.imag(), /*pad*/ pad > 0 ? pad - 1 : 0) + "j";
    }
    // non-complex (zero or not)
    return num_to_string(num.real(), pad);
}
#endif

/*** getters and setters with bound guards ***/
static inline void IDX_CHECK(Index i, Index MAX)
{
    if (i < 0 || i >= MAX) {
        PyErr_SetString(PyExc_IndexError, ("Index " + lexical_cast<string>(i) + " out of range 0.." + lexical_cast<string>(MAX - 1)).c_str());
        py::throw_error_already_set();
    }
}
static inline void IDX2_CHECKED_TUPLE_INTS(py::tuple tuple, const Index max2[2], Index arr2[2])
{
    Index l = py::len(tuple);
    if (l != 2) {
        PyErr_SetString(PyExc_IndexError, "Index must be integer or a 2-tuple");
        py::throw_error_already_set();
    }
    for (int _i = 0; _i < 2; _i++) {
        py::extract<Index> val(tuple[_i]);
        if (!val.check()) {
            PyErr_SetString(PyExc_ValueError, ("Unable to convert " + lexical_cast<string>(_i) + "-th index to integer.").c_str());
            py::throw_error_already_set();
        }
        Index v = val();
        IDX_CHECK(v, max2[_i]);
        arr2[_i] = v;
    }
}

static inline string object_class_name(const py::object& obj) { return py::extract<string>(obj.attr("__class__").attr("__name__"))(); }
