#ifndef CONTROLLER_FUNCTIONS
#define CONTROLLER_FUNCTIONS


#include <windows_manager/windows_manager.hpp>
#include <math_model/gas_model.hpp>
#include <windows_manager/buttons_manager.hpp>
#include <data.hpp>


class Controller
{
    View *view_;
    GasModel *model_;
    std::vector<ButtonCommands> commands_;

public:
    Controller( View *init_view, GasModel *init_model);
    Controller() = default;

    bool isOver();
    void proceedModel();
    void proceedWindows( const sf::Event &event, const sf::Keyboard &key);
    void addButtonCmd( ButtonCommands cmd);
    void createButtons();
    void createWindows();

};


#endif // CONTROLLER_FUNCTIONS
