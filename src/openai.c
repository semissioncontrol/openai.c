#include <stdio.h>
#include <string.h>

#include <openai.h>
#include <math.h>

#include "requests.h"

void initOpenAI(char* requestKey) {
    key = requestKey;
}

OpenAIResponse engines() {
    return request(makeRequest(GET, "/engines", NULL));
}

OpenAIResponse engine(char* engine) {
    char endpoint[10 + strlen(engine)];
    snprintf(endpoint, 10 + strlen(key), "/engines/%s", engine);

    return request(makeRequest(GET, endpoint, NULL));
}

OpenAIResponse completion(char* engine, char* prompt, int max_tokens) {
    char endpoint[21 + strlen(engine)];
    snprintf(endpoint, 21 + strlen(key), "/engines/%s/completions", engine);

    char data[30 + strlen(prompt) + (int)((ceil(log10(max_tokens))+1)*sizeof(char))]; // wtf
    snprintf(data, 30 + strlen(prompt) + (int)((ceil(log10(max_tokens))+1)*sizeof(char)), "{\"prompt\": \"%s\", \"max_tokens\": %d}", prompt, max_tokens);

    return request(makeRequest(POST, endpoint, data));
}

OpenAIResponse search(char* engine, char* query, char** documents) {
    // TODO: To implement.
}