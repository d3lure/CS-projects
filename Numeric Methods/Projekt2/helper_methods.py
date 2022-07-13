from math import sqrt
import numpy as np


def get_diag(matrix, N):
    diag = []
    for i in range(N):
        diag.append(matrix[i][i])
    return np.array(diag)


def matrx_from_diag(diag, N):
    m = np.array([np.array([0] * N)] * N)
    for i in range(N):
        m[i][i] = diag[i]
    return m


def norm(vect):
    res = 0
    for num in vect:
        res += num**2
    return sqrt(res)


