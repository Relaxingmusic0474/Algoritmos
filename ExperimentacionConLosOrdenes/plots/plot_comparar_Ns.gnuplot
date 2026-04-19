# Script de gnuplot para comparar tiempos (f1,f2,f3,f4,mergesort)
set terminal pngcairo size 900,600 enhanced font 'DejaVu Sans,10'
set output 'plots/comparatives/comparar_Ns.png'
set datafile separator ','
set key left top
set title 'Comparativa de tiempos: f1 vs f2 vs f3 vs f4 vs mergesort'
set xlabel 'n'
set ylabel 'tiempo (s)'
set grid
# Forzar ticks cada 0.001, rango desde 0 y redondeo superior de ymax al múltiplo de 0.001
stats "db/comparar_Ns.csv" using 1 name 'X' nooutput
stats "db/comparar_Ns.csv" using 6 name 'Y' nooutput
xmax = X_max
ymin = Y_min

# Forzar rango Y entre 0.000 y 0.010 con pasos de 0.001 (10 pasos de 0.001)
set yrange [0:0.010]
set ytics 0,0.001,0.010
set format y '%.3f'

# ajustar márgenes y desplazamiento de etiqueta para mejorar separación visual
set lmargin 16
set bmargin 6
set ylabel offset -1,0

# Calcular factores de escala para las curvas de referencia (n y n log n)
scale_n = (xmax > 0) ? (0.010 / xmax) : 1
scale_nlog = (xmax > 1) ? (0.010 / (xmax * log(xmax))) : scale_n

# funciones de referencia escaladas
f_n(x) = scale_n * x
f_nlog(x) = scale_nlog * x * log(x)

# Líneas originales menos nítidas: líneas finas y sin marcadores
set style line 1 lt 1 lw 0.6 lc rgb '#1f77b4'
set style line 2 lt 1 lw 0.6 lc rgb '#ff7f0e'
set style line 3 lt 1 lw 0.6 lc rgb '#2ca02c'
set style line 4 lt 1 lw 0.6 lc rgb '#d62728'
set style line 5 lt 1 lw 0.6 lc rgb '#9467bd'

# Líneas de tendencia más marcadas (suavizado)
set style line 11 lt 1 lw 2.5 lc rgb '#1f77b4'
set style line 12 lt 1 lw 2.5 lc rgb '#ff7f0e'
set style line 13 lt 1 lw 2.5 lc rgb '#2ca02c'
set style line 14 lt 1 lw 2.5 lc rgb '#d62728'
set style line 15 lt 1 lw 2.5 lc rgb '#9467bd'

# Ventana de media móvil (menor para no sobre-alisar): ajustar si quieres
window = 21
# Llamar al script de shell que genera archivos suavizados
system(sprintf("/bin/bash plots/smooth_csv.sh %d 2 db/comparar_Ns.csv plots/comparatives/f1_smooth.dat", window))
system(sprintf("/bin/bash plots/smooth_csv.sh %d 3 db/comparar_Ns.csv plots/comparatives/f2_smooth.dat", window))
system(sprintf("/bin/bash plots/smooth_csv.sh %d 4 db/comparar_Ns.csv plots/comparatives/f3_smooth.dat", window))
system(sprintf("/bin/bash plots/smooth_csv.sh %d 5 db/comparar_Ns.csv plots/comparatives/f4_smooth.dat", window))
system(sprintf("/bin/bash plots/smooth_csv.sh %d 6 db/comparar_Ns.csv plots/comparatives/ms_smooth.dat", window))

# Usar configuración fija y gruesa para garantizar visibilidad
set yrange [0:0.003]
set ytics 0,0.0005,0.003
set format y '%.6f'

# Líneas de tendencia visibles y continuas
set style line 11 lt 1 lw 3.5 lc rgb '#1f77b4'
set style line 12 lt 1 lw 3.5 lc rgb '#ff7f0e'
set style line 13 lt 1 lw 3.5 lc rgb '#2ca02c'
set style line 14 lt 1 lw 3.5 lc rgb '#d62728'
set style line 15 lt 1 lw 3.5 lc rgb '#9467bd'

plot \
	'plots/comparatives/f1_smooth.dat' using 1:2 smooth csplines with lines ls 11 title 'f1 (smooth)', \
	'plots/comparatives/f2_smooth.dat' using 1:2 smooth csplines with lines ls 12 title 'f2 (smooth)', \
	'plots/comparatives/f3_smooth.dat' using 1:2 smooth csplines with lines ls 13 title 'f3 (smooth)', \
	'plots/comparatives/f4_smooth.dat' using 1:2 smooth csplines with lines ls 14 title 'f4 (smooth)', \
	'plots/comparatives/ms_smooth.dat' using 1:2 smooth csplines with lines ls 15 title 'mergesort (smooth)'
