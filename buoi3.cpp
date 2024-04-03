// Cho đồ thị có hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (0 < w <= 100).

// Viết chương trình tìm đường đi ngắn nhất từ đỉnh 1 đến n.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m.

// - m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

// Đầu ra (Output):

// In ra màn hình chiều dài của đường đi ngắn nhất từ 1 đến n. Nếu không có đường đi từ 1 đến n, in ra -1.
#include <stdio.h>
#include <stdbool.h>
#define maxv 50 
#define idx 100
#define  NO_EDGE 0 
#define INFINITY 999999999 
typedef int Vertices;

int n,m;//Biến toàn cục lưu số đỉnh và số cung

//Khai báo cấu trúc đồ thị
typedef struct{
	int matrix[maxv][maxv];
	Vertices n; //Đỉnh n
}Graph;

//Khởi tạo đồ thị(Tất cả cung trong đồ thị đều bằng 0/NO_EDGE)
void initGraph(Graph *g){
	g->n=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			g->matrix[i][j]=NO_EDGE;
		}
	}
}

//Thêm cung e =(x,y,t) vào đồ thị với t là trọng số
void addEdge(Graph *g, int x, int y, int t){
	g->matrix[x][y]=t;
}

//Hàm tìm giá trị nhỏ nhất
int min(int a, int b){
    return (a<b) ? a: b;
}

int mark[maxv]; //Mảng toàn cục để đánh dấu các đỉnh
int pi[maxv]; //Mảng toàn cục để lưu đường đi ngắn nhất tạm thời
int p[maxv]; //Mảng toàn cục để lưu đỉnh cha của một đỉnh

//Thuật toán tìm đường đi ngắn nhất
void Dijkstra(Graph *g, int x){

	int i,j,k;
	for(i=1;i<=n;i++){
		pi[i] = INFINITY; //Khởi tạo đường đi ngắn nhất tạm thời của tất cả các đỉnh bằng vô cực
		mark[i]=0; //Khởi tạo chưa có đỉnh nào được đánh dấu( Đỉnh chưa đánh dâu có chỉ số bằng 0)
	}

	pi[x] = 0;//Xét đỉnh đầu tiên nên ta thay đổi pi của đỉnh đầu tiên từ vô cực sang 0 để bắt đầu thuật toán
	p[x] = -1;//Đỉnh cha của đỉnh đầu tiên gán bằng -1 tức đỉnh 1 không có đỉnh cha

	//Tìm đỉnh chưa đánh dấu(mark[x]==0) và có pi[x] nhỏ nhất để xét
	for(k=1;k<=n;k++){
		int min_pi = INFINITY;
		for(j=1;j<=n;j++){
			if(mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				i=j;
			}
		}

		mark[i]=1;//Sau khi đã tìm được đỉnh có pi[index] nhỏ nhất thì đánh dấu đỉnh đó đã được duyệt
		
		for(j=1;j<=n;j++){
			int v = g->matrix[i][j];
			//Nếu v là đỉnh kề của đỉnh x (tức đường đi từ x tới v có trọng số khác 0/NO_EDGE) và mark[v] chưa được duyệt
			if( v !=  NO_EDGE  && mark[j]==0){ 
			    int pi_before = pi[j];//pi_before để lưu đường đi ngắn nhất tạm thời trước đó
				int pi_after = min(pi[j],pi[i]) + g->matrix[i][j]; //pi_after là đường đi ngắn nhất tạm thời vừa mới tính được
				//Nếu đường đi ngắn nhất tạm thời sau < đường đi ngắn nhất tạm thời trước đó
				if(pi_after < pi_before ){
				    pi[j]=pi_after;//Cập nhật lại đường đi ngắn nhất tạm thời = đường đi ngắn nhất tạm thời vừa tìm được
				    p[j]=i;//Sau khi cập nhật xong thì lưu đỉnh cha của đỉnh vừa cập nhật 
				}    
			}
		}
	}
}
int main(){
	Graph g;
    	scanf("%d%d",&n,&m);
	initGraph(&g);
	int u,v,t;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&t);
		addEdge(&g,u,v,t);
	}
	Dijkstra(&g,1);
	if(pi[n]==INFINITY) printf("-1");
	else printf("%d",pi[n]);
	return 0;
}
// Cho đồ thị vô hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (0 < w <= 100).

