// 보간 탐색

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int interpolationSearch(int arr[], int low, int high, int key) {
    if (key < arr[low] || arr[high] < key) return -1;
    int pos = ((double)high - low) * (key - arr[low]) / (arr[high] - arr[low]) + low;
    if (arr[pos] == key) return pos;
    else if (arr[pos] > key) return interpolationSearch(arr, low, pos - 1, key);
    else return interpolationSearch(arr, pos + 1, high, key);

}

void display(int* arr, int size) {
    for (int i = 0; i < size; i++) printf("%3d ", arr[i]);
    printf("\n");
}
void quick(int* arr, int st, int end) {
    int left = st, right = end, pivot = arr[(st + end) / 2];
    while (left <= right) {
        while (arr[left] < pivot)  left++;
        while (pivot < arr[right])  right--;
        if (left <= right) {
            int temp = arr[left]; arr[left] = arr[right]; arr[right] = temp;
            left++, right--;
        }
    }
    if (st < right) quick(arr, st, right);
    if (left < end)  quick(arr, left, end);
}
int main() {
    srand(time(NULL));
    int n = 20;
    int range = 20;
    int* a = (int*)calloc(n, sizeof(int));
    int arr[20] = { 0, 1, 1, 1, 2, 2, 4, 4, 5, 5, 7, 7, 7, 9, 11, 14, 15, 16, 18, 18 };
    printf("\n\t<< 보간 검색 >>\n");
    for (int i = 0; i < n; i++)
        a[i] = rand() % range;
    quick(a, 0, n - 1);
    display(a, n);
    for (int i = 0; i < range; i++)
        printf(" %3d 의 위치는 a[%3d] 칸 \n", i, interpolationSearch(a, 0, n - 1, i));
    return 0;
}
