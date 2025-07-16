#ifndef CLASS_FILE_READER_HPP
#define CLASS_FILE_READER_HPP

#include "BaseType.hpp"
#include "ClassFile.hpp"
#include <cassert>
#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

/**
 * @file ClassFileReader.hpp
 * @brief Declara a classe ClassFileReader responsável por interpretar arquivos `.class` da linguagem Java.
 */

/**
 * @class ClassFileReader
 * @brief Classe responsável por ler e interpretar os dados binários de um arquivo `.class` da JVM.
 * 
 * Implementa o padrão Singleton, contendo métodos para ler a estrutura de um arquivo `.class`, incluindo
 * informações gerais, constant pool, métodos, campos e atributos.
 */
class ClassFileReader {
public:
    /**
     * @brief Retorna a instância única do leitor de arquivos `.class`.
     * @return Referência para a instância Singleton.
     */
    static ClassFileReader& get_instance()
    {
        static ClassFileReader instance;
        return instance;
    }

    /**
     * @brief Destrutor.
     */
    ~ClassFileReader();

    /**
     * @brief Lê um arquivo `.class` e retorna sua representação interna.
     * @param file Ponteiro para o arquivo `.class` já aberto.
     * @return Ponteiro para estrutura ClassFile preenchida.
     */
    ClassFile* read_class_file(FILE* file);

private:
    /**
     * @brief Construtor privado (Singleton).
     */
    ClassFileReader();

    /**
     * @brief Construtor de cópia desativado (Singleton).
     */
    ClassFileReader(ClassFileReader const&);

    bool is_little_endian; ///< Indica se a máquina atual é little-endian.

    /**
     * @brief Verifica o tipo de endianess da máquina.
     * @return true se for little-endian.
     */
    bool check_endian_type();

    /**
    * @brief Lê um byte (unsigned 8 bits) do arquivo.
    * 
    * @param file Ponteiro para o arquivo aberto em modo leitura binária.
    * @return u1 Valor lido do arquivo.
    */
    u1 read_u1(FILE* file);

    /**
    * @brief Lê dois bytes (unsigned 16 bits) do arquivo, com endianness Big-Endian.
    * 
    * @param file Ponteiro para o arquivo aberto em modo leitura binária.
    * @return u2 Valor lido do arquivo.
    */
    u2 read_u2(FILE* file);

    /**
    * @brief Lê quatro bytes (unsigned 32 bits) do arquivo, com endianness Big-Endian.
    * 
    * @param file Ponteiro para o arquivo aberto em modo leitura binária.
    * @return u4 Valor lido do arquivo.
    */
    u4 read_u4(FILE* file);

    /**
    * @brief Lê e define o campo "magic" de um arquivo .class a partir do arquivo aberto.
    * 
    * @param fp Ponteiro para o arquivo .class aberto em modo leitura binária.
    * @param class_file Ponteiro para a estrutura ClassFile onde o campo magic será armazenado.
    */
    void set_magic(FILE* fp, ClassFile* class_file);

    /**
    * @brief Verifica se o campo "magic" da estrutura ClassFile possui o valor esperado (0xCAFEBABE).
    * 
    * @param class_file Ponteiro para a estrutura ClassFile a ser verificada.
    * @return true Se o campo magic for válido (igual a 0xCAFEBABE).
    * @return false Caso contrário.
    */
    bool check_magic_valid(ClassFile* class_file);

    /**
    * @brief Lê e define as versões minor e major de um arquivo .class a partir do arquivo aberto.
    * 
    * @param fp Ponteiro para o arquivo .class aberto em modo leitura binária.
    * @param class_file Ponteiro para a estrutura ClassFile onde as versões serão armazenadas.
    */
    void set_version(FILE* fp, ClassFile* class_file);

    /**
    * @brief Verifica se a versão major da estrutura ClassFile corresponde à versão esperada.
    * 
    * @param class_file Ponteiro para a estrutura ClassFile a ser verificada.
    * @param major Versão major esperada para validação.
    * @return true Se a versão major for válida (igual ao parâmetro major).
    * @return false Caso contrário.
    */
    bool is_version_valid(ClassFile* class_file, uint16_t major);


