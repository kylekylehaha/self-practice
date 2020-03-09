reset
set ylabel 'time(ns)'
set xlabel 'size'
set title 'runtime'
set term png enhanced font 'Verdana,10'

set output 'runtime.png'
set key left top

plot [:][:] \
'test_fd.txt' using 1:2 with linespoints linewidth 2 title 'fast doubling', \
'test_fd_clz.txt' using 1:2 with linespoints linewidth 2 title 'fast doubling clz', \
'test_fseq.txt' using 1:2 with linespoints linewidth 2 title 'sequence'
