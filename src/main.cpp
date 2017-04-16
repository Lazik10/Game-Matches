#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

const int PLAYER_TURN           = 0;
const int COMPUTER_TURN         = 1;

enum Language
{
    ENGLISH,
    CZECH,
    MAX_LANGUAGES,
};

enum Sentences
{
    // Menu
    SELECT_LANGUAGE,
    SELECTED_LANGUAGE,
    HELLO,
    DIFFICULTY,
    NUMBER_OF_MATCHES,
    ERROR_MESSAGE_WRONG_NUMBER_OR_NOT_A_NUMBER,
    START,
    // Player turn
    PLAYERS_TURN,
    PLAYERS_CHOICE,
    YOU_TOOK,
    MATCH,
    MATCHES,
    BETWEEN_ONE_AND_THREE,
    // Computer turn
    COMPUTERS_TURN,
    COMPUTERS_CHOICE,
    ONE_MATCH,
    TWO_MATCHES,
    THREE_MATCHES,
    // Both turns
    THERE_IS,
    THERE_IS_LAST_FOUR,
    NUM_OF_MATCHES,
    REMAINING,
    // Result
    PLAYER_WIN,
    COMPUTER_WIN,
    RESTART,
    // Max sentences
    MAX_SENTENCES,
};

void SetWindowAttributes();
void Intro();
void StartGame();
void RestartGame();
void SelectLanguage();
void CheckForWin();
void ComputerTurn();
void PlayerTurn();
int  PlayerTakeMatches();
void DrawMatches();
void DrawLogo();
string WriteSentence(int numOfSentence, int language = 0);

int m_language;
int m_turn                  = 0;
int m_numberOfMatches       = 0;
int m_difficulty            = 1;
int m_maxTakenMatches       = 3;
int m_playerTakesMatches    = 0;
string m_newGame = "YES";

string writeSentence[MAX_SENTENCES][MAX_LANGUAGES]
{
    { "Select language, type EN for English or CZ for Czech" },
    { "Your selected language is English." , "Vasim zvolenym jazykem je cestina." },
    { "\nHello, welcome in this game called Matches!\n\n"
      "Rules of this game are quiet simple: \n\nYou can take 1-3 matches from the stack"
      " (in one turn) \nand whoever takes the LAST match will loose.",
      "\nAhoj, vitej ve hre jmenem Sirky!\n\n"
      "Pravidla teto hry jsou jednoducha: \n\nMuzes vzit 1-3 sirky z hromadky"
      " (v jednom kole) \na kdokoliv si musi tahnout posledni sirku prohral." },
    { "Select number of difficulty: (1 - easy, 2 - normal, 3 - hard)" , "Zvolte cislo obtiznosti: (1 - lehka, 2 - stredni, 3 - tezka)" },
    { "Select number of matches you would like to play with (Between 20-30)" , "Zvolte s jakym poctem sirek chcete hrat (Mezi 20-30)" },
    { "Please input a number between 20-30!" , "Zadejte prosim cislo mezi 20-30!" },
    { "---   Let the game begin:   ---" , "---   Start hry:   ---" },
    { "PLAYER TURN: " , "TAH HRACE: " },
    { "How many matches do you want to take? (Between 1-" , "Kolik sirek si prejete odebrat? (Mezi 1-" },
    { "You took " , "Odebrali jste " },
    { " match" , " sirku." },
    { " matches.", " sirky." },
    { "Please input a number between 1 - " , "Prosim vlozte cislo mezi 1 - " },
    { "COMPUTER TURN : " , "TAH POCITACE: " },
    { "Computer is going to take " , "Pocitac odebral " },
    { "Computer is going to take 1 match." , "Pocitac prave odebral 1 sirku." },
    { "Computer is going to take 2 matches." , "Pocitac prave odebral 2 sirky." },
    { "Computer is going to take 3 matches." , "Pocitac prave odebral 3 sirky." },
    { "There is ", "Stale je zde " },
    { "There is ", "Stale jsou zde " },
    { " matches." , " sirek."},
    { " Matches remaining: ", "Zbyva sirek: " },
    { "There is one last match left for the computer. Congratulations, you have won!" , "Posledni sirka zbyla na pocitac. Gratuluji, vyhral jsi!" },
    { "There is only one match left for you. \nUnfortunately, computer is smarter than you and won!" , "Zbyla na tebe posledni sirka. \nBohuzel pocitac te prechytracil a vyhral!" },
    { "Do you want to play again? (YES/NO): " , "Chcete hrat znovu? (ANO/NE): " },
};

