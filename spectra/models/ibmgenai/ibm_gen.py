import os
from genai import Credentials, Client
from genai.schema import (
    TextGenerationParameters,
    TextGenerationReturnOptions,
)
from jinja2 import Template


class PromptTemplates:
    _deepseek: Template = Template(
        "You are an AI programming assistant, utilizing the Deepseek Coder model, developed by Deepseek Company, and you only answer questions related to computer science. For politically sensitive questions, security and privacy issues, and other non-computer science questions, you will refuse to answer.\n### Instruction:\n{{ USER_MESSAGE }}\n### Response:```"
    )
    _mixtral: Template = Template("Question:{{ USER_MESSAGE }}\nAnswer:```")
    _llama: Template = Template(
        "<|begin_of_text|><|start_header_id|>user<|end_header_id|>\n\n{{ USER_MESSAGE }}<|eot_id|><|start_header_id|>assistant<|end_header_id|>```"
    )
    _codellama: Template = Template("[INST]\n{{ USER_MESSAGE }}\n[/INST]```")

    @classmethod
    def get_prompt_for_model(cls, model: str, message: str) -> str:
        """Given a model, return the template for that model

        Args:
            model (str): The model name (deepseek, mixtral, llama, codellama)
            message (str): The message to be used in the template

        Returns:
            str: The filled prompt template for the model
        """
        assert message is not None, "Message cannot be None"

        if "deepseek" in model:
            template: Template = PromptTemplates._deepseek
        elif "llama" in model and "codellama" not in model:
            template: Template = PromptTemplates._llama
        elif "codellama" in model:
            template: Template = PromptTemplates._codellama
        elif "mixtral" in model:
            template: Template = PromptTemplates._mixtral
        else:
            raise ValueError(f"Unknown model: {model}")
        return template.render(USER_MESSAGE=message)


class IBMGenAI:

    def __init__(self, model):
        self.model = model
        self.client = Client(credentials=Credentials(api_key=os.environ["GENAI_KEY"]))

    def gen(self, messages, temperature=0, top_k=1) -> list[str]:
        """
        Generate a response given a list of messages

        Args:
            messages (list[dict]): List of messages
            temperature (float, optional): The temperature for sampling. Defaults to 0.
            top_k (int, optional): The number of responses to generate. Defaults to 1.

        Returns:
            list[str]: List of generated responses

        Notes:

        This is what the messages should look like:
        + messages: [{'role': 'system', 'content': 'You are an intelligent code assistant'},
                     {'role': 'user', 'content': 'Translate this program...'}]
        """

        assert (
            top_k != 1 and temperature == 0
        ), "Top k sampling requires a non-zero temperature"

        prompt = PromptTemplates.get_prompt_for_model(
            self.model, messages[-1].get("content", None)
        )

        codegen_params = TextGenerationParameters(
            max_new_tokens=4096,
            min_new_tokens=20,
            temperature=temperature,
            decoding_method="sample",
            return_options=TextGenerationReturnOptions(
                input_text=False,
            ),
        )

        for response in self.client.text.generation.create(
            model_id=self.model,
            inputs=top_k * [prompt],
            parameters=codegen_params,
        ):
            response_text = response.results
            if len(response_text):
                return [response_text[0].generated_text]

        # TODO: Top-k -> if above doens't work, try to iterate k times...
