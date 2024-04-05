// Cho một đồ thị vô hướng đơn. Hãy in ra thứ tự của các đỉnh khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1.

// Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

// Quy ước:

// Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef int ElementType;

typedef struct Node {
    ElementType Data;
    struct Node *Next;
} Node;

typedef struct {
    Node *Front, *Rear;
} Queue;

void make_null_queue (Queue *pQ){
    Node *Header = (Node*)malloc(sizeof(Node));
    Header->Next = NULL;
    pQ->Front = Header;
    pQ->Rear = Header;
}

void enqueue (Queue *pQ, int x){
    pQ->Rear->Next =  (Node*)malloc (sizeof (Node));
    pQ->Rear = pQ->Rear->Next;
    pQ->Rear->Data = x;
    pQ->Rear->Next = NULL;
}

ElementType dequeue (Queue *pQ){
    Node *Temp;
    Temp = pQ->Front;
    pQ->Front = pQ->Front->Next;
    free(Temp);
    return pQ->Front->Data;
}

typedef struct{
	int n, m;
	int A[MAX_N][MAX_N];
} Graph;

void init_graph (Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; i <= n; i++)
			pG->A[i][j] = 0;
}

void add_edge (Graph *pG, int u, int v) {
	pG->A[u][v] = 1;
    pG->A[v][u] = 1; // Undirected Graph
	pG->m++;
}

void read_graph (Graph *pG){
    int n, m;
    scanf ("%d %d", &n, &m);
    init_graph (pG, n);
    for (int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(pG, u, v);
    }
}

int mark[MAX_N];

void bfs(Graph *pG, int s){
    Queue Q;
    make_null_queue(&Q);
    enqueue(&Q, s);
    while (Q.Front != Q.Rear){
        int u = dequeue(&Q);
        if (!mark[u]){
            mark[u] = 1;
            printf("%d\n", u);
            for (int v = 1; v <= pG->n; v++)
                if (pG->A[u][v])
                    enqueue(&Q, v);
        }
    }
}

int main (){
    Graph G;    
    read_graph (&G);
    for(int i = 1; i <= G.n; i++)
        mark[i] = 0;
    for(int i = 1; i <= G.n; i++)
        bfs(&G, i);
}

/*
Cho một đồ thị vô hướng đơn. Hãy in ra thứ tự của các đỉnh khi duyệt đồ thị theo chiều sâu (sử dụng NGĂN XẾP) bắt đầu từ đỉnh 1.

Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

Quy ước:

Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần.


Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng mô tả cung (u, v).

Đầu ra (Output):

In ra các đỉnh theo thứ tự duyệt, mỗi đỉnh trên 1 dòng.

Xem thêm các ví dụ bên dưới.



Hướng dẫn đọc dữ liệu và chạy thử chương trình
Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
*/

//CODE

/// Duyệt đồ thị theo chiều sâu - Stack
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m;//Biến toàn cục lưu n đỉnh và m cung

// Khai báo cấu trúc đồ thị
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

// Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;

// Khai báo cấu trúc ngắn xếp - STACK
typedef struct{
    int data[idx];
    int size;
}Stack;

/*Các hàm của ngăn xếp*/

// Làm rỗng ngăn xếp
void makenullStack(Stack *s){
    s->size=0;
}

// Kiểm tra ngăn xếp có rỗng hay không
bool emptyStack(Stack *s){
    return s->size==0;
}

// Thêm 1 phần tử vào ngăn xếp
void pushStack(Stack *s, int element){
    s->data[s->size]=element;
    s->size++;
}

//Truy cập phần tử trong ngăn xếp
int getStack(Stack *s){
    return s->data[s->size-1];
}

// Xóa vị trí phần tử trong ngăn xếp đi(Vị trị này thực tế vẫn còn nhưng chúng ta không truy cập đến nữa)
void delSize(Stack *s){
    s->size--;
}

/*Các hàm trên danh sách*/

// Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

// Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

// Thêm 1 phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}

// Truy cập đến phần tử có vị trí index trong danh sách
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm trên đồ thị*/

// Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}

// Thêm cung e = (x,y) vào đồ thị
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

// Kiểm tra 2 đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}

// Tìm tất cả đỉnh láng giềng(đỉnh kề) của đỉnh x
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(adjacent(g,x,i)){
            pushList(&L,i);
        }
    }
    return L;
}
int mark[maxv];//Mảng toàn cục mark để đánh dấu 1 đỉnh đã được duyệt hay chưa

// Giải thuật duyệt sâu sử dụng ngăn xếp - DFS - STACK
List DFS_Stack(Graph *g, int x){
    List rs;//Danh sách lưu các đỉnh đã được duyệt
    makenullList(&rs);
    Stack s;
    makenullStack(&s);
    pushStack(&s,x);
    while(!emptyStack(&s)){ //Lập trong khi ngăn xếp chưa rỗng
        int u = getStack(&s);
        delSize(&s);
        if(mark[u]==1) continue; //Nếu đỉnh u đã được duyệt thì bỏ qua các câu lệnh phía sau
        pushList(&rs,u); //Nếu u chưa duyệt thay vì in ra thì chúng ta sẽ đưa vào danh sách rs(result) -> danh sách kết quả
        mark[u]=1; //Đánh dấu u đã duyệt
        List L = neighbors(g,u); //Tìm đỉnh láng giềng của u đưa vào danh sách L
        for(int j=1;j<=L.size;j++){
            int v = getList(&L,j); //Lấy đỉnh láng giềng u trong danh sách L ra -> Lấy đỉnh v
            if(mark[v]==0){ //Nếu v chưa được duyệt
                pushStack(&s,v); //Đưa vào ngăp xếp duyệt v
            }
        }
    }
    return rs;
}
int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    // Khởi tạo toàn bộ phần tử trong mảng mark bằng 0 vì chưa có đỉnh nào được duyệt
    for(int i=1;i<=n;i++) mark[i]=0;
     
    for(int i=1;i<=n;i++){
        if(mark[i]==0){ //Nếu đỉnh chưa được duyệt
            List L = DFS_Stack(&g,i); //Gọi hàm và duyệt 
            for(int j=1;j<=L.size;j++){
                int v = getList(&L,j);
                printf("%d\n",v); //in
                mark[v]=1; //Đánh dấu đã duyệt
            }
        }
    }
    return 0;
}
// Cho một đồ thị vô hướng đơn. Hãy in ra thứ tự của các đỉnh khi duyệt đồ thị theo chiều sâu (sử dụng ĐỆ QUY) bắt đầu từ đỉnh 1.

// Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

// Quy ước:

// Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần.

#include <stdio.h>
#define MAX 100

typedef struct {
	int u, v;
}Edge;

typedef struct {
	int n, m;
	Edge edges[MAX];
}Graph;

void init_graph(Graph* pG, int n) {
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph* pG, int u, int v) {
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->m++;
}

int adjacent(Graph* pG, int u, int v) {
	for (int e = 0; e < pG->m; e++)
		if ((pG->edges[e].u == u && pG->edges[e].v == v)
			|| (pG->edges[e].u == v && pG->edges[e].v == u))
			return 1;
	return 0;
}

int mark[MAX];

