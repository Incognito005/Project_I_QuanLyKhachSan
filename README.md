# 🏨 Hệ thống Quản lý Khách sạn

Hệ thống quản lý khách sạn được xây dựng bằng C++ với giao diện command line. Hỗ trợ quản lý phòng, khách hàng, đặt phòng và báo cáo thống kê.

## 📋 Chức năng chính

- **Quản lý phòng**: Thêm, sửa, xóa, tìm kiếm phòng
- **Quản lý khách hàng**: Thêm, sửa, xóa, tìm kiếm khách hàng
- **Quản lý đặt phòng**: Đặt phòng, check-out, hủy booking
- **Báo cáo**: Thống kê doanh thu, trạng thái phòng, lịch sử khách hàng

## 🔍 Thuật toán sử dụng

### 1. Tìm kiếm (Search)
- **Binary Search**: Tìm phòng và booking theo mã (O(log n))
- **Linear Search**: Tìm kiếm theo các tiêu chí khác (O(n))

### 2. Sắp xếp (Sort)
- Sắp xếp phòng và booking theo mã để hỗ trợ Binary Search (O(n log n))

### 3. Quy hoạch động (Dynamic Programming)
- **Bài toán**: Tối ưu doanh thu từ các booking không trùng lịch
- **Thuật toán**: Weighted Interval Scheduling
- **Độ phức tạp**: O(n²)
- **Cách dùng**: Menu "Báo cáo & Thống kê" → "Toi uu doanh thu"

## 🚀 Cách chạy

```bash
# Biên dịch
g++ -o hotel_management Project_I_QuanLyKhachSan.cpp

# Chạy chương trình
./hotel_management
```

Chương trình sẽ tự động tạo dữ liệu mẫu khi khởi động.

## 📊 Cấu trúc dữ liệu

- **Room**: id, type, capacity, pricePerNight, status
- **Customer**: id, name, phone, email, idCard
- **Booking**: id, customerID, roomID, checkIn, checkOut, guest, totalCost, status
- **Date**: day, month, year

## 👨‍💻 Tác giả
Nguyen Nguyen Trung
