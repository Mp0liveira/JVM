#include "StrObject.hpp"

// Construtor da classe StrObject
// Inicializa o atributo interno com a string fornecida
StrObject::StrObject(string s) :
    internal_str(s)
{
}

// Destrutor da classe StrObject
// Não é necessário fazer nada aqui porque o tipo std::string se limpa sozinho
StrObject::~StrObject()
{
}

// Retorna o tipo do objeto, no caso uma instância de String
// Isso permite à JVM saber que tipo de objeto está lidando
ObjectType StrObject::object_type()
{
    return ObjectType::STRING_INSTANCE;
}

// Retorna o valor atual da string armazenada no objeto
string StrObject::get_str()
{
    return internal_str;
}

// Atualiza o valor da string armazenada no objeto
void StrObject::set_str(string s)
{
    internal_str = s;
}
