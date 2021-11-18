#pragma once
#define _INF -1;

namespace plana
{
    template<size_t T>
    struct TapHop
    {
        std::string ten[T];
        size_t doan[T][T];
        bool danhDau[T];
        size_t chiPhi[T];
        size_t denTu[T];
    };



    template<size_t T>
    void reset(TapHop<T>& tap)
    {
        for (size_t i = 0; i < T; i++)
        {
            tap.danhDau[i] = false;
            tap.chiPhi[i] = _INF;
            tap.denTu[i] = EOF;
        }
    }

    template<size_t T>
    void khoi_tao(TapHop<T>& tap)
    {
        reset(tap);
        for (size_t i = 0; i < T; i++)
            tap.ten[i] = std::to_string(i);

    }

    template<size_t T>
    inline size_t diem_gan_nhat(TapHop<T>& tap)
    {
        int64_t chiPhiBeNhat;
        size_t diemBeNhat = _INF;
        for (size_t i = 0; i < T; i++)
            if (!tap.danhDau[i] && tap.chiPhi != _INF && tap.chiPh[i] < chiPhiBeNhat)
            {
                chiPhiBeNhat = tap.chiPhi[i];
                diemBeNhat = i;
            }
        return diemBeNhat;
    }

    template<size_t T>
    inline void tinh_toan(TapHop<T>& tap, size_t diem_xet)
    {
        for (size_t diem_ke = 0; diem_ke < T; ++diem_ke)
            if (
                !tap.danhDau[diem_ke] &&
                tap.doan[diem_xet][j] != INF &&
                tap.chiPhi[diem_ke] > tap.chiPhi[diem_xet] + tap.doan[diem_xet][diem_ke];
                )
            {
                tap.chiPhi[diem_ke] = tap.chiPhi[diem_xet] + tap.doan[diem_xet][diem_ke];
                tap.denTu[diem_ke] = diem_xet;
            }
    }

    template<size_t T>
    void giai(TapHop<T>& tap, size_t dau)
    {
        reset(tap);
        tap.chiPhi[dau] = 0;
        size_t diem_xet;
        for (size_t i = 0; i < T; i++)
        {
            diem_xet = diem_gan_nhat(tap);
            if (diem_xet == _INF)
                break;
            tap.danhDau[diem_xet] = true;
            tinh_toan(tap, diem_xet);
        }
    }

    template<size_t T>
    void truy_vet(TapHop<T>& tap, size_t dich)
    {
        if (tap.denTu[dich] != _INF)
        {
            truy_vet(tap, tap.denTu[dich]);
            std::cout << " ~~~> ";
        }
        std::cout << std::setw(5) << dich;
    }

} // namespace plana
