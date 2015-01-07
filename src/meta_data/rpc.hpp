extern volatile int force_exit;
#ifdef __cplusplus
extern "C" {
    extern int find_client(const char *path);
    extern int write_to_client(int fd, const char *path, const char *data, ulong offset, ulong len);
    extern int read_from_client(int fd, const char *path, 
                                ulong offset, ulong size, 
                                char *data);
}
#else
extern int find_client(const char *path);
extern int write_to_client(int fd, const char *path, const char *data, ulong offset, ulong len);
extern int read_from_client(int fd, const char *path, 
                            ulong offset, ulong size, 
                            char *data);
#endif
