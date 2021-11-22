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


#define SAFE_RUN(func)                   \
            do {                         \
                if ((func) != NULL)      \
                   func();               \
            } while (0)

#define SAFE_SOCKET_CREATION(descriptor, domain, type, protocol)\
            do {                                                \
                descriptor = socket(domain, type, protocol);    \
                if (descriptor == -1) {                         \
                    printf("Error while creating socket");      \
                    return 1;                                   \
                }                                               \
            } while (0)


#define SAFE_BIND(descriptor, server_info)                                                            \
            do {                                                                                      \
                 if (bind(descriptor, (struct sockaddr *) &server_info, sizeof(server_info)) == -1) { \
                    printf("Error while binding");                                                    \
                    return 1;                                                                         \
                 }                                                                                    \
            } while (0)

#define SAFE_LISTEN(descriptor, backlog)                    \
            do {                                            \
                  if (listen(descriptor, backlog) == -1) {  \
                     printf("Error while listening");       \
                     return 1;                              \
                  }                                         \
            } while (0)

#define SAFE_ACCEPT(buffer_descriptor, descriptor)                                                       \
             do {                                                                                        \
                  struct sockaddr_in information;                                                        \
                  memset(&information, 0, sizeof(information));                                          \
                  socklen_t socket_size = sizeof(information);                                           \
                  buffer_descriptor = accept(descriptor, (struct sockaddr *) &information, &socket_size);\
                  if (buffer_descriptor == -1) {                                                         \
                    printf("Error in temporary socket creation");                                        \
                    return 1;                                                                            \
                  }                                                                                      \
            } while (0)

#define SAFE_CONNECT(descriptor, information)                                                               \
              do {                                                                                          \
                    if (connect(descriptor, (struct sockaddr *) &information, sizeof(information)) == -1) { \
                        printf("Error while connecting\n ");                                                \
                        return 1;                                                                           \
                    }                                                                                       \
            } while (0)


#endif //BLOWFISH_ALGORITHM_SAFE_MACROSES_H
