#include <stdio.h>   
#include <string.h>  
#include <stdbool.h> 
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
typedef struct {
    char buffer[BUFFER_SIZE];  // المصفوفة التي تخزن البيانات
    int head;                  // مؤشر الكتابة (مكان الإدخال التالي)
    int tail;                  // مؤشر القراءة (مكان الإخراج التالي)
    int count;                 // عدد العناصر الموجودة حالياً
} CircularBuffer;
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
    printf("تم تهيئة المخزن الدائري بحجم %d\n", BUFFER_SIZE);
}
bool isFull(CircularBuffer *cb) {
    return cb->count == BUFFER_SIZE;
}
bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}
void write(CircularBuffer *cb, char data) {
    // أولاً: التحقق من الامتلاء
    if (isFull(cb)) {
        printf("Buffer Overflow\n");
        return;  // اخرج من الدالة فوراً، لا تخزن شيئاً
    }
    
    //head ثانياً: تخزين البيانات في موقع 
    cb->buffer[cb->head] = data;
    
    // دورياً head  ثالثاً: تحديث 
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    
    // رابعاً: زيادة العداد
    cb->count = cb->count + 1;
}
char read(CircularBuffer *cb) {
    // أولاً: التحقق من الفراغ
    if (isEmpty(cb)) {
        printf("Buffer Underflow\n");
        return '\0';  // إرجاع حرف فارغ للدلالة على الخطأ
    }
    
    //tail ثانياً: قراءة البيانات من موقع 
    char data = cb->buffer[cb->tail];
    
    // دورياً tail  ثالثاً: تحديث 
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    
    // رابعاً: إنقاص العداد
    cb->count = cb->count - 1;
    
    // خامساً: إرجاع الحرف المقروء
    return data;
}
int main() {
    // 1. إنشاء وتهيئة المخزن
    CircularBuffer cb;
    init(&cb);
    
    // 2. تعريف مصفوفة للاسم
    char name[100];
    
    // 3. طلب الاسم من المستخدم
    printf("أدخل اسمك: ");
    fgets(name, sizeof(name), stdin);
    
    // 4. إزالة علامة نهاية السطر (newline)
    name[strcspn(name, "\n")] = '\0';
    
    // 5. إضافة اللاحقة "CE-ESY"
    strcat(name, "CE-ESY");
    
    // 6. طباعة الاسم الكامل للتوضيح
    printf("الاسم الكامل المخزن: %s\n", name);
    printf("طول السلسلة: %lu حرف\n", strlen(name));
    
    // 7. تخزين كل حرف في المخزن
    printf("\n--- مرحلة الكتابة إلى المخزن ---\n");
    for (int i = 0; i < strlen(name); i++) {
        printf("محاولة كتابة الحرف '%c': ", name[i]);
        write(&cb, name[i]);
    }
        // 8. قراءة البيانات وعرضها
    printf("\n--- مرحلة القراءة من المخزن ---\n");
    printf("البيانات المقروءة: ");
    while (!isEmpty(&cb)) {
        char ch = read(&cb);
        putchar(ch);  // طباعة الحرف بدون سطر جديد
    }
    printf("\n");
        // 9. التأكد من فراغ المخزن
    if (isEmpty(&cb)) {
        printf("المخزن فارغ الآن. ✅\n");
    } else {
        printf("تحذير: المخزن لا يزال يحتوي على %d عنصر!\n", cb.count);
    }
    
    return 0;
}
