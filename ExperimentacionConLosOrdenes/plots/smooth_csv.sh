#!/usr/bin/env bash
# Uso: smooth_csv.sh WINDOW COL INFILE OUTFILE
window="$1"
col="$2"
infile="$3"
outfile="$4"

# Forzar locale POSIX para asegurar que awk imprima punto decimal
export LC_NUMERIC=C

awk -v W="$window" -v COL="$col" -F, 'NR>1{ L++; a[L] = $(COL); n[L] = $1 } END { for(i=1;i<=L;i++){ sum=0; start=i-int(W/2); end=i+int(W/2); if(start<1) start=1; if(end>L) end=L; cnt=0; for(j=start;j<=end;j++){ sum += a[j]; cnt++ } printf "%d %.6f\n", n[i], sum/cnt } }' "$infile" > "$outfile"
