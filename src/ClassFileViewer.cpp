#include "ClassFileViewer.hpp"
#include "ClassFileUtils.hpp"

using namespace std;

FILE* out;

void write_class_file(ClassFile* class_file, FILE* output)
{
    out = output;
    fprintf(out, "General Information\n{\n");
    write_general_info(class_file);
    fprintf(out, "}\n\n");
    fprintf(out, "Constant Pool (Member count: %d)\n{\n", class_file->constant_pool_count);
    write_constant_pool(class_file);
    fprintf(out, "}\n\n");
    fprintf(out, "Interfaces (Member count: %d) \n{\n", class_file->interfaces_count);
    write_interfaces(class_file);
    fprintf(out, "}\n\n");
    fprintf(out, "Fields (Member count: %d)\n{\n", class_file->fields_count);
    write_fields(class_file);
    fprintf(out, "}\n\n");
    fprintf(out, "Methods (Member count: %d)\n{\n", class_file->methods_count);
    write_methods(class_file);
    fprintf(out, "}\n\n");
    fprintf(out, "Attributes (Member count: %d)\n{\n", class_file->attributes_count);
    write_attributes(class_file);
    fprintf(out, "}\n\n");
}

void write_general_info(ClassFile* class_file)
{
    fprintf(out, "\t Minor Version: \t\t %hu\n", class_file->minor_version);
    fprintf(out, "\t Major Version: \t\t %hu [%.1f]\n", class_file->major_version, ClassFileUtils::return_version(class_file));
    fprintf(out, "\t Constant Pool count: \t\t %hu\n", class_file->constant_pool_count);
    fprintf(out, "\t Access Flags: \t\t\t 0x%.4X [%s]\n", class_file->access_flags, get_access_flags(class_file->access_flags));
    fprintf(out, "\t This Class: \t\t\t ConstantPoolInfo #%hu <%s>\n", class_file->this_class,
        get_formatted_constant(class_file->constant_pool, class_file->this_class));
    if (class_file->super_class == 0) {
        fprintf(out, "\t Super class: \t\t\t none\n");
    } else {
        fprintf(out, "\t Super class: \t\t\t ConstantPoolInfo #%hu <%s>\n", class_file->super_class,
            get_formatted_constant(class_file->constant_pool, class_file->super_class));
    }
    fprintf(out, "\t Interfaces count: \t\t %hu\n", class_file->interfaces_count);
    fprintf(out, "\t Fields count: \t\t\t %hu\n", class_file->fields_count);
    fprintf(out, "\t Methods pool count: \t\t %hu\n", class_file->methods_count);
    fprintf(out, "\t Attributes pool count: \t %hu\n", class_file->attributes_count);
}

