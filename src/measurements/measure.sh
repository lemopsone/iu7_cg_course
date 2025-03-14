#!/bin/bash

# Переменные
sizes=(200 300 400 500 600 700 800 900 1000) # Размеры экрана
#sizes=(600)
#iters=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
#iters=(1 2 3)
iters=(10)
types=("single" "concurrent" "opengl")                 # Типы программы
runs=50                                               # Количество запусков

# Циклы для всех комбинаций параметров
for ((i=1; i<=runs; i++)); do
  for size in "${sizes[@]}"; do
    for iter in "${iters[@]}"; do
      for type in "${types[@]}"; do
      # Имя выходного файла для данной конфигурации
      output_file="results/results_${type}_${size}_${iter}.txt"

      echo "Running for size=${size}, iters=${iter}, type=${type}, saving to ${output_file}..."

      # Запускаем программу 20 раз для текущей конфигурации
        # Выполняем программу и сохраняем результат в файл
        ./measure "$size" "$iter" "$type" >> "$output_file"
      done
    done
  done
done

echo "Замеры завершены!"

