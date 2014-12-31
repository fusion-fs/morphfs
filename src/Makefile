THRIFT=/usr/local/bin/thrift
NODE=/usr/bin/node
all:
	cd thrift;${THRIFT} --gen js:node rpc.thrift

server: all
	cd thrift; ${NODE} server.js

client: all
	${NODE} client.js
