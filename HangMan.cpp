#include <iostream>
#include <string>

using namespace std;

int MAX_BAD_GUESSES;

// Wordlist for player to guess
const string WORD_LIST[] = {"angle", "ant", "apple", "arch", "arm", "army",
"baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry","bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
"brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
"cake", "camera", "card", "cart", "carriage", "cat", "chain", "cheese", "chest",
"chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
"cow", "cup", "curtain", "cushion",
"dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
"face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
"foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
"hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
"hospital", "house", "island", "jewel", "kettle", "key", "knee", "knife", "knot",
"leaf", "leg", "library", "line", "lip", "lock",
"map", "match", "monkey", "moon", "mouth", "muscle",
"nail", "neck", "needle", "nerve", "net", "nose", "nut",
"office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
"pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
"rail", "rat", "receipt", "ring", "rod", "roof", "root",
"sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
"shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
"square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
"store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
"toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
"wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm",};
const int WORD_COUNT = sizeof(WORD_LIST)/sizeof(string);
// cout hangman
const string FIGURE[] = 
{" ------------- \n"
" | \n"
" | \n"
" | \n"
" | \n"
" | \n"
" ----- \n", 
" ------------- \n"
" |           | \n"
" | \n"
" | \n"
" | \n"
" | \n"
" ----- \n", 
" ------------- \n"
" |           | \n"
" |           O \n"
" | \n"
" | \n"
" | \n"
" ----- \n", 
" ------------- \n"
" |           | \n"
" |           O \n"
" |           | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |          /| \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |          /|\\ \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |          /|\\ \n"
" |          / \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |          /|\\ \n"
" |          / \\ \n"
" | \n"
" ----- \n",};

string initGuessedWord(int answerWordLength);
string choseWord();
void renderHangMan(string guessedWord, int badGuessCount);
char readPlayerGuess();
bool contain(string answerWord, char playerGuess);
string update(string guessedWord, string answerWord, char playerGuess);
void playHangMan();
bool replayHangMan();
void selectMode();

int main()
{
    bool replay = true;
    do
    {
        playHangMan();
        replay = replayHangMan();
    } while (replay == true);
    cout << "Thanks, have a nice day!";
    return 0;
}

void selectMode()
{
    char playerSelectMode;
    cout << "Welcome to Hangman" << endl;
    cout << "CopyRight by pknguyendev" << endl << "---------" << endl << endl;
    cout << "Please Select mode you want to play" << endl;
    cout << "Select E to play EASY mode" << endl << "Select M to play MEDIUM mode" << endl << "Select H to play Hard mode" << endl;
    cout << "[E/M/H]?: ";
    do
    {
        cin >> playerSelectMode;
    } while (playerSelectMode != 'E' && playerSelectMode != 'M' && playerSelectMode != 'H');
    
    if(playerSelectMode == 'E')
        MAX_BAD_GUESSES = 8;
    if(playerSelectMode == 'M')
        MAX_BAD_GUESSES = 6;
    if(playerSelectMode == 'H')
        MAX_BAD_GUESSES = 44;

}
string choseWord()
{
    int randomIndex = rand()%WORD_COUNT;
    return WORD_LIST[randomIndex];
}
string initGuessedWord(int answerWordLength)
{
    string guessedWord = string(answerWordLength, '_');
    return guessedWord;
}
string update(string guessedWord, string answerWord, char playerGuess)
{
    for(int i = 0; i < guessedWord.length(); i++)
    {
        if(answerWord[i] == playerGuess)
            guessedWord[i] = playerGuess;
    }
    return guessedWord;
}
char readPlayerGuess()
{
    cout << "Please enter the character you guess: ";
    char playerGuess;
    cin >> playerGuess;
    return playerGuess;
}
void renderHangMan(string guessedWord, int badGuessCount)
{
    cout << FIGURE[badGuessCount] << endl;
    cout << "The answer word: " << guessedWord << endl;
    cout << "Number of wrong guesses: " << badGuessCount << endl;
}
bool contain(string answerWord, char playerGuess)
{
    for(int i = 0; i < answerWord.length(); i++)
        if(playerGuess == answerWord[i])
            return true;
    return false;
}
void playHangMan()
{
    string answerWord = choseWord();
    string guessedWord = initGuessedWord(answerWord.length());
    int badGuessCount = 0;
    selectMode();
    cout << endl << "Your Max bad guess turn is: " << MAX_BAD_GUESSES << endl;
    do
    {
        renderHangMan(guessedWord, badGuessCount);
        char playerGuess = readPlayerGuess();
        if(contain(answerWord, playerGuess))
            guessedWord = update(guessedWord, answerWord, playerGuess);
        else
            badGuessCount++;
    } while (badGuessCount < MAX_BAD_GUESSES && answerWord != guessedWord);
    
    renderHangMan(guessedWord, badGuessCount);
    if(badGuessCount < MAX_BAD_GUESSES)
        cout << "Congratulation! You win!";
    else cout << "You lost. The correct answer is " << answerWord << endl << endl;
}

bool replayHangMan()
{
    cout << "Do you want to play again?" << endl;
    char selectReplayOption;
    do
    {
    cout << "Select Y to play again" << endl << "Select N to stop" << endl << "[Y/N]?:";
    cin >> selectReplayOption;
    } while (selectReplayOption != 'Y' && selectReplayOption != 'N');
    
    if(selectReplayOption == 'Y')
        return true;
    return false;
}