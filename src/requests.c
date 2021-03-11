#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include <openai.h>
#include <stdarg.h>

#include "requests.h"

OpenAIResponse errorResponse(const char* message) {
    OpenAIResponse response;
    response.status = ERROR;
    response.data = message;
    return response;
}

OpenAIRequest makeRequest(OpenAIRequestType type, char* endpoint, char* data) {
    OpenAIRequest request;
    request.type = type;
    request.endpoint = endpoint;
    request.data = data;

    return request;
}

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("error: not enough memory\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

OpenAIResponse request(OpenAIRequest request) {
    CURL *handle;
    CURLcode res;

    char authentication[23 + strlen(key)];
    snprintf(authentication, 23 + strlen(key), "Authorization: Bearer %s", key);

    char target[27 + strlen(request.endpoint)];
    snprintf(target, 27 + strlen(request.endpoint), "https://api.openai.com/v1%s", request.endpoint);

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    handle = curl_easy_init();
    if (handle) {
        curl_easy_setopt(handle, CURLOPT_URL, target);
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, authentication);
        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

        switch (request.type) {
            case POST: curl_easy_setopt(handle, CURLOPT_POSTFIELDS, request.data); break;
        }

        res = curl_easy_perform(handle);

        if(res != CURLE_OK) {
            return errorResponse(curl_easy_strerror(res));
        }

        OpenAIResponse response;
        response.size = chunk.size;
        response.data = chunk.memory;

        curl_easy_cleanup(handle);
        free(chunk.memory);
        return response;
    }

    return errorResponse("Error: curl not connected.");
}