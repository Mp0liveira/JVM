#ifndef HEADER_FILE_NAME_HPP
#define HEADER_FILE_NAME_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file HEADER_FILE_NAME_HPP
 * @brief Declara a estrutura `Parameters` e funções para processamento de argumentos da linha de comando.
 */

/**
 * @struct Parameters
 * @brief Estrutura para armazenar os argumentos fornecidos pela linha de comando.
 */
typedef struct {
    char* class_file_path;     /**< Caminho do arquivo `.class` a ser processado. */
    char* output_file_path;    /**< Caminho do arquivo de saída (utilizado no modo leitura). */
    bool execute;              /**< Modo de operação: `true` para execução, `false` para leitura. */
} Parameters;

/**
 * @brief Analisa os argumentos da linha de comando e retorna uma estrutura Parameters preenchida.
 * 
 * @param argc Número de argumentos.
 * @param argv Vetor de strings com os argumentos.
 * @return Estrutura Parameters preenchida com os valores interpretados.
 */
const Parameters parse_args(int argc, char* argv[]);

/**
 * @brief Valida os parâmetros fornecidos, garantindo que são coerentes com os modos suportados.
 * 
 * @param params Ponteiro para a estrutura de parâmetros a ser validada.
 * @return `true` se os parâmetros forem válidos, `false` caso contrário.
 */
bool validate_parameters(const Parameters* params);

#endif // HEADER_FILE_NAME_HPP
