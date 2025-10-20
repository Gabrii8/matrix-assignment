import pandas as pd
import matplotlib.pyplot as plt
import os

df_c = pd.read_csv("output-data/results_c.csv")
df_java = pd.read_csv("output-data/results_java.csv")
df_python = pd.read_csv("output-data/results_python.csv")

plt.style.use('seaborn-v0_8-whitegrid')
fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(df_c["MatrixSize"], df_c["AverageTime(s)"], marker='o', linestyle='-', label='C')
ax.plot(df_java["MatrixSize"], df_java["AverageTime(s)"], marker='s', linestyle='-', label='Java')
ax.plot(df_python["MatrixSize"], df_python["AverageTime(s)"], marker='^', linestyle='-', label='Python')
ax.set_yscale('log')
ax.set_xlabel("Matrix Size (N x N)", fontsize=12)
ax.set_ylabel("Average Execution Time (seconds) - Log Scale", fontsize=12)
ax.set_title("Performance Comparison of Matrix Multiplication", fontsize=14)
ax.legend()
ax.grid(True)

output_dir = "paper"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

file_path = os.path.join(output_dir, "performance_plot.png")
plt.savefig(file_path, dpi=300, bbox_inches='tight')

print(f"Plot saved successfully to: {file_path}")