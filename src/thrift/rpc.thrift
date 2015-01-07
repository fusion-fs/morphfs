enum Capability
{
	LIST = 1,
	READ = 2,
	WRITE = 4,
	DELETE = 8,
}

struct ShowArg
{
	1:string key,
	2:i64    offset,
    3:i64    len,
}

struct ShowRes
{
	1:i32   status,
	2:optional i64 len,
    3:optional list<string> data,
}

struct ReadArg
{
	1:string key,
	2:i64    offset,
    3:i64    len,
}

struct ReadRes
{
	1:i32   status,
	2:optional i64 len,
    3:optional string data,
}

struct WriteArg
{
	1:string key,
	2:i64    offset,
    3:i64    len,
	4:string data,
}

struct WriteRes
{
	1:i32   status,
	2:optional i64 len,
}

service RPC 
{
  ShowRes show (1:ShowArg arg),
  ReadRes read (1:ReadArg arg),
  WriteRes write (1:WriteArg arg),
}