set terminal pngcairo size 1920,1080 background rgb 'black'
set output "sorts_benchmark.png"

set title "Sorting Algorithms Benchmark"
set xlabel "Input Size"      tc rgb 'white'
set ylabel "Time (seconds)"  tc rgb 'white'
set border lc rgb 'white'
set key tc rgb 'white'
set linetype 1 lc rgb 'white'
set grid lc rgb 'white'

plot "shell_sort.dat" using 1:2 with linespoints title "Shell Sort", \
     "merge_sort_inplace.dat" using 1:2 with linespoints title "Merge Sort Inplace", \
     "merge_sort_shell_sort.dat" using 1:2 with linespoints title "Merge Sort with Shell Sort", \
     "merge_sort.dat" using 1:2 with linespoints title "Merge Sort", \
     "radix_sort.dat" using 1:2 with linespoints title "Radix Sort", \
     "heap_sort.dat" using 1:2 with linespoints title "Heap Sort", \
     "insertion.dat" using 1:2 with linespoints title "Insertion Sort", \
     "quick.dat" using 1:2 with linespoints title "Quick Sort", \
     "merge_sort_pp.dat" using 1:2 with linespoints title "PP Merge Sort"
