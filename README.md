# 🏨 Hệ thống Quản lý Khách sạn

## 📋 Mô tả
Dự án này là một hệ thống quản lý khách sạn hoàn chỉnh được xây dựng bằng **C++**, sử dụng giao diện **Command Line Interface (CLI)**. Hệ thống hỗ trợ quản lý toàn diện các hoạt động của khách sạn bao gồm: quản lý phòng, quản lý khách hàng, đặt phòng và báo cáo thống kê. Dự án áp dụng các thuật toán cơ bản và nâng cao như **Tìm kiếm**, **Sắp xếp** và **Quy hoạch động** để tối ưu hóa hiệu suất và giải quyết các bài toán nghiệp vụ phức tạp.

## 🎯 Mục tiêu
- Quản lý thông tin phòng: Thêm, sửa, xóa, tìm kiếm và hiển thị danh sách phòng.
- Quản lý thông tin khách hàng: Lưu trữ và quản lý thông tin khách hàng với validation đầy đủ.
- Quản lý đặt phòng: Xử lý quy trình đặt phòng, check-out và hủy booking với kiểm tra trùng lịch.
- Báo cáo và thống kê: Thống kê doanh thu, trạng thái phòng và lịch sử khách hàng.
- Tối ưu hóa nghiệp vụ: Sử dụng thuật toán Quy hoạch động để tối ưu doanh thu từ các booking.

---

## 📊 Cấu trúc Dữ liệu

### 🔹 Cấu trúc Room (Phòng)
```cpp
struct Room {
    string id;              // Mã phòng (VD: R101, R201)
    string type;             // Loại phòng (Standard/Deluxe/Royal Suite)
    int capacity;            // Sức chứa (số khách)
    int pricePerNight;      // Giá phòng/đêm (VND)
    string status;           // Trạng thái: "San sang", "Dang su dung", "Sua chua"
};
```

### 🔹 Cấu trúc Customer (Khách hàng)
```cpp
struct Customer {
    string id;              // Mã khách hàng (VD: C001)
    string name;            // Tên khách hàng
    string phone;           // Số điện thoại (10-11 số, bắt đầu bằng 0)
    string email;           // Email
    string idCard;          // CMND/CCCD
};
```

### 🔹 Cấu trúc Booking (Đặt phòng)
```cpp
struct Booking {
    string id;              // Mã booking (VD: B001)
    string customerID;      // Mã khách hàng
    string roomID;          // Mã phòng
    Date checkIn;           // Ngày nhận phòng
    Date checkOut;          // Ngày trả phòng
    int guest;              // Số lượng khách
    int pricePerNight;      // Giá phòng/đêm
    int serviceFee;         // Phí dịch vụ/đêm
    int totalCost;          // Tổng chi phí
    string status;          // Trạng thái: "Dang hoat dong", "Check Out", "Da huy"
};
```

### 🔹 Cấu trúc Date (Ngày tháng)
```cpp
struct Date {
    int day;               // Ngày (1-31)
    int month;             // Tháng (1-12)
    int year;              // Năm (1900-2100)
};
```

---

## 🧠 Các Chức năng Nghiệp vụ

### 1️⃣ Quản lý Phòng
- ✅ **Thêm phòng**: Thêm phòng mới vào hệ thống với đầy đủ thông tin.
- ✅ **Cập nhật phòng**: Sửa đổi thông tin phòng (loại, sức chứa, giá).
- ✅ **Xóa phòng**: Xóa phòng (kiểm tra không có booking đang hoạt động).
- ✅ **Tìm kiếm phòng**: 
  - Tìm theo mã phòng (Binary Search)
  - Tìm theo loại phòng
  - Tìm theo khoảng giá
  - Xem phòng trống
- ✅ **Danh sách phòng**: Hiển thị toàn bộ danh sách phòng.

### 2️⃣ Quản lý Khách hàng
- ✅ **Thêm khách hàng**: Thêm khách hàng mới với validation số điện thoại và email.
- ✅ **Cập nhật khách hàng**: Sửa đổi thông tin khách hàng.
- ✅ **Xóa khách hàng**: Xóa khách hàng (kiểm tra không có booking đang hoạt động).
- ✅ **Tìm kiếm khách hàng**:
  - Tìm theo mã khách hàng
  - Tìm theo tên (tìm kiếm một phần)
  - Tìm theo số điện thoại
