/*Viết hàm add_edge(Graph* G, int x, int y) để thêm cung (x, y) vào đồ thị G.
void add_edge(Graph* G, int x, int y) {
}
Chú ý:
- Nếu cung (x, y) không hợp lệ (vd: x < 1, y > n, ...) thì bỏ qua không làm gì cả.
*/
void add_edge(Graph *G,int x,int y){
    if(x>0 && x<=G->n && y>0 && y<=G->n){
        //dua cung(u,v) vao edge
        G->edges[G->m].x=x;
        G->edges[G->m].y=y;
        //tang so cung len 1
        G->m++;
    }
}
// Giả sử đồ thị vô hướng, có đa cung và có chứa khuyên. Để biểu diễn khuyên e = (x, x), ta gán A[x][e] = 2.

// Viết hàm add_edge(Graph* G, int e, int x, int y) để thêm cung e = (x, y) vào đồ thị G.

// void add_edge(Graph* G, int e, int x, int y)  {
// }
void add_edge(Graph* G,int e,int x,int y){
    if(x!=y){
    G->A[x][e]=1;
    G->A[y][e]=1;
    }
    else
    {
    G->A[x][e]=2;
    }
}
// Giả sử đồ thị vô hướng, không chứa khuyên.

// Viết hàm add_edge(Graph* G, int e, int x, int y) để thêm cung e = (x, y) vào đồ thị G.

// void add_edge(Graph* G, int e, int x, int y) {
// }
void add_edge(Graph* G,int e,int x,int y){
    G->A[x][e]=1;
    G->A[y][e]=1;
    }
// Giả sử đồ thị vô hướng, không chứa khuyên.

// Viết hàm int deg(Graph* G, int x) để tính bậc của đỉnh x.

// int deg(Graph* G, int x) {
// }
int deg(Graph* G, int x){
    int i, deg = 0;
    for(i = 0; i<= G->m;i++){
        if(G->A[x][i] == 1){
            deg++;
        }
    }
    return deg ;
}

// Giả sử đồ thị không chứa khuyên.

// Viết hàm List neighbors(Graph* G, int x) trả về danh sách các đỉnh kề của x.

// Chú ý: các đỉnh kề của x được sắp xếp theo thứ tự tăng dần và không trùng nhau. Ví dụ: nếu các đỉnh kề 
// của 1 là 4 và 2 thì danh sách trả về chứa: 2 và 4.
List neighbors(Graph* G, int x){
int i,j;
List L;
make_null(&L);
for(i=1; i<=G->n;i++){
if(i!=x){
for(j=1;j<=G->m;j++)
if((G->A[i][j]==1)&&(G->A[x][j]==1)){
push_back(&L,i);
break;
}
}
}
return L;
}
// Viết hàm int deg(Graph* G, int x) để tính bậc của đỉnh x.

// int deg(Graph* G, int x) {
// }
int deg(Graph* G, int x){
    int i, deg = 0;
    for(i = 0; i<= G->n;i++){
        if(G->A[x][i] == 1){
            deg++;
        }
    }
    return deg ;
}

// Giả sử đồ thị vô hướng, không chứa khuyên, nhưng có chứa đa cung

// Viết hàm int edgeCount(Graph* G) để đếm số cung của đồ thị G.

int edgeCount(Graph *G){
    int u,v, dem=0;
    for (u=1;u<=G->n;u++)
     for(v=1;v<=u;v++)
      if(G->A[u][v]!=0)
       dem+=G->A[u][v];
    return dem;
}
// Hãy viết chương trình đọc đồ thị từ tập tin và hiển thị ma trận kề của đồ thị này.

// Giả sử đồ thị được cho là đồ thị vô hướng đơn.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ tập tin dt1.txt với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

// - m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v mô tả cung (u, v).

// Đầu ra (Output):

