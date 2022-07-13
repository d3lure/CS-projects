from lagrange import *
from splines import *
import time


# True --> Lagrange, False --> Splines
def interpolate(file_path, num_points, method, verbose=True):
    df = pd.read_csv(file_path)
    interpolation_data = df.iloc[::(int(df.shape[0] / num_points)), :].to_numpy()

    if method:
        F = create_lagrange_interpolation_function(interpolation_data)
    else:
        F = create_spline_interpolation_function(interpolation_data)

    shift = 0
    if not method:
        shift = df.shape[0] % num_points - 1

    true_distance, true_height = [], []
    interpolated_height = []
    for idx, row in df.iterrows():
        x, y = row['Distance'], row['Height']
        true_distance.append(x)
        true_height.append(y)
        interpolated_height.append(F(x))

    res_distance, res_height = [], []
    for point in interpolation_data:
        x, y = point
        res_distance.append(x)
        res_height.append(y)

    if verbose:
        if method:
            fig, (ax1, ax2) = plt.subplots(1, 2, sharex="all")
            fig.suptitle(f'Przybliżenie interpolacją Lagrange\'a \n{len(interpolation_data) - 1} punkty(ów)')
            fig.supxlabel('Odległość [m]')
            fig.supylabel('Wysokość [m]')

            ax1.semilogy(res_distance, res_height, 'r.', label="wybrane punkty")
            ax1.semilogy(true_distance, true_height, label="trasa zmierzona")
            ax1.semilogy(true_distance, interpolated_height, label="funkcja interpolująca")
            ax1.legend()

            ax2.plot(res_distance, res_height, 'r.', label="wybrane punkty")
            ax2.plot(true_distance, true_height, label="trasa zmierzona")
            ax2.plot(true_distance, interpolated_height, label="funkcja interpolująca")
        else:
            fig, ax1 = plt.subplots()
            fig.suptitle(f'Przybliżenie interpolacją Splajnami \n{len(interpolation_data)-1} punkty(ów)')
            fig.supxlabel('Odległość [m]')
            fig.supylabel('Wysokość [m]')

            ax1.plot(res_distance, res_height, 'r.', label="wybrane punkty")
            ax1.plot(true_distance, true_height, label="trasa zmierzona")
            ax1.plot(true_distance[:-shift], interpolated_height[:-shift], label="funkcja interpolująca")
            ax1.legend()

        plt.grid()
        plt.show()


if __name__ == "__main__":
    # True --> Lagrange, False --> Splines
    num_points = 50
    interpolate('paths/Obiadek.csv', num_points, True)
    interpolate('paths/Obiadek.csv', num_points, False)


