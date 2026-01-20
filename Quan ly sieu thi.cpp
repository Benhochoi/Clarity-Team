#include <iostream> // nhap xuat du lieu
#include <fstream> // lam viec voi file
#include <sstream> // xu ly chuoi
#include <vector> // su dung mang dong vector
#include <string> // lam viec voi string
#include <iomanip> // setw, setprecision, left, right (dinh dang bang)
#include <cstdio> // xu ly ngay thang
#include <cctype>  // dung cho isdigit, toupper, tolower
// cac thu vien can phai dung

using namespace std;

class HangHoa;
class NhaCungCap;

// Tim vi tri hang hoa theo MA (tra ve -1 neu khong co)
int findHangIndexByMa(const vector<HangHoa>& kho, const string& ma);
// Tim vi tri hang hoa theo TEN (tra ve -1 neu khong co)
int findHangIndexByTen(const vector<HangHoa>& kho, const string& ten);

// Chuyen chuoi sang chu in hoa
string toUpperCase(const string& s) {
    string result = s;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = toupper((unsigned char)result[i]);
    }
    return result;
}

// Chuyen chuoi sang chu thuong
string toLowerCase(const string& s) {
    string result = s;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = tolower((unsigned char)result[i]);
    }
    return result;
}

// Ham kiem tra chuoi con (khong phan biet hoa thuong)
bool chuaChuoiCon(const string& chuoiGoc, const string& chuoiCon) {
    string goc = toLowerCase(chuoiGoc);
    string con = toLowerCase(chuoiCon);
    return goc.find(con) != string::npos;
}

// Kiem tra chuoi co chua bat ky chu so nao khong
bool chuaChuSo(const string& s) {
    for (size_t i = 0; i < s.size(); ++i) if (isdigit((unsigned char)s[i])) return true;
    return false;
}
// Kiem tra chuoi co phai toan bo chu so hay khong
bool tatCaLaChuSo(const string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); ++i) if (!isdigit((unsigned char)s[i])) return false;
    return true;
}

// Doc so nguyen >= 0, chong loi nhap sai
int docSoNguyenKhongAm(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) continue;
        if (line.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
        bool ok = true;
        for (size_t i = 0; i < line.size(); ++i) {
            if (i==0 && (line[i]=='+' || line[i]=='-')) continue;
            if (!isdigit((unsigned char)line[i])) { ok = false; break; }
        }
        if (!ok) { cout << "? Phai la so nguyen khong am. Nhap lai.\n"; continue; }
        stringstream ss(line);
        long long val;
        ss >> val;
        if (ss.fail() || val < 0) { cout << "? Gia tri khong hop le hoac < 0. Nhap lai.\n"; continue; }
        x = static_cast<int>(val);
        return x;
    }
}

// Doc so thuc >= 0
double docSoThucKhongAm(const string& prompt) {
    double x;
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) continue;
        if (line.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
        bool ok = true;
        int dotCount = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '.') { dotCount++; if (dotCount > 1) { ok = false; break; } }
            else if (i==0 && (c=='+' || c=='-')) continue;
            else if (!isdigit((unsigned char)c)) { ok = false; break; }
        }
        if (!ok) { cout << "? Phai la so thuc >=0. Nhap lai.\n"; continue; }
        stringstream ss(line);
        double val;
        ss >> val;
        if (ss.fail() || val < 0) { cout << "? Gia tri khong hop le hoac < 0. Nhap lai.\n"; continue; }
        x = val;
        return x;
    }
}

