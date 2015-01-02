extern volatile int force_exit;
#ifdef __cplusplus
extern "C" {
    extern int constructOSD(const char *config);
    extern int add_client(const char *host);
    extern int find_client(const char *path);
    extern int write_to_client(int fd, const char *path, const char *data, ulong offset, ulong len);
    extern int read_from_client(int fd, const char *path, 
                                ulong offset, ulong size, 
                                char *data);
    extern int mkdir_on_client(int fd, const char *path, uint mode);
}
#else
extern int constructOSD(const char *config);
extern int add_client(const char *host);
extern int find_client(const char *path);
extern int write_to_client(int fd, const char *path, const char *data, ulong offset, ulong len);
extern int read_from_client(int fd, const char *path, 
                            ulong offset, ulong size, 
                            char *data);
extern int mkdir_on_client(int fd, const char *path, uint mode);
#endif
