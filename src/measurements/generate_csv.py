import os
import csv
import numpy as np

# Путь к папке с результатами
results_folder = "results"

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

# Сбор данных
data = collect_data(results_folder)

# Функция для сохранения данных в CSV
def save_csv(data, output_file, variable, fixed_value):
    """
    Создает CSV-файл.

    :param data: Словарь с данными
    :param output_file: Имя файла для сохранения
    :param variable: "size" или "iters", что изменяется в таблице
    :param fixed_value: Фиксированное значение итераций или разрешения
    """
    header = ["Кол-во итераций", "Однопоточный", "Многопоточный", "OpenGL"]
    rows = []

    if variable == "size":
        header[0] = "Разрешение"
        for size in sorted(data["single"].keys()):
            print(data)
            if fixed_value in data["single"][size]:
                rows.append([
                    size,
                    int(data["single"][size][fixed_value]),
                    int(data["concurrent"][size][fixed_value]),
                    int(data["opengl"][size][fixed_value]),
                ])
    elif variable == "iters":
        header[0] = "Кол-во итераций"
        for iters in sorted(data["single"][fixed_value].keys()):
            rows.append([
                iters,
                int(data["single"][fixed_value][iters]),
                int(data["concurrent"][fixed_value][iters]),
                int(data["opengl"][fixed_value][iters]),
            ])

    # Сохранение в CSV
    with open(output_file, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(header)
        writer.writerows(rows)

# Создание CSV-файлов
output_folder = "csv_results"
os.makedirs(output_folder, exist_ok=True)

# Таблица 1: Изменение разрешения при фиксированных итерациях (iters = 25)
save_csv(data, os.path.join(output_folder, "resolution_comparison.csv"), variable="size", fixed_value=10)

# Таблица 2: Изменение количества итераций при фиксированном разрешении (size = 600)
save_csv(data, os.path.join(output_folder, "iterations_comparison.csv"), variable="iters", fixed_value=600)

print("CSV-файлы сохранены в папке 'csv_results'.")

