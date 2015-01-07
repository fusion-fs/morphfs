var thrift = require('thrift');
var options = { tls: false};

var RPC = require('./gen-nodejs/RPC.js'),
    ttypes = require('./gen-nodejs/rpc_types');

var test_showRes = new ttypes.ShowRes({status: 0,
				       len: 0});

var server = thrift.createServer(RPC, {
    show: function(arg, result) {
	    console.log("show:", arg.key);
	    result(null, test_showRes);
	},

    read: function(arg, result) {
	    console.log("read:");
	    result(null);
	},

    write: function(arg, result) {
	    console.log("write:" + arg.key + 
                    " " + arg.offset + " " + arg.len);
        var test_writeRes = new ttypes.WriteRes({status: 0,
                                                 len: arg.len});

	    result(null, test_writeRes);
	},
    },
    options);

server.listen(9090);
