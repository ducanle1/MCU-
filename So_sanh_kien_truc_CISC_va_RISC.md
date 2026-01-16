# SO SÁNH KIẾN TRÚC CISC VÀ RISC

## 1.1. Khái niệm cơ bản về CISC và RISC

### CISC (Complex Instruction Set Computer)

CISC là kiến trúc máy tính với tập lệnh phức tạp, trong đó mỗi lệnh có thể thực hiện nhiều thao tác ở mức cao như truy cập bộ nhớ, tính toán và lưu kết quả chỉ trong một lệnh. Các bộ xử lý CISC thường có số lượng lệnh lớn, độ dài lệnh không cố định và nhiều chế độ định địa chỉ.

Mục tiêu chính của CISC là giảm số lượng lệnh trong chương trình, từ đó giảm dung lượng bộ nhớ cần thiết và đơn giản hóa công việc của lập trình viên ở thời kỳ đầu khi bộ nhớ còn hạn chế.

**Ví dụ tiêu biểu:** Intel x86.


### RISC (Reduced Instruction Set Computer)

RISC là kiến trúc sử dụng tập lệnh đơn giản, mỗi lệnh thường thực hiện một thao tác cơ bản và có độ dài cố định. RISC tuân theo nguyên tắc **load/store**, nghĩa là chỉ có lệnh *load* và *store* mới được phép truy cập bộ nhớ, các phép toán khác chỉ thao tác trên thanh ghi.

Triết lý của RISC là tối ưu hóa tốc độ thực thi, tận dụng *pipeline* và đơn giản hóa phần cứng để đạt hiệu năng cao hơn trên mỗi chu kỳ xung nhịp.

**Ví dụ tiêu biểu:** ARM, MIPS, RISC-V.



## 1.2. Ưu điểm và nhược điểm của từng kiến trúc

### Ưu điểm và nhược điểm của CISC

**Ưu điểm:**
- Giảm số lượng lệnh trong chương trình, giúp mã máy ngắn hơn.
- Phù hợp với các trình biên dịch và ngôn ngữ bậc cao truyền thống.
- Tương thích ngược tốt, đặc biệt trong các hệ thống lâu đời như x86.

**Nhược điểm:**
- Phần cứng phức tạp, khó thiết kế và tiêu tốn nhiều transistor.
- Khó tối ưu *pipeline* do lệnh có độ dài và thời gian thực thi khác nhau.
- Tiêu thụ điện năng cao hơn.



### Ưu điểm và nhược điểm của RISC

**Ưu điểm:**
- Tập lệnh đơn giản, dễ tối ưu *pipeline* và song song hóa.
- Hiệu năng cao trên mỗi watt, phù hợp cho thiết bị di động và nhúng.
- Thiết kế phần cứng đơn giản, dễ mở rộng.

**Nhược điểm:**
- Chương trình có thể dài hơn do cần nhiều lệnh hơn.
- Phụ thuộc nhiều vào trình biên dịch để tối ưu hiệu năng.
- Một số tác vụ phức tạp cần nhiều lệnh để thực hiện.


## 1.3. So sánh CISC và RISC theo các tiêu chí

### 1.3.1. Cấu trúc tập lệnh

- **CISC:** Tập lệnh lớn, phức tạp, nhiều chế độ định địa chỉ, độ dài lệnh thay đổi.
- **RISC:** Tập lệnh nhỏ, đơn giản, ít chế độ định địa chỉ, độ dài lệnh cố định.


### 1.3.2. Tốc độ xử lý

- **CISC:** Một lệnh có thể mất nhiều chu kỳ để thực thi.
- **RISC:** Mỗi lệnh thường hoàn thành trong một chu kỳ, tối ưu cho *pipeline* → tốc độ xử lý cao hơn trong thực tế.


### 1.3.3. Kích thước chương trình

- **CISC:** Chương trình thường nhỏ gọn hơn do lệnh phức tạp.
- **RISC:** Chương trình dài hơn nhưng bù lại dễ tối ưu và thực thi nhanh.


### 1.3.4. Độ phức tạp phần cứng

- **CISC:** Phần cứng phức tạp, khó mở rộng và tiêu thụ nhiều năng lượng.
- **RISC:** Phần cứng đơn giản, dễ thiết kế và tiết kiệm năng lượng.


### 1.3.5. Ứng dụng thực tế

- **CISC:** Máy tính cá nhân, máy chủ (Intel, AMD – kiến trúc x86).
- **RISC:** Thiết bị di động, IoT, hệ thống nhúng (ARM, RISC-V).


## 1.4. Quan điểm cá nhân

Trong bối cảnh phát triển mạnh mẽ của hệ thống nhúng, IoT và thiết bị di động, kiến trúc **RISC** tỏ ra phù hợp hơn nhờ mức tiêu thụ năng lượng thấp, hiệu năng trên mỗi watt cao và khả năng tích hợp tốt trong các hệ thống nhỏ gọn.

Tuy nhiên, **CISC** vẫn giữ vai trò quan trọng trong lĩnh vực máy tính cá nhân và máy chủ nhờ khả năng tương thích ngược và sức mạnh xử lý cao. Do đó, việc lựa chọn kiến trúc phù hợp cần dựa trên mục đích sử dụng cụ thể của hệ thống.


## Kết luận

CISC và RISC là hai kiến trúc với những triết lý thiết kế khác nhau, mỗi loại đều có ưu và nhược điểm riêng. Trong khi CISC mạnh về tính linh hoạt và tương thích, RISC lại nổi bật ở hiệu năng và tiết kiệm năng lượng. Hiểu rõ sự khác biệt giữa hai kiến trúc giúp người học và kỹ sư lựa chọn giải pháp phù hợp cho từng bài toán thực tế.
