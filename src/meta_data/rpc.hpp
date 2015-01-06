extern volatile int force_exit;
#ifdef __cplusplus
extern "C" {
    extern int find_client(const char *path);
    extern int write_to_client(int fd, unsigned char *data, ulong len);
    extern int read_from_client(int fd, unsigned char *req, ulong req_len, 
                                unsigned char *resp, ulong resp_len);
}
#else
extern int find_client(const char *path);
extern int write_to_client(int fd, unsigned char *data, ulong len);
extern int read_from_client(int fd, unsigned char *req, ulong req_len, 
                            unsigned char *resp, ulong resp_len);
#endif
