#include <iostream>
using namespace std;

void bubble_sort (int a[]) { //O(n^2)
    int n = 10;
    int temp;
    for (int i = 0; i < n ; i++)
        for (int j = 0; j < n - 1; j++) {
            if (a[j] > a[j+1]) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
}

void selection_sort (int a[]) { //O(n^2)
    int n = 10;
    int temp;
    for (int i = 0; i < n - 1; i++) {
        int minpos = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minpos])
                minpos = j;
        temp = a[i];
        a[i] = a[minpos];
        a[minpos] = temp;
    }
}

void insertion_sort (int a[]) { //O(n^2)
    int n = 10;
    for (int i = 1; i < n; i++) {
        int x = a [i];
        int j = i;
        while (j > 0 && a[j - 1] > x) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = x;
    }
}

void merge_sort (int a[], int first, int last) { //O(nlogn)
    int mid;
    if (first >= last)
        return;
    mid = (first + last) / 2;
    merge_sort (a, first, mid);
    merge_sort (a, mid + 1, last);
    int b[last - first + 1];
    int i = first, j = mid + 1, k = 0;
    while (i <= mid && j <= last)
        if (a[i] < a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    while (i <= mid)
        b[k++] = a[i++];
    while (j <= last)
        b[k++] = a[j++];
    for (i=0; i<k; i++)
        a[first+i] = b[i];
}

void quick_sort (int a[], int first, int last) { //O(nlogn)
    if (first >= last)
        return;
    int x = a[(first + last)/2];
    int i = first, j = last;
    while (true) {
        while (a[i] < x) i++;
        while (x < a[j]) j--;
        if (i >= j) break;
        swap(a[i], a[j]); i++; j--;
    }
    quick_sort (a, first, i);
    quick_sort (a, i + 1, last);
}

int main () {
    int a1[10] = {1, 5, 4, 7, 2, 8, 10, 3, 9, 6};
    int a2[10] = {3, 6, 1, 8, 10, 9, 7, 4, 2, 5};
    int a3[10] = {1, 3, 5, 2, 4, 7, 6, 8, 9, 10};
    int a4[10] = {10, 9 ,8, 6, 7, 4, 3, 2,  5, 1};
    int a5[10] = {1, 4, 7, 8, 9, 10, 2, 3, 5, 6};
    bubble_sort(a1);
    selection_sort(a2);
    insertion_sort(a3);
    merge_sort(a4, 1, 10);
    quick_sort(a5, 1, 10);
    for (int i = 0; i < 10; i++)
        cout << a1[i] << " ";
    cout << endl;
    for (int i = 0; i < 10; i++)
        cout << a2[i] << " ";
    cout << endl;
    for (int i = 0; i < 10; i++)
        cout << a3[i] << " ";
    cout << endl;
    for (int i = 0; i < 10; i++)
        cout << a4[i] << " ";
    cout << endl;
    for (int i = 0; i < 10; i++)
        cout << a5[i] << " ";
    cout << endl;
    return 0;
}
