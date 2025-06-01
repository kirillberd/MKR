set terminal pngcairo size 800,600 enhanced font "Arial,12"
set output 'temperature_distribution.png'
set title "Распределение температуры в пластине"
set xlabel "Координата X"
set ylabel "Координата Y"
set cblabel "Температура" rotate by -90
set key off

# Настройка палитры с шагом 25
set palette defined ( \
  0    "dark-blue", \
  25   "blue", \
  50   "cyan", \
  75   "green", \
  100  "light-green", \
  125  "yellow", \
  150  "orange", \
  175  "red", \
  200  "dark-red" \
)

set xrange [-0.5:32.5]
set yrange [24.5:-0.5]  # Первая строка данных - верхняя часть пластины

set cbrange [0:200]
set tics out
set grid front

plot 'solution.txt' matrix with image