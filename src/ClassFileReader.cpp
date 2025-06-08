#include "ClassFileUtils.hpp"

using namespace std;

ClassFileReader::ClassFileReader()
{
    is_little_endian = check_endian_type();
};

ClassFileReader::~ClassFileReader()
{
}

bool ClassFileReader::check_endian_type()
{
    int n = 1;
    return (*(char*)&n == 1);
}

ClassFile* ClassFileReader::read_class_file(FILE* fp)
{
    ClassFile* class_file = new ClassFile();
    set_magic(fp, class_file);
    if (check_magic_valid(class_file) == false) {
        cerr << "Invalid file format!\nThe expected Magic Signature \"0xCAFEBABE\" for the .class file was not found.\n";
        delete class_file;
        exit(3);
    }
    set_version(fp, class_file);
    if (is_version_valid(class_file, 45) == false) {
        double friendlyVersion = ClassFileUtils::non_suported_version(class_file);
        if (friendlyVersion != 0) {
            cerr << "Versions higher than Java SE 1.8 (52) are not supported. The class file version is Java SE" << friendlyVersion << ".\n";
            delete class_file;
            exit(4);
        }
    }
    set_constant_pool_size(fp, class_file);
    set_constant_pool(fp, class_file);
    set_access_flags(fp, class_file);
    set_this_class(fp, class_file);
    set_super_class(fp, class_file);
    set_interfaces_count(fp, class_file);
    set_interfaces(fp, class_file);
    set_fields_count(fp, class_file);
    set_fields(fp, class_file);
    set_methods_count(fp, class_file);
    set_methods(fp, class_file);
    set_attributes_count(fp, class_file);
    set_attributes(fp, class_file);
    return class_file;
}

u1 ClassFileReader::read_u1(FILE* fp)
{
    u1 result = 0;
    fread(&result, sizeof(u1), 1, fp);
    return result;
}

u2 ClassFileReader::read_u2(FILE* fp)
{
    u2 result = 0;
    if (is_little_endian) {
        for (int i = 0; i < 2; i++) {
            result += read_u1(fp) << (8 - 8 * i);
        }
    } else {
        fread(&result, sizeof(u2), 1, fp);
    }
    return result;
}

u4 ClassFileReader::read_u4(FILE* fp)
{
    u4 result = 0;
    if (is_little_endian) {
        for (int i = 0; i < 4; i++) {
            result += read_u1(fp) << (24 - 8 * i);
        }
    } else {
        fread(&result, sizeof(u4), 1, fp);
    }
    return result;
}

void ClassFileReader::set_magic(FILE* fp, ClassFile* class_file)
{
    class_file->magic = read_u4(fp);
}

bool ClassFileReader::check_magic_valid(ClassFile* class_file)
{
    return class_file->magic == 0xCAFEBABE ? true : false;
}

void ClassFileReader::set_version(FILE* fp, ClassFile* class_file)
{
    class_file->minor_version = read_u2(fp);
    class_file->major_version = read_u2(fp);
}

bool ClassFileReader::is_version_valid(ClassFile* class_file, uint16_t major)
{
    return class_file->major_version <= major;
}

void ClassFileReader::set_constant_pool_size(FILE* fp, ClassFile* class_file)
{
    class_file->constant_pool_count = read_u2(fp);
}

void ClassFileReader::set_constant_pool(FILE* fp, ClassFile* class_file) {
    u2 pool_size = class_file->constant_pool_count - 1;
    class_file->constant_pool = (ConstantPoolInfo*)malloc(sizeof(ConstantPoolInfo) * pool_size);
    ConstantPoolInfo* current_entry = class_file->constant_pool;

    for (u2 i = 0; i < pool_size; i++) {
        u1 tag = read_u1(fp);
        current_entry->tag = tag;

        switch (tag) {
        case ConstClass:
            current_entry->info.class_info = get_const_class_info(fp);
            break;
        case ConstFieldRef:
            current_entry->info.field_ref_info = get_const_field_ref_info(fp);
            break;
        case ConstMethodRef:
            current_entry->info.method_ref_info = get_const_method_ref_info(fp);
            break;
        case ConstInterfaceMethodRef:
            current_entry->info.interface_method_ref_info = get_const_interface_method_ref_info(fp);
            break;
        case ConstStr:
            current_entry->info.str_info = get_const_str_info(fp);
            break;
        case ConstInt:
            current_entry->info.int_info = get_const_int_info(fp);
            break;
        case ConstFloat:
            current_entry->info.float_info = get_const_float_info(fp);
            break;
        case ConstLong:
            current_entry->info.long_info = get_const_long_info(fp);
            (++current_entry)->tag = ConstNull; 
            i++;
            break;
        case ConstDouble:
            current_entry->info.double_info = get_const_double_info(fp);
            (++current_entry)->tag = ConstNull; 
            i++;
            break;
        case ConstNameType:
            current_entry->info.name_type_info = get_const_name_type_info(fp);
            break;
        case ConstUtf8:
            current_entry->info.utf8_info = get_const_utf8_info(fp);
            break;
        default:
            cerr << "The .class file has an invalid tag in its constant pool.\n";
            exit(5);
        }

        current_entry++;
    }
}

