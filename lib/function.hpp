#include "core.hpp"
#include <sstream>



class Function :
    public virtual Core
{
private:
    BoNgauNhien cache;
protected:
    void run(int luaChon);
public:
    Function();
};

Function::Function()
{
    cache.tiLeDuong = 25;
    cache.chieuDaiToiThieu = 5;
    cache.chieuDaiToiDa = 100;
    cache.soLuongToiDa = 1000;
    cache.soLuongToiThieu = 500;
    cache.mode = 0;
}


void Function::run(int luaChon)
{
    switch (luaChon)
    {
        case 0:
            {
                Core::hien_thi();
            }
            break;
        case 1:
            {
                cache.hien();
                int luaChon;
                std::cout
                    << "00. Tiep tuc" << std::endl
                    << "01. Chinh" << std::endl;
                std::cin >> luaChon;
                std::cin.ignore(1);
                if (luaChon)
                    cache.nhap();
                std::cout << " Dang khoi tao ngau nhien....." << std::endl;
                Core::random(cache);
            }
            break;
        case 2:
            {
                size_t soLuong;
                size_t khoiDau;
                size_t giaSo;
                do
                {
                    std::cout << "So luong ban thu : ";
                    std::cin >> soLuong;
                    std::cin.ignore(1);
                } while (soLuong < 0);

                do
                {
                    std::cout << "Khoi dau         : ";
                    std::cin >> khoiDau;
                    std::cin.ignore(1);
                } while (khoiDau < 0);

                do
                {
                    std::cout << "Gia so            : ";
                    std::cin >> giaSo;
                    std::cin.ignore(1);
                } while (giaSo < 0);
                std::vector<BanGhi> record;
                record.reserve(soLuong);
                for (size_t i = 0; i < soLuong; khoiDau += giaSo, i++)
                {
                    std::cout << "Ban thu " << std::setw(5) << i << " : ";
                    Core::random(100, 5, 100, khoiDau, khoiDau, DA_CHIEU);
                    Core::dat_dich(std::rand() % khoiDau);
                    auto start = std::chrono::high_resolution_clock::now();
                    Core::tinh_toan_chi_phi();
                    auto stop = std::chrono::high_resolution_clock::now();
                    record.push_back({ khoiDau, (stop - start) });
                    std::cout << "ok" << std::endl;
                }
                for (std::vector<BanGhi>::const_iterator i = record.begin(); i != record.end(); i++)
                    std::cout << std::setw(5) << i->soLuong << " : " << i->thoiGian.count() << "ns" << std::endl;
            }
            break;
        case 3:
            {
                Core::hien_tuyen_duong();
            }
            break;
        case 4:
            {
                size_t n;
                std::cout << "Chon dau : ";
                std::cin >> n;
                std::cin.ignore(1);
                Core::xoa_diem(n);
            }
            break;
        case 5:
            {
                std::string str;
                std::cout << "Nhap : ";
                std::getline(std::cin, str);
                std::stringstream buffer(str);
                std::vector<Diem*> arr;
                while (buffer >> str)
                {
                    Diem* addr = Core::getDiem(str);
                    if (addr)
                        arr.push_back(addr);
                }
                if (arr.size() % 2 == 0)
                    for (size_t i = 0; i < arr.size(); i += 2)
                        std::cout << std::setw(5) << arr[i]->get_ten() << " -> " << std::setw(5) << arr[i + 1]->get_ten() << " : " << arr[i]->doan_duong(arr[i + 1]) << std::endl;
                else
                    std::cout << "Nhap sai!!!" << std::endl;
            }
            break;
        case 6:
            {
                Core::nap_tu_file("input.txt");
            }
            break;
        case 7:
            {
                std::chrono::microseconds duration;
                auto start = std::chrono::high_resolution_clock::now();
                Core::tinh_toan_chi_phi();
                auto stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                std::cout << "Thoi gian chay : " << duration.count() << "μs" << std::endl;
            }
            break;
        case 8:
            {
                Core::danh_sach_chi_phi();
            }
            break;
        case 9:
            {
                size_t n;
                std::cout << "Chon dau : ";
                std::cin >> n;
                std::cin.ignore(1);
                Core::dat_dich(n);
            }
            break;
        case 10:
            {
                std::string ten;
                std::cout << "Chon : ";
                std::getline(std::cin, ten);
                Core::tim_duong(ten);
            }
            break;
        case 11:
            {
                std::string str;
                std::cout << "Chon : ";
                std::getline(std::cin, str);
                std::stringstream buffer(str);
                size_t tmp;
                while (buffer >> tmp)
                    Core::hien_thi(tmp);

            }
            break;
        case 12:
            {
                Core::running = false;
            }
            break;
        default:
            std::cout << "\n <Khong ro lenh!!!!!!>\n";
            break;
    }
}

