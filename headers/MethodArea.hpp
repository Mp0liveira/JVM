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

/**
 * @file MethodArea.hpp
 * @brief Declara a classe MethodArea, responsável pelo gerenciamento de classes carregadas pela JVM.
 */

/**
 * @class MethodArea
 * @brief Representa a área de métodos da JVM, responsável por armazenar classes carregadas.
 * 
 * Implementa o padrão Singleton. A MethodArea mantém um mapa de classes carregadas,
 * permitindo buscar ou carregar classes com base em seus nomes.
 */
class MethodArea {

public:
    /**
     * @brief Retorna a instância única da MethodArea (Singleton).
     * @return Referência para a instância da MethodArea.
     */
    static MethodArea& get_instance()
    {
        static MethodArea instance; // Singleton
        return instance;
    }

    /**
     * @brief Destrutor da MethodArea.
     */
    ~MethodArea();

    /**
     * @brief Carrega uma classe a partir do nome, se ainda não estiver carregada.
     * 
     * @param class_name Nome da classe a ser carregada.
     * @return Ponteiro para a classe carregada (StaticClass*).
     */
    StaticClass* load_class(const string& class_name); // load_class_by_name

    /**
     * @brief Retorna uma classe já carregada a partir do nome.
     * 
     * @param class_name Nome da classe.
     * @return Ponteiro para a StaticClass correspondente, ou nullptr se não encontrada.
     */
    StaticClass* get_class(const string& class_name); // get_class_by_name

    /**
     * @brief Caminho base onde os arquivos `.class` são procurados.
     * 
     * Deve ser configurado antes de chamar `load_class()`.
     */
    string class_path = "";

private:
    /**
     * @brief Construtor privado (Singleton).
     */
    MethodArea();

    /**
     * @brief Construtor de cópia desativado.
     */
    MethodArea(MethodArea const&);

    /**
     * @brief Operador de atribuição desativado.
     */
    void operator=(MethodArea const&);

    /**
     * @brief Insere uma classe carregada na MethodArea.
     * 
     * @param class_file Ponteiro para a classe carregada.
     * @return `true` se a inserção foi bem-sucedida, `false` se a classe já existia.
     */
    bool insert_class(StaticClass* class_file);

    /**
     * @brief Mapa com todas as classes já carregadas, indexadas por nome.
     */
    map<string, StaticClass*> classes;
};

#endif // METHOD_AREA_HPP
