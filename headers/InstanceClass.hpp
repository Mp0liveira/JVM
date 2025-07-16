#ifndef INSTANCE_CLASS_HPP
#define INSTANCE_CLASS_HPP

#include "BaseType.hpp"
#include "Object.hpp"
#include "StaticClass.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

/**
 * @file InstanceClass.hpp
 * @brief Declara a classe InstanceClass, que representa uma instância de um objeto em Java.
 */

/**
 * @class InstanceClass
 * @brief Representa um objeto instanciado a partir de uma classe Java dentro da JVM.
 * 
 * Herda de `Object`, armazenando os fields da instância e mantendo referência à `StaticClass`
 * que define o layout e comportamento da classe.
 */
class InstanceClass : public Object {

public:
    /**
     * @brief Construtor que inicializa a instância com a classe estática correspondente.
     * @param class_runtime Ponteiro para a definição da classe (`StaticClass*`).
     */
    InstanceClass(StaticClass* class_runtime);

    /**
     * @brief Destrutor da instância.
     */
    ~InstanceClass();

    /**
     * @brief Retorna o tipo do objeto (`INSTANCE_CLASS`).
     * @return Enum `ObjectType` representando o tipo da instância.
     */
    ObjectType object_type();

    /**
     * @brief Retorna o ponteiro para a `StaticClass` associada a esta instância.
     * @return Ponteiro para a `StaticClass` correspondente.
     */
    StaticClass* get_class_runtime();

    /**
     * @brief Insere ou atualiza o valor de um campo de instância.
     * 
     * @param value Valor a ser inserido.
     * @param field_name Nome do campo.
     */
    void insert_value(Value value, const string& field_name);

    /**
     * @brief Recupera o valor de um campo de instância.
     * 
     * @param field_name Nome do campo desejado.
     * @return Valor armazenado no campo.
     */
    Value get_value(const string& field_name);

    /**
     * @brief Verifica se um campo de instância existe.
     * 
     * @param field_name Nome do campo.
     * @return `true` se o campo existe, `false` caso contrário.
     */
    bool check_field(const string& field_name);

private:
    /**
     * @brief Ponteiro para a definição da classe estática (`StaticClass`).
     */
    StaticClass* class_runtime;

    /**
     * @brief Mapa que armazena os fields da instância (`nome → valor`).
     */
    map<string, Value> class_fields;
};

#endif // INSTANCE_CLASS_HPP
