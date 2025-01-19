#include <iostream>
#include <string>
using namespace std;

std::string caesarDecrypt(const std::string& encryptedText, int shift)
{
    std::string decryptedText = "";

    // 遍历每一个字符
    for (char c : encryptedText)
    {
        // 如果是大写字母
        if (isupper(c))
        {
            decryptedText += char(int(c - shift - 65 + 26) % 26 + 65);
        }
        // 如果是小写字母
        else if (islower(c))
        {
            decryptedText += char(int(c - shift - 97 + 26) % 26 + 97);
        }
        // 如果是非字母字符，保持不变
        else {
            decryptedText += c;
        }
    }

    return decryptedText;
}

int main()
{
    for (int shift = 1; shift <= 25; shift++)
    {
        std::string encryptedText = "DROZKCCGYBNSCDROCAEKBOYPOSQRDIYXO";  // 这是加密文本
        std::string decryptedText = caesarDecrypt(encryptedText, shift);
        std::cout << "解密后的文本: " << decryptedText << std::endl;
    }
    return 0;
}