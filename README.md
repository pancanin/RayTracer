## Ray Tracer

### Determinant of a matrix.
If we represent a transformation using a matrix, the determinant of that matrix is the factor by which the area of the parallelogram
is scaled after applying the transformation to the vectors.

// TODO: Add picture for explanation on why this formula is the way determinant is computed.

The computation for a 2D transformation is as follows:
T = [
	a, b
	c, d
]

det(T) = ad - cb

In 3D it is a bit trickier to understand the formula, but it can be explained visually and in effect we boil it down to finding 2D determinants.
Good way to visualise the steps needed is to create a 3x3 matrix that will help us see the operations needed.


### Cross product in 3D

The cross product of two 3D vectors a and b returns a new vector that is perpendicular to a and b.
Finding the cross product vector of two vectors in 3D space means finding the determinant of a 3x3 matrix, where:
M = [
	i, j, k
	ax, ay, az
	bx, by, bz
]

det(M) = det(ay, az | by, bz)i - det(ax, az | bx, bz)j + det(ax, ay | bx, by)k =
= (ay*bz - az*by)i - (ax*bz - az*bx)j + (ax*by - ay*bx)k

The result is a 3D vector (factors for i, j, k) that is the cross product of A and B.

Interesting fact!!
The length of the cross product vector is equal to the determinant of A and B. :O

For example, if we have vectors:

A = [3, 5, -7], B = [2, -6, 4]

We can compute the cross product with the help of a matrix.

A x B = [
	i, j, k
	3, 5, -7
	2, -6, 4
]

We find the determinant of the 3x3 matrix ( I will use | to separate rows):

= i[5, -7 | -6, 4] - j[3, 2 | -7, 4] + k[3, 5 | 2, -6]

Now we find the determinants of the 2D matrices.

= -22i - 26j - 28k

So the vector that is perpendicular to A and B is [-22, -26, -28]