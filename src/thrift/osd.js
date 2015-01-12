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

    mkdir: function(arg, result) {
            console.log("mkdir:", arg.key);
            var fd = fs.mkdirSync(root + arg.key, arg.mode);
            var mkdirRes = new ttypes.MkdirRes({status: 0});
            result(null, mkdirRes);
        },

    truncate: function(arg, result) {
            console.log("truncate:" + arg.key + " size " + arg.newSize);
            var path = root + arg.key;
            if (fs.existsSync(path) == false)
                fs.openSync(path, "w");
            var fd = fs.truncateSync(root + arg.key, arg.newSize);
            var truncateRes = new ttypes.TruncateRes({status: 0});
            result(null, truncateRes);
        },

    read: function(arg, result) {
            console.log("read:" + arg.key + " off " + arg.offset + " len " + arg.len);


            var fd = fs.open(path, "r",  function(err, fd) {
                    if (err) {
                        throw "cannot open " + path;
                    } else {
                        var sz = parseInt(arg.len, 10);
                        var buf = new Buffer(sz);
                        fs.read(fd, buf, 0, buf.length, arg.offset,  
                                 function(err, len, buffer) {
                                    fs.close(fd);
                                    if (len > 0) {
                                        var readRes = new ttypes.ReadRes({
                                            status: 0,
                                            len: len,
                                            data: buffer});
                                    }else {                                    
                                        var readRes = new ttypes.ReadRes({status: -1});
                                    }
                                    result(null, readRes);
                                });
                    }

                });
        },

    write: function(arg, result) {
            console.log("write:" + arg.key + " off " + arg.offset + " len " + arg.len);
            var path = root + arg.key;
            var buf = new Buffer(arg.data);
            var flag = "w+";
            if (fs.existsSync(path)){
                flag = "rs+";
            }
            var fd = fs.open(path, flag,  function(err, fd) {
                    if (err) {
                        throw "open failed " + path;
                    } else {
                        var off = parseInt(arg.offset, 10);
                        var sz = parseInt(arg.len, 10);
                        //console.log("off " + off + " sz " + sz + " len " + buf.length);
                        fs.write(fd, buf, 0, sz, off,  
                                 function(err, len, buffer) {
                                     fs.close(fd);
                                     var status = 0;
                                     if (len < 0)
                                         status = -1;
                                     
                                     var writeRes = new ttypes.WriteRes({status: status,
                                                                         len: len});

                                     result(null, writeRes);
                                 });

                    }
                });
        },
    },
    options
    );

server.listen(9090);
