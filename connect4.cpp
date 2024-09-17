#include <iostream>
#include <map>
#include <string>

using namespace std;

class Player{
    public:
    string name;
    char skin;
    int score = 0;
};

void place(char* bruh, int inty, Player p){
    for (int i = 5; i >= 0; i--){
        if (bruh[i*7 + inty - 1] == '_'){
            bruh[i*7 + inty - 1] = p.skin;
            break;
        }
    }
}

void board(char* c){
    cout << " 1 2 3 4 5 6 7 " << endl;
    for (int i = 0; i < 6; i++) {
        cout << "|";
        for (int j = 0; j < 7; j++) {
            cout << c[i*7 + j] << "|";
        }
        cout << endl;
    }
    cout << endl << endl;
}

bool win(char* c){
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 7; x++) {
            if (x <= 3 && c[y * 7 + x] != '_' &&
                c[y * 7 + x] == c[y * 7 + x + 1] &&
                c[y * 7 + x] == c[y * 7 + x + 2] &&
                c[y * 7 + x] == c[y * 7 + x + 3]) {
                return 1;
            } else if (y <= 2 && c[y * 7 + x] != '_' &&
                c[y * 7 + x] == c[(y + 1) * 7 + x] &&
                c[y * 7 + x] == c[(y + 2) * 7 + x] &&
                c[y * 7 + x] == c[(y + 3) * 7 + x]) {
                return 1;
            } else if (x <= 3 && y <= 2 && c[y * 7 + x] != '_' &&
                c[y * 7 + x] == c[(y + 1) * 7 + x + 1] &&
                c[y * 7 + x] == c[(y + 2) * 7 + x + 2] &&
                c[y * 7 + x] == c[(y + 3) * 7 + x + 3]) {
                return 1;
            } else if (x >= 3 && y <= 2 && c[y * 7 + x] != '_' &&
                c[y * 7 + x] == c[(y + 1) * 7 + x - 1] &&
                c[y * 7 + x] == c[(y + 2) * 7 + x - 2] &&
                c[y * 7 + x] == c[(y + 3) * 7 + x - 3]) {
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    string input;
    cout << "How many players shall be playing this round? (2-4)" << endl;
    for (int i = 0; i < 1;){
        cin >> input;
        if (input == "2" || input == "3" || input == "4"){
            i++;
        } else if (input == "1"){
            cout << "I'm afraid that you will need friends to play this game. Please enter a valid number." << endl;
        } else {
            cout << "Please enter a valid number." << endl;
        }
    }
    int playercount = stoi(input);
    Player players [playercount];
    for (int i = 0; i < playercount; i++){
        cout << "Okay, can Player " + to_string(i + 1) + " please enter their username?" << endl;
        cin >> input;
        players[i].name = input;
        for (int j = 0; j < 1;){
            cout << "Okay, can Player " + to_string(i + 1) + " also please enter what skin they would like? (Any single character that hasn't been chosen will do)" << endl;
            cin >> input;
            if (input.length() == 1){
                j++;
            }
            for (Player p : players){
                if (p.skin == input[0]){
                    j = 0;
                    break;
                }
            }
        }
        players[i].skin = input[0];
        cout << "Hello, " + players[i].name + ", your skin will be [" + players[i].skin + "]!" << endl;
    }
    int rounds = 0;
    for (int i = 0; i < 1;){
        char c [42];
        for (int j = 0; j < 42; j++){
            c[j] = '_';
        }
        int turn = rounds;
        for (int k = 0; k < 1;){
            int who = turn % playercount;
            board(c);
            for (int k = 0; k < 1;){
                for (int j = 0; j < 1;){
                    cout << players[who].name << ", please place your chip. (Or enter 'random' to randomize your decision)" << endl;
                    cin >> input;
                    if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "random"){
                        j++;
                    } else {
                        cout << "That is not a valid slot." << endl;
                    }
                }
                if (input == "random"){
                    for (int o; o < 1;){
                        input = to_string((rand() % 7) + 1);
                        if (c[stoi(input) - 1] == '_'){
                            o++;
                        }
                    }
                }
                if (c[stoi(input) - 1] == '_'){
                    k++;
                } else {
                    cout << "This column is unfortunately full. Please choose a different column." << endl;
                }
            }
            place(c, stoi(input), players[who]);
            if (win(c)){
                cout << "Congratulations, " << players[who].name << "! You've won!" << endl;
                players[who].score++;
                board(c);
                k++;
            } else {
                bool b = 1;
                for (char ch : c){
                    if (ch == '_'){
                        b = 0;
                    }
                }
                if (b == 1){
                    k++;
                    cout << endl << endl << "Oh no! It's a cat's game! Meow!" << endl;
                    board(c);

                } else {
                    turn++;
                }
            }
        }
        cout << "Scoreboard:" << endl;
        for (Player p : players){
            cout << p.name << " - " << to_string(p.score) << endl;
        }
        cout << endl;
        for (int o = 0; o < 1;){
            cout << "Would you like to play again? Y/N" << endl;
            cin >> input;
            if (input == "Y" || input == "N"){
                o++;
            } else {
                cout << "Let me ask again:" << endl;
            }
        }
        if (input == "Y"){
            cout << endl << endl << "Okay, have fun!" << endl << endl;
            rounds++;
        } else if (input == "N"){
            cout << "Okay, thanks for playing! :)" << endl;
            i++;
        }
    }
    return 0;
}
