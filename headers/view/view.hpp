#ifndef VIEW_CLASS_FUNCTIONS
#define VIEW_CLASS_FUNCTIONS


#include "view/awindow.hpp"
#include <SFML/Graphics.hpp>
#include <list>


class View
{
    sf::RenderWindow main_window_;
    unsigned int width_;
    unsigned int height_;

    std::list<AWindow *> windows_;

public:
    View( unsigned int init_width, unsigned int init_height, const char *label = "hello");
    ~View();

    unsigned int getHeight() const;
    unsigned int getWidth() const;
    sf::RenderWindow &getMainWindow();

    void addWindow( AWindow *new_window);
    AWindow *getWindow();

    void display();
    void clear( sf::Color color = sf::Color::Black);
    void draw();
};


void createWindows( View &view);


#endif // VIEW_CLASS_FUNCTIONS
