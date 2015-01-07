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
    

    int write_to_client(int fd, unsigned char *data, ulong len) 
    {
        RPCClient* client = get_client(fd);
        return len;
    }
    
    int read_from_client(int fd, unsigned char *req, ulong req_len, 
                         unsigned char *resp, ulong resp_len)
    {
        RPCClient* client = get_client(fd);
        return req_len;
    }

}
#endif
