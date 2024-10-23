set terminal pngcairo size 1920,1080 background rgb 'black'
set output "sorts_benchmark.png"

set title "Sorting Algorithms Benchmark"
set xlabel "Input Size"      tc rgb 'white'
set ylabel "Time (seconds)"  tc rgb 'white'
set border lc rgb 'white'
set key tc rgb 'white'
set linetype 1 lc rgb 'white'
set grid lc rgb 'white'

set style line 1 lc rgb '#FF5733' # Red
set style line 2 lc rgb '#33FF57' # Green
set style line 3 lc rgb '#3357FF' # Blue
set style line 4 lc rgb '#FFFF33' # Yellow
set style line 5 lc rgb '#FF33A1' # Magenta
set style line 6 lc rgb '#33FFF5' # Cyan
set style line 7 lc rgb '#FFA533' # Orange
set style line 8 lc rgb '#A133FF' # Purple
set style line 9 lc rgb '#FFFFFF' # White

plot "shell_sort.dat" using 1:2 with linespoints linestyle 1 title "Shell Sort", \
     "merge_sort_inplace.dat" using 1:2 with linespoints linestyle 2 title "Merge Sort Inplace", \
     "merge_sort_shell_sort.dat" using 1:2 with linespoints linestyle 3 title "Merge Sort with Shell Sort", \
     "merge_sort.dat" using 1:2 with linespoints linestyle 4 title "Merge Sort", \
     "radix_sort.dat" using 1:2 with linespoints linestyle 5 title "Radix Sort", \
     "heap_sort.dat" using 1:2 with linespoints linestyle 6 title "Heap Sort", \
     "insertion.dat" using 1:2 with linespoints linestyle 7 title "Insertion Sort", \
     "quick.dat" using 1:2 with linespoints linestyle 8 title "Quick Sort", \
     "merge_sort_pp.dat" using 1:2 with linespoints linestyle 9 title "PP Merge Sort"
