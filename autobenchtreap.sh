#!/bin/sh

file="tabletreap.txt"

cat << EOF > $file
| Backend     | NSubreddits | NArticles | Execution Time | Memory Used  |
|-------------|-------------|-----------|----------------|--------------|
EOF

for mode in treap
do
    for nitems in 1 10 25 50 100 250
    do
        for narticles in 1 5 10 20 27
        do
            FILE="sub${nitems}.txt"
            INS_TIME=$(../common/measure store_reddit -b $mode -n $narticles < $FILE | tail -n 1 | grep -Eo '[0-9.]*' | head -n 1)
            SEA_TIME=$(../common/measure store_reddit -b $mode -n $narticles < $FILE | tail -n 1 | grep -Eo '[0-9.]*' | tail -n 1)
            printf "| %-12s| %-12s| %-10s| %-15s| %-13s|\n" "$mode" "$nitems" "$narticles" "$INS_TIME" "$SEA_TIME" >> $file
            cat $file
        done
    done
done


