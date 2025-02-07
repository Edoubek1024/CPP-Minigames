#include <SFML/Graphics.hpp>
#include <windows.h>
#include <SFML/Window.hpp>
#include <list>
#include <tuple>
#include <optional>

// Direction enum makes later code simple and (no pun intended) direct
enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Width, heigh, and tick rate of the board are initialized in an easily editable way
const int WIDTH = 17;
const int HEIGHT = 15;
int SPEED = 100;

// Direction enum that will be used throughout following functions
Direction direction;

// This function will load the map visual for the user
void loadMap(sf::RenderWindow& window, int arr[WIDTH][HEIGHT]) {
    // The exact colors that will be used in the board
    sf::Color GRASS(162, 208, 73);
    sf::Color HEAD(70, 117, 233);
    sf::Color APPLE = sf::Color::Red;
    // `rectangle` serves as a paintbrush for the map's pixels
    sf::RectangleShape rectangle({50.f, 50.f});
    // Loops through all pixels and colors them accordingly
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            rectangle.setPosition(sf::Vector2f(i * 50.f, j * 50.f));
            if (arr[i][j] == 0) {
                rectangle.setFillColor(GRASS);
            } else if (arr[i][j] == 1) {
                rectangle.setFillColor(HEAD);
            } else if (arr[i][j] == 3) {
                rectangle.setFillColor(APPLE);
            }
            window.draw(rectangle);
        }
    }
}

// This function will load the tail visual for the user
void loadTail(sf::RenderWindow& window, int arr[WIDTH][HEIGHT], std::list<std::tuple<int, int>>& tail) {
    // `rectangle` serves as a paintbrush for the map's pixels
    sf::RectangleShape rectangle({50.f, 50.f});
    // Loops through and paints each pixel of the tail
    for (int i = 0; i < tail.size(); i++) {
        auto it = tail.begin();
        std::advance(it, i);
        std::tuple<int, int> piece = *it;
        rectangle.setPosition(sf::Vector2f(std::get<0>(piece) * 50.f, std::get<1>(piece) * 50.f));
        // Applies a gradient to the snake's appearance, going from light blue at the head to dark blue at the end
        rectangle.setFillColor(sf::Color(15 + (i * 55 / tail.size()), 
                                        61 + (i * 56 / tail.size()), 
                                        141 + (i * 92 / tail.size())));
        window.draw(rectangle);
    }
}

// The event handler handles any events from the user (moving or exiting)
bool eventHandler(sf::RenderWindow& window) {
    // The `moved` boolean ensures that the user can only move in one direction per tick
    bool moved = false;
    while (const std::optional event = window.pollEvent()) {
        // Closes the window upon pressing the exit button
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>(); keyPressed && !moved) {
            // Changes the direction enum when the user makes a movement appropriately
            if ((keyPressed->scancode == sf::Keyboard::Scancode::W 
                || keyPressed->scancode == sf::Keyboard::Scancode::Up)&& direction != DOWN) {
                direction = UP;
                moved = true;
            } else if ((keyPressed->scancode == sf::Keyboard::Scancode::A 
                || keyPressed->scancode == sf::Keyboard::Scancode::Left) && direction != RIGHT) {
                direction = LEFT;
                moved = true;
            } else if ((keyPressed->scancode == sf::Keyboard::Scancode::S 
                || keyPressed->scancode == sf::Keyboard::Scancode::Down) && direction != UP) {
                direction = DOWN;
                moved = true;
            } else if ((keyPressed->scancode == sf::Keyboard::Scancode::D 
                || keyPressed->scancode == sf::Keyboard::Scancode::Right) && direction != LEFT) {
                direction = RIGHT;
                moved = true;
            }
        }
    }
    return moved;
}

// Changes the position of the head of the snake and checks if the user has lost the game
void changeHead(sf::RenderWindow& window, int& x, int& y, int board[WIDTH][HEIGHT]) {
    board[x][y] = 0;
    switch (direction) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case DOWN: y++; break;
        case UP: y--; break;
    }
    // Closes the game upon losing
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        window.close();
    }
}

// Manages the tail growth and/or movement as well as handles any interaction with the apple
void move(sf::RenderWindow& window, int& score, std::list<std::tuple<int, int>>& tail, int board[WIDTH][HEIGHT], int& x, int& y) {
    if (board[x][y] != 3) {
        auto [oldX, oldY] = tail.front();
        board[oldX][oldY] = 0;
        tail.pop_front();
    } else {
        int appleX, appleY;
        do {
            appleX = rand() % WIDTH;
            appleY = rand() % HEIGHT;
        } while (board[appleX][appleY] > 0);
        board[appleX][appleY] = 3;
        score++;
        window.setTitle(("Snake Game (Score: " + std::to_string(score) + ")"));
    }
    // Closes if snake runs into the wall but moves head otherwise
    if (board[x][y] == 2) {
        window.close();
    } else {
        board[x][y] = 1;
    }
}


int main() {
    // This renderwindow is what will be used to display the game to the user
    sf::RenderWindow window(sf::VideoMode({(WIDTH * 50), (HEIGHT * 50)}), "Snake Game (Score: 0)");

    // The 2D array `board` is what will keep track of everything within the game
    // A pixel set to 0 is empty,
    // A pixel set to 1 is the snake's head
    // A pixel set to 2 is a part of the snake's tail
    // A pixel set to 3 is an apple (what the user is supposed to collect)
    int board[WIDTH][HEIGHT];
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            board[i][j] = 0;
        }
    }

    // Initializes variables for the appropriate start of the game
    int x = 5, y = 7;
    board[10][7] = 3;
    direction = RIGHT;
    bool moved = false;
    int score = 0;
    // A list of tuples (x,y) for each part of the tail makes painting and growth much easier
    std::list<std::tuple<int, int>> tail = {{5, 7}, {4, 7}};

    // Keeps the game running
    while (window.isOpen()) {
        // Checks for events
        bool moved = eventHandler(window);
        // Adds a position to the tail
        tail.push_back(std::make_tuple(x, y));
        // Changes the head position and checks if the user has lost the game
        changeHead(window, x, y, board);
        // Handles the tail movement/growth
        move(window, score, tail, board, x, y);
        // Officially sets all parts of the tail
        for (std::tuple<int, int> i : tail) {
            board[std::get<0>(i)][std::get<1>(i)] = 2;
        }
        // Paints the game for the user
        window.clear();
        loadMap(window, board);
        loadTail(window, board, tail);
        window.display();
        moved = false;
        Sleep(SPEED);
    }
}