void DFS(Graph* pG, int u) {
	mark[u] = 1;
	printf("%d\n", u);
	for(int v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v) && !mark[v] ) {
				DFS(pG, v);
		}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Graph G;
	init_graph(&G, n);
	for (int e = 1; e <= m; e++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}

	for (int u = 1; u <= G.n; u++)
		mark[u] = 0;
	for (int u = 1; u <= G.n; u++)
		if (!mark[u])
			DFS(&G, u);
	return 0;
}
/*
Cho một đồ thị vô hướng đơn. Hãy dựng (các) cây DUYỆT ĐỒ THỊ khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1.

Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

Quy ước:

Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần

Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng mô tả cung (u, v).

Đầu ra (Output):

In ra cây duyệt đồ thị theo định dạng:

1 <đỉnh cha của 1>
2 <đỉnh cha của 2>
....
i <đỉnh cha của i>
...
n <đỉnh cha của n>

Quy ước: Nếu 1 đỉnh không có đỉnh cha (nó là đỉnh gốc của cây) thì đỉnh cha của nó là 0.

Xem thêm các ví dụ bên dưới.



Gợi ý:

Sử dụng mảng parent[u] để lưu đỉnh cha của đỉnh u.
Trong quá trình duyệt, thay vì in các đỉnh ra màn hình, ghi nhận lại đỉnh cha của các đỉnh.
Khi duyệt xong lần lượt in ra u và parent[u] (u chạy từ 1 đến n).


Hướng dẫn đọc dữ liệu và chạy thử chương trình
Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

*/

//CODE

//Duyệt và dựng cây đồ thị theo chiều rộng - QUEUE

#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m;//Biến toàn cục lưu n đỉnh và m cung

// Khai báo cấu trúc đồ thị - GRAPH
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;// Đỉnh n
}Graph;

//Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;

// Khai báo cấu trúc hàng đợi - QUEUE
typedef struct{
    int front;
    int rear;
    int data[maxv];
}Queue;

/*Các hàm của hàng đợi*/

// Làm rỗng hàng đợi
void makenullQueue(Queue *q){
    q->front=0;
    q->rear=-1;
}

// Kiểm tra hàng đợi có rỗng hay không
bool emptyQueue(Queue *q){
    return q->front > q->rear;
}

// Thêm 1 phần tử vào hàng đợi
void pushQueue(Queue *q, int element){
    q->rear++;
    q->data[q->rear]=element;
}

// Truy cập phần tử trong hàng đợi
int getQueue(Queue *q){
    return q->data[q->front];
}

// Xóa vị trí phần tử trong hàng đợi đi(Vị trị này thực tế vẫn còn nhưng chúng ta không truy cập đến nữa)
void plusFront(Queue *q){
    q->front++;
}
/*Các hàm trên danh sách*/

// Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

//Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

// Thêm phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}

// Truy cập phần tử trong danh sách bắt đầu từ vị trí thứ 1(Mảng bắt đầu bằng 0 nên index phải trừ đi 1)
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm trên đồ thị*/

// Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}

// Thêm cung e = (x,y) vào đồ thị
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

// Kiểm tra 2 đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}

// Tìm tất cả đỉnh láng giềng(đỉnh kề) của đỉnh x
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(adjacent(g,x,i)){
            pushList(&L,i);
        }
    }
    return L;
}

int mark[maxv];//Mảng toàn cục mark để đánh dấu 1 đỉnh đã được duyệt hay chưa
int parent[maxv]; //Mảng toàn cục parent để lưu đỉnh cha của toàn bộ đỉnh trong đồ thị

// Giải thuật duyệt rộng sử dụng hàng đợi - BFS - QUEUE
List BFS(Graph *g, int x){
    List rs; //Danh sách lưu các đỉnh đã được duyệt
    makenullList(&rs);
    Queue q; 
    makenullQueue(&q);
    pushQueue(&q,x);
    parent[x]=0; //Nếu đỉnh đang xét là đỉnh gốc thì đỉnh cha của đỉnh gốc là 0
    while(!emptyQueue(&q)){ //Lập trong khi hàng đợi chưa rỗng
        int u = getQueue(&q);
        plusFront(&q);
        if(mark[u]==1) continue; //Nếu đỉnh u đã được duyệt thì bỏ qua các câu lệnh phía sau
        pushList(&rs,u); //Nếu u chưa duyệt thay vì in ra thì chúng ta sẽ đưa vào danh sách rs(result) -> danh sách kết quả
        mark[u]=1; //Đánh dấu u đã duyệt 
        List L = neighbors(g,u); //Tìm đỉnh láng giềng của u đưa vào danh sách L
        for(int j=1;j<=L.size;j++){
            int v = getList(&L,j); //Lấy đỉnh láng giềng u trong danh sách L ra -> Lấy đỉnh v
            if(mark[v]==0){ //Nếu v chưa được duyệt
                pushQueue(&q,v); //Đưa vào hàng đợi duyệt v
                if(parent[v]==-1){ //Nếu đỉnh v chưa có đỉnh cha 
                    parent[v]=u; //Thì đỉnh cha của v là đỉnh u
                }
            }
        }
    }
    return rs;
}
int main(){ 
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int e=1;e<=m;e++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    // Khởi tạo toàn bộ phần tử trong mảng mark bằng 0 vì chưa có đỉnh nào được duyệt
    for(int i=1;i<=n;i++){
        mark[i]=0;
        parent[i]=-1;
    } 
    
    for(int i=1;i<=n;i++){
        if(mark[i]==0){ //Nếu đỉnh chưa được duyệt
            List L = BFS(&g,i); //Gọi hàm và duyệt 
            for(int j=1;j<=L.size;j++){
                int v = getList(&L,j);
                // printf("%d\n",v); 
                //Đề yêu cầu chỉ in đỉnh cha của các đỉnh ra thôi nên không cần in thứ tự duyệt của đồ thị
                mark[v]=1;//Đánh dấu đã duyệt
            }
        }
    }
    //In các đỉnh cha của các đỉnh trong đồ thị
    for(int i=1;i<=n;i++)
        printf("%d %d\n",i,parent[i]); //Đỉnh i có đỉnh cha là parent[i]
    return 0;
}
/*
Cho một đồ thị vô hướng đơn. Hãy dựng (các) cây DUYỆT ĐỒ THỊ khi duyệt đồ thị theo chiều sâu (dùng ĐỆ QUY) bắt đầu từ đỉnh 1.

Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

Quy ước:

Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần.


Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng mô tả cung (u, v).

Đầu ra (Output):

In ra cây duyệt đồ thị theo định dạng:

1 <đỉnh cha của 1>
2 <đỉnh cha của 2>
....
i <đỉnh cha của i>
...
n <đỉnh cha của n>

Quy ước: Nếu 1 đỉnh không có đỉnh cha (nó là đỉnh gốc của cây) thì đỉnh cha của nó là 0.

Xem thêm các ví dụ bên dưới.



Gợi ý:

Sử dụng mảng parent[u] để lưu đỉnh cha của đỉnh u.
Trong quá trình duyệt, thay vì in các đỉnh ra màn hình, ghi nhận lại đỉnh cha của các đỉnh.
Thêm 1 tham số p (đỉnh cha của đỉnh u) cho hàm visit(). Khi gọi đệ quy duyệt v ta truyền u như là đỉnh cha của v.
void visit(Graph* G, int u, int p) {
    ...
    for (các đỉnh kề v của u)
        visit(G, v, u);
}
Khi duyệt xong lần lượt in ra u và parent[u] (u chạy từ 1 đến n).


Hướng dẫn đọc dữ liệu và chạy thử chương trình
Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
*/

//CODE

//Duyệt và dựng cây đồ thị theo chiều sâu - Đệ qui - Recursion
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m; //Biến toàn cục lưu n đỉnh và m cung

//Khai báo cấu trúc đồ thị
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

// Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;

/*Các hàm trên danh sách*/

//Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

// Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

// Thêm 1 phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}

// Truy cập phần tử trong danh sách bắt đâu từ vị trí thứ 1 (Mảng bắt đầu bằng 0 nên index phải trừ đi 1)
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm trên đồ thị*/

// Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}

// Thêm cung e = (x,y) vào đồ thị
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

// Kiểm tra 2 đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}

// Tìm đỉnh láng giềng(đỉnh kề) của một đỉnh
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(adjacent(g,x,i)){
            pushList(&L,i);
        }
    }
    return L;
}

int mark[maxv];//Mảng toàn cục mark để đánh dấu 1 đỉnh đã được duyệt hay chưa
int parent[maxv];//Mảng parent lưu đỉnh cha của tất cả các đỉnh trong đồ thị
// Giải thuật duyệt đồ thị theo chiều sâu - Sử dụng đệ qui
void DFS_Recursion(Graph *g, int x, int p){
    if(mark[x]==1) return; //Nếu đỉnh đã được duyệt kết thúc và không trả về gì
    mark[x]=1; //Nếu chưa duyệt thì đánh dấu đã duyệt
    //printf("%d\n",x); Đề bài yêu cầu chỉ cần in ra cha nên không cần phải in thứ tự duyệt
    parent[x]=p; //Đỉnh đầu tiên được xét là đỉnh 1 nên cha của đỉnh 1 theo quy ước lúc này = p = 0, các lần lặp sau p có thể sẽ thay đổi
    List L = neighbors(g,x); //Tìm đỉnh láng giềng của đỉnh đang xét
    for(int j=1;j<=L.size;j++){
        int v = getList(&L,j); //Lấy đỉnh v kề với đỉnh đang xét ra 
        DFS_Recursion(g,v,x); //Tiếp tục gọi đệ qui đỉnh cha của đỉnh đang đang xét là đỉnh trước đó(Lúc này p đã không còn là 0 mà đã là x)
    }
}
int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    
    for(int i=1;i<=n;i++){
        mark[i]=0; //Khởi tạo tất cả các đỉnh điều chưa được duyệt
        parent[i]=-1; //Khởi tạo tất cả các đỉnh có đỉnh cha bằng null(-1)
    }
        
    for(int i=1;i<=n;i++)
         DFS_Recursion(&g,i,0); //Gọi hàm để duyệt và đỉnh cha của đỉnh đầu tiền là 0
    
    for(int i=1;i<=n;i++)
        printf("%d %d\n",i,parent[i]); //In ra các đỉnh và đỉnh cha của các đỉnh đó
    return 0;
}
/*

Có n hòn đảo và m cây cầu. Mỗi cây cầu bắt qua 2 hòn đảo. Một hôm chúa đảo tự hỏi là với các cây cầu hiện tại thì đứng ở một hòn đảo bất kỳ có thể nào đi đến được tất cả các hòn đảo khác hay không.

Hãy giúp chúa đảo viết chương trình kiểm tra.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đảo và số cây cầu.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng có 1 cây cầu bắt qua hai hòn đảo u và v.

Đầu ra (Output):

Nếu có thể đi được in ra màn hình YES, ngược lại in ra NO.

Xem thêm ví dụ bên dưới.
For example:

Input	Result

4 3      YES
1 2
2 3
3 4

4 2     NO
3 4
1 2

*/

//CODE
//Bài toán thực tế - Đồ thị liên thông - Qua đảo
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m; //Biến toàn cục lưu n đỉnh và m cung

//Khai báo cấu trúc đồ thị
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

// Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;

/*Các hàm trên danh sách*/

//Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

// Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

// Thêm 1 phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}

// Truy cập phần tử trong danh sách bắt đâu từ vị trí thứ 1 (Mảng bắt đầu bằng 0 nên index phải trừ đi 1)
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm trên đồ thị*/

// Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}

// Thêm cung e = (x,y) vào đồ thị
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

// Kiểm tra 2 đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}

// Tìm đỉnh láng giềng(đỉnh kề) của một đỉnh
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(adjacent(g,x,i)){
            pushList(&L,i);
        }
    }
    return L;
}

int mark[maxv];//Mảng toàn cục mark để đánh dấu 1 đỉnh đã được duyệt hay chưa
int count=0;//Biến count toàn cục để kiểm tra -> Khi một đỉnh được duyệt count sẽ tăng lên 1 -> Nếu kết thúc giải thuật mà count = đỉnh n -> Liên thông

// Giải thuật duyệt đồ thị theo chiều sâu - Sử dụng đệ qui
void DFS_Recursion(Graph *g, int x){
    if(mark[x]==1) return; //Nếu đỉnh đã được duyệt kết thúc và không trả về gì
    mark[x]=1; //Nếu chưa duyệt thì đánh dấu đã duyệt
    count++; //Khi có một đỉnh được duyệt -> Tăng count
    List L = neighbors(g,x); //Tìm đỉnh láng giềng của đỉnh đang xét
    for(int j=1;j<=L.size;j++){
        int v = getList(&L,j); //Lấy đỉnh v kề với đỉnh đang xét ra 
        DFS_Recursion(g,v); //Tiếp tục gọi đệ qui
    }
}
bool check(){
    return n==count; //Nếu count = số đỉnh ban đầu của đồ thị -> Đồ thị liên thông -> Giải quyết được vấn đề của chúa đảo
}
int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    
    for(int i=1;i<=n;i++)
        mark[i]=0; //Khởi tạo tất cả các đỉnh điều chưa được duyệt
    

    DFS_Recursion(&g,1); 
    //Muốn kiểm tra đồ thị có liên thông hay không thì dựa vào tính chất -> đồ thị được gọi là liên thông thì chỉ có một thành phần liên thông
    //Nên ta chỉ gọi hàm cho đỉnh 1 nếu nó liên thông thì mặc nhiên tất cả các đỉnh trong đồ thị sẽ được duyệt

    if(check()) printf("YES"); //Liên thông 
    else printf("NO"); //Không liên thông
    
    return 0;
}
/*

Tôn Ngộ Không là một trong các nhân vật chính của truyện Tây du ký. Khi còn ở Hoa Quả Sơn, Tôn Ngộ Không là vua của loài khỉ. Hoa Quả Sơn có rất nhiều cây ăn trái, nên loài khỉ rất thích. Do đặc tính của mình, khỉ không thích đi bộ mà chỉ thích chuyền từ cây này sang một cây khác. Tuy nhiên, nếu khoảng cách giữa hai cây quá xa thi chúng không thể chuyền qua lại được.
Đường đường là vua của loài khỉ, Tôn Ngộ Không muốn vạch ra một kế hoạch hái trái cây trên tất cả các cây có trên Hoa Quả Sơn mà không cần phải nhảy xuống đất. Tôn Ngộ Không dự định sẽ bắt đầu leo lên một cây, hái trái của cây này, sau đó chuyền qua một cây kế tiếp hái trái của này và tiếp tục như thế cho đến khi tất cả các cây đều được hái trái. Một cây có thể được chuyền qua chuyền lại nhiều lần.
Hãy giúp Tôn Ngộ Không kiểm tra xem kế hoạch này có thể thực hiện được không.

Đầu vào (Input):
Giả sử số lượng cây ăn trái ở Hoa Quả Sơn là n cây và được đánh số từ 1 đến n.

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số cây và số cặp cây có thể chuyền qua lại.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng có thể chuyền từ cây u sang cây v hoặc chuyền từ cây v sang cây u.

Đầu ra (Output):

Nếu kế hoạch của Tôn Ngộ Không có thể thực hiện được DUOC, ngược lại in ra KHONG.

Xem thêm ví dụ bên dưới. Trong ví dụ đầu tiên, Tôn Ngộ Không bắt đầu từ cây 1, chuyền qua cây 2, sau đó chuyền ngược về 1, chuyền tiếp sang 3 và sau cùng là sang 4.

For example:

Input	Result

4 3     DUOC 
2 1
1 3
3 4

4 2     KHONG    
1 2
3 4

*/

