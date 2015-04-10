#define DEBUG 1

#ifdef DEBUG
	#define DEBUGSBEGIN Serial.begin(9600); \
		while(!Serial);\
		delay(200);
	#define DEBUGSPRINTLN(msg) Serial.println(msg);
	#define DEBUGSPRINT(msg) Serial.print(msg);
#else
	#define DEBUGSPRINTLN ;
	#define DEBUGSBEGIN ;
#endif