#include <iostream>
#include <stdlib.h>
using namespace std;

enum enChoices { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, NoWinner = 3};

struct strRoundInfo{
    short RoundNumber = 0;
    enChoices PlayerChoice = enChoices::Rock;
    enChoices ComputerChoice = enChoices::Rock;
    enWinner RoundWinner = enWinner::NoWinner;
    string WinnerName = "";
};

struct strGameResults {
    short NumberOfRounds = 0;
    short PlayerWinningTimes = 0;
    short ComputerWinningTimes = 0;
    short DrawTimes = 0;
    enWinner FinalWinner = enWinner::NoWinner;
    string FinalWinnerName = "";
};

struct strWinningTimes {
    short PlayerWinningTimes = 0;
    short ComputerWinningTimes = 0;
    short DrawTimes = 0;
};

short ReadRoundsNumber() {

    short RoundsNumber = 0;

    do {
        cout << "How many rounds do you want to play?\n";
        cin >> RoundsNumber;
    } while (RoundsNumber < 1 || RoundsNumber > 10);
    
    return RoundsNumber;
}

enChoices ReadPlayerChoice() {

    short PlayerChoice = 1;

    do {
        cout << "Your choice: [1]:Rock, [2]:Paper, [3]:Scissors? ";
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice > 3);

    return (enChoices)PlayerChoice;
}

short RandomNumber(short from, short to) {

    short RandomNum = 0;

    RandomNum = rand() % (to - from + 1) + from;

    return RandomNum;
}

enChoices GetComputerChoice() {
    
    return (enChoices)RandomNumber(1, 3);
}

enWinner RoundWinner(strRoundInfo RoundInfo) {

    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice) {
        return enWinner::NoWinner;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enChoices::Rock:
        if (RoundInfo.ComputerChoice == enChoices::Paper) {
            return enWinner::Computer;
        }
        break;
    case enChoices::Paper:
        if (RoundInfo.ComputerChoice == enChoices::Scissors) {
            return enWinner::Computer;
        }
        break;
    case enChoices::Scissors:
        if (RoundInfo.ComputerChoice == Rock) {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}

string WinnerToText(enWinner Winner) {

    string arrWinnerName[3] = {"Player", "Computer", "No Winner"};

    return arrWinnerName[Winner - 1];
}

strRoundInfo FillRoundInfo(short RoundNumber) {

    strRoundInfo RoundInfo;

    RoundInfo.RoundNumber = RoundNumber;
    RoundInfo.PlayerChoice = ReadPlayerChoice();
    RoundInfo.ComputerChoice = GetComputerChoice();
    RoundInfo.RoundWinner = RoundWinner(RoundInfo);
    RoundInfo.WinnerName = WinnerToText(RoundInfo.RoundWinner);

    return RoundInfo;
}

string ChoiceToText(enChoices Choice) {

    string arrChoiceName[3] = { "Rock", "Paper", "Scissors" };

    return arrChoiceName[Choice - 1];
}

void PrintRoundResults(strRoundInfo RoundInfo) {
    cout << "\n_______________ Round [" << RoundInfo.RoundNumber << "] _______________\n";
    cout << "\nPlayer choice  : " << ChoiceToText(RoundInfo.PlayerChoice) << "\n";
    cout << "Computer choice: " << ChoiceToText(RoundInfo.ComputerChoice) << "\n";
    cout << "Round Winner   : " << WinnerToText(RoundInfo.RoundWinner) << "\n";
    cout << "_________________________________________\n";
}

void SetWinnerScreenColor(enWinner Winner) {

    switch (Winner)
    {
    case Player:
        system("color 2F");
        break;
    case Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
    }
}

enWinner FinalWinner(short PlayerWinningTimes, short ComputerWinningTimes) {

    if (PlayerWinningTimes == ComputerWinningTimes) {
        return enWinner::NoWinner;
    }
    else if (PlayerWinningTimes > ComputerWinningTimes) {
        return enWinner::Player;
    }
    else {
        return enWinner::Computer;
    }
}

strGameResults FillGameResults(short RoundsNumber, strWinningTimes WinningAndDrawTimes) {

    strGameResults GameResults;

    GameResults.ComputerWinningTimes = WinningAndDrawTimes.ComputerWinningTimes;
    GameResults.PlayerWinningTimes = WinningAndDrawTimes.PlayerWinningTimes;
    GameResults.DrawTimes = WinningAndDrawTimes.DrawTimes;
    GameResults.FinalWinner = FinalWinner(WinningAndDrawTimes.PlayerWinningTimes, WinningAndDrawTimes.ComputerWinningTimes);
    GameResults.FinalWinnerName = WinnerToText(GameResults.FinalWinner);
    GameResults.NumberOfRounds = RoundsNumber;

    return GameResults;
}

strWinningTimes CountWinningAndDrawTimes(enWinner RoundWinner, strWinningTimes WinningAndDrawTimes) {

    switch (RoundWinner)
    {
    case enWinner::Computer:
        WinningAndDrawTimes.ComputerWinningTimes++;
        break;
    case enWinner::Player:
        WinningAndDrawTimes.PlayerWinningTimes++;
        break;
    default:
        WinningAndDrawTimes.DrawTimes++;
        break;
    }

    return WinningAndDrawTimes;
}

strGameResults PlayGame() {

    short RoundsNumber = ReadRoundsNumber();
    strRoundInfo RoundInfo;
    strWinningTimes WinningAndDrawTimes;
    
    for (short Round = 1; Round <= RoundsNumber; Round++) {
        cout << "\nRound [" << Round << "] begins:\n";
        RoundInfo = FillRoundInfo(Round);
        WinningAndDrawTimes = CountWinningAndDrawTimes(RoundInfo.RoundWinner, WinningAndDrawTimes);
        PrintRoundResults(RoundInfo);
        SetWinnerScreenColor(RoundInfo.RoundWinner);
    }

    return FillGameResults(RoundsNumber, WinningAndDrawTimes);
}

string Tabs(short TabsNumber) {

    string t = "";

    for (short counter = 1; counter <= TabsNumber; counter++) {
        t += "\t";
    }

    return t;
}

void ShowGameOverScreen() {
    cout << "\n" << Tabs(2) << "________________________________________________________\n";
    cout << "\n" << Tabs(4) << "+++ G a m e  O v e r +++\n";
    cout << "\n" << Tabs(2) << "________________________________________________________\n\n";
}

void PrintGameResults(strGameResults GameResults) {

    cout << Tabs(2) << "___________________ [Game Results] ___________________\n\n";
    cout << Tabs(2) << "Game Rounds           : " << GameResults.NumberOfRounds << "\n";
    cout << Tabs(2) << "Player winning times  : " << GameResults.PlayerWinningTimes << "\n";
    cout << Tabs(2) << "Computer winning times: " << GameResults.ComputerWinningTimes << "\n";
    cout << Tabs(2) << "Draw times            : " << GameResults.DrawTimes << "\n";
    cout << Tabs(2) << "Winner name           : " << GameResults.FinalWinnerName << "\n\n";
    cout << Tabs(2) << "______________________________________________________\n\n";
}

char AskToReplay() {

    char Replay;

    cout << "Do you want to play again? [ Y / N ] ";
    cin >> Replay;

    return Replay;
}

void ResetScreen() {
    
    system("cls");
    system("color 0F");
}

void StartGame() {

    strGameResults GameResults;
    char Replay;

    do {
        ResetScreen();
        GameResults = PlayGame();
        ShowGameOverScreen();
        PrintGameResults(GameResults);
        Replay = AskToReplay();
    } while (Replay == 'Y' || Replay == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
} 
