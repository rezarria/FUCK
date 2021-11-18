#pragma once
#define _INF -1

namespace plana
{
    struct TapHop
    {
        std::string* ten;
        size_t** doan;
        bool* danhDau;
        size_t* chiPhi;
        size_t* denTu;
        size_t soLuong;
    };



    void reset(TapHop& tap)
    {
        for (size_t i = 0; i < tap.soLuong; i++)
        {
            tap.danhDau[i] = false;
            tap.chiPhi[i] = _INF;
            tap.denTu[i] = EOF;
            for (size_t j = 0; j < tap.soLuong; j++)
                tap.doan[i][j] = INF;
        }
    }

    void khoi_tao(TapHop& tap, size_t soLuong)
    {
        tap.soLuong = soLuong;
        tap.chiPhi = new size_t[soLuong];
        tap.danhDau = new bool[soLuong];
        tap.denTu = new size_t[soLuong];
        tap.ten = new std::string[soLuong];
        tap.doan = new size_t * [soLuong];
        for (size_t i = 0; i < tap.soLuong; i++)
        {
            tap.ten[i] = std::to_string(i);
            tap.doan[i] = new size_t[tap.soLuong];
        }
        reset(tap);
    }

    void xoa(TapHop& tap)
    {
        delete[] tap.chiPhi;
        delete[] tap.denTu;
        delete[] tap.danhDau;
        delete[] tap.ten;
        for (size_t i = 0; i < tap.soLuong; i++)
            delete[] tap.doan[i];
        delete[] tap.doan;
    }

    inline size_t diem_gan_nhat(TapHop& tap)
    {
        int64_t chiPhiBeNhat;
        size_t diemBeNhat = _INF;
        for (size_t i = 0; i < tap.soLuong; i++)
            if (!tap.danhDau[i] && tap.chiPhi[i] != _INF && tap.chiPhi[i] < chiPhiBeNhat)
            {
                chiPhiBeNhat = tap.chiPhi[i];
                diemBeNhat = i;
            }
        return diemBeNhat;
    }

    inline void tinh_toan(TapHop& tap, size_t diem_xet)
    {
        for (size_t diem_ke = 0; diem_ke < tap.soLuong; ++diem_ke)
            if (
                !tap.danhDau[diem_ke] &&
                tap.doan[diem_xet][diem_ke] != INF &&
                tap.chiPhi[diem_ke] > tap.chiPhi[diem_xet] + tap.doan[diem_xet][diem_ke]
                )
            {
                tap.chiPhi[diem_ke] = tap.chiPhi[diem_xet] + tap.doan[diem_xet][diem_ke];
                tap.denTu[diem_ke] = diem_xet;
            }
    }

    void dijkstra(TapHop& tap, size_t dau)
    {
        reset(tap);
        tap.chiPhi[dau] = 0;
        size_t diem_xet;
        for (size_t i = 0; i < tap.soLuong; i++)
        {
            diem_xet = diem_gan_nhat(tap);
            if (diem_xet == _INF)
                break;
            tap.danhDau[diem_xet] = true;
            tinh_toan(tap, diem_xet);
        }
    }

    void truy_vet(TapHop& tap, size_t dich)
    {
        if (tap.denTu[dich] != _INF)
        {
            truy_vet(tap, tap.denTu[dich]);
            std::cout << " ~~~> ";
        }
        std::cout << std::setw(5) << dich;
    }

} // namespace plana
