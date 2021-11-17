#ifndef BLOWFISH_ALGORITHM_SAFE_MACROSES_H
#define BLOWFISH_ALGORITHM_SAFE_MACROSES_H

#define SAFE_GETTING_TIME(time_sec)                   \
        do {                                          \
            (time_sec) = time(NULL);                  \
            if ((time_sec) == 0) {                    \
                printf("Error while getting time\n"); \
                return 1;                             \
            }                                         \
        } while (0)

#define SAFE_MALLOC(ptr, type, size)                        \
         do {                                               \
            (ptr) = (type *) malloc(size);                  \
            if ((ptr) == NULL) {                            \
                printf("Error while allocating memory\n");  \
                return 1;                                   \
            }                                               \
        } while (0)

#define SAFE_OPENING_FILE(file, file_name, mode)     \
         do {                                        \
            (file) = fopen((file_name), (mode));     \
            if ((file) == NULL) {                    \
                printf("Error while opening file\n");\
                return 1;                            \
            }                                        \
        } while (0)



#endif //BLOWFISH_ALGORITHM_SAFE_MACROSES_H
