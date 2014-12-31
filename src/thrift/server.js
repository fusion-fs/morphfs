var thrift = require('thrift');
var options = { 'tls': false};

var RPC = require('./gen-nodejs/RPC.js'),
    ttypes = require('./gen-nodejs/rpc_types');

var server = thrift.createServer(RPC, {
    show: function(arg, result) {
	    console.log("show:");
	    result(null);
	},

    read: function(arg, result) {
	    console.log("read:");
	    result(null);
	},

    write: function(arg, result) {
	    console.log("write:");
	    result(null);
	},
    },
    options);

server.listen(9090);
