#ifndef HEADER_FILE_NAME_HPP
#define HEADER_FILE_NAME_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os argumentos recebidos pela linha de comando
typedef struct {
    char* class_file_path;     // Caminho do arquivo .class
    char* output_file_path;    // Caminho do arquivo de saída (se for leitura)
    bool execute;              // Indica se o modo é execução (true) ou leitura (false)
} Parameters;

// Função que analisa os argumentos passados na linha de comando e retorna a estrutura preenchida
const Parameters parse_args(int argc, char* argv[]);

// Função que valida se os argumentos fornecidos são válidos
bool validate_parameters(const Parameters* params);

#endif
