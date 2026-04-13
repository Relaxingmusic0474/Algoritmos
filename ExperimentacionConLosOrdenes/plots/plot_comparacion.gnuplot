# Script gnuplot: versión muy suavizada (comparacion.png)
set terminal pngcairo size 1200,700 enhanced font 'DejaVu Sans,11'
set output 'plots/comparatives/comparacion.png'
set datafile separator ' '
set title 'Comparación (muy suavizado)'
set key left top
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid

# Mantener los mismos ticks en X que usar en comparar_Ns (0 .. 1e6, pasos 2e5)
set xrange [0:1e6]
set xtics 0,200000,1000000
set format x '%.0e'

# Eje Y compacto (mismo que usar en comparar_Ns)
set yrange [0:0.2]
set ytics 0,0.05,0.2
set format y '%.4f'

# Estilos
set style line 1 lt 1 lw 3 lc rgb '#1f77b4'
set style line 2 lt 1 lw 3 lc rgb '#ff7f0e'
set style line 3 lt 1 lw 3 lc rgb '#2ca02c'
set style line 4 lt 1 lw 3 lc rgb '#d62728'
set style line 5 lt 1 lw 3 lc rgb '#9467bd'
# (opcional) estilo extra definido pero no usado
# set style line 6 lt 1 lw 5 lc rgb '#800080' pt 7 ps 1.2

# Usaremos archivos con suavizado más fuerte (generados con smooth_csv.sh con ventana mayor)
plot \
  'plots/comparatives/f1_more_smooth.dat' using 1:2 with lines ls 1 title 'f1 (smooth)', \
  'plots/comparatives/f2_more_smooth.dat' using 1:2 with lines ls 2 title 'f2 (smooth)', \
  'plots/comparatives/f3_more_smooth.dat' using 1:2 with lines ls 3 title 'f3 (smooth)', \
  'plots/comparatives/f4_more_smooth.dat' using 1:2 with lines ls 4 title 'f4 (smooth)', \
  'plots/comparatives/ms_more_smooth.dat' using 1:2 with lines ls 5 title 'mergesort (smooth)', \
  'plots/comparatives/ms_raw.dat' using 1:2 with lines ls 5 dashtype 2 title 'mergesort (raw)', \
  'db/comparar_Ns.csv' every 10 using 1:2 with points pt 7 ps 0.6 lc rgb '#1f77b4' notitle, \
  'db/comparar_Ns.csv' every 10 using 1:3 with points pt 7 ps 0.6 lc rgb '#ff7f0e' notitle, \
  'db/comparar_Ns.csv' every 10 using 1:4 with points pt 7 ps 0.6 lc rgb '#2ca02c' notitle, \
  'db/comparar_Ns.csv' every 10 using 1:5 with points pt 7 ps 0.6 lc rgb '#d62728' notitle
