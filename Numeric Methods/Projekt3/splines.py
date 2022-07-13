from utils import *


def create_spline_interpolation_function(points):
    def calculate_params():

        n = len(points)
        A = [[0.0] * 4 * (n-1)] * 4 * (n-1)
        b = [0.0] * 4 * (n-1)

        for i in range(n - 1):
            x, y = points[i]
            row = [0.0] * 4 * (n-1)
            row[4 * i + 3] = 1
            A[4 * i + 3] = row
            b[4 * i + 3] = y

        for i in range(n - 1):
            x_1, y_1 = points[i + 1]
            x_0, y_0 = points[i]
            h = x_1 - x_0
            row = [0.0] * 4 * (n - 1)
            row[4 * i] = h ** 3
            row[4 * i + 1] = h ** 2
            row[4 * i + 2] = h ** 1
            row[4 * i + 3] = 1
            A[4 * i + 2] = row
            b[4 * i + 2] = y_1

        for i in range(n - 2):
            x_1, y_1 = points[i + 1]
            x_0, y_0 = points[i]
            h = x_1 - x_0
            row = [0.0] * 4 * (n - 1)
            row[4 * i] = 3 * (h ** 2)
            row[4 * i + 1] = 2 * h
            row[4 * i + 2] = 1
            row[4 * (i + 1) + 2] = -1
            A[4 * i] = row
            b[4 * i] = 0.0

        for i in range(n - 2):
            x_1, y_1 = points[i + 1]
            x_0, y_0 = points[i]
            h = x_1 - x_0
            row = [0.0] * 4 * (n - 1)
            row[4 * i] = 6 * h
            row[4 * i + 1] = 2
            row[4 * (i + 1) + 1] = -2
            A[4 * (i + 1) + 1] = row
            b[4 * (i + 1) + 1] = 0.0

        # first point
        row = [0.0] * 4 * (n - 1)
        row[1] = 2
        A[1] = row
        b[1] = 0

        # last point
        row = [0.0] * 4 * (n - 1)
        x_1, y_1 = points[-1]
        x_0, y_0 = points[-2]
        h = x_1 - x_0
        row[1] = 2
        row[-4] = 6 * h
        A[-4] = row
        b[-4] = 0.0

        result = lu_factorization(A, b)
        return result

    params = calculate_params()

    def f(x):
        param_array = []
        row = []
        for param in params:
            row.append(param)
            if len(row) == 4:
                param_array.append(row.copy())
                row.clear()

        for i in range(1, len(points)):
            x_i, y_i = points[i-1]
            x_j, y_j = points[i]
            if x_i <= x <= x_j:
                a, b, c, d = param_array[i-1]
                h = x - x_i
                return a*(h**3)+b*(h**2)+c*h+d
    return f