void write_constant_pool(ClassFile* class_file)
{
    ConstantPoolInfo* constant_pool = class_file->constant_pool;
    for (int i = 0; i < class_file->constant_pool_count - 1; i++) {
        ConstantPoolInfo element = constant_pool[i];
        if (element.tag == ConstClass) {
            ConstClassInfo class_info = element.info.class_info;
            fprintf(out, "\t [%d] ConstClassInfo\n", i + 1);
            fprintf(out, "\t\t Class name: \t\t\t ConstantPoolInfo #%hu <%s>\n", class_info.name_index,
                get_formatted_constant(constant_pool, class_info.name_index));
        } else if (element.tag == ConstFieldRef) {
            ConstFieldRefInfo field_ref_info = element.info.field_ref_info;
            fprintf(out, "\t [%d] ConstFieldRefInfo\n", i + 1);
            fprintf(out, "\t\t Class name: \t\t\t ConstantPoolInfo #%hu <%s>\n ", field_ref_info.class_index,
                get_formatted_constant(constant_pool, field_ref_info.class_index));
            fprintf(out, "\t\t Name and type: \t\t ConstantPoolInfo #%hu <%s>\n", field_ref_info.name_and_type_index,
                get_formatted_constant(constant_pool, field_ref_info.name_and_type_index));
        } else if (element.tag == ConstMethodRef) {
            ConstMethodRefInfo method_info = element.info.method_ref_info;
            fprintf(out, "\t [%d] ConstMethodRefInfo\n", i + 1);
            fprintf(out, "\t\t Class name: \t\t\t ConstantPoolInfo #%hu <%s>\n ", method_info.class_index,
                get_formatted_constant(constant_pool, method_info.class_index));
            fprintf(out, "\t\t Name and type: \t\t ConstantPoolInfo #%hu <%s>\n", method_info.name_and_type_index,
                get_formatted_constant(constant_pool, method_info.name_and_type_index));
        } else if (element.tag == ConstInterfaceMethodRef) {
            ConstInterfaceMethodRefInfo interface_method_info = element.info.interface_method_ref_info;
            fprintf(out, "\t [%d] ConstInterfaceMethodRefInfo\n", i + 1);
            fprintf(out, "\t\t Class name: \t\t\t ConstantPoolInfo #%hu <%s>\n ", interface_method_info.class_index,
                get_formatted_constant(constant_pool, interface_method_info.class_index));
            fprintf(out, "\t\t Name and type: \t\t ConstantPoolInfo #%hu <%s>\n", interface_method_info.name_and_type_index,
                get_formatted_constant(constant_pool, interface_method_info.name_and_type_index));
        } else if (element.tag == ConstStr) {
            ConstStrInfo str_info = element.info.str_info;
            fprintf(out, "\t [%d] ConstStrInfo\n", i + 1);
            fprintf(out, "\t String: \t\t\t\t ConstantPoolInfo #%hu <%s>\n", str_info.string_index,
                get_formatted_constant(constant_pool, str_info.string_index));
        } else if (element.tag == ConstInt) {
            ConstIntInfo int_info = element.info.int_info;
            fprintf(out, "\t [%d] ConstIntInfo\n", i + 1);
            fprintf(out, "\t Bytes: \t\t\t\t 0x%.8X\n", int_info.bytes);
            fprintf(out, "\t Integer: \t\t\t\t %s\n", get_formatted_constant(constant_pool, i + 1));
        } else if (element.tag == ConstFloat) {
            ConstFloatInfo float_info = element.info.float_info;
            fprintf(out, "\t [%d] ConstFloatInfo\n", i + 1);
            fprintf(out, "\t\t Bytes: \t\t\t 0x%.8X\n", float_info.bytes);
            fprintf(out, "\t\t Float: \t\t\t %s\n", get_formatted_constant(constant_pool, i + 1));
        } else if (element.tag == ConstLong) {
            ConstLongInfo long_info = element.info.long_info;
            fprintf(out, "\t [%d] ConstLongInfo\n", i + 1);
            fprintf(out, "\t\t High Bytes: \t\t\t 0x%.8X\n", long_info.high_bytes);
            fprintf(out, "\t\t Low Bytes: \t\t\t 0x%.8X\n", long_info.low_bytes);
            fprintf(out, "\t\t Long: \t\t\t\t %s\n", get_formatted_constant(constant_pool, i + 1));
        } else if (element.tag == ConstDouble) {
            ConstDoubleInfo double_info = element.info.double_info;
            fprintf(out, "\t [%d] ConstDoubleInfo\n", i + 1);
            fprintf(out, "\t\t High Bytes: \t\t\t 0x%.8X\n", double_info.high_bytes);
            fprintf(out, "\t\t Low Bytes: \t\t\t 0x%.8X\n", double_info.low_bytes);
            fprintf(out, "\t\t Double: \t\t\t %s\n", get_formatted_constant(constant_pool, i + 1));
        } else if (element.tag == ConstNameType) {
            ConstNameTypeInfo name_type_info = element.info.name_type_info;
            fprintf(out, "\t [%d] ConstNameTypeInfo\n", i + 1);
            fprintf(out, "\t\t Name: \t\t\t\t ConstantPoolInfo #%hu <%s>\n", name_type_info.name_index,
                get_formatted_constant(constant_pool, name_type_info.name_index));
            fprintf(out, "\t\t Descriptor: \t\t\t ConstantPoolInfo #%hu <%s>\n", name_type_info.descriptor_index,
                get_formatted_constant(constant_pool, name_type_info.descriptor_index));
        } else if (element.tag == ConstUtf8) {
            ConstUtf8Info utf8_info = element.info.utf8_info;
            const char* str = get_formatted_constant(constant_pool, i + 1);
            fprintf(out, "\t [%d] ConstUtf8Info\n", i + 1);
            fprintf(out, "\t\t Length of byte array: \t\t %hu\n", utf8_info.length);
            fprintf(out, "\t\t Length of string: \t\t %llu\n", strlen(str));
            fprintf(out, "\t\t String: \t\t\t %s\n", str);
        } else if (element.tag == ConstNull) {
            fprintf(out, "\t [%d] (large numeric continued)\n", i + 1);
        } else {
            cerr << "The .class file has an invalid tag in its constant pool." << endl;
            exit(5);
        }
        fprintf(out, "\n");
    }
}