ConstClassInfo ClassFileReader::get_const_class_info(FILE* fp)
{
    ConstClassInfo result;
    result.name_index = read_u2(fp);
    return result;
}

ConstFieldRefInfo ClassFileReader::get_const_field_ref_info(FILE* fp)
{
    ConstFieldRefInfo result;
    result.class_index = read_u2(fp);
    result.name_and_type_index = read_u2(fp);
    return result;
}

ConstMethodRefInfo ClassFileReader::get_const_method_ref_info(FILE* fp)
{
    ConstMethodRefInfo result;
    result.class_index = read_u2(fp);
    result.name_and_type_index = read_u2(fp);
    return result;
}

ConstInterfaceMethodRefInfo ClassFileReader::get_const_interface_method_ref_info(FILE* fp)
{
    ConstInterfaceMethodRefInfo result;
    result.class_index = read_u2(fp);
    result.name_and_type_index = read_u2(fp);
    return result;
}

ConstStrInfo ClassFileReader::get_const_str_info(FILE* fp)
{
    ConstStrInfo result;
    result.string_index = read_u2(fp);
    return result;
}

ConstIntInfo ClassFileReader::get_const_int_info(FILE* fp)
{
    ConstIntInfo result;
    result.bytes = read_u4(fp);
    return result;
}

ConstFloatInfo ClassFileReader::get_const_float_info(FILE* fp)
{
    ConstFloatInfo result;
    result.bytes = read_u4(fp);
    return result;
}

ConstLongInfo ClassFileReader::get_const_long_info(FILE* fp)
{
    ConstLongInfo result;
    result.high_bytes = read_u4(fp);
    result.low_bytes = read_u4(fp);
    return result;
}

ConstDoubleInfo ClassFileReader::get_const_double_info(FILE* fp)
{
    ConstDoubleInfo result;
    result.high_bytes = read_u4(fp);
    result.low_bytes = read_u4(fp);
    return result;
}

ConstNameTypeInfo ClassFileReader::get_const_name_type_info(FILE* fp)
{
    ConstNameTypeInfo result;
    result.name_index = read_u2(fp);
    result.descriptor_index = read_u2(fp);
    return result;
}

ConstUtf8Info ClassFileReader::get_const_utf8_info(FILE* fp)
{
    ConstUtf8Info result;
    result.length = read_u2(fp);
    result.bytes = (u1*)malloc(sizeof(u1) * result.length);
    for (u2 i = 0; i < result.length; i++) {
        result.bytes[i] = read_u1(fp);
    }
    return result;
}

void ClassFileReader::set_access_flags(FILE* fp, ClassFile* class_file)
{
    class_file->access_flags = read_u2(fp);
}

void ClassFileReader::set_this_class(FILE* fp, ClassFile* class_file)
{
    class_file->this_class = read_u2(fp);
}

void ClassFileReader::set_super_class(FILE* fp, ClassFile* class_file)
{
    class_file->super_class = read_u2(fp);
}

void ClassFileReader::set_interfaces_count(FILE* fp, ClassFile* class_file)
{
    class_file->interfaces_count = read_u2(fp);
}

void ClassFileReader::set_interfaces(FILE* fp, ClassFile* class_file)
{
    class_file->interfaces = (u2*)malloc(sizeof(u2) * class_file->interfaces_count);
    for (u2 i = 0; i < class_file->interfaces_count; i++) {
        class_file->interfaces[i] = read_u2(fp);
    }
}

void ClassFileReader::set_fields_count(FILE* fp, ClassFile* class_file)
{
    class_file->fields_count = read_u2(fp);
}

