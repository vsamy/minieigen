import unittest
from minieigen import *
import math

class TestEigen(unittest.TestCase):
    def setUp(self):
        # Vectors (Add 3i)
        self.vZ3f = Vector3f(0, 0, 0)
        self.vZ3d = Vector3d(0, 0, 0)
        self.vZ6f = Vector6f(0,0,0,0,0,0)
        self.vZ6d = Vector6d(0,0,0,0,0,0)
        self.v2f = Vector2f.Random()
        self.v2d = Vector2d.Random()
        self.v3f = Vector3f.Random()
        self.v3d = Vector3d.Random()
        self.v3cf = Vector3cf(1,5j,1-3j)
        self.v3cd = Vector3cd(1,5j,1-3j)
        self.v6f = Vector6f(0,1,2, 3,4,5)
        self.v6d = Vector6d(0,1,2, 3,4,5)
        self.vXf = VectorXf.Random(7)
        self.vXd = VectorXd.Random(7)
        # Other constructor test
        Vector6d((0,1,2),(3,4,5))
        Vector6d((0,1,2),(3,4,5))
        VectorXf.Ones(11)

        # Matrices
        self.m3f = Matrix3f.Random()
        self.m3d = Matrix3d.Random()
        self.m6f = Matrix6f.Random()
        self.m6d = Matrix6d.Random()
        self.mXf = MatrixXf.Random(8,5)
        self.mXd = MatrixXd.Random(8,5)
        # Other constructor test
        MatrixXd.Identity(4, 7)
        Matrix3d(0,1,2, 3,4,5, 6,7,8)

        # Aligned box
        self.boxf = AlignedBox3f((1,2,3),(4,5,6))
        self.boxd = AlignedBox3d((1,2,3),(4,5,6))

        # Quaternion
        self.qf = Quaternionf.Identity
        self.qd = Quaterniond.Identity

    def test_vectors(self):
        self.assertTrue(self.vZ3f == Vector3f.Zero)
        self.assertTrue(self.vZ3d == Vector3d.Zero)
        self.assertTrue(self.vZ6f == Vector6f.Zero)
        self.assertTrue(self.vZ6d == Vector6d.Zero)
        self.assertTrue(self.vZ3f != Vector3f(1, 1, 1))
        self.assertTrue(self.vZ3d != Vector3d(1, 1, 1))
        self.assertTrue(self.vZ6f != Vector6f(1, 1, 1, 1, 1, 1))
        self.assertTrue(self.vZ6d != Vector6d(1, 1, 1, 1, 1, 1))
        self.assertEqual(Vector3i(1, 2, 3).sum(), 6)
        self.assertEqual(Vector6i(1, 2, 3, 4, 5, 6).sum(), 21)
        [i for i in self.v2f]
        [i for i in self.v2d]
        [i for i in self.v3f]
        [i for i in self.v3d]
        [i for i in self.v6f]
        [i for i in self.v6d]
        self.assertEqual(len(self.v2f), 2)
        self.assertEqual(len(self.v2d), 2)
        self.assertEqual(len(self.v3f), 3)
        self.assertEqual(len(self.v3d), 3)
        self.assertEqual(len(self.v6f), 6)
        self.assertEqual(len(self.v6d), 6)
        self.assertTrue(Vector3f(1,2,3).isApprox((1,2,3+1e-6)))
        self.assertTrue(Vector3f(1,2,3).isApprox((1,2,3.1),prec=.2))
        self.assertTrue(Vector3d(1,2,3).isApprox((1,2,3+1e-13)))
        self.assertTrue(Vector3d(1,2,3).isApprox((1,2,3.1),prec=.2))
        self.assertEqual(Vector3i(1, 2, 3).maxCoeff(), 3)
        self.assertEqual(Vector3i(1, 2, 3).minCoeff(), 1)
        self.assertEqual(Vector3i(1, 2, 3).mean(), 2)
        self.assertEqual(Vector3i(1, 2, 3).prod(), 6)

    def test_matrices_op(self):
        self.m3f.inverse().diagonal()
        self.m3d.inverse().diagonal()
        self.m6f.inverse().diagonal()
        self.m6d.inverse().diagonal()
        self.m3f * Matrix3f.Random()
        self.m3d * Matrix3d.Random()
        self.m6f * Matrix6f.Random()
        self.m6d * Matrix6d.Random()

    def test_mixed_op(self):
        self.m3f * self.v3f
        self.m3d * self.v3d
        self.m6f * self.v6f
        self.m6d * self.v6d
        # Should not work !!!!! add rowVector and transpose.
        # Same as m * v
        self.v3f * self.m3f
        self.v3d * self.m3d
        self.v6f * self.m6f
        self.v6d * self.m6d

    def test_quaternions(self):
        q2f = Quaternionf((1,0,0), math.pi/2)
        q2d = Quaterniond((1,0,0), math.pi/2)
        for t in (0,.5,1): self.qf.slerp(t,q2f)
        for t in (0,.5,1): self.qd.slerp(t,q2d)

    def test_aligned_box(self):
        boxf = AlignedBox3f((0,0,0),(5,5,5))
        boxd = AlignedBox3d((0,0,0),(5,5,5))
        boxf.volume()
        boxd.volume()
        boxf.min[2]*=2
        boxd.max[0]*=2
        self.boxf.intersection(boxf)
        self.boxd.intersection(boxd)
        self.assertTrue(self.boxf.contains((3,3,3)))
        self.assertTrue(self.boxd.contains((3,3,3)))


if __name__ == '__main__':
    unittest.main()