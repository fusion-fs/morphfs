#include "./gen-cpp/RPC.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#ifdef __cplusplus
extern "C" {
    using namespace ::apache::thrift;
    using namespace ::apache::thrift::protocol;
    using namespace ::apache::thrift::transport;

    using boost::shared_ptr;

    
    int find_client(const char *path) 
    { 
        return 0; 
    }

    RPCClient* get_client(int fd)
    {
        //FIXME: get client from vector
        static RPCClient *client = NULL;
       
        if (!client) {
            shared_ptr<TSocket> socket(new TSocket("127.0.0.1", 9090));
            shared_ptr<TTransport> transport(new TBufferedTransport(socket));
            shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
            client = new RPCClient(protocol);
            transport->open();
        }
        return client;
    }
    

    int write_to_client(int fd, const char *path, 
                        const char *data, ulong offset, ulong size) 
    {
        RPCClient* client = get_client(fd);
        WriteArg arg;
        arg.__set_key(path);
        arg.__set_offset(offset);
        arg.__set_len(size);
        arg.__set_data(data);
        client->send_write(arg);
        WriteRes res;
        //FIXME: catch exception
        client->recv_write(res);
        fprintf(stderr, "write recv: status %d\n", res.status);
        if (!res.status)
            return (int)res.len;
        else
            return res.status;
    }
    
    int read_from_client(int fd, const char *path, 
                         ulong offset, ulong size, 
                         char *data)
    {
        RPCClient* client = get_client(fd);
        ReadArg arg;
        arg.__set_key(path);
        arg.__set_offset(offset);
        arg.__set_len(size);
        client->send_read(arg);
        ReadRes res;

        //FIXME: catch exception
        client->recv_read(res);
        fprintf(stderr, "read recv: status %d\n", res.status);
        if (!res.status){
            memcpy(data, res.data.c_str(), res.len);
            return (int)res.len;
        }
        else
            return res.status;
    }

}
#endif