void ClassFileReader::set_fields(FILE* fp, ClassFile* class_file)
{
    class_file->fields = (FieldInfo*)malloc(sizeof(FieldInfo) * class_file->fields_count);
    for (u2 i = 0; i < class_file->fields_count; i++) {
        FieldInfo field;
        field.access_flags = read_u2(fp);
        field.name_index = read_u2(fp);
        field.descriptor_index = read_u2(fp);
        field.attributes_count = read_u2(fp);
        field.attributes = (AttributeInfo*)malloc(sizeof(AttributeInfo) * field.attributes_count);
        for (u2 j = 0; j < field.attributes_count; j++) {
            field.attributes[j] = get_attribute_info(fp, class_file);
        }
        class_file->fields[i] = field;
    }
}

ConstUtf8Info ClassFileReader::get_utf8_from_constant_pool(u2 index, ClassFile* class_file)
{
    ConstantPoolInfo constant = class_file->constant_pool[index - 1];
    assert(constant.tag == ConstUtf8);
    return constant.info.utf8_info;
}

ConstValueAttribute ClassFileReader::get_attribute_constant_value(FILE* fp)
{
    ConstValueAttribute result;
    result.const_value_index = read_u2(fp);
    return result;
}

ExceptionTable ClassFileReader::get_exception_table(FILE* fp)
{
    ExceptionTable result;
    result.start_pc = read_u2(fp);
    result.end_pc = read_u2(fp);
    result.handler_pc = read_u2(fp);
    result.catch_type = read_u2(fp);
    return result;
}

CodeAttribute ClassFileReader::get_attribute_code(FILE* fp, ClassFile* class_file)
{
    CodeAttribute result;
    result.max_stack = read_u2(fp);
    result.max_locals = read_u2(fp);
    result.code_length = read_u4(fp);
    result.code = (u1*)malloc(sizeof(u1) * result.code_length);
    for (u4 i = 0; i < result.code_length; i++) {
        result.code[i] = read_u1(fp);
    }
    result.exception_table_length = read_u2(fp);
    result.exception_table = (ExceptionTable*)malloc(sizeof(ExceptionTable) * result.exception_table_length);
    for (u2 i = 0; i < result.exception_table_length; i++) {
        result.exception_table[i] = get_exception_table(fp);
    }
    result.attributes_count = read_u2(fp);
    result.attributes = (AttributeInfo*)malloc(sizeof(AttributeInfo) * result.attributes_count);
    for (u2 i = 0; i < result.attributes_count; i++) {
        result.attributes[i] = get_attribute_info(fp, class_file);
    }
    
    for (u2 i = 0; i < result.attributes_count; i++) {
    }

    return result;
}


ExceptionsAttribute ClassFileReader::get_attribute_exceptions(FILE* fp)
{
    ExceptionsAttribute result;
    result.number_of_exceptions = read_u2(fp);
    result.exception_index_table = (u2*)malloc(sizeof(u2) * result.number_of_exceptions);
    for (u2 i = 0; i < result.number_of_exceptions; i++) {
        result.exception_index_table[i] = read_u2(fp);
    }
    return result;
}

Class ClassFileReader::get_class(FILE* fp)
{
    Class result;
    result.inner_class_info_index = read_u2(fp);
    result.outer_class_info_index = read_u2(fp);
    result.inner_name_index = read_u2(fp);
    result.inner_class_access_flags = read_u2(fp);
    return result;
}

InnerClassesAttribute ClassFileReader::get_attribute_inner_classes(FILE* fp)
{
    InnerClassesAttribute result;
    result.number_of_classes = read_u2(fp);
    result.classes = (Class*)malloc(sizeof(Class) * result.number_of_classes);
    for (u2 i = 0; i < result.number_of_classes; i++) {
        result.classes[i] = get_class(fp);
    }
    return result;
}

SyntheticAttribute ClassFileReader::get_attribute_synthetic()
{
    SyntheticAttribute result;
    return result;
}

SourceFileAttribute ClassFileReader::get_attribute_source_file(FILE* fp)
{
    SourceFileAttribute result;
    result.sourcefile_index = read_u2(fp);
    return result;
}

LineNumberTable ClassFileReader::get_line_number_table(FILE* fp)
{
    LineNumberTable result;
    result.start_pc = read_u2(fp);
    result.line_number = read_u2(fp);
    return result;
}

LineNumberTableAttribute ClassFileReader::get_attribute_line_number_table(FILE* fp)
{
    LineNumberTableAttribute result;
    result.line_number_table_length = read_u2(fp);
    result.line_number_table = (LineNumberTable*)malloc(sizeof(LineNumberTable) * result.line_number_table_length);
    for (u2 i = 0; i < result.line_number_table_length; i++) {
        result.line_number_table[i] = get_line_number_table(fp);
    }
    return result;
}

