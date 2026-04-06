# Script de gnuplot para comparar tiempos (f1,f2,f3)
set terminal pngcairo size 900,600 enhanced font 'DejaVu Sans,10'
set output 'plots/comparatives/comparar_Ns.png'
set datafile separator ','
set key left top
set title 'Comparativa de tiempos: f1 vs f2 vs f3'
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid

set style line 1 lt 1 lw 2 lc rgb '#1f77b4' pt 7
set style line 2 lt 1 lw 2 lc rgb '#ff7f0e' pt 5
set style line 3 lt 1 lw 2 lc rgb '#2ca02c' pt 9

plot 'db/comparar_Ns.csv' using 1:2 with linespoints ls 1 title 'f1', \
     'db/comparar_Ns.csv' using 1:3 with linespoints ls 2 title 'f2', \
     'db/comparar_Ns.csv' using 1:4 with linespoints ls 3 title 'f3'
