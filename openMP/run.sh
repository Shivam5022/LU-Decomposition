#!/bin/bash

# Set the path to your C++ program
cpp_program="./prog"
output_file="omp-time.txt"

dimentions=3000

start_value=1
end_value=16

clang-format -i *.cpp
clang-format -i *.hpp
make

# echo "Dimention=$dimentions"
# echo "Dimention=$dimentions" >> $output_file

# Loop through the range of threads
for ((j= 3000; j<=8000; j+=1000))
do
    echo "Dimention=$j"
    echo "Dimention=$j" >> $output_file
    for ((i=$start_value; i<=$end_value; i*=2))
    do
        # Run the C++ program with the current command line arguments
        output=$("$cpp_program" $j $i)

        # Print the command line arguments and recorded value
        echo "Threads=$i, Time: $output"
        echo "Threads=$i, Time: $output" >> $output_file
    done
done

make clean