void write_interfaces(ClassFile* class_file)
{
    for (int i = 0; i < class_file->interfaces_count; i++) {
        const char* class_name = get_formatted_constant(class_file->constant_pool, class_file->interfaces[i]);
        fprintf(out, "\t Interface %d \n", i);
        fprintf(out, "\t\t Interface: \t\t ConstantPoolInfo #%hu <%s>\n ", class_file->interfaces[i], class_name);
    }
}

void write_fields(ClassFile* class_file)
{
    for (u2 i = 0; i < class_file->fields_count; i++) {
        FieldInfo field = class_file->fields[i];
        fprintf(out, "\t[%hu] %s\n", i, get_formatted_constant(class_file->constant_pool, field.name_index));
        fprintf(out, "\t{\n");
        fprintf(out, "\t\tName: \t\t\t ConstantPoolInfo #%hu <%s>\n ", field.name_index,
            get_formatted_constant(class_file->constant_pool, field.name_index));
        fprintf(out, "\t\tDescriptor: \t ConstantPoolInfo #%hu <%s>\n ", field.descriptor_index,
            get_formatted_constant(class_file->constant_pool, field.descriptor_index));
        fprintf(out, "\t\tAccess flags: \t %x [%s]\n", field.access_flags, get_access_flags(field.access_flags));
        fprintf(out, "\t\tAttributes:\n");
        for (u2 j = 0; j < field.attributes_count; j++) {
            write_attribute_info(field.attributes[j], j, class_file->constant_pool, 3);
        }
        fprintf(out, "\t}\n");
    }
}

void write_methods(ClassFile* class_file)
{
    for (int i = 0; i < class_file->methods_count; i++) {
        MethodInfo method = class_file->methods[i];
        const char* methodName = get_formatted_constant(class_file->constant_pool, method.name_index);
        const char* descriptor = get_formatted_constant(class_file->constant_pool, method.descriptor_index);
        const char* access_flags = get_access_flags(method.access_flags);
        fprintf(out, "\t[%d] %s\n", i, methodName);
        fprintf(out, "\t{\n");
        fprintf(out, "\t\tName: \t\t ConstantPoolInfo #%d <%s>\n", method.name_index, methodName);
        fprintf(out, "\t\tDescriptor: \t ConstantPoolInfo #%d <%s>\n", method.descriptor_index, descriptor);
        fprintf(out, "\t\tAccess flags: \t 0x%.4X [%s]\n", method.access_flags, access_flags);
        fprintf(out, "\t\tAttributes:\n");
        for (int j = 0; j < method.attributes_count; j++) {
            write_attribute_info(method.attributes[j], j, class_file->constant_pool, 3);
        }
        fprintf(out, "\t}\n");
    }
}

void write_attributes(ClassFile* class_file)
{
    for (uint16_t i = 0; i < class_file->attributes_count; i++) {
        write_attribute_info(class_file->attributes[i], i, class_file->constant_pool, 1);
    }
}

