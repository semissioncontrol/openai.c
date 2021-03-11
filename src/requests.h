#ifndef OPENAI_REQUESTS_H
#define OPENAI_REQUESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

typedef enum {
    GET, POST,
} OpenAIRequestType;

typedef struct {
    OpenAIRequestType type;
    char* endpoint;
    char* data;
} OpenAIRequest;

OpenAIResponse request(OpenAIRequest request);
OpenAIRequest makeRequest(OpenAIRequestType type, char* endpoint, char* data);

#endif