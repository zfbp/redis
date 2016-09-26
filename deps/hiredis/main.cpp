#include "hiredis.h"
#include <Windows.h>

int main(int argc, char **argv) {
	return 0;
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	//---
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	//---
	return(TRUE);
}

#define MQ_EXPORT __declspec(dllexport)

/* Public API for the protocol parser. */
MQ_EXPORT redisReader *mqReaderCreate(void) {
	return redisReaderCreate();
}

MQ_EXPORT void mqReaderFree(redisReader *r) {
	return redisReaderFree(r);
}

MQ_EXPORT int mqReaderFeed(redisReader *r, const char *buf, size_t len) {
	return redisReaderFeed(r, buf, len);
}

MQ_EXPORT int mqReaderGetReply(redisReader *r, void **reply) {
	return redisReaderGetReply(r, reply);
}

/* Function to free the reply objects hiredis returns by default. */
MQ_EXPORT void mqFreeReplyObject(void *reply) {
	freeReplyObject(reply);
}

/* Functions to format a command according to the protocol. */
MQ_EXPORT int mqvFormatCommand(char **target, const char *format, va_list ap)
{
	return redisvFormatCommand(target, format, ap);
}

// MQ_EXPORT int mqFormatCommand(char **target, const char *format, ...)
// {
// return redisFormatCommand(target, format, ...);
// }

MQ_EXPORT int mqFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen)
{
	return redisFormatCommandArgv(target, argc, argv, argvlen);
}

MQ_EXPORT redisContext *mqConnect(const char *ip, int port)
{
	return redisConnect(ip, port);
}

MQ_EXPORT redisContext *mqConnectWithTimeout(const char *ip, int port, const struct timeval tv)
{
	return redisConnectWithTimeout(ip, port, tv);
}

MQ_EXPORT redisContext *mqConnectNonBlock(const char *ip, int port)
{
	return redisConnectNonBlock(ip, port);
}

MQ_EXPORT redisContext *mqConnectBindNonBlock(const char *ip, int port, const char *source_addr)
{
	return redisConnectBindNonBlock(ip, port, source_addr);
}

MQ_EXPORT redisContext *mqConnectUnix(const char *path)
{
	return redisConnectUnix(path);
}

MQ_EXPORT redisContext *mqConnectUnixWithTimeout(const char *path, const struct timeval tv)
{
	return redisConnectUnixWithTimeout(path, tv);
}

MQ_EXPORT redisContext *mqConnectUnixNonBlock(const char *path)
{
	return redisConnectUnixNonBlock(path);
}

MQ_EXPORT redisContext *mqConnectFd(int fd)
{
	return redisConnectFd(fd);
}

MQ_EXPORT int mqSetTimeout(redisContext *c, const struct timeval tv)
{
	return redisSetTimeout(c, tv);
}

MQ_EXPORT int mqEnableKeepAlive(redisContext *c)
{
	return redisEnableKeepAlive(c);
}

MQ_EXPORT void mqFree(redisContext *c)
{
	redisFree(c);
}

MQ_EXPORT int mqFreeKeepFd(redisContext *c)
{
	return redisFreeKeepFd(c);
}

MQ_EXPORT int mqBufferRead(redisContext *c)
{
	return redisBufferRead(c);
}

MQ_EXPORT int mqBufferWrite(redisContext *c, int *done)
{
	return redisBufferWrite(c, done);
}

/* In a blocking context, this function first checks if there are unconsumed
 * replies to return and returns one if so. Otherwise, it flushes the output
 * buffer to the socket and reads until it has a reply. In a non-blocking
 * context, it will return unconsumed replies until there are no more. */
MQ_EXPORT int mqGetReply(redisContext *c, void **reply)
{
	return redisGetReply(c, reply);
}

MQ_EXPORT int mqGetReplyFromReader(redisContext *c, void **reply)
{
	return redisGetReplyFromReader(c, reply);
}

/* Write a formatted command to the output buffer. Use these functions in blocking mode
 * to get a pipeline of commands. */
MQ_EXPORT int mqAppendFormattedCommand(redisContext *c, const char *cmd, size_t len)
{
	return redisAppendFormattedCommand(c, cmd, len);
}

/* Write a command to the output buffer. Use these functions in blocking mode
 * to get a pipeline of commands. */
MQ_EXPORT int mqvAppendCommand(redisContext *c, const char *format, va_list ap)
{
	return redisvAppendCommand(c, format, ap);
}

// MQ_EXPORT int mqAppendCommand(redisContext *c, const char *format, ...)
// {
// return redisAppendCommand(c, format, ...);
// }

MQ_EXPORT int mqAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen)
{
	return redisAppendCommandArgv(c, argc, argv, argvlen);
}

/* Issue a command to Redis. In a blocking context, it is identical to calling
 * redisAppendCommand, followed by redisGetReply. The function will return
 * NULL if there was an error in performing the request, otherwise it will
 * return the reply. In a non-blocking context, it is identical to calling
 * only redisAppendCommand and will always return NULL. */
MQ_EXPORT void *mqvCommand(redisContext *c, const char *format, va_list ap)
{
	return redisvCommand(c, format, ap);
}

// MQ_EXPORT void *mqCommand(redisContext *c, const char *format, ...)
// {
// return redisCommand(c, format, ...);
// }

MQ_EXPORT void *mqCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen)
{
	return redisCommandArgv(c, argc, argv, argvlen);
}
