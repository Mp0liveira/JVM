#include "Array.hpp"

// Construtor que define o tipo dos elementos que o array irá armazenar
Array::Array(ValueType type)
    : array_type{type}
{
}

// Destrutor padrão (sem ação específica neste caso)
Array::~Array()
{
}

// Retorna o tipo do objeto, que neste caso é ARRAY
ObjectType Array::object_type()
{
    return ARRAY;
}

// Retorna o tipo dos valores armazenados no array
ValueType Array::array_content_type()
{
    return array_type;
}

// Adiciona um novo valor ao final do array
void Array::push_value(Value value)
{
    array_elements.push_back(value);
}

// Remove o valor no índice especificado e o retorna
Value Array::remove_at(uint32_t index)
{
    // Verifica se o índice está fora dos limites
    if (index >= array_elements.size()) {
        Value invalid_return = Value{ INT, INT, {.int_value = -1} };
        cerr << "Array::remove_at - Índice inválido\n";
        return invalid_return;
    }

    Value temp = array_elements[index];
    array_elements.erase(array_elements.begin() + index);
    return temp;
}

// Remove o último elemento do array e o retorna
Value Array::remove_last()
{
    Value temp = array_elements.back();
    array_elements.pop_back();
    return temp;
}

// Remove o primeiro elemento do array e o retorna
Value Array::remove_first()
{
    Value temp = array_elements.front();
    array_elements.erase(array_elements.begin());
    return temp;
}

// Retorna o número de elementos no array
uint32_t Array::get_size()
{
    return array_elements.size();
}

// Retorna o valor armazenado no índice especificado
Value Array::get_value(uint32_t index)
{
    if (index >= array_elements.size()) {
        Value invalid_return = Value{ INT, INT, {.int_value = -1} };
        cerr << "Array::get_value - Índice inválido\n";
        return invalid_return;
    }
    return array_elements[index];
}

// Altera o valor armazenado em um determinado índice
void Array::change_value(uint32_t index, Value value)
{
    if (index >= array_elements.size()) {
        cerr << "Array::change_value - Índice inválido\n";
        return;
    }
    array_elements[index] = value;
}
