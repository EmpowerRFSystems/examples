#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>  /* libcurl4-openssl-dev */

#define USAGE_MSG "Usage: webApi HOST[:PORT] KEY [KEY ...]"
#define STATUS_URL_FMT "http://%s/api/v1/status"
#define GET_STATUS_ITEM_FMT "{\"messageType\":\"getStatusItem\",\"key\":\"%s\"}"
#define GET_STATUS_ITEM_BATCH_HEAD "{\"messageType\":\"getStatusItemBatch\",\"keys\":[\""
#define GET_STATUS_ITEM_BATCH_TAIL "]}"

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

struct memory {
    char *response;
    size_t size;
};

size_t postWriterCallback(void *data, size_t size, size_t nmemb, void *userp);
CURL* setup_curl(const char* url);
void getStatusItem(CURL* handle, const char* json, struct memory* chunk);
void init_mem(struct memory *m);
char* buildJsonRequest(int argv, const char** argc);

int main(const int argv, const char** argc)
{
    CURL *curl_handle;
    struct memory chunk;
    char *jsonRequest;

    if(argv < 3)
    {
        puts(USAGE_MSG);
        exit(EXIT_FAILURE);
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);

    init_mem(&chunk);

    jsonRequest = buildJsonRequest(argv, argc);
    if(jsonRequest == NULL)
    {
        puts("buildJsonRequest() Failed!!\n");
        exit(EXIT_FAILURE);
    }

    printf("JSON Request: %s\n", jsonRequest);

    curl_handle = setup_curl(argc[1]);
    getStatusItem(curl_handle, jsonRequest, &chunk);
    printf("Resp: %s\n", chunk.response);

    free(jsonRequest);
    free(chunk.response);

    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    return 0;
}

size_t postWriterCallback(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL)
    {
        printf("realloc() failed\n");
        exit(EXIT_FAILURE);
    }

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

CURL* setup_curl(const char* url)
{
    CURL *resp;

    resp = curl_easy_init();
    if(resp)
    {
        char urlSet[80];
        bzero(urlSet, NELEMS(urlSet));
        sprintf(urlSet, STATUS_URL_FMT, url);
        curl_easy_setopt(resp, CURLOPT_URL, urlSet);
        curl_easy_setopt(resp, CURLOPT_WRITEFUNCTION, postWriterCallback);
    }

    return resp;
}

void getStatusItem(CURL* handle, const char* json, struct memory* chunk)
{
    if(handle)
    {
        CURLcode res = CURLE_OK;

        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, json);
        curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, (long)strlen(json));
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)chunk);

        res = curl_easy_perform(handle);
        if(res != CURLE_OK)
        {
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
    }
}

void init_mem(struct memory *m)
{
    m->size = 0;
    m->response = malloc(m->size+1);

    if (m->response == NULL)
    {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }

    m->response[0] = '\0';
}

char* buildJsonRequest(int argv, const char** argc)
{
    char* str = NULL;

    if(argv == 3)
    {
        size_t strSize = strlen(GET_STATUS_ITEM_FMT) + 1;

        strSize += strlen(argc[2]) + 1;
        str = (char*)malloc(strSize);
        bzero(str, strSize);
        sprintf(str, GET_STATUS_ITEM_FMT, argc[2]);
    }
    else
    {
        int argIdx;
        size_t strSize = strlen(GET_STATUS_ITEM_BATCH_HEAD) + strlen(GET_STATUS_ITEM_BATCH_TAIL) + 1;

        for(argIdx = 2; argIdx < argv; ++argIdx)
        {
            strSize += strlen(argc[argIdx]) + 2;
        }

        str = (char*)malloc(strSize);
        bzero(str, strSize);
        strcat(str, GET_STATUS_ITEM_BATCH_HEAD);

        for(argIdx = 2; argIdx < argv; ++argIdx)
        {
            strcat(strcat(str, argc[argIdx]), "\",\"");
        }

        strSize = strlen(str);
        str[strSize-2] = '\0';
        str[strSize-1] = '\0';

        strcat(str, GET_STATUS_ITEM_BATCH_TAIL);
    }

    return str;
}
