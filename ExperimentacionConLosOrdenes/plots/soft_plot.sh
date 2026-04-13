#!/usr/bin/env bash
set -euo pipefail

# Script helper: generar archivos muy suavizados y el PNG comparacion.png
W=201
mkdir -p plots/comparatives

# Asegurar que el script de suavizado sea ejecutable
chmod +x ./plots/smooth_csv.sh || true

./plots/smooth_csv.sh "$W" 2 db/comparar_Ns.csv plots/comparatives/f1_more_smooth.dat
./plots/smooth_csv.sh "$W" 3 db/comparar_Ns.csv plots/comparatives/f2_more_smooth.dat
./plots/smooth_csv.sh "$W" 4 db/comparar_Ns.csv plots/comparatives/f3_more_smooth.dat
./plots/smooth_csv.sh "$W" 5 db/comparar_Ns.csv plots/comparatives/f4_more_smooth.dat

# Generar mergesort: preferir ms_smooth.dat (ya existente), sino usar db/comparar_Ns.csv col 6 si existe
if awk -F, 'NR>1{if(NF>=6){exit 0}} END{exit 1}' db/comparar_Ns.csv; then
  ./plots/smooth_csv.sh "$W" 6 db/comparar_Ns.csv plots/comparatives/ms_more_smooth.dat
else
  # crear archivo vacío pero con un punto válido para evitar warnings (usar línea con primer n y 0)
  head -n1 db/comparar_Ns.csv | awk -F, 'NR==1{print "0 0"}' > plots/comparatives/ms_more_smooth.dat || :
fi

# Además generar una versión "raw" (sin suavizar) para mergesort para comparar fácilmente
if awk -F, 'NR>1{if(NF>=6){exit 0}} END{exit 1}' db/comparar_Ns.csv; then
  awk -F, 'NR>1{print $1, $6}' db/comparar_Ns.csv > plots/comparatives/ms_raw.dat
else
  : > plots/comparatives/ms_raw.dat
fi

# Generar el plot
gnuplot ./plots/plot_comparacion.gnuplot
