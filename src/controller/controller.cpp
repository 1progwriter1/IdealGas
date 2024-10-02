#include <cassert>
#include <controller/controller.hpp>
#include <windows_manager/windows.hpp>


Controller::Controller( View *init_view, GasModel *init_model)
    :   view_( init_view), model_( init_model)
{
    assert( init_view );
    assert( init_model );
}


bool Controller::isOver()
{
    return !view_->getMainWindow().isOpen();
}


void Controller::proceedModel()
{
    for ( auto &cmd : commands_ )
    {
        model_->proceedCmd( cmd);
    }
    commands_.clear();

    model_->moveMolecules();
}


void Controller::addButtonCmd( ButtonCommands cmd)
{
    if ( cmd != CmdNoAction )
        commands_.push_back( cmd);
}


void Controller::createButtons()
{
    for ( auto &window : view_->getWindows() )
    {
        window->createButtons();
    }
}


void Controller::createWindows()
{
    WindowMolecules *molecules = new WindowMolecules( view_->getWidth(), view_->getHeight(), model_->getGas(), this);
    view_->addWindow( molecules);

    WindowTemp *temp = new WindowTemp( 300, 150, 0, view_->getHeight());
    view_->addWindow( temp);
}


void Controller::proceedWindows( const sf::Event &event, const sf::Keyboard &key)
{
    for ( auto &window : view_->getWindows() )
    {
        window->proceedButtons( view_->getMainWindow(), event, key);
    }
}


void Controller::drawWindows()
{
    for ( const auto &window : view_->getWindows() )
    {
        window->draw( view_->getMainWindow());
    }
}
