#ifndef STR_OBJECT_HPP
#define STR_OBJECT_HPP

#include "Object.hpp"
#include <cstdlib>
#include <string>

using namespace std;

/**
 * @file StrObject.hpp
 * @brief Declara a classe StrObject que representa um objeto `String` da linguagem Java.
 */

/**
 * @class StrObject
 * @brief Representa um objeto do tipo `String` da linguagem Java dentro da JVM.
 * 
 * Esta classe herda de `Object` e modela o comportamento imutável das strings em Java.
 */
class StrObject : public Object {
public:
    /**
     * @brief Construtor que inicializa o objeto com uma string opcional.
     * 
     * @param s Valor inicial da string (padrão: string vazia).
     */
    StrObject(string s = "");

    /**
     * @brief Destrutor da classe.
     * 
     * O destrutor não realiza nenhuma liberação especial, pois `std::string` lida com seus próprios recursos.
     */
    ~StrObject();

    /**
     * @brief Retorna o tipo do objeto.
     * 
     * Este método identifica o objeto como sendo do tipo string, o que pode ser útil para verificações dinâmicas na JVM.
     * 
     * @return ObjectType Enum que representa o tipo do objeto.
     */
    ObjectType object_type();

    /**
     * @brief Retorna o conteúdo atual da string armazenada.
     * @return string A string interna do objeto.
     */
    string get_str();

    /**
     * @brief Define ou atualiza o valor da string armazenada.
     * 
     * @param s Novo valor para a string.
     */
    void set_str(string s);

private:
    /**
     * @brief Armazena internamente o conteúdo do objeto Java String.
     */
    string internal_str;
};

#endif // STR_OBJECT_HPP
