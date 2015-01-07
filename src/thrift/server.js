var thrift = require('thrift');
var options = {tls: false, transport: thrift.TBufferedTransport};
var fs = require('fs');

var RPC = require('./gen-nodejs/RPC.js'),
    ttypes = require('./gen-nodejs/rpc_types');

var root = "/tmp/osd";

var server = thrift.createServer(RPC, {
    show: function(arg, result) {
            console.log("show:", arg.key);
            var test_showRes = new ttypes.ShowRes({status: 0,
                                                   len: 0});

            result(null, test_showRes);
        },

    read: function(arg, result) {
            console.log("read:");
            var test_readRes = new ttypes.ReadRes({status: -1});

            result(null, test_readRes);
        },

    write: function(arg, result) {
            console.log("write:" + arg.key + 
                        " at " + arg.offset + " len " + arg.len + " data:" + arg.data);
            var path = root + arg.key;
            var fd = fs.openSync(path, "w+");
            var buffer = new Buffer(arg.data);
            var len = fs.writeSync(fd, buffer, 0, arg.len, arg.offset);
            fs.close(fd);
            var status = 0;
            if (len < 0)
                status = -1;
            
            var writeRes = new ttypes.WriteRes({status: status,
                                                len: len});

            result(null, writeRes);
        },
    },
    options
    );

server.listen(9090);