void write_attribute_info(AttributeInfo attribute_info, uint32_t index, ConstantPoolInfo* constant_pool, uint8_t indentation)
{
    const char* attribute_name = get_formatted_constant(constant_pool, attribute_info.attribute_name_index);
    ClassFileUtils::file_indent(out, indentation);
    fprintf(out, "[%d] %s\n", index, attribute_name);
    ClassFileUtils::file_indent(out, indentation + 1);
    fprintf(out, "Attribute name index:\t ConstantPoolInfo #%d\n", attribute_info.attribute_name_index);
    ClassFileUtils::file_indent(out, indentation + 1);
    fprintf(out, "Attribute length:\t %d\n", attribute_info.attribute_length);
    ConstUtf8Info attribute_utf8 = constant_pool[attribute_info.attribute_name_index - 1].info.utf8_info;
    if (ClassFileUtils::compare_utf8_str(attribute_utf8, "ConstantValue")) {
        ConstValueAttribute const_value = attribute_info.info.const_value_info;
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Constant value index:\t ConstantPoolInfo #%d <%s>\n", const_value.const_value_index,
            get_formatted_constant(constant_pool, const_value.const_value_index));
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "Code")) {
        CodeAttribute code = attribute_info.info.code_info;
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Maximum stack depth:\t %d\n", code.max_stack);
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Maximum local variables: %d\n", code.max_locals);
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Code length:\t\t %u\n", code.code_length);
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Exception table:\n");
        ClassFileUtils::file_indent(out, indentation + 2);
        if (code.exception_table_length > 0) {
            fprintf(out, "Nr.\t start_pc\t end_pc\t handler_pc\t catch_type\t verbose\n");
            for (uint16_t i = 0; i < code.exception_table_length; i++) {
                ExceptionTable attribute_utf8 = code.exception_table[i];
                ClassFileUtils::file_indent(out, indentation + 2);
                fprintf(out, "%d\t ", i);
                fprintf(out, "%d\t ", attribute_utf8.start_pc);
                fprintf(out, "%d\t ", attribute_utf8.end_pc);
                fprintf(out, "%d\t ", attribute_utf8.handler_pc);
                if (attribute_utf8.catch_type == 0) {
                    fprintf(out, "0\n");
                } else {
                    fprintf(out, "ConstantPoolInfo #%d\t ", attribute_utf8.catch_type);
                    fprintf(out, "%s\n", get_formatted_constant(constant_pool, attribute_utf8.catch_type));
                }
            }
        } else {
            fprintf(out, "Exception table is empty.\n");
        }
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Bytecode:\n");
        write_file_bytecode(code, constant_pool, indentation + 2);
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Attributes:\n");
        for (uint16_t i = 0; i < code.attributes_count; i++) {
            write_attribute_info(code.attributes[i], i, constant_pool, indentation + 2);
        }
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "Exceptions")) {
        ExceptionsAttribute exceptions_attribute = attribute_info.info.exceptions_info;
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Nr.\t exception\t verbose\n");
        for (uint16_t i = 0; i < exceptions_attribute.number_of_exceptions; i++) {
            ClassFileUtils::file_indent(out, indentation + 1);
            fprintf(out, "%d\t ", i);
            fprintf(out, "ConstantPoolInfo #%d\t ", exceptions_attribute.exception_index_table[i]);
            fprintf(out, "%s\n", get_formatted_constant(constant_pool, exceptions_attribute.exception_index_table[i]));
        }
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "InnerClasses")) {
        InnerClassesAttribute inner_class_attribute = attribute_info.info.inner_classes_info;
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Nr.\t inner_class\t outer_class\t inner_name\t access flags\n");
        for (uint16_t i = 0; i < inner_class_attribute.number_of_classes; i++) {
            Class innerClass = inner_class_attribute.classes[i];
            ClassFileUtils::file_indent(out, indentation + 1);
            fprintf(out, "%d\t ", i);
            fprintf(out, "ConstantPoolInfo #%d <%s>\t ", innerClass.inner_class_info_index,
                get_formatted_constant(constant_pool, innerClass.inner_class_info_index));
            fprintf(out, "ConstantPoolInfo #%d <%s>\t ", innerClass.outer_class_info_index,
                get_formatted_constant(constant_pool, innerClass.outer_class_info_index));
            fprintf(out, "ConstantPoolInfo #%d <%s>\t ", innerClass.inner_name_index,
                get_formatted_constant(constant_pool, innerClass.inner_name_index));
            fprintf(out, "0x%.4X [%s]\n", innerClass.inner_class_access_flags, get_access_flags(innerClass.inner_class_access_flags));
        }
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "Synthetic")) {
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "SourceFile")) {
        SourceFileAttribute source_file = attribute_info.info.source_file_info;
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Constant value index:\t ConstantPoolInfo #%d <%s>\n", source_file.sourcefile_index,
            get_formatted_constant(constant_pool, source_file.sourcefile_index));
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "LineNumberTable")) {
        LineNumberTableAttribute line_number_table = attribute_info.info.line_number_table_info;
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Nr.\t start_pc\t line_number\n");
        for (uint16_t i = 0; i < line_number_table.line_number_table_length; i++) {
            LineNumberTable table = line_number_table.line_number_table[i];
            ClassFileUtils::file_indent(out, indentation + 1);
            fprintf(out, "%d\t ", i);
            fprintf(out, "%d\t ", table.start_pc);
            fprintf(out, "%d\n", table.line_number);
        }
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "LocalVariableTable")) {
        LocalVariableTableAttribute local_variable = attribute_info.info.local_variable_table_info;
        ClassFileUtils::file_indent(out, indentation + 1);
        fprintf(out, "Nr.\t start_pc\t length\t index\t name\t descriptor\n");
        for (uint16_t i = 0; i < local_variable.local_variable_table_length; i++) {
            LocalVariableTable variable = local_variable.local_variable_table[i];
            ClassFileUtils::file_indent(out, indentation + 1);
            fprintf(out, "%d\t ", i);
            fprintf(out, "%d\t ", variable.start_pc);
            fprintf(out, "%d\t ", variable.length);
            fprintf(out, "%d\t ", variable.index);
            fprintf(out, "ConstantPoolInfo #%d <%s>\t ", variable.name_index, get_formatted_constant(constant_pool, variable.name_index));
            fprintf(out, "ConstantPoolInfo #%d <%s>\n", variable.descriptor_index, get_formatted_constant(constant_pool, variable.descriptor_index));
        }
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "Deprecated")) {
    } else if (ClassFileUtils::compare_utf8_str(attribute_utf8, "StackMapTable")) {
    } else {
        cerr << "The .class file has an invalid attribute. (write_attribute_info)" << endl;
        exit(6);
    }
    fprintf(out, "\n");
}

