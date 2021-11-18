#pragma once
#include "core.hpp"

class Menu :
    public virtual Core
{
private:
    int lua_chon();
protected:
    virtual void danh_sach();
    int menu();
public:
    Menu();
};

Menu::Menu()
{
}

int Menu::lua_chon()
{
    int luaChon;
    danh_sach();
    std::cout << "> ";
    std::cin >> luaChon;
    std::cin.ignore(1);
    return luaChon;
}

int Menu::menu()
{
    return lua_chon();
}

void Menu::danh_sach()
{
    std::cout
        << "00. Hien toan bo thong tin." << std::endl
        << "01. Khoi tao ngau nhien" << std::endl
        << "02. Khoi tao" << std::endl
        << "03. Xoa" << std::endl
        << "04. Noi - Them" << std::endl
        << "05. Noi - Xoa" << std::endl
        << "06. Reset" << std::endl
        << "07. Danh sach chi phi" << std::endl
        << "08. Dat dich" << std::endl
        << "09. Tim duong" << std::endl
        << "10. Thong tin vai diem" << std::endl
        << "11. Thoat" << std::endl;
}