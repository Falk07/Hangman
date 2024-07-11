#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<string> words = {"programming", "hangman", "puzzle", "challenge", "random"};

void displayWord(const string &word, const vector<bool> &guessed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool isWordGuessed(const vector<bool> &guessed) {
    return all_of(guessed.begin(), guessed.end(), [](bool b) { return b; });
}

void playGame() {
    srand(static_cast<unsigned int>(time(nullptr)));
    string word = words[rand() % words.size()];
    vector<bool> guessed(word.length(), false);
    vector<char> incorrectGuesses;
    int maxIncorrectGuesses = 6;

    cout << "Welcome to Hangman!" << endl;

    while (incorrectGuesses.size() < maxIncorrectGuesses) {
        cout << "Word: ";
        displayWord(word, guessed);

        cout << "Incorrect guesses: ";
        for (char c : incorrectGuesses) {
            cout << c << " ";
        }
        cout << endl;

        cout << "Guess a letter: ";
        char guess;
        cin >> guess;

        if (find(word.begin(), word.end(), guess) != word.end()) {
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] == guess) {
                    guessed[i] = true;
                }
            }
            if (isWordGuessed(guessed)) {
                cout << "Congratulations! You've guessed the word: " << word << endl;
                return;
            }
        } else {
            if (find(incorrectGuesses.begin(), incorrectGuesses.end(), guess) == incorrectGuesses.end()) {
                incorrectGuesses.push_back(guess);
            }
            cout << "Incorrect! You have " << maxIncorrectGuesses - incorrectGuesses.size() << " guesses left." << endl;
        }
    }

    cout << "Game Over! The word was: " << word << endl;
}

int main() {
    char playAgain;
    do {
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y');
    return 0;
}
