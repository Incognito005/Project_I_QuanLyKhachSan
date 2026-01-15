#include<bits/stdc++.h>
using namespace std;

struct Date {
    int day = 1;
    int month = 1;
    int year = 2025;
};

struct Room {
    string id;
    string type;
    int capacity = 1;
    int pricePerNight = 0;
    string status = "San sang"; // Mặc định là phòng đang sẵn sàng (Đang sử dụng/ Sửa chữa)
};

struct Customer {
    string id;
    string name;
    string phone;
    string email;
    string idCard; // CMND/CCCD
};

struct Booking {
    string id;
    string customerID;
    string roomID;
    Date checkIn;
    Date checkOut;
    int guest = 1;
    int pricePerNight = 0;
    int serviceFee = 0;
    int totalCost = 0;
    string status = "Dang hoat dong"; // Đang hoạt động, Check Out và Đã hủy
};

// Xử lý ngày tháng
bool isLeap(int year){
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

long long dateToDays(int day, int month, int year){
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    long long days = 0;

    for(int y = 1; y < year; y++){
        days += isLeap(y) ? 366 : 365;
    }

    for(int m = 1; m < month; m++){
        days += monthDays[m - 1];
        if (m == 2 && isLeap(year)) days++;
    }

    days += day;
    const long long eOffset = 719162;
    return days - eOffset;
}

Date daysToDate(long long totalDays){
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const long long eOffset = 719162;
    totalDays += eOffset;

    Date result;
    result.year = 1;

    while(true){
        int daysInYear = isLeap(result.year) ? 366 : 365;
        if (totalDays <= daysInYear) break;
        totalDays -= daysInYear;
        result.year++;
    }
    result.month = 1;
    for(int m = 0; m < 12; m++){
        int days = monthDays[m];
        if(m == 1 && isLeap(result.year)) days = 29;
        if(totalDays <= days){
            result.month = m + 1;
            result.day = (int)totalDays;
            break;
        }
        totalDays -= days;
    }
    return result;
}

bool isValidDate(Date& date){
    if (date.year < 1900 || date.year > 2100) return false;
    if (date.month < 1 || date.month > 12) return false;
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = monthDays[date.month - 1];
    if(date.month == 2 && isLeap(date.year)) maxDay = 29;
    return date.day >= 1 && date.day <= maxDay;
}

int compareDate(const Date& lhs, const Date& rhs) {
    long long a = dateToDays(lhs.day, lhs.month, lhs.year);
    long long b = dateToDays(rhs.day, rhs.month, rhs.year);
    if(a < b) return -1;
    if(a > b) return 1;
    return 0;
}

int daysBetween(Date& start, Date& end){
    long long a = dateToDays(start.day, start.month, start.year);
    long long b = dateToDays(end.day, end.month, end.year);
    return (int)(b - a);
}

Date addDays(Date& date, int offset){
    long long days = dateToDays(date.day, date.month, date.year);
    return daysToDate(days + offset);
}

string dateToString(Date& date){
    stringstream ss;
    ss << setfill('0') << setw(2) << date.day << "/"
       << setw(2) << date.month << "/"
       << setw(4) << date.year;
    return ss.str();
}

bool isValidPhone(const string& phone){
    if(phone.length() < 10 || phone.length() > 11) return false;
    for(char c : phone){
        if(!isdigit(c)) return false;
    }
    return phone[0] == '0';
}

bool isValidEmail(const string& email){
    return email.find('@') != string::npos && email.find('.') != string::npos;
}

// Nhập xuất dữ liệu
string readLine(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin >> ws, value);
    return value;
}

