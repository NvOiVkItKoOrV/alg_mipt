#include "../include/path_convertor.h"

int main(int argc, char* argv[])
{
    char* path = calloc(PATH_MAX_LENGTH, sizeof(char));
    extra_slashes_deleter(argv[1], path);
    queue* dir_name_data = make_dir_names_data(path);
    path_dots_deleter(dir_name_data);
    char* final_path = make_final_path(dir_name_data);
    printf("%s\n", final_path);
    return 0;
}