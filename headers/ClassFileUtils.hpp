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

class ClassFileUtils {
public:
    
    // Retorna versão do Java (45 até 52)
    static double return_version(ClassFile* class_file);    // check_version

    // Retorna versão do Java não suportada
    static double non_suported_version(ClassFile* class_file);  //verify_class_version

    // Compara string da ConstantPool com string em C
    static bool compare_utf8_str(ConstUtf8Info constant, const char* str);

    // Verifica se o nome do arquivo .class corresponde a classe declarada no arquivo
    static bool verify_classfile_name(string filename, string classname);   //check_this_class

    // Transforma streamstring para char*
    static const char* stream_to_cstring(const stringstream& ss);

    // Indentar a saída  
    static void file_indent(FILE* out, uint8_t n);

    // ACHO QUE PODE APAGAR, NÃO TEM REFERENCIA DESSA FUNCAO EM LUGAR NENHUM
    static void display_indent(uint8_t n);

};

#endif
