#pragma once
#include "core.hpp"
#include "tap.hpp"
#include "plana.hpp"


namespace plana
{

    void random(TapHop& tap, int tiLeDuong, int64_t chieuDaiToiThieu, int64_t chieuDaiToiDa, char mode);
    std::vector<BanGhi> simulation(BoNgauNhien cache, size_t soBanThu, size_t khoiDau, size_t giaSo);
    std::vector<BanGhi> simulation_2(BoNgauNhien cache, size_t soBanThu, size_t khoiDau, size_t giaSo);
    void random(TapHop& tap, BoNgauNhien cache);
    std::chrono::nanoseconds dijkstra_runtime(TapHop& tap, size_t dau);
    void hien_thoi_gian_chay(const std::vector<BanGhi>& record);
};

void plana::hien_thoi_gian_chay(const std::vector<BanGhi>& record)
{
    for (std::vector<BanGhi>::const_iterator i = record.begin(); i != record.end(); i++)
        std::cout << std::setw(5) << i->soLuong << " : " << i->thoiGian.count() << "ns" << std::endl;
}

void plana::random(TapHop& tap, int tiLeDuong, int64_t chieuDaiToiThieu, int64_t chieuDaiToiDa, char mode)
{
    if (!mode)
        tiLeDuong = tiLeDuong / 2;

    chieuDaiToiDa++;
    std::srand((unsigned int)std::time(NULL));

    int64_t doDai;

    for (size_t i = 0; i < tap.soLuong; i++)
        for (size_t j = 0; j < tap.soLuong; j++)
            if (i != j && std::rand() % 100 < tiLeDuong)
            {
                do
                    doDai = std::rand() % chieuDaiToiDa;
                while (doDai < chieuDaiToiThieu);
                switch (mode)
                {
                    case DA_CHIEU:
                        tap.doan[j][i] = doDai;
                    case DON_CHIEU:
                        tap.doan[i][j] = doDai;
                        break;
                }
            }
}

std::vector<BanGhi> plana::simulation(BoNgauNhien cache, size_t soBanThu, size_t khoiDau, size_t giaSo)
{
    std::vector<BanGhi> record;
    TapHop tap;
    for (size_t i = 0; i < soBanThu; i++, khoiDau += giaSo)
    {
        cache.soLuongToiDa = cache.soLuongToiThieu = khoiDau;
        khoi_tao(tap, khoiDau);
        random(tap, cache);
        record.push_back({ khoiDau, dijkstra_runtime(tap, 0) });
        xoa(tap);
    }
    return record;
}

// khong khoi tao lai du lieu = speed, chu y 16GB RAM da day voi simulation_2(), y hon 16GB chay simulation()
std::vector<BanGhi> plana::simulation_2(BoNgauNhien cache, size_t soBanThu, size_t khoiDau, size_t giaSo)
{
    std::vector<BanGhi> record;
    TapHop tap;
    khoi_tao(tap, (soBanThu - 1) * giaSo + khoiDau);
    for (size_t i = 0; i < soBanThu; i++, khoiDau += giaSo)
    {
        tap.soLuong = khoiDau;
        reset(tap);
        random(tap, cache);
        record.push_back({ khoiDau, dijkstra_runtime(tap, 0) });
    }
    return record;
}

void plana::random(TapHop& tap, BoNgauNhien cache)
{
    plana::random(tap, cache.tiLeDuong, cache.chieuDaiToiThieu, cache.chieuDaiToiDa, cache.mode);
}

std::chrono::nanoseconds plana::dijkstra_runtime(TapHop& tap, size_t dau)
{
    auto start = std::chrono::high_resolution_clock::now();
    dijkstra(tap, dau);
    auto stop = std::chrono::high_resolution_clock::now();
    return stop - start;
}


