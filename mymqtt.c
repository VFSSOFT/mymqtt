#include "mymqtt.h"

#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

static int MYMQTT_INITIALIZED = 0;

#ifdef _WIN32
static CRITICAL_SECTION mutex;
#else // _WIN32
static pthread_mutex_t mutex;
#endif // _WIN32

struct mymqtt_s {
    int socket;
    
    SSL_CTX* sslctx;
    SSL*     ssl;
};

int mymqtt__global_init() {
  int err;
  if (!MYMQTT_INITIALIZED) {

#if _WIN32
    WSADATA wsaData;
    err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != 0) {
      return err;
    }
  
    InitializeCriticalSection(&mutex);
    
#else // _WIN32
    pthread_mutex_init(&mutex, NULL);
    
#endif // _WIN32
  
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    
    MYMQTT_INITIALIZED = 1;
  }
#if _WIN32

#else
#endif
  
  return 0;
}
int mymqtt__global_deinit() {
  if (MYMQTT_INITIALIZED) {
#if _WIN32
    DeleteCriticalSection(&mutex);
#else // _WIN32
    pthread_mutex_destroy(&mutex);
#endif
  
    EVP_cleanup();
    ERR_free_strings();
    
    MYMQTT_INITIALIZED = 0;
  }
  return 0;
}

static void mymqtt__lock() {
#if _WIN32
  EnterCriticalSection(&mutex);
#else
  pthread_mutex_lock(&mutex);
#endif
}
static void mymqtt__unlock() {
#if _WIN32
  LeaveCriticalSection(&mutex);
#else
  pthread_mutex_unlock(&mutex);
#endif
}

int mymqtt__init(mymqtt_t* m) {

}
int mymqtt__destroy(mymqtt_t* m) {

}


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