- ✅ **Danh sách khách hàng**: Hiển thị toàn bộ danh sách khách hàng.

### 3️⃣ Quản lý Đặt phòng
- ✅ **Đặt phòng**: Tạo booking mới với kiểm tra:
  - Phòng tồn tại và sẵn sàng
  - Không trùng lịch với booking khác
  - Số khách không vượt quá sức chứa
  - Tính toán tự động tổng chi phí
- ✅ **Check-out**: Xử lý trả phòng và cập nhật trạng thái.
- ✅ **Hủy booking**: Hủy booking đang hoạt động.
- ✅ **Tìm kiếm booking**:
  - Tìm theo mã booking (Binary Search)
  - Tìm theo mã khách hàng
  - Tìm theo mã phòng
  - Tìm theo trạng thái
- ✅ **Danh sách booking**: Hiển thị toàn bộ danh sách booking.

### 4️⃣ Báo cáo & Thống kê
- ✅ **Thống kê doanh thu**: Tổng doanh thu, số lượng booking theo trạng thái.
- ✅ **Thống kê trạng thái phòng**: Số phòng trống, đã đặt, bảo trì và tỷ lệ sử dụng.
- ✅ **Lịch sử khách hàng**: Xem lịch sử đặt phòng và tổng chi tiêu của khách hàng.
- ✅ **Tối ưu doanh thu (Quy hoạch động)**: Tìm cách chọn các booking không trùng lịch để tối đa hóa doanh thu.

---

## 🔍 Thuật toán được sử dụng

### 1️⃣ Tìm kiếm (Search)

#### 🔹 Binary Search (Tìm kiếm nhị phân)
- **Mục đích**: Tìm kiếm nhanh phòng và booking theo mã.
- **Độ phức tạp**: O(log n)
- **Vị trí sử dụng**:
  - `binarySearchRoomById()`: Tìm phòng theo mã
  - `binarySearchBookingById()`: Tìm booking theo mã
- **Yêu cầu**: Dữ liệu phải được sắp xếp trước khi tìm kiếm.

#### 🔹 Linear Search (Tìm kiếm tuyến tính)
- **Mục đích**: Tìm kiếm khách hàng, phòng và booking theo các tiêu chí khác.
- **Độ phức tạp**: O(n)
- **Vị trí sử dụng**:
  - `findRoom()`, `findCustomer()`, `findBooking()`
  - Tìm kiếm theo loại phòng, tên khách hàng, số điện thoại

### 2️⃣ Sắp xếp (Sort)

#### 🔹 STL Sort với Comparator
- **Mục đích**: Sắp xếp danh sách phòng và booking theo mã để hỗ trợ Binary Search.
- **Độ phức tạp**: O(n log n)
- **Vị trí sử dụng**:
  - `sortRoomsById()`: Sắp xếp phòng theo mã tăng dần
  - `sortBookingsById()`: Sắp xếp booking theo mã tăng dần
- **Thuật toán**: Sử dụng `std::sort()` với lambda comparator.

### 3️⃣ Quy hoạch động (Dynamic Programming)

#### 🔹 Tối ưu Doanh thu - Weighted Interval Scheduling
- **Bài toán**: Cho danh sách booking, tìm cách chọn các booking không trùng lịch để tối đa hóa doanh thu.
- **Phương pháp**: 
  1. Sắp xếp booking theo ngày check-out (kết thúc)
  2. Với mỗi booking i, tìm booking gần nhất không trùng lịch (lastNonOverlap)
  3. DP: `dp[i] = max(không chọn booking i, chọn booking i + dp[lastNonOverlap])`
  4. Kết quả: `dp[n-1]` là doanh thu tối đa có thể đạt được
- **Độ phức tạp**: O(n²) với n là số lượng booking
- **Vị trí**: `optimizeRevenue()` trong menu Báo cáo & Thống kê → Mục 4
- **Kết quả**: Hiển thị doanh thu tối đa, tổng doanh thu hiện tại và tỷ lệ tối ưu