// Viết chương trình tìm đường đi ngắn nhất từ đỉnh 1 đến n.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m.

// - m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

// Đầu ra (Output):

// In ra màn hình chiều dài của đường đi ngắn nhất từ 1 đến n. Nếu không có đường đi từ 1 đến n, in ra -1.
#include <stdio.h>
#include <stdbool.h>
#define maxv 50 
#define idx 100
#define  NO_EDGE 0 
#define INFINITY 999999999 
typedef int Vertices;

int n,m;//Biến toàn cục lưu số đỉnh và số cung

//Khai báo cấu trúc đồ thị
typedef struct{
	int matrix[maxv][maxv];
	Vertices n; //Đỉnh n
}Graph;

//Khởi tạo đồ thị(Tất cả cung trong đồ thị đều bằng 0/NO_EDGE)
void initGraph(Graph *g){
	g->n=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			g->matrix[i][j]=NO_EDGE;
		}
	}
}

//Thêm cung e =(x,y,t) vào đồ thị với t là trọng số
void addEdge(Graph *g, int x, int y, int t){
	g->matrix[x][y]=t;
}

//Hàm tìm giá trị nhỏ nhất
int min(int a, int b){
    return (a<b) ? a: b;
}

int mark[maxv]; //Mảng toàn cục để đánh dấu các đỉnh
int pi[maxv]; //Mảng toàn cục để lưu đường đi ngắn nhất tạm thời
int p[maxv]; //Mảng toàn cục để lưu đỉnh cha của một đỉnh

//Thuật toán tìm đường đi ngắn nhất
void Dijkstra(Graph *g, int x){

	int i,j,k;
	for(i=1;i<=n;i++){
		pi[i] = INFINITY; //Khởi tạo đường đi ngắn nhất tạm thời của tất cả các đỉnh bằng vô cực
		mark[i]=0; //Khởi tạo chưa có đỉnh nào được đánh dấu( Đỉnh chưa đánh dâu có chỉ số bằng 0)
	}

	pi[x] = 0;//Xét đỉnh đầu tiên nên ta thay đổi pi của đỉnh đầu tiên từ vô cực sang 0 để bắt đầu thuật toán
	p[x] = -1;//Đỉnh cha của đỉnh đầu tiên gán bằng -1 tức đỉnh 1 không có đỉnh cha

	//Tìm đỉnh chưa đánh dấu(mark[x]==0) và có pi[x] nhỏ nhất để xét
	for(k=1;k<=n;k++){
		int min_pi = INFINITY;
		for(j=1;j<=n;j++){
			if(mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				i=j;
			}
		}

		mark[i]=1;//Sau khi đã tìm được đỉnh có pi[index] nhỏ nhất thì đánh dấu đỉnh đó đã được duyệt
		
		for(j=1;j<=n;j++){
			int v = g->matrix[i][j];
			//Nếu v là đỉnh kề của đỉnh x (tức đường đi từ x tới v có trọng số khác 0/NO_EDGE) và mark[v] chưa được duyệt
			if( v !=  NO_EDGE  && mark[j]==0){ 
			    int pi_before = pi[j];//pi_before để lưu đường đi ngắn nhất tạm thời trước đó
				int pi_after = min(pi[j],pi[i]) + g->matrix[i][j]; //pi_after là đường đi ngắn nhất tạm thời vừa mới tính được
				//Nếu đường đi ngắn nhất tạm thời sau < đường đi ngắn nhất tạm thời trước đó
				if(pi_after < pi_before ){
				    pi[j]=pi_after;//Cập nhật lại đường đi ngắn nhất tạm thời = đường đi ngắn nhất tạm thời vừa tìm được
				    p[j]=i;//Sau khi cập nhật xong thì lưu đỉnh cha của đỉnh vừa cập nhật 
				}    
			}
		}
	}
}
int main(){
	Graph g;
    	scanf("%d%d",&n,&m);
	initGraph(&g);
	int u,v,t;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&t);
		addEdge(&g,u,v,t);
	}
	Dijkstra(&g,1);
	if(pi[n]==INFINITY) printf("-1");
	else printf("%d",pi[n]);
	return 0;
}
// "Ngưu Lang là vị thần chăn trâu của Ngọc Hoàng Thượng đế, vì say mê một tiên nữ phụ trách 
// việc dệt vải tên là Chức Nữ nên bỏ bễ việc chăn trâu, để 
// trâu đi nghênh ngang vào điện Ngọc Hư. Chức Nữ cũng vì mê tiếng tiêu của
// Ngưu Lang nên trễ nải việc dệt vải. Ngọc Hoàng giận dữ, bắt cả hai phải ở
//  cách xa nhau, người đầu sông Ngân, kẻ cuối sông.
#include <stdio.h>

