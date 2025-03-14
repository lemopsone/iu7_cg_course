import os
import numpy as np
import matplotlib.pyplot as plt

# Путь к папке с файлами
results_folder = "results"

algos = {
    "single": "Однопоточный",
    "concurrent": "Многопоточный",
    "opengl": "OpenGL"
}

# Функция для чтения среднего значения времени из файла
def read_average_times(file_path):
    with open(file_path, "r") as f:
        times = [float(line.strip()) for line in f if line.strip()]
    return np.mean(times)

# Функция для обработки файлов и извлечения данных
def collect_data(folder):
    data = {"single": {}, "concurrent": {}, "opengl": {}}
    for file_name in os.listdir(folder):
        if not file_name.startswith("results_") or not file_name.endswith(".txt"):
            continue

        parts = file_name.replace("results_", "").replace(".txt", "").split("_")
        algorithm = parts[0]
        size, iters = map(int, parts[1:])

        if algorithm in data:
            if size not in data[algorithm]:
                data[algorithm][size] = {}
            data[algorithm][size][iters] = read_average_times(os.path.join(folder, file_name))
    return data

# Сбор данных из файлов
data = collect_data(results_folder)

# Построение графика 1: Влияние разрешения при фиксированных итерациях
def plot_resolution_comparison(data, fixed_iters, output_folder, log_scale=False):
    plt.figure(figsize=(10, 6))
    for algo, line_style in zip(data.keys(), ["-", "--", ":"]):
        sizes = sorted(data[algo].keys())
        avg_times = [data[algo][size].get(fixed_iters, None) for size in sizes]
        plt.plot(sizes, avg_times, line_style, label=algos[algo], linewidth=2)

    plt.title(f"Фиксированное кол-во итераций = {fixed_iters}")
    plt.xlabel("Разрешение экрана")
    plt.ylabel("Время выполнения, нс")
    if log_scale:
        plt.yscale("log")
        plt.title(f"Фиксированное кол-во итераций = {fixed_iters} (лог. шкала)")
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.7)

    # Сохранение в двух форматах
    scale_suffix = "_log" if log_scale else "_linear"
    plt.savefig(os.path.join(output_folder, f"resolution_comparison{scale_suffix}.png"))
    plt.savefig(os.path.join(output_folder, f"resolution_comparison{scale_suffix}.svg"))
    plt.close()

# Построение графика 2: Влияние количества итераций при фиксированном разрешении
def plot_iterations_comparison(data, fixed_size, output_folder, log_scale=False):
    plt.figure(figsize=(10, 6))
    for algo, line_style in zip(data.keys(), ["-", "--", ":"]):
        iters_list = sorted(data[algo][fixed_size].keys())
        avg_times = [data[algo][fixed_size].get(iters, None) for iters in iters_list]
        plt.plot(iters_list, avg_times, line_style, label=algos[algo], linewidth=2)

    plt.title(f"Фиксированное разрешение, {fixed_size}x{fixed_size}")
    plt.xlabel("Количество итераций")
    plt.ylabel("Время выолпнения, нс")
    if log_scale:
        plt.yscale("log")
        plt.title(f"Фиксированное разрешение, {fixed_size}x{fixed_size} (лог. шкала)")
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.7)

    # Сохранение в двух форматах
    scale_suffix = "_log" if log_scale else "_linear"
    plt.savefig(os.path.join(output_folder, f"iterations_comparison{scale_suffix}.png"))
    plt.savefig(os.path.join(output_folder, f"iterations_comparison{scale_suffix}.svg"))
    plt.close()

# Построение графиков
output_folder = "plots"
os.makedirs(output_folder, exist_ok=True)

# Для разрешения
plot_resolution_comparison(data, fixed_iters=10, output_folder=output_folder, log_scale=False)
plot_resolution_comparison(data, fixed_iters=10, output_folder=output_folder, log_scale=True)

# Для количества итераций
plot_iterations_comparison(data, fixed_size=600, output_folder=output_folder, log_scale=False)
plot_iterations_comparison(data, fixed_size=600, output_folder=output_folder, log_scale=True)

print("Графики сохранены в папке 'plots' в форматах PNG и SVG.")

