#ifndef STATIC_CLASS_HPP
#define STATIC_CLASS_HPP

#include "ClassFile.hpp"
#include "ClassFileReader.hpp"
#include <map>
#include <string>

using namespace std;

class StaticClass {

public:
    // Conta com um ponteiro para o ClassFile que contém os dados da classe
    StaticClass(ClassFile* class_file);

    // Retorna o ponteiro para o ClasseFile que foi passado no método construtor
    ClassFile* get_class_file();

    // Altera o valor de um static field
    void insert_value(const Value &value, const string& field_name); // insert_value_into_field

    // Acessa o valor de um static field
    Value get_value(const string& field_name); // get_value_from_field

    // Verifica se um static field em específico existe
    bool check_field(const string& field_name);  // field_exists

    // Inicializa os blocos de inicialização estáticas (clinit)
    string initialize_file(char* argv[]);

private:
    // ClassFile a ser acessado
    ClassFile* class_file;

    // Nomes e valores dos static fields
    map<string, Value> static_fields;
};

#endif
