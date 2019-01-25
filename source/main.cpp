// Copyright 2019 AndreevSemen
#include <sstream>
#include <Request.hpp>
#include <Response.hpp>
#include <Skill.hpp>
#include <decryption.hpp>
#include <encryption.hpp>

std::string GetPrefix(const std::string&);
__uint32_t GetKey(const std::string&);
std::string GetText(const std::string&);

void CryptoCallback(const Alice::Request& request,
                    Alice::Response& response)
{
    if (request.RequestType() == Alice::Request::Type::SimpleUtterance)
    {
        std::string title;
        if (request.Command() == "")
        {
            title = "Привет!\n"
                    "Чтобы зашифровать текст, введите сначала ключ шифрования "
                    "(он должен занимать ровно 8 первых символов текста), а затем текст.\n"
                    "Чтобы расшифровать ранее зашифрованный текст, введите ключ, "
                    "аналогично, как для шифрования, и выданый при шифровании текст.";
            Alice::Button endingSessionButton("Пока!", {"end"}, false);
            response.PushButton(endingSessionButton);
        } else {
            title = "Выберете действие с помощью соответсвующей кнопки";
            Alice::Button encryptionButton("Шифруй", {"encry " + request.Command()}, true);
            Alice::Button decryptionButton("Расшифровывай", {"decry " + request.Command()}, true);
            response.PushButton(encryptionButton);
            response.PushButton(decryptionButton);
        }
        response.SetText(title);
    } else {
        if (request.Payload().dump() == "end")
        {
            response.SetEndSession(true);
        } else {
            std::string json = request.Payload().dump();
            std::string prefix = GetPrefix(json);
            __uint32_t key = GetKey(json);
            std::string text = GetText(json);
            if (prefix == "encry")
            {
                text = Encryption(text, key);
            } else if (prefix == "decry") {
                text = Decryption(text, key);
            }
            response.SetText(text);
        }
    }
}

int main()
{
    Skill s;
    s.SetCallback(CryptoCallback);
    s.Run();
    return 0;
}

std::string GetPrefix(const std::string& json)
{
    std::string prefix;
    for (size_t i = 0; json[i] != ' '; ++i)
    {
        prefix += json[i];
    }
    return prefix;
}

__uint32_t GetKey(const std::string& json)
{
    size_t index = 0;
    for (;json[index] != ' '; ++index);
    ++index;
    std::stringstream stream;
    for (size_t i = 0; i < 8; ++index, ++i)
    {
        stream << std::hex << json[index];
    }
    __uint32_t key = 0;
    stream >> key;
    return key;
}

std::string GetText(const std::string& json)
{
    std::string text;
    size_t index = 0;
    for (;json[index] != ' '; ++index);
    ++index;
    for (size_t i = 0; i < 8; ++index, ++i);
    for (;json[index] != 0; ++index)
    {
        text += json[index];
    }
    return text;
}

