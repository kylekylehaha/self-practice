reset
set ylabel 'time(ns)'
set xlabel 'experiment time'
set title 'diff sorting time'
set term png enhanced font 'Verdana, 10'

set output 'diff_sorting_time.png'

plot[:][:] \
'op_merge_sort.txt' using 1:2 with linespoints linewidth 3 title 'op merge sort', \
'insertion_sort.txt' using 1:2 with linespoints linewidth 3 title 'insertion sort', \
'merge_sort.txt' using 1:2 with linespoints linewidth 3 title 'merge_sort'

