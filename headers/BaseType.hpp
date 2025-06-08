#ifndef BASETYPE
#define BASETYPE

#include <stdint.h>

// Tipos de dados

typedef uint8_t u1; // 8 bits
typedef uint16_t u2; // 16 bits
typedef uint32_t u4; // 32 bits

// Tipos de objetos
enum ObjectType {
    CLASS_INSTANCE, // Representa a class instance
    STRING_INSTANCE, // Representa a string instance
    ARRAY // Representa array instance
};
typedef enum ObjectType ObjectType;

// Value types e tipos primitivos
enum ValueType {
    BOOLEAN,
    BYTE,
    CHAR,
    SHORT,
    INT,
    FLOAT,
    LONG,
    DOUBLE,
    RETURN_ADDR,
    REFERENCE,
    PADDING
};
typedef enum ValueType ValueType;


class Object;
struct Value;
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

struct Value {
    ValueType print_type; // O tipo do valor
    ValueType type; // O valor do tipo
    union {
        bool boolean_value;
        int8_t byte_value;
        uint8_t char_value;
        int16_t short_value;
        int32_t int_value;
        float float_value;
        int64_t long_value;
        double double_value;
        u4 return_address;
        Object* object;
    } data; 
};
typedef struct Value Value;

// Constant pool
typedef struct ConstantPoolInfo ConstantPoolInfo;
typedef struct ConstClassInfo ConstClassInfo;
typedef struct ConstFieldRefInfo ConstFieldRefInfo;
typedef struct ConstMethodRefInfo ConstMethodRefInfo;
typedef struct ConstInterfaceMethodRefInfo ConstInterfaceMethodRefInfo;
typedef struct ConstStrInfo ConstStrInfo;
typedef struct ConstIntInfo ConstIntInfo;
typedef struct ConstFloatInfo ConstFloatInfo;
typedef struct ConstLongInfo ConstLongInfo;
typedef struct ConstDoubleInfo ConstDoubleInfo;
typedef struct ConstNameTypeInfo ConstNameTypeInfo;
typedef struct ConstUtf8Info ConstUtf8Info;
typedef struct FieldInfo FieldInfo;
typedef struct AttributeInfo AttributeInfo;
typedef struct ConstValueAttribute ConstValueAttribute;
typedef struct ExceptionTable ExceptionTable;
typedef struct CodeAttribute CodeAttribute;
typedef struct ExceptionsAttribute ExceptionsAttribute;
typedef struct Class Class;
typedef struct InnerClassesAttribute InnerClassesAttribute;
typedef struct SyntheticAttribute SyntheticAttribute;
typedef struct SourceFileAttribute SourceFileAttribute;
typedef struct LineNumberTable LineNumberTable;
typedef struct LineNumberTableAttribute LineNumberTableAttribute;
typedef struct LocalVariableTable LocalVariableTable;
typedef struct LocalVariableTableAttribute LocalVariableTableAttribute;
typedef struct DeprecatedAttribute DeprecatedAttribute;
typedef struct MethodInfo MethodInfo;

enum FIELD_FLAGS {
    FIELD_FLAG_ACC_PUBLIC = 0x1,
    FIELD_FLAG_ACC_PRIVATE = 0x2,
    FIELD_FLAG_ACC_PROTECTED = 0x4,
    FIELD_FLAG_ACC_STATIC = 0x8,
    FIELD_FLAG_ACC_FINAL = 0x10,
    FIELD_FLAG_ACC_VOLATILE = 0x40,
    FIELD_FLAG_ACC_TRANSIENT = 0x80,
    FIELD_FLAG_ACC_SYNTHETIC = 0x1000,
    FIELD_FLAG_ACC_ENUM = 0x4000,
};

// Field do classfile
struct FieldInfo {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo* attributes;
};

// Mmetodo do classfile
struct MethodInfo {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo* attributes;
};

// TIpos das constantes do constante pool
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

struct ConstClassInfo {
    u2 name_index;
};

struct ConstFieldRefInfo {
    u2 class_index;
    u2 name_and_type_index;
};

struct ConstMethodRefInfo {
    u2 class_index;
    u2 name_and_type_index;
};

struct ConstInterfaceMethodRefInfo {
    u2 class_index;
    u2 name_and_type_index;
};

struct ConstStrInfo {
    u2 string_index;
};

struct ConstIntInfo {
    u4 bytes;
};

struct ConstFloatInfo {
    u4 bytes;
};

struct ConstLongInfo {
    u4 high_bytes;
    u4 low_bytes;
};

struct ConstDoubleInfo {
    u4 high_bytes;
    u4 low_bytes;
};

struct ConstNameTypeInfo {
    u2 name_index;
    u2 descriptor_index;
};

struct ConstUtf8Info {
    u2 length;
    u1* bytes;
};

struct ConstantPoolInfo {
    u1 tag;
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

struct ConstValueAttribute {
    u2 const_value_index;
};

struct ExceptionTable {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

struct CodeAttribute {
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1* code;
    u2 exception_table_length;
    ExceptionTable* exception_table;
    u2 attributes_count;
    AttributeInfo* attributes;
};

struct ExceptionsAttribute {
    u2 number_of_exceptions;
    u2* exception_index_table;
};

struct Class {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
};

struct InnerClassesAttribute {
    u2 number_of_classes;
    Class* classes;
};

struct SyntheticAttribute { };

struct SourceFileAttribute {
    u2 sourcefile_index;
};

struct LineNumberTable {
    u2 start_pc;
    u2 line_number;
};

struct LineNumberTableAttribute {
    u2 line_number_table_length;
    LineNumberTable* line_number_table;
};

struct LocalVariableTable {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
};

struct LocalVariableTableAttribute {
    u2 local_variable_table_length;
    LocalVariableTable* local_variable_table;
};

struct DeprecatedAttribute { };

struct DeprecatedAttribute1 { };

struct AttributeInfo {
    u2 attribute_name_index;
    u4 attribute_length;
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