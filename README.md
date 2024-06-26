# **Programing_C_Advance**
NGUYỄN VĂN THƯỜNG

## **Lesson 0: Compiler and Macro** 
16/04/2024
### **Compiler là gì ?**
Compiler hay còn gọi là ***trình biên dịch*** có thể đucợ hiểu là công việc dịch chuối câu lệnh được viết từ một ngôn ngữ lập trình thành chương trình tương đương dưới dạng ngôn ngữ máy tính, thường là ngôn ngữ ở cấp thấp hơn, ngôn ngữ máy. Đơn giản dễ hiểu thì có thể tạm nói là nhờ Compiler này mà file .c chúng ta viết mới được dịch thành file .hex .bin để nạp được xuống một MCU bất kỳ.

### **Quá trình biên dịch**

<img src= https://hocarm.org/content/images/2020/04/compiler_gcc.gif>

<img src= https://hocarm.org/content/images/2020/04/excuting_a_program.png>

***"Kiến thúc về tool chain tham khảo trong link này".***
https://hocarm.org/tim-hieu-compiler/

### **Practice**
#### **Lệnh Compiler**

```c
gcc -E main.c -o main.i
gcc -E main.c -o main.i
```
### **Macro**
***Macro khác biến cái gì ?***

Macro chỉ diễn ra ở preprocess, chỉ thay thế cái đoạn chương mà nó được định nghĩa thôi.

Trong quá trình preprocess các đoạn Commend bị mất đi.

***Loại Macro:***

Macro function.
```c
#include <stdio.h>

#define SUM(a, b) a + b

int main(int argc, char const *argv[])
{
    printf("Tong a va b: %d\n", SUM(5, 8));
    printf("Tong a va b: %d\n", SUM(4, 3));
    printf("Tong a va b: %d\n", SUM(4, 8));
    return 0;
}
```
Một số toán tử trong Macro.

```c
#include <stdio.h>

#define STRINGGIZE_RESULT(x) STRINGIZE(x)
#define STRINGIZE(x) #x
#define DATA 40

int main()
{
    printf("The value is: %s\n", STRINGGIZE_RESULT(DATA));
    
    return 0;
}
```
```c
#include <stdio.h>

#define DECLARE_VARIABLE(prefix, number) int prefix##number

int main()
{
    DECLARE_VARIABLE(var, 1);
    DECLARE_VARIABLE(var, 2);

    var1 = 10;
    var2 = 20;

    printf("The value of var 1 is: %d\n", var1);
    printf("The value of var 2 is: %d\n", var2);
    
    return 0;
}
```
```c
#include <stdio.h>

#define PRINT_MENU_ITEM(number, item) printf("%d. %s\n", number, item);
#define PRINT_MENU(...) \
        do { \
            const char* items[] = {__VA_ARGS__}; \
            int n = sizeof(items)/sizeof(items[0]); \
            for (int i = 0; i < n; i++) { \
                PRINT_MENU_ITEM(i+1, items[i]); \
            } \
        } while (0);

#define HANDLE_OPTION(option, ...) \
        switch (option) { \
            __VA_ARGS__ \
            default: printf("Invalid option!\n"); \
        }

#define CASE_OPTION(number, function) \
        case number: \
            function(); \
            break;

void feature1() {
    printf(" Feature 1 selected\n");
}

void feature2() {
    printf(" Feature 2 selected\n");
}

void feature3() {
    printf(" Feature 3 selected\n");
}
int main()
{
    PRINT_MENU( "OPTION 1", 
                "OPTION 2", 
                "OPTION 3",  
                "EXIT");

    int option;
    scanf("%d", &option);

    HANDLE_OPTION(option,
        CASE_OPTION(1, feature1)
        CASE_OPTION(2, feature2)
        CASE_OPTION(3, feature3)    
    )
    return 0;
}

#include <stdio.h>

#define DISPLAY(name, cmd)                  \
void name() {                               \
    printf(#cmd);                           \
    printf("\n");                           \
}

DISPLAY(test1, This is test 1);

DISPLAY(test2, This is test 2);

#define CREATE_VARIABLE(name)               \
int int##_name;                             \
double double##_name;                       \
char char##_name;    

int main(int argc, char const *argv[])
{
    test1();
    test2();

    CREATE_VARIABLE(test1);
    return 0;
}
```

