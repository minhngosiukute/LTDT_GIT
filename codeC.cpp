// Viết hàm int add(int a, int b) tính tổng hai số nguyên a+b.
int add(int a, int b){
    return (a+b);
}
// Viết chương trình đọc hai số nguyên từ bàn phím và in ra màn hình tổng của chúng.
#include<stdio.h>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d",a+b);
    return (0);
}
// Viết chương trình đọc một ma trận và đếm số phần tử lớn hơn 0 của ma trận này. In kết quả ra màn hình.

// Dữ liệu đầu vào được cho dưới dạng:

// - Dòng đầu tiên chứa số hàng m và số cột n, mỗi số cách nhau 1 khoảng trắng, (1 <= m,n <= 100).

// - m dòng tiếp theo, mỗi dòng chứa các phần tử trên cùng một hàng, mỗi phần tử cách nhau 1 khoảng trắng.

// Đầu ra: in ra số phần tử lớn hơn 0.
#include<stdio.h>
int main(){
    int m,n,t,c=0;
    scanf("%d%d",&m,&n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&t);
            if(t>0) c++;
        }
    }
    printf("%d",c);
    return 0;
}
#include <stdio.h>
int main() {
    int A[100][100], m, n;
    //Đọc số hàng m và số cột n
    scanf("%d%d", &m, &n);
    int i, j;
    //Đọc ma trận
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    //Đếm số phần tử > 0
    int kq = 0;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (A[i][j] > 0)
                kq++;
            
    //In số phần tử > 0 ra màn hình
    printf("%d\n", kq);
    return 0;
}
//nam nhuan
#include <stdio.h>

int main() {
   int year;
   year = 2016;
   
   if (((year % 4 == 0) && (year % 100!= 0)) || (year%400 == 0))
      printf("%d la mot nam nhuan", year);
   else
      printf("%d khong phai la nam nhuan", year);
      
   return 0;
}