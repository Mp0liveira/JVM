#include "ClassFileUtils.hpp"

using namespace std;

namespace JavaVersions {
    constexpr int V_1_1 = 45;
    constexpr int V_1_4 = 48;
    constexpr int V_1_8 = 52;
}

double ClassFileUtils::return_version(ClassFile* class_file)
{
    if (class_file->major_version < JavaVersions::V_1_1 || class_file->major_version > JavaVersions::V_1_8) {
        return 0;
    }
    if (class_file->major_version <= JavaVersions::V_1_4) {
        return 1.0 + (class_file->major_version - 44) * 0.1;
    }
    return 5 + (class_file->major_version - 49);
}

double ClassFileUtils::non_suported_version(ClassFile* class_file)
{
    if (class_file->major_version < JavaVersions::V_1_1 || class_file->major_version > JavaVersions::V_1_8) {
        return 5 + (class_file->major_version - 49);
    }
    return 0;
}

bool ClassFileUtils::compare_utf8_str(ConstUtf8Info constant, const char* str)
{
    if (constant.length != strlen(str)) {
        return false;
    }

    return strncmp((const char*)constant.bytes, str, constant.length) == 0;
}

bool ClassFileUtils::verify_classfile_name(string filename, string classname)
{
    int aux_pos;
    filename = filename.substr(0, filename.size() - 6);
    aux_pos = filename.find("\\");
    while (aux_pos >= 0 && (unsigned int)aux_pos <= filename.size()) {
        filename = filename.substr(aux_pos + 1);
        aux_pos = filename.find("\\");
    }
    aux_pos = filename.find("/");
    while (aux_pos >= 0 && (unsigned int)aux_pos <= filename.size()) {
        filename = filename.substr(aux_pos + 1);
        aux_pos = filename.find("/");
    }
    aux_pos = classname.find("\\");
    while (aux_pos >= 0 && (unsigned int)aux_pos <= classname.size()) {
        classname = classname.substr(aux_pos + 1);
        aux_pos = classname.find("\\");
    }
    aux_pos = classname.find("/");
    while (aux_pos >= 0 && (unsigned int)aux_pos <= classname.size()) {
        classname = classname.substr(aux_pos + 1);
        aux_pos = classname.find("/");
    }
    return (classname == filename);
}

const char* ClassFileUtils::stream_to_cstring(const stringstream& ss)
{
    string tmp = ss.str();
    char* result = (char*)malloc(sizeof(char) * (tmp.size() + 1));
    if (result == nullptr) {
        cerr << "Unable to malloc";
        exit(EXIT_FAILURE);
    }
    tmp.copy(result, tmp.size());
    result[tmp.size()] = '\0';
    return result;
}

void ClassFileUtils::file_indent(FILE* out, uint8_t n)
{
    for (uint8_t i = 0; i < n; i++)
        fprintf(out, "\t");
}
