import numpy as np
from helper_methods import *
from equations import Equations


def lu(A):
    # Get the number of rows
    n = A.shape[0]

    U = A.copy()
    L = np.eye(n, dtype=np.double)

    # Loop over rows
    for i in range(n):
        # Eliminate entries below i with row operations
        # on U and reverse the row operations to
        # manipulate L
        factor = U[i + 1:, i] / U[i, i]
        L[i + 1:, i] = factor
        U[i + 1:] -= factor[:, np.newaxis] * U[i]

    return L, U


def forward_substitution(L, b):
    # Get number of rows
    n = L.shape[0]

    # Allocating space for the solution vector
    y = np.zeros_like(b, dtype=np.double)

    # Here we perform the forward-substitution.
    # Initializing  with the first row.
    y[0] = b[0] / L[0, 0]

    # Looping over rows in reverse (from the bottom  up),
    # starting with the second to last row, because  the
    # last row solve was completed in the last step.
    for i in range(1, n):
        y[i] = (b[i] - np.dot(L[i, :i], y[:i])) / L[i, i]

    return y


def back_substitution(U, y):
    # Number of rows
    n = U.shape[0]

    # Allocating space for the solution vector
    x = np.zeros_like(y, dtype=np.double)

    # Here we perform the back-substitution.
    # Initializing with the last row.
    x[-1] = y[-1] / U[-1, -1]

    # Looping over rows in reverse (from the bottom up),
    # starting with the second to last row, because the
    # last row solve was completed in the last step.
    for i in range(n - 2, -1, -1):
        x[i] = (y[i] - np.dot(U[i, i:], x[i:])) / U[i, i]

    return x


def lu_solve(A, b):
    L, U = lu(A)

    y = forward_substitution(L, b)

    return back_substitution(U, y)


e = Equations(a1=3, a2=-1, a3=-1)
# print((lu_solve(e.A, e.b)))
# print(np.linalg.solve(e.A, e.b))

# norm_res = norm(np.dot(e.A, lu_solve(e.A, e.b)) - e.b)
# print(norm_res)

array = np.array([1,2,3,4])
print(array)

array = array[:,np.newaxis]
print(array)

array = np.array([[i+1] for i in range(4)])
print(array)
