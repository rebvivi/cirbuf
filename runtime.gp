reset
set ylabel 'time(ms)'
set xlabel 'message size'
set xtics 0, 128
set title 'runtime of circular buffer read write'
set term png enhanced font 'Verdana,10'

set output 'runtime_comparison.png'

plot [:][:0.032]'time.txt' \
   using 1:2 with linespoints linewidth 3  title 'slow', \
'' using 1:3 with linespoints linewidth 3 title 'fast' , \