int readInt(const string& prompt, int minValue, int maxValue){
    while(true){
        cout << prompt;
        int value;
        if(cin >> value){
            if(value >= minValue && value <= maxValue){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
        cout << "Gia tri khong hop le, vui long nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

Date inputDate(const string& label){
    while(true){
        cout << label << " (dd/mm/yyyy): ";
        Date date;
        if(cin >> date.day >> date.month >> date.year){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(isValidDate(date)){
                return date;
            }
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Ngay thang khong hop le, vui long thu lai.\n";
    }
}

vector<Room> rooms;
vector<Customer> customers;
vector<Booking> bookings;

// Thuật toán sắp xếp + tìm kiếm
void sortRoomsById(){
    sort(rooms.begin(), rooms.end(), [](const Room& a, const Room& b){
         return a.id < b.id;
    });
}

void sortBookingsById() {
    sort(bookings.begin(), bookings.end(), [](const Booking& a, const Booking& b){
            return a.id < b.id;
    });
}

// Tìm kiếm nhị phân trên danh sách phòng theo mã
Room* binarySearchRoomById(const string& roomId){
    if(rooms.empty()) return nullptr;
    sortRoomsById();
    auto it = lower_bound(rooms.begin(), rooms.end(), roomId, [](const Room& room, const string& value){
            return room.id < value;
    });
    if(it != rooms.end() && it->id == roomId) return &(*it);
    return nullptr;
}

// Tìm kiếm nhị phân trên danh sách booking theo mã
Booking* binarySearchBookingById(const string& bookingId){
    if(bookings.empty()) return nullptr;
    sortBookingsById();
    auto it = lower_bound(bookings.begin(), bookings.end(), bookingId, [](const Booking& b, const string& value){
            return b.id < value;
    });
    if(it != bookings.end() && it->id == bookingId) return &(*it);
    return nullptr;
}

// Tìm kiếm
Room* findRoom(const string& roomId){
    for(auto& room : rooms){
        if(room.id == roomId) return &room;
    }
    return nullptr;
}

Customer* findCustomer(const string& customerId){
    for(auto& customer : customers){
        if(customer.id == customerId){
            return &customer;
        }
    }
    return nullptr;
}

Booking* findBooking(const string& bookingId){
    for(auto& booking : bookings){
        if(booking.id == bookingId){
            return &booking;
        }
    }
    return nullptr;
}

bool isRoomAvailable(const string& roomId, Date& checkIn, Date& checkOut){
    for(auto& b : bookings){
        if(b.roomID == roomId && b.status == "Dang hoat dong"){
            bool overlap = !(compareDate(checkOut, b.checkIn) <= 0 ||
                            compareDate(b.checkOut, checkIn) <= 0);
            if(overlap) return false;
        }
    }
    return true;
}

// Quản lý phòng
void addRoom(){
    Room room;
    room.id = readLine("Nhap ma phong: ");
    if(findRoom(room.id) != nullptr){
        cout << "Ma phong da ton tai!\n";
        return;
    }
    room.type = readLine("Nhap loai phong (Standard/Deluxe/Royal Suite): ");
    room.capacity = readInt("Nhap suc chua: ", 1, 10);
    room.pricePerNight = readInt("Nhap gia phong/dem (VND): ", 0, 100000000);
    room.status = "San sang";
    rooms.push_back(room);
    sortRoomsById();
    cout << "Them phong thanh cong!\n";
}

void updateRoom(){
    string roomId = readLine("Nhap ma phong can sua: ");
    Room* room = findRoom(roomId);
    if(room == nullptr){
        cout << "Khong tim thay phong!\n";
        return;
    }
    cout << "\n=== Thong tin hien tai ===\n";
    cout << "Loai phong: " << room->type << "\n";
    cout << "Suc chua: " << room->capacity << "\n";
    cout << "Gia/dem: " << room->pricePerNight << " VND\n";
    cout << "Trang thai: " << room->status << "\n";
    cout << "\n=== Nhap thong tin moi (Enter de giu nguyen) ===\n";
    string newType = readLine("Loai phong moi: ");
    if(!newType.empty()){
            room->type = newType;
    }
    int newCapacity = readInt("Suc chua moi (0 de giu nguyen): ", 0, 10);
    if(newCapacity > 0) room->capacity = newCapacity;

    int newPrice = readInt("Gia phong moi (0 de giu nguyen): ", 0, 100000000);
    if(newPrice > 0) room->pricePerNight = newPrice;
}

void deleteRoom() {
    string roomId = readLine("Nhap ma phong can xoa: ");
    // Kiểm tra phòng có booking không
    for(auto& booking : bookings){
        if (booking.roomID == roomId && booking.status == "Dang hoat dong") {
            cout << "Khong the xoa phong dang co booking!\n";
            return;
        }
    }
    auto it = remove_if(rooms.begin(), rooms.end(), [&roomId](const Room& r){
        return r.id == roomId;
    });
    if(it != rooms.end()){
        rooms.erase(it, rooms.end());
        cout << "Xoa phong thanh cong!\n";
    }
    else {
        cout << "Khong tim thay phong!\n";
    }
}

void searchRoom(){

    cout << "\n=============================== Tim kiem phong ===============================\n";
    cout << "1. Tim theo ma phong\n";
    cout << "2. Tim theo loai phong\n";
    cout << "3. Tim theo khoang gia\n";
    cout << "4. Xem phong trong\n";

    int option = readInt("Chon: ", 1, 4);
    if(option == 1){
        string roomId = readLine("Nhap ma phong: ");
        Room* room = binarySearchRoomById(roomId);
        if(room){
            cout << "\nMa: " << room->id << " | Loai: " << room->type
                 << " | Suc chua: " << room->capacity
                 << " | Gia: " << room->pricePerNight
                 << " | Trang thai: " << room->status << "\n";
        }
        else {
            cout << "Khong tim thay!\n";
        }
    }
    else if(option == 2){
        string type = readLine("Nhap loai phong: ");
        bool found = false;
        for(auto& room : rooms){
            if(room.type == type){
                cout << "Ma: " << room.id << " | Gia: " << room.pricePerNight
                     << " | Trang thai: " << room.status << "\n";
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay!\n";
    }
    else if(option == 3){
        int minPrice = readInt("Gia toi thieu: ", 0, 100000000);
        int maxPrice = readInt("Gia toi da: ", 0, 100000000);
        bool found = false;
        for(auto& room : rooms){
            if (room.pricePerNight >= minPrice && room.pricePerNight <= maxPrice){
                cout << "Ma: " << room.id << " | Loai: " << room.type
                     << " | Gia: " << room.pricePerNight << "\n";
                found = true;
            }
        }
        if(!found) cout << "Khong tim thay!\n";
    }
    else if(option == 4){
        bool found = false;
        for(const auto& room : rooms){
            if(room.status == "San sang"){
                cout << "Ma: " << room.id << " | Loai: " << room.type
                     << " | Gia: " << room.pricePerNight << "\n";
                found = true;
            }
        }
        if(!found){
            cout << "Khong co phong trong!\n";
        }
    }
}

void listRooms(){
    if(rooms.empty()){
        cout << "Khong co phong nao.\n";
        return;
    }
    cout << "\n" << string(80, '=') << "\n";
    cout << "================================ DANH SACH PHONG ===============================\n";
    cout << string(80, '=') << "\n";
    cout << left << setw(10) << "Ma phong"
         << setw(15) << "Loai phong"
         << setw(10) << "Suc chua"
         << setw(15) << "Gia/dem"
         << setw(15) << "Trang thai" << "\n";
    cout << string(80, '-') << "\n";

    for(auto& room : rooms){
        cout << left << setw(10) << room.id
             << setw(15) << room.type
             << setw(10) << room.capacity
             << setw(15) << room.pricePerNight
             << setw(15) << room.status << "\n";
    }
    cout << string(80, '=') << "\n";
}

// Quản lý khách hàng
void addCustomer(){
    Customer customer;
    customer.id = readLine("Nhap ma khach hang: ");
    if(findCustomer(customer.id) != nullptr){
        cout << "Ma khach hang da ton tai!\n";
        return;
    }
    customer.name = readLine("Nhap ten khach hang: ");

    // Validate sdt
    while(true){
        customer.phone = readLine("Nhap so dien thoai: ");
        if(isValidPhone(customer.phone)) break;
        cout << "So dien thoai khong hop le! (10-11 so, bat dau bang 0)\n";
    }

    // Validate email
    while(true){
        customer.email = readLine("Nhap email: ");
        if(customer.email.empty() || isValidEmail(customer.email)) break;
        cout << "Email khong hop le!\n";
    }

    customer.idCard = readLine("Nhap CMND/CCCD: ");
    customers.push_back(customer);
    cout << "Them khach hang thanh cong!\n";
}

void updateCustomer(){
    string customerId = readLine("Nhap ma khach hang can sua: ");
    Customer* customer = findCustomer(customerId);
    if(customer == nullptr){
        cout << "Khong tim thay khach hang!\n";
        return;
    }
    cout << "\n=== Thong tin hien tai ===\n";
    cout << "Ten: " << customer->name << "\n";
    cout << "SDT: " << customer->phone << "\n";
    cout << "Email: " << customer->email << "\n";
    cout << "CMND: " << customer->idCard << "\n";

    cout << "\n=== Nhap thong tin moi ===\n";
    string newName = readLine("Ten moi (Enter de giu nguyen): ");
    if(!newName.empty()){
        customer->name = newName;
    }
    string newPhone = readLine("SDT moi (Enter de giu nguyen): ");
    if(!newPhone.empty()){
        customer->phone = newPhone;
    }
    string newEmail = readLine("Email moi (Enter de giu nguyen): ");
    if(!newEmail.empty()){
        customer->email = newEmail;
    }
    cout << "Cap nhat khach hang thanh cong!\n";
}

void deleteCustomer(){
    string customerId = readLine("Nhap ma khach hang can xoa: ");
    // Kiểm tra khách có booking không
    for(const auto& booking : bookings){
        if(booking.customerID == customerId && booking.status == "Dang hoat dong"){
            cout << "Khong the xoa khach hang dang co booking!\n";
            return;
        }
    }

    auto it = remove_if(customers.begin(), customers.end(), [&customerId](const Customer& c){
        return c.id == customerId;
    });
    if(it != customers.end()){
        customers.erase(it, customers.end());
        cout << "Xoa khach hang thanh cong!\n";
    }
    else {
        cout << "Khong tim thay khach hang!\n";
    }
}

void searchCustomer(){
    cout << "\n" << string(80, '=') << "\n";
    cout << "============================== TIM KIEM KHACH HANG =============================\n";
    cout << "1. Tim theo ma\n";
    cout << "2. Tim theo ten\n";
    cout << "3. Tim theo SDT\n";
    cout << string(80, '=') << "\n";

    int option = readInt("Chon: ", 1, 3);
    if(option == 1){
        string id = readLine("Nhap ma khach hang: ");
        Customer* c = findCustomer(id);
        if(c){
            cout << "\nMa: " << c->id << " | Ten: " << c->name
                 << " | SDT: " << c->phone << " | Email: " << c->email << "\n";
        }
        else {
            cout << "Khong tim thay!\n";
        }
    }
    else if(option == 2){
        string name = readLine("Nhap ten (hoac mot phan): ");
        bool found = false;
        for(auto& c : customers){
            if(c.name.find(name) != string::npos){
                cout << "Ma: " << c.id << " | Ten: " << c.name
                     << " | SDT: " << c.phone << "\n";
                found = true;
            }
        }
        if(!found){
            cout << "Khong tim thay!\n";
        }
    }
    else if(option == 3){
        string phone = readLine("Nhap SDT: ");
        bool found = false;
        for(const auto& c : customers){
            if(c.phone.find(phone) != string::npos){
                cout << "Ma: " << c.id << " | Ten: " << c.name
                     << " | SDT: " << c.phone << "\n";
                found = true;
            }
        }
        if(!found){
            cout << "Khong tim thay!\n";
        }
    }
}

void listCustomers(){
    if(customers.empty()){
        cout << "Khong co khach hang nao.\n";
        return;
    }

    cout << "\n" << string(80, '=') << "\n";
    cout << "Danh sach khach hang\n";
    cout << string(80, '=') << "\n";
    cout << left << setw(10) << "Ma KH"
         << setw(20) << "Ten KH"
         << setw(15) << "SDT"
         << setw(25) << "Email" << "\n";
    cout << string(80, '-') << "\n";

    for(auto& customer : customers){
        cout << left << setw(10) << customer.id
             << setw(20) << customer.name
             << setw(15) << customer.phone
             << setw(25) << customer.email << "\n";
    }
    cout << string(80, '=') << "\n";
}

// Quản lý booking
void addBooking(){
    Booking booking;
    booking.id = readLine("Nhap ma dat phong: ");
    if(findBooking(booking.id) != nullptr){
        cout << "Ma dat phong da ton tai!\n";
        return;
    }
    booking.customerID = readLine("Nhap ma khach hang: ");
    if(findCustomer(booking.customerID) == nullptr){
        cout << "Khach hang khong ton tai!\n";
        return;
    }

    booking.roomID = readLine("Nhap ma phong: ");
    Room* room = findRoom(booking.roomID);
    if(room == nullptr){
        cout << "Phong khong ton tai!\n";
        return;
    }

    if(room->status != "San sang"){
        cout << "Phong khong san sang!\n";
        return;
    }

    booking.checkIn = inputDate("Ngay check-in");
    booking.checkOut = inputDate("Ngay check-out");
    if(compareDate(booking.checkIn, booking.checkOut) >= 0){
        cout << "Ngay check-out phai sau ngay check-in!\n";
        return;
    }

    if(!isRoomAvailable(booking.roomID, booking.checkIn, booking.checkOut)){
        cout << "Phong da duoc dat trong khoang thoi gian nay!\n";
        return;
    }

    booking.guest = readInt("So luong khach: ", 1, room->capacity);
    booking.pricePerNight = room->pricePerNight;
    booking.serviceFee = readInt("Phi dich vu/dem (VND): ", 0, 1000000);

    int nights = daysBetween(booking.checkIn, booking.checkOut);
    booking.totalCost = nights * (booking.pricePerNight + booking.serviceFee);
    booking.status = "Dang hoat dong";

    // Cập nhật trạng thái phòng
    room->status = "Dang su dung";

    bookings.push_back(booking);
    sortBookingsById();
    cout << "\n=== DAT PHONG THANH CONG ===\n";
    cout << "So dem: " << nights << "\n";
    cout << "Tong chi phi: " << booking.totalCost << " VND\n";
}

void checkOut() {
    string bookingId = readLine("Nhap ma dat phong can check-out: ");
    Booking* booking = findBooking(bookingId);

    if(booking == nullptr){
        cout << "Khong tim thay booking!\n";
        return;
    }
    if(booking->status != "Dang hoat dong"){
        cout << "Booking khong con hoat dong!\n";
        return;
    }
    cout << "\n=== Thong tin booking ===\n";
    cout << "Ma KH: " << booking->customerID << "\n";
    cout << "Ma phong: " << booking->roomID << "\n";
    cout << "Check-in: " << dateToString(booking->checkIn) << "\n";
    cout << "Check-out: " << dateToString(booking->checkOut) << "\n";
    cout << "Tong chi phi: " << booking->totalCost << " VND\n";

    string confirm = readLine("\nXac nhan check-out? (y/n): ");
    if(confirm == "y" || confirm == "Y"){
        booking->status = "Check Out";

        // Cập nhật trạng thái phòng
        Room* room = findRoom(booking->roomID);
        if(room){
            room->status = "San sang";
        }
        cout << "Check-out thanh cong!\n";
    }
}

void cancelBooking(){
    string bookingId = readLine("Nhap ma dat phong can huy: ");
    Booking* booking = findBooking(bookingId);

    if(booking == nullptr){
        cout << "Khong tim thay booking!\n";
        return;
    }
    if(booking->status != "Dang hoat dong"){
        cout << "Booking khong con hoat dong!\n";
        return;
    }
    string confirm = readLine("Xac nhan huy booking? (Y/N): ");
    if(confirm == "y" || confirm == "Y") {
        booking->status = "Da huy";
        // Cập nhật trạng thái phòng
        Room* room = findRoom(booking->roomID);
        if(room){
            room->status = "San sang";
        }
        cout << "Huy booking thanh cong!\n";
    }
}

void searchBooking(){
    cout << "\n" << string(80, '=');
    cout << "\n=============================== Tim kiem booking ===============================\n";
    cout << "1. Tim theo ma booking\n";
    cout << "2. Tim theo ma khach hang\n";
    cout << "3. Tim theo ma phong\n";
    cout << "4. Xem booking theo trang thai\n";
    cout << string(80, '=') << "\n";

    int option = readInt("Chon: ", 1, 4);
    if(option == 1){
        string id = readLine("Nhap ma booking: ");
        Booking* b = binarySearchBookingById(id);
        if(b){
            cout << "\nMa: " << b->id << " | KH: " << b->customerID
                 << " | Phong: " << b->roomID
                 << " | Tong: " << b->totalCost << " VND"
                 << " | Trang thai: " << b->status << "\n";
        }
        else {
            cout << "Khong tim thay!\n";
        }
    }
    else if(option == 2){
        string customerId = readLine("Nhap ma khach hang: ");
        bool found = false;
        for(auto& b : bookings){
            if(b.customerID == customerId){
                cout << "Ma: " << b.id << " | Phong: " << b.roomID
                     << " | Check-in: " << dateToString(b.checkIn)
                     << " | Status: " << b.status << "\n";
                found = true;
            }
        }
        if(!found){
            cout << "Khong tim thay!\n";
        }
    }
    else if(option == 3){
        string roomId = readLine("Nhap ma phong: ");
        bool found = false;
        for(auto& b : bookings){
            if(b.roomID == roomId){
                cout << "Ma: " << b.id << " | KH: " << b.customerID
                     << " | Check-in: " << dateToString(b.checkIn)
                     << " | Status: " << b.status << "\n";
                found = true;
            }
        }
        if(!found){
            cout << "Khong tim thay!\n";
        }
    }
    else if(option == 4){
        string status = readLine("Nhap trang thai (Dang hoat dong/Check Out/Da huy): ");
        bool found = false;
        for(auto& b : bookings){
            if(b.status == status){
                cout << "Ma: " << b.id << " | KH: " << b.customerID
                     << " | Phong: " << b.roomID
                     << " | Tong: " << b.totalCost << " VND\n";
                found = true;
            }
        }
        if(!found){
            cout << "Khong tim thay!\n";
        }
    }
}

void listBookings(){
    if(bookings.empty()){
        cout << "Khong co booking nao.\n";
        return;
    }
    cout << "\n" << string(100, '=') << "\n";
    cout << "DANH SACH DAT PHONG\n";
    cout << string(100, '=') << "\n";
    for(auto& booking : bookings){
        cout << "Ma booking: " << booking.id << " | Trang thai: " << booking.status << "\n";
        cout << "  Khach hang: " << booking.customerID << " | Phong: " << booking.roomID << "\n";
        cout << "  Check-in: " << dateToString(booking.checkIn)
             << " | Check-out: " << dateToString(booking.checkOut) << "\n";
        cout << "  So khach: " << booking.guest << " | Tong chi phi: " << booking.totalCost << " VND\n";
        cout << string(100, '-') << "\n";
    }
    cout << string(100, '=') << "\n";
}

void reportRevenue(){
    cout << "\n=== Thong ke doanh thu ===\n";
    int totalRevenue = 0;
    int activeBookings = 0;
    int completedBookings = 0;
    int cancelledBookings = 0;
    for(const auto& booking : bookings){
        if(booking.status == "Dang hoat dong") activeBookings++;
        else if(booking.status == "Check Out"){
            completedBookings++;
            totalRevenue += booking.totalCost;
        }
        else if (booking.status == "Da huy") cancelledBookings++;
    }

    cout << "Tong doanh thu: " << totalRevenue << " VND\n";
    cout << "Booking dang hoat dong: " << activeBookings << "\n";
    cout << "Booking da hoan thanh: " << completedBookings << "\n";
    cout << "Booking da huy: " << cancelledBookings << "\n";
}

void reportRoomStatus() {
    cout << "\n=== Thong ke trang thai phong ===\n";

    int cnt1 = 0, cnt2 = 0, cnt3 = 0;

    for (const auto& room : rooms) {
        if (room.status == "San sang") cnt1++;
        else if (room.status == "Dang su dung") cnt2++;
        else if (room.status == "Sua chua") cnt3++;
    }

    cout << "Tong so phong: " << rooms.size() << "\n";
    cout << "Phong trong: " << cnt1 << "\n";
    cout << "Phong da dat: " << cnt2 << "\n";
    cout << "Phong bao tri: " << cnt3 << "\n";
    cout << "Ti le su dung: " << fixed << setprecision(1)
         << (rooms.empty() ? 0.0 : (cnt2 * 100.0 / rooms.size())) << "%\n";
}

void reportCustomerHistory() {
    string customerId = readLine("Nhap ma khach hang: ");
    Customer* customer = findCustomer(customerId);

    if (customer == nullptr) {
        cout << "Khong tim thay khach hang!\n";
        return;
    }
    cout << "\n=== Lich su dat phong cua " << customer->name << " ===\n";
    int totalBookings = 0;
    int totalSpent = 0;
    for (auto& booking : bookings) {
        if (booking.customerID == customerId) {
            totalBookings++;
            if (booking.status == "Check Out") {
                totalSpent += booking.totalCost;
            }

            cout << "\nBooking: " << booking.id << " (" << booking.status << ")\n";
            cout << "  Phong: " << booking.roomID << "\n";
            cout << "  Check-in: " << dateToString(booking.checkIn)
                 << " -> Check-out: " << dateToString(booking.checkOut) << "\n";
            cout << "  Chi phi: " << booking.totalCost << " VND\n";
        }
    }

    cout << "\nTong so booking: " << totalBookings << "\n";
    cout << "Tong chi tieu: " << totalSpent << " VND\n";
}

// Quy hoach dong: Tối ưu doanh thu từ các booking không trùng lịch
// Cho danh sách booking, tìm cách chọn các booking không trùng lịch để tối đa hóa doanh thu
void optimizeRevenue() {
    cout << "\n=== Toi uu doanh thu ===\n";
    cout << "Tim cach chon cac booking khong trung lich de toi da doanh thu\n";

    // Lọc các booking có thể chọn (đang hoạt động hoặc đã check-out)
    vector<Booking> candidateBookings;
    for(auto& b : bookings){
        if(b.status == "Dang hoat dong" || b.status == "Check Out"){
            candidateBookings.push_back(b);
        }
    }

    if(candidateBookings.empty()){
        cout << "Khong co booking nao de toi uu!\n";
        return;
    }

    // Sắp xếp booking theo ngày check-out (kết thúc)
    sort(candidateBookings.begin(), candidateBookings.end(), [](const Booking& a, const Booking& b){
        return compareDate(a.checkOut, b.checkOut) < 0;
    });

    int n = candidateBookings.size();
    vector<int> dp(n, 0);  // dp[i] = doanh thu tối đa khi xét đến booking thứ i

    // Tìm booking gần nhất không trùng lịch với booking tại vị trí i
    auto findLastNonOverlap = [&](int i) -> int{
        for(int j = i - 1; j >= 0; j--){
            bool conflict = false;
            // Kiểm tra conflict (chỉ xảy ra khi cùng phòng VÀ thời gian overlap)
            if(candidateBookings[j].roomID == candidateBookings[i].roomID){
                bool overlap = !(compareDate(candidateBookings[i].checkOut, candidateBookings[j].checkIn) <= 0 ||
                                compareDate(candidateBookings[j].checkOut, candidateBookings[i].checkIn) <= 0);
                conflict = overlap;
            }
            // Khác phòng thì không conflict
            
            if(!conflict) return j;
        }
        return -1;
    };

    // DP: dp[i] = max(không chọn booking i, chọn booking i + dp[lastNonOverlap])
    dp[0] = candidateBookings[0].totalCost;
    for(int i = 1; i < n; i++){
        // Không chọn booking i
        int notTake = dp[i - 1];

        // Chọn booking i
        int lastNonOverlap = findLastNonOverlap(i);
        int take = candidateBookings[i].totalCost;
        if(lastNonOverlap >= 0){
            take += dp[lastNonOverlap];
        }
        dp[i] = max(notTake, take);
    }

    cout << "Doanh thu toi da co the dat duoc: " << dp[n - 1] << " VND\n";
    cout << "Tong doanh thu hien tai (tat ca booking): ";
    int totalCurrent = 0;
    for(auto& b : candidateBookings){
        totalCurrent += b.totalCost;
    }
    cout << totalCurrent << " VND\n";
    cout << "Ti le toi uu: " << fixed << setprecision(1)
         << (totalCurrent > 0 ? (dp[n - 1] * 100.0 / totalCurrent) : 0) << "%\n";
}

// Data mẫu
void seedDemoData() {
    rooms.clear();
    customers.clear();
    bookings.clear();
    // Phòng mẫu
    rooms.push_back({"R101", "Standard", 2, 500000, "San sang"});
    rooms.push_back({"R102", "Standard", 2, 500000, "San sang"});
    rooms.push_back({"R201", "Deluxe", 3, 800000, "San sang"});
    rooms.push_back({"R202", "Deluxe", 3, 800000, "San sang"});
    rooms.push_back({"R301", "Royal Suite", 4, 1500000, "San sang"});

    // Khách hàng mẫu
    customers.push_back({"C001", "Nguyen Nguyen Trung", "0912345678", "nnt@gmail.com", "001234567890"});
    customers.push_back({"C002", "Tran Van A", "0987654321", "tva@gmail.com", "009876543210"});
    customers.push_back({"C003", "Ho Huu C", "0901234567", "hhc@gmail.com", "001122334455"});

    // Booking mẫu
    Booking b1;
    b1.id = "B001";
    b1.customerID = "C001";
    b1.roomID = "R101";
    b1.checkIn = {25, 12, 2025};
    b1.checkOut = {27, 12, 2025};
    b1.guest = 2;
    b1.pricePerNight = 500000;
    b1.serviceFee = 50000;
    b1.totalCost = 2 * (500000 + 50000); // Từ 25/12 đến 27/12 = 2 đêm
    b1.status = "Dang hoat dong";
    bookings.push_back(b1);

    // Cập nhật trạng thái phòng
    findRoom("R101")->status = "Dang su dung";

    // Sắp xếp dữ liệu để hỗ trợ tìm kiếm nhị phân
    sortRoomsById();
    sortBookingsById();
}

// Menu hệ thống các chức năng
void roomMenu(){
    while(true){
        cout << "\n" << string(80, '=') << "\n";
        cout << "               Quan ly phong\n";
        cout << "1. Them phong\n";
        cout << "2. Cap nhat phong\n";
        cout << "3. Xoa phong\n";
        cout << "4. Tim kiem phong\n";
        cout << "5. Xem danh sach phong\n";
        cout << "0. Quay lai\n";
        cout << string(80, '=') << "\n";

        int option = readInt("Chon chuc nang: ", 0, 5);
        if(option == 0) break;
        else if(option == 1) addRoom();
        else if(option == 2) updateRoom();
        else if(option == 3) deleteRoom();
        else if(option == 4) searchRoom();
        else if(option == 5) listRooms();
    }
}

void customerMenu(){
    while(true){
        cout << "\n" << string(80, '=') << "\n";
        cout << "============================== Quan ly khach hang ==============================\n";
        cout << "1. Them khach hang\n";
        cout << "2. Cap nhat khach hang\n";
        cout << "3. Xoa khach hang\n";
        cout << "4. Tim kiem khach hang\n";
        cout << "5. Xem danh sach khach hang\n";
        cout << "0. Quay lai\n";
        cout << string(80, '=') << "\n";

        int option = readInt("Chon chuc nang: ", 0, 5);

        if (option == 0) break;
        else if(option == 1) addCustomer();
        else if(option == 2) updateCustomer();
        else if(option == 3) deleteCustomer();
        else if(option == 4) searchCustomer();
        else if(option == 5) listCustomers();
    }
}

void bookingMenu(){
    while(true){
        cout << "\n" << string(80, '=') << "\n";
        cout << "============================== QUAN LY DAT PHONG ===============================\n";
        cout << "1. Dat phong\n";
        cout << "2. Check-out\n";
        cout << "3. Huy booking\n";
        cout << "4. Tim kiem booking\n";
        cout << "5. Xem danh sach booking\n";
        cout << "0. Quay lai\n";
        cout << string(80, '=') << "\n";
        int option = readInt("Chon chuc nang: ", 0, 5);

        if(option == 0) break;
        else if(option == 1) addBooking();
        else if(option == 2) checkOut();
        else if(option == 3) cancelBooking();
        else if(option == 4) searchBooking();
        else if(option == 5) listBookings();
    }
}

void reportMenu(){
    while(true){
        cout << "\n" << string(80, '=') << "\n";
        cout << "=============================== Bao cao thong ke ===============================\n";
        cout << "1. Thong ke doanh thu\n";
        cout << "2. Thong ke trang thai phong\n";
        cout << "3. Lich su khach hang\n";
        cout << "4. Toi uu doanh thu (Quy hoach dong)\n";
        cout << "0. Quay lai\n";
        cout << string(80, '=') << "\n";

        int option = readInt("Chon chuc nang: ", 0, 4);

        if(option == 0) break;
        else if(option == 1) reportRevenue();
        else if(option == 2) reportRoomStatus();
        else if(option == 3) reportCustomerHistory();
        else if(option == 4) optimizeRevenue();
    }
}

void showMainMenu(){
    cout << string(80, '=') << "\n";
    cout << "========================== He thong quan ly khach san ==========================\n";
    cout << "1. Quan ly phong\n";
    cout << "2. Quan ly khach hang\n";
    cout << "3. Quan ly dat phong\n";
    cout << "4. Bao cao & Thong ke\n";
    cout << "0. Thoat\n";
    cout << string(80, '=') << "\n";
}

void runApp(){
    seedDemoData();
    while(true){
        showMainMenu();
        int option = readInt("Chon chuc nang: ", 0, 4);
        if(option == 0){
            cout << "\n  Cam on ban da su dung!\n";
            cout << "  Hen gap lai!\n";
            break;
        }
        else if(option == 1) roomMenu();
        else if(option == 2) customerMenu();
        else if(option == 3) bookingMenu();
        else if(option == 4) reportMenu();
    }
}


int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
    runApp();
    return 0;
}
