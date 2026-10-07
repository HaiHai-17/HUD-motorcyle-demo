# Motorcycle HUD Demo

Demo giao diện **Head-Up Display (HUD) cho xe máy**, chạy trên ESP32-S3 và màn hình TFT độ phân giải 320×240. Giao diện được xây dựng bằng LVGL, hiển thị các thông tin cơ bản như tốc độ, cấp số, điện áp, nhiệt độ, mức nhiên liệu, vòng tua máy và các đèn cảnh báo.

> Đây là bản demo giao diện. Các giá trị HUD hiện được tạo ngẫu nhiên để mô phỏng dữ liệu cảm biến, chưa lấy từ ECU hoặc cảm biến thực tế.

## Hình ảnh demo

<img width="2268" height="1441" alt="1791392909255_2303028224121812024_2347431114217680222_efc3d665e21d9063921ab5aeb4866314" src="https://github.com/user-attachments/assets/6b9e0cc7-2129-41db-b335-3e47ab8ef3de" />

## Sơ đồ mạch

Xem sơ đồ kết nối trên Cirkit Designer:
https://app.cirkitdesigner.com/project/0c11ae4d-57a4-40f7-b794-aa193b1a1176

## Tính năng

- Hiển thị giao diện HUD trên màn hình TFT 320×240.
- Hiển thị tốc độ, cấp số và đồng hồ thời gian.
- Hiển thị điện áp ắc quy, quãng đường chuyến đi, odo và mức tiêu thụ trung bình.
- Hiển thị nhiệt độ, mức nhiên liệu và vòng tua máy.
- Mô phỏng trạng thái các đèn báo:
  - Xi-nhan trái/phải.
  - Đèn pha.
  - Check engine.
  - Dầu máy.
  - Nhiệt độ.
- Cập nhật dữ liệu mô phỏng định kỳ khoảng 700 ms.
- Giao diện được thiết kế và sinh mã bằng EEZ Studio/LVGL.

## Phần cứng

- ESP32-S3 DevKitM-1.
- Màn hình TFT SPI tương thích với `TFT_eSPI`, độ phân giải 320×240.
- Dây nối và nguồn phù hợp với board/màn hình đang sử dụng.

> Chân kết nối và driver màn hình phụ thuộc vào module TFT thực tế. Hãy kiểm tra và cấu hình `TFT_eSPI` trước khi nạp chương trình.

## Công nghệ và thư viện

- [PlatformIO](https://platformio.org/)
- Arduino framework cho ESP32.
- [LVGL](https://lvgl.io/) `^9.5.0`
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) `^2.5.43`

## Cấu trúc dự án

```text
.
├── include/
│   └── lv_conf.h       # Cấu hình LVGL
├── lib/
│   └── ui/             # Mã giao diện được sinh từ EEZ Studio
├── src/
│   └── main.cpp        # Khởi tạo màn hình và vòng lặp HUD
├── platformio.ini      # Cấu hình board và thư viện
└── README.md
```

## Cài đặt và chạy

### Yêu cầu

- Visual Studio Code.
- Extension [PlatformIO IDE](https://platformio.org/install/ide).
- Cáp USB có hỗ trợ truyền dữ liệu.

### Các bước

1. Clone repository và mở thư mục dự án bằng Visual Studio Code.
2. Kết nối ESP32-S3 với máy tính.
3. Kiểm tra lại cấu hình board trong `platformio.ini`:

   ```ini
   [env:esp32-s3-devkitm-1]
   board = esp32-s3-devkitm-1
   framework = arduino
   ```

4. Cấu hình chân SPI, driver và kích thước màn hình trong cấu hình của `TFT_eSPI`.
5. Build và nạp firmware bằng PlatformIO:

   ```bash
   pio run
   pio run --target upload
   ```

6. Mở Serial Monitor ở tốc độ `115200` để kiểm tra log khởi động:

   ```bash
   pio device monitor -b 115200
   ```

Khi khởi động thành công, Serial Monitor sẽ in:

```text
HUD display ready
```

## Ghi chú phát triển

- Logic khởi tạo màn hình và vòng lặp chính nằm trong [`src/main.cpp`](src/main.cpp).
- Các widget và hình ảnh của giao diện nằm trong [`lib/ui/`](lib/ui/).
- Có thể thay các giá trị ngẫu nhiên trong `updateRandomHud()` bằng dữ liệu đọc từ cảm biến, CAN bus hoặc ECU.
- Khi thay đổi giao diện bằng EEZ Studio, cần cập nhật lại các tệp sinh mã trong `lib/ui/`.

## Hướng phát triển

- Đọc tốc độ và vòng tua thực tế từ ECU/CAN bus.
- Kết nối cảm biến nhiên liệu, nhiệt độ và điện áp.
- Thêm cảnh báo vượt tốc độ và cảnh báo lỗi.
- Lưu dữ liệu chuyến đi và odo vào bộ nhớ không mất dữ liệu.
- Tối ưu độ sáng và khả năng đọc ngoài trời.

## Giấy phép

Chưa thiết lập giấy phép cho dự án. Vui lòng bổ sung file `LICENSE` trước khi phân phối hoặc sử dụng lại mã nguồn.
