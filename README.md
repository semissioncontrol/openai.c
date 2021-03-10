# openai.c

C wrapper for the OpenAI API

### Dependencies
 - [ ] `libcurl`

### TODO

 - [ ] Way to pass authentication key to request
 - [ ] Common endpoints:
   - [ ] `GET https://api.openai.com/v1/engines`
   - [ ] `GET https://api.openai.com/v1/engines/{engine_id}`
   - [ ] `POST https://api.openai.com/v1/engines/{engine_id}/completions`
   - [ ] `POST https://api.openai.com/v1/engines/{engine_id}/completions/browser_stream`
   - [ ] `POST https://api.openai.com/v1/engines/{engine_id}/search`

See [existing bindings in the Python documentation](https://beta.openai.com/docs/api-reference/introduction?lang=python)
for more details.