// In ra Ma trận kề (0/1) của đồ thị
#include<stdio.h>
#define MAX_N 100
typedef struct{
int n; // Voi n la so dinh cua ma tran
int A[MAX_N][MAX_N];
}Graph;
void init_graph(Graph *G, int n){
int i,j;
G->n=n;
for ( i=1; i<= n; i++){ for ( j=1; j<= n; j++) G->A[i][j]=0;
}
}
void add_edge(Graph *G, int x, int y){
G->A[x][y]=1;
G->A[y][x]=1;
}
int main(){
int e,n,m,u,v,i,j;
Graph G;
freopen("dt1.txt","r",stdin);
scanf("%d%d",&n,&m);
init_graph(&G,n);
for(e=1;e<=n;e++){
scanf("%d%d",&u,&v);
add_edge(&G,u,v);
}
for (i=1;i<=G.n;i++){
for (j=1;j<=G.n;j++){
printf("%d ",G.A[i][j]);
}
printf("\n");
}
return 0;
}
/*
Cho một đồ thị vô hướng, không khuyên, không đa cung có n đỉnh và m cung.

Viết chương trình tính và in ra màn hình đỉnh có bậc lớn nhất và bậc tương ứng của nó. Nếu có nhiều đỉnh có bật bằng nhau thì in ra đỉnh có số thứ tự nhỏ nhất.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v mô tả cung (u, v)

Đầu ra (Output):

In ra màn hình đỉnh có bậc lớn nhất và bậc của nó.

Xem thêm ví dụ bên dưới.

Trong ví dụ đầu tiên ta có:

Bậc của đỉnh 1 là 1,
Bậc của đỉnh 2 là 3
Bậc của đỉnh 3 là 2
Bậc của đỉnh 4 là 2
Vậy đỉnh có bậc lớn nhất là đỉnh 2 và bậc của nó là 3. Vì thế ta in ra:

2 3

Chú ý:

Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v);
		add_edge(&G, u, v);
	}
*/

//code

#include <stdio.h>
#define maxv 50
#define idx 100
typedef struct{
    int matrix[maxv][maxv];
    int n;
}Graph;

void initGraph(Graph *g, int n){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}

void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

int degree(Graph g, int x){
    int count=0;
    for(int i=1;i<=g.n;i++){
        if(g.matrix[x][i]==1) count++;
    }
    return count;
}

int main(){
    Graph g;
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	initGraph(&g, n);
	for (int e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		addGraph(&g, u, v);
	}

	int max=0,index=0;
	for(int i=1;i<=g.n;i++){
	    int temp = degree(g,i);
	    if(temp > max){
	        max = temp;
	        index = i;
	    }
	}
    
	printf("%d %d\n",index,max);
    return 0;
}

/*
Cho một đồ thị vô hướng, không khuyên, không đa cung có n đỉnh và m cung.

Viết chương trình tính và in ra màn hình đỉnh có bậc mho nhất và bậc tương ứng của nó. Nếu có nhiều đỉnh có bật bằng nhau thì in ra đỉnh có số thứ tự nhỏ nhất.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v mô tả cung (u, v)

Đầu ra (Output):

In ra màn hình đỉnh có bậc lớn nhất và bậc của nó.

Xem thêm ví dụ bên dưới.

Trong ví dụ đầu tiên ta có:

Bậc của đỉnh 1 là 1,
Bậc của đỉnh 2 là 3
Bậc của đỉnh 3 là 2
Bậc của đỉnh 4 là 2
Vậy đỉnh có bậc lớn nhất là đỉnh 2 và bậc của nó là 3. Vì thế ta in ra:

2 3

Chú ý:

Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v);
		add_edge(&G, u, v);
	}
*/

//code

#include <stdio.h>
#define maxv 50
#define idx 100
typedef struct{
    int matrix[maxv][maxv];
    int n;
}Graph;

void initGraph(Graph *g, int n){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}

void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

int degree(Graph g, int x){
    int count=0;
    for(int i=1;i<=g.n;i++){
        if(g.matrix[x][i]==1) count++;
    }
    return count;
}

int main(){
    Graph g;
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	initGraph(&g, n);
	for (int e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		addGraph(&g, u, v);
	}

	int min=degree(g,1);
	int index=1;
	for(int i=1;i<=g.n;i++){
	    int temp = degree(g,i);
	    if(temp < min){
	        min = temp;
	        index = i;
	    }
	}
    
	printf("%d %d\n",index,min);
    return 0;
}