```c
#include <stdio.h>
#include <stdint.h>

#define STM32F103 0
#define PID16F887 1

#define MCU PID16F887

typedef enum{
    LOW,
    HIGH
}Status;

typedef enum{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}Pins;

#if MCU == STM32F103
void digitaWrite(Pins pins, Status status) {
    if (status == HIGH){
        GPIOA->BSRR |= (1<<pins); // Set the pin PA5
    } else{
        GPIOA->BSRR |= ((1<<pins) << 16); // Reset the pin PA5
    }
}

#elif MCU == PID16F887
void digitaWrite(Pins pins, Status status) {
    if (status == HIGH){
        GPIOA |= (1<<pins); // Set the pin PA5
    }else {
        GPIOA |= ((1<<pins) << 16); // Reset the pin PA5
    }
}
#endif

int main(int argc, char const *argv[])
{
    digitaWrite(PIN0, HIGH);
    return 0;
}
```

```c
#define SIZE 30

int arr[SIZE];

#undef SIZE  

#define SIZE 35

int arr[SIZE];
```

```c
#define SIZE 30
#ifdef SIZE 

void () {
    printf(""test\n);
}
#endif
```
```c
#ifndef SIZE

#endif
```

***Thiết kế thư viện.***
```c
#ifndef _TEST_H
#define _TEST_H

#endif
```

```c
#include <stdio.h>
#include <stdint.h>

#define SUM(...) \
    int array[] = {__VA_ARGS__, 0}; \
    int i = 0; \
    int sum = 0; \
    printf("Tong: "); \
    while (array[i] != 0){ \
        printf("%d\n", array[i]); \
        sum = sum + array[i]; \
        i++; \
    } \ 
    printf("= %d\n", sum); \


int main(int argc, char const *argv[])
{
    SUM(5, 8, 1, 9);
    return 0;
}
```

```c
#include <stdio.h>
#include <stdint.h>

#define PRINT_MENU_ITEM(number, item) printf("%d. %s\n", number, item)
#define PRINT_MENU(...) \
    do { \
        const char* items[] = {__VA_ARGS__}; \
        int n = sizeof(items) / sizeof(items[0]); \
        for (int i = 0; i < n; i++) { \
            PRINT_MENU_ITEM(i + 1, items[i]); \
        } \
    } while (0)

#define CASE_OPTION(number, function) case number: function(); break;
#define HANDLE_OPTION(option, ...) \
    switch (option) { \
        __VA_ARGS__ \
        default: printf("Invalid option!\n"); \
    }


void feature1() { printf("Feature 1 selected\n"); }
void feature2() { printf("Feature 2 selected\n"); }
void feature3() { printf("Feature 3 selected\n"); }
void feature4() { printf("Feature 3 selected\n"); }

int main()
{
    PRINT_MENU("Option 1", "Option 2", "Option 3","Option4", "Exit");

    // Giả sử option được nhập từ người dùng
    int option ;
    scanf("%d", &option);

    HANDLE_OPTION(option,
        CASE_OPTION(1, feature1)
        CASE_OPTION(2, feature2)
        CASE_OPTION(3, feature3)
        CASE_OPTION(4, feature4)
    )
    return 0;
}

```
### **Lesson 1: Stdarg  and assert**
**1. Thư viện Stdarg**

Cung cấp các phương thức để làm việc với các hàm có số lượng input parameter không cố định.

Các hàm như printf và scanf là ví dụ điển hình 

**va_list:** là một kiểu dữ liệu để đại diện cho danh sách các đối số biến đổi.

**va_start:** Bắt đầu một danh sách đối số biến đổi. Nó cần được gọi trước khi truy cập các đối số biến đổi đầu tiên.

**va_arg:** Truy cập một đối số trong danh sách. Hàm này nhận một đối số của kiểu được xác định bởi tham số thứ hai.

**va_end:** Kết thúc việc sử dụng danh sách đối số biến đổi. Nó cần được gọi trước khi kết thúc hàm.

