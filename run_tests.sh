#!/bin/bash

mkdir -p ./output

# Loop over each .class file in the examples folder
for class_file in examples/*.class; do
    # Print the current testing file
    echo -e -n "\t\t"
    echo "Now testing: " $class_file
    # Setup the output file path
    stripped_format=${class_file%.class}
    stripped_path=${stripped_format#examples\/}
    output_file="output/${stripped_path}.txt"
    # Run the program with the given arguments
    ./bin -r=$class_file -o=$output_file
    # Leave an empty line for readability
    echo -e -n "\n"
done
