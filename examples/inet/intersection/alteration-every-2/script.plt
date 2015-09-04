set terminal postscript eps enhanced color "Bold-Times-New-Roman" 26 
set grid
set output "alteration-every-2.eps"
set xlabel font "Bold-Times-New-Roman,26" "Time (s)"
set ylabel offset 1 font "Bold-Times-New-Roman,26" "Traffic light timing"
set key left
set title font "Bold-Times-New-Roman,26" "Bypass interval: every 2 messages"

plot [0:90] [-15:15] "tl3" title "TL3 behavior" with lines lt 1 lc rgb "#FF0000" lw 3, "tl1" title "TL1, TL2 behavior" with lines  lt 1 lc rgb "#008000" lw 3