const int MAX_LOGO_LINES = 6;

string matchesLogoEN[MAX_LOGO_LINES]
{
    { "   _____               __             .__                       " },
    { "  /     \\   _____    _/  |_    ____   |  |__     ____     ______" },
    { " /  \\ /  \\  \\__  \\   \\   __\\ _/ ___\\  |  |  \\  _/ __ \\   /  ___/" },
    { "/    Y    \\  / __ \\_  |  |   \\  \\___  |   Y  \\ \\  ___/   \\___ \\ " },
    { "\\____|__  / (____  /  |__|    \\___  > |___|  /  \\___  > /____  >" },
    { "        \\/       \\/               \\/       \\/       \\/       \\/ " },
};

string matchesLogoCZ[MAX_LOGO_LINES]
{
    { "  _________ .__            __             " },
    { " /   _____/ |__| _______  |  | __  ___.__." },
    { " \\_____  \\  |  | \\_  __ \\ |  |/ / <   |  |" },
    { " /        \\ |  |  |  | \\/ |    <   \\___  |" },
    { "/_______  / |__|  |__|    |__|_ \\  / ____|" },
    { "        \\/                     \\/  \\/     " },
};

// Start the game
int main()
{
    SetWindowAttributes();
    SelectLanguage();

    while (m_newGame == "YES")
    {
        system("CLS");
        Intro();
        StartGame();
    }

    Sleep(10000);
    return 0;
}

void SetWindowAttributes()
{
    // Set Font Size
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 15;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    // Set new Command Prompt window size
    system("MODE 70, 25");
    // Set new Command Prompt position
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, 0, 600, 300, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    // Set new Command Promt window name
    SetConsoleTitle(TEXT("Matches"));
}

// Intro
void Intro()
{
    DrawLogo();
    Sleep(2000);
    cout << WriteSentence(HELLO) << endl << endl;
    Sleep(5000);

    // Implement difficulty somehow?
    //cout << WriteSentence(DIFFICULTY) << endl;
    //cin >> m_difficulty;
}

void SelectLanguage()
{
    string language;
    while (language != "EN" && language != "en" && language != "CZ" && language != "cz")
    {
        cout << WriteSentence(SELECT_LANGUAGE) << endl;
        cin >> language;

        if (language == "EN" || language == "en")
            m_language = ENGLISH;
        else if (language == "CZ" || language == "cz")
            m_language = CZECH;
    }

    cout << WriteSentence(SELECTED_LANGUAGE) << endl;
    cout << endl;

    Sleep(2000);
}

void DrawLogo()
{
    for (int i = 0; i < MAX_LOGO_LINES; i++)
    {
        Sleep(250);
        if (m_language == ENGLISH)
            cout << matchesLogoEN[i] << endl;
        else if (m_language == CZECH)
            cout << matchesLogoCZ[i] << endl;
    }
}

string WriteSentence(int numOfSentence, int language)
{
    language = m_language;
    return writeSentence[numOfSentence][language];
}

