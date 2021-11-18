#include "menu.hpp"

class MainMenu
    : public Menu
{
protected:
    void danh_sach();
};

void MainMenu::danh_sach()
{
    std::cout
        << std::endl
        << "00. Hien toan bo thong tin." << std::endl
        << "01. Khoi tao ngau nhien" << std::endl
        << "02. Sample" << std::endl
        << "03. Hien cac tuyen duong" << std::endl
        << "04. Xoa" << std::endl
        << "05. Khoang cach giua 2 diem" << std::endl
        << "06. Nap tu file" << std::endl
        << "07. Tinh toan" << std::endl
        << "08. Danh sach chi phi" << std::endl
        << "09. Dat diem xuat phat" << std::endl
        << "10. Tim duong" << std::endl
        << "11. Thong tin vai diem" << std::endl
        << "12. Thoat" << std::endl;
}