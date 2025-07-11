#ifndef INSTANCE_CLASS_HPP
#define INSTANCE_CLASS_HPP

/**
 * @file InstanceClass.hpp
 * @brief Defines the InstanceClass for representing instances of Java classes in a JVM 8 environment.
 *
 * This class extends Object and serves as a runtime representation of an instance
 * of a Java class. It maintains a reference to its corresponding StaticClass (which
 * represents the class definition) and provides mechanisms for field storage and retrieval.
 */

#include "BaseType.hpp"
#include "Object.hpp"
#include "StaticClass.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

/**
 * @class InstanceClass
 * @brief Represents an instance of a Java class in the JVM runtime.
 *
 * This class provides storage for instance fields and links to its corresponding
 * StaticClass, which holds class-level metadata.
 */
class InstanceClass : public Object {

public:
    /**
     * @brief Constructs an InstanceClass object.
     * @param class_runtime Pointer to the StaticClass representing the class definition.
     */
    InstanceClass(StaticClass* class_runtime);

    /**
     * @brief Destructor for InstanceClass.
     */
    ~InstanceClass();

    /**
     * @brief Returns the object type of this instance.
     * @return The ObjectType representing the type of this instance.
     */
    ObjectType object_type();

    /**
     * @brief Retrieves the class runtime (StaticClass) associated with this instance.
     * @return Pointer to the StaticClass object.
     */
    StaticClass* get_class_runtime();

    /**
     * @brief Inserts a value into an instance field.
     * @param value The value to insert.
     * @param field_name The name of the field.
     *
     * This method allows dynamic storage of instance fields at runtime.
     */
    void insert_value_into_field(Value value, const string& field_name);

    /**
     * @brief Retrieves a value from an instance field.
     * @param field_name The name of the field.
     * @return The value stored in the specified field.
     *
     * If the field does not exist, behavior is undefined.
     */
    Value get_value_from_field(const string& field_name);

    /**
     * @brief Checks if a field exists in this instance.
     * @param field_name The name of the field.
     * @return True if the field exists, false otherwise.
     */
    bool field_exists(const string& field_name);

private:
    StaticClass* class_runtime; ///< Pointer to the class definition (StaticClass).

    map<string, Value> class_fields; ///< Storage for instance fields.
};

#endif // INSTANCE_CLASS_HPP
