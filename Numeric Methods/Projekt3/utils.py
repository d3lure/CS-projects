def lu_factorization(a, b):

    m = len(a)
    matrix_a = copy_matrix(a)
    matrix_l = diagonal_to_square_matrix([1] * m)
    matrix_u = matrix_zeros(m)

    vector_b = copy_vector(b)
    vector_x = [1.0] * m
    vector_y = [0] * m

    # create matrices L and U
    # LUx = b
    for j in range(m):
        for i in range(j + 1):
            matrix_u[i][j] += matrix_a[i][j]
            for k in range(i):
                matrix_u[i][j] -= matrix_l[i][k] * matrix_u[k][j]

        for i in range(j + 1, m):
            for k in range(j):
                matrix_l[i][j] -= matrix_l[i][k] * matrix_u[k][j]
            matrix_l[i][j] += matrix_a[i][j]
            matrix_l[i][j] /= matrix_u[j][j]

    # solve Ly = b
    for i in range(m):
        value = vector_b[i]
        for j in range(i):
            value -= matrix_l[i][j] * vector_y[j]

        vector_y[i] = value / matrix_l[i][i]

    # solve Ux = y
    for i in range(m - 1, -1, -1):
        value = vector_y[i]
        for j in range(i + 1, m):
            value -= matrix_u[i][j] * vector_x[j]
        vector_x[i] = value / matrix_u[i][i]

    return vector_x


def dot_product(a, b):
    copy_a = copy_matrix(a)
    copy_b = copy_vector(b)
    m = len(copy_a)
    n = len(copy_a[0])
    c = [0] * m

    for i in range(m):
        for l in range(n):
            c[i] += copy_a[i][l] * copy_b[l]
    return c


def copy_matrix(matrix):
    copy = []
    for row in matrix:
        new_row = []
        for elem in row:
            new_row.append(elem)
        copy.append(new_row)
    return copy


def matrix_zeros(n):
    matrix = []
    for _ in range(n):
        row = []
        for _ in range(n):
            row.append(int(0))
        matrix.append(row)
    return matrix


def diagonal_to_square_matrix(vector):
    tmp = matrix_zeros(len(vector))
    for i in range(len(vector)):
        tmp[i][i] = vector[i]
    return tmp


def diagonal(a):
    diag = []
    for i in range(len(a)):
        diag.append(a[i][i])
    return diag


def copy_vector(vector):
    copy = []
    for elem in vector:
        copy.append(elem)
    return copy
