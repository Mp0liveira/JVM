#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "BaseType.hpp" 
#include "Object.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @file Array.hpp
 * @brief Representa um objeto de array na JVM.
 *
 */
 
 /**
 * @class
 * @brief 
 * Esta classe modela o comportamento de arrays em Java, armazenando uma sequência
 * de valores homogêneos (todos do mesmo tipo primitivo ou referência).
 * Herda de Object e pode armazenar qualquer tipo definido em ValueType.
 */
class Array : public Object {

public:
    /**
     * @brief Construtor da classe Array.
     * @param type Tipo dos elementos que o array irá armazenar.
     */
    Array(ValueType type);

    /**
     * @brief Destrutor da classe Array.
     */
    ~Array();

    /**
     * @brief Retorna o tipo do objeto (ARRAY).
     * @return Tipo do objeto (ObjectType::ARRAY).
     */
    ObjectType object_type();

    /**
     * @brief Retorna o tipo dos valores armazenados no array.
     * @return Tipo dos elementos (ValueType).
     */
    ValueType array_content_type();

    /**
     * @brief Adiciona um valor ao final do array.
     * @param value Valor a ser adicionado.
     */
    void push_value(Value value);

    /**
     * @brief Remove e retorna o valor de uma posição específica do array.
     * @param index Índice do elemento a ser removido.
     * @return Valor removido.
     */
    Value remove_at(uint32_t index);

    /**
     * @brief Remove e retorna o último valor do array.
     * @return Valor removido do final.
     */
    Value remove_last();

    /**
     * @brief Remove e retorna o primeiro valor do array.
     * @return Valor removido do início.
     */
    Value remove_first();

    /**
     * @brief Retorna o tamanho atual do array.
     * @return Quantidade de elementos no array.
     */
    uint32_t get_size();

    /**
     * @brief Retorna o valor armazenado em uma posição específica.
     * @param index Índice do valor desejado.
     * @return Valor armazenado na posição.
     */
    Value get_value(uint32_t index);

    /**
     * @brief Altera o valor armazenado em uma posição específica.
     * @param index Índice do valor a ser alterado.
     * @param value Novo valor a ser armazenado.
     */
    void change_value(uint32_t index, Value value);

private:
    ValueType array_type;            ///< Tipo dos valores armazenados.
    vector<Value> array_elements;    ///< Vetor com os elementos do array.
};

#endif