void StartGame()
{
    Sleep(2000);
    do
    {
        cout << WriteSentence(NUMBER_OF_MATCHES) << endl;

        // Check if it's a number
        while (!(cin >> m_numberOfMatches))
        {
            cout << WriteSentence(ERROR_MESSAGE_WRONG_NUMBER_OR_NOT_A_NUMBER) << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    // Repeat until number input is greater than minimum required number
    } while (m_numberOfMatches < 20 || m_numberOfMatches > 30);


    cout << endl << WriteSentence(START) << endl << endl;

    while (m_numberOfMatches > 1)
    {
        Sleep(2000);
        if (m_turn == PLAYER_TURN)
            PlayerTurn();
        else ComputerTurn();
    }

    CheckForWin();

    // Ask if we want to restart the game
    RestartGame();
}

void RestartGame()
{
    Sleep(2000);
    string restart;
    while ((m_language == ENGLISH && restart != "YES" && restart != "yes" && restart != "NO" && restart != "no")
        || (m_language == CZECH && restart != "ANO" && restart != "ano" && restart != "NE" && restart != "ne"))
    {
        cout << WriteSentence(RESTART) << endl;
        cin >> restart;

        if (restart == "YES" || restart == "yes" || restart == "ANO" || restart == "ano")
            m_newGame = "YES";
        else m_newGame = "NO";
    }
}

void ComputerTurn()
{
    if (m_numberOfMatches >= 5)
        cout << WriteSentence(COMPUTERS_TURN) << WriteSentence(THERE_IS) << m_numberOfMatches << WriteSentence(NUM_OF_MATCHES) << endl;
    else
        cout << WriteSentence(COMPUTERS_TURN) << WriteSentence(THERE_IS_LAST_FOUR) << m_numberOfMatches << WriteSentence(MATCHES) << endl;
    DrawMatches();
    int takeMatches = 0;
    int modulo = m_numberOfMatches % (m_maxTakenMatches + 1);

    if (m_numberOfMatches <= m_maxTakenMatches + 1)
    {
        takeMatches = m_numberOfMatches - 1;
        cout << WriteSentence(COMPUTERS_CHOICE) << takeMatches << (takeMatches == 1 ? WriteSentence(MATCH) : WriteSentence(MATCHES)) << "  ";
    }
    else
    {
        Sleep(2000);
        switch (modulo)
        {
        case 0:
            cout << WriteSentence(THREE_MATCHES) << "  ";
            takeMatches = 3;
            break;
        case 1:
            // Take random number of matches, since there is no possible option to get to (n_numberOfMatches % (m_maxTakenMatches + 1)) again, so it does't matter
            takeMatches = rand() % 3 + 1;
            if (takeMatches == 1)
                cout << WriteSentence(ONE_MATCH) << "  ";
            else
                cout << WriteSentence(COMPUTERS_CHOICE) << takeMatches << WriteSentence(MATCHES) << "  ";
            break;
        case 2:
            cout << WriteSentence(ONE_MATCH) << "  ";
            takeMatches = 1;
            break;
        case 3:
            cout << WriteSentence(TWO_MATCHES) << "  ";
            takeMatches = 2;
            break;
        default:
            break;
        }
    }

    m_numberOfMatches -= takeMatches;
    cout << WriteSentence(REMAINING) << m_numberOfMatches << endl << endl;

    m_turn = PLAYER_TURN;
}

int PlayerTakeMatches()
{
    int takeMatches;

    while (!(cin >> takeMatches))
    {
        cout << WriteSentence(BETWEEN_ONE_AND_THREE) << m_maxTakenMatches << "!\n";
        cin.clear();
        cin.ignore(100, '\n');
    }

    m_playerTakesMatches = takeMatches;

    return m_playerTakesMatches;
}

void PlayerTurn()
{
    cout << WriteSentence(PLAYERS_TURN) << WriteSentence(THERE_IS) << m_numberOfMatches << WriteSentence(NUM_OF_MATCHES) << endl;
    DrawMatches();

    // Reset for each turn!
    m_playerTakesMatches = 0;

    while (m_playerTakesMatches <= 0 || m_playerTakesMatches > m_maxTakenMatches)
    {
        cout << WriteSentence(PLAYERS_CHOICE) << m_maxTakenMatches << ")" <<endl;
        PlayerTakeMatches();
    }
    m_numberOfMatches -= m_playerTakesMatches;

    cout << WriteSentence(YOU_TOOK) << m_playerTakesMatches << (m_playerTakesMatches == 1 ? WriteSentence(MATCH) : WriteSentence(MATCHES)) 
        << "  " << WriteSentence(REMAINING) << m_numberOfMatches << endl << endl;

    m_turn = COMPUTER_TURN;
}

void CheckForWin()
{
    Sleep(2000);

    if (m_numberOfMatches == 1)
    {
        if (m_turn == PLAYER_TURN)
            cout << WriteSentence(COMPUTER_WIN) << endl << endl;
        else
            cout << WriteSentence(PLAYER_WIN) << endl << endl;
    }
}

void DrawMatches()
{
    for (int i = 0; i < m_numberOfMatches; i++)
    {
        if (i % 10 == 0)
            cout << endl;
        if (i % 5 == 0 && i != 0 && i % 10 != 0)
            cout << " ";
        cout << "| ";
        Sleep(100);
    }

    cout << endl << endl;
}