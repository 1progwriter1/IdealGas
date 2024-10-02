#ifndef BUTTONS_MANAGER
#define BUTTONS_MANAGER

#include "abutton.hpp"
#include <windows_manager/awindow.hpp>
#include <vector>
#include <math_model/gas_model.hpp>


class ButtonsManager
{
    std::vector<AButton *> buttons_;

public:
    ButtonsManager();
    ~ButtonsManager();

    void addButton( AButton *new_button);
    void drawButtons( sf::RenderWindow &window);

    void proceedButtons( const sf::RenderWindow &window, const sf::Event &event, const sf::Keyboard &key, GasModel *model);
};


#endif // BUTTONS_MANAGER
