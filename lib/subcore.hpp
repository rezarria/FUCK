#pragma once
#include "core.hpp"
#include "tap.hpp"
#include "plana.hpp"


namespace plana
{

    void random(TapHop& tap, int tiLeDuong, int64_t chieuDaiToiThieu, int64_t chieuDaiToiDa, char mode);
    std::vector<BanGhi> simulation(BoNgauNhien cache, size_t soBanThu, size_t khoiDau, size_t giaSo);

    void random(TapHop& tap, BoNgauNhien cache);

    // template<size_t T>
    // void chuyenDoi(const Tap& c_tap, TapHop<T>* tap);
    // không chắc...

    std::chrono::nanoseconds dijkstra_runtime(TapHop& tap, size_t dau);
};

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


