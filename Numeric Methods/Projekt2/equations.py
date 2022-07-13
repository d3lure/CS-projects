import math
import numpy as np
from helper_methods import *


class Equations:

    def __init__(self, a1=9, a2=-1, a3=-1, N=980):
        self.N = N
        self.a1 = a1
        self.a2 = a2
        self.a3 = a3
        self.b = np.array([math.sin(i * (4 + 1)) for i in range(self.N)])
        self.A = self.create_A()
        self.e = 10**-9

    def create_A(self):
        A = np.array([[0.0] * self.N] * self.N)

        for row_id in range(self.N):
            A[row_id][row_id] = self.a1
            try:
                A[row_id][row_id - 1] = self.a2
            except:
                pass
            try:
                A[row_id][row_id + 1] = self.a2
            except:
                pass
            try:
                A[row_id][row_id - 2] = self.a3
            except:
                pass
            try:
                A[row_id][row_id + 2] = self.a3
            except:
                pass

        return A

    def jacobi(self, max_iters=1000):
        x = np.zeros_like(self.b)
        D = get_diag(self.A, self.N)
        R = self.A - matrx_from_diag(D, self.N)

        for i in range(max_iters):
            x = (self.b - np.dot(R, x)) / D

            norm_res = norm(np.dot(self.A, x) - self.b)
            if norm_res <= self.e:
                return x, i, norm_res

    def gauss_seidel(self, max_iters=1000):
        x = np.zeros_like(self.b)
        for k in range(max_iters):
            x_new = np.zeros_like(x)
            for i in range(self.N):
                s1 = np.dot(self.A[i, :i], x_new[:i])
                s2 = np.dot(self.A[i, i + 1:], x[i + 1:])
                x_new[i] = (self.b[i] - s1 - s2) / self.A[i, i]

            x = x_new
            norm_res = norm(np.dot(self.A, x) - self.b)
            if norm_res <= self.e:
                return x, k, norm_res

    def lu(self):
        U = self.A.copy()
        L = np.eye(self.N)

        for i in range(self.N):
            tmp = U[i + 1:, i] / U[i, i]
            L[i + 1:, i] = U[i + 1:, i] / U[i, i]
            U[i + 1:] -= tmp[:, np.newaxis] * U[i]

        return L, U

    def forward_substitution(self, L):
        y = np.zeros_like(self.b)

        for i in range(self.N):
            if i == 0:
                y[i] = self.b[i] / L[i, i]
            else:
                y[i] = (self.b[i] - np.dot(L[i, :i], y[:i])) / L[i, i]

        return y

    def back_substitution(self, U, y):
        x = np.zeros_like(y)

        for i in range(self.N - 1, -1, -1):
            if i == self.N - 1:
                x[-1] = y[-1] / U[-1, -1]
            else:
                x[i] = (y[i] - np.dot(U[i, i:], x[i:])) / U[i, i]

        return x

    def lu_solve(self):
        L, U = self.lu()
        y = self.forward_substitution(L)
        x = self.back_substitution(U, y)

        res = np.dot(self.A, x) - self.b
        return x, norm(res)
