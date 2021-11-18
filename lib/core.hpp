#pragma once
#include "tap.hpp"
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>


struct BanGhi {
	size_t soLuong;
	std::chrono::nanoseconds thoiGian;
};

struct BoNgauNhien
{
	int tiLeDuong;
	int64_t chieuDaiToiThieu;
	int64_t chieuDaiToiDa;
	size_t soLuongToiThieu;
	size_t soLuongToiDa;
	char mode;
	void hien();
	void nhap();
};

class Core
{
private:
	Tap tap;
protected:
	void hien_thi();
	void hien_thi(size_t n);
	bool running;
	void xoa_tap();
	void khoi_tao_tap(size_t soLuong);
	void random(int tiLeDuong, int64_t chieuDaiToiThieu, int64_t chieuDaiToiDa, size_t soLuongToiThieu, size_t soLuongToiDa, char mode);
	void random(BoNgauNhien cache);
	void dat_dich(size_t n);
	void tinh_toan_chi_phi();
	void tim_duong(size_t n);
	void tim_duong(std::string ten);
	void hien_tuyen_duong();
	void xoa_diem(size_t n);
	void danh_sach_chi_phi();
	Diem* getDiem(std::string ten);
	bool nap_tu_file(std::string path);

public:
	Core();
	~Core();
};

bool Core::nap_tu_file(std::string path)
{
	std::fstream file;
	file.open(path, std::ios::in);
	size_t soLuong;
	if (file.is_open() && file >> soLuong)
	{
		khoi_tao_tap(soLuong);
		size_t a, b;
		int64_t khoangCach;
		int mode;
		while (file >> a >> b >> khoangCach >> mode)
			tap.noi(a, b, khoangCach, mode);
		file.close();
		return true;
	}
	else
	{
		file.close();
		std::cout << "Tep sai?" << std::endl;
		return false;
	}
}


Diem* Core::getDiem(std::string ten)
{
	return tap.layDiem(ten);
}

void Core::xoa_diem(size_t n)
{
	tap.xoa(n);
}

void Core::danh_sach_chi_phi()
{
	for (Tap::const_iterator diem = tap.begin(); diem != tap.end(); diem++)
		std::cout << std::setw(5) << (*diem)->get_ten() << " : " << ((*diem)->get_chi_phi() == INF ? "INF" : std::to_string((*diem)->get_chi_phi())) << std::endl;
}

void Core::hien_tuyen_duong()
{
	tap.hien_tuyen_duong();
}

void Core::tim_duong(std::string ten)
{
	for (size_t i = 0; i < tap.size(); i++)
		if (tap[i]->get_ten() == ten)
		{
			tim_duong(i);
			return;
		}
	std::cout << "Khong tim thay!!!" << std::endl;
}

void Core::tim_duong(size_t n)
{
	std::stack<Diem*> buoc_di = tap[n]->tim_duong();
	std::cout << "[ ";
	while (buoc_di.size())
	{
		std::cout << buoc_di.top()->get_ten();
		if (buoc_di.size() != 1)
			std::cout << " ~~> ";
		buoc_di.pop();
	}
	std::cout << " ] Chi phi : " << (tap[n]->get_chi_phi() == INF ? "INF" : std::to_string(tap[n]->get_chi_phi())) << std::endl;
}

void Core::tinh_toan_chi_phi()
{
	tap.dijkstra();
}

void Core::hien_thi(size_t n)
{
	if (n < tap.size())
		tap[n]->thong_tin();
}

void Core::dat_dich(size_t n)
{
	tap.setDau(n);
}

void Core::hien_thi()
{
	if (tap.size())
		tap.chi_tiet();
	else
		std::cout << "Khong co duu lieu" << std::endl;
}

Core::Core()
{
	running = false;
	tap.reserve(1000);
}

Core::~Core()
{}

void Core::xoa_tap()
{
	tap.clear();
}

void Core::khoi_tao_tap(size_t soLuong)
{
	_tmp::id = 0;
	if (tap.size())
		xoa_tap();
	tap.reserve(soLuong);
	for (size_t i = 0; i < soLuong; ++i)
		tap.push_back(new Diem);
}

void Core::random(BoNgauNhien cache)
{
	random(cache.tiLeDuong, cache.chieuDaiToiThieu, cache.chieuDaiToiDa, cache.soLuongToiThieu, cache.soLuongToiDa, cache.mode);
}

void Core::random(int tiLeDuong, int64_t chieuDaiToiThieu, int64_t chieuDaiToiDa, size_t soLuongToiThieu, size_t soLuongToiDa, char mode)
{
	if (!mode)
		tiLeDuong = tiLeDuong / 2;

	chieuDaiToiDa++;
	soLuongToiDa++;
	std::srand((unsigned int)std::time(NULL));
	size_t soLuong;

	do
		soLuong = std::rand() % soLuongToiDa;
	while (soLuong < soLuongToiThieu);

	khoi_tao_tap(soLuong);

	int64_t doDai;

	for (size_t i = 0; i < soLuong; i++)
		for (size_t j = 0; j < soLuong; j++)
			if (i != j && std::rand() % 100 < tiLeDuong)
			{
				do
					doDai = std::rand() % chieuDaiToiDa;
				while (doDai < chieuDaiToiThieu);
				switch (mode)
				{
					case DA_CHIEU:
						tap[j]->noi(*tap[i], doDai);
					case DON_CHIEU:
						tap[i]->noi(*tap[j], doDai);
						break;

				}
			}
}

void BoNgauNhien::hien()
{
	std::cout
		<< "Ti le duong                   : " << tiLeDuong << std::endl
		<< "Chieu dai toi thieu cua duong : " << chieuDaiToiThieu << std::endl
		<< "Chieu dai toi da cua duong    : " << chieuDaiToiDa << std::endl
		<< "So luong diem toi thieu       : " << soLuongToiThieu << std::endl
		<< "So luong diem toi da          : " << soLuongToiDa << std::endl
		<< "Che do                        : " << (mode ? "Don chieu" : "Da chieu") << std::endl;
}

void BoNgauNhien::nhap()
{
	std::cout << "Ti le duong                   : ";
	std::cin >> tiLeDuong;
	std::cout << "Chieu dai toi thieu cua duong : ";
	std::cin >> chieuDaiToiThieu;
	std::cout << "Chieu dai toi da cua duong    : ";
	std::cin >> chieuDaiToiDa;
	std::cout << "So luong diem toi thieu       : ";
	std::cin >> soLuongToiThieu;
	std::cout << "So luong diem toi da          : ";
	std::cin >> soLuongToiDa;
	std::cout << "Che do                        : ";
	std::cin >> mode;
	std::cin.ignore(1);
}