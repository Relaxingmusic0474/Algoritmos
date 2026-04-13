set terminal pngcairo size 900,600 enhanced font 'DejaVuSans,10'
set output 'plots/comparatives/comparacion_f4_msort_smooth.png'

set datafile separator ','
set xlabel 'n'
set ylabel 'Tiempo (s)'

# Título del gráfico
set title 'Comparación f4 y mergesort (suavizado)'

# Ajuste de ejes según petición
set yrange [0:0.003]
set ytics 0.0005
set grid ytics

# Generar archivos suavizados (salida con separador espacio)
system("bash -c 'plots/smooth_csv.sh 101 5 db/comparar_Ns.csv plots/comparatives/f4_smooth_for_plot.dat'")
system("bash -c 'plots/smooth_csv.sh 101 6 db/comparar_Ns.csv plots/comparatives/ms_smooth_for_plot.dat'")

# Los archivos generados por smooth_csv.sh usan separador espacio
set datafile separator ' '

plot \
  'plots/comparatives/f4_smooth_for_plot.dat' using 1:2 with lines lw 1 lc rgb '#FF0000' title 'f4 (smooth)', \
  'plots/comparatives/ms_smooth_for_plot.dat' using 1:2 with lines lw 1 lc rgb '#7E2F8E' title 'mergesort (smooth)'
