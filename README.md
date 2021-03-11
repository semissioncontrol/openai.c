# openai.c

C wrapper for the OpenAI API.

No dependencies apart from libc and libcurl.

### TODO

 - [ ] Common endpoints:
   - [x] `GET https://api.openai.com/v1/engines`
   - [x] `GET https://api.openai.com/v1/engines/{engine_id}`
   - [x] `POST https://api.openai.com/v1/engines/{engine_id}/completions`
   - [ ] `POST https://api.openai.com/v1/engines/{engine_id}/search`

See [existing bindings in the Python documentation](https://beta.openai.com/docs/api-reference/introduction?lang=python)
for more details.