#include "../include/path_convertor.h"

int main(int argc, char* argv[])
{
    char* path = (char*)calloc(PATH_MAX_LENGTH, sizeof(char));
    extra_slashes_deleter(argv[1], path);
    printf("%s\n", argv[1]);

    queue_t* dir_name_data = make_dir_names_data(path);
    path_dots_deleter(dir_name_data);

    char* final_path = make_final_path(dir_name_data);
    queue_dtor(dir_name_data);
    printf("%s\n", final_path);
    free(final_path);
    return 0;
}