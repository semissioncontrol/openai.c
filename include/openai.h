#ifndef OPENAI_OPENAI_H
#define OPENAI_OPENAI_H

#include <curl/curl.h>

char* key;

typedef enum {
    OK, ERROR,
} OpenAIResponseStatus;

typedef struct {
    OpenAIResponseStatus status;
    size_t size;
    const char* data;
} OpenAIResponse;

void initOpenAI(char* requestKey);
OpenAIResponse engines();
OpenAIResponse engine(char* engine);
OpenAIResponse completion(char* engine, char* prompt, int max_tokens);
OpenAIResponse search(char* engine, char* query, char* documents[]);

#endif