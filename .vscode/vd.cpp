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
    int u,v,t,m,n;
    freopen("dothi.txt", "r", stdin);//Khi nộp bài nhớ xóa dòng này
    scanf("%d%d",&n,&m);
	initGraph(&g);
	
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&t);
		addEdge(&g,u,v,t);
	}
	Dijkstra(&g,1);
	if(pi[n]==INFINITY) printf("-1");
	else printf("%d",pi[n]);
	return 0;
}