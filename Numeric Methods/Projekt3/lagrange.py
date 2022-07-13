import matplotlib.pyplot as plt
import pandas as pd


def create_lagrange_interpolation_function(points):
    def f(x):
        res = 0
        n = len(points)
        for i in range(n):
            x_i, y_i = points[i]
            base = 1
            for j in range(n):
                if i == j:
                    continue
                else:
                    x_j, y_j = points[j]
                    base *= (x - x_j) / (x_i - x_j)
            res += y_i * base
        return res
    return f


