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

class InstanceClass : public Object {

public:

    InstanceClass(StaticClass* class_runtime);

    ~InstanceClass();

    // O objecttype que representa a instância
    ObjectType object_type();

    // Retorna static class associada a está instância
    StaticClass* get_class_runtime();

    // Inserve um valor em um instance field
    void insert_value_into_field(Value value, const string& field_name);

    // Retorna o valor de um field
    Value get_value_from_field(const string& field_name);

    // Verifica se o field existe
    bool field_exists(const string& field_name);

private:
    StaticClass* class_runtime; ///< Pointer to the class definition (StaticClass).

    map<string, Value> class_fields; ///< Storage for instance fields.
};

#endif // INSTANCE_CLASS_HPP
