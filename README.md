# 🏪 HỆ THỐNG QUẢN LÝ SIÊU THỊ

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-blue?style=for-the-badge)
![Version](https://img.shields.io/badge/version-1.0.0-green?style=for-the-badge)
## 📋 MÔ TẢ DỰ ÁN  

Hệ thống quản lý siêu thị là một ứng dụng console được phát triển bằng C++, cung cấp giải pháp toàn diện cho việc quản lý các hoạt động kinh doanh bán lẻ. Dự án áp dụng các nguyên lý lập trình hướng đối tượng (OOP) với kiến trúc class rõ ràng, hệ thống kế thừa đa cấp và quản lý dữ liệu persistent thông qua file CSV.

### ✨ TÍNH NĂNG CHÍNH

- **👥 Quản lý Khách hàng**: CRUD đầy đủ với validation dữ liệu (SĐT, địa chỉ)
- **👨‍💼 Quản lý Nhân viên**: Hồ sơ chi tiết (tuổi 18-100, email, chức vụ, lương theo giờ)
- **🏭 Quản lý Nhà cung cấp**: Theo dõi đối tác, giao dịch nhập hàng, tính toán giá trị hàng hóa
- **📦 Quản lý Hàng hóa**: Kho hàng với ngày nhập/hết hạn, mức giảm giá, trạng thái tồn kho
- **🧾 Quản lý Hóa đơn**: Tạo đơn hàng, áp dụng giảm giá, thanh toán tự động trừ kho
- **📊 Thống kê & Báo cáo**: Doanh thu theo ngày, phân tích tồn kho, báo cáo tổng hợp

### 🎯 LÝ DO LỰA CHỌN CÔNG NGHỆ

- **C++ Standard Library**: Hiệu năng cao, quản lý bộ nhớ tối ưu cho ứng dụng desktop
- **STL Containers (vector)**: Quản lý danh sách động hiệu quả
- **File I/O Streams**: Lưu trữ dữ liệu persistent dạng CSV, dễ migration sang database
- **OOP Design**: Tính kế thừa (class `Nguoi`), đa hình, encapsulation cho maintainability

### 🚧 THÁCH THỨC ĐÃ GẶP

1. **Quản lý quan hệ dữ liệu**: Đảm bảo tính toàn vẹn khi xóa (foreign key constraints thủ công)
2. **Validation phức tạp**: Xử lý input với nhiều ràng buộc (email, SĐT, ngày tháng, tuổi)
3. **Đồng bộ file**: Cập nhật đồng thời nhiều file CSV khi thao tác liên quan (hóa đơn ↔ kho)
4. **UX Console**: Thiết kế menu trực quan, xử lý lỗi nhập liệu gracefully

### 🔮 HƯỚNG PHÁT TRIỂN TƯƠNG LAI

- [ ] **Database Migration**: Chuyển từ CSV sang SQLite/MySQL cho ACID compliance
- [ ] **GUI Application**: Phát triển giao diện đồ họa (Qt/wxWidgets)
- [ ] **Multi-user Support**: Hệ thống phân quyền (admin, nhân viên, kế toán)
- [ ] **Analytics Dashboard**: Biểu đồ doanh thu, forecast hàng bán chạy
- [ ] **Barcode Scanner Integration**: Tích hợp quét mã vạch cho hóa đơn
- [ ] **Export Reports**: Xuất báo cáo PDF/Excel
- [ ] **Network Sync**: Đồng bộ dữ liệu đa chi nhánh

## 📑 MỤC LỤC

- [MÔ TẢ DỰ ÁN](#-mô-tả-dự-án)
- [TECH STACK](#-Tech-Stack)
- [CÀI ĐẶT](#-cài-đặt--thiết-lập)
- [HƯỚNG DẪN SỬ DỤNG](#-hướng-dẫn-sử-dụng)
- [KIẾN TRÚC DỰ ÁN](#-kiến-trúc-dự-án)
- [KIỂM THỬ](#-kiểm-thử)
- [ĐÓNG GÓP](#-đóng-góp)
- [CREDITS](#-credits)
- [LICENSE](#-license)

## 🛠️ TECH STACK

| Công nghệ | Phiên bản | Mục đích |
|-----------|-----------|----------|
| **C++** |[5.11] | Ngôn ngữ lập trình chính |
| **STL** | Standard Library | Các bộ chứa (vector, string), Luồng Nhập/Xuất |
| **CSV Format** | UTF-8 | Lưu trữ dữ liệu persistent |

**Thư Viện Standard sử dụng:**
- `<iostream>` - Nhập/Xuất dữ liệu (Input/Output).
- `<fstream>` - Xử lý tệp tin (Đọc và ghi file).
- `<sstream>` - Phân tích cú pháp chuỗi (String parsing).
- `<vector>` - Mảng động (Cấu trúc dữ liệu có thể thay đổi kích thước).
- `<iomanip>` - Định dạng hiển thị (Ví dụ: thiết lập độ rộng `setw`, độ chính xác số thập phân `setprecision`).
- `<cstdio>` - Xử lý định dạng kiểu C (Thường dùng để kiểm tra tính hợp lệ của ngày tháng qua `sscanf`,`sprintf`).
- `<cctype>` - Xử lý ký tự (Ví dụ: kiểm tra chữ số `isdigit`, chuyển đổi chữ hoa `toupper`).

## 🚀 CÀI ĐẶT & THIẾT LẬP

### YÊU CẦU HỆ THỐNG

- **Trình biên dịch C++**: GCC 5.0+, Clang 3.5+, MSVC 2015+
- **Hệ điều hành**: Windows, Linux, macOS
- **RAM**: Tối thiểu 512MB

### Clone Repository
```bash
git clone https://github.com/Benhochoi/Clarity-Team.git
cd Clarity-Team
```

### BIÊN DỊCH DỰ ÁN

**Trên Linux/macOS:**
```bash
g++ -std=c++11 "Quan ly sieu thi.cpp" -o QuanLySieuThi
chmod +x QuanLySieuThi
./QuanLySieuThi
```

**Trên Windows (MinGW):**
```cmd
g++ -std=c++11 "Quan ly sieu thi.cpp" -o QuanLySieuThi.exe
QuanLySieuThi.exe
```

**Với Dev-C++:**
1. Mở file `Quan ly sieu thi.cpp`
2. Nhấn `F11` hoặc Execute → Compile & Run

**Với Visual Studio:**
1. Tạo **Console Application** mới
2. Add existing item → `Quan ly sieu thi.cpp`
3. Build → `Ctrl+Shift+B`
4. Run → `Ctrl+F5`

### CẤU HÌNH BAN ĐẦU

**Thay đổi mật khẩu mặc định** (trong source code):
```cpp
const string ADMIN_PASSWORD = "admin123"; // Đổi thành mật khẩu của bạn
```

**Files dữ liệu được tạo tự động:**
```
khachhang.txt      # Dữ liệu khách hàng
nhanvien.txt       # Dữ liệu nhân viên
nhacungcap.txt     # Dữ liệu nhà cung cấp
hanghoa.txt        # Dữ liệu hàng hóa
hoadon.txt         # Dữ liệu hóa đơn
```

## 📖 Hướng Dẫn Sử Dụng

### Đăng nhập hệ thống
```
DANG NHAP HE THONG QUAN LY
Nhap mat khau (Lan thu 1/3): admin123
* Dang nhap thanh cong!
```

💡 **Lưu ý**: Bạn có 3 lần thử nhập mật khẩu. Sau đó chương trình tự động thoát.

### Menu chính
```
=====================================================
                 HE THONG QUAN LY                    
=====================================================
  [1]  Quan ly Khach hang
  [2]  Quan ly Nhan vien
  [3]  Quan ly Nha cung cap
  [4]  Quan ly Hang hoa
  [5]  Quan ly Hoa don
  [6]  Thong ke
  [0]  Thoat chuong trinh
-----------------------------------------------------
```

### QUY TRÌNH LÀM VIỆC ĐỀ XUẤT

#### 1️⃣ **Thiết lập ban đầu**
```
Menu [2] → Thêm nhân viên
Menu [3] → Thêm nhà cung cấp
Menu [3] → Nhập giao dịch hàng hóa từ NCC
```

#### 2️⃣ **Hoạt động hàng ngày**
```
Menu [1] → Thêm khách hàng mới (nếu cần)
Menu [5] → Tạo hóa đơn
  ↳ Nhập mã hàng hóa
  ↳ Xem tổng tiền, giảm giá
Menu [5] → Thanh toán (tự động trừ kho)
```

#### 3️⃣ **Quản lý kho**
```
Menu [4] → Cập nhật số lượng từ NCC
Menu [4] → Kiểm tra hàng sắp hết (option 10)
Menu [3] → Tính tổng giá trị hàng theo NCC (option 7)
```

#### 4️⃣ **Thống kê cuối ngày**
```
Menu [6] → Thống kê doanh thu theo ngày
Menu [6] → Xem số hóa đơn trong ngày
```

### VÍ DỤ SỬ DỤNG

**Thêm hàng hóa từ nhà cung cấp:**
```
Chon chuc nang: 3
Chon: 1  # Hiển thị danh sách NCC
Chon: 6  # Chi tiết NCC
Nhap ma nha cung cap: NCC001

# Nhập giao dịch
Nhap so luong mat hang can nhap: 2

Mat hang thu 1:
 Ma hang: SP001
 Ten mat hang: Sua TH True Milk
 Loai hang: Do uong
 So luong nhap: 100
 Don gia nhap: 8000

>>> Tong gia tri hang hoa nay cho NCC NCC001: 800000 VND
```

**Tạo hoá đơn:**
```
Chon chuc nang: 5
Chon: 2  # Thêm hóa đơn

Nhap ma hoa don: HD001
Nhap ma khach hang: KH001
Nhap ngay lap hoa don (dd/mm/yyyy): 20/01/2026

Nhap ma hang hoa (hoac 'x' de ket thuc): SP001
Hang hoa: Sua TH True Milk, Ton kho: 100
Nhap so luong: 10
* Da them mat hang vao hoa don.

Nhap ma hang hoa (hoac 'x' de ket thuc): x

===== HOA DON: HD001 =====
Khach hang: KH001
Ngay lap: 20/01/2026

MaHH        Ten Hang                  SL      Gia Ban    Giam%   TienGoc        TienGiam       ThanhTien      
SP001       Sua TH True Milk          10      10400      0       104000         0              104000         

Tong tien goc : 104000
Tong tien giam : 0
Tong thanh toan: 104000

Luu hoa don? (y/n): y
* Da luu hoa don.
```

## 🏗️ KIẾN TRÚC DỰ ÁN

### Class Diagram
```
Nguoi (Abstract Base Class)
  ├── KhachHang
  └── NhanVien

NhaCungCap (Independent)

HangHoa
  └── Liên kết: NhaCungCap (maNhaCungCap)

HoaDon
  ├── Liên kết: KhachHang (maKhachHang)
  └── Chứa: vector<ChiTietHoaDon>

ChiTietHoaDon
  └── Tham chiếu: HangHoa (maHang)

QuanLy (Main Controller)
  ├── vector<KhachHang>
  ├── vector<NhanVien>
  ├── vector<NhaCungCap>
  ├── vector<HangHoa>
  └── vector<HoaDon>
```

### ĐỊNH DẠNG FILE TXT

**khachhang.txt:**
```csv
MaKH,HoTen,SoDienThoai,DiaChi
KH001,Nguyen Van A,0912345678,123 Le Loi, Q1, TP.HCM
```

**nhanvien.txt:**
```csv
MaNV,HoTen,SoDienThoai,DiaChi,Email,Tuoi,ChucVu,NgayVaoLam,LuongTheoGio
NV001,Tran Thi B,0987654321,456 Nguyen Hue, Q1,b@email.com,25,Thu ngan,01/01/2025,50000
```

**hanghoa.txt:**
```csv
MaHH,TenHH,LoaiHang,MaNCC,DonViTinh,SoLuongTon,DonGia,NgayNhap,NgayHetHan,MucGiamGia,ConHang
SP001,Sua TH,Do uong,NCC001,hop,100,8000,20/01/2026,20/02/2026,0,1
```

**hoadon.txt:**
```csv
MaHD,MaKH,NgayLap,DaThanhToan,SoLuongMatHang,ChiTiet
HD001,KH001,20/01/2026,1,2,SP001|Sua TH|10|8000|10400|0;SP002|Banh mi|5|5000|6500|10
```

### QUY TẮC XÁC THỰC

| Trường | Ràng Buộc |
|--------|-----------|
| **Số điện thoại** | Chỉ số và dấu `+`, không âm |
| **Email** | Bắt buộc có `@` |
| **Tuổi nhân viên** | 18 ≤ tuổi ≤ 100 |
| **Ngày tháng** | Hợp lệ theo lịch (xử lý năm nhuận) |
| **Ngày hết hạn** | Phải sau ngày nhập |
| **Giá bán** | = Đơn giá × 1.3 (auto) |
| **Mức giảm giá** | 0% ≤ giảm ≤ 100% |

## 🧪 KIỂM THỬ

### Manual Testing Checklist

- [ ] **Khách hàng**: Thêm/sửa/xóa, kiểm tra trùng mã
- [ ] **Nhân viên**: Validation tuổi, email, SĐT
- [ ] **Nhà cung cấp**: Nhập giao dịch, tính tổng giá trị
- [ ] **Hàng hóa**: Kiểm tra tồn kho, ngày hết hạn
- [ ] **Hóa đơn**: 
  - Thêm nhiều mặt hàng
  - Kiểm tra giảm giá
  - Thanh toán → kiểm tra trừ kho
  - Không sửa/xóa được hóa đơn đã thanh toán
- [ ] **Thống kê**: Doanh thu theo ngày, tổng hợp

### VÍ DỤ KIỂM THỬ
```cpp
// Test: Không xóa được NCC có hàng hóa liên quan
1. Thêm NCC: NCC001
2. Thêm hàng hóa: SP001 (maNCC = NCC001)
3. Xóa NCC001 → Expected: "? Khong the xoa nha cung cap vi co hang hoa lien quan."
```

## 🤝 ĐÓNG GÓP

Mọi đóng góp đều được chào đón! Vui lòng làm theo các bước sau:

1. **Fork** repository
2. Tạo **feature branch**:
```bash
   git checkout -b feature/TinhNangMoi
```
3. **Commit** thay đổi:
```bash
   git commit -m "feat: Thêm tính năng xuất báo cáo PDF"
```
4. **Push** lên branch:
```bash
   git push origin feature/TinhNangMoi
```
5. Tạo **Pull Request**

### Coding Conventions

- **Naming**: `camelCase` cho biến, `PascalCase` cho class
- **Comments**: Tiếng Việt cho logic phức tạp
- **Indentation**: 4 spaces
- **Commit messages**: Theo [Conventional Commits](https://www.conventionalcommits.org/)

## 👥 CREDITS

### Thành vên phát triển

| Tên | GitHub | Role |
|-----|--------|------|
| [Đào Nguyên Chiến] | [@Benhochoi]() | Leader |
| [Lê Thị Phượng] | [@lean270106-boop](https://github.com/lean270106-boop) | Dev |
| [Hoàng Thị Hiếu] | [@hoanghieu-101](https://github.com/hoanghieu-101) | Dev|
| [Nguyễn Quỳnh Anh] | [@dinhquynhanh0711-ux](https://github.com/username) |Dev |

### Tài liệu tham khảo

- [C++ Reference](https://en.cppreference.com/)
- [STL Documentation](https://www.cplusplus.com/reference/stl/)
- [Design Patterns in C++](https://refactoring.guru/design-patterns/cpp)

### Lời cảm ơn

- Giảng viên hướng dẫn: Ths Lê Văn Hùng
- Cộng đồng C++ Vietnam
- Stack Overflow contributors

## 📄 LICENSE
Dự án này được phân phối dưới giấy phép **MIT License**.
```
Copyright (c) 2026 Clarity Team
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE
```

---

<div align="center">

**⭐ Nếu dự án hữu ích, hãy cho một star! ⭐**

Made with ❤️ by Clarity Team.

[📧 Email](denousce@gmail.com]) • [🐛 Report Bug](https://github.com/Benhochoi/issues) • [💡 Request Feature](https://github.com/Benhochoi/issues)

</div>