#define NO_EDGE -1

typedef struct {
	int n, m;
	int W[100][100];
}Graph;

void init_graph(Graph* pG, int n) {
	pG->n = n;
	pG->m = 0;
	for (int u = 1; u <= n; u++) {
		for (int v = 1; v <= n; v++) {
			pG->W[u][v] = NO_EDGE;
		}
	}
}

void add_edge(Graph* pG, int u, int v, int w) {
	pG->W[u][v] = w;
	pG->W[v][u] = w;
	pG->m++;
}

#define oo 999999
int mark[100], p[100], pi[100];

void Dijkstra(Graph* pG, int s) {
	for (int u = 1; u <= pG->n; u++) {
		mark[u] = 0;
		pi[u] = oo;
	}
	pi[s] = 0;
	p[s] = -1;
	int u;
	for (int i = 1; i < pG->n; i++) {
		int minpi = oo;
		for (int v = 1; v <= pG->n; v++) {
			if (!mark[v] && pi[v] < minpi) {
				minpi = pi[v];
				u = v;
			}
		}
		mark[u] = 1;
		for (int v = 1; v <= pG->n; v++) {
			if (!mark[v] && pG->W[u][v] != NO_EDGE) {
				if (pi[u] + pG->W[u][v] < pi[v]) {
					pi[v] = pi[u] + pG->W[u][v];
					p[v] = u;
				}
			}
		}
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Graph G;
	init_graph(&G, n);
	for (int e = 0; e < m; e++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	Dijkstra(&G, 1);
	
	printf("%d", pi[n]);
	return 0;
}
// Đất nước CyberGraph có n thành phố và m con đường. Mỗi con đường nối 2 thành phố lại với nhau. tất cả các con đường đều là đường 2 chiều, mỗi con đường có một chiều dài nào đó. giữa hai thành phố có nhiều nhất là 1 con đường.

// Tổng thổng của nước này dự định sẽ đi từ thành phố s đến thành phố t. Đương nhiên, ông ta sẽ chọn hành trình có tổng chiều dài các con đường đi qua ngắn nhất.

// Hãy giúp Ngài tổng thổng tìm hành trình ngắn nhất đi từ s đến t.
#include <stdio.h>

#define NO_EDGE -1

typedef struct {
	int n, m;
	int W[100][100];
}Graph;

void init_graph(Graph* pG, int n) {
	pG->n = n;
	pG->m = 0;
	for (int u = 1; u <= n; u++) {
		for (int v = 1; v <= n; v++) {
			pG->W[u][v] = NO_EDGE;
		}
	}
}

void add_edge(Graph* pG, int u, int v, int w) {
	pG->W[u][v] = w;
	pG->W[v][u] = w;
	pG->m++;
}

#define oo 999999
int mark[100], p[100], pi[100];

void Dijkstra(Graph* pG, int s) {
	for (int u = 1; u <= pG->n; u++) {
		mark[u] = 0;
		pi[u] = oo;
	}
	pi[s] = 0;
	p[s] = -1;
	int u;
	for (int i = 1; i < pG->n; i++) {
		int minpi = oo;
		for (int v = 1; v <= pG->n; v++) {
			if (!mark[v] && pi[v] < minpi) {
				minpi = pi[v];
				u = v;
			}
		}
		mark[u] = 1;
		for (int v = 1; v <= pG->n; v++) {
			if (!mark[v] && pG->W[u][v] != NO_EDGE) {
				if (pi[u] + pG->W[u][v] < pi[v]) {
					pi[v] = pi[u] + pG->W[u][v];
					p[v] = u;
				}
			}
		}
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Graph G;
	init_graph(&G, n);
	for (int e = 0; e < m; e++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	int s, t;
	scanf("%d %d", &s, &t);
	Dijkstra(&G, s);
	printf("%d", pi[t]);
	return 0;
}
// Mê cung số (number maze)

// Cho một mê cung số được biểu diễn bằng một mảng 2 chiều chứa các con số từ 0 đến 9 
#include<stdio.h>
#define maxv 100
#define INFINITY 999999
#define NO_EDGE 0
typedef int Vertices;

//Khai báo cấu trúc đồ thị
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

//Khởi tạo 
void initGraph(Graph *g, int n){
    int i,j;
    g->n=n;
    for(i=1;i<=g->n;i++)
        for(j=1;j<=g->n;j++)
            g->matrix[i][j] = 0;
}

//Hàm tìm giá trị nhỏ nhất
int min(int a, int b){
    return (a<b) ? a: b;
} 

int mark[maxv]; //Mảng toàn cục để đánh dấu các đỉnh
int pi[maxv]; //Mảng toàn cục để lưu đường đi ngắn nhất tạm thời
int p[maxv]; //Mảng toàn cục để lưu đỉnh cha của một đỉnh
int w[maxv]; //Mảng w để lưu tất cả trọng số của các ô bắt đầu từ ô thứ 1 đến n

//Thuật toán tìm đường đi ngắn nhất
void Dijkstra(Graph *g, int x){

    int i,j,k;
    for(i=1;i<=g->n;i++){
        pi[i] = INFINITY; //Khởi tạo đường đi ngắn nhất tạm thời của tất cả các đỉnh bằng vô cực
        mark[i]=0; //Khởi tạo chưa có đỉnh nào được đánh dấu( Đỉnh chưa đánh dâu có chỉ số bằng 0)
    }

    pi[x] = w[x];
    p[x] = -1;//Đỉnh cha của đỉnh đầu tiên gán bằng -1 tức đỉnh 1 không có đỉnh cha

    //Tìm đỉnh chưa đánh dấu(mark[x]==0) và có pi[x] nhỏ nhất để xét
    for(k=1;k<=g->n;k++){
        int min_pi = INFINITY;
        for(j=1;j<=g->n;j++){
            if(mark[j] == 0 && pi[j] < min_pi){
                min_pi = pi[j];
                i=j;
            }
        }

        mark[i]=1;//Sau khi đã tìm được đỉnh có pi[index] nhỏ nhất thì đánh dấu đỉnh đó đã được duyệt
        
        for(j=1;j<=g->n;j++){
            int v = g->matrix[i][j];
            //Nếu v là đỉnh kề của đỉnh x (tức đường đi từ x tới v có trọng số khác 0/NO_EDGE) và mark[v] chưa được duyệt
            if( v !=  NO_EDGE  && mark[j]==0){ 
                int pi_before = pi[j];//pi_before để lưu đường đi ngắn nhất tạm thời trước đó
                int pi_after = min(pi[j],pi[i]) + g->matrix[i][j]; //pi_after là đường đi ngắn nhất tạm thời vừa mới tính được
                //Nếu đường đi ngắn nhất tạm thời sau < đường đi ngắn nhất tạm thời trước đó
                if(pi_after < pi_before ){
                    pi[j]=pi_after;//Cập nhật lại đường đi ngắn nhất tạm thời = đường đi ngắn nhất tạm thời vừa tìm được
                    p[j]=i;//Sau khi cập nhật xong thì lưu đỉnh cha của đỉnh vừa cập nhật 
                }
                /*Nếu câu điều kiện phía trên không thực hiện thì đường đi ngắn nhất tạm thời sau không 
                lớn hơn đường đi ngắn nhất tạm thời trước đó thì không cập nhật mà chỉ lưu đỉnh cha của đỉnh đó*/
                p[j]=i;    
            }
        }
    }
}
int main(){
    Graph g;
    int m,n,u,v;
    int i_ke,j_ke;

    scanf("%d %d",&m,&n); // Nhap M : so hang , N : so cot

    initGraph(&g,m*n); //Khởi tạo tổ hợp gồm n*m hàng và n*m cột

    //Nhập giá trị cho từng ô tức trọng số của đồ thị rồi lưu vào mảng w 
    for(int i=1;i<=(n*m);i++){
        scanf("%d",&u);
        w[i]=u;
    }

    //Thuật toán tìm đỉnh kề của một đỉnh
    for(int i=0;i<m;i++){
         for(int j=0;j<n;j++){
            //Mỗi ô trong ma trận có thể nhiều nhất 4 ô khác nếu 
            int di[] = {-1,1,0,0};
            int dj[] = {0,0,-1,1};
            //Duyệt qua các ô kề của o(i,j)
            for(int k=0;k<4;k++){
                i_ke = i+di[k];
                j_ke = j + dj[k];
                //Kiểm tra o(i_ke,j_ke) có nằm trong mê cung không tức là nằm trong phạm vi (0,0) và (M-1, N-1).
                if((i_ke>=0) && (i_ke<m) && (j_ke>=0) && (j_ke<n)){
                    v = i_ke * n + j_ke + 1;
                    u = i * n + j + 1;
                    g.matrix[u][v] = w[v]; //Kết quả là tìm được các đỉnh kề trong mê cung và gán trọng số
                }
            }
        }
    }

    Dijkstra(&g,1);

    printf("%d ",pi[g.n]);
    
    return 0;
}
// Cho đồ thị đơn, vô hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (0 < w <= 100).

// Viết chương trình tìm đếm xem có bao nhiêu đường đi ngắn nhất từ đỉnh 1 đến n.
#include <stdio.h>

#define NO_EDGE -1

typedef struct {
	int n, m;
	int W[100][100];
}Graph;

void init_graph(Graph* pG, int n) {
	pG->n = n;
	pG->m = 0;
	for (int u = 1; u <= n; u++)
		for (int v = 1; v <= n; v++)
			pG->W[u][v] = NO_EDGE;
}

void add_edge(Graph* pG, int u, int v, int w) {
	pG->W[u][v] = w;
	pG->W[v][u] = w;
	pG->m++;
}

#define oo 999999

int mark[100];
int pi[100];
int p[100];
int cnt[100];
void MooreDijkstra(Graph* pG, int s) {
	for (int u = 1; u <= pG->n; u++) {
		pi[u] = oo;
		mark[u] = 0;
		cnt[u] = 1;
	}

	pi[s] = 0;
	p[s] = -1;
	int u, v;
	for (int i = 1; i < pG->n; i++) {
		int min_pi = oo;
		for (int j = 1; j <= pG->n; j++) {
			if (mark[j] == 0 && pi[j] < min_pi) {
				min_pi = pi[j];
				u = j;
			}
		}
		mark[u] = 1;

		for (v = 1; v <= pG->n; v++) {
			if (pG->W[u][v] != NO_EDGE && mark[v] == 0) {
				if (pi[u] + pG->W[u][v] < pi[v]) {
					pi[v] = pi[u] + pG->W[u][v];
					p[v] = u;
					cnt[v] = cnt[u];
				}
				else if (pi[u] + pG->W[u][v] == pi[v])
					cnt[v] += cnt[u];
			}
		}
	}
}

int main() {
	int n, m;
	Graph G;
	scanf("%d %d", &n, &m);
	init_graph(&G, n);
	for (int e = 1; e <= m; e++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

	MooreDijkstra(&G, 1);
	if (pi[n] < oo)
		printf("%d %d", pi[n], cnt[n]);
	else
		printf("-1 0");
	return 0;
}
