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

#ifdef __cplusplus
extern "C" {
#endif


	/* Public API for the protocol parser. */
	MQ_EXPORT void * __stdcall mqReaderCreate(void) {
		return redisReaderCreate();
	}

	MQ_EXPORT void __stdcall mqReaderFree(void *r) {
		return redisReaderFree((redisReader *)r);
	}

	MQ_EXPORT int __stdcall mqReaderFeed(void *r, const char *buf, size_t len) {
		return redisReaderFeed((redisReader *)r, buf, len);
	}

	MQ_EXPORT int __stdcall mqReaderGetReply(void *r, void **reply) {
		return redisReaderGetReply((redisReader *)r, reply);
	}

	/* Function to free the reply objects hiredis returns by default. */
	MQ_EXPORT void __stdcall mqFreeReplyObject(void *reply) {
		freeReplyObject(reply);
	}

	/* Functions to format a command according to the protocol. */
	MQ_EXPORT int __stdcall mqvFormatCommand(char **target, const char *format, va_list ap)
	{
		return redisvFormatCommand(target, format, ap);
	}

	// MQ_EXPORT int mqFormatCommand(char **target, const char *format, ...)
	// {
	// return redisFormatCommand(target, format, ...);
	// }

	MQ_EXPORT int __stdcall mqFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen)
	{
		return redisFormatCommandArgv(target, argc, argv, argvlen);
	}

	MQ_EXPORT void * __stdcall mqConnect(const wchar_t *ip, int port)
	{
		char buf[128];
		size_t sz = wcstombs(buf, ip, sizeof(buf));
		if (sz > 0 && sz <= sizeof(buf)) {
			return redisConnect(buf, port);
		}
		return NULL;
	}

	MQ_EXPORT void* __stdcall mqConnectWithTimeout(const wchar_t *ip, int port, const struct timeval tv)
	{
		char buf[128];
		size_t sz = wcstombs(buf, ip, sizeof(buf));
		if (sz > 0 && sz <= sizeof(buf)) {
			return redisConnectWithTimeout(buf, port, (const struct timeval)tv);
		}
		return NULL;
	}

	MQ_EXPORT void *__stdcall mqConnectNonBlock(const char *ip, int port)
	{
		return redisConnectNonBlock(ip, port);
	}

	MQ_EXPORT void *__stdcall mqConnectBindNonBlock(const char *ip, int port, const char *source_addr)
	{
		return redisConnectBindNonBlock(ip, port, source_addr);
	}

	MQ_EXPORT void *__stdcall mqConnectUnix(const char *path)
	{
		return redisConnectUnix(path);
	}

	MQ_EXPORT void *__stdcall mqConnectUnixWithTimeout(const char *path, const struct timeval tv)
	{
		return redisConnectUnixWithTimeout(path, tv);
	}

	MQ_EXPORT void *__stdcall mqConnectUnixNonBlock(const char *path)
	{
		return redisConnectUnixNonBlock(path);
	}

	MQ_EXPORT void *__stdcall mqConnectFd(int fd)
	{
		return redisConnectFd(fd);
	}

	MQ_EXPORT int __stdcall mqSetTimeout(void *c, const struct timeval tv)
	{
		return redisSetTimeout((redisContext *)c, tv);
	}

	MQ_EXPORT int __stdcall mqEnableKeepAlive(void *c)
	{
		return redisEnableKeepAlive((redisContext *)c);
	}

	MQ_EXPORT void __stdcall mqFree(void *c)
	{
		redisFree((redisContext *)c);
	}

	MQ_EXPORT int __stdcall mqFreeKeepFd(void *c)
	{
		return redisFreeKeepFd((redisContext *)c);
	}

	MQ_EXPORT int __stdcall mqBufferRead(void *c)
	{
		return redisBufferRead((redisContext *)c);
	}

	MQ_EXPORT int __stdcall mqBufferWrite(void *c, int *done)
	{
		return redisBufferWrite((redisContext *)c, done);
	}

	/* In a blocking context, this function first checks if there are unconsumed
	 * replies to return and returns one if so. Otherwise, it flushes the output
	 * buffer to the socket and reads until it has a reply. In a non-blocking
	 * context, it will return unconsumed replies until there are no more. */
	MQ_EXPORT int __stdcall mqGetReply(void *c, void **reply)
	{
		return redisGetReply((redisContext *)c, reply);
	}

	MQ_EXPORT int __stdcall mqGetReplyFromReader(void *c, void **reply)
	{
		return redisGetReplyFromReader((redisContext *)c, reply);
	}

	/* Write a formatted command to the output buffer. Use these functions in blocking mode
	 * to get a pipeline of commands. */
	MQ_EXPORT int __stdcall mqAppendFormattedCommand(void *c, const char *cmd, size_t len)
	{
		return redisAppendFormattedCommand((redisContext *)c, cmd, len);
	}

	/* Write a command to the output buffer. Use these functions in blocking mode
	 * to get a pipeline of commands. */
	MQ_EXPORT int __stdcall mqvAppendCommand(void *c, const char *format, va_list ap)
	{
		return redisvAppendCommand((redisContext *)c, format, ap);
	}

	// MQ_EXPORT int mqAppendCommand(redisContext *c, const char *format, ...)
	// {
	// return redisAppendCommand(c, format, ...);
	// }

	MQ_EXPORT int __stdcall mqAppendCommandArgv(void *c, int argc, const char **argv, const size_t *argvlen)
	{
		return redisAppendCommandArgv((redisContext *)c, argc, argv, argvlen);
	}

	/* Issue a command to Redis. In a blocking context, it is identical to calling
	 * redisAppendCommand, followed by redisGetReply. The function will return
	 * NULL if there was an error in performing the request, otherwise it will
	 * return the reply. In a non-blocking context, it is identical to calling
	 * only redisAppendCommand and will always return NULL. */
	MQ_EXPORT void *__stdcall mqvCommand(void *c, const char *format, va_list ap)
	{
		return redisvCommand((redisContext *)c, format, ap);
	}

	MQ_EXPORT const wchar_t *mqCommand(redisContext* rc, const wchar_t *format)
	{
		char buf[1024];
		size_t sz = wcstombs(buf, format, sizeof(buf));
		if (sz > 0 && sz <= sizeof(buf)) {
			redisReply* rp = (redisReply *)redisCommand(rc, buf);
			if (rp != NULL) {
				wchar_t * ret = (wchar_t*)malloc(sizeof(wchar_t) * (rp->len + 1));
				size_t retSz = mbstowcs(ret, rp->str, rp->len);
				if (retSz > 0) {
					ret[retSz] = '\0';
					return ret;
				}
			}
		}
		return NULL;
	}

	MQ_EXPORT void *__stdcall mqCommandArgv(void *c, int argc, const char **argv, const size_t *argvlen)
	{
		return redisCommandArgv((redisContext *)c, argc, argv, argvlen);
	}


#ifdef __cplusplus
}
#endif
