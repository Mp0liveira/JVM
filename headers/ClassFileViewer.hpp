#ifndef CLASS_FILE_VIEWER_HPP
#define CLASS_FILE_VIEWER_HPP

#include "BaseType.hpp"
#include "ClassFile.hpp"
#include "ClassFileReader.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

/**
 * @file ClassFileViewer.hpp
 * @brief Declara funções para visualização e gravação de informações do arquivo `.class` Java.
 */

/**
 * @brief Escreve todas as informações contidas no ClassFile para um arquivo de saída.
 * 
 * @param class_file Ponteiro para a estrutura ClassFile.
 * @param output Ponteiro para o arquivo de saída.
 */
void write_class_file(ClassFile* class_file, FILE* output);

/**
 * @brief Escreve informações gerais do ClassFile, como versão e flags de acesso.
 * 
 * @param class_file Ponteiro para a estrutura ClassFile.
 */
void write_general_info(ClassFile* class_file);

/**
 * @brief Escreve os elementos da Constant Pool do ClassFile.
 * 
 * @param class_file Ponteiro para a estrutura ClassFile.
 */
void write_constant_pool(ClassFile* class_file);

/**
 * @brief Escreve as interfaces implementadas pela classe.
 * 
 * @param class_file Ponteiro para a estrutura ClassFile.
 */
void write_interfaces(ClassFile* class_file);

/**
 * @brief Escreve os campos declarados na classe.
 * 
 * @param class_file Ponteiro para a estrutura ClassFile.
 */
void write_fields(ClassFile* class_file);

/**
 * @brief Escreve os métodos da classe.
 * 
 * @param class_file Ponteiro para a estrutura ClassFile.
 */
void write_methods(ClassFile* class_file);

/**
 * @brief Escreve os atributos globais do ClassFile.
 * 
 * @param class_file Ponteiro para a estrutura ClassFile.
 */
void write_attributes(ClassFile* class_file);

/**
 * @brief Escreve um atributo específico do ClassFile.
 * 
 * @param attribute_info Estrutura com as informações do atributo.
 * @param index Índice do atributo (para identificação).
 * @param constant_pool Ponteiro para a Constant Pool.
 * @param indentation Nível de indentação para a saída.
 */
void write_attribute_info(AttributeInfo attribute_info, uint32_t index, ConstantPoolInfo* constant_pool, uint8_t indentation);

/**
 * @brief Escreve o bytecode contido no atributo CodeAttribute.
 * 
 * @param code_attribute Estrutura com o bytecode.
 * @param constant_pool Ponteiro para a Constant Pool.
 * @param indentation Nível de indentação para a saída.
 */
void write_file_bytecode(CodeAttribute code_attribute, ConstantPoolInfo* constant_pool, uint8_t indentation);

/**
 * @brief Retorna uma string representando os flags de acesso da classe, método ou campo.
 * 
 * @param access_flags Flags de acesso codificados como `u2`.
 * @return const char* String representando os flags.
 */
const char* get_access_flags(u2 access_flags);

/**
 * @brief Retorna uma constante formatada da Constant Pool, a partir de um índice.
 * 
 * @param constant_pool Ponteiro para a Constant Pool.
 * @param index Índice da constante a ser formatada.
 * @return const char* Representação em string da constante.
 */
const char* get_formatted_constant(ConstantPoolInfo* constant_pool, u2 index);

/**
 * @brief Array de nomes das instruções da JVM.
 * 
 * Este array contém as instruções em ordem de opcode (0x00 até 0xC9).
 * Pode ser usado para mapear bytecodes para nomes legíveis.
 */