// doc chuoi khong chua chu so
string docChuoiKhongChuaSo(const string& prompt) {
    while (true) {
        cout << prompt;
        string s;
        if (!getline(cin, s)) continue;
        if (s.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
        if (chuaChuSo(s)) { cout << "? Khong duoc chua chu so. Nhap lai.\n"; continue; }
        return s;
    }
}
// Doc ma so, tu dong cat khoang trang dau + cuoi
string docMaSo(const string& prompt) {
    while (true) {
        cout << prompt;
        string s;
        if (!getline(cin, s)) continue;
        if (s.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
        size_t a = s.find_first_not_of(" \t\r\n");
        size_t b = s.find_last_not_of(" \t\r\n");
        if (a==string::npos) { cout << "? Khong duoc toan khoang trang. Nhap lai.\n"; continue; }
        string t = s.substr(a, b-a+1);
        if (t.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
        return t;
    }
}
// kiem tra ngay co hop le khong
bool ngayHopLe(int d, int m, int y) {
    if (y < 1 || y > 9999) return false;
    if (m < 1 || m > 12) return false;
    int mdays;
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: mdays = 31; break;
        case 4: case 6: case 9: case 11: mdays = 30; break;
        case 2:
            {
                bool leap = (y%400==0) || (y%4==0 && y%100!=0);
                mdays = leap ? 29 : 28;
            }
            break;
        default: return false;
    }
    if (d < 1 || d > mdays) return false;
    return true;
}

// Doc ngay theo dinh dang dd/mm/yyyy 
string docNgay(const string& prompt) {
    while (true) {
        cout << prompt << " (dd/mm/yyyy): ";
        string s;
        if (!getline(cin, s)) continue;
        if (s.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
        int d=0,m=0,y=0;
        if (sscanf(s.c_str(), "%d/%d/%d", &d,&m,&y) != 3) { cout << "? Dinh dang phai dd/mm/yyyy. Nhap lai.\n"; continue; }
        if (!ngayHopLe(d,m,y)) { cout << "? Ngay khong hop le theo duong lich. Nhap lai.\n"; continue; }
        char buf[16];
        sprintf(buf, "%02d/%02d/%04d", d,m,y);
        return string(buf);
    }
}

// class nguoi 
class Nguoi {
protected:
    string maSo;
    string hoVaTen;
    string soDienThoai;
    string diaChi;

public:
    // Constructor mac dinh
    Nguoi(): maSo(""), hoVaTen(""), soDienThoai(""), diaChi("") {}

    // Constructor day du thong tin
    Nguoi(const string& m, const string& ht, const string& sdt, const string& dc)
        : maSo(m), hoVaTen(ht), soDienThoai(sdt), diaChi(dc) {}

    // Constructor khong co so dien thoai
    Nguoi(const string& m, const string& ht, const string& dc)
        : maSo(m), hoVaTen(ht), soDienThoai(""), diaChi(dc) {}

    virtual ~Nguoi() {}

    // Ham ao bat buoc lop ke thua phai dinh nghia
    virtual void nhapThongTin() = 0;
    virtual void xuatThongTin() const = 0;
    virtual void luuVaoFile(ofstream& ofs) const = 0;
    virtual void suaThongTin() = 0;

    // Getter lay du lieu
    string getMa() const { return maSo; }
    string getTen() const { return hoVaTen; }
    string getSoDienThoai() const { return soDienThoai; }

    // Toan tu ==, dung de kiem tra trung ma so hoac so dien thoai
    bool operator==(const Nguoi& other) const {
        return (maSo == other.maSo || soDienThoai == other.soDienThoai);
    }

    // Toan tu << in thong tin ra ostream
    friend ostream& operator<<(ostream& os, const Nguoi& n);
};

ostream& operator<<(ostream& os, const Nguoi& n) {
    os << "Ma: " << n.maSo << ", Ten: " << n.hoVaTen
       << ", SDT: " << n.soDienThoai << ", Dia chi: " << n.diaChi;
    return os;
}


/////////////////////// KhachHang ///////////////////////
class KhachHang : public Nguoi {
public: 
    KhachHang() : Nguoi() {}

    KhachHang(const string& m, const string& ht, const string& dc)
        : Nguoi(m, ht, dc) {}  

    ~KhachHang() {}

    void nhapThongTin() {
	// Nhap thong tin khach hang, co rang buoc so dien thoai
        cout << "\n--- Nhap Khach Hang ---\n";
	// Ham docMaSo + docChuoiKhongChuaSo
        maSo = docMaSo("Nhap ma khach hang: ");
        hoVaTen = docChuoiKhongChuaSo("Nhap ho ten: ");
	// Vong lap kiem tra so dien thoai hop le
        while (true) {
    			cout << "Nhap so dien thoai: ";
    			if (!getline(cin, soDienThoai)) continue;
    			if (soDienThoai.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
    
    			// Loai bo khoang trang
    			string temp = "";
    			for (size_t i = 0; i < soDienThoai.size(); ++i) {
    		    if (soDienThoai[i] != ' ') temp += soDienThoai[i];
    			}
    	
    			// Kiem tra am
    			if (temp[0] == '-') {
    		    cout << "? So dien thoai khong duoc la so am. Nhap lai.\n";
    		    continue;
   				}
    
    			// Kiem tra ki tu hop le
    			bool ok = true;
    			for (size_t i = 0; i < temp.size(); ++i) {
      			  char c = temp[i];
      			  if (!(isdigit((unsigned char)c) || c=='+')) { ok = false; break; }
    			}
    			if (!ok) { cout << "? So dien thoai chi chua chu so va dau +. Nhap lai.\n"; continue; }
    
    			soDienThoai = temp;
    			break;
		}
        diaChi = docMaSo("Nhap dia chi: ");
    }

    void suaThongTin() {
	// Sua thong tin khach hang
        cout << "\n--- Sua Khach Hang ---\n";
        hoVaTen = docChuoiKhongChuaSo("Nhap ho ten moi: ");
	 // Nhap lai so dien thoai, kiem tra hop le
        while (true) {
    cout << "Nhap so dien thoai moi: ";
    if (!getline(cin, soDienThoai)) continue;
    if (soDienThoai.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
    
    // Loai bo khoang trang
    string temp = "";
    for (size_t i = 0; i < soDienThoai.size(); ++i) {
        if (soDienThoai[i] != ' ') temp += soDienThoai[i];
    }
    
    // kiem tra am
    if (temp[0] == '-') {
        cout << "? So dien thoai khong duoc la so am. Nhap lai.\n";
        continue;
    }
    
    // Kiem tra ki tu hop le
    bool ok = true;
    for (size_t i = 0; i < temp.size(); ++i) {
        char c = temp[i];
        if (!(isdigit((unsigned char)c) || c=='+')) { ok = false; break; }
    }
    if (!ok) { cout << "? So dien thoai chi chua chu so va dau +. Nhap lai.\n"; continue; }
    
    soDienThoai = temp;
    break;
}
        diaChi = docMaSo("Nhap dia chi moi: ");
    }

    void xuatThongTin() const {
	// In dang bang de hien thi danh sach
    cout << "| " << left << setw(10) << maSo
         << "| " << setw(23) << hoVaTen
         << "| " << setw(14) << soDienThoai
         << "| " << setw(28) << diaChi << "|" <<endl;
    cout << "+-----------+------------------------+---------------+-----------------------------+"<<endl;
}

    void luuVaoFile(ofstream& ofs) const {
	// Ghi ra file CSV
        ofs << maSo << "," << hoVaTen << "," << soDienThoai << "," << diaChi << "\n";
    }

    static void tieuDe() {
	// In tieu de cot bang hien thi
    cout << "\n+-----------+------------------------+---------------+-----------------------------+\n";
    cout << "| " << left << setw(10) << "Ma KH"
         << "| " << setw(23) << "Ho va Ten"
         << "| " << setw(14) << "So DT"
         << "| " << setw(28) << "Dia Chi" << "|\n";
    cout << "+-----------+------------------------+---------------+-----------------------------+" << endl;
}
    void deserializeLine(const string& line) {
	 // Doc du lieu tu file CSV vao doi tuong
        stringstream ss(line);
        getline(ss, maSo, ',');
        getline(ss, hoVaTen, ',');
        getline(ss, soDienThoai, ',');
        getline(ss, diaChi, ',');
    }
};


/////////////////////// NhanVien ///////////////////////
class NhanVien : public Nguoi {
private:
    string chucVu;
    string ngayVaoLam;
    double luongCoBan;
    int tuoi;           
    string email;       

public:
NhanVien(): Nguoi(), chucVu(""), ngayVaoLam(""), luongCoBan(0), tuoi(0), email("") {}
    ~NhanVien() {}

    void nhapThongTin() {
	// Nhap thong tin nhan vien, nhieu rang buoc hon khach hang
    cout << "\n--- Nhap Nhan Vien ---\n";
    maSo = docMaSo("Nhap ma nhan vien: ");
    hoVaTen = docChuoiKhongChuaSo("Nhap ho ten: ");
    
    
   // Vong lap kiem tra so dien thoai
    while (true) {
    cout << "Nhap so dien thoai moi: ";
    if (!getline(cin, soDienThoai)) continue;
    if (soDienThoai.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
    
    
    string temp = "";
    for (size_t i = 0; i < soDienThoai.size(); ++i) {
        if (soDienThoai[i] != ' ') temp += soDienThoai[i];
    }
    
    // Kiem tra am
    if (temp[0] == '-') {
        cout << "? So dien thoai khong duoc la so am. Nhap lai.\n";
        continue;
    }
    
    // Kiem tra tinh hop le
    bool ok = true;
    for (size_t i = 0; i < temp.size(); ++i) {
        char c = temp[i];
        if (!(isdigit((unsigned char)c) || c=='+')) { ok = false; break; }
    }
    if (!ok) { cout << "? So dien thoai chi chua chu so va dau +. Nhap lai.\n"; continue; }
    
    soDienThoai = temp;
    break;
}
    
    diaChi = docMaSo("Nhap dia chi: ");
    
    // Kiem tra email co ky tu @
    while (true) {
        cout << "Nhap email: ";
        if (!getline(cin, email)) continue;
        if (email.empty()) { 
            cout << "? Khong duoc de trong. Nhap lai.\n"; 
            continue; 
        }
        if (email.find('@') == string::npos) { 
            cout << "? Email khong hop le (phai chua @). Nhap lai.\n"; 
            continue; 
        }
        break;
    }
    
    // Kiem tra tuoi phai tu 18 den 100
    tuoi = docSoNguyenKhongAm("Nhap tuoi (>=18): ");
    while (tuoi < 18 || tuoi > 100) {
        cout << "? Tuoi phai tu 18 den 100. Nhap lai.\n";
        tuoi = docSoNguyenKhongAm("Nhap tuoi (>=18): ");
    }
    
    chucVu = docChuoiKhongChuaSo("Nhap chuc vu: ");
    ngayVaoLam = docNgay("Nhap ngay vao lam");
    luongCoBan = docSoThucKhongAm("Nhap luong theo gio (>=0): ");
	while (luongCoBan <= 0) {
    	cout << "? Luong phai lon hon 0. Nhap lai.\n";
    	luongCoBan = docSoThucKhongAm("Nhap luong theo gio (>0): ");
	}
}

  void suaThongTin() {
	// Sua thong tin nhan vien
    cout << "\n--- Sua Nhan Vien ---\n";
    hoVaTen = docChuoiKhongChuaSo("Nhap ho ten moi: ");
    
   //Nhap so dien thoai rang buoc
while (true) {
    cout << "Nhap so dien thoai: ";
    if (!getline(cin, soDienThoai)) continue;
    if (soDienThoai.empty()) { 
        cout << "? Khong duoc de trong. Nhap lai.\n"; 
        continue; 
    }
    
    
    string temp = "";
    for (size_t i = 0; i < soDienThoai.size(); ++i) {
        if (soDienThoai[i] != ' ') temp += soDienThoai[i];
    }
    
    // Kiem tra am
    if (temp[0] == '-') {
        cout << "? So dien thoai khong duoc la so am. Nhap lai.\n";
        continue;
    }
    
    // Kiem tra ky tu hop le va co it nhat 1 chu so
    bool ok = true;
    bool hasDigit = false;
    for (size_t i = 0; i < temp.size(); ++i) {
        char c = temp[i];
        if (isdigit((unsigned char)c)) {
            hasDigit = true;
        } else if (c != '+') { 
            ok = false; 
            break; 
        }
    }
    if (!ok || !hasDigit) { 
        cout << "? So dien thoai chi chua chu so va dau +. Nhap lai.\n"; 
        continue; 
    }
    
    soDienThoai = temp;
    break;
}
    
    diaChi = docMaSo("Nhap dia chi moi: ");
    
     // Kiem tra email co ky tu @
    while (true) {
        cout << "Nhap email moi: ";
        if (!getline(cin, email)) continue;
        if (email.empty()) { 
            cout << "? Khong duoc de trong. Nhap lai.\n"; 
            continue; 
        }
        if (email.find('@') == string::npos) { 
            cout << "? Email khong hop le (phai chua @). Nhap lai.\n"; 
            continue; 
        }
        break;
    }
    
    // Kiem tra tuoi phai tu 18 den 100
    tuoi = docSoNguyenKhongAm("Nhap tuoi moi (>=18): ");
    while (tuoi < 18 || tuoi > 100) {
        cout << "? Tuoi phai tu 18 den 100. Nhap lai.\n";
        tuoi = docSoNguyenKhongAm("Nhap tuoi moi (>=18): ");
    }
    
    chucVu = docChuoiKhongChuaSo("Nhap chuc vu moi: ");
    ngayVaoLam = docNgay("Nhap ngay vao lam moi");
    luongCoBan = docSoThucKhongAm("Nhap luong theo gio moi (>=0): ");
while (luongCoBan <= 0) {
    cout << "? Luong phai lon hon 0. Nhap lai.\n";
    luongCoBan = docSoThucKhongAm("Nhap luong theo gio moi (>0): ");
}
}


 void xuatThongTin() const {
	// In theo dang bang nhieu cot, dung setw can le
    cout << "| " << left << setw(10) << maSo
         << "| " << setw(20) << hoVaTen
         << "| " << setw(5) << tuoi
         << "| " << setw(13) << soDienThoai
         << "| " << setw(25) << email
         << "| " << setw(22) << diaChi
         << "| " << setw(15) << chucVu
         << "| " << setw(10) << ngayVaoLam << "|" << endl;
    cout << "+-----------+---------------------+------+--------------+--------------------------+-----------------------+----------------+-----------+" << endl;
}

   void luuVaoFile(ofstream& ofs) const {
// Ghi tat ca truong vao file CSV
    ofs << maSo << "," << hoVaTen << "," << soDienThoai << "," << diaChi << ","
        << email << "," << tuoi << "," << chucVu << "," << ngayVaoLam << "," << luongCoBan << "\n";
}

   static void tieuDe() {
	// Tieu de cot bang nhan vien
    cout << "\n+-----------+---------------------+------+--------------+--------------------------+-----------------------+----------------+-----------+\n";
    cout << "| " << left << setw(10) << "Ma NV"
         << "| " << setw(20) << "Ho va Ten"
         << "| " << setw(5) << "Tuoi"
         << "| " << setw(13) << "So DT"
         << "| " << setw(25) << "Email"
         << "| " << setw(22) << "Dia Chi"
         << "| " << setw(15) << "Chuc Vu"
         << "| " << setw(10) << "Ngay VL" << "|\n";
    cout << "+-----------+---------------------+------+--------------+--------------------------+-----------------------+----------------+-----------+" << endl;
}

   void deserializeLine(const string& line) {
	// Load du lieu tu 1 dong file CSV
    stringstream ss(line);
    getline(ss, maSo, ',');
    getline(ss, hoVaTen, ',');
    getline(ss, soDienThoai, ',');
    getline(ss, diaChi, ',');
    getline(ss, email, ',');
    ss >> tuoi; ss.ignore();
    getline(ss, chucVu, ',');
    getline(ss, ngayVaoLam, ',');
    ss >> luongCoBan; ss.ignore();
}

void xuatChiTiet() const {
	// In chi tiet theo kieu form thong tin
    cout << "\n+------------------------------------------------+";
    cout << "\n|---------------CHI TIET NHAN VIEN --------------|\n";
    cout << "+----------------+-------------------------------+\n";
    cout << "| Ma nhan vien   | " << left << setw(30) << maSo << "|\n";
    cout << "| Ten nhan vien  | " << left << setw(30) << hoVaTen << "|\n";
    cout << "| Dia chi        | " << left << setw(30) << diaChi << "|\n";
    cout << "| So dien thoai  | " << left << setw(30) << soDienThoai << "|\n";
    cout << "| Email          | " << left << setw(30) << email << "|\n";
    cout << "| Tuoi           | " << left << setw(30) << tuoi << "|\n";
    cout << "| Chuc vu        | " << left << setw(30) << chucVu << "|\n";
    cout << "| Ngay vao lam   | " << left << setw(30) << ngayVaoLam << "|\n";
    cout << "| Luong theo gio | " << left << setw(30) 
         << (to_string((long long)luongCoBan) + " VND") << "|\n";
    cout << "+------------------------------------------------+\n";
}

};

//nha cung cap 
class NhaCungCap {
private:
    string maNhaCungCap;
    string tenNhaCungCap;
    string diaChi;
    string soDienThoai;
    string email;
 
    
public:
    NhaCungCap(): maNhaCungCap(""), tenNhaCungCap(""), diaChi(""), soDienThoai(""), email("")
                   {}
    ~NhaCungCap() {}

// nhap thong tin
    void nhapThongTin() {
    cout << "\n--- Nhap Nha Cung Cap ---\n";
    maNhaCungCap = docMaSo("Nhap ma nha cung cap: ");
    tenNhaCungCap = docChuoiKhongChuaSo("Nhap ten nha cung cap: ");
    diaChi = docMaSo("Nhap dia chi: ");
    
    while (true) {
        cout << "Nhap so dien thoai: ";
        if (!getline(cin, soDienThoai)) continue;
        if (soDienThoai.empty()) { 
            cout << "? Khong duoc de trong. Nhap lai.\n"; 
            continue; 
        }
        
       
        string temp = "";
        for (size_t i = 0; i < soDienThoai.size(); ++i) {
            if (soDienThoai[i] != ' ') temp += soDienThoai[i];
        }
        
        
        if (temp[0] == '-') {
            cout << "? So dien thoai khong duoc la so am. Nhap lai.\n";
            continue;
        }
        
        // Kiem tra ky tu hop le: chi cho phep chu so va dau +
        bool ok = true;
        for (size_t i = 0; i < temp.size(); ++i) {
            char c = temp[i];
            if (!(isdigit((unsigned char)c) || c=='+')) { 
                ok = false; 
                break; 
            }
        }
        if (!ok) { 
            cout << "? So dien thoai chi chua chu so va dau +. Nhap lai.\n"; 
            continue; 
        }
        
        soDienThoai = temp;
        break;  
    }
    
    // Nhap email: bat buoc co ky tu '@'
    while (true) {
        cout << "Nhap email: ";
        if (!getline(cin, email)) continue;
        if (email.empty()) { 
            cout << "? Khong duoc de trong. Nhap lai.\n"; 
            continue; 
        }
        if (email.find('@') == string::npos) { 
            cout << "? Email khong hop le (khong co @). Nhap lai.\n"; 
            continue; 
        }
        break;  
    }
   
    
 }
// sua thong tin
    void suaThongTin() {
        cout << "\n--- Sua Nha Cung Cap ---\n";
        tenNhaCungCap = docChuoiKhongChuaSo("Nhap ten nha cung cap moi: ");
        diaChi = docMaSo("Nhap dia chi moi: ");
        while (true) {
    cout << "Nhap so dien thoai moi: ";
    if (!getline(cin, soDienThoai)) continue;
    if (soDienThoai.empty()) { 
        cout << "? Khong duoc de trong. Nhap lai.\n"; 
        continue; 
    }
    // Loai bo khoang trang trong chuoi nhap
    string temp = "";
    for (size_t i = 0; i < soDienThoai.size(); ++i) {
        if (soDienThoai[i] != ' ') temp += soDienThoai[i];
    }
    
    if (temp[0] == '-') {
        cout << "? So dien thoai khong duoc la so am. Nhap lai.\n";
        continue;
    }
    
    bool ok = true;
    for (size_t i = 0; i < temp.size(); ++i) {
        char c = temp[i];
        if (!(isdigit((unsigned char)c) || c=='+')) { 
            ok = false; 
            break; 
        }
    }
    if (!ok) { 
        cout << "? So dien thoai chi chua chu so va dau +. Nhap lai.\n"; 
        continue; 
    }
    
    soDienThoai = temp;
    break;
}// Nhap email moi
        while (true) {
            cout << "Nhap email moi: ";
            if (!getline(cin, email)) continue;
            if (email.empty()) { cout << "? Khong duoc de trong. Nhap lai.\n"; continue; }
            if (email.find('@') == string::npos) { cout << "? Email khong hop le (khong co @). Nhap lai.\n"; continue; }
            break;
        }
    }
   	// xuat thong tin
    void xuatThongTin() const {
        cout << "| " << left << setw(10) << maNhaCungCap
             << "| " << setw(23) << tenNhaCungCap
             << "| " << setw(18) << soDienThoai
             << "| " << setw(28) << diaChi << "|\n";
        cout << "+-----------+------------------------+-------------------+-----------------------------+" << endl;
    }
    
    // nhap giao dich
    void nhapGiaoDich(std::vector<HangHoa>& kho);
	// luu file
    void luuVaoFile(ofstream& ofs) const {
        ofs << maNhaCungCap << "," << tenNhaCungCap << "," << diaChi << "," << soDienThoai << "," << email << "\n";
    }

    string getMaNCC() const { return maNhaCungCap; }
    string getTenNCC() const { return tenNhaCungCap; }
      // In tieu de bang khi hien thi danh sach NCC
    static void tieuDe() {
        cout << "\n+-----------+------------------------+-------------------+-----------------------------+\n";
        cout << "| " << left << setw(10) << "Ma NCC"
             << "| " << setw(23) << "Ten NCC"
             << "| " << setw(18) << "SDT"
             << "| " << setw(28) << "Dia Chi"  << "|\n";
        cout << "+-----------+------------------------+-------------------+-----------------------------+" << endl;
    }
	//item
    void deserializeLine(const string& line) {
        stringstream ss(line);
        getline(ss, maNhaCungCap, ',');
        getline(ss, tenNhaCungCap, ',');
        getline(ss, diaChi, ',');
        getline(ss, soDienThoai, ',');
        getline(ss, email, ',');

    string item;
    while (getline(ss, item, ',')) {
        stringstream itemss(item);
        string ma, ten, loai, sl, gia;
        getline(itemss, ma, '|');
        getline(itemss, ten, '|');
        getline(itemss, loai, '|');
        getline(itemss, sl, '|');
        getline(itemss, gia, '|');
        
      
    }
}
	// xuat chi tiet
    void xuatChiTiet() const {
    cout << "\n+------------------------------------------------+";
    cout << "\n|----------CHI TIET NHA CUNG CAP ----------------|\n";
    cout << "+----------------+-------------------------------+\n";
    cout << "| Ma NCC         | " << left << setw(30) << maNhaCungCap << "|\n";
    cout << "| Ten NCC        | " << left << setw(30) << tenNhaCungCap << "|\n";
    cout << "| Dia chi        | " << left << setw(30) << diaChi << "|\n";
    cout << "| So dien thoai  | " << left << setw(30) << soDienThoai << "|\n";
    cout << "| Email          | " << left << setw(30) << email << "|\n";

    cout << "+------------------------------------------------+\n";
}
    bool operator==(const NhaCungCap& other) const {
        return (maNhaCungCap == other.maNhaCungCap || soDienThoai == other.soDienThoai);
    }
    
    
};


//hang hoa
class HangHoa {
private:
    string maHangHoa;
    string tenHangHoa;
    string loaiHang;
    string maNhaCungCap;
    string donViTinh;
    int soLuongTon;
    string ngayNhap;
    string ngayHetHan;
    double donGia;
    double mucGiamGia;
    bool conHang;
public:
    HangHoa(): maHangHoa(""), tenHangHoa(""), loaiHang(""), maNhaCungCap(""), donViTinh(""),
               soLuongTon(0), ngayNhap(""), ngayHetHan(""), donGia(0), mucGiamGia(0), conHang(true) {}
    ~HangHoa() {}
// nhap thong tin
    void nhapThongTin() {
        cout << "\n--- Nhap Hang Hoa ---\n";
        maHangHoa = docMaSo("Nhap ma hang hoa: ");
        tenHangHoa = docChuoiKhongChuaSo("Nhap ten hang hoa: ");
        loaiHang = docChuoiKhongChuaSo("Nhap loai hang: ");
        maNhaCungCap = docMaSo("Nhap ma nha cung cap: ");
        donViTinh = docMaSo("Nhap don vi tinh (vd: cai/kg/lit): ");
        soLuongTon = docSoNguyenKhongAm("Nhap so luong ton (>=0): ");
        donGia = docSoThucKhongAm("Nhap don gia (>=0): ");
double tongGiaTri = donGia * soLuongTon;
cout << "\n>>> Tong gia tri hang hoa nay cho NCC " << maNhaCungCap 
     << ": " << fixed << setprecision(0) << tongGiaTri << " VND\n";

        ngayNhap = docNgay("Nhap ngay nhap");
        ngayHetHan = docNgay("Nhap ngay het han");
        int d1,m1,y1,d2,m2,y2;
        sscanf(ngayNhap.c_str(), "%d/%d/%d", &d1,&m1,&y1);
        sscanf(ngayHetHan.c_str(), "%d/%d/%d", &d2,&m2,&y2);
        bool after = false;
        if (y2>y1) after=true;
        else if (y2==y1 && m2>m1) after=true;
        else if (y2==y1 && m2==m1 && d2>d1) after=true;
        if (!after) {
            cout << "? Ngay het han phai sau ngay nhap. Se yeu cau nhap lai.\n";
            ngayHetHan = docNgay("Nhap lai ngay het han");
        }
        mucGiamGia = docSoThucKhongAm("Nhap muc giam gia (%) (0-100): ");
        if (mucGiamGia < 0) mucGiamGia = 0;
        if (mucGiamGia > 100) mucGiamGia = 100;
        int tt = docSoNguyenKhongAm("Trang thai (1-Con hang / 0-Het hang): ");
        conHang = (tt == 1);
    }
	//sua thong tin
    void suaThongTin() {
        cout << "\n--- Sua Hang Hoa ---\n";
        tenHangHoa = docChuoiKhongChuaSo("Nhap ten hang hoa moi: ");
        loaiHang = docChuoiKhongChuaSo("Nhap loai hang moi: ");
        maNhaCungCap = docMaSo("Nhap ma nha cung cap moi: ");
        donViTinh = docMaSo("Nhap don vi tinh moi (vd: cai/kg/lit): ");
        soLuongTon = docSoNguyenKhongAm("Nhap so luong ton moi (>=0): ");
        donGia = docSoThucKhongAm("Nhap don gia moi (>=0): ");
        ngayNhap = docNgay("Nhap ngay nhap moi");
        ngayHetHan = docNgay("Nhap ngay het han moi");
        int d1,m1,y1,d2,m2,y2;
        sscanf(ngayNhap.c_str(), "%d/%d/%d", &d1,&m1,&y1);
        sscanf(ngayHetHan.c_str(), "%d/%d/%d", &d2,&m2,&y2);
        bool after = false;
        if (y2>y1) after=true;
        else if (y2==y1 && m2>m1) after=true;
        else if (y2==y1 && m2==m1 && d2>d1) after=true;
        if (!after) {
            cout << "? Ngay het han phai sau ngay nhap. Se yeu cau nhap lai.\n";
            ngayHetHan = docNgay("Nhap lai ngay het han");
        }
        mucGiamGia = docSoThucKhongAm("Nhap muc giam gia moi (%) (0-100): ");
        if (mucGiamGia < 0) mucGiamGia = 0;
        if (mucGiamGia > 100) mucGiamGia = 100;
        int tt = docSoNguyenKhongAm("Trang thai moi (1-Con hang / 0-Het hang): ");
        conHang = (tt == 1);
    }
	//xuat thong tin
    void xuatThongTin() const {
    cout << "|" << left << setw(12) << maHangHoa
         << "|" << setw(27) << tenHangHoa
         << "|" << setw(14) << loaiHang
         << "|" << setw(14) << maNhaCungCap
         << "|" << setw(10)  << donViTinh
         << "|" << right << setw(6) << soLuongTon
         << "|" << setw(14) << fixed << setprecision(0) << donGia
         << "|" << setw(10)  << mucGiamGia
         << "|" << setw(14) << (conHang ? "Con hang" : "Het hang")
         << "|\n";

    cout << "+------------+---------------------------+--------------+--------------+----------+------+--------------+----------+--------------+\n";
}
// xuat chi tiet
void xuatChiTiet() const {
	cout << "\n+------------------------------------------------+";
    cout << "\n|---------------CHI TIET HANG HOA ---------------|\n";
    cout << "+----------------+-------------------------------+\n";
    cout << "| Ma hang hoa    | " << left << setw(30) << maHangHoa << "|\n";
    cout << "| Ten hang hoa   | " << left << setw(30) << tenHangHoa << "|\n";
    cout << "| Loai hang      | " << left << setw(30) << loaiHang << "|\n";
    cout << "| Ngay nhap      | " << left << setw(30) << ngayNhap << "|\n";
    cout << "| Ngay het han   | " << left << setw(30) << ngayHetHan << "|\n";

    cout << "| So luong ton   | " << left << setw(30) 
         << (to_string(soLuongTon) + " " + donViTinh) << "|\n";

    cout << "| Don gia        | " 
         << left << setw(30) << (to_string((long long)donGia) + " VND") << "|\n";

    cout << "| Muc giam gia   | " 
         << left << setw(30) << (to_string(mucGiamGia) + "%") << "|\n";

    cout << "| Trang thai     | " 
         << left << setw(30) << (conHang ? "Con hang" : "Het hang") << "|\n";

    cout << "| Ma NCC         | " << left << setw(30) << maNhaCungCap << "|\n";

    cout << "+------------------------------------------------+\n";
}
    // Trong class HangHoa - public methods
    void nhapTuGiaoDich(const string& ma, const string& ten, const string& loai, 
                    const string& maNCC_in, int sl, double gia) {
        maHangHoa = ma;
        tenHangHoa = ten;
        loaiHang = loai;
        maNhaCungCap = maNCC_in;
        donViTinh = "chua_co";
        soLuongTon = sl;
        donGia = gia;
        ngayNhap = "hom_nay";
        ngayHetHan = "chua_co";
        mucGiamGia = 0.0;
        conHang = (soLuongTon > 0);
    }
    //don gia
    void setDonGia(double gia) {
        donGia = gia;
    }
	//luu file
    void luuVaoFile(ofstream& ofs) const {
        ofs << maHangHoa << "," << tenHangHoa << "," << loaiHang << "," << maNhaCungCap << ","
            << donViTinh << "," << soLuongTon << "," << donGia << "," << ngayNhap << ","
            << ngayHetHan << "," << mucGiamGia << "," << conHang << "\n";
    }

    string getMaHH() const { return maHangHoa; }
    string getTenHH() const { return tenHangHoa; }
    string getMaNCC() const { return maNhaCungCap; }
    int getSoLuong() const { return soLuongTon; }

   
    double getDonGia() const { return donGia; }
    double getMucGiamGia() const { return mucGiamGia; }
	

    void capNhatTuNhaCungCap(int soLuongThem, double giaMoi, const string& maNCC) {
        if (soLuongThem > 0) {
            soLuongTon += soLuongThem;  // Tang ton kho
            donGia = giaMoi;  // cap nhap gia moi nha cung cap
            maNhaCungCap = maNCC;  // lien ket vi tri nha cung cap
            conHang = (soLuongTon > 0);  // Cap nhap trang thai
double tongGiaTri = giaMoi * soLuongTon;
cout << ">>> Tong gia tri moi cho NCC " << maNCC 
     << ": " << fixed << setprecision(0) << tongGiaTri << " VND\n";

            cout << "* Da cap nhat hang hoa " << maHangHoa << ": SL tang " << soLuongThem 
                 << ", Gia moi: " << fixed << setprecision(0) << giaMoi << endl;
        } else {
            cout << "? So luong them phai > 0. Khong cap nhat!\n";
        }
    }
	//giam so luong trong ton khi
    void giamSoLuongTon(int sl) {
        if (sl == 0) return;
        if (sl > 0) {
            if (sl <= soLuongTon) {
                soLuongTon -= sl;
                if (soLuongTon == 0) conHang = false;
            }
        } else { // sl < 0 : tang kho
            int add = -sl;
            soLuongTon += add;
            if (soLuongTon > 0) conHang = true;
        }
    }
	//IN TIEU DE KHI HIEN THI DANH SACH HANG
    static void tieuDe() {
    cout << "\n+------------+---------------------------+--------------+--------------+----------+------+--------------+----------+--------------+\n";
    cout << "|" << left << setw(12) << "MaHH"
         << "|" << setw(27) << "Ten Hang"
         << "|" << setw(14) << "Loai"
         << "|" << setw(14) << "MaNCC"
         << "|" << setw(10) << "DVT"
         << "|" << right << setw(6) << "SL"
         << "|" << setw(14) << "Don Gia"
         << "|" << setw(10) << "Giam%"
         << "|" << setw(14) << "TrangThai" << "|\n";
    cout << "+------------+---------------------------+--------------+--------------+----------+------+--------------+----------+--------------+\n";
}
	//phan tich dong CSV de khoi tao doi tuong
    void deserializeLine(const string& line) {
        stringstream ss(line);
        getline(ss, maHangHoa, ',');
        getline(ss, tenHangHoa, ',');
        getline(ss, loaiHang, ',');
        getline(ss, maNhaCungCap, ',');
        getline(ss, donViTinh, ',');
        ss >> soLuongTon; ss.ignore();
        ss >> donGia; ss.ignore();
        getline(ss, ngayNhap, ',');
        getline(ss, ngayHetHan, ',');
        ss >> mucGiamGia; ss.ignore();
        ss >> conHang;
    }
	// So sanh theo ma hang
    bool operator==(const HangHoa& other) const { return maHangHoa == other.maHangHoa; }

    // In thong tin ngan gon bang ostream
    friend ostream& operator<<(ostream& os, const HangHoa& hh);
};

ostream& operator<<(ostream& os, const HangHoa& hh) {
    os << "MaHH: " << hh.maHangHoa << ", Ten: " << hh.tenHangHoa << ", Loai: " << hh.loaiHang << ", MaNCC: " << hh.maNhaCungCap << ", SL: " << hh.soLuongTon << ", Don Gia: " << fixed << setprecision(0) << hh.donGia << ", Giam%: " << hh.mucGiamGia << ", Trang thai: " << (hh.conHang ? "Con hang" : "Het hang");
    return os;
}

// Tim kiem khong phan biet hoa thuong
int findHangIndexByMa(const std::vector<HangHoa>& kho, const std::string& ma) {
    string maUpper = toUpperCase(ma);
    for (size_t i = 0; i < kho.size(); ++i) {
        if (toUpperCase(kho[i].getMaHH()) == maUpper) 
            return static_cast<int>(i);
    }
    return -1;
}
//theo ten 
int findHangIndexByTen(const std::vector<HangHoa>& kho, const std::string& ten) {
    string tenLower = toLowerCase(ten);
    for (size_t i = 0; i < kho.size(); ++i) {
        if (toLowerCase(kho[i].getTenHH()) == tenLower) 
            return static_cast<int>(i);
    }
    return -1;
}

// nhap giao dich tu nha cung cap
void NhaCungCap::nhapGiaoDich(std::vector<HangHoa>& kho) {
    cout << "\n--- Nhap Giao Dich Nhap Hang Tu NCC " << maNhaCungCap << " ---\n";
    int soLan = docSoNguyenKhongAm("Nhap so luong mat hang can nhap: ");
    if (soLan <= 0) return;
    
    for (int i = 0; i < soLan; ++i) {
        cout << "\nMat hang thu " << i + 1 << ":\n";
        
        string ma;
        cout << " Ma hang (Enter de tu sinh neu khong nho): ";
        if (!getline(cin, ma)) ma = "";
        
        string ten = docChuoiKhongChuaSo(" Ten mat hang: ");
        string loai;
        cout << " Loai hang: ";
        if (!getline(cin, loai)) loai = "";
        
        int sl = docSoNguyenKhongAm(" So luong nhap: ");
        double gia = docSoThucKhongAm(" Don gia nhap: ");

        int idx = -1;
        
        if (!ma.empty()) {
            idx = findHangIndexByMa(kho, ma);
        }
        
        if (idx == -1 && !ten.empty()) {
            idx = findHangIndexByTen(kho, ten);
        }
        
        if (idx != -1) {
             // Neu tim thay trong kho thi cap nhat
            int soLuongCu = kho[idx].getSoLuong();
            kho[idx].capNhatTuNhaCungCap(sl, gia, this->maNhaCungCap);
            cout << " -> Da cap nhat kho: " << kho[idx].getMaHH() 
                 << " (SL cu: " << soLuongCu 
                 << " -> SL moi: " << kho[idx].getSoLuong() << ").\n";
        } else {
            
            if (ma.empty()) {
                string p1 = ten.size() >= 3 ? ten.substr(0,3) : ten;
                string p2 = maNhaCungCap.size() >= 3 ? maNhaCungCap.substr(0,3) : maNhaCungCap;
                ma = "AUTO_" + p1 + "_" + p2;
                
                // dam bao ma hang không trùng
                int counter = 1;
                std::string originalMa = ma;
                while (findHangIndexByMa(kho, ma) != -1) {
                    std::stringstream ss;
                    ss << originalMa << "_" << counter;
                    ma = ss.str();
                    counter++;
                }
            }
            
            HangHoa hh;
            hh.nhapTuGiaoDich(ma, ten, loai, this->maNhaCungCap, sl, gia);
            kho.push_back(hh);
            cout << " -> Them hang moi vao kho: " << hh.getMaHH() 
                 << " (SL = " << sl << ").\n";
        }
        
        // Cap nhap thong kê NCC

    }
    

}


//chi tiet hoa don
class ChiTietHoaDon {
private:
    string maHang;
    string tenHangHoa;
    int soLuong;
    double donGia;
    double giaBan;      
    double giamGia; 
    double tienGoc;
    double tienGiam;
    double tienThanhToan;
public:
    ChiTietHoaDon() {
        maHang = "";
        tenHangHoa = "";
        soLuong = 0;
        donGia = 0.0;
        giaBan = 0.0;  
        giamGia = 0.0;
        tienGoc = tienGiam = tienThanhToan = 0.0;
    }
    ChiTietHoaDon(const string& m,const string& h ,int sl, double dg, double gg) {
        maHang = m;
        tenHangHoa = h;
        soLuong = sl;
        donGia = dg;
        giaBan = dg * 1.3;  // gia ban = don gia *1.3
        giamGia = gg;
        tinhTien();// tinh cac truong tienGoc, tienGiam, tienThanhToan
    }
    
//ham tinh tien
   void tinhTien() {
        tienGoc = giaBan * soLuong;  
        tienGiam = tienGoc * (giamGia / 100.0);
        tienThanhToan = tienGoc - tienGiam;
    }

    string getMaHang() const { return maHang; }
    string gettenHangHoa() const { return tenHangHoa;}
    int getSoLuong() const { return soLuong; }
    double getDonGia() const { return donGia; }
    double getGiamGia() const { return giamGia; }
    double getGiaBan() const { return giaBan; }  
    double getTienGoc() const { return tienGoc; }
    double getTienGiam() const { return tienGiam; }
    double getTienThanhToan() const { return tienThanhToan; }

    void setSoLuong(int sl) { soLuong = sl; tinhTien(); }
    void setDonGia(double dg) { 
        donGia = dg; 
        giaBan = dg * 1.3;  
        tinhTien(); 
    }
    void setGiamGia(double gg) { giamGia = gg; tinhTien(); }
};

//hoa don
class HoaDon {
private:
    string maHoaDon;
    string tenHangHoa;
    string maKhachHang;
    string ngayLap;  
    vector<ChiTietHoaDon> dsCT;
    bool daThanhToan;
public:
    HoaDon() { 
        maHoaDon = "";
        tenHangHoa = ""; 
        maKhachHang = ""; 
        ngayLap = "";  
        daThanhToan = false; 
    }
    
    HoaDon(const string& mhd, const string& thh, const string& mkh) { 
        maHoaDon = mhd;
        tenHangHoa=thh; 
        maKhachHang = mkh; 
        ngayLap = "";  
        daThanhToan = false; 
    }
// getters / setters 
    void setMaHD(const string& m) { maHoaDon = m; }
    void setMaKH(const string& k) { maKhachHang = k; }
    void settenHangHoa(const string& h) { tenHangHoa = h;}
    string getMaHD() const { return maHoaDon; }
    string getMaKH() const { return maKhachHang; }
    string gettenHangHoa() const { return tenHangHoa;}
    void setNgayLap(const string& nl) { ngayLap = nl; }
    string getNgayLap() const { return ngayLap; }

    bool isDaThanhToan() const { return daThanhToan; }

    // them mat hang (chua tru ton kho )
    bool themMatHang(const HangHoa& hh, int sl) {
        if (daThanhToan) return false;
        if (sl <= 0) return false;
        // neu mat hang da co thi cong so luong
        for (size_t i = 0; i < dsCT.size(); ++i) {
            if (dsCT[i].getMaHang() == hh.getMaHH()) {
                int newSL = dsCT[i].getSoLuong() + sl;
                dsCT[i].setSoLuong(newSL);
                return true;
            }
        }
        ChiTietHoaDon ct(hh.getMaHH(), hh.getTenHH(), sl, hh.getDonGia(), hh.getMucGiamGia());
        dsCT.push_back(ct);
        return true;
    }
  // Xoa mat hang theo ma (neu chua thanh toan)
    bool xoaMatHang(const string& maHH) {
        if (daThanhToan) return false;
        for (size_t i = 0; i < dsCT.size(); ++i) {
            if (dsCT[i].getMaHang() == maHH) {
                dsCT.erase(dsCT.begin() + i);
                return true;
            }
        }
        return false;
    }
// Sua so luong mat hang co san trong hoa don
    bool suaSoLuong(const string& maHH, int slMoi) {
        if (daThanhToan) return false;
        if (slMoi <= 0) return false;
        for (size_t i = 0; i < dsCT.size(); ++i) {
            if (dsCT[i].getMaHang() == maHH) {
                dsCT[i].setSoLuong(slMoi);
                return true;
            }
        }
        return false;
    }
//Tong hop so tien trong hoa don
    double tongTienGoc() const {
        double s = 0;
        for (size_t i = 0; i < dsCT.size(); ++i) s += dsCT[i].getTienGoc();
        return s;
    }
    double tongTienGiam() const {
        double s = 0;
        for (size_t i = 0; i < dsCT.size(); ++i) s += dsCT[i].getTienGiam();
        return s;
    }
    double tongThanhToan() const {
        double s = 0;
        for (size_t i = 0; i < dsCT.size(); ++i) s += dsCT[i].getTienThanhToan();
        return s;
    }
//xuat hoa don
   void xuatHoaDon() const {
    cout << "\n===== HOA DON: " << maHoaDon << " =====\n";
    cout << "Khach hang: " << maKhachHang << "\n";
    cout << "Ngay lap: " << ngayLap << "\n\n"; 
    cout << left << setw(12) << "MaHH"
         << setw(25) << "Ten Hang"      
         << setw(8) << "SL"
         << setw(12) << "Gia Ban"
         << setw(8) << "Giam%"
         << setw(15) << "TienGoc"
         << setw(15) << "TienGiam"
         << setw(15) << "ThanhTien" << endl;
    cout << string(110, '-') << endl;   
    
    for (size_t i = 0; i < dsCT.size(); ++i) {
        const ChiTietHoaDon& ct = dsCT[i];
        cout << left << setw(12) << ct.getMaHang()
             << setw(25) << ct.gettenHangHoa()  
             << setw(8) << ct.getSoLuong()
             << setw(12) << fixed << setprecision(0) << ct.getGiaBan()
             << setw(8) << ct.getGiamGia()
             << setw(15) << fixed << setprecision(0) << ct.getTienGoc()
             << setw(15) << fixed << setprecision(0) << ct.getTienGiam()
             << setw(15) << fixed << setprecision(0) << ct.getTienThanhToan()
             << endl;
    }
    cout << string(110, '-') << endl;   
    cout << "Tong tien goc : " << fixed << setprecision(0) << tongTienGoc() << endl;
    cout << "Tong tien giam : " << fixed << setprecision(0) << tongTienGiam() << endl;
    cout << "Tong thanh toan: " << fixed << setprecision(0) << tongThanhToan() << endl;
}
    // ham thanh toan
    void thanhToan() { daThanhToan = true; }
	// nhap thong tin
	void nhapThongTin() {
    	cout << "\n--- Nhap Hoa Don ---\n";
    	maHoaDon = docMaSo("Nhap ma hoa don: ");
    	maKhachHang = docMaSo("Nhap ma khach hang: ");
    	
	}
	// sua thong tin
	void suaThongTin() {
    	cout << "\n--- Sua Hoa Don ---\n";
    	maKhachHang = docMaSo("Nhap ma khach hang moi: ");
    
	}

	string getMaHH() const {
    	
    	if (!dsCT.empty()) return dsCT[0].getMaHang();
    	return "";
	}	

	int getSoLuong() const {
    	// vi tri, so luong
    	int total = 0;
    	for (size_t i = 0; i < dsCT.size(); ++i) {
       	 total += dsCT[i].getSoLuong();
   	 }
    	return total;
	}
	
    // luu vao file 
void luuVaoFile(ofstream& ofs) const {
    ofs << maHoaDon << "," << maKhachHang << "," << ngayLap << "," 
        << daThanhToan << "," << dsCT.size() << ",";  
    for (size_t i = 0; i < dsCT.size(); ++i) {
        const ChiTietHoaDon& ct = dsCT[i];
        ofs << ct.getMaHang() << "|" 
            << ct.gettenHangHoa() << "|"
            << ct.getSoLuong() << "|" 
            << ct.getDonGia() << "|"
            << ct.getGiaBan() << "|"
            << ct.getGiamGia();
        if (i + 1 < dsCT.size()) ofs << ";";
    }
    ofs << "\n";
}
    
//PHUC HOI TU 1 DONG FILE
   void deserializeLine(const string& line) {
    dsCT.clear();
    stringstream ss(line);
    string mhd, mkh, nl, ttStr, sc, items;  
    getline(ss, mhd, ',');
    getline(ss, mkh, ',');
    getline(ss, nl, ',');   
    getline(ss, ttStr, ',');
    getline(ss, sc, ',');
    getline(ss, items);
    
    maHoaDon = mhd;
    maKhachHang = mkh;
    ngayLap = nl;  
    daThanhToan = (ttStr == "1");
    
    string tmp = items;
    while (!tmp.empty()) {
        size_t sep = tmp.find(';');
        string token;
        if (sep == string::npos) { token = tmp; tmp = ""; }
        else { token = tmp.substr(0, sep); tmp = tmp.substr(sep + 1); }
        
        stringstream it(token);
        string ma, ten, sls, dg, gb, gg;
        getline(it, ma, '|');
        getline(it, ten, '|');      
        getline(it, sls, '|');
        getline(it, dg, '|');
        getline(it, gb, '|');
        getline(it, gg, '|');
        
        int sl = atoi(sls.c_str());
        double don = atof(dg.c_str());
        double g = atof(gg.c_str());
        ChiTietHoaDon ct(ma, ten, sl, don, g);
        dsCT.push_back(ct);
    }
}

    vector<ChiTietHoaDon>& getChiTiet() { return dsCT; }

    friend ostream& operator<<(ostream& os, const HoaDon& hd);
};

ostream& operator<<(ostream& os, const HoaDon& hd) {
    os << "MaHD: " << hd.maHoaDon << ", MaKH: " << hd.maKhachHang << ", Tong TT: " << fixed << setprecision(0) << hd.tongThanhToan() << ", Da thanh toan: " << (hd.daThanhToan ? "Co" : "Khong");
    return os;
}

// Ham thu vien dung de luu/nap cac doi tuong vao file
template<typename T>
void appendToFile(const string& filename, const T& item) {
    ofstream ofs(filename.c_str(), ios::app);
    if (ofs.is_open()) {
        item.luuVaoFile(ofs);
        ofs.close();
    } else {
        cerr << "? Khong the mo file " << filename << " de ghi.\n";
    }
}

template<typename T>
void loadFromFile(const string& filename, vector<T>& vec) {
    ifstream ifs(filename.c_str());
    if (!ifs.is_open()) return;
    string line;
    while (getline(ifs, line)) {
        if (line.empty()) continue;
        T item;
        item.deserializeLine(line);
        vec.push_back(item);
    }
    ifs.close();
}

template<typename T>
void saveToFile(const string& filename, const vector<T>& vec) {
    ofstream ofs(filename.c_str());
    if (!ofs.is_open()) {
        cerr << "? Khong the mo file " << filename << " de ghi.\n";
        return;
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i].luuVaoFile(ofs);
    }
    ofs.close();
}

//quanly
class QuanLy {
private:
    vector<KhachHang> dsKH;
    vector<NhanVien> dsNV;
    vector<NhaCungCap> dsNCC;
    vector<HangHoa> dsHH;
    vector<HoaDon> dsHD;

    const string fileKH;
    const string fileNV;
    const string fileNCC;
    const string fileHH;
    const string fileHD;
// HAM KIEM TRA TON TAI THEO MA
    bool existsMaKH(const string& ma) const {
        for (size_t i = 0; i < dsKH.size(); ++i) if (dsKH[i].getMa() == ma) return true;
        return false;
    }
    bool existsMaNV(const string& ma) const {
        for (size_t i = 0; i < dsNV.size(); ++i) if (dsNV[i].getMa() == ma) return true;
        return false;
    }
    bool existsMaNCC(const string& ma) const {
        for (size_t i = 0; i < dsNCC.size(); ++i) if (dsNCC[i].getMaNCC() == ma) return true;
        return false;
    }
    bool existsMaHH(const string& ma) const {
        for (size_t i = 0; i < dsHH.size(); ++i) if (dsHH[i].getMaHH() == ma) return true;
        return false;
    }
    bool existsMaHD(const string& ma) const {
        for (size_t i = 0; i < dsHD.size(); ++i) if (dsHD[i].getMaHD() == ma) return true;
        return false;
    }
    // Thêm vào phần private của class QuanLy, ví dụ sau hàm chiTietNhanVien()
void tinhTongGiaTriTheoNCC() {
    cout << "\n=====================================================\n";
    cout << "          TINH TONG GIA TRI HANG HOA THEO NCC        \n";
    cout << "=====================================================\n";
    
    string maNCC = docMaSo("Nhap ma nha cung cap: ");
    
    // Kiem tra NCC co ton tai khong
    bool nccExists = false;
    string tenNCC = "";
    for (size_t i = 0; i < dsNCC.size(); ++i) {
        if (dsNCC[i].getMaNCC() == maNCC) {
            nccExists = true;
            tenNCC = dsNCC[i].getTenNCC();
            break;
        }
    }
    
    if (!nccExists) {
        cout << "? Ma nha cung cap khong ton tai.\n";
        return;
    }
    
    // Tinh tong gia tri va liet ke hang hoa
    double tongGiaTri = 0;
    vector<size_t> dsChiSoHH;  // Luu chi so cac hang hoa cua NCC
    
    for (size_t i = 0; i < dsHH.size(); ++i) {
        if (dsHH[i].getMaNCC() == maNCC) {
            tongGiaTri += dsHH[i].getDonGia() * dsHH[i].getSoLuong();
            dsChiSoHH.push_back(i);
        }
    }
    
    if (dsChiSoHH.empty()) {
        cout << "\n? Nha cung cap " << maNCC << " (" << tenNCC 
             << ") chua cung cap hang hoa nao.\n";
        return;
    }
    
    // Hien thi ket qua
    cout << "\n--- NHA CUNG CAP: " << maNCC << " - " << tenNCC << " ---\n";
    cout << "So luong mat hang: " << dsChiSoHH.size() << "\n\n";
    
    // Hien thi bang danh sach hang hoa
    cout << "+------------+---------------------------+------+--------------+-----------------+\n";
    cout << "|" << left << setw(12) << "Ma HH"
         << "|" << setw(27) << "Ten Hang"
         << "|" << right << setw(6) << "SL"
         << "|" << setw(14) << "Don Gia"
         << "|" << setw(17) << "Thanh Tien" << "|\n";
    cout << "+------------+---------------------------+------+--------------+-----------------+\n";
    
    for (size_t i = 0; i < dsChiSoHH.size(); ++i) {
        const HangHoa& hh = dsHH[dsChiSoHH[i]];
        double thanhTien = hh.getDonGia() * hh.getSoLuong();
        
        cout << "|" << left << setw(12) << hh.getMaHH()
             << "|" << setw(27) << hh.getTenHH()
             << "|" << right << setw(6) << hh.getSoLuong()
             << "|" << setw(14) << fixed << setprecision(0) << hh.getDonGia()
             << "|" << setw(17) << fixed << setprecision(0) << thanhTien << "|\n";
    }
    
    cout << "+------------+---------------------------+------+--------------+-----------------+\n";
    cout << "|" << left << setw(62) << " TONG GIA TRI"
         << "|" << right << setw(17) << fixed << setprecision(0) << tongGiaTri << "|\n";
    cout << "+------------+---------------------------+------+--------------+-----------------+\n";
    
    cout << "\n>>> Tong gia tri hang hoa tu NCC " << maNCC 
         << ": " << fixed << setprecision(0) << tongGiaTri << " VND\n";
    cout << "=====================================================\n";
}


    // Tim kiem theo ma
    void timKiemTheoMa(const vector<KhachHang>& ds) {
        string maInput;
        cout << "\nNhap ma khach hang can tim: ";
        cin >> maInput;
        cin.ignore();
        maInput = toUpperCase(maInput);
        bool found = false;
        cout << "\n";
        KhachHang::tieuDe();
        for (size_t i = 0; i < ds.size(); i++) {
            if (toUpperCase(ds[i].getMa()) == maInput) {
                ds[i].xuatThongTin();
                found = true;
            }
        }
        if (!found) {
            cout << "\n? Khong tim thay khach hang nao co ma tren!\n";
        }
    }
// tim kiem theo ma nhan vien
 void timKiemTheoMaNV(const vector<NhanVien>& ds) {
    string maInput;
    cout << "\nNhap ma nhan vien can tim: ";
    cin >> maInput;
    cin.ignore();
    maInput = toUpperCase(maInput);
    bool found = false;
    
    for (size_t i = 0; i < ds.size(); i++) {
        if (toUpperCase(ds[i].getMa()) == maInput) {
            cout << "\n* Tim thay nhan vien: " << ds[i].getTen() << "\n";
            found = true;
            break;  
        }
    }
    
    if (!found) {
        cout << "\n? Khong tim thay nhan vien nao co ma " << maInput << "!\n";
    }
}

// tim kiem theo ma ncc
  void timKiemTheoMaNCC(const vector<NhaCungCap>& ds) {
    string maInput;
    cout << "\nNhap ma nha cung cap can tim: ";
    cin >> maInput;
    cin.ignore();
    maInput = toUpperCase(maInput);
    bool found = false;
    
    for (size_t i = 0; i < ds.size(); i++) {
        if (toUpperCase(ds[i].getMaNCC()) == maInput) {
            cout << "\n* Tim thay nha cung cap: " << ds[i].getTenNCC() << "\n";
            found = true;
            break;  // Dung sao khi tim thay
        }
    }
    
    if (!found) {
        cout << "\n? Khong tim thay nha cung cap nao co ma " << maInput << "!\n";
    }
}




    //chi tiet nha cung cap
    void chiTietNhaCungCap() {
    string ma = docMaSo("Nhap ma nha cung cap can xem chi tiet: ");
    bool found = false;
    for (size_t i = 0; i < dsNCC.size(); ++i) {
        if (dsNCC[i].getMaNCC() == ma) {
            dsNCC[i].xuatChiTiet();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "? Khong tim thay nha cung cap co ma " << ma << ".\n";
    }
}
	// tim kiem theo ma hh
   void timKiemTheoMaHH(const vector<HangHoa>& ds) {
    string maInput;
    cout << "\nNhap ma hang hoa can tim: ";
    cin >> maInput;
    cin.ignore();
    maInput = toUpperCase(maInput);
    bool found = false;
    
    for (size_t i = 0; i < ds.size(); i++) {
        if (toUpperCase(ds[i].getMaHH()) == maInput) {
            cout << "\n* Tim thay hang hoa: " << ds[i].getTenHH() << "\n";
            cout << "  Trang thai: " << (ds[i].getSoLuong() > 0 ? "Con hang" : "Het hang") << "\n";
            found = true;
            break;  // dung lai sau khi tim thay
        }
    }
    
    if (!found) {
        cout << "\n? Khong tim thay hang hoa nao co ma " << maInput << "!\n";
    }
}

//chi tiet hang hoa
void chiTietHangHoa() {
    string ma = docMaSo("Nhap ma hang hoa can xem chi tiet: ");
    bool found = false;
    for (size_t i = 0; i < dsHH.size(); ++i) {
        if (dsHH[i].getMaHH() == ma) {
            dsHH[i].xuatChiTiet();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "? Khong tim thay hang hoa co ma " << ma << ".\n";
    }
}
//chi tiet nhan vien
void chiTietNhanVien() {
    string ma = docMaSo("Nhap ma nhan vien can xem chi tiet: ");
    bool found = false;
    for (size_t i = 0; i < dsNV.size(); ++i) {
        if (dsNV[i].getMa() == ma) {
            dsNV[i].xuatChiTiet();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "? Khong tim thay nhan vien co ma " << ma << ".\n";
    }
}
// cap nhap so luong hang hoa
void capNhatSoLuongHangHoa() {
    cout << "\n--- Cap Nhat So Luong Hang Hoa ---\n";
    
    string maNCC = docMaSo("Nhap ma nha cung cap: ");
    if (!existsMaNCC(maNCC)) {
        cout << "? Ma nha cung cap khong ton tai.\n";
        return;
    }
    
    string maHH = docMaSo("Nhap ma hang hoa: ");
    bool found = false;
    for (size_t i = 0; i < dsHH.size(); ++i) {
        if (dsHH[i].getMaHH() == maHH) {
            found = true;
            
            // Kiem tra xem hang hoa co thuoc nha cung cap k
            if (dsHH[i].getMaNCC() != maNCC) {
                cout << "? Hang hoa nay khong thuoc nha cung cap " << maNCC << ".\n";
                cout << "  (Hang hoa thuoc NCC: " << dsHH[i].getMaNCC() << ")\n";
                return;
            }
            
            cout << "Hang hoa: " << dsHH[i].getTenHH() << "\n";
            cout << "So luong ton hien tai: " << dsHH[i].getSoLuong() << "\n";
            
            int soLuongThem = docSoNguyenKhongAm("Nhap so luong can them: ");
            
            if (soLuongThem > 0) {
                double donGiaMoi = docSoThucKhongAm("Nhap don gia: ");
                
                if (donGiaMoi > 0) {
                    dsHH[i].capNhatTuNhaCungCap(soLuongThem, donGiaMoi, maNCC);
                } else {
                    // Giu nguyên don giá cu
                    dsHH[i].capNhatTuNhaCungCap(soLuongThem, dsHH[i].getDonGia(), maNCC);
                }
                
                capNhatFileHH();
                cout << "* So luong moi: " << dsHH[i].getSoLuong() << "\n";
cout << "* Da cap nhat thanh cong!\n";

// Hiển thị tổng giá trị mới cho NCC
double tongGiaTri = dsHH[i].getDonGia() * dsHH[i].getSoLuong();
cout << ">>> Tong gia tri moi cho NCC " << maNCC 
     << ": " << fixed << setprecision(0) << tongGiaTri << " VND\n";
            } else {
                cout << "? So luong them phai lon hon 0.\n";
            }
            break;
        }
    }
    
    if (!found) {
        cout << "? Khong tim thay hang hoa co ma " << maHH << ".\n";
    }
}
   
    // Tim kiem theo tên - HH
    void timKiemTheoTenHH(const vector<HangHoa>& ds) {
    string tenInput;
    cout << "\nNhap ten (viet hoa chu cai dau) hang hoa can tim: ";
    getline(cin, tenInput);
    if (tenInput.empty()) {
        cout << "? Chuoi tim kiem khong duoc de trong!\n";
        return;
    }
    bool found = false;
    cout << "\n";
    
    for (size_t i = 0; i < ds.size(); i++) {
        if (chuaChuoiCon(ds[i].getTenHH(), tenInput)) {
            cout << "* " << ds[i].getTenHH() 
                 << " - Trang thai: " << (ds[i].getSoLuong() > 0 ? "Con hang" : "Het hang") << "\n";
            found = true;
        }
    }
    
    if (!found) {
        cout << "\n? Khong tim thay hang hoa nao chua chuoi '" << tenInput << "'!\n";
    }
}
// so luong hang hoa max
void hangHoaNhieuNhat() {
    if (dsHH.empty()) {
        cout << "\n? Chua co hang hoa nao.\n";
        return;
    }
    
    // Tim so luong lon nhat
    int maxSL = dsHH[0].getSoLuong();
    for (size_t i = 1; i < dsHH.size(); ++i) {
        if (dsHH[i].getSoLuong() > maxSL) {
            maxSL = dsHH[i].getSoLuong();
        }
    }
    
    // Hien thi tat ca hang hoa co so luong = maxSL
    cout << "\n=== HANG HOA CO SO LUONG TON NHIEU NHAT ===\n";
    cout << "So luong ton: " << maxSL << "\n\n";
    
    for (size_t i = 0; i < dsHH.size(); ++i) {
        if (dsHH[i].getSoLuong() == maxSL) {
            cout << "* Ma: " << dsHH[i].getMaHH() 
                 << " | Ten: " << dsHH[i].getTenHH() 
                 << " | So luong: " << dsHH[i].getSoLuong() << "\n";
        }
    }
    cout << "\n";
}

// hang hoa co luong min
void hangHoaBanChayNhat() {
    if (dsHH.empty()) {
        cout << "\n? Chua co hang hoa nao.\n";
        return;
    }
    
    // Tim so luong nho nhat
    int minSL = dsHH[0].getSoLuong();
    for (size_t i = 1; i < dsHH.size(); ++i) {
        if (dsHH[i].getSoLuong() < minSL) {
            minSL = dsHH[i].getSoLuong();
        }
    }
    
    // Hien thi tat ca hang hoa co so luong = minSL
    cout << "\n=== HANG HOA CO SO LUONG TON IT NHAT ===\n";
    cout << "So luong ton: " << minSL << "\n\n";
    
    for (size_t i = 0; i < dsHH.size(); ++i) {
        if (dsHH[i].getSoLuong() == minSL) {
            cout << "* Ma: " << dsHH[i].getMaHH() 
                 << " | Ten: " << dsHH[i].getTenHH() 
                 << " | So luong: " << dsHH[i].getSoLuong() << "\n";
        }
    }
    cout << "\n";
}
	//sua hoa don
    void suaHoaDon() {
        string ma = docMaSo("Nhap ma hoa don can sua: ");
        bool found = false;
        
        for (size_t i = 0; i < dsHD.size(); ++i) {
            if (dsHD[i].getMaHD() == ma) {
                found = true;
                
                if (dsHD[i].isDaThanhToan()) {
                    cout << "? Khong the sua hoa don da thanh toan.\n";
                    return;
                }
                
                cout << "\n=== HOA DON HIEN TAI ===\n";
                dsHD[i].xuatHoaDon();
                
                while (true) {
                    cout << "\n--- Sua Hoa Don " << ma << " ---\n";
                    cout << "  [1] Sua ma khach hang\n";
                    cout << "  [2] Them mat hang\n";
                    cout << "  [3] Xoa mat hang\n";
                    cout << "  [4] Sua so luong mat hang\n";
                    cout << "  [5] Xem hoa don hien tai\n";
                    cout << "  [0] Luu va thoat\n";
                    cout << "------------------------------\n";
                    
                    int choice = docSoNguyenKhongAm("Chon: ");
                    
                    if (choice == 0) {
                        capNhatFileHD();
                        cout << "* Da luu thay doi hoa don.\n";
                        break;
                    }
                    else if (choice == 1) {
                        string maKHMoi = docMaSo("Nhap ma khach hang moi: ");
                        if (!existsMaKH(maKHMoi)) {
                            cout << "? Ma khach hang khong ton tai.\n";
                        } else {
                            dsHD[i].setMaKH(maKHMoi);
                            cout << "* Da cap nhat ma khach hang.\n";
                        }
                    }
                    else if (choice == 2) {
                        string maHH = docMaSo("Nhap ma hang hoa can them: ");
                        HangHoa* pHH = NULL;
                        for (size_t j = 0; j < dsHH.size(); ++j) {
                            if (dsHH[j].getMaHH() == maHH) {
                                pHH = &dsHH[j];
                                break;
                            }
                        }
                        
                        if (!pHH) {
                            cout << "? Ma hang hoa khong ton tai.\n";
                        } else {
                            cout << "Hang hoa: " << pHH->getTenHH() 
                                 << ", Ton kho: " << pHH->getSoLuong() << endl;
                            int sl = docSoNguyenKhongAm("Nhap so luong: ");
                            
                            if (sl > pHH->getSoLuong()) {
                                cout << "? So luong vuot qua ton kho.\n";
                            } else if (sl <= 0) {
                                cout << "? So luong phai lon hon 0.\n";
                            } else {
                                if (dsHD[i].themMatHang(*pHH, sl)) {
                                    cout << "* Da them mat hang vao hoa don.\n";
                                } else {
                                    cout << "? Khong the them mat hang.\n";
                                }
                            }
                        }
                    }
                    else if (choice == 3) {
                        string maHH = docMaSo("Nhap ma hang hoa can xoa: ");
                        if (dsHD[i].xoaMatHang(maHH)) {
                            cout << "* Da xoa mat hang khoi hoa don.\n";
                        } else {
                            cout << "? Khong tim thay mat hang trong hoa don.\n";
                        }
                    }
                    else if (choice == 4) {
                        string maHH = docMaSo("Nhap ma hang hoa can sua so luong: ");
                        
                        bool coTrongHD = false;
                        for (size_t j = 0; j < dsHD[i].getChiTiet().size(); ++j) {
                            if (dsHD[i].getChiTiet()[j].getMaHang() == maHH) {
                                coTrongHD = true;
                                break;
                            }
                        }
                        
                        if (!coTrongHD) {
                            cout << "? Mat hang khong co trong hoa don.\n";
                            continue;
                        }
                        
                        HangHoa* pHH = NULL;
                        for (size_t j = 0; j < dsHH.size(); ++j) {
                            if (dsHH[j].getMaHH() == maHH) {
                                pHH = &dsHH[j];
                                break;
                            }
                        }
                        
                        if (!pHH) {
                            cout << "? Hang hoa khong ton tai trong kho.\n";
                            continue;
                        }
                        
                        cout << "Ton kho: " << pHH->getSoLuong() << endl;
                        int slMoi = docSoNguyenKhongAm("Nhap so luong moi: ");
                        
                        if (slMoi > pHH->getSoLuong()) {
                            cout << "? So luong vuot qua ton kho.\n";
                        } else if (slMoi <= 0) {
                            cout << "? So luong phai lon hon 0.\n";
                        } else {
                            if (dsHD[i].suaSoLuong(maHH, slMoi)) {
                                cout << "* Da cap nhat so luong.\n";
                            } else {
                                cout << "? Khong the cap nhat so luong.\n";
                            }
                        }
                    }
                    else if (choice == 5) {
                        dsHD[i].xuatHoaDon();
                    }
                    else {
                        cout << "? Lua chon khong hop le.\n";
                    }
                }
                break;
            }
        }
        
        if (!found) {
            cout << "? Khong tim thay hoa don co ma " << ma << ".\n";
        }
    }

    // Cap nhap file
    void capNhatFileKH() {
        saveToFile(fileKH, dsKH);
    }

    void capNhatFileNV() {
        saveToFile(fileNV, dsNV);
    }

    void capNhatFileNCC() {
        saveToFile(fileNCC, dsNCC);
    }

    void capNhatFileHH() {
        saveToFile(fileHH, dsHH);
    }

    void capNhatFileHD() {
        saveToFile(fileHD, dsHD);
    }

public:
    QuanLy() : fileKH("khachhang.txt"), fileNV("nhanvien.txt"), fileNCC("nhacungcap.txt"), fileHH("hanghoa.txt"), fileHD("hoadon.txt") {
        loadAll();
    }
    ~QuanLy() {}
    void loadAll() {
        dsKH.clear(); dsNV.clear(); dsNCC.clear(); dsHH.clear(); dsHD.clear();
        loadFromFile(fileKH, dsKH);
        loadFromFile(fileNV, dsNV);
        loadFromFile(fileNCC, dsNCC);
        loadFromFile(fileHH, dsHH);
        loadFromFile(fileHD, dsHD);

    }
	//menu khach hang
    void menuKhachHang() {
    while (true) {
        cout << "\n=====================================================\n";
        cout << "                QUAN LY KHACH HANG                   \n";
        cout << "=====================================================\n";
        cout << "  [1]  Hien danh sach khach hang\n";
        cout << "  [2]  Them khach hang\n";
        cout << "  [3]  Sua thong tin khach hang\n";
        cout << "  [4]  Xoa khach hang\n";
        cout << "  [5]  Tim kiem theo ma\n";
        cout << "  [0]  Quay lai menu truoc\n";
        cout << "-----------------------------------------------------\n";

            int ch = docSoNguyenKhongAm("Chon: ");
            if (ch==0) break;
            if (ch==1) {
                if (dsKH.empty()) cout << "? Chua co khach hang nao.\n";
                else {
                    KhachHang::tieuDe();
                    for (size_t i = 0; i < dsKH.size(); ++i) dsKH[i].xuatThongTin();
                }
            } else if (ch==2) {
                KhachHang k;
                k.nhapThongTin();
                if (existsMaKH(k.getMa())) {
                    cout << "? Ma khach hang da ton tai. Bo qua them.\n";
                } else {
                    dsKH.push_back(k);
                    appendToFile(fileKH, k);
                    cout << "* Da them khach hang va luu vao file.\n";
                }
            } else if (ch==3) {
                string ma;
                cout << "Nhap ma khach hang can sua: ";
                getline(cin, ma);
                if (ma.empty()) {
                    cout << "? Ma khong duoc de trong.\n";
                    continue;
                }
                bool found = false;
                for (size_t i = 0; i < dsKH.size(); ++i) {
                    if (dsKH[i].getMa() == ma) {
                        dsKH[i].suaThongTin();
                        capNhatFileKH();
                        cout << "* Da sua khach hang va cap nhat file.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "? Khong tim thay khach hang co ma " << ma << ".\n";
            } else if (ch==4) {
                string ma;
                cout << "Nhap ma khach hang can xoa: ";
                getline(cin, ma);
                if (ma.empty()) {
                    cout << "? Ma khong duoc de trong.\n";
                    continue;
                }
                bool found = false;
                for (size_t i = 0; i < dsKH.size(); ++i) {
                    if (dsKH[i].getMa() == ma) {
                        // Kiem tra co hoa don nao liên quan không
                        bool hasHD = false;
                        for (size_t j = 0; j < dsHD.size(); ++j) {
                            if (dsHD[j].getMaKH() == ma) {
                                hasHD = true;
                                break;
                            }
                        }
                        if (hasHD) {
                            cout << "? Khong the xoa khach hang vi co hoa don lien quan.\n";
                        } else {
                            dsKH.erase(dsKH.begin() + i);
                            capNhatFileKH();
                            cout << "* Da xoa khach hang va cap nhat file.\n";
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "? Khong tim thay khach hang co ma " << ma << ".\n";
            } else if (ch==5) {
                timKiemTheoMa(dsKH);
            }  else {
                cout << "? Lua chon khong hop le.\n";
            }
        }
    }
	// menu nhan vien
     void menuNhanVien() {
    while (true) {
        cout << "\n=====================================================\n";
        cout << "                 QUAN LY NHAN VIEN                   \n";
        cout << "=====================================================\n";
       cout << "  [1]  Hien danh sach nhan vien\n";
cout << "  [2]  Them nhan vien\n";
cout << "  [3]  Sua thong tin nhan vien\n";
cout << "  [4]  Xoa nhan vien\n";
cout << "  [5]  Tim kiem theo ma\n";
cout << "  [6]  Chi tiet nhan vien\n";
cout << "  [0]  Quay lai menu truoc\n";
cout << "-----------------------------------------------------\n";

            int ch = docSoNguyenKhongAm("Chon: ");
            if (ch==0) break;
            if (ch==1) {
                if (dsNV.empty()) cout << "? Chua co nhan vien nao.\n";
                else {
                    NhanVien::tieuDe();
                    for (size_t i = 0; i < dsNV.size(); ++i) dsNV[i].xuatThongTin();
                }
            } else if (ch==2) {
                NhanVien nv;
                nv.nhapThongTin();
                if (existsMaNV(nv.getMa())) {
                    cout << "? Ma nhan vien da ton tai. Bo qua them.\n";
                } else {
                    dsNV.push_back(nv);
                    appendToFile(fileNV, nv);
                    cout << "* Da them nhan vien va luu vao file.\n";
                }
            } else if (ch==3) {
                string ma;
                cout << "Nhap ma nhan vien can sua: ";
                getline(cin, ma);
                if (ma.empty()) {
                    cout << "? Ma khong duoc de trong.\n";
                    continue;
                }
                bool found = false;
                for (size_t i = 0; i < dsNV.size(); ++i) {
                    if (dsNV[i].getMa() == ma) {
                        dsNV[i].suaThongTin();
                        capNhatFileNV();
                        cout << "* Da sua nhan vien va cap nhat file.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "? Khong tim thay nhan vien co ma " << ma << ".\n";
            } else if (ch==4) {
                string ma;
                cout << "Nhap ma nhan vien can xoa: ";
                getline(cin, ma);
                if (ma.empty()) {
                    cout << "? Ma khong duoc de trong.\n";
                    continue;
                }
                bool found = false;
                for (size_t i = 0; i < dsNV.size(); ++i) {
                    if (dsNV[i].getMa() == ma) {
                        dsNV.erase(dsNV.begin() + i);
                        capNhatFileNV();
                        cout << "* Da xoa nhan vien va cap nhat file.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "? Khong tim thay nhan vien co ma " << ma << ".\n";
           } else if (ch==5) {
    timKiemTheoMaNV(dsNV);
} else if (ch==6) {
    chiTietNhanVien();
} else {
    cout << "? Lua chon khong hop le.\n";
}

        }
    }
	//menu nha cc
   void menuNhaCungCap() {
    while (true) {
        cout << "\n=====================================================\n";
        cout << "               QUAN LY NHA CUNG CAP                  \n";
        cout << "=====================================================\n";
        cout << "  [1]  Hien danh sach nha cung cap\n";
        cout << "  [2]  Them nha cung cap\n";
        cout << "  [3]  Sua thong tin nha cung cap\n";
        cout << "  [4]  Xoa nha cung cap\n";
        cout << "  [5]  Tim kiem theo ma\n";
        cout << "  [6]  Chi tiet nha cung cap\n";
        cout << "  [7]  Tinh tong gia tri hang hoa theo NCC\n";  // THÊM DÒNG NÀY
        cout << "  [0]  Quay lai menu truoc\n";
        cout << "-----------------------------------------------------\n";

        int ch = docSoNguyenKhongAm("Chon: ");
        if (ch==0) break;
        
        if (ch==1) {
            if (dsNCC.empty()) cout << "? Chua co nha cung cap nao.\n";
            else {
                NhaCungCap::tieuDe();
                for (size_t i = 0; i < dsNCC.size(); ++i) dsNCC[i].xuatThongTin();
            }
        } else if (ch==2) {
            NhaCungCap n;
            n.nhapThongTin();
            if (existsMaNCC(n.getMaNCC())) {
                cout << "? Ma nha cung cap da ton tai. Bo qua them.\n";
            } else {
                dsNCC.push_back(n);
                appendToFile(fileNCC, n);
                cout << "* Da them NCC va luu vao file.\n";
            }
        } else if (ch==3) {
            string ma;
            cout << "Nhap ma nha cung cap can sua: ";
            getline(cin, ma);
            if (ma.empty()) {
                cout << "? Ma khong duoc de trong.\n";
                continue;
            }
            bool found = false;
            for (size_t i = 0; i < dsNCC.size(); ++i) {
                if (dsNCC[i].getMaNCC() == ma) {
                    dsNCC[i].suaThongTin();
                    capNhatFileNCC();
                    cout << "* Da sua nha cung cap va cap nhat file.\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "? Khong tim thay nha cung cap co ma " << ma << ".\n";
        } else if (ch==4) {
            string ma;
            cout << "Nhap ma nha cung cap can xoa: ";
            getline(cin, ma);
            if (ma.empty()) {
                cout << "? Ma khong duoc de trong.\n";
                continue;
            }
            bool found = false;
            for (size_t i = 0; i < dsNCC.size(); ++i) {
                if (dsNCC[i].getMaNCC() == ma) {
                    // Kiem tra xem co hang hoa nao lien quan k
                    bool hasHH = false;
                    for (size_t j = 0; j < dsHH.size(); ++j) {
                        if (dsHH[j].getMaNCC() == ma) {
                            hasHH = true;
                            break;
                        }
                    }
                    if (hasHH) {
                        cout << "? Khong the xoa nha cung cap vi co hang hoa lien quan.\n";
                    } else {
                        dsNCC.erase(dsNCC.begin() + i);
                        capNhatFileNCC();
                        cout << "* Da xoa nha cung cap va cap nhat file.\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "? Khong tim thay nha cung cap co ma " << ma << ".\n";
        } else if (ch==5) {
            timKiemTheoMaNCC(dsNCC);
        } else if (ch==6) {  
            chiTietNhaCungCap();
        } else if (ch==7) {  // THÊM CASE NÀY
            tinhTongGiaTriTheoNCC();
        } else {
            cout << "? Lua chon khong hop le.\n";
        }
    }
}

	//menu hang hoa
     void menuHangHoa() {
    while (true) {
        cout << "\n=====================================================\n";
        cout << "                 QUAN LY HANG HOA                    \n";
        cout << "=====================================================\n";
        cout << "  [1]  Hien danh sach hang hoa\n";
        cout << "  [2]  Them hang hoa\n";
        cout << "  [3]  Sua thong tin hang hoa\n";
        cout << "  [4]  Xoa hang hoa\n";
        cout << "  [5]  Tim kiem theo ma hang\n";	
        cout << "  [6]  Tim kiem theo ten hang\n";
        cout << "  [7]  Chi tiet hang hoa\n";
        cout << "  [8]  Cap nhat so luong hang hoa\n";
        cout << "  [9]  Hang hoa co so luong nhieu nhat\n";             
        cout << "  [10] Hang hoa co so luong it nhat\n";            
        cout << "  [0]  Quay lai menu truoc\n";
        cout << "-----------------------------------------------------\n";
        
        int ch = docSoNguyenKhongAm("Chon: ");
        if (ch==0) break;
        if (ch==1) {
            if (dsHH.empty()) cout << "? Chua co hang hoa nao.\n";
            else {
                HangHoa::tieuDe();
                for (size_t i = 0; i < dsHH.size(); ++i) dsHH[i].xuatThongTin();
            }
        } else if (ch==2) {
            HangHoa h;
            h.nhapThongTin();
            if (existsMaHH(h.getMaHH())) {
                cout << "? Ma hang hoa da ton tai. Bo qua them.\n";
            } else {
                if (!existsMaNCC(h.getMaNCC())) {
                    cout << "? Ma NCC chua ton tai. Them NCC truoc.\n";
                } else {
                    dsHH.push_back(h);
                    appendToFile(fileHH, h);
                    cout << "* Da them hang hoa va luu vao file.\n";
                }
            }
        } else if (ch==3) {
            string ma;
            cout << "Nhap ma hang hoa can sua: ";
            getline(cin, ma);
            if (ma.empty()) {
                cout << "? Ma khong duoc de trong.\n";
                continue;
            }
            bool found = false;
            for (size_t i = 0; i < dsHH.size(); ++i) {
                if (dsHH[i].getMaHH() == ma) {
                    dsHH[i].suaThongTin();
                    capNhatFileHH();
                    cout << "* Da sua hang hoa va cap nhat file.\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "? Khong tim thay hang hoa co ma " << ma << ".\n";
        } else if (ch==4) {
            string ma;
            cout << "Nhap ma hang hoa can xoa: ";
            getline(cin, ma);
            if (ma.empty()) {
                cout << "? Ma khong duoc de trong.\n";
                continue;
            }
            bool found = false;
            for (size_t i = 0; i < dsHH.size(); ++i) {
                if (dsHH[i].getMaHH() == ma) {
                    bool hasHD = false;
                    for (size_t j = 0; j < dsHD.size(); ++j) {
                        if (dsHD[j].getMaHH() == ma) {
                            hasHD = true;
                            break;
                        }
                    }
                    if (hasHD) {
                        cout << "? Khong the xoa hang hoa vi co hoa don lien quan.\n";
                    } else {
                        dsHH.erase(dsHH.begin() + i);
                        capNhatFileHH();
                        cout << "* Da xoa hang hoa va cap nhat file.\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "? Khong tim thay hang hoa co ma " << ma << ".\n";
        } else if (ch==5) {
            timKiemTheoMaHH(dsHH);
        } else if (ch==6) {
            timKiemTheoTenHH(dsHH);
        } else if (ch==7) {  
            chiTietHangHoa();
        } else if (ch==8) {
            capNhatSoLuongHangHoa();
        } else if (ch==9) {  
            hangHoaNhieuNhat();  
        } else if (ch==10) {  
            hangHoaBanChayNhat();
        } else {
            cout << "? Lua chon khong hop le.\n";
        }
    }
}

    //menu hoa don
	void menuHoaDon() {
    while (true) {
        cout << "\n=====================================================\n";
        cout << "                  QUAN LY HOA DON                    \n";
        cout << "=====================================================\n";
        cout << "  [1]  Hien danh sach hoa don\n";
        cout << "  [2]  Them hoa don\n";
        cout << "  [3]  Chi tiet hoa don\n";
        cout << "  [4]  Sua hoa don\n";
        cout << "  [5]  Thanh toan hoa don\n";
        cout << "  [6]  Xoa hoa don\n";
        cout << "  [0]  Quay lai menu truoc\n";
        cout << "-----------------------------------------------------\n";

        int ch = docSoNguyenKhongAm("Chon: ");
        if (ch==0) break;
        
        if (ch==1) {
            if (dsHD.empty()) {
                cout << "? Chua co hoa don nao.\n";
            } else {
                cout << "\n" << left << setw(15) << "Ma HD"
                     << setw(15) << "Ma KH"
                     << setw(20) << "Tong thanh toan"
                     << setw(15) << "Trang thai" << endl;
                cout << string(65, '-') << endl;
                for (size_t i = 0; i < dsHD.size(); ++i) {
                    cout << left << setw(15) << dsHD[i].getMaHD()
                         << setw(15) << dsHD[i].getMaKH()
                         << right << setw(15) << fixed << setprecision(0) << dsHD[i].tongThanhToan()
                         << "     " << (dsHD[i].isDaThanhToan() ? "Da TT" : "Chua TT") << endl;
                }
            }
        }else if (ch==2) {
    string maHD = docMaSo("Nhap ma hoa don: ");
    if (existsMaHD(maHD)) {
        cout << "? Ma hoa don da ton tai.\n";
        continue;
    }
    string maKH = docMaSo("Nhap ma khach hang: ");
    if (!existsMaKH(maKH)) {
        cout << "? Ma khach hang khong ton tai.\n";
        continue;
    }
    
    string ngayLap = docNgay("Nhap ngay lap hoa don");  
    
    HoaDon hd(maHD," ", maKH);
    hd.setNgayLap(ngayLap);  
    
    
            while (true) {
                cout << "\n--- Them mat hang vao hoa don ---\n";
                string maHH = docMaSo("Nhap ma hang hoa (hoac 'x' de ket thuc): ");
                if (maHH == "x" || maHH == "X") break;
                
                HangHoa* pHH = NULL;
                for (size_t i = 0; i < dsHH.size(); ++i) {
                    if (dsHH[i].getMaHH() == maHH) {
                        pHH = &dsHH[i];
                        break;
                    }
                }
                
                if (!pHH) {
                    cout << "? Ma hang hoa khong ton tai.\n";
                    continue;
                }
                
                cout << "Hang hoa: " << pHH->getTenHH() << ", Ton kho: " << pHH->getSoLuong() << endl;
                int sl = docSoNguyenKhongAm("Nhap so luong: ");
                
                if (sl > pHH->getSoLuong()) {
                    cout << "? So luong vuot qua ton kho.\n";
                    continue;
                }
                
                hd.themMatHang(*pHH, sl);
                cout << "* Da them mat hang vao hoa don.\n";
            }
            
            if (hd.getChiTiet().empty()) {
                cout << "? Hoa don khong co mat hang nao. Huy tao hoa don.\n";
            } else {
                hd.xuatHoaDon();
                cout << "\nLuu hoa don? (y/n): ";
                string ans; getline(cin, ans);
                if (!ans.empty() && (ans[0]=='y' || ans[0]=='Y')) {
                    dsHD.push_back(hd);
                    appendToFile(fileHD, hd);
                    cout << "* Da luu hoa don.\n";
                }
            }
        } else if (ch==3) {
            string ma = docMaSo("Nhap ma hoa don can xem: ");
            bool found = false;
            for (size_t i = 0; i < dsHD.size(); ++i) {
                if (dsHD[i].getMaHD() == ma) {
                    dsHD[i].xuatHoaDon();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "? Khong tim thay hoa don.\n";
        } else if (ch==4) {
            suaHoaDon();
        } else if (ch==5) {
            string ma = docMaSo("Nhap ma hoa don can thanh toan: ");
            bool found = false;
            for (size_t i = 0; i < dsHD.size(); ++i) {
                if (dsHD[i].getMaHD() == ma) {
                    if (dsHD[i].isDaThanhToan()) {
                        cout << "? Hoa don da duoc thanh toan.\n";
                    } else {
                        vector<ChiTietHoaDon>& ct = dsHD[i].getChiTiet();
                        for (size_t j = 0; j < ct.size(); ++j) {
                            for (size_t k = 0; k < dsHH.size(); ++k) {
                                if (dsHH[k].getMaHH() == ct[j].getMaHang()) {
                                    dsHH[k].giamSoLuongTon(ct[j].getSoLuong());
                                    break;
                                }
                            }
                        }
                        dsHD[i].thanhToan();
                        capNhatFileHD();
                        capNhatFileHH();
                        cout << "* Da thanh toan hoa don va cap nhat ton kho.\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "? Khong tim thay hoa don.\n";
            
            
        } else if (ch==6) {
            string ma = docMaSo("Nhap ma hoa don can xoa: ");
            bool found = false;
            for (size_t i = 0; i < dsHD.size(); ++i) {
                if (dsHD[i].getMaHD() == ma) {
                    if (dsHD[i].isDaThanhToan()) {
                        cout << "? Khong the xoa hoa don da thanh toan.\n";
                    } else {
                        dsHD.erase(dsHD.begin() + i);
                        capNhatFileHD();
                        cout << "* Da xoa hoa don.\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "? Khong tim thay hoa don.\n";
        } else {
            cout << "? Lua chon khong hop le.\n";
        }
    }
}
//menu thong ke
void menuThongKe() {
    while (true) {
        cout << "\n=====================================================\n";
        cout << "                    THONG KE                         \n";
        cout << "=====================================================\n";
        cout << "  [1]  Tong doanh thu\n";
        cout << "  [2]  Tong so nhan vien trong cua hang\n";       
        cout << "  [3]  Tong so nha cung cap cua cua hang\n";       
        cout << "  [4]  Tong so hang hoa trong cua hang\n";        
        cout << "  [5]  Hoa don/so khach hang trong ngay\n";                      
        cout << "  [0]  Quay lai menu truoc\n";
        cout << "-----------------------------------------------------\n";

        int ch = docSoNguyenKhongAm("Chon: ");
        if (ch==0) break;
        
        if (ch==1) {
            thongKeDoanhThu();
        } else if (ch==2) {                                         
            cout << "\n*** TONG SO NHAN VIEN: " << dsNV.size() << " ***\n";
        } else if (ch==3) {                                        
            cout << "\n*** TONG SO NHA CUNG CAP: " << dsNCC.size() << " ***\n";
        } else if (ch==4) {                                        
            cout << "\n*** TONG SO HANG HOA: " << dsHH.size() << " ***\n";
        } else if (ch==5) {                                        
            thongKeHoaDonTrongNgay();
        } else {
            cout << "? Lua chon khong hop le.\n";
        }
    }
}
	//thong ke doanh thu
    void thongKeDoanhThu() {
        cout << "\n=====================================================\n";
        cout << "                 THONG KE DOANH THU                  \n";
        cout << "=====================================================\n";
        
        string ngayCanTK = docNgay("Nhap ngay can thong ke");
        
        double doanhThuNgay = 0;
        double tongDoanhThu = 0;
        int soHDNgay = 0;
        int tongSoHD = 0;
        
        for (size_t i = 0; i < dsHD.size(); ++i) {
            if (dsHD[i].isDaThanhToan()) {
                tongDoanhThu += dsHD[i].tongThanhToan();
                tongSoHD++;
                
                if (dsHD[i].getNgayLap() == ngayCanTK) {
                    doanhThuNgay += dsHD[i].tongThanhToan();
                    soHDNgay++;
                }
            }
        }
        
        cout << "\n--- DOANH THU NGAY " << ngayCanTK << " ---\n";
        cout << "  So hoa don: " << soHDNgay << "\n";
        cout << "  Tong tien: " << fixed << setprecision(0) << doanhThuNgay << " VND\n";
        
        cout << "\n--- TONG DOANH THU (TAT CA) ---\n";
        cout << "  Tong so hoa don da thanh toan: " << tongSoHD << "\n";
        cout << "  Tong doanh thu: " << fixed << setprecision(0) << tongDoanhThu << " VND\n";
        cout << "=====================================================\n";
    }
//thong ke hoa don trong ngay
void thongKeHoaDonTrongNgay() {
    cout << "\n=====================================================\n";
    cout << "              HOA DON TRONG NGAY                     \n";
    cout << "=====================================================\n";
    
    string ngayCanXem = docNgay("Nhap ngay can xem hoa don");
    
    // Tim cac hoa don trong ngay
    vector<size_t> dsChiSo;  
    for (size_t i = 0; i < dsHD.size(); ++i) {
        if (dsHD[i].getNgayLap() == ngayCanXem) {
            dsChiSo.push_back(i);
        }
    }
    
    if (dsChiSo.empty()) {
        cout << "\n? Khong co hoa don nao trong ngay " << ngayCanXem << ".\n";
        return;
    }
    
   // hien thi danh sach hoa don
    cout << "\n--- CO " << dsChiSo.size() << " HOA DON/KHACH HANG TRONG NGAY " << ngayCanXem << " ---\n\n";
    cout << left << setw(15) << "Ma HD"
         << setw(15) << "Ma KH"
         << setw(20) << "Tong tien (VND)"
         << setw(15) << "Trang thai" << endl;
    cout << string(65, '-') << endl;
    
    double tongTien = 0;
    for (size_t i = 0; i < dsChiSo.size(); ++i) {
        const HoaDon& hd = dsHD[dsChiSo[i]];
        cout << left << setw(15) << hd.getMaHD()
             << setw(15) << hd.getMaKH()
             << right << setw(15) << fixed << setprecision(0) << hd.tongThanhToan()
             << "     " << (hd.isDaThanhToan() ? "Da TT" : "Chua TT") << endl;
        
        if (hd.isDaThanhToan()) {
            tongTien += hd.tongThanhToan();
        }
    }
    
    cout << string(65, '-') << endl;
    cout << "Tong doanh thu da thanh toan: " << fixed << setprecision(0) << tongTien << " VND\n";
    cout << "=====================================================\n";
}

    //menu chinh
	void menuChinh() {
    while (true) {
        cout << "\n=====================================================\n";
        cout << "                 HE THONG QUAN LY                    \n";
        cout << "=====================================================\n";
        cout << "  [1]  Quan ly Khach hang\n";
        cout << "  [2]  Quan ly Nhan vien\n";
        cout << "  [3]  Quan ly Nha cung cap\n";
        cout << "  [4]  Quan ly Hang hoa\n";
        cout << "  [5]  Quan ly Hoa don\n";
        cout << "  [6]  Thong ke\n";  
        cout << "  [0]  Thoat chuong trinh\n";
        cout << "-----------------------------------------------------\n";

        int ch = docSoNguyenKhongAm("Chon chuc nang: ");
        switch (ch) {
            case 1: menuKhachHang(); break;
            case 2: menuNhanVien(); break;
            case 3: menuNhaCungCap(); break;
            case 4: menuHangHoa(); break;
            case 5: menuHoaDon(); break;
            case 6: menuThongKe(); break;  
            case 0: {
                cout << "* Thoat. Cam on!\n";
                return;
            }
            default: cout << "? Lua chon khong hop le.\n";
        }
    }
}
};

// Them vao file
const string ADMIN_PASSWORD = "admin123"; // mat khau mac dinh

// ham kiem tra mk
bool kiemTraMatKhau() {
    const int MAX_ATTEMPTS = 3;
    int attempts = 0;
    
    cout << "\n=====================================================\n";
    cout << "            DANG NHAP HE THONG QUAN LY               \n";
    cout << "=====================================================\n";
    
    while (attempts < MAX_ATTEMPTS) {
        string password;
        cout << "\nNhap mat khau (Lan thu " << attempts + 1 << "/" << MAX_ATTEMPTS << "): ";
        
        
        char ch;
        password = "";
        while (true) {
            ch = getchar(); 
            if (ch == 13) { // Enter
                cout << endl;
                break;
            } else if (ch == 8) { 
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            } else {
                password += ch;
                cout << '*';
            }
        }
        
        if (password == ADMIN_PASSWORD) {
            cout << "\n* Dang nhap thanh cong!\n";
            return true;
        } else {
            attempts++;
            if (attempts < MAX_ATTEMPTS) {
                cout << "? Mat khau sai! Vui long thu lai.\n";
            }
        }
    }
    
    cout << "\n? Da nhap sai qua " << MAX_ATTEMPTS << " lan. Chuong trinh se thoat.\n";
    return false;
}

// neu mk khong dung, dung chuong trinh
bool kiemTraMatKhauDonGian() {
    const int MAX_ATTEMPTS = 3;
    int attempts = 0;
    
    cout << "\n=====================================================\n";
    cout << "            DANG NHAP HE THONG QUAN LY               \n";
    cout << "=====================================================\n";
   
    
    while (attempts < MAX_ATTEMPTS) {
        string password;
        cout << "\nNhap mat khau (Lan thu " << attempts + 1 << "/" << MAX_ATTEMPTS << "): ";
        getline(cin, password);
        
        if (password == ADMIN_PASSWORD) {
            cout << "\n* Dang nhap thanh cong!\n";
            return true;
        } else {
            attempts++;
            if (attempts < MAX_ATTEMPTS) {
                cout << "? Mat khau sai! Vui long thu lai.\n";
            }
        }
    }
    
    cout << "\n? Da nhap sai qua " << MAX_ATTEMPTS << " lan. Chuong trinh se thoat.\n";
    return false;
}

// int main
int main() {
    cout << ">> Ung dung Quan Ly - Khach Hang, Nhan Vien, Nha Cung Cap, Hang Hoa, Hoa Don\n";
    
    // kiem tra mk
    if (!kiemTraMatKhauDonGian()) {
        return 1; // Thoat chuong trinh neu sai mk
    }
    
    QuanLy ql;
    ql.menuChinh();
    return 0;
}











