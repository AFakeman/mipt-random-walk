(echo threads count time
for count in 30 300 3000 30000; do
    for threads in 1 2 4 8 16; do
        for i in `seq 1 10`; do
            ./main 0 100 50 $count 0.5 $threads
        done | echo  $threads $count \
                     $(awk '{sum_time+=$1} \
                           END {print sum_time/10}') \
        
    done
done) | python3 render.py