LocalVariableTable ClassFileReader::get_local_variable_table(FILE* fp)
{
    LocalVariableTable result;
    result.start_pc = read_u2(fp);
    result.length = read_u2(fp);
    result.name_index = read_u2(fp);
    result.descriptor_index = read_u2(fp);
    result.index = read_u2(fp);
    return result;
}

LocalVariableTableAttribute ClassFileReader::get_attribute_local_variable(FILE* fp)
{
    LocalVariableTableAttribute result;
    result.local_variable_table_length = read_u2(fp);
    result.local_variable_table = (LocalVariableTable*)malloc(sizeof(LocalVariableTable) * result.local_variable_table_length);
    for (u2 i = 0; i < result.local_variable_table_length; i++) {
        result.local_variable_table[i] = get_local_variable_table(fp);
    }
    return result;
}

DeprecatedAttribute ClassFileReader::get_attribute_deprecated()
{
    DeprecatedAttribute result;
    return result;
}

AttributeInfo ClassFileReader::get_attribute_info(FILE* fp, ClassFile* class_file)
{
    AttributeInfo result;
    result.attribute_name_index = read_u2(fp);
    result.attribute_length = read_u4(fp);
    ConstUtf8Info name = get_utf8_from_constant_pool(result.attribute_name_index, class_file);
    if (ClassFileUtils::compare_utf8_str(name, "ConstantValue")) {
        result.info.const_value_info = get_attribute_constant_value(fp);
    } else if (ClassFileUtils::compare_utf8_str(name, "Code")) {
        result.info.code_info = get_attribute_code(fp, class_file);
    } else if (ClassFileUtils::compare_utf8_str(name, "Exceptions")) {
        result.info.exceptions_info = get_attribute_exceptions(fp);
    } else if (ClassFileUtils::compare_utf8_str(name, "InnerClasses")) {
        result.info.inner_classes_info = get_attribute_inner_classes(fp);
    } else if (ClassFileUtils::compare_utf8_str(name, "Synthetic")) {
        result.info.synthetic_info = get_attribute_synthetic();
    } else if (ClassFileUtils::compare_utf8_str(name, "SourceFile")) {
        result.info.source_file_info = get_attribute_source_file(fp);
    } else if (ClassFileUtils::compare_utf8_str(name, "LineNumberTable")) {
        result.info.line_number_table_info = get_attribute_line_number_table(fp);
    } else if (ClassFileUtils::compare_utf8_str(name, "LocalVariableTable")) {
        result.info.local_variable_table_info = get_attribute_local_variable(fp);
    } else if (ClassFileUtils::compare_utf8_str(name, "Deprecated")) {
        result.info.deprecated_info = get_attribute_deprecated();
    } else if (ClassFileUtils::compare_utf8_str(name, "StackMapTable")) {
        for (int i = 0; i < (signed)result.attribute_length; i++) {
            read_u1(fp);
        }
    } else {
        cerr << "The .class file has an invalid attribute." << endl;
        exit(6);
    }
    return result;
}

void ClassFileReader::set_methods_count(FILE* fp, ClassFile* class_file)
{
    class_file->methods_count = read_u2(fp);
}

void ClassFileReader::set_methods(FILE* fp, ClassFile* class_file)
{
    class_file->methods = (MethodInfo*)malloc(sizeof(MethodInfo) * class_file->methods_count);
    for (u2 i = 0; i < class_file->methods_count; i++) {
        MethodInfo* method = &class_file->methods[i];
        method->access_flags = read_u2(fp);
        method->name_index = read_u2(fp);
        method->descriptor_index = read_u2(fp);
        method->attributes_count = read_u2(fp);
        method->attributes = (AttributeInfo*)malloc(sizeof(AttributeInfo) * method->attributes_count);
        for (u2 j = 0; j < method->attributes_count; j++) {
            method->attributes[j] = get_attribute_info(fp, class_file);
        }
    }
}

void ClassFileReader::set_attributes_count(FILE* fp, ClassFile* class_file)
{
    class_file->attributes_count = read_u2(fp);
}

void ClassFileReader::set_attributes(FILE* fp, ClassFile* class_file)
{
    class_file->attributes = (AttributeInfo*)malloc(sizeof(AttributeInfo) * class_file->attributes_count);
    for (u2 i = 0; i < class_file->attributes_count; i++) {
        class_file->attributes[i] = get_attribute_info(fp, class_file);
    }
}
