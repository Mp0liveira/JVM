#ifndef CLASSFILE
#define CLASSFILE

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string>
#include <fstream>
#include "BaseType.hpp"

using namespace std;

/**
 * @file ClassFile.hpp
 * @brief Define a estrutura principal que representa um arquivo `.class` Java.
 */

/**
 * @class ClassFile
 * @brief Representa a estrutura completa de um arquivo `.class` Java, contendo informações gerais,
 * constant pool, campos, métodos e atributos.
 */
class ClassFile {
public:
    /**
     * @brief Construtor padrão.
     */
    ClassFile();

    u4 magic;                     /**< Número mágico identificador do arquivo (.class) */
    u2 minor_version;             /**< Versão menor do formato da classe */
    u2 major_version;             /**< Versão maior do formato da classe */
    u2 constant_pool_count;       /**< Quantidade de entradas no constant pool */
    ConstantPoolInfo* constant_pool; /**< Ponteiro para o constant pool */
    u2 access_flags;              /**< Flags de acesso da classe (público, final, abstrato, etc.) */
    u2 this_class;                /**< Índice da classe atual no constant pool */
    u2 super_class;               /**< Índice da superclasse no constant pool */
    u2 interfaces_count;          /**< Quantidade de interfaces implementadas */
    u2* interfaces;               /**< Array de índices das interfaces no constant pool */
    u2 fields_count;              /**< Quantidade de campos (fields) da classe */
    FieldInfo* fields;            /**< Ponteiro para os campos da classe */
    u2 methods_count;             /**< Quantidade de métodos da classe */
    MethodInfo* methods;          /**< Ponteiro para os métodos da classe */
    u2 attributes_count;          /**< Quantidade de atributos da classe */
    AttributeInfo* attributes;    /**< Ponteiro para os atributos da classe */
};

#endif // CLASSFILE
