set terminal svg size 1920,1080 dynamic
set output "sorts_benchmark.svg"

set title "Sorting Algorithms Benchmark"
set xlabel "Input Size"
set ylabel "Time (seconds)"
set grid

plot "shell_sort.dat" using 1:2 with linespoints title "Shell Sort", \
     "merge_sort_inplace.dat" using 1:2 with linespoints title "Merge Sort Inplace", \
     "merge_sort_shell_sort.dat" using 1:2 with linespoints title "Merge Sort with Shell Sort", \
     "merge_sort.dat" using 1:2 with linespoints title "Merge Sort", \
     "radix_sort.dat" using 1:2 with linespoints title "Radix Sort", \
     "heap_sort.dat" using 1:2 with linespoints title "Heap Sort", \
     "insertion.dat" using 1:2 with linespoints title "Insertion Sort", \
     "quick.dat" using 1:2 with linespoints title "Quick Sort", \
     "merge_sort_pp.dat" using 1:2 with linespoints title "PP Merge Sort"