/*

Có n hòn đảo và m cây cầu. Mỗi cây cầu bắt qua 2 hòn đảo. Một hôm chúa đảo tự hỏi là với các cây cầu hiện tại thì đứng ở một hòn đảo bất kỳ có thể nào đi đến được tất cả các hòn đảo khác hay không.

Hãy giúp chúa đảo viết chương trình kiểm tra.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đảo và số cây cầu.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng có 1 cây cầu bắt qua hai hòn đảo u và v.

Đầu ra (Output):

Nếu có thể đi được in ra màn hình YES, ngược lại in ra NO.

Xem thêm ví dụ bên dưới.
For example:

Input	Result

4 3      YES
1 2
2 3
3 4

4 2     NO
3 4
1 2

*/

//CODE
//Bài toán thực tế - Tôn ngộ không -> Giống bài Qua đảo
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m; //Biến toàn cục lưu n đỉnh và m cung

//Khai báo cấu trúc đồ thị
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

// Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;

/*Các hàm trên danh sách*/

//Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

// Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

// Thêm 1 phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}

// Truy cập phần tử trong danh sách bắt đâu từ vị trí thứ 1 (Mảng bắt đầu bằng 0 nên index phải trừ đi 1)
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm trên đồ thị*/

// Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}

// Thêm cung e = (x,y) vào đồ thị
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

// Kiểm tra 2 đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}

// Tìm đỉnh láng giềng(đỉnh kề) của một đỉnh
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(adjacent(g,x,i)){
            pushList(&L,i);
        }
    }
    return L;
}

int mark[maxv];//Mảng toàn cục mark để đánh dấu 1 đỉnh đã được duyệt hay chưa
int count=0;//Biến count toàn cục để kiểm tra -> Khi một đỉnh được duyệt count sẽ tăng lên 1 -> Nếu kết thúc giải thuật mà count = đỉnh n -> Liên thông

// Giải thuật duyệt đồ thị theo chiều sâu - Sử dụng đệ qui
void DFS_Recursion(Graph *g, int x){
    if(mark[x]==1) return; //Nếu đỉnh đã được duyệt kết thúc và không trả về gì
    mark[x]=1; //Nếu chưa duyệt thì đánh dấu đã duyệt
    count++; //Khi có một đỉnh được duyệt -> Tăng count
    List L = neighbors(g,x); //Tìm đỉnh láng giềng của đỉnh đang xét
    for(int j=1;j<=L.size;j++){
        int v = getList(&L,j); //Lấy đỉnh v kề với đỉnh đang xét ra 
        DFS_Recursion(g,v); //Tiếp tục gọi đệ qui
    }
}
bool check(){
    return n==count; //Nếu count = số đỉnh ban đầu của đồ thị -> Đồ thị liên thông -> Giải quyết được vấn đề của chúa đảo
}
int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    
    for(int i=1;i<=n;i++)
        mark[i]=0; //Khởi tạo tất cả các đỉnh điều chưa được duyệt
    

    DFS_Recursion(&g,1); 
    //Muốn kiểm tra đồ thị có liên thông hay không thì dựa vào tính chất -> đồ thị được gọi là liên thông thì chỉ có một thành phần liên thông
    //Nên ta chỉ gọi hàm cho đỉnh 1 nếu nó liên thông thì mặc nhiên tất cả các đỉnh trong đồ thị sẽ được duyệt

    if(check()) printf("DUOC"); //Liên thông 
    else printf("KHONG"); //Không liên thông
    
    return 0;
}
/*
Cho một đồ thị vô hướng đơn. Hãy in ra thứ tự của các đỉnh khi duyệt đồ thị theo chiều sâu (sử dụng NGĂN XẾP) bắt đầu từ đỉnh 1.

Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

Quy ước:

Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần.


Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng mô tả cung (u, v).

Đầu ra (Output):

In ra các đỉnh theo thứ tự duyệt, mỗi đỉnh trên 1 dòng.

Xem thêm các ví dụ bên dưới.



Hướng dẫn đọc dữ liệu và chạy thử chương trình
Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
*/

//CODE

/// Duyệt đồ thị theo chiều sâu - Stack
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100

int n,m;//Biến toàn cục lưu n đỉnh và m cung

// Khai báo cấu trúc đồ thị
typedef int Vertices;
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Đỉnh n
}Graph;

// Khai báo cấu trúc danh sách - LIST
typedef struct{
    int data[idx];
    int size;
}List;

// Khai báo cấu trúc ngắn xếp - STACK
typedef struct{
    int data[idx];
    int size;
}Stack;

/*Các hàm của ngăn xếp*/

// Làm rỗng ngăn xếp
void makenullStack(Stack *s){
    s->size=0;
}

// Kiểm tra ngăn xếp có rỗng hay không
bool emptyStack(Stack *s){
    return s->size==0;
}

// Thêm 1 phần tử vào ngăn xếp
void pushStack(Stack *s, int element){
    s->data[s->size]=element;
    s->size++;
}

//Truy cập phần tử trong ngăn xếp
int getStack(Stack *s){
    return s->data[s->size-1];
}

// Xóa vị trí phần tử trong ngăn xếp đi(Vị trị này thực tế vẫn còn nhưng chúng ta không truy cập đến nữa)
void delSize(Stack *s){
    s->size--;
}

/*Các hàm trên danh sách*/

// Làm rỗng danh sách
void makenullList(List *l){
    l->size=0;
}

// Kiểm tra danh sách có rỗng hay không
bool emptyList(List *l){
    return l->size==0;
}

// Thêm 1 phần tử vào danh sách
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}

// Truy cập đến phần tử có vị trí index trong danh sách
int getList(List *l, int index){
    return l->data[index-1];
}

/*Các hàm trên đồ thị*/

// Khởi tạo đồ thị
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}

// Thêm cung e = (x,y) vào đồ thị
void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
    g->matrix[y][x]=1;
}

// Kiểm tra 2 đỉnh có kề nhau hay không
bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}

// Tìm tất cả đỉnh láng giềng(đỉnh kề) của đỉnh x
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(adjacent(g,x,i)){
            pushList(&L,i);
        }
    }
    return L;
}
int mark[maxv];//Mảng toàn cục mark để đánh dấu 1 đỉnh đã được duyệt hay chưa

// Giải thuật duyệt sâu sử dụng ngăn xếp - DFS - STACK
List DFS_Stack(Graph *g, int x){
    List rs;//Danh sách lưu các đỉnh đã được duyệt
    makenullList(&rs);
    Stack s;
    makenullStack(&s);
    pushStack(&s,x);
    while(!emptyStack(&s)){ //Lập trong khi ngăn xếp chưa rỗng
        int u = getStack(&s);
        delSize(&s);
        if(mark[u]==1) continue; //Nếu đỉnh u đã được duyệt thì bỏ qua các câu lệnh phía sau
        pushList(&rs,u); //Nếu u chưa duyệt thay vì in ra thì chúng ta sẽ đưa vào danh sách rs(result) -> danh sách kết quả
        mark[u]=1; //Đánh dấu u đã duyệt
        List L = neighbors(g,u); //Tìm đỉnh láng giềng của u đưa vào danh sách L
        for(int j=1;j<=L.size;j++){
            int v = getList(&L,j); //Lấy đỉnh láng giềng u trong danh sách L ra -> Lấy đỉnh v
            if(mark[v]==0){ //Nếu v chưa được duyệt
                pushStack(&s,v); //Đưa vào ngăp xếp duyệt v
            }
        }
    }
    return rs;
}
int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&g,u,v);
    }
    // Khởi tạo toàn bộ phần tử trong mảng mark bằng 0 vì chưa có đỉnh nào được duyệt
    for(int i=1;i<=n;i++) mark[i]=0;
    
    for(int i=1;i<=n;i++){
        if(mark[i]==0){ //Nếu đỉnh chưa được duyệt
            List L = DFS_Stack(&g,i); //Gọi hàm và duyệt 
            for(int j=1;j<=L.size;j++){
                int v = getList(&L,j);
                printf("%d\n",v); //in
                mark[v]=1; //Đánh dấu đã duyệt
            }
        }
    }
    return 0;
}
// Cho G=<V, E> là một đồ thị vô hướng (có thể chứa có khuyên và đa cung). Hãy viết chương trình kiểm tra xem có chứa chu trình hay không.

