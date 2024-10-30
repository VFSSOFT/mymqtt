#ifndef MYMQTT_H
#define MYMQTT_H

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef struct mymqtt_s mymqtt_t;

int mymqtt__global_init();
int mymqtt__global_deinit();

int mymqtt__init(mymqtt_t* m);
int mymqtt__destroy(mymqtt_t* m);


int mymqtt__set_client_id(mymqtt_t* m, const char* client_id, int client_id_len);
const char* mymqtt__get_client_id(mymqtt_t* m);

int mymqtt__set_user(mymqtt_t* m, const char* user, int user_len);
const char* mymqtt__get_user(mymqtt_t* m);

int mymqtt__set_password(mymqtt_t* m, const char* password, int password_len);
const char* mymqtt__get_password(mymqtt_t* m);

int mymqtt__set_keepalive(mymqtt_t* m, int keepalive);
int mymqtt__get_keepalive(mymqtt_t* m);

int mymqtt__set_clean_session(mymqtt_t* m, int val);
int mymqtt__get_clean_session(mymqtt_t* m);

int mymyqtt__set_will(mymqtt_t* m, const char* topic, int qos, const char* payload, int payload_len, int retain);
const char* mymqtt__get_will_topic(mymqtt_t* m);
int mymqtt__get_will_qos(mymqtt_t* m);
int mymqtt__get_will_retain(mymqtt_t* m);
const char* mymqtt__get_will_payload(mymqtt_t* m);
int mymqtt__get_will_payload_len(mymqtt_t* m);

int mymqtt__connect(mymqtt_t* m, const char* host_port);
int mymqtt__disconnect(mymqtt_t* m);

int mymqtt__subscribe(mymqtt_t* m, const char** topics, int* qos, int count);
int mymqtt__unsubscribe(mymqtt_t* m, const char** topics, int count);

int mymqtt__publish(mymqtt_t* m, const char* topic, int qos, const char* payload, int payload_len, int retain);

int mymqtt__run(mymqtt_t* m);

#ifdef __cplusplus
}
#endif

#endif //MYMQTT_H

