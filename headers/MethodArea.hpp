#ifndef METHOD_AREA_HPP
#define METHOD_AREA_HPP

#include "BaseType.hpp"
#include "StaticClass.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class MethodArea {

public:
    
    // Garante que só existe uma instância de MethodArea
    static MethodArea& get_instance()
    {
        static MethodArea instance; // Singleton
        return instance;
    }

    // Destrutor
    ~MethodArea();

    // Retorna a instância da classe se ela já estiver sido carregada
    StaticClass* load_class(const string& class_name); // load_class_by_name

    // Retorna um ponteiro para um objeto static class
    StaticClass* get_class(const string& class_name); // get_class_by_name

    // Caminho com os arquivos necessários para execução da JVM
    string class_path = "";

private:
    
    MethodArea();

    MethodArea(MethodArea const&);

    void operator=(MethodArea const&);

    // Adiciona uma classe já carregada no MethodArea
    bool insert_class(StaticClass* class_file);

    // Classes já carregadas
    map<string, StaticClass*> classes;
};

#endif // METHOD_AREA_HPP