    /**
    * @brief Lê o tamanho da constant pool a partir do arquivo .class e armazena na estrutura ClassFile.
    * 
    * @param fp Ponteiro para o arquivo .class aberto em modo leitura binária.
    * @param class_file Ponteiro para a estrutura ClassFile onde o tamanho da constant pool será armazenado.
    */
    void set_constant_pool_size(FILE* fp, ClassFile* class_file);

    /**
    * @brief Lê e popula as entradas da constant pool no arquivo .class dentro da estrutura ClassFile.
    * 
    * Deve ser chamado após set_constant_pool_size para reservar o espaço necessário.
    * 
    * @param fp Ponteiro para o arquivo .class aberto em modo leitura binária.
    * @param class_file Ponteiro para a estrutura ClassFile onde a constant pool será armazenada.
    */
    void set_constant_pool(FILE* fp, ClassFile* class_file);


    // --- Leitura de entradas específicas da constant pool ---

    ConstClassInfo get_const_class_info(FILE* fp);
    ConstFieldRefInfo get_const_field_ref_info(FILE* fp);
    ConstMethodRefInfo get_const_method_ref_info(FILE* fp);
    ConstInterfaceMethodRefInfo get_const_interface_method_ref_info(FILE* fp);
    ConstStrInfo get_const_str_info(FILE* fp);
    ConstIntInfo get_const_int_info(FILE* fp);
    ConstFloatInfo get_const_float_info(FILE* fp);
    ConstLongInfo get_const_long_info(FILE* fp);
    ConstDoubleInfo get_const_double_info(FILE* fp);
    ConstNameTypeInfo get_const_name_type_info(FILE* fp);
    ConstUtf8Info get_const_utf8_info(FILE* fp);

    // --- Leitura de metadados da classe ---

    void set_access_flags(FILE* fp, ClassFile* class_file);
    void set_this_class(FILE* fp, ClassFile* class_file);
    void set_super_class(FILE* fp, ClassFile* class_file);
    void set_interfaces_count(FILE* fp, ClassFile* class_file);
    void set_interfaces(FILE* fp, ClassFile* class_file);
    void set_fields_count(FILE* fp, ClassFile* class_file);
    void set_fields(FILE* fp, ClassFile* class_file);

    // --- Leitura de atributos ---

    AttributeInfo get_attribute_info(FILE* fp, ClassFile* class_file);
    ConstValueAttribute get_attribute_constant_value(FILE* fp);
    ExceptionTable get_exception_table(FILE* fp);
    CodeAttribute get_attribute_code(FILE* fp, ClassFile* class_file);
    ExceptionsAttribute get_attribute_exceptions(FILE* fp);
    Class get_class(FILE* fp);
    InnerClassesAttribute get_attribute_inner_classes(FILE* fp);
    SyntheticAttribute get_attribute_synthetic();
    SourceFileAttribute get_attribute_source_file(FILE* fp);
    LineNumberTable get_line_number_table(FILE* fp);
    LineNumberTableAttribute get_attribute_line_number_table(FILE* fp);
    LocalVariableTable get_local_variable_table(FILE* fp);
    LocalVariableTableAttribute get_attribute_local_variable(FILE* fp);
    DeprecatedAttribute get_attribute_deprecated();

    /**
     * @brief Obtém uma entrada UTF-8 da constant pool por índice.
     * @param index Índice no constant pool.
     * @param class_file Estrutura ClassFile contendo a constant pool.
     * @return ConstUtf8Info Entrada UTF-8 correspondente.
     */
    ConstUtf8Info get_utf8_from_constant_pool(u2 index, ClassFile* class_file);

    // --- Leitura de métodos e seus atributos ---

    void set_methods(FILE* fp, ClassFile* class_file);
    void set_methods_count(FILE* fp, ClassFile* class_file);
    void set_attributes(FILE* fp, ClassFile* class_file);
    void set_attributes_count(FILE* fp, ClassFile* class_file);

    /**
     * @brief Libera todos os recursos alocados em uma estrutura ClassFile.
     * @param class_file Ponteiro para a estrutura a ser liberada.
     */
    void free_class_file(ClassFile* class_file);
};

#endif // CLASS_FILE_READER_HPP
