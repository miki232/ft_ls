//
// Created by mtoia on 01/01/25.
//

#include "../include/ft_ls.h"

char *ft_get_color(const char *src, struct stat *sb_ptr) {
    struct stat sb;

    if (!sb_ptr) {
        char *tmp = ft_strjoin(op.path, "/");
        char *path = ft_strjoin(tmp, src);

        if (lstat(path, &sb) == -1) {
            free(tmp);
            free(path);
            return NULL;
        }

        free(tmp);
        free(path);

        sb_ptr = &sb;
    }
    return (S_ISDIR(sb_ptr->st_mode)) ? "\033[1;34m"     // blue for directories
         : (S_ISLNK(sb_ptr->st_mode)) ? "\033[1;36m"    // cyan for symlinks
         : (S_IEXEC & sb_ptr->st_mode) ? "\033[1;32m"  // green for executables
         : is_archive(src) ? "\033[1;31m"        // red for archives
         : "";                                  // default color
}