#include <iostream>
#include <string>
using namespace std;

std::string caesarDecrypt(const std::string& encryptedText, int shift)
{
    std::string decryptedText = "";

    // ����ÿһ���ַ�
    for (char c : encryptedText)
    {
        // ����Ǵ�д��ĸ
        if (isupper(c))
        {
            decryptedText += char(int(c - shift - 65 + 26) % 26 + 65);
        }
        // �����Сд��ĸ
        else if (islower(c))
        {
            decryptedText += char(int(c - shift - 97 + 26) % 26 + 97);
        }
        // ����Ƿ���ĸ�ַ������ֲ���
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
        std::string encryptedText = "DROZKCCGYBNSCDROCAEKBOYPOSQRDIYXO";  // ���Ǽ����ı�
        std::string decryptedText = caesarDecrypt(encryptedText, shift);
        std::cout << "���ܺ���ı�: " << decryptedText << std::endl;
    }
    return 0;
}