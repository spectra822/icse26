import openai
import time
import os

class OpenAIEmbed:

    def __init__(self, model):

        openai.api_key = os.environ['OPENAI_API_KEY']
        self.model = model

    def embed(self, text):

        from models import ModelException
        
        count = 0
        while True:
            try:
                embedding = openai.Embedding.create(
                    input=text, model=self.model
                )["data"][0]["embedding"]
                break
            except openai.error.InvalidRequestError as e:
                raise ModelException(f"Encountered an error with OpenAI API {e}")
            except (openai.error.RateLimitError, openai.error.ServiceUnavailableError, openai.error.APIError):
                count += 1
                if count >= 5:
                    raise ModelException("Too many retries")
                print("OpenAI Error. Waiting 10 seconds and retrying")
                time.sleep(10)
            except:
                raise ModelException("Unknown error")

        return embedding