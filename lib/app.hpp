#include "function.hpp"
#include "MainMenu.hpp"

class App :
    public MainMenu,
    public Function
{
private:
    void update();
public:
    int chay();
};


void App::update()
{
    int luaChon = MainMenu::menu();
    Function::run(luaChon);
}

int App::chay()
{
    Core::running = true;
    do
        update();
    while (running);
    return 0;
}