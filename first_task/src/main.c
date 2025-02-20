#include "path_convertor.h"

int main(int argc, char* argv[])
{
    char* path = (char*)calloc(PATH_MAX_LENGTH, sizeof(char));
    extra_slashes_deleter(argv[1], path);

    list_info_t* lst_info = make_dir_names_data(path);

    char* final_path = make_final_path(lst_info);
    printf("%s\n", final_path);
    free(final_path);
    return 0;
}