#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int FromHex(const std::string& s) { return strtoul(s.c_str(), NULL, 16); }

std::string FromHexToAcsii(std::vector<int> arr)
{
    std::string result = "";

    for (const auto& a : arr)
    {
        result.push_back((char)a);
    }
    return result;
}

std::string Deciper(std::string hex)
{
    std::vector<int> vec;

    for (int i = 0; i < hex.length() - 1; i+=2)
    {
        vec.push_back(FromHex(hex.substr(i, 2)));
    }

    return FromHexToAcsii(vec);
}

std::string XORText(std::string text1, std::string text2)
{
    int len = text1.size() < text2.size() ? text1.size() : text2.size();
    std::string result = "";
    for (int i = 0; i < len; i++)
    {
        result.push_back(text1[i] ^ text2[i]);
    }

    return result;
}

int main()
{
    std::ifstream file;
    file.open("ciper.txt");

	std::string str_to_compare = Deciper("280dc9e47f3352c307f6d894ee8d534313429a79c1d8a6021f8a8eabca919cfb685a0d468973625e757490daa981ea6b");
    std::string purpose_key = XORText("For who would bear the whips and scorns of time,", str_to_compare);

    if (file.is_open())
    {
        std::string line;
        int i = 1;
        while (std::getline(file, line))
        {
            std::cout << i;
            std::cout << " - ";
            std::cout << XORText(purpose_key, Deciper(line)) << std::endl;
            i++;
        }
        file.close();
    }
}