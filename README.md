## Ray Tracer

### Determinant of a matrix.
Determinant of two vectors A an B is the area of the parallelogram that is created when a copy of A is put at the end of B and same is done for the other side.

![determinant explanation of formula](https://github.com/pancanin/RayTracer/blob/master/helpful_materials/matrix-determinant.PNG?raw=true)

The computation for a 2D transformation is as follows:
```
T = [
	a, b
	c, d
]

det(T) = ad - cb
```

For 3D:

```
M = [
	i, j, k
	ax, ay, az
	bx, by, bz
]

det(M) = det(ay, az | by, bz)i - det(ax, az | bx, bz)j + det(ax, ay | bx, by)k =
= (ay*bz - az*by)i - (ax*bz - az*bx)j + (ax*by - ay*bx)k
```


### Cross product in 3D

The cross product of two 3D vectors a and b returns a new vector that is perpendicular to a and b.
Finding the cross product vector of two vectors in 3D space means finding the determinant of a 3x3 matrix, where:

The result is a 3D vector (factors for i, j, k) that is the cross product of A and B.

Interesting fact!!
The length of the cross product vector is equal to the determinant of A and B. :O

For example, if we have vectors:
```
A = [3, 5, -7], B = [2, -6, 4]
```
We can compute the cross product with the help of a matrix.

```
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
```

### Subtracting matrices (in calculating lower left point context)

Subtraction of two matrices of equal dimensions is the subtraction of corresponding elements. The result is a matrix with 
same dimensions as the terms.

It looks like subtracting two vectors gives a vector that is in the opposite or perpendicular direction of their addition vector.

The lower left point is used as a reference vector to which we add the vertical and horizontal vectors adjusted with offset u, v.

// TODO: Add drawing

### Calculating ray direction based on current pixel
