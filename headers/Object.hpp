#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "BaseType.hpp"

class Object {
public:
    // Método virtual
    virtual ObjectType object_type() = 0;
};

#endif // OBJECT_HPP
