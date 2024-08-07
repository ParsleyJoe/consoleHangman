#include <iostream>
#include <string>
#include <array>
#include <random>
#include <vector>

class Game
{
private:
    int attempts = 7;
    std::array<std::string, 10> wordArray = { "snow", "cheek", "energy", "execute", "number", "pig", "whip", "snatch", "turkey", "mayor" };
    std::string word;
    bool isGameActive;

public:
    void welcome()
    {
        // Useless but needed
        std::cout << "Welcome to Console Hangman\n";
        std::cout << "Time to guess a word\n";
        std::cout << "You have " << attempts << " attempts\n";
    }
    Game()
    {
        // Constructor
        guessWord();
        isGameActive = true;
    }
    void guessWord()
    {
        // Gets the word needed to be guessed
        std::random_device rd{};
        std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
        std::mt19937 mt{ ss };
        std::uniform_int_distribution die10{ 1, 10 };

        word = wordArray[die10(mt)];
    }
    void printDashes(std::vector<char>& guessArr)
    {
        // Prints the dashes and the letters guessed right
        if (guessArr.empty())
        {
            for (int i = 0; i < word.length(); i++)
            {
                std::cout << "_";
            }
            std::cout << '\n';
        }
        else
        {
            bool printed = false;
            for (std::string::iterator i = word.begin(); i != word.end(); ++i)
            {
                printed = false;
                for (std::vector<char>::iterator j = guessArr.begin(); j != guessArr.end(); ++j)
                {
                    if (*i == *j)
                    {
                        std::cout << *j;
                        printed = true;
                    }
                }
                if (!printed)
                {
                    std::cout << "_";
                }
            }
            std::cout << '\n';
        }
    }
    void Play()
    {
        // Calls the print dashes function and gets a guess by user
        char guess{};
        std::vector<char> guessArr;

        while (attempts > 0)
        {
            printDashes(guessArr);
            std::cout << "Guess a letter: ";
            std::cin >> guess;

            if (word.find(guess) != word.npos)
            {
                guessArr.push_back(guess);
            }
            else
            {
                attempts--;
                std::cout << "Wrong guess, now you have " << attempts << " attempts\n";
            }
            if (guessedAll(guessArr))
            {
                Win();
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (attempts <= 0)
            gameOver();
    }
    void gameOver()
    {
        std::cout << " GAME OVER!!! \n";
        std::cout << " The word was " << word << " \n";
    }
    bool guessedAll(std::vector<char>& guessArr)
    {
        int foundWords = 0;
        for (std::string::iterator i = word.begin(); i != word.end(); ++i)
        {
            for (std::vector<char>::iterator j = guessArr.begin(); j != guessArr.end(); ++j)
            {
                if (*j == *i)
                {
                    ++foundWords;
                }
            }
        }
        if (foundWords >= word.size())
        {
            return true;
        }
        else
            return false;
    }
    void Win()
    {
        std::cout << "You Win!!\n";
    }
};

int main()
{
    Game game;
    // Select a word from array

    // Welcome and shit
    game.welcome();

    // Start the guessing game
    game.Play();

    return 0;
}
