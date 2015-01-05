var redis = require("redis");
var client;
var root = "";

module.exports = 
{
    init: function()
    {
        client = redis.createClient();

        client.on("error", function (err) {
                console.log("Redis " + err);
                process.exit();
            });
    },

    getParent: function (path)
    {
        var n = path.lastIndexOf("/\\");
        if (n < 0) return "/";
        return path.substring(0, n);
    },

    getFile:  function (path)
    {
        var n = path.lastIndexOf("/\\");
        if (n < 0) return path;
        return path.substring(n + 1);
    },

    setRoot: function(path)
    {
        root = path;
    },

    getNewInode: function (inode, cb, arg)
    {
        var key = root + ":INODE";
        var inode = 0;
        client.incr(key, function(err, reply) {
            cb(reply, arg);
            });
    },

    Path2Inode: function(path, cb, arg)
    {
        var key = _root + ":INODE:" + path;
        var inode;
        client.get(key, function (err, reply) {
            cb(reply, arg);
            });
    },

    SetInode: function(path, ino)
    {
        var key = _root + ":INODE:" + path;
        client.set(key, ino);
    },

    AddDirEntry:  function(parent, file)
    {
        var key = _root + ":DIR:" + parent;
        client.lpush(key, file);
    },


};
