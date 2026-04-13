set terminal pngcairo size 1200,700 enhanced font 'DejaVu Sans,11'
set output 'plots/comparatives/comparar_f1_a_f3.png'
set datafile separator ' '
set title 'Comparativa f1 a f3 (suavizado)'
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid
set yrange [0:0.003]
set ytics 0,0.0005,0.003
set xrange [0:10000]
set xtics 0,1000,10000
set style line 1 lt 1 lw 3 lc rgb '#1f77b4'
set style line 2 lt 1 lw 3 lc rgb '#ff7f0e'
set style line 3 lt 1 lw 3 lc rgb '#2ca02c'
set style line 4 lt 1 lw 3 lc rgb '#d62728'
set style line 5 lt 1 lw 3 lc rgb '#9467bd'
plot \
  'db/comparar_Ns.csv' using 1:2 with lines lw 2 lc rgb '#1f77b4' title 'f1 (raw)', \
  'db/comparar_Ns.csv' using 1:3 with lines lw 2 lc rgb '#ff7f0e' title 'f2 (raw)', \
  'db/comparar_Ns.csv' using 1:4 with lines lw 2 lc rgb '#2ca02c' title 'f3 (raw)'
