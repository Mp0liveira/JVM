#ifndef STR_OBJECT_HPP
#define STR_OBJECT_HPP

#include "Object.hpp"
#include <cstdlib>
#include <string>

using namespace std;

// Classe que representa um objeto String da linguagem Java dentro da JVM
// Essa classe herda da classe base Object e modela strings imutáveis
class StrObject : public Object {

public:
    // Construtor que inicializa o objeto com uma string (opcional)
    // Caso nenhuma string seja passada, o valor padrão é uma string vazia
    StrObject(string s = "");

    // Destrutor (não faz nada especial, pois a string será limpa automaticamente)
    ~StrObject();

    // Retorna o tipo do objeto (no caso, indica que é uma string)
    // Útil para fazer verificações de tipo na JVM
    ObjectType object_type();

    // Retorna o conteúdo atual da string armazenada
    string get_str();

    // Define ou atualiza o valor da string armazenada
    void set_str(string s);

private:
    // Armazena internamente o valor da string (conteúdo do objeto Java String)
    string internal_str;
};

#endif
