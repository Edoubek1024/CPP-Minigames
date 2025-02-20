#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <map>

// The colors of the possible squares within the game
std::map<int, sf::Color> colors = {
    {2, sf::Color(231, 209, 186)},
    {4, sf::Color(225, 193, 158)},
    {8, sf::Color(230, 153, 71)},
    {16, sf::Color(239, 131, 17)},
    {32, sf::Color(239, 91, 17)},
    {64, sf::Color(239, 54, 17)},
    {128, sf::Color(239, 232, 17)},
    {4096, sf::Color(25, 25, 13)},
    {0, sf::Color(212,202,190)}
};
// Using an enum to describe directions makes things much more clear
enum Direction { LEFT, RIGHT, UP, DOWN };
// The score of the game will be displayed in the title of the window
sf::RenderWindow window(sf::VideoMode({(800), (800)}), "2048 (Score: 0)");
// The score is stored in an int and all block values are stored in a 2D array
int score;
int grid[4][4];

// Initialize variables to be used throughout functions
void init() {
    for (int i = 0; i < 16; i++) {
        grid[i % 4][i / 4] = 0;
    }
    int score = 0;
    // All games start with 2 randomly placed 2 blocks
    for (int i = 0; i < 2; i ++) {
        while (true) {
            int place = rand() % 16;
            if (grid[place % 4][place / 4] == 0) {
                grid[place % 4][place / 4] = 2;
                break;
            }
        }
    }
}

// This function makes the move specified by the user
void move(Direction direction) {
    // Keeping track of which squares have been finalized is extremely important
    bool checks[4][4];
    for (int c = 0; c < 16; c++) {
        checks[c % 4][c / 4] = false;
    }
    // Keeping track of if something has happened prevents new blocks spawning from invalid moves
    bool something = false;
    int dx = (direction == RIGHT) - (direction == LEFT);
    int dy = (direction == DOWN) - (direction == UP);
    // Loops through the rows or columns and finds the end result of each move
    for (int i = 0; i < 4; i++) {
        bool moved;
        do {
            moved = false;
            for (int j = (dx + dy) > 0 ? 2 : 1; (dx + dy) > 0 ? j >= 0 : j < 4; j -= (dx + dy)) {
                int x = (dx == 0) ? i : j;
                int y = (dy == 0) ? i : j;
                int fx = (x + dx);
                int fy = (y + dy);
                if (grid[x][y] != 0 && grid[x][y] == grid[fx][fy] && !checks[x][y] && !checks[fx][fy]) {
                    grid[fx][fy] *= 2;
                    score += grid[fx][fy];
                    grid[x][y] = 0;
                    checks[fx][fy] = true;
                    checks[x][y] = false;
                    moved = true;
                    something = true;
                } else if (grid[x][y] != 0 && grid[fx][fy] == 0) {
                    grid[fx][fy] = grid[x][y];
                    grid[x][y] = 0;
                    moved = true;
                    something = true;
                }
            }
        } while (moved);
    }
    // Spawns a new block if the move is valid
    if (something) {
        int four = std::rand() % 10;
        int new_val = (four == 0) ? 4 : 2;
        while (true) {
            int place = rand() % 16;
            if (grid[place % 4][place / 4] == 0) {
                grid[place % 4][place / 4] = new_val;
                break;
            }
        }
    }
}

// Renders the game to be displayed to the viewer
void renderGrid() {
    sf::RectangleShape rectangle({200.f, 200.f});
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            rectangle.setPosition(sf::Vector2f(x * 200, y * 200));
            int state = grid[x][y];
            if (state >= 4096) {
                rectangle.setFillColor(colors[4096]);
            } else if (state >= 128) {
                rectangle.setFillColor(colors[128]);
            } else {
                rectangle.setFillColor(colors[state]);
            }
            window.draw(rectangle);
            if (state != 0) {
                sf::Font font;
                font.loadFromFile("G_ari_bd.TTF");
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(grid[x][y]));
                text.setCharacterSize(80);
                text.setFillColor(sf::Color::White);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f + textRect.top);
                text.setPosition(x * 200 + 100, y * 200 + 100);
                window.draw(text);
            }
        }
    }
    sf::RectangleShape lineh({800.f, 14.f});
    sf::RectangleShape linev({14.f, 800.f});
    linev.setFillColor(sf::Color(186,173,164));
    lineh.setFillColor(sf::Color(186,173,164));
    for (float i : {-7.f, 193.f, 393.f, 593.f, 793.f}) {
        lineh.setPosition(0.f, i);
        linev.setPosition(i, 0.f);
        window.draw(lineh);
        window.draw(linev);
    }
    window.setTitle("2048 (Score: " + std::to_string(score) + ")");
}
// Handles all events from the user
void eventHandler() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Ensures the SFML window closes when requested
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // Takes in move requests from the user through key usage
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
                move(LEFT);
            } else if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                move(UP);
            } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                move(DOWN);
            } else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                move(RIGHT);
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

int main() {
    
    init();

    while (window.isOpen()) {
        eventHandler();
        window.clear();
        renderGrid();
        window.display();
    }
}
