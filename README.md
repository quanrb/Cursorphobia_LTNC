# Bài tập lớn INT2215 23
# *Cursorphobia*
## Thông tin chung
- Họ và tên: Nguyễn Minh Quân
- MSSV: 22028290
- Bài tập lớn: Cursorphobia (Lớp lập trình nâng cao - INT2215 23)
## Mô tả chi tiết
## *Nhân vật*
- Nhân vật trong game có đặc điểm là... sợ con trỏ chuột (cursor - phobia). Khi ta di chuyển chuột đến gần thì player sẽ di chuyển theo hướng ra xa con trỏ, nếu chuột chạm vào nhân vật thì nhân vật sẽ... "tiêu".
## *Cách chơi*
- Hoàn toàn sử dụng chuột, khi con trỏ chuột ở đủ gần nhân vật, nhân vật sẽ di chuyển và có thể nhảy lên khi ấn chuột.
- Phần xử lý vật lý cho phép con trỏ càng gần nhân vật thì tốc độ của nhân vật càng nhanh và nhảy cũng sẽ cao hơn.
- Khi nhân vật "chạm" phải bẫy gai, nhân vật cũng sẽ tèo.
## *Gameplay*
### [YouTube](https://www.youtube.com/watch?v=KDwvrNPs01A)
![image](https://github.com/quanrb/Cursorphobia_LTNC/assets/124875538/2ec8c940-fcdd-4334-a0bd-5e47a8c8abde)
![image](https://github.com/quanrb/Cursorphobia_LTNC/assets/124875538/db92c368-163f-4e74-a3e7-7f1a7c6f3c82)
![image](https://github.com/quanrb/Cursorphobia_LTNC/assets/124875538/ecc8280e-e7bc-4672-acf9-e17753e6f4bc)
![image](https://github.com/quanrb/Cursorphobia_LTNC/assets/124875538/7afb958a-ba06-4b37-ba98-a877f4edbfb6)
![image](https://github.com/quanrb/Cursorphobia_LTNC/assets/124875538/219fc6d2-01dc-4a7f-8b37-04114d58007d)
![image](https://github.com/quanrb/Cursorphobia_LTNC/assets/124875538/a5abcc13-400b-4bec-9663-09ce8a3d80d7)

## *Các kĩ thuật sử dụng*
### *SDL2*
- Groundtile, render,...
- Tải hình ảnh, text, âm thanh đơn giản.
### *C++*
- Kiến thức lập trình cơ bản: vector, rand,...
- Lập trình hướng đối tượng (OOP): class, đóng gói, kế thừa,...
## *Cài đặt*
- Windows 64bit & MinGW-64.
- Tải hoặc clone thư mục GitHub này về thiết bị, compile và run.
- Build `main.exe` như sau:
  ``` g++ -Iinclude -Iinclude/sdl -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf ```
## *Nguồn tham khảo*
- Thư viện SDL2: [LazyFoo](https://lazyfoo.net/tutorials/SDL/index.php), Bài giảng của cô Châu.
- OOP: Giáo trình OOP của ĐHQGHN.
- Cách vận dụng: 
  - [Channel Phát triển phần mềm](https://www.youtube.com/@PhatTrienPhanMem123AZ)
- Hình ảnh: PolyMars & Tự phát triển
- Âm thanh: Google
## *Hướng phát triển tiếp*
- Thêm một số "tính năng" cho game như quái đuổi hoặc ăn "tim" để có thêm mạng.
