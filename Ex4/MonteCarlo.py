import threading
import random

total_points = 0
points_in_circle = 0


def generate_random_points(x1_bound, y1_bound, x2_bound, y2_bound, radius_circle):
    global total_points, points_in_circle
    x_circle = (x1_bound + x2_bound) / 2
    y_circle = (y1_bound + y2_bound) / 2

    for _ in range(0, 1000000):
        random_point = (random.uniform(x1_bound, x2_bound), random.uniform(y1_bound, y2_bound))
        distance = radius_circle ** 2 - ((random_point[0] - x_circle) ** 2 + (random_point[1] - y_circle) ** 2)
        if distance < 0:
            total_points += 1
            continue
        else:
            total_points += 1
            points_in_circle += 1


if __name__ == '__main__':
    t = threading.Thread(target=generate_random_points, args=[-1, -1, 1, 1, 1])
    t.start()
    t.join()
    pi = 4 * points_in_circle / total_points
    print(pi)
