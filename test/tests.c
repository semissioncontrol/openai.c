#include <openai.h>

int main() {
    char* key = "sk-my-api-key";

    /*
     * Initialize the key using the content in .env
     */
    initOpenAI(key);

    /*
     * Query a list of engines
     */
    OpenAIResponse listOfEngines = engines();
    printf("%s", listOfEngines.data);

    /*
     * Query information about the Davinci engine
     */
    OpenAIResponse davinciEngine = engine("davinci");
    printf("%s", davinciEngine.data);

    /*
     * Start a completion
     */
    OpenAIResponse complete = completion("davinci", "Once upon a time,", 5);
    printf("%s", complete.data);

    return 0;
}