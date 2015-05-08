//#define DEBUG 1

#ifdef DEBUG
	#define DEBUGSBEGIN Serial.begin(9600); \
		while(!Serial); \
		delay(200);
	#define DEBUGSPRINTLN(msg) Serial.println(msg);
	#define DEBUGSPRINT(msg) Serial.print(msg);
#else
	#define DEBUGSPRINTLN(msg) ;
	#define DEBUGSPRINT(msg) ;
	#define DEBUGSBEGIN;
#endif

#define INT_LONG_MAX ((long)0x7fffffff)
#define INT_LONG_MIN ((long)0x80000000)

#define INT_SHORT_MAX ((short)0x7fff)
#define INT_SHORT_MIN ((short)0x8000)

#define Wire WireModified