// Chu trình là một đường đi đơn cung có đỉnh đầu trùng với đỉnh cuối.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

// - m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

// Đầu ra (Output):

// In ra màn hình YES nếu đồ thị có chứa chu trình, ngược lại in ra NO
#include <stdio.h>

#define MAX_N 100

typedef struct{
	int n, m;
	int A[MAX_N][MAX_N];
} Graph;

void init_graph (Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; i <= n; i++)
			pG->A[i][j] = 0;
}

void add_edge (Graph *pG, int u, int v) {
	pG->A[u][v] = 1;
    //pG->A[v][u] = 1; // Uncomment for undirected graph
	pG->m++;
}

void read_graph (Graph *pG){
    int n, m;
    scanf ("%d %d", &n, &m);
    init_graph (pG, n);
    for (int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(pG, u, v);
    }
}

int mark[MAX_N];

void init_mark(int n){
    for(int i = 1; i <= n; i++)
        mark[i] = 0;
}

int cycle_check (Graph *pG, int u){
    if (!mark[u]){
        mark[u] = 1;
        for (int v = 1; v <= pG->n; v++){
            if(pG->A[u][v]){
                if(!mark[v])
                    return cycle_check(pG, v);
                else if (mark[v] == 1)
                   return 1;
            }
        }
    }
    mark[u] = 2;
    return 0;
}

int main (){
    Graph G;    
    read_graph (&G);
    init_mark(G.n);
    printf(cycle_check(&G, 1) ? "YES" : "NO");
}
/*
Thuyền trưởng Haddock (truyện Tintin) là một người luôn say xỉn. Vì thế đôi khi Tintin không biết ông ta đang say hay tỉnh. Một ngày nọ, Tintin hỏi ông ta về cách uống. Haddock nói như thế này: Có nhiều loại thức uống (soda, wine, water, …), tuy nhiên Haddock lại tuân theo quy tắc “để uống một loại thức uống nào đó cần phải uống tất cả các loại thức uống tiên quyết của nó”. Ví dụ: để uống rượu (wine), Haddock cần phải uống soda và nước (water) trước. Vì thế muốn say cũng không phải dễ !

Cho danh sách các thức uống và các thức uống tiên quyết của nó. Hãy xét xem Haddock có thể nào say không ? Để làm cho Haddock say, ông ta phải uống hết tất cả các thức uống.

Ví dụ 1:

soda wine
water wine
Thức uống tiên quyết được cho dưới dạng a b, có nghĩa là để uống b bạn phải uống a trước. Trong ví dụ trên để uống wine, Haddock phải uống soda và water trước. Soda và water không có thức uống tiên quyết nên Haddock sẽ SAY.

Ví dụ 2:

soda wine
water wine
wine water
Để uống wine, cần uống water. Tuy nhiên để uống water lại cần wine. Vì thế Haddock không thể uống hết được các thức uống nên ông ta KHÔNG SAY.

Để đơn giản ta có thể giả sử các thức uống được mã hoá thành các số nguyên từ 1, 2, … và dữ liệu đầu vào được cho có dạng như sau (ví dụ 1):

3 2
1 2
3 2
Có loại thức uống (soda: 1, wine: 2 và water: 3) và có 2 điều kiện tiên quyết

1 -> 2 và 3 -> 2.

Với ví dụ 2, ta có dữ liệu:

3 3
1 2
3 2
2 3

Viết chương trình đọc dữ liệu các thức uống và kiểm tra xem Haddock có thể say không. Nếu có in ra “YES”, ngược lại in ra “NO”.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím (stdin) với định dạng:

Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số thức uống và số điều kiện tiên quyết .
m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng thức uống u là tiên quyết của thức uống v.
Đầu ra (Output):

Nếu Haddock có thể say in ra YES, ngược lại in ra NO.
*/

//code
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
int mark[maxv];
int index;
typedef int Vertices;
int n,m;//So dinh va so cung 
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Dinh n
}Graph;
//Cau truc danh sach - List
typedef struct{
    int data[idx];
    int size;
}List;
//lam rong
void makenullList(List *l){
    l->size=0;
}
//Them phan tu
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}
//Truy cap phan tu
int getList(List *l, int index){
    return l->data[index];
}
//Khoi tao
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
//Add
void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}
//Lang gieng cua 1 dinh 
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(g->matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
void dfs(Graph* G, int x) {
    if(mark[x]==2) return;
    //print("%d\n",x)
    mark[x] = 2;
    List L = neighbors(G, x);
    for(int j=0;j<L.size;j++){
        int v = getList(&L, j);
        if(mark[v] == 2){
            index = 1; // Ton tai chu trinh
            return;
        }
        dfs(G, v);
    }
    mark[x]=1;
}
int check(Graph* G) {
    for(int i=1;i<=G->n;i++){
        mark[i] = 0;
    }
    index = 0;
    for(int j=1;j<=G->n;j++){
        dfs(G, j);    
    }
    return index;
}

int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&u,&v);
        addGraph(&g,u,v);
    }
    if (check(&g)==1) printf("NO");
    else printf("YES");
    
    return 0;
}
/*
Thuyền trưởng Haddock (truyện Tintin) là một người luôn say xỉn. Vì thế đôi khi Tintin không biết ông ta đang say hay tỉnh. Một ngày nọ, Tintin hỏi ông ta về cách uống. Haddock nói như thế này: Có nhiều loại thức uống (soda, wine, water, …), tuy nhiên Haddock lại tuân theo quy tắc “để uống một loại thức uống nào đó cần phải uống tất cả các loại thức uống tiên quyết của nó”. Ví dụ: để uống rượu (wine), Haddock cần phải uống soda và nước (water) trước. Vì thế muốn say cũng không phải dễ !

Cho danh sách các thức uống và các thức uống tiên quyết của nó. Hãy xét xem Haddock có thể nào say không ? Để làm cho Haddock say, ông ta phải uống hết tất cả các thức uống.

Ví dụ 1:

soda wine
water wine
Thức uống tiên quyết được cho dưới dạng a b, có nghĩa là để uống b bạn phải uống a trước. Trong ví dụ trên để uống wine, Haddock phải uống soda và water trước. Soda và water không có thức uống tiên quyết nên Haddock sẽ SAY.

Ví dụ 2:

soda wine
water wine
wine water
Để uống wine, cần uống water. Tuy nhiên để uống water lại cần wine. Vì thế Haddock không thể uống hết được các thức uống nên ông ta KHÔNG SAY.

Để đơn giản ta có thể giả sử các thức uống được mã hoá thành các số nguyên từ 1, 2, … và dữ liệu đầu vào được cho có dạng như sau (ví dụ 1):

3 2
1 2
3 2
Có loại thức uống (soda: 1, wine: 2 và water: 3) và có 2 điều kiện tiên quyết

1 -> 2 và 3 -> 2.

Với ví dụ 2, ta có dữ liệu:

3 3
1 2
3 2
2 3

Viết chương trình đọc dữ liệu các thức uống và kiểm tra xem Haddock có thể say không. Nếu có in ra “YES”, ngược lại in ra “NO”.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím (stdin) với định dạng:

Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số thức uống và số điều kiện tiên quyết .
m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng thức uống u là tiên quyết của thức uống v.
Đầu ra (Output):

Nếu Haddock có thể say in ra YES, ngược lại in ra NO.
*/

