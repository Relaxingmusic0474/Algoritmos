set terminal pngcairo size 1200,700 enhanced font 'DejaVu Sans,11'
set output 'plots/comparatives/comparacion_f4_mergesort_fixed.png'
set datafile separator ','
set title 'Comparativa f4 vs mergesort (datos crudos)'
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid
set xrange [0:10000]
set xtics 0,1000,10000
# Aumentar Y para mostrar hasta ~0.1
set yrange [0:0.1]
set ytics 0,0.01,0.1
set format y '%.3f'
# Graficar directamente columnas 5 y 6 del CSV (crudo, separado por coma)
plot \
  'db/comparar_Ns.csv' using 1:5 with lines lw 2 lc rgb '#d62728' title 'f4 (raw)', \
  'db/comparar_Ns.csv' using 1:6 with lines lw 2 lc rgb '#9467bd' title 'mergesort (raw)'
