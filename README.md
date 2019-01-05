# Castlevania
<p align="center">Đồ án môn học Nhập môn phát triển Game - Trường Đại học Công nghệ thông tin - DHQG HCM.</p>

### GIẢNG VIÊN HƯỚNG DẪN:
- Đinh Nguyễn Anh Dũng
- Huỳnh Hồ Thị Mộng Trinh

### SINH VIÊN THỰC HIỆN:
Nguyễn Thành Luân - MSSV: 16520703 - Lớp: SE102.J13.PMCL

### HƯỚNG DẪN
1. Màn hình TitleScreen:
- Ấn phím bất kì để chơi game.
2. Màn hình OverScreen:
- Up: Di chuyển lựa chọn lên trên.
- Down: Di chuyển lựa chọn xuống dưới.
- Z: Xác nhận lựa chọn.
3. Điều khiển Simon:
- Left: Di chuyển qua trái, hoặc đi lên/xuống cầu thang khi Simon đang đứng trên cầu thang.
- Right: Di chuyển qua phải, hoặc đi lên/xuống cầu thang khi Simon đang đứng trên cầu thang.
- Up: Đi lên cầu thang.
- Down: Ngồi xuống, hoặc đi xuống cầu thang nếu Simon đứng gần cầu thang.
- A: Quất roi.
- S hoặc Up + A: Phóng vũ khí phụ.
- Space: Nhảy.
4. Nâng cấp vũ khí (tương tự như khi nhặt vật phẩm):
- Num 0: Đồng hồ ngưng thời gian
- Num 1: Dao găm
- Num 2: Rìu
- Num 3: Nước thánh
- Num 4: Boomerang
5. Hiệu ứng của vật phẩm (tương tự như khi nhặt vật phẩm):
- Num 5: Hiệu ứng thánh giá
- Num 6: Hiệu ứng double-shot (phóng 2 vũ khí phụ cùng lúc)
- Num 7: Hiệu ứng triple-shot (phóng 3 vũ khí phụ cùng lúc)
- Num 8: Hiệu ứng tàng hình
6. Chuyển trạng thái game (màn chơi)
- Q: Cảnh ngoài lâu đài
- W: Cảnh trong lâu đài, phòng 1 (phòng chứa báo đen)
- E: Cảnh trong lâu đài, phòng 2 (phòng chứa dơi)
- R: Cảnh trong lâu đài, phòng 3 (phòng chứa boss)
- T: Cảnh trong lâu đài, hầm nước, cầu thang xuống 1
- Y: Cảnh trong lâu đài, hầm nước, cầu thang xuống 2
7. Phím chức năng:
- Pause: Pause game
- L: Reset game về cảnh ngoài lâu đài

### NOTE
- Không thể ấn phím nếu animation hành động của Simon vẫn chưa diễn ra hết.

### THƯ VIỆN HỖ TRỢ
- Directx 9 SDK

### MÔI TRƯỜNG PHÁT TRIỂN
- Microsoft Visual Studio 2015
- C++
- Mappy TiledMap Editor

### TÀI LIỆU THAM KHẢO
- Wiki: http://castlevania.wikia.com
- Resource: https://www.spriters-resource.com/nes/cv/
- Grid: http://gameprogrammingpatterns.com/spatial-partition.html
- Mappy: https://tilemap.co.uk/mappy.php
- Framework của thầy Đinh Nguyễn Anh Dũng: https://github.com/dungdna2000/gamedev-intro-tutorials
