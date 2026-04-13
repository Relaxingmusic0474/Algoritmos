set terminal pngcairo size 1200,700 enhanced font 'DejaVu Sans,11'
set output 'plots/comparatives/comparar_f4_mergesort_smooth.png'
set datafile separator ' '
set title 'Comparativa (suavizado) f4 vs mergesort'
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid
set xrange [0:10000]
set yrange [0:0.003]
set ytics 0,0.0005,0.003
set xtics 0,1000,10000
set style line 4 lt 1 lw 3 lc rgb '#d62728'
set style line 5 lt 1 lw 3 lc rgb '#9467bd'
plot \
  'plots/comparatives/f4_smooth.dat' using 1:2 with lines ls 4 title 'f4 (smooth)', \
  'plots/comparatives/ms_smooth.dat' using 1:2 with lines ls 5 title 'mergesort (smooth)'