> 💡 **Giải thích**: Đây là bài toán Weighted Interval Scheduling kinh điển trong thuật toán. Mỗi booking được coi như một interval có trọng số (doanh thu), và ta cần chọn các interval không trùng lịch để tối đa hóa tổng trọng số.

---

## 🛠️ Xử lý Dữ liệu

### 🔹 Validation dữ liệu
- **Ngày tháng**: Kiểm tra tính hợp lệ (năm nhuận, số ngày trong tháng).
- **Số điện thoại**: 10-11 số, bắt đầu bằng 0.
- **Email**: Kiểm tra định dạng cơ bản (@ và dấu chấm).
- **Trùng lịch**: Kiểm tra booking không trùng lịch khi đặt phòng.

### 🔹 Tính toán tự động
- **Số đêm**: Tính tự động từ ngày check-in và check-out.
- **Tổng chi phí**: `totalCost = số_đêm × (pricePerNight + serviceFee)`
- **Tỷ lệ sử dụng phòng**: `(số_phòng_đã_đặt / tổng_số_phòng) × 100%`

---

## 📈 Cách sử dụng

### 🔹 Biên dịch và chạy chương trình

```bash
# Biên dịch (Windows với MinGW)
g++ -o hotel_management Project_I_QuanLyKhachSan.cpp

# Chạy chương trình
./hotel_management
```

### 🔹 Menu chính
```
========================== He thong quan ly khach san ==========================
1. Quan ly phong
2. Quan ly khach hang
3. Quan ly dat phong
4. Bao cao & Thong ke
0. Thoat
```

### 🔹 Menu Báo cáo & Thống kê
```
=============================== Bao cao thong ke ===============================
1. Thong ke doanh thu
2. Thong ke trang thai phong
3. Lich su khach hang
4. Toi uu doanh thu (Quy hoach dong)
0. Quay lai
```

### 🔹 Quy trình sử dụng cơ bản

1. **Thêm dữ liệu mẫu**: Chương trình tự động tạo dữ liệu mẫu khi khởi động.
2. **Quản lý phòng**: Thêm, sửa, xóa và tìm kiếm phòng.
3. **Quản lý khách hàng**: Thêm và quản lý thông tin khách hàng.
4. **Đặt phòng**: Tạo booking mới với kiểm tra tự động.
5. **Báo cáo**: Xem thống kê và sử dụng tính năng tối ưu doanh thu.

---

## 📊 Kết quả và Đánh giá

### 🔹 Hiệu suất thuật toán
- **Binary Search**: Tìm kiếm phòng/booking trong O(log n) thay vì O(n), tăng tốc đáng kể với dữ liệu lớn.
- **Quy hoạch động**: Tối ưu doanh thu với độ phức tạp O(n²), có thể xử lý hàng trăm booking một cách hiệu quả.
- **Sắp xếp**: Sử dụng thuật toán sắp xếp tối ưu O(n log n) của STL.

### 🔹 Tính năng nổi bật
- ✅ Giao diện Command Line thân thiện, dễ sử dụng.
- ✅ Validation dữ liệu đầy đủ, đảm bảo tính toàn vẹn.
- ✅ Kiểm tra trùng lịch tự động khi đặt phòng.
- ✅ Tính toán chi phí tự động.
- ✅ Báo cáo và thống kê chi tiết.
- ✅ Áp dụng thuật toán Quy hoạch động để giải quyết bài toán tối ưu doanh thu thực tế.

### 🔹 Ứng dụng thực tế
- Hệ thống có thể được sử dụng để quản lý khách sạn nhỏ và vừa.
- Thuật toán Quy hoạch động giúp tối ưu hóa việc sử dụng phòng và tăng doanh thu.
- Code được viết rõ ràng, dễ bảo trì và mở rộng.

---

## 📝 Ghi chú

- Dữ liệu được lưu trữ trong bộ nhớ (vector), không lưu vào file.
- Chương trình tự động tạo dữ liệu mẫu khi khởi động để demo.
- Tất cả các chức năng đều có validation và xử lý lỗi đầy đủ.
- Thuật toán Quy hoạch động được áp dụng cho bài toán Weighted Interval Scheduling.

---

## 👨‍💻 Tác giả
Nguyen Nguyen Trung

## 📄 License
Dự án này được tạo cho mục đích học tập và nghiên cứu.
