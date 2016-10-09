#include "hiredis.h"
#include <Windows.h>

int main(int argc, char **argv) {
	return 0;
}

#ifdef __cplusplus
extern "C" {
#endif

	void mqLog(const char*format, ...) {
		FILE* f = fopen("D:\\mqDebug.log", "a+");
		va_list args;
		va_start(args, format);
		vfprintf(f, format, args);
		va_end(args);
		fflush(f);
		fclose(f);
	}

	redisContext* mqConnect(const wchar_t *ip, int port)
	{
		char buf[128];
		size_t sz = wcstombs(buf, ip, sizeof(buf));
		if (sz > 0 && sz <= sizeof(buf)) {
			return redisConnect(buf, port);
		}
		return NULL;
	}

	///* This is the reply object returned by redisCommand() */
	//typedef struct redisReply {
	//	int type; /* REDIS_REPLY_* */
	//	PORT_LONGLONG integer; /* The integer when type is REDIS_REPLY_INTEGER */
	//	int len; /* Length of string */
	//	char *str; /* Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING */
	//	size_t elements; /* number of elements, for REDIS_REPLY_ARRAY */
	//	struct redisReply **element; /* elements vector for REDIS_REPLY_ARRAY */
	//} redisReply;

	int mqReplyType(const redisReply* reply) {
		return reply->type;
	}

	bool mqReplyInt(const redisReply* reply, PORT_LONGLONG* result) {
		if (reply->type == REDIS_REPLY_INTEGER) {
			*result = reply->integer;
			return true;
		}
		return false;
	}

	int mqReplyStrLen(const redisReply* reply) {
		switch (reply->type) {
		case REDIS_REPLY_ERROR:
		case REDIS_REPLY_STATUS:
		case REDIS_REPLY_STRING:
			return reply->len;
		default:
			return -1;
		}
	}

	bool mqReplyStr(const redisReply* reply, char* result) {
		switch (reply->type) {
		case REDIS_REPLY_ERROR:
		case REDIS_REPLY_STATUS:
		case REDIS_REPLY_STRING:
			memcpy(result, reply->str, reply->len);
			return true;
		default:
			return false;
		}
	}

#ifdef __cplusplus
}
#endif
