from helper_methods import *
import time
from equations import Equations
from matplotlib import *
import matplotlib.pyplot as plt


m = Equations()

print("Zadanie B")
start = time.time()
res = m.jacobi()
end = time.time()
print("Jacobi method ended after {} iterations.\nTime elapsed: {:.2f} [s]\nResiduum norm = {}\n"
      .format(res[1], end - start, res[2]))

start = time.time()
res = m.gauss_seidel()
end = time.time()
print("Gauss-Seidel method ended after {} iterations.\nTime elapsed: {:.2f} [s]\nResiduum norm = {}\n"
      .format(res[1], end - start, res[2]))


print("\nZadanie C")
m = Equations(a1=3, a2=-1, a3=-1)

start = time.time()
res = m.jacobi()
end = time.time()
if res is None:
    print("Jacobi method didn't converge. Time elapsed: {:.2f}s".format(end - start))


start = time.time()
res = m.gauss_seidel()
end = time.time()
if res is None:
    print("Gauss-Seidel method didn't converge. Time elapsed: {:.2f}s".format(end - start))


print("\nZadanie D")
start = time.time()
res = m.lu_solve()
end = time.time()
print("LU method ended after {:.2f} seconds and residuum norm = {}".format(end-start, res[1]))


print("\nZadanie E")
N = [100, 500, 1000, 2000, 2500]
jacobi_times, gauss_seidel_times, lu_times = [], [], []

for n in N:
    m = Equations(N=n)

    start = time.time()
    m.jacobi()
    end = time.time()
    jacobi_times.append(end - start)

    start = time.time()
    m.gauss_seidel()
    end = time.time()
    gauss_seidel_times.append(end - start)

    start = time.time()
    m.lu_solve()
    end = time.time()
    lu_times.append(end - start)


plt.title("Time dependence on the number of variables")
plt.plot(N, jacobi_times, label="Jacobi")
plt.plot(N, gauss_seidel_times, label="Gauss-Seidel")
# plt.plot(N, lu_times, label="LU")
plt.xlabel("Number of variables")
plt.ylabel("Time [s]")
plt.legend()
plt.show()


plt.title("Time dependence on the number of variables")
plt.plot(N, lu_times, label="LU")
plt.xlabel("Number of variables")
plt.ylabel("Time [s]")
plt.legend()
plt.show()