```c
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR
} SensorType;

void processSensorData(SensorType type, ...) {
    va_list args;
    va_start(args, type);

    switch (type) {
        case TEMPERATURE_SENSOR: {
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            float temperature = va_arg(args, double); // float duoc promote thanh double
            printf("Temperature Sensor ID: %d, Reading: %.2f degrees\n", sensorId, temperature);
            if (numArgs > 2) {
                char* additionalInfo = va_arg(args, char*);
                printf("Additional Info: %s\n", additionalInfo);
            }
            break;
        }

        case PRESSURE_SENSOR: {
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            int pressure = va_arg(args, int);
            printf("Pressure Sensor ID: %d, Reading: %d Pa\n", sensorId, pressure);
            if (numArgs > 2) {
                char* uint = va_arg(args, char*);
                printf("Unit: %s\n", uint);
            }
            break;
        }
    }

    va_end(args);
}

int main()
{
    int a = 2;
    processSensorData(TEMPERATURE_SENSOR, a, 1, 36.5, "jhajksdas");
    return 0;
}
```

```c
#include <stdio.h>
#define NDEBUG
#include <assert.h>

double thuong(int a, int b) {
    assert("ERROR!! b == 0" && b != 0);
    return (double)a/b;
}

int main()
{
    printf("Thuong: %f\n", thuong(5, 0));
    return 0;
}
```

```c
#include <stdio.h>

int main()
{
    int var = 10;

    printf("Dia chi var: %p\n", &var);

    int *ptr = &var; // int *ptr = (int *)0x5465432

    printf("Dia chi: %p, gia tri: %d\n", ptr, *ptr); // *ptr = *(&var)
    return 0;
}
```
***Kích thước Pointer phụ thuộc vào kiến trúc của máy tính và trình biên dịch.***
```c
#include <stdio.h>

int main()
{
    float *ptr; // int, double or float .. thì size of pointer bằng nhau
    printf("Size of pointer: %d bytes\n", sizeof(ptr));
    return 0;
}
```
***chương trình Swap hai số nguyên***
```c
#include <stdio.h>

void swap(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main()
{
    int a = 10, b = 20;
    swap(&a, &b);

    printf("Value a is: %d\n", a);
    printf("Value b is: %d\n", b);
    return 0;
}
```
***Function Pointer***
Pointer to function là một biến mà giữa địa chỉ của một ***hàm***. Có nghĩa là nó trỏ đến vùng nhớ trong bộ nhớ chứa mã máy của hàm được định nghĩa trong chương trình.

Trong ngôn ngữ lập trình C, pointer to function ***cho phép bạn truyền một hàm như là một đối số cho một hàm khác***, ***lưu trữ địa chỉ của hàm trong một cấu trúc dữ liệu*** hoặc thậm chí ***truyền hàm như một giá trị trả về từ một hàm khác.***

```c
#include <stdio.h>

void greetEnglish() {
    printf("Hello!\n");
}

void greetFrench() {
    printf("Bonjour!\n");
}

int main()
{
    void (*ptrToGreet)();

    ptrToGreet = greetEnglish;

    (*ptrToGreet)();

    ptrToGreet = greetFrench;

    (*ptrToGreet)();

    return 0;
}
```

```c
#include <stdio.h>

void sum(int a, int b) {
    printf("Sum of %d and %d is: %d\n", a, b, a+b);
}

void subtract(int a, int b) {
    printf("Subtract of %d by %d is: %d \n", a, b, a-b);
}

void multiple(int a, int b) {
    printf("Multiple of %d and %d is: %d\n", a, b, a*b);
}

void divide(int a, int b) {
    if (b == 0) {
        printf("Mau só phai khac 0\n");
        return;
    }
    printf("%d divided by %d is: %f\n", a, b, (double)a / (double)b);
}

void calculator(void (*ptr)(int, int), int a, int b) {
    printf("Program calculate: ");
    ptr(a, b);
}
int main()
{
    calculator(sum, 5, 2);
    calculator(subtract, 5, 2);
    calculator(multiple, 5, 2);
    calculator(divide, 5, 2);

    return 0;
}
```

## **Lesson 1: Biến** 
Ngày: 7/11/2023
### **Biến**
- Các biến nguyên thủy: float, double....
- Trong ngành Nhúng ta sử dụng thư viện "stdint" để định nghĩa lại.
- Thư viện "stdio.h" giao tiếp với màn hình console.
- Để xác định kích thước của biến ta dùng hàm sizeof(). Lưu ý đối kích thước ta truyền với kiểu %lu. VD:
```c
#include <stdio.h>
#include <stdint.h>
uint8_t var; 
int main() {
    printf("size: %lu byte", sizeof(var));
    return 0;
}
```
- Ta thấy kết quả: 

