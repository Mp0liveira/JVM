#ifndef BASETYPE
#define BASETYPE

#include <stdint.h>

/**
 * @file BaseType.hpp
 * @brief Define os tipos básicos e estruturas essenciais para a JVM.
 */

/**
 * @typedef u1
 * @brief Inteiro sem sinal de 8 bits.
 */
typedef uint8_t u1;

/**
 * @typedef u2
 * @brief Inteiro sem sinal de 16 bits.
 */
typedef uint16_t u2;

/**
 * @typedef u4
 * @brief Inteiro sem sinal de 32 bits.
 */
typedef uint32_t u4;

/**
 * @enum ObjectType
 * @brief Tipos possíveis para objetos na JVM.
 */
enum ObjectType {
    CLASS_INSTANCE,     /**< Representa uma instância de classe Java */
    STRING_INSTANCE,    /**< Representa uma instância de String Java */
    ARRAY               /**< Representa uma instância de array */
};
typedef enum ObjectType ObjectType;

/**
 * @enum ValueType
 * @brief Tipos possíveis para valores usados na JVM.
 */
enum ValueType {
    BOOLEAN,
    BYTE,
    CHAR,
    SHORT,
    INT,
    FLOAT,
    LONG,
    DOUBLE,
    RETURN_ADDR,    /**< Endereço de retorno para invocações */
    REFERENCE,      /**< Referência para objetos */
    PADDING         /**< Espaço reservado */
};
typedef enum ValueType ValueType;

class Object; ///< Declaração antecipada da classe Object

/**
 * @struct Value
 * @brief Estrutura que representa um valor na JVM, com seu tipo e dados.
 */
struct Value {
    ValueType print_type;   /**< Tipo para impressão/formatação */
    ValueType type;         /**< Tipo real do valor */
    union {
        bool boolean_value;       /**< Valor booleano */
        int8_t byte_value;        /**< Valor byte */
        uint8_t char_value;       /**< Valor char */
        int16_t short_value;      /**< Valor short */
        int32_t int_value;        /**< Valor inteiro */
        float float_value;        /**< Valor float */
        int64_t long_value;       /**< Valor long */
        double double_value;      /**< Valor double */
        u4 return_address;        /**< Endereço de retorno */
        Object* object;           /**< Ponteiro para objeto */
    } data; 
};
typedef struct Value Value;

// Forward declarations das estruturas usadas no constant pool e atributos
struct ConstantPoolInfo;
struct ConstClassInfo;
struct ConstFieldRefInfo;
struct ConstMethodRefInfo;
struct ConstInterfaceMethodRefInfo;
struct ConstStrInfo;
struct ConstIntInfo;
struct ConstFloatInfo;
struct ConstLongInfo;
struct ConstDoubleInfo;
struct ConstNameTypeInfo;
struct ConstUtf8Info;
struct FieldInfo;
struct AttributeInfo;
struct ConstValueAttribute;
struct ExceptionTable;
struct CodeAttribute;
struct ExceptionsAttribute;
struct Class;
struct InnerClassesAttribute;
struct SyntheticAttribute;
struct SourceFileAttribute;
struct LineNumberTable;
struct LineNumberTableAttribute;
struct LocalVariableTable;
struct LocalVariableTableAttribute;
struct DeprecatedAttribute;
struct MethodInfo;

// Flags para campos (fields)
enum FIELD_FLAGS {
    FIELD_FLAG_ACC_PUBLIC = 0x1,       /**< Público */
    FIELD_FLAG_ACC_PRIVATE = 0x2,      /**< Privado */
    FIELD_FLAG_ACC_PROTECTED = 0x4,    /**< Protegido */
    FIELD_FLAG_ACC_STATIC = 0x8,       /**< Estático */
    FIELD_FLAG_ACC_FINAL = 0x10,       /**< Final */
    FIELD_FLAG_ACC_VOLATILE = 0x40,    /**< Volátil */
    FIELD_FLAG_ACC_TRANSIENT = 0x80,   /**< Transiente */
    FIELD_FLAG_ACC_SYNTHETIC = 0x1000, /**< Sintético */
    FIELD_FLAG_ACC_ENUM = 0x4000        /**< Enumeração */
};

/**
 * @struct FieldInfo
 * @brief Representa um campo (field) de uma classe Java.
 */
