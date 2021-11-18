#pragma once
#include "core.hpp"
#include "tap.hpp"
#include "plana.hpp"


namespace plana
{
    template<size_t T>
    void khoi_tao_tap(TapHop<T>& tap);

    template<size_t T>
    void random(TapHop<T>& tap, int tiLeDuong, int64_t chieuDaiToiThieu, int64_t chieuDaiToiDa, char mode);

    template<size_t T>
    void random(TapHop<T>& tap, BoNgauNhien cache);

    // template<size_t T>
    // void chuyenDoi(const Tap& c_tap, TapHop<T>* tap);
    // không chắc...

    
};

template<size_t T>
void plana::khoi_tao_tap(TapHop<T>& tap)
{
    reset(tap);
}

template<size_t T>
void plana::random(TapHop<T>& tap, int tiLeDuong, int64_t chieuDaiToiThieu, int64_t chieuDaiToiDa, char mode)
{
    if (!mode)
        tiLeDuong = tiLeDuong / 2;

    chieuDaiToiDa++;
    std::srand((unsigned int)std::time(NULL));

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
                        tap.doan[j][i] = doDai;
                    case DON_CHIEU:
                        tap.doan[i][j] = doDai;
                        break;

                }
            }
}

template<size_t T>
void plana::random(TapHop<T>& tap, BoNgauNhien cache)
{
    plan::random(cache.tiLeDuong, cache.chieuDaiToiThieu, cache.chieuDaiToiDa, cache.mode);
}




