#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "BaseType.hpp" 
#include "Object.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// Classe que representa um objeto de array da JVM
class Array : public Object {

public:
    // Construtor: define o tipo de valor que o array irá armazenar
    Array(ValueType type);

    // Destrutor
    ~Array();

    // Retorna o tipo do objeto (no caso, ARRAY)
    ObjectType object_type();

    // Retorna o tipo dos dados armazenados no array
    ValueType array_content_type();

    // Insere um valor no final do array
    void push_value(Value value);

    // Remove o valor em uma posição específica e o retorna
    Value remove_at(uint32_t index);

    // Remove o último valor do array e o retorna
    Value remove_last();

    // Remove o primeiro valor do array e o retorna
    Value remove_first();

    // Retorna o tamanho atual do array
    uint32_t get_size();

    // Retorna o valor armazenado em uma posição específica
    Value get_value(uint32_t index);

    // Altera o valor em uma posição específica
    void change_value(uint32_t index, Value value);

private:
    ValueType array_type;            // Tipo dos valores armazenados
    vector<Value> array_elements;   // Vetor dinâmico com os elementos do array
};

#endif // ARRAY_HPP
