#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define InitSize 16

// 定义一个结构体。
// 数组
typedef struct
{
    int *data;       //  数组的首地址
    size_t size;     // 数组的大小
    size_t capacity; // 数组的容量
} DynamicArray;

/// @brief   初始化数组
/// @return  返回指针。
DynamicArray *init_array()
{
    // 使用malloc 动态分配地址。
    DynamicArray *array = (DynamicArray *)malloc(sizeof(DynamicArray));

    // 数组
    array->data = (int *)malloc(InitSize * sizeof(int));
    //
    array->size = 0;
    array->capacity = InitSize;
    return array;
}

// 大小
int size(DynamicArray *array)
{
    return array->size;
}
// 容量
int capactiy(DynamicArray *arr)
{
    return arr->capacity;
}

// 是否为空
bool is_empty(DynamicArray *arr)
{
    return arr->size == 0;
}

// 指针下标的数据
int at(DynamicArray *arr, int index)
{
    if (index >= arr->size)
    {
        // 越界，报错
        return -1;
    }
    return *(arr->data + index);
}

void resize(DynamicArray *arr, int new_capacity)
{
    int *new_data = (int *)malloc(new_capacity * sizeof(int));

    for (size_t i = 0; i < arr->size; ++i)
    {
        // 复制 值
        *(new_data + i) = *(arr->data + i);
    }

    // 释放
    free(arr->data);
    arr->data = new_data;
    arr->capacity = new_capacity;
}

// 添加
void push(DynamicArray *arr, int item)
{
    // 判断数组容量，进行扩容
    if (arr->size >= arr->capacity)
    {
        // 2倍扩容
        resize(arr, arr->capacity * 2);
    }

    *(arr->data + arr->size) = item;
    arr->size++;
}

// 在指定索引中插入元素，并把后面的元素依次后移
void my_insert(DynamicArray *arr, int index, int item)
{   
    if (arr->capacity <= index)
    {
        printf("指针越界 ！");
        exit(1);
    }
    
    // 判断容量
    if (arr->data + 1 >= arr->capacity)
    {
        resize(arr, arr->capacity * 2);
    }
    // 所有数据往后移动
    for (size_t i = arr->size; i > (size_t)index; --i)
    {
        *(arr->data + i) = *(arr->data + i - 1);
    }
    *(arr->data + index) = item;
    arr->size++;
}

// 重头插入
void prepend(DynamicArray *arr, int item)
{
    my_insert(arr, 0, item);
}

// 推出末端值
int pop(DynamicArray *arr)
{
    // 空数组
    if (arr->size == 0)
    {
        return -1;
    }
    int result = *(arr->data + arr->size - 1);
    arr->size--;
    if (arr->size <= arr->capacity / 4)
    {
        resize(arr, arr->capacity / 2);
    }
    return result;
}

// 删除指定索引的元素，并把后面的元素依次前移
void delete(DynamicArray *arr, int index)
{
    // 前移动
    for (size_t i = index; i < arr->size; ++i)
    {
        *(arr->data + i) = *(arr->data + i + 1);
    }
    arr->size--;
    if (arr->size <= arr->capacity / 4)
    {
        resize(arr, arr->capacity / 2);
    }
}

//  删除指定值的元素，并返回其索引（即使有多个元素）
int remove_item(DynamicArray *arr, int item)
{
    int index = -1;
    for (size_t i = 0; i < arr->size; ++i)
    {
        if (*(arr->data + i) == item)
        {
            index = i;
            delete(arr, i);
        }
    }
    return index;
}

/// @brief 寻找指定值的元素并返回其中第一个出现的元素其索引，若未找到则返回 -1
/// @param arr
/// @param item
/// @return -1 or index
int find(DynamicArray *arr, int item)
{
    int index = -1;
    for (size_t i = 0; i < arr->size; ++i)
    {
        if (*(arr->data +i) == item)
        {
            index = i;
            break; // 跳出循环
        }      
    }
    return index;
}




int main(int argc, char const *argv[])
{
    DynamicArray *arr = init_array();

    for (int i = 0; i < 200; i++)
    {
        push(arr,i);
    }

    my_insert(arr,2,88);

    //pop 
    printf( " pop :  %zu \n",pop(arr));

    // at
    printf(" at 23: %zu \n",at(arr,23));

    // szie
    printf("Array size: %zu\n", size(arr));
    // capacity
    printf("Array size: %zu\n", capactiy(arr));

    // delete
    delete(arr,2);
    
    //find 
    printf(" find 88: %zu\n",find(arr,88));
    

    printf("Array size: %zu\n", capactiy(arr));
    return 0;
}
