#pragma once
#include <string>
#include <map>
#include <iostream>
#include <stack>
#define INF INT64_MAX
namespace _tmp
{
    size_t id = 0;
};



class Diem
{
private:
    std::string ten;
    bool danhDau;
    std::map<Diem*, int64_t> doanDuong;
    Diem* denTu;
    int64_t chiPhi;



public:
    Diem(int64_t chiPhi = INF, std::string ten = "");
    Diem& noi(Diem& diem, int64_t khoangCach);
    void tinh_toan();
    void thong_tin();
    std::stack<Diem*> tim_duong();
    std::string get_ten();
    int64_t get_chi_phi();
    int64_t doan_duong(Diem* diem);

    friend class Tap;
};

int64_t Diem::doan_duong(Diem* diem)
{
    if (doanDuong.find(diem) != doanDuong.end())
        return doanDuong[diem];
    else
        return INF;
}

int64_t Diem::get_chi_phi()
{
    return chiPhi;
}

void Diem::thong_tin()
{
    std::cout
        << "Ten      : " << ten << std::endl
        << "Danh dau : " << (danhDau ? "True" : "False") << std::endl
        << "Chi phi  : " << (chiPhi == INF ? "INF" : std::to_string(chiPhi)) << std::endl
        << "Den tu   : " << (denTu ? denTu->ten : "NULL") << std::endl
        << "Noi den  : ";
    if (doanDuong.size())
        for (std::map<Diem*, int64_t>::const_iterator i = doanDuong.cbegin(); i != doanDuong.cend(); i++)
        {
            const Diem& diem_ke = *i->first;
            int64_t khoangCach = i->second;
            std::cout << "(" << diem_ke.ten << "|" << khoangCach << ")  ";
        }
    else
        std::cout << "NULL";
    puts("\n\n");

}

std::string Diem::get_ten()
{
    return ten;
}

Diem::Diem(int64_t chiPhi, std::string ten)
{
    this->chiPhi = chiPhi;
    denTu = nullptr;
    danhDau = false;
    if (ten == "")
    {
        this->ten = std::to_string(_tmp::id);
        _tmp::id++;
    }
    else
        this->ten = ten;
}

Diem& Diem::noi(Diem& diem, int64_t khoangCach)
{
    if (doanDuong.find(&diem) != doanDuong.end())
        doanDuong[&diem] = khoangCach;
    return *this;
}

std::stack<Diem*> Diem::tim_duong()
{
    std::stack<Diem*> duong;
    Diem* diem = &*this;
    while (diem)
    {
        duong.push(diem);
        diem = diem->denTu;
    }
    return duong;
}

void Diem::tinh_toan()
{
    for (std::map<Diem*, int64_t>::iterator i = doanDuong.begin();
        i != doanDuong.end();
        i++
        )
    {
        Diem& diem_ke = *i->first;
        int64_t doanDuong = i->second;
        if (!diem_ke.danhDau &&
            diem_ke.chiPhi > chiPhi + doanDuong)
        {
            diem_ke.chiPhi = chiPhi + doanDuong;
            diem_ke.denTu = &(*this);
        }
    }
}