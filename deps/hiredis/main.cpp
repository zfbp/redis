#include "hiredis.h"
#include <Windows.h>

int main(int argc, char **argv) {
	return 0;
}

#define MQ_EXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif


	void mqLog(const char*format, ...) {
		FILE* f = fopen("D:\\mqDebug.log", "a+");
		va_list args;
		va_start(args, format);
		vfprintf(f, format, args);
		va_end(args);
		fclose(f);
	}

	char * CharArrayToStr(const char* fname, const char array[]) {
		mqLog("%s%d\n", fname, sizeof(array));
		return NULL;
	}

	/* Function to free the reply objects hiredis returns by default. */
	MQ_EXPORT void __stdcall mqFreeReplyObject(void *reply) {
		freeReplyObject(reply);
	}

	MQ_EXPORT redisContext* __stdcall mqConnect(const wchar_t *ip, int port)
	{
		char buf[128];
		size_t sz = wcstombs(buf, ip, sizeof(buf));
		if (sz > 0 && sz <= sizeof(buf)) {
			mqLog("%s:%d\n", buf, port);
			//CharArrayToStr(__FUNCTION__, buf);
			return redisConnect(buf, port);
		}
		return NULL;
	}

	MQ_EXPORT redisContext* __stdcall mqConnectWithTimeout(const wchar_t *ip, int port, long sec, long usec)
	{
		char buf[128];
		size_t sz = wcstombs(buf, ip, sizeof(buf));
		if (sz > 0 && sz <= sizeof(buf)) {
			//struct timeval {
			//	long    tv_sec;         /* seconds */
			//	long    tv_usec;        /* and microseconds */
			//}
			timeval tv;
			tv.tv_sec = sec;
			tv.tv_usec = usec;
			return redisConnectWithTimeout(buf, port, tv);
		}
		return NULL;
	}

	MQ_EXPORT void __stdcall mqFree(redisContext *c)
	{
		redisFree(c);
	}

	/* Issue a command to Redis. In a blocking context, it is identical to calling
	 * redisAppendCommand, followed by redisGetReply. The function will return
	 * NULL if there was an error in performing the request, otherwise it will
	 * return the reply. In a non-blocking context, it is identical to calling
	 * only redisAppendCommand and will always return NULL. */
	MQ_EXPORT void *__stdcall mqvCommand(redisContext *c, const char *format, va_list ap)
	{
		return redisvCommand(c, format, ap);
	}

	MQ_EXPORT const wchar_t *mqCommand(redisContext* rc, const wchar_t *format)
	{
		char buf[1024];
		size_t sz = wcstombs(buf, format, sizeof(buf));
		if (sz > 0 && sz <= sizeof(buf)) {
			CharArrayToStr(__FUNCTION__, buf);
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