static const string function_names_array[] = {
    "nop", 
    "aconst_null", 
    "iconst_m1", 
    "iconst_0", 
    "iconst_1", 
    "iconst_2", 
    "iconst_3", 
    "iconst_4", 
    "iconst_5",
    "lconst_0", 
    "lconst_1", 
    "fconst_0", 
    "fconst_1", 
    "fconst_2", 
    "dconst_0", 
    "dconst_1", 
    "bipush", 
    "sipush",
    "ldc", 
    "ldc_w", 
    "ldc2_w", 
    "iload", 
    "lload", 
    "fload", 
    "dload", 
    "aload", 
    "iload_0",
    "iload_1", 
    "iload_2", 
    "iload_3",
    "lload_0", 
    "lload_1", 
    "lload_2", 
    "lload_3", 
    "fload_0", 
    "fload_1", 
    "fload_2", 
    "fload_3", 
    "dload_0", 
    "dload_1",
    "dload_2", 
    "dload_3", 
    "aload_0", 
    "aload_1", 
    "aload_2",
    "aload_3", 
    "iaload", 
    "laload", 
    "faload", 
    "daload",
    "aaload",
    "baload", 
    "caload", 
    "saload", 
    "istore", 
    "lstore", 
    "fstore", 
    "dstore", 
    "astore", 
    "istore_0", 
    "istore_1", 
    "istore_2",
    "istore_3", 
    "lstore_0", 
    "lstore_1", 
    "lstore_2", 
    "lstore_3", 
    "fstore_0", 
    "fstore_1", 
    "fstore_2", 
    "fstore_3",
    "dstore_0", 
    "dstore_1", 
    "dstore_2", 
    "dstore_3", 
    "astore_0", 
    "astore_1", 
    "astore_2", 
    "astore_3", 
    "iastore",
    "lastore", 
    "fastore", 
    "dastore", 
    "aastore", 
    "bastore", 
    "castore", 
    "sastore", 
    "pop", 
    "pop2", 
    "dup", 
    "dup_x1",
    "dup_x2", 
    "dup2", 
    "dup2_x1", 
    "dup2_x2", 
    "swap", 
    "iadd", 
    "ladd", 
    "fadd", 
    "dadd", 
    "isub", 
    "lsub", 
    "fsub", 
    "dsub",
    "imul", 
    "lmul", 
    "fmul", 
    "dmul", 
    "idiv", 
    "ldiv", 
    "fdiv", 
    "ddiv", 
    "irem", 
    "lrem", 
    "frem", 
    "drem", 
    "ineg", 
    "lneg",
    "fneg", 
    "dneg", 
    "ishl", 
    "lshl", 
    "ishr", 
    "lshr", 
    "iushr", 
    "lushr", 
    "iand", 
    "land", 
    "ior", 
    "lor", 
    "ixor", 
    "lxor",
    "iinc", 
    "i2l", 
    "i2f", 
    "i2d", 
    "l2i", 
    "l2f", 
    "l2d", 
    "f2i", 
    "f2l", 
    "f2d", 
    "d2i", 
    "d2l", 
    "d2f", 
    "i2b", 
    "i2c", 
    "i2s",
    "lcmp", 
    "fcmpl", 
    "fcmpg", 
    "dcmpl", 
    "dcmpg", 
    "ifeq", 
    "ifne", 
    "iflt", 
    "ifge", 
    "ifgt", 
    "ifle", 
    "if_icmpeq",
    "if_icmpne", 
    "if_icmplt", 
    "if_icmpge", 
    "if_icmpgt", 
    "if_icmple", 
    "if_acmpeq", 
    "if_acmpne", 
    "goto", 
    "jsr", 
    "ret",
    "tableswitch", 
    "lookupswitch", 
    "ireturn", 
    "lreturn", 
    "freturn", 
    "dreturn",
    "areturn", 
    "return", 
    "getstatic",
    "putstatic", 
    "getfield", 
    "putfield", 
    "invokevirtual", 
    "invokespecial", 
    "invokestatic",
    "invokeinterface",
    "UNUSED", 
    "new", 
    "newarray", 
    "anewarray", 
    "arraylength", 
    "athrow", 
    "checkcast",
    "instanceof", 
    "monitorenter",
    "monitorexit", 
    "wide", 
    "multianewarray", 
    "ifnull", 
    "ifnonnull", 
    "goto_w", 
    "jsr_w"
};

#endif