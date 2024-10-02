#ifndef VIEW_WINDOWS_FUNCTIONS
#define VIEW_WINDOWS_FUNCTIONS


#include <windows_manager/awindow.hpp>
#include <list>
#include <math_model/amolecule.hpp>
#include <windows_manager/buttons_manager.hpp>
#include <controller/controller.hpp>
#include <deque>


class WindowMolecules : public AWindow
{
    unsigned int width_;
    unsigned int height_;
    CoordinateSys c_sys_;

    std::list<AMolecule *> *gas_;
    std::vector<AButton *> buttons_;

    Controller *ctrl_;

public:
    WindowMolecules( unsigned int init_width, unsigned int init_height, std::list<AMolecule *> *init_gas, Controller *ctrl);
    ~WindowMolecules() = default;

    CoordinateSys &getCSys();
    void draw( sf::RenderWindow &window);
    void createButtons();
    void proceedButtons( const sf::RenderWindow &window, const sf::Event &event, const sf::Keyboard &key);

private:
    void drawButtons( sf::RenderWindow &window);
};


class WindowTemp : public AWindow
{
    unsigned int width_;
    unsigned int height_;

    unsigned int pos_x_;
    unsigned int pos_y_;

    sf::RectangleShape rectangle_;
    std::vector<sf::Vertex> base_lines_;
    std::deque<sf::Vertex> lines_;
    std::vector<sf::Text> marks_;
    sf::Font *font_;

    const size_t MAX_LINES_CNT = 10;
    const size_t STEP_TEMP = 10;

public:
    WindowTemp( unsigned int init_width, unsigned int init_height, unsigned int init_pos_x, unsigned int init_pos_y);
    ~WindowTemp();

    void draw( sf::RenderWindow &window);
    void createButtons() {};
    void proceedButtons( const sf::RenderWindow &window, const sf::Event &event, const sf::Keyboard &key) {};

private:
    void fillInfoToDraw();
    void fillBaseLines();
    void fillMarks();
};


#endif // VIEW_WINDOWS_FUNCTIONS
