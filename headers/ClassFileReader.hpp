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

class ClassFileReader {
public:
    static ClassFileReader& get_instance()
    {
        static ClassFileReader instance;
        return instance;
    }

    ~ClassFileReader();

    // Funcão principal que lê o .class
    ClassFile* read_class_file(FILE* file);

private:
    ClassFileReader();
    ClassFileReader(ClassFileReader const&);

    bool is_little_endian;
    bool check_endian_type();

    // Funcões para ler os dados binários (u1, u2 e u4)
    u1 read_u1(FILE* file);
    u2 read_u2(FILE* file);
    u4 read_u4(FILE* file);

    // Lê e verifica o número mágico do .class
    void set_magic(FILE* fp, ClassFile* class_file);
    bool check_magic_valid(ClassFile* class_file);

    // Lê e verifica a versão do .class
    void set_version(FILE* fp, ClassFile* class_file);
    bool is_version_valid(ClassFile* class_file, uint16_t major);

    // Lê a tabela de constantes
    void set_constant_pool(FILE* fp, ClassFile* class_file);
    void set_constant_pool_size(FILE* fp, ClassFile* class_file);

    // Funcões para ler as entradas da tabela de constantes
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

    // Funções para ler os atributos do .class (flags, classes, superclasses, interfaces e fields)
    void set_access_flags(FILE* fp, ClassFile* class_file);
    void set_this_class(FILE* fp, ClassFile* class_file);
    void set_super_class(FILE* fp, ClassFile* class_file);
    void set_interfaces_count(FILE* fp, ClassFile* class_file);
    void set_interfaces(FILE* fp, ClassFile* class_file);
    void set_fields_count(FILE* fp, ClassFile* class_file);
    void set_fields(FILE* fp, ClassFile* class_file);

    // Lê os atributos de cada campo
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
    ConstUtf8Info get_utf8_from_constant_pool(u2 index, ClassFile* class_file);

    // Funções para ler os métodos do .class (métodos do ClassFile e seus atributos)
    void set_methods(FILE* fp, ClassFile* class_file);
    void set_methods_count(FILE* fp, ClassFile* class_file);
    void set_attributes(FILE* fp, ClassFile* class_file);
    void set_attributes_count(FILE* fp, ClassFile* class_file);
    
    // Libera a memória alocada para o ClassFile    
    void free_class_file(ClassFile* class_file);
};

#endif
