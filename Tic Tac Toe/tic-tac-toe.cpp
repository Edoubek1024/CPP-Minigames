#include <iostream>

using namespace std;

bool win(char a, char* l){
    bool b;
    if ((l[0] == a && l[1] == a && l[2] == a) || (l[3] == a && l[4] == a && l[5] == a) || (l[6] == a && l[7] == a && l[8] == a) || (l[0] == a && l[4] == a && l[8] == a) || (l[2] == a && l[4] == a && l[6] == a) || (l[0] == a && l[3] == a && l[6] == a) || (l[1] == a && l[4] == a && l[7] == a) || (l[2] == a && l[5] == a && l[8] == a)){
        b = 1;
    } else {
        b = 0;
    }
    return b;
}

bool cat(char* l){
    bool b = 1;
    for (int i = 0; i < 9; i++) {
        if (l[i] == '-'){
            b = 0;
            break;
        }
    }
    return b;
}

int main(){
    string s;
    int p;
    string play;
    cout<< "Will O or X start first?" << endl;
    for (int i = 0; i < 1;) {
        std::cin >> s;
        if(s == "X" || s == "x"){
            p = 2;
            i++;
        } else if (s == "O" || s == "o"){
            p = 1;
            i++;
        } else {
            cout << "Please insert a proper character." << endl;
        }
    }
    if (p == 1) {
        cout << "Okay, O will start" << endl;
    } else if (p == 2){
        cout << "Okay, X will start" << endl;
    }
    char spot [9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
    for (int j = 0; j < 1;) {
        cout << "   1     2     3" << endl;
        cout << "      |     |     " << endl;
        cout << "a  " << spot[0] << "  |  " << spot[1] << "  |  " << spot[2] << "  " << endl;
        cout << " _____|_____|_____" << endl;
        cout << "      |     |     " << endl;
        cout << "b  " << spot[3] << "  |  " << spot[4] << "  |  " << spot[5] << "  " << endl;
        cout << " _____|_____|_____" << endl;
        cout << "      |     |     " << endl;
        cout << "c  " << spot[6] << "  |  " << spot[7] << "  |  " << spot[8] << "  " << endl;
        cout << "      |     |     " << endl;
        if (p % 2 != 0) {
            cout << "Player O, please enter a space" << endl << "Player O: ";
        } else if (p % 2 == 0){
            cout << "Player X, please enter a space" << endl << "Player X: ";
        }
        for (int i = 0; i < 1;) {
            cin >> play;
            char turn = 'X';
            if (p % 2 != 0) {
                turn = 'O';
            }
            if (play.length() >= 2 && (int(play[0]) % 32 > 0) && (int(play[0]) % 32 < 4) && (int(play[1]) - 48 > 0) && (int(play[1]) - 48 < 4)) {
                int y = (int(play[0]) % 32) - 1;
                int x = (int(play[1]) - 49);
                cout << (y*3 + x) << endl;
                if (spot[y*3 + x] == '-') {
                    i++;
                    spot[y*3 + x] = turn;
                } else {
                    cout << "That space is taken!" << endl;
                }
            } else {
                cout << "Please insert a proper response." << endl;
            }
        }
        p++;
        if (win('X', spot)){
            j++;
            cout << "Congrats! Player X won!" << endl;
        } else if (win('O', spot)){
            j++;
            cout << "Congrats! Player O won!" << endl;
        } else if (cat(spot) && j == 0){
            j++;
            cout << "Cat's game! Meow!" << endl;
        }
    }
    return 0;
}
