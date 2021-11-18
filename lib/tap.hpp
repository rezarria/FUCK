#pragma once
#include "diem.hpp"
#include <vector>
#include <iomanip>
#define DA_CHIEU 0
#define DON_CHIEU 1

class Tap : public std::vector<Diem*>
{
private:
    size_t dau;
    size_t diem_gan_nhat();
    bool daTinh;

public:
    using std::vector<Diem*>::push_back;

    Tap();
    void dijkstra();
    void setDau(size_t n);
    void push_back(Diem& diem);
    void clear();
    void chi_tiet();
    void hien_tuyen_duong();
    void xoa(size_t n);
    void reset();
    void danh_sach_chi_phi();
    void noi(size_t a, size_t b, int64_t khoangCach, char mode);
    Diem* layDiem(std::string ten);
    size_t getViTri(Diem* diem);
};

size_t Tap::getViTri(Diem* diem)
{
    for (size_t i = 0; i < size(); i++)
        if (at(i) == diem)
            return i;
    return EOF;
}


void Tap::noi(size_t a, size_t b, int64_t khoangCach, char mode)
{
    switch (mode)
    {
        case 0:
            at(b)->doanDuong[at(a)] = khoangCach;
        case 1:
            at(a)->doanDuong[at(b)] = khoangCach;
            break;
    }
}

Diem* Tap::layDiem(std::string ten)
{
    for (iterator diem = begin(); diem != end(); diem++)
        if ((*diem)->ten == ten)
            return *diem;
    return NULL;
}

void Tap::reset()
{
    dau = INF;
    daTinh = false;
    for (iterator i = begin(); i != end(); i++)
    {
        (*i)->chiPhi = INF;
        (*i)->danhDau = false;
    }
}

void Tap::xoa(size_t n)
{
    Diem* const target = at(n);
    for (size_t i = 0; i < size(); i++)
        at(i)->doanDuong.erase(target);
    erase(begin() + n);
    reset();
}

void Tap::hien_tuyen_duong()
{
    std::cout << "      ";
    for (size_t i = 0; i < size(); i++)
        std::cout << std::setw(5) << at(i)->ten;
    putchar(10);
    putchar(10);
    for (size_t i = 0; i < size(); i++)
    {
        std::cout << std::setw(5) << at(i)->ten << " ";
        for (size_t j = 0; j < size(); j++)
            if (i == j)
                std::cout << std::setw(5) << 0;
            else
                if (at(i)->doanDuong.find(at(j)) != at(i)->doanDuong.end())
                    std::cout << std::setw(5) << at(i)->doanDuong[at(j)];
                else
                    std::cout << "    .";
        putchar(10);

    }

}

void Tap::chi_tiet()
{
    for (iterator diem = begin(); diem != end(); diem++)
        (*diem)->thong_tin();
}

void Tap::clear()
{
    std::vector<Diem*>::clear();
    dau = EOF;
}

void Tap::push_back(Diem& diem)
{
    vector<Diem*>::push_back(&diem);
}

Tap::Tap()
{
    daTinh = false;
    dau = EOF;
}

void Tap::dijkstra()
{
    if (!daTinh && size() && dau != EOF)
    {
        for (size_t i = 0; i < size(); i++)
        {
            size_t viTri = diem_gan_nhat();
            if (viTri != EOF)
            {
                Diem& diem = *at(viTri);
                diem.danhDau = true;
                diem.tinh_toan();
            }
        }
        daTinh = true;
    }
}

size_t Tap::diem_gan_nhat()
{
    int64_t chi_phi_be_nhat = INF;
    size_t diem_be_nhat = EOF;
    if (size() && dau != EOF)
        for (size_t i = 0; i < size(); ++i)
            if (!at(i)->danhDau &&
                chi_phi_be_nhat > at(i)->chiPhi &&
                at(i)->chiPhi != INF)
            {
                chi_phi_be_nhat = at(i)->chiPhi;
                diem_be_nhat = i;
            }
    return diem_be_nhat;
}

void Tap::setDau(size_t n)
{
    if (dau != EOF)
        at(dau)->chiPhi = INF;

    if (n < size())
        dau = n;
    at(n)->chiPhi = 0;
}