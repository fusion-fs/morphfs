#include "./gen-cpp/RPC.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <vector>
#ifdef __cplusplus
extern "C" {
    using namespace ::apache::thrift;
    using namespace ::apache::thrift::protocol;
    using namespace ::apache::thrift::transport;
    using boost::shared_ptr;
    using namespace std;
    typedef pair<string, RPCClient *> OSDPair;
    vector<OSDPair> OSDVector;
    
    int add_client(const char *host)
    {
	OSDPair p = make_pair(host, (RPCClient *)NULL);
	OSDVector.insert(OSDVector.begin(), p);
	return 0;
    }

    int find_client(const char *path) 
    { 
        return 0; 
    }

    RPCClient* get_client(int fd)
    {
	OSDPair pair = OSDVector[fd];
        RPCClient *client = pair.second;
	
        if (!client) {
	    string osd = pair.first;
	    string host = osd;
	    ulong port = 9090;

	    unsigned found = osd.find_last_of(":");
	    if (found) {
		host = osd.substr(0,found);
		port = atoi(osd.substr(found + 1).c_str());
	    }
	    fprintf(stderr, "create rpc to %s:%lu\n", host.c_str(), port);

            shared_ptr<TSocket> socket(new TSocket(host, port));
            shared_ptr<TTransport> transport(new TBufferedTransport(socket));
            shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
            client = new RPCClient(protocol);
	    pair.second = client;
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

    int mkdir_on_client(int fd, const char *path, uint mode)
    {
        RPCClient* client = get_client(fd);
        MkdirArg arg;
        arg.__set_key(path);
        arg.__set_mode(mode);
        client->send_mkdir(arg);
        MkdirRes res;

        //FIXME: catch exception
        client->recv_mkdir(res);
        fprintf(stderr, "read recv: status %d\n", res.status);
	return res.status;
    }
}
#endif