>size: 1 byte

- Định nghĩa "uint8_t" trong thư viện "stdint.h"

>typedef unsigned char		uint8_t;

unsigned: số dương.

unit8_t là kiểu số nguyên dương.

Kích thước 1 byte = 8 bit ~ phạm vi [0 - 255].

VD: 
```c
#include <stdio.h>
#include <stdint.h>

uint8_t var; // 8 bit = 1 byte ~ 2^8 = 256  0-255


int main() {
  var = 256;
  printf("size: %lu byte\n", sizeof(var));

  printf("var = %d\n", var);
  return 0;
}
```

- Ta thấy kết quả:
```
lesson_1.c:8:9: warning: large integer implicitly truncated to unsigned type [-Woverflow]
   var = 256;
         ^~~
size: 1 byte
var = 0
```
- Định nghĩa "int8_t" trong thư viện "stdint.h".

unit8_t là kiểu số nguyên dương và âm.

Kích thước 1 byte = 8 bit ~ phạm vi [-128 - 127].

VD: 
```C
#include <stdio.h>
#include <stdint.h>

int8_t var; // 8 bit = 1 byte

int main() {
  var = 256;
  printf("size: %lu byte\n", sizeof(var));

  printf("var = %d\n", var);
  return 0;
}
```

- Ta có kết quả:
```
lesson_1.c:8:9: warning: overflow in implicit constant conversion [-Woverflow]     
   var = 256;
         ^~~
size: 1 byte
var = 0
```

- Định nghĩa "int32_t" trong thư viện "stdint.h".

unit8_t là kiểu số nguyên dương và âm.

Kích thước 1 byte = 8 bit ~ phạm vi [-2^32 - 2^32-1].

- Trong lập trình Nhúng ta không dùng kiểu:

>int: kiểu số nguyên, kích thước 4 byte khi kiến trúc 64 bit còn nếu 2 byte với kiến trúc 32 bit. Ví thế người ta không thể dùng cho các chip khác nhau. 

- Định nghĩa float: kiểu số thực, kích thước 4 byte.
- Định nghĩa double: kiểu số thực, kích thước 8 byte. 

- Trong lập trình nhúng bộ nhớ giới hạn nên việc khai báo biến cực kì cẩn thận.

**Hàm**

VD: Hàm không trả về
```C
#include <stdio.h>
#include <stdint.h>

void hienThi(uint16_t id, char* ten, uint8_t tuoi){

    printf("ID: %d, TEN: %s, TUOI: %d\n", id, ten, tuoi);

}
int main() {
    
    // printf("ID: 1001, TEN: HOANG, TUOI: 19\n");
    // printf("ID: 1001, TEN: TUAN, TUOI: 14\n");
    // printf("ID: 1001, TEN: QUAN, TUOI: 148\n");
    // printf("ID: 1001, TEN: NAM, TUOI: 17\n");
    hienThi(1000, "Hoang", 19);
    return 0;
}
```
- Ta thấy kết quả:
```
ID: 1000, TEN: Hoang, TUOI: 19
```
VD: Hàm trả về giá trị kiểu "**uint8_t**"
```C
#include <stdio.h>
#include <stdint.h>

uint8_t tong(uint8_t a, uint8_t b){
    return a+ b;
}


int main() {

    printf("Tong a + b = %d\n", tong(7, 8));
    return 0;
}
```
- Ta thấy kết quả:
```
Tong a + b = 15
```

VD: Hàm trả về giá trị kiểu "**float**"
```c
#include <stdio.h>
#include <stdint.h>

float thuong(uint8_t a, uint8_t b){
    if (b == 0)
        printf("ERROR!! Mau bang 0\n");
    return (float)a/b;
}


int main() {

    printf("Thuogn a / b = %f\n", thuong(7, 8));
    return 0;
}

```
- Ta thấy kết quả:
```
Thuogn a / b = 0.875000
```

**Tính chất hàm:**
- Hàm có thể có hoặc không có tham số.
- Có sự lặp đi lặp lại nhiều lần

## **Lesson 2: Câu điều kiện** 

VD: 
```


```