//code
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
int mark[maxv];
int index;
typedef int Vertices;
int n,m;//So dinh va so cung 
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//Dinh n
}Graph;
//Cau truc danh sach - List
typedef struct{
    int data[idx];
    int size;
}List;
//lam rong
void makenullList(List *l){
    l->size=0;
}
//Them phan tu
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}
//Truy cap phan tu
int getList(List *l, int index){
    return l->data[index];
}
//Khoi tao
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
//Add
void addGraph(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}
//Lang gieng cua 1 dinh 
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(g->matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
void dfs(Graph* G, int x) {
    if(mark[x]==2) return;
    //print("%d\n",x)
    mark[x] = 2;
    List L = neighbors(G, x);
    for(int j=0;j<L.size;j++){
        int v = getList(&L, j);
        if(mark[v] == 2){
            index = 1; // Ton tai chu trinh
            return;
        }
        dfs(G, v);
    }
    mark[x]=1;
}
int check(Graph* G) {
    for(int i=1;i<=G->n;i++){
        mark[i] = 0;
    }
    index = 0;
    for(int j=1;j<=G->n;j++){
        dfs(G, j);    
    }
    return index;
}

int main(){
    Graph g;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    int u,v;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&u,&v);
        addGraph(&g,u,v);
    }
    if (check(&g)==1) printf("NO");
    else printf("YES");
    
    return 0;
}
/*
Viết chương trình kiểm tra xem một đồ thị có hướng có liên thông mạnh không.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàna phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

Chú ý: đồ thị không chứa đa cung.

Đầu ra (Output):

In ra màn hình strong connected nếu đồ thị đã cho liên thông mạnh, ngược lại in ra unconnected.

Xem thêm ví dụ bên dưới.

Hướng dẫn đọc dữ liệu và chạy thử chương trình

Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

*/

//code

#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
typedef int Vertices;
int n,m;//Bien toan cuc luu so dinh va so cung 
//Khai bao cau truc do thi - GRAPH
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//
}Graph;
//Khai bao cau truc ngan xep - STACK
typedef struct{
    int data[maxv];
    int size;
}Stack;
//Lam rong
void makenullStack(Stack *s){
    s->size=0;
}
//Them phan tu vao ngap xep
void pushStack(Stack *s, int element){
    s->data[s->size] = element;
    s->size++;
}
//Lay phan tu cua ngan xep
int getStack(Stack *s){
    return s->data[s->size-1];
}
void delSize(Stack *s){
    s->size--;
}
//Khai bao cau truc danh sach - LIST
typedef struct{
    int data[idx];
    int size;
}List;
//Lam rong
void makenullList(List *l){
    l->size=0;
}
//Them phan tu vao danh sach
void pushList(List *l, int element){
    l->data[l->size] = element;
    l->size++;
}
//Truy cap phan tu trong danh sach
int getList(List *l, int index){
    return l->data[index];
}
//Khoi tao
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
//Them cung 
void addEdges(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}
//In do thi
void printGraph(Graph g){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
}
//Tim dinh lang gieng
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(g->matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
//Cac bien mang toan cuc de thuc hien viec kiem tra
int count=0,k=1;
int num[maxv],min_num[maxv],on_stack[maxv];
//Ham tim gia tri nho nhat
int min(int a, int b){
    return (a<b) ? a : b;
}
void strong_connect(Graph *g, int x){
    //Cho num va min num bang chi so k
    num[x] = min_num[x] = k;
    k++;
    Stack s;
    makenullStack(&s);
    //Dua dinh dau tien vao stack
    pushStack(&s,x);
    //Danh dau dinh do da dua vao stack bang bien mang on_stack
    on_stack[x]=1;
    //Tim dinh lang gieng cua dinh do
    List L = neighbors(g,x);
    //Xet cac dinh ke cua x
    for(int j=0;j<L.size;j++){
        int v = getList(&L,j);
        //Neu dinh ke x chua co trong stack
        if(on_stack[v]==-1){
            //Goi de qui duyet dinh ke cua x
            strong_connect(g,v);
            //Khi dut lui cap nhat lai min_num cho dinh x(min_num cha < min_num con)
            min_num[x] = min(min_num[x],min_num[v]);
        }
        //Neu dinh v ke x da co trong stack
        else if(on_stack[v]==1){
            //Cap nhat lai min num
            min_num[x] = min(min_num[x],num[v]);
        }
        //Sau khi duyet xong 1 dinh ma vong lap for o tren dung lai tuc la ta da co 1 bo phan lien thong manh
        //Neu do thi lien thong manh thi ket thuc luon chuong trinh vi do thi lien thong thi chi co 1 thanh phan lien thong
        if(num[x]==min_num[x]){
            count++;//Bien count de diem so bo phan lien thong manh cua do thi
            int value;
            do{
                //Lay dinh o dau stack ra
                value = getStack(&s);
                delSize(&s);
                //danh dau dinh da lay ra khoi stack
                on_stack[x]=0;
            }while(value!=x);//Lap den khi lay duoc dinh x(Dinh cat)
        }
    }
}
int main(){
    Graph g;
    int u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdges(&g,u,v);
    }
    for(int i=1;i<=n;i++){
        on_stack[i]=-1;
    }
    for(int i=1;i<=n;i++){
        if(on_stack[i]==-1){
            strong_connect(&g,i);
        }
    }
    if(count==1) printf("strong connected");
    else printf("unconnected");
    return 0;
}
/*
Viết chương trình đếm số bộ phận liên thông mạnh (BPLTM) của một đồ thị có hướng.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.
- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

Chú ý: đồ thị không chứa đa cung.

Đầu ra (Output):

In ra màn hình một con số nguyên duy nhất chỉ số BPTLM của đồ thị.

Xem thêm ví dụ bên dưới.

Hướng dẫn đọc dữ liệu và chạy thử chương trình
Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
*/

//code

