#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "BaseType.hpp"

/**
 * @file Object.hpp
 * @brief Define a classe base abstrata `Object`, usada para representar qualquer objeto manipulável pela JVM.
 */

/**
 * @class Object
 * @brief Classe base abstrata para todos os objetos na JVM.
 * 
 * Toda classe que representa um objeto instanciável (como strings, instâncias de classe, arrays, etc.)
 * deve herdar desta classe e implementar o método `object_type()`.
 */
class Object {
public:
    /**
     * @brief Retorna o tipo do objeto.
     * 
     * Método puramente virtual que deve ser implementado por todas as subclasses.
     * 
     * @return ObjectType Enumerador que representa o tipo do objeto.
     */
    virtual ObjectType object_type() = 0;

    // Virtual destructor pode ser adicionado se houver gerenciamento de memória complexo futuramente
    // virtual ~Object() = default;
};

#endif // OBJECT_HPP
