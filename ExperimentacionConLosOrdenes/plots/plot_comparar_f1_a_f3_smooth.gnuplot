set terminal pngcairo size 1200,700 enhanced font 'DejaVu Sans,11'
set output 'plots/comparatives/comparar_f1_a_f3_smooth.png'
set datafile separator ' '
set title 'Comparativa (suavizado) f1..f3'
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid
set xrange [0:10000]
set yrange [0:0.003]
set ytics 0,0.0005,0.003
set xtics 0,1000,10000
set style line 1 lt 1 lw 3 lc rgb '#1f77b4'
set style line 2 lt 1 lw 3 lc rgb '#ff7f0e'
set style line 3 lt 1 lw 3 lc rgb '#2ca02c'
set style line 4 lt 1 lw 3 lc rgb '#d62728'
set style line 5 lt 1 lw 3 lc rgb '#9467bd'
plot \
  'plots/comparatives/f1_smooth.dat' using 1:2 with lines ls 1 title 'f1 (smooth)', \
  'plots/comparatives/f2_smooth.dat' using 1:2 with lines ls 2 title 'f2 (smooth)', \
  'plots/comparatives/f3_smooth.dat' using 1:2 with lines ls 3 title 'f3 (smooth)'
