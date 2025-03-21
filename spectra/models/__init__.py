from .openai import OpenAIGen, OpenAIEmbed
from .google import GoogleGen
from .claude import ClaudeGen
from .ibmgenai import IBMGenAI
from dotenv import load_dotenv

load_dotenv()


class ModelException(Exception):
    pass


def get_model_from_name(name):

    if name == "gpt4":
        return OpenAIGen(model="gpt-4-0125-preview")
    elif name == "gpt4o":
        return OpenAIGen(model="gpt-4o-2024-05-13")
    elif name == "gpt3":
        return OpenAIGen(model="gpt-3.5-turbo")
    elif name == "gemini":
        return GoogleGen(model="gemini-1.0-pro")
    elif name == "claude":
        return ClaudeGen(model="claude-3-opus-20240229")
    elif name == "embedding":
        return OpenAIEmbed(model="text-embedding-3-large")

        # Locally hosted models
    elif name == "llama70b":  # 70B
        return IBMGenAI(model="meta-llama/llama-3-70b")
    elif name == "llama8b":  # 8B
        return IBMGenAI(model="meta-llama/llama-3-8b")
    elif name == "codellama34b":  # 34B
        return IBMGenAI(model="codellama/codellama-34b-instruct")
    elif name == "deepseek":  # 34B
        return IBMGenAI(model="deepseek-ai/deepseek-coder-33b-instruct")
    elif name == "mixtral":  # 7x8 = 56B
        return IBMGenAI(model="mistralai/mixtral-8x7b-instruct-v01")
    else:
        raise NotImplementedError("Unknown model name")


__all__ = [
    "OpenAIGen",
    "GoogleGen",
    "ClaudeGen",
    "OpenAIEmbed",
    "ModelException",
    "get_model_from_name",
    "IBMGenAI",
]