void write_file_bytecode(CodeAttribute code_attribute, ConstantPoolInfo* constant_pool, uint8_t indentation)
{
    u4 code_length = code_attribute.code_length;
    u1* code = code_attribute.code;
    u1* current_ptr = code;
    u1* end_ptr = code + code_length;
    uint32_t line_number = 1;
    while (current_ptr < end_ptr) {
        u4 offset = current_ptr - code;

        ClassFileUtils::file_indent(out, indentation);
        fprintf(out, "%d\t%d\t%s", line_number++, offset, function_names_array[*current_ptr].c_str());

        if (*current_ptr <= 0x0f || (*current_ptr >= 0x1a && *current_ptr <= 0x35) || (*current_ptr >= 0x3b && *current_ptr <= 0x83)
            || (*current_ptr >= 0x85 && *current_ptr <= 0x98) || (*current_ptr >= 0xac && *current_ptr <= 0xb1) || *current_ptr == 0xbe || *current_ptr == 0xbf
            || *current_ptr == 0xc2 || *current_ptr == 0xc3) {
            fprintf(out, "\n");
            current_ptr += 1;
        } else if (*current_ptr == 0x12) {
            fprintf(out, " #%d <%s>\n", *(current_ptr + 1), get_formatted_constant(constant_pool, *(current_ptr + 1)));
            current_ptr += 2;
        } else if (*current_ptr == 0xbc) {
            u1 atype = *(current_ptr + 1);
            const char* types[] = { "boolean", "char", "float", "double", "byte", "short", "int", "long" };
            fprintf(out, " %d (%s)\n", atype, types[atype - 4]);
            current_ptr += 2;
        } else if (*current_ptr == 0x10 || (*current_ptr >= 0x15 && *current_ptr <= 0x19) || (*current_ptr >= 0x36 && *current_ptr <= 0x3a) || *current_ptr == 0xa9) {
            fprintf(out, " %d\n", *(current_ptr + 1));
            current_ptr += 2;
        } else if (*current_ptr == 0x11) {
            int16_t number = (*(current_ptr + 1) << 8) | *(current_ptr + 2);
            fprintf(out, " %d\n", number);
            current_ptr += 3;
        } else if (*current_ptr == 0x84) {
            fprintf(out, " %d by %d\n", *(current_ptr + 1), *(current_ptr + 2));
            current_ptr += 3;
        } else if (*current_ptr == 0x13 || *current_ptr == 0x14 || (*current_ptr >= 0xb2 && *current_ptr <= 0xb8) || *current_ptr == 0xbb || *current_ptr == 0xbd
            || *current_ptr == 0xc0 || *current_ptr == 0xc1) {
            u2 number = (*(current_ptr + 1) << 8) | *(current_ptr + 2);
            fprintf(out, " #%d <%s>\n", number, get_formatted_constant(constant_pool, number));
            current_ptr += 3;
        } else if ((*current_ptr >= 0x99 && *current_ptr <= 0xa8) || *current_ptr == 0xc6 || *current_ptr == 0xc7) {
            int16_t number = (*(current_ptr + 1) << 8) | *(current_ptr + 2);
            fprintf(out, " %d (%+d)\n", offset + number, number);
            current_ptr += 3;
        } else if (*current_ptr == 0xc5) {
            u2 number = (*(current_ptr + 1) << 8) | *(current_ptr + 2);
            fprintf(out, " #%d <%s> dim %d\n", number, get_formatted_constant(constant_pool, number), *(current_ptr + 3));
            current_ptr += 4;
        } else if (*current_ptr == 0xb9) {
            u2 number = (*(current_ptr + 1) << 8) | *(current_ptr + 2);
            fprintf(out, " #%d <%s> count %d\n", number, get_formatted_constant(constant_pool, number), *(current_ptr + 3));
            assert(*(current_ptr + 4) == 0);
            current_ptr += 5;
        } else if (*current_ptr == 0xc8 || *current_ptr == 0xc9) {
            int32_t number = (*(current_ptr + 1) << 24) | (*(current_ptr + 2) << 16) | (*(current_ptr + 3) << 8) | *(current_ptr + 4);
            fprintf(out, " %d (%+d)\n", offset + number, number);
            current_ptr += 5;
        } else if (*current_ptr == 0xc4) {
            u2 indexbyte = (*(current_ptr + 2) << 8) | *(current_ptr + 3);
            fprintf(out, "\n");
            ClassFileUtils::file_indent(out, indentation);
            fprintf(out, "%d\t%d\t%s %d", line_number++, offset + 1, function_names_array[*(current_ptr + 1)].c_str(), indexbyte);
            if (*(current_ptr + 1) == 0x84) {
                int16_t constbyte = (*(current_ptr + 4) << 8) | *(current_ptr + 5);
                fprintf(out, " by %d", constbyte);
                current_ptr += 6;
            } else {
                current_ptr += 4;
            }
            fprintf(out, "\n");
        } else {
            fprintf(out, "Invalid instruction opcode.\n");
            exit(7);
        }
    }
}

