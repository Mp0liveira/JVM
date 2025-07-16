#ifndef CLASS_FILE_UTILS_HPP
#define CLASS_FILE_UTILS_HPP

#include "BaseType.hpp"
#include "ClassFileReader.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * @file ClassFileUtils.hpp
 * @brief Classe utilitária para operações auxiliares relacionadas à leitura e manipulação de arquivos `.class` Java.
 */

class ClassFileUtils {
public:

    /**
     * @brief Retorna a versão da linguagem Java correspondente ao arquivo `.class`.
     * 
     * @param class_file Ponteiro para a estrutura ClassFile.
     * @return double Versão do Java (ex: 45.3, 52.0).
     * 
     * @note A versão é baseada nos valores `major_version` e `minor_version` do class_file.
     */
    static double return_version(ClassFile* class_file); // check_version

    /**
     * @brief Verifica se a versão do `.class` não é suportada e retorna a versão numérica.
     * 
     * @param class_file Ponteiro para a estrutura ClassFile.
     * @return double Versão do Java não suportada.
     * 
     * @note Essa função pode ser usada para emitir mensagens de erro ou advertência.
     */
    static double non_suported_version(ClassFile* class_file); // verify_class_version

    /**
     * @brief Compara uma string UTF-8 da Constant Pool com uma string C convencional.
     * 
     * @param constant Estrutura ConstUtf8Info a ser comparada.
     * @param str Ponteiro para string C que será comparada.
     * @return true Se ambas as strings forem iguais.
     * @return false Caso contrário.
     */
    static bool compare_utf8_str(ConstUtf8Info constant, const char* str);

    /**
     * @brief Verifica se o nome do arquivo `.class` coincide com o nome da classe declarada.
     * 
     * @param filename Nome do arquivo `.class`.
     * @param classname Nome da classe interna declarada no arquivo.
     * @return true Se os nomes coincidirem.
     * @return false Caso contrário.
     */
    static bool verify_classfile_name(string filename, string classname); // check_this_class

    /**
     * @brief Converte um objeto stringstream para uma string C (`const char*`).
     * 
     * @param ss Referência para o stringstream de entrada.
     * @return const char* String resultante alocada dinamicamente.
     * 
     * @warning A string retornada pode precisar ser liberada com `delete[]` para evitar vazamento de memória.
     */
    static const char* stream_to_cstring(const stringstream& ss);

    /**
     * @brief Imprime uma indentação (espaços) no arquivo especificado.
     * 
     * @param out Ponteiro para o arquivo de saída.
     * @param n Quantidade de espaços a serem impressos.
     */
    static void file_indent(FILE* out, uint8_t n);

    /**
     * @brief (Possivelmente obsoleta) Imprime indentação na saída padrão.
     * 
     * @param n Quantidade de espaços a serem impressos.
     * 
     * @note Esta função aparentemente não é utilizada e pode ser removida.
     */
    static void display_indent(uint8_t n);
};

#endif
