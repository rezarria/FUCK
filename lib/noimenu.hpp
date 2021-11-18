#include "menu.hpp"



class NoiMenu
    : public Menu
{
public:
    void danh_sach();
};

void NoiMenu::danh_sach()
{
    std::cout
        << "00. Noi them" << std::endl
        << "01. Xoa noi" << std::endl;
}