//Kiem tra do thi co lien thong manh hay khong - Don do thi co huong - ma tran dinh dinh
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
typedef int Vertices;
int n,m;//Bien toan cuc luu so dinh va so cung 
//Khai bao cau truc do thi - GRAPH
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//
}Graph;
//Khai bao cau truc ngan xep - STACK
typedef struct{
    int data[maxv];
    int size;
}Stack;
//Lam rong
void makenullStack(Stack *s){
    s->size=0;
}
//Them phan tu vao ngap xep
void pushStack(Stack *s, int element){
    s->data[s->size] = element;
    s->size++;
}
//Lay phan tu cua ngan xep
int getStack(Stack *s){
    return s->data[s->size-1];
}
void delSize(Stack *s){
    s->size--;
}
//Khai bao cau truc danh sach - LIST
typedef struct{
    int data[idx];
    int size;
}List;
//Lam rong
void makenullList(List *l){
    l->size=0;
}
//Them phan tu vao danh sach
void pushList(List *l, int element){
    l->data[l->size] = element;
    l->size++;
}
//Truy cap phan tu trong danh sach
int getList(List *l, int index){
    return l->data[index];
}
//Khoi tao
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
//Them cung 
void addEdges(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}
//In do thi
void printGraph(Graph g){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
}
//Tim dinh lang gieng
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(g->matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
//Cac bien mang toan cuc de thuc hien viec kiem tra
int count,k=1;
int num[maxv],min_num[maxv],on_stack[maxv];
//Ham tim gia tri nho nhat
int min(int a, int b){
    return (a<b) ? a : b;
}
void strong_connect(Graph *g, int x){
    //Cho num va min num bang chi so k
    num[x] = min_num[x] = k;
    k++;
    Stack s;
    makenullStack(&s);
    //Dua dinh dau tien vao stack
    pushStack(&s,x);
    //Danh dau dinh do da dua vao stack bang bien mang on_stack
    on_stack[x]=1;
    //Tim dinh lang gieng cua dinh do
    List L = neighbors(g,x);
    //Xet cac dinh ke cua x
    for(int j=0;j<L.size;j++){
        int v = getList(&L,j);
        //Neu dinh ke x chua co trong stack
        if(num[v]==-1){
            //Goi de qui duyet dinh ke cua x
            strong_connect(g,v);
            //Khi dut lui cap nhat lai min_num cho dinh x(min_num cha < min_num con)
            min_num[x] = min(min_num[x],min_num[v]);
        }
        //Neu dinh v ke x da co trong stack
        else if(on_stack[v]==1){
            //Cap nhat lai min num
            min_num[x] = min(min_num[x],num[v]);
        }
        //Sau khi duyet xong 1 dinh ma vong lap for o tren dung lai tuc la ta da co 1 bo phan lien thong manh
        //Neu do thi lien thong manh thi ket thuc luon chuong trinh vi do thi lien thong thi chi co 1 thanh phan lien thong
        if(num[x]==min_num[x]){
            count++;//Bien count de diem so bo phan lien thong manh cua do thi
            int value;
            do{
                //Lay dinh o dau stack ra
                value = getStack(&s);
                delSize(&s);
                //danh dau dinh da lay ra khoi stack
                on_stack[x]=0;
            }while(value!=x);//Lap den khi lay duoc dinh x(Dinh cat)
        }
    }
}
int main(){
    Graph g;
    int u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdges(&g,u,v);
    }
    count=0;//Khoi tao bien dem ban dau = 0 - day la bien toan cuc

    for(int i=1;i<=n;i++){
        num[i] = -1;
        min_num[i] = 0;
    }
    for(int i=1;i<=n;i++){
        if(num[i]==-1){
            strong_connect(&g,i);
        }
    }
    printf("%d",count);
    return 0;
}
/*
Trong một thành phố có N địa điểm được nối với nhau bằng M con đường 1 chiều và 2 chiều. Yêu cầu tối thiểu của một thành phố là từ địa điểm này bạn phải có thể đi đến một địa điểm khác bất kỳ.

Hãy viết chương trình kiểm tra xem các con đường của thành phố có thoả mãn yêu cầu tối thiểu này không. Nếu có in ra OKIE, ngược lại in ra NO.

(nguồn: UVA Online Judge, Problem 11838)

Dữ liệu đầu vào có dạng như sau:

4 5
1 2 1
1 3 2
2 4 1
3 4 1
4 1 2
Trong ví dụ này, có 4 địa điểm và 5 con đường, mỗi con đường có dạng a b p,  trong đó a, b là các địa điểm; và nếu p = 1, con đường đang xét là đường 1 chiều, ngược lại nó là đường 2 chiều.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím (stdin) với định dạng:

- Dòng đầu tiên chứa 2 số nguyên N và M, tương ứng là số địa điểm và số con đường.

- M dòng tiếp theo mỗi dòng chứa 3 số nguyên a, b, p. Nếu p = 1, con đường (a, b) là con đường 1 chiều, ngược lại nếu p = 2, con đường (a, b) là con đường 2 chiều.

Đầu ra (Output):

In ra màn hình OKIE nếu các con đường của thành phố có thoả mãn yêu cầu, ngược lại in ra NO.

Xem thêm ví dụ bên dưới.

Gợi ý:

Xây dựng đồ thị có hướng từ dữ liệu các con đường và các địa điểm
Địa điểm ~ đỉnh
Đường 1 chiều ~ cung
Đường 2 chiều ~ 2 cung
Áp dụng giải thuật kiểm tra đồ thị có liên thông mạnh hay không.
*/

//code
//Kiem tra do thi co lien thong manh hay khong - Don do thi co huong - ma tran dinh dinh
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
typedef int Vertices;
int n,m;//Bien toan cuc luu so dinh va so cung 
//Khai bao cau truc do thi - GRAPH
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//
}Graph;
//Khai bao cau truc ngan xep - STACK
typedef struct{
    int data[maxv];
    int size;
}Stack;
//Lam rong
void makenullStack(Stack *s){
    s->size=0;
}
//Them phan tu vao ngap xep
void pushStack(Stack *s, int element){
    s->data[s->size] = element;
    s->size++;
}
//Lay phan tu cua ngan xep
int getStack(Stack *s){
    return s->data[s->size-1];
}
void delSize(Stack *s){
    s->size--;
}
//Khai bao cau truc danh sach - LIST
typedef struct{
    int data[idx];
    int size;
}List;
//Lam rong
void makenullList(List *l){
    l->size=0;
}
int emptyList(List *l){
    return l->size==0;
}
//Them phan tu vao danh sach
void pushList(List *l, int element){
    l->data[l->size] = element;
    l->size++;
}
//Truy cap phan tu trong danh sach
int getList(List *l, int index){
    return l->data[index];
}
//Khoi tao
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
//Them cung 
void addEdges(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}
//In do thi
void printGraph(Graph g){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
}
//Tim dinh lang gieng
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(g->matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
//Cac bien mang toan cuc de thuc hien viec kiem tra
int count=0,k=1;
int num[maxv],min_num[maxv],on_stack[maxv];
//Ham tim gia tri nho nhat
int min(int a, int b){
    return (a<b) ? a : b;
}
void strong_connect(Graph *g, int x){
    //Cho num va min num bang chi so k
    num[x] = min_num[x] = k;
    k++;
    Stack s;
    makenullStack(&s);
    //Dua dinh dau tien vao stack
    pushStack(&s,x);
    //Danh dau dinh do da dua vao stack bang bien mang on_stack
    on_stack[x]=1;
    //Tim dinh lang gieng cua dinh do
    List L = neighbors(g,x);
    //Xet cac dinh ke cua x
    for(int j=0;j<L.size;j++){
        int v = getList(&L,j);
        //Neu dinh ke x chua co trong stack
        if(num[v]==-1){
            //Goi de qui duyet dinh ke cua x
            strong_connect(g,v);
            //Khi dut lui cap nhat lai min_num cho dinh x(min_num cha < min_num con)
            min_num[x] = min(min_num[x],min_num[v]);
        }
        //Neu dinh v ke x da co trong stack
        else if(on_stack[v]==1){
            //Cap nhat lai min num
            min_num[x] = min(min_num[x],num[v]);
        }
        //Sau khi duyet xong 1 dinh ma vong lap for o tren dung lai tuc la ta da co 1 bo phan lien thong manh
        //Neu do thi lien thong manh thi ket thuc luon chuong trinh vi do thi lien thong thi chi co 1 thanh phan lien thong
        if(num[x]==min_num[x]){
            count++;//Bien count de diem so bo phan lien thong manh cua do thi
            int value;
            do{
                //Lay dinh o dau stack ra
                value = getStack(&s);
                delSize(&s);
                //danh dau dinh da lay ra khoi stack
                on_stack[x]=0;
            }while(value!=x);//Lap den khi lay duoc dinh x(Dinh cat)
        }
    }
}
int main(){
    Graph g;
    int u,v,y;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&y);
        if(y==1) addEdges(&g,u,v);
        else if(y==2){
            addEdges(&g,u,v);
            addEdges(&g,v,u);
        }
        
    }

    for(int i=1;i<=n;i++){
        num[i] = -1;
        min_num[i] = 0;
    }
    for(int i=1;i<=n;i++){
        if(num[i]==-1){
            strong_connect(&g,i);
        }
    }

    if(count==n || count==1) printf("OKIE");
    else printf("NO");    
    
    
    return 0;
}
// Hãy hoàn thiện chương trình sau để đếm số thành phần liên thông của đồ thị vô hướng. Hãy copy đoạn chương trình của bạn và dán vào ô trả lời.