struct FieldInfo {
    u2 access_flags;             /**< Flags de acesso ao campo */
    u2 name_index;               /**< Índice do nome no constant pool */
    u2 descriptor_index;         /**< Índice do descritor no constant pool */
    u2 attributes_count;         /**< Quantidade de atributos */
    AttributeInfo* attributes;   /**< Ponteiro para os atributos */
};

/**
 * @struct MethodInfo
 * @brief Representa um método de uma classe Java.
 */
struct MethodInfo {
    u2 access_flags;             /**< Flags de acesso ao método */
    u2 name_index;               /**< Índice do nome no constant pool */
    u2 descriptor_index;         /**< Índice do descritor no constant pool */
    u2 attributes_count;         /**< Quantidade de atributos */
    AttributeInfo* attributes;   /**< Ponteiro para os atributos */
};

/**
 * @enum ConstType
 * @brief Tipos de constantes na constant pool.
 */
typedef enum ConstType {
    ConstClass = 7,
    ConstFieldRef = 9,
    ConstMethodRef = 10,
    ConstInterfaceMethodRef = 11,
    ConstStr = 8,
    ConstInt = 3,
    ConstFloat = 4,
    ConstLong = 5,
    ConstDouble = 6,
    ConstNameType = 12,
    ConstUtf8 = 1,
    ConstNull = 0
} ConstType;

/**
 * @struct ConstClassInfo
 * @brief Informação de constante do tipo Classe.
 */
struct ConstClassInfo {
    u2 name_index; /**< Índice UTF8 do nome da classe */
};

/**
 * @struct ConstFieldRefInfo
 * @brief Informação de constante FieldRef.
 */
struct ConstFieldRefInfo {
    u2 class_index;           /**< Índice para a classe */
    u2 name_and_type_index;   /**< Índice para nome e tipo */
};

/**
 * @struct ConstMethodRefInfo
 * @brief Informação de constante MethodRef.
 */
struct ConstMethodRefInfo {
    u2 class_index;           /**< Índice para a classe */
    u2 name_and_type_index;   /**< Índice para nome e tipo */
};

/**
 * @struct ConstInterfaceMethodRefInfo
 * @brief Informação de constante InterfaceMethodRef.
 */
struct ConstInterfaceMethodRefInfo {
    u2 class_index;           /**< Índice para a classe */
    u2 name_and_type_index;   /**< Índice para nome e tipo */
};

/**
 * @struct ConstStrInfo
 * @brief Informação de constante String.
 */
struct ConstStrInfo {
    u2 string_index;          /**< Índice para string UTF8 */
};

/**
 * @struct ConstIntInfo
 * @brief Informação de constante Integer.
 */
struct ConstIntInfo {
    u4 bytes;                 /**< Valor inteiro */
};

/**
 * @struct ConstFloatInfo
 * @brief Informação de constante Float.
 */
struct ConstFloatInfo {
    u4 bytes;                 /**< Valor float */
};

/**
 * @struct ConstLongInfo
 * @brief Informação de constante Long.
 */
struct ConstLongInfo {
    u4 high_bytes;            /**< Bytes altos */
    u4 low_bytes;             /**< Bytes baixos */
};

/**
 * @struct ConstDoubleInfo
 * @brief Informação de constante Double.
 */
struct ConstDoubleInfo {
    u4 high_bytes;            /**< Bytes altos */
    u4 low_bytes;             /**< Bytes baixos */
};

/**
 * @struct ConstNameTypeInfo
 * @brief Informação de constante NameAndType.
 */
struct ConstNameTypeInfo {
    u2 name_index;            /**< Índice para nome */
    u2 descriptor_index;      /**< Índice para descritor */
};

/**
 * @struct ConstUtf8Info
 * @brief Informação de constante UTF8.
 */
struct ConstUtf8Info {
    u2 length;                /**< Comprimento da string */
    u1* bytes;                /**< Ponteiro para os bytes da string */
};

/**
 * @struct ConstantPoolInfo
 * @brief Entrada genérica da constant pool.
 */
struct ConstantPoolInfo {
    u1 tag;                   /**< Tipo da constante */
    union {
        ConstClassInfo class_info;
        ConstFieldRefInfo field_ref_info;
        ConstMethodRefInfo method_ref_info;
        ConstInterfaceMethodRefInfo interface_method_ref_info;
        ConstStrInfo str_info;
        ConstIntInfo int_info;
        ConstFloatInfo float_info;
        ConstLongInfo long_info;
        ConstDoubleInfo double_info;
        ConstNameTypeInfo name_type_info;
        ConstUtf8Info utf8_info;
    } info;
};

