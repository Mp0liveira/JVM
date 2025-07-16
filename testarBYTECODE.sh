#!/bin/bash

mkdir -p ./output

# Loop para cada .class em exemplos
for class_file in examples/*.class; do
    echo -e -n "\t\t"
    echo "Testando o arquivo: " $class_file
    
    # Seta o caminho do diretorio de saida
    stripped_format=${class_file%.class}
    stripped_path=${stripped_format#examples\/}
    output_file="output/${stripped_path}.txt"
    
    # Executa o programa com os argumentos
    ./bin -r=$class_file -o=$output_file
    echo -e -n "\n"
done
