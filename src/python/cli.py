import random
import time
import argparse
import csv
import os
from matmul import matmul


def random_matrix(n):
    """Generate an n x n matrix with random float values between 0 and 1"""
    return [[random.random() for _ in range(n)] for _ in range(n)]


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Matrix multiplication benchmark")
    parser.add_argument("--size", type=int, default=128, help="Matrix size (N x N)")
    parser.add_argument("--repeats", type=int, default=3, help="Number of repetitions")
    args = parser.parse_args()

    n = args.size
    reps = args.repeats
    times = []

    print(f"\n[Running {reps} repetitions with {n}x{n} matrices]\n")

    for r in range(reps):
        A = random_matrix(n)
        B = random_matrix(n)

        start = time.perf_counter()
        matmul(A, B)
        end = time.perf_counter()

        t = end - start
        times.append(t)
        print(f"Run {r+1}: {t:.6f} seconds")

    avg_time = sum(times) / len(times)
    print(f"\nAverage time ({reps} runs): {avg_time:.6f} seconds\n")

    os.makedirs("output-data", exist_ok=True)
    csv_path = "output-data/results_python.csv"
    file_exists = os.path.isfile(csv_path)

    with open(csv_path, "a", newline="") as f:
        writer = csv.writer(f)
        if not file_exists:
            writer.writerow(["MatrixSize", "Repeats", "AverageTime(s)"])
        writer.writerow([n, reps, round(avg_time, 6)])

    print(f"[Results saved to {csv_path}]")