// Chú ý: Biểu diễn đồ thị bằng phương pháp ma trận kề.

// /*===BAT DAU==*/
// Viết chương trình của bạn ở đây và copy phần này dán vào ô trả lời.
// /*===KET THUC==*/
// int main() {
//     Graph G;
//     int m, n, e;
//     scanf("%d%d", &n, &m);
//     init_graph(&G, n);
//     for (e = 1; e <= m; e++) {
//         int u, v;
//         scanf("%d%d", &u, &v);
//         G.A[u][v] = G.A[v][u] = 1;
//     }
    
//     printf("%d\n", connected_components(&G));
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef int ElementType;

typedef struct Node {
    ElementType Data;
    struct Node *Next;
} Node;

typedef Node *Stack;

void make_null_stack(Stack *pS){
    (*pS) = (Node*)malloc(sizeof(Node));
    (*pS)->Next = NULL;    
}
    
void push(Stack *pS, int x){
    Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->Data = x;
	newNode->Next = (*pS)->Next;
    (*pS)->Next   = newNode;
}

ElementType pop(Stack *pS){
    Node *Temp = (*pS);
    (*pS) = (*pS)->Next;
    free(Temp);
    return (*pS)->Data;
}

typedef struct{
	int n, m;
	int A[MAX_N][MAX_N];
} Graph;

void init_graph (Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; i <= n; i++)
			pG->A[i][j] = 0;
}

void add_edge (Graph *pG, int u, int v) {
	pG->A[u][v] = 1;
    pG->A[v][u] = 1;
	pG->m++;
}

void read_graph (Graph *pG){
    int n, m;
    scanf ("%d %d", &n, &m);
    init_graph (pG, n);
    for (int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(pG, u, v);
    }
}

int mark[MAX_N];

void init_mark (int n){
    for(int i = 1; i <= n; i++){
        mark[i] = 0;
    }
}

int dfs(Graph *pG, int s){
    int nodes_count = 0;
    Stack S;
    make_null_stack(&S);
    push(&S, s);
    while (S->Next != NULL){
        int u = pop(&S);
        if (!mark[u]){
            mark[u] = 1;
            nodes_count++;
            for (int v = pG->n; v >= 1; v--)
                if (pG->A[u][v])
                    push(&S,v);
        }            
    }
    return nodes_count;
}
int connected_components (Graph *pG){
    int c=0;
    for(int i = 0; i <= pG->n; i++){
        mark[i] = 0;
    }
    dfs(pG, 1);
    for (int i =0; i < pG->n; i++)
        if (!mark[i])
        c++;
    return c;
}
/*
Viết chương trình kiểm tra xem một đồ thị có hướng có liên thông mạnh không.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàna phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

Chú ý: đồ thị không chứa đa cung.

Đầu ra (Output):

In ra màn hình strong connected nếu đồ thị đã cho liên thông mạnh, ngược lại in ra unconnected.

Xem thêm ví dụ bên dưới.

Hướng dẫn đọc dữ liệu và chạy thử chương trình

Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

*/

//code

#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
typedef int Vertices;
int n,m;//Bien toan cuc luu so dinh va so cung 
//Khai bao cau truc do thi - GRAPH
typedef struct{
    int matrix[maxv][maxv];
    Vertices n;//
}Graph;
//Khai bao cau truc ngan xep - STACK
typedef struct{
    int data[maxv];
    int size;
}Stack;
//Lam rong
void makenullStack(Stack *s){
    s->size=0;
}
//Them phan tu vao ngap xep
void pushStack(Stack *s, int element){
    s->data[s->size] = element;
    s->size++;
}
//Lay phan tu cua ngan xep
int getStack(Stack *s){
    return s->data[s->size-1];
}
void delSize(Stack *s){
    s->size--;
}
//Khai bao cau truc danh sach - LIST
typedef struct{
    int data[idx];
    int size;
}List;
//Lam rong
void makenullList(List *l){
    l->size=0;
}
//Them phan tu vao danh sach
void pushList(List *l, int element){
    l->data[l->size] = element;
    l->size++;
}
//Truy cap phan tu trong danh sach
int getList(List *l, int index){
    return l->data[index];
}
//Khoi tao
void initGraph(Graph *g){
    g->n=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g->matrix[i][j]=0;
        }
    }
}
//Them cung 
void addEdges(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}
//In do thi
void printGraph(Graph g){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
}
//Tim dinh lang gieng
List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=n;i++){
        if(g->matrix[x][i]==1){
            pushList(&L,i);
        }
    }
    return L;
}
//Cac bien mang toan cuc de thuc hien viec kiem tra
int count=0,k=1;
int num[maxv],min_num[maxv],on_stack[maxv];
//Ham tim gia tri nho nhat
int min(int a, int b){
    return (a<b) ? a : b;
}
void strong_connect(Graph *g, int x){
    //Cho num va min num bang chi so k
    num[x] = min_num[x] = k;
    k++;
    Stack s;
    makenullStack(&s);
    //Dua dinh dau tien vao stack
    pushStack(&s,x);
    //Danh dau dinh do da dua vao stack bang bien mang on_stack
    on_stack[x]=1;
    //Tim dinh lang gieng cua dinh do
    List L = neighbors(g,x);
    //Xet cac dinh ke cua x
    for(int j=0;j<L.size;j++){
        int v = getList(&L,j);
        //Neu dinh ke x chua co trong stack
        if(on_stack[v]==-1){
            //Goi de qui duyet dinh ke cua x
            strong_connect(g,v);
            //Khi dut lui cap nhat lai min_num cho dinh x(min_num cha < min_num con)
            min_num[x] = min(min_num[x],min_num[v]);
        }
        //Neu dinh v ke x da co trong stack
        else if(on_stack[v]==1){
            //Cap nhat lai min num
            min_num[x] = min(min_num[x],num[v]);
        }
        //Sau khi duyet xong 1 dinh ma vong lap for o tren dung lai tuc la ta da co 1 bo phan lien thong manh
        //Neu do thi lien thong manh thi ket thuc luon chuong trinh vi do thi lien thong thi chi co 1 thanh phan lien thong
        if(num[x]==min_num[x]){
            count++;//Bien count de diem so bo phan lien thong manh cua do thi
            int value;
            do{
                //Lay dinh o dau stack ra
                value = getStack(&s);
                delSize(&s);
                //danh dau dinh da lay ra khoi stack
                on_stack[x]=0;
            }while(value!=x);//Lap den khi lay duoc dinh x(Dinh cat)
        }
    }
}
int main(){
    Graph g;
    int u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdges(&g,u,v);
    }
    for(int i=1;i<=n;i++){
        on_stack[i]=-1;
    }
    for(int i=1;i<=n;i++){
        if(on_stack[i]==-1){
            strong_connect(&g,i);
        }
    }
    if(count==1) printf("connected");
    else printf("unconnected");
    return 0;
}