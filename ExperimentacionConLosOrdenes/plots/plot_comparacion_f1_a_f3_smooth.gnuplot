set terminal pngcairo size 1200,700 enhanced font 'DejaVu Sans,11'
set output 'plots/comparatives/comparacion_f1_a_f3_smooth.png'
set datafile separator ','
set title 'Comparativa (suavizado) f1..f3'
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid
set xrange [0:10000]
set yrange [0:0.0005]
set ytics 0,0.0001,0.0005
set xtics 0,1000,10000
set format y '%.6f'
set style line 1 lt 1 lw 3 lc rgb '#1f77b4'
set style line 2 lt 1 lw 3 lc rgb '#ff7f0e'
set style line 3 lt 1 lw 3 lc rgb '#2ca02c'
plot \
  'db/comparar_Ns.csv' using 1:2 every ::1 with lines ls 1 title 'f1 (raw)', \
  'db/comparar_Ns.csv' using 1:3 every ::1 with lines ls 2 title 'f2 (raw)', \
  'db/comparar_Ns.csv' using 1:4 every ::1 with lines ls 3 title 'f3 (raw)'
