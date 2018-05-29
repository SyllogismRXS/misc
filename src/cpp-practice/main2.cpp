#include <string>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

class Palindrome
{
public:
    static bool isPalindrome(const std::string& word)
    {
        for (int i = 0; i < (word.size() / 2); i++) {
            cout << i << "-" << std::toupper(word[i]) << ", " << std::toupper(word[word.size()-1-i]) << endl;
            if (std::toupper(word[i]) != std::toupper(word[word.size()-1-i])) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    std::cout << Palindrome::isPalindrome("Deleveled");
}
