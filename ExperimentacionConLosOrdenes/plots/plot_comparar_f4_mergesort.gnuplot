set terminal pngcairo size 1200,700 enhanced font 'DejaVu Sans,11'
set output 'plots/comparatives/comparar_f4_mergesort.png'
set datafile separator ' '
set title 'Comparativa f4 vs mergesort (suavizado)'
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid
set yrange [0:0.003]
set ytics 0,0.0005,0.003
set xrange [0:10000]
set xtics 0,1000,10000
set style line 4 lt 1 lw 3 lc rgb '#d62728'
set style line 5 lt 1 lw 3 lc rgb '#9467bd'
plot \
  'db/comparar_Ns.csv' using 1:5 with lines lw 2 lc rgb '#d62728' title 'f4 (raw)', \
  'db/comparar_Ns.csv' using 1:6 with lines lw 2 lc rgb '#9467bd' title 'mergesort (raw)'