/**
 * @struct ConstValueAttribute
 * @brief Atributo que contém valor constante.
 */
struct ConstValueAttribute {
    u2 const_value_index;     /**< Índice para o valor constante */
};

/**
 * @struct ExceptionTable
 * @brief Entrada da tabela de exceções do atributo Code.
 */
struct ExceptionTable {
    u2 start_pc;              /**< Início do código protegido */
    u2 end_pc;                /**< Fim do código protegido */
    u2 handler_pc;            /**< Posição do handler */
    u2 catch_type;            /**< Tipo da exceção capturada */
};

/**
 * @struct CodeAttribute
 * @brief Atributo Code contendo o código bytecode do método.
 */
struct CodeAttribute {
    u2 max_stack;                 /**< Tamanho máximo da pilha */
    u2 max_locals;                /**< Número máximo de variáveis locais */
    u4 code_length;               /**< Tamanho do código */
    u1* code;                    /**< Ponteiro para o bytecode */
    u2 exception_table_length;    /**< Tamanho da tabela de exceções */
    ExceptionTable* exception_table; /**< Ponteiro para a tabela de exceções */
    u2 attributes_count;          /**< Quantidade de atributos */
    AttributeInfo* attributes;    /**< Ponteiro para os atributos */
};

/**
 * @struct ExceptionsAttribute
 * @brief Atributo Exceptions que lista exceções lançadas.
 */
struct ExceptionsAttribute {
    u2 number_of_exceptions;      /**< Quantidade de exceções */
    u2* exception_index_table;    /**< Índices das exceções */
};

/**
 * @struct Class
 * @brief Entrada da lista de classes internas.
 */
struct Class {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
};

/**
 * @struct InnerClassesAttribute
 * @brief Atributo contendo classes internas.
 */
struct InnerClassesAttribute {
    u2 number_of_classes;
    Class* classes;
};

/**
 * @struct SyntheticAttribute
 * @brief Atributo sintético (vazio).
 */
struct SyntheticAttribute { };

/**
 * @struct SourceFileAttribute
 * @brief Atributo com informação do arquivo fonte.
 */
struct SourceFileAttribute {
    u2 sourcefile_index;
};

/**
 * @struct LineNumberTable
 * @brief Entrada da tabela de número de linhas.
 */
struct LineNumberTable {
    u2 start_pc;
    u2 line_number;
};

/**
 * @struct LineNumberTableAttribute
 * @brief Atributo que contém a tabela de números de linha.
 */
struct LineNumberTableAttribute {
    u2 line_number_table_length;
    LineNumberTable* line_number_table;
};

/**
 * @struct LocalVariableTable
 * @brief Entrada da tabela de variáveis locais.
 */
struct LocalVariableTable {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
};

/**
 * @struct LocalVariableTableAttribute
 * @brief Atributo que contém a tabela de variáveis locais.
 */
struct LocalVariableTableAttribute {
    u2 local_variable_table_length;
    LocalVariableTable* local_variable_table;
};

/**
 * @struct DeprecatedAttribute
 * @brief Atributo Deprecated (vazio).
 */
struct DeprecatedAttribute { };

/**
 * @struct DeprecatedAttribute1
 * @brief Versão alternativa do atributo Deprecated (vazio).
 */
struct DeprecatedAttribute1 { };

/**
 * @struct AttributeInfo
 * @brief Estrutura genérica para atributos do classfile.
 */
struct AttributeInfo {
    u2 attribute_name_index;  /**< Índice do nome do atributo */
    u4 attribute_length;      /**< Comprimento do atributo */
    union {
        ConstValueAttribute const_value_info;
        CodeAttribute code_info;
        ExceptionsAttribute exceptions_info;
        InnerClassesAttribute inner_classes_info;
        SyntheticAttribute synthetic_info;
        SourceFileAttribute source_file_info;
        LineNumberTableAttribute line_number_table_info;
        LocalVariableTableAttribute local_variable_table_info;
        DeprecatedAttribute deprecated_info;
        DeprecatedAttribute1 deprecated_info1;
    } info;
};

#endif
