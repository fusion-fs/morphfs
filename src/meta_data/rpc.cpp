#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <libwebsockets.h>
#include <errno.h>
#include <set>
#include "rpc.hpp"
#ifdef __cplusplus
extern "C" {
    int find_client(const char *path) 
    { 
        return 0; 
    }

    int write_to_client(int fd, unsigned char *data, ulong len) 
    {
        return 0;
    }
    
    int read_from_client(int fd, unsigned char *req, ulong req_len, 
                                unsigned char *resp, ulong resp_len)
    {
        return 0;
    }

    int start_rpc_server(ulong port)
    {
        return 0;
    }

}
#endif
