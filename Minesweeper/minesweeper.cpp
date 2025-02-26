#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include <set>
#include <array>
#include <vector>
#include <map>

// Map containing all the colors and their corresponding numbers
std::map<int, sf::Color> colors = {
    {1, sf::Color(53,108,165)},
    {2, sf::Color(84,124,62)},
    {3, sf::Color(178,70,57)},
    {4, sf::Color(111,35,144)},
    {5, sf::Color(237,147,33)},
    {6, sf::Color(22,151,173)},
    {7, sf::Color(66,67,59)},
    {8, sf::Color(237,147,33)}
};

// Universal variables to be used
int grid[30][16];
bool valid[30][16];
std::set<std::array<int, 2>> display;
sf::RenderWindow window(sf::VideoMode({(1350), (720)}), "Minesweeper");
bool active;
bool game_over;
bool game_win;

// Initializes variables
void init() {

    sf::Image icon;
    if (icon.loadFromFile("sprites/Flag.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    for (int i = 0; i < 480; i++) {
        grid[i % 30][i / 30] = 0;
    }
    for (int i = 0; i < 480; i++) {
        valid[i % 30][i / 30] = true;
    }
    active = false;
    game_over = false;
    game_win = false;
}

// Handles the reveal mechanic in non-bomb cases
void dfsCheck(int x, int y) {
    int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    // Marks the clicked squares
    display.insert({x, y});
    // Uses stack-based depth-first search to check if surrounding squares should be revealed
    std::vector<std::array<int, 2>> todo = {{x, y}};
    while (!todo.empty()) {
        std::array<int, 2> current = todo.back();
        todo.pop_back();
        for (int i = 0; i < 8; i++) {
            int fx = current[0] + dx[i];
            int fy = current[1] + dy[i];
            if (grid[current[0]][current[1]] == 0 && fy >= 0 && fy < 16 && fx >= 0 && fx < 30 && display.find({{fx, fy}}) == display.end()) {
                todo.push_back({{fx, fy}});
                display.insert({fx, fy});
            }
        }
    }
}

// Initializes the game and sets all bomb positions
void gameInit(int x, int y) {
    int dx[] = {1, 1, 1, 0, 0, -1, -1, -1, 0};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1, 0};
    for (int i = 0; i < 9; i++) {
        int fx = x + dx[i];
        int fy = y + dy[i];
        if (fy >= 0 && fy < 16 && fx >= 0 && fx < 30) {
            grid[fx][fy] = -2;
        }
    }

    // Bombs couldn't be placed where the initial click was made nor in immediately adjacent squares
    int bombs_left = 99;
    do {
        int bx = rand() % 30;
        int by = rand() % 16;
        if (grid[bx][by] == 0) {
            grid[bx][by] = -1;
            bombs_left--;
        }
    } while (bombs_left > 0);

    for (int i = 0; i < 480; i++) {
        int gx = i % 30;
        int gy = i / 30;
        if (grid[gx][gy] != -1) {
            int count = 0;
            for (int j = 0; j < 8; j++) {
                int cx = gx + dx[j];
                int cy = gy + dy[j];
                if (grid[cx][cy] == -1 && cy >= 0 && cy < 16 && cx >= 0 && cx < 30) {
                    count++;
                }
            }
            grid[gx][gy] = count;
        }
    }
}

// Makes the game displayable
void renderGrid() {
    int flags_used = 0;

    sf::RectangleShape rectangle({45.f, 45.f});

    sf::Font font;
    font.loadFromFile("G_ari_bd.TTF");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);

    sf::Texture texture;
    texture.loadFromFile("sprites/Flag.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.7f, 0.7f);

    for (int x = 0; x < 30; x++) {
        for (int y = 0; y < 16; y++) {
            if (display.find({x, y}) == display.end()) {
                if ((x + y) % 2 == 0) {
                    rectangle.setFillColor(sf::Color(162,208,73));
                } else {
                    rectangle.setFillColor(sf::Color(169,215,81));
                }
                rectangle.setPosition(sf::Vector2f(x * 45, y * 45));
                window.draw(rectangle);
                if (!valid[x][y]) {
                    sprite.setPosition(x*45, y*45);
                    window.draw(sprite);
                    flags_used += 1;
                }
            } else {
                if ((x + y) % 2 == 0) {
                    rectangle.setFillColor(sf::Color(215,184,153));
                } else {
                    rectangle.setFillColor(sf::Color(228,194,159));
                }
                rectangle.setPosition(sf::Vector2f(x * 45, y * 45));
                window.draw(rectangle);
                if (grid[x][y] == -1) {
                    rectangle.setFillColor(sf::Color::Red);
                    if (game_win) {
                        rectangle.setFillColor(sf::Color::Blue);
                    }
                    window.draw(rectangle);
                    sf::CircleShape circle(15.f);
                    circle.setPosition(sf::Vector2f(x * 45 + 7.5, y * 45 + 7.5));
                    circle.setFillColor(sf::Color::Black);
                    window.draw(circle);
                } else if (grid[x][y] != 0) {
                    text.setString(std::to_string(grid[x][y]));
                    text.setFillColor(colors[grid[x][y]]);
                    sf::FloatRect textRect = text.getLocalBounds();
                    text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f + textRect.top);
                    text.setPosition(x * 45 + 22, y * 45 + 22);
                    window.draw(text);
                }
            }
        }
    }
    window.setTitle("Minesweeper (" + std::to_string(flags_used) + "/99 bombs marked)");
}

// Handles any events from the user
void eventHandler() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Closes the game window if requested
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        // Handles both left and right button clicks to affect the board
        if (event.type == sf::Event::MouseButtonPressed) {
            int square_x = event.mouseButton.x / 45;
            int square_y = event.mouseButton.y / 45;
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (!active) {
                    active = true;
                    gameInit(square_x, square_y);
                }
                if (display.find({square_x, square_y}) == display.end() && valid[square_x][square_y]){
                    dfsCheck(square_x, square_y);
                    if (grid[square_x][square_y] == -1) {
                        game_over = true;
                    } else if (display.size() == 381) {
                        game_win = true;
                    }
                }
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                if (display.find({square_x, square_y}) == display.end()) {
                    valid[square_x][square_y] = !valid[square_x][square_y];
                }
            }
        }
    }
}

// Carries out the end-of-game procedure
void gameOver(std::string message) {
    for (int x = 0; x < 30; x++) {
        for (int y = 0; y < 16; y++) {
            if (grid[x][y] == -1 && display.find({x, y}) == display.end()) {
                display.insert({x, y});
            }
        }
    }
    renderGrid();
    window.display();
    for (int i = 5; i >= 0; i--) {
        window.setTitle(message + " Terminating in " + std::to_string(i) + "...");
        Sleep(1000);
    }
    window.close();
}

int main() {

    init();

    while (window.isOpen()) {
        eventHandler();
        window.clear();
        renderGrid();
        window.display();
        if (game_over) {
            gameOver("Game over!");
        } else if (game_win) {
            gameOver("You win!");
        }
    }
    return 0;
}
