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

echo "Dimention=$dimentions"
echo "Dimention=$dimentions" >> $output_file

# Loop through the range of threads
for ((i=$start_value; i<=$end_value; i*=2))
do
    # Run the C++ program with the current command line arguments
    output=$("$cpp_program" $dimentions $i)

    # Print the command line arguments and recorded value
    echo "Threads=$i, Time: $output"
    echo "Threads=$i, Time: $output" >> $output_file
done

make clean