const char* get_access_flags(u2 access_flags)
{
    const char* flags[] = { "public ", "final ", "super ", "interface ", "abstract ", "private ", "protected ", "static ", "volatile ",
        "transient " };
    uint16_t masks[] = { 0x0001, 0x0010, 0x0020, 0x0200, 0x0400, 0x0002, 0x0004, 0x0008, 0x0040, 0x0080 };
    stringstream ss;
    for (uint8_t i = 0; i < 10; i++) {
        if ((access_flags & masks[i]) != 0) {
            ss << flags[i];
        }
    }
    return ClassFileUtils::stream_to_cstring(ss);
}

const char* get_formatted_constant(ConstantPoolInfo* constant_pool, u2 index)
{
    ConstantPoolInfo constant = constant_pool[index - 1];
    if (constant.tag == ConstClass) {
        ConstClassInfo class_info = constant.info.class_info;
        return get_formatted_constant(constant_pool, class_info.name_index);
    } else if (constant.tag == ConstFieldRef) {
        ConstFieldRefInfo field_ref_info = constant.info.field_ref_info;
        ConstNameTypeInfo name_type_info = constant_pool[field_ref_info.name_and_type_index - 1].info.name_type_info;
        const char* class_name = get_formatted_constant(constant_pool, field_ref_info.class_index);
        const char* name = get_formatted_constant(constant_pool, name_type_info.name_index);
        stringstream ss;
        ss << class_name << "." << name;
        return ClassFileUtils::stream_to_cstring(ss);
    } else if (constant.tag == ConstMethodRef) {
        ConstMethodRefInfo method_ref_info = constant.info.method_ref_info;
        ConstNameTypeInfo name_type_info = constant_pool[method_ref_info.name_and_type_index - 1].info.name_type_info;
        const char* class_name = get_formatted_constant(constant_pool, method_ref_info.class_index);
        const char* name = get_formatted_constant(constant_pool, name_type_info.name_index);
        stringstream ss;
        ss << class_name << "." << name;
        return ClassFileUtils::stream_to_cstring(ss);
    } else if (constant.tag == ConstInterfaceMethodRef) {
        ConstInterfaceMethodRefInfo interfaceMethodRefInfo = constant.info.interface_method_ref_info;
        ConstNameTypeInfo name_type_info = constant_pool[interfaceMethodRefInfo.name_and_type_index - 1].info.name_type_info;
        const char* class_name = get_formatted_constant(constant_pool, interfaceMethodRefInfo.class_index);
        const char* name = get_formatted_constant(constant_pool, name_type_info.name_index);
        stringstream ss;
        ss << class_name << "." << name;
        return ClassFileUtils::stream_to_cstring(ss);
    } else if (constant.tag == ConstStr) {
        ConstStrInfo str_info = constant.info.str_info;
        return get_formatted_constant(constant_pool, str_info.string_index);
    } else if (constant.tag == ConstInt) {
        ConstIntInfo int_info = constant.info.int_info;
        int32_t number = int_info.bytes;
        char* s = (char*)malloc(sizeof(char) * 100);
        snprintf(s, sizeof(char) * 100, "%d", number);
        return s;
    } else if (constant.tag == ConstFloat) {
        ConstFloatInfo float_info = constant.info.float_info;
        int32_t s = ((float_info.bytes >> 31) == 0) ? 1 : -1;
        int32_t e = ((float_info.bytes >> 23) & 0xff);
        int32_t m = (e == 0) ? (float_info.bytes & 0x7fffff) << 1 : (float_info.bytes & 0x7fffff) | 0x800000;
        float number = s * m * pow(2, e - 150);
        char* str = (char*)malloc(sizeof(char) * 100);
        snprintf(str, sizeof(char) * 100, "%f", number);
        return str;
    } else if (constant.tag == ConstLong) {
        ConstLongInfo long_info = constant.info.long_info;
        int64_t number = ((int64_t)long_info.high_bytes << 32) + long_info.low_bytes;
        char* str = (char*)malloc(sizeof(char) * 100);
        snprintf(str, sizeof(char) * 100, "%lld", (long long)number);
        return str;
    } else if (constant.tag == ConstDouble) {
        ConstDoubleInfo double_info = constant.info.double_info;
        int64_t bytes = ((int64_t)double_info.high_bytes << 32) + double_info.low_bytes;
        int32_t s = ((bytes >> 63) == 0) ? 1 : -1;
        int32_t e = (int32_t)((bytes >> 52) & 0x7ffL);
        int64_t m = (e == 0) ? (bytes & 0xfffffffffffffL) << 1 : (bytes & 0xfffffffffffffL) | 0x10000000000000L;
        double number = s * m * pow(2, e - 1075);
        char* str = (char*)malloc(sizeof(char) * 100);
        snprintf(str, sizeof(char) * 100, "%f", number);
        return str;
    } else if (constant.tag == ConstNameType) {
        ConstNameTypeInfo name_type_info = constant.info.name_type_info;
        const char* name = get_formatted_constant(constant_pool, name_type_info.name_index);
        const char* descriptor = get_formatted_constant(constant_pool, name_type_info.descriptor_index);
        char* result = (char*)malloc(sizeof(char) * (strlen(name) + strlen(descriptor)) + 1);
        strcpy(result, name);
        strcat(result, descriptor);
        return result;
    } else if (constant.tag == ConstUtf8) {
        ConstUtf8Info utf8_info = constant.info.utf8_info;
        char* str = (char*)malloc((utf8_info.length + 1) * sizeof(char));
        uint16_t j = 0;
        for (uint16_t i = 0; i < utf8_info.length; i++) {
            if (isprint(utf8_info.bytes[i]))
                str[j++] = utf8_info.bytes[i];
        }
        str[j] = '\0';
        return str;
    } else {
        cerr << "The .class file has an invalid tag (" << constant.tag << ") in its constant pool." << endl;
        exit(5);
    }
    return NULL;
}
