#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;
#include "Graph.h"
#include "Graphlnk.h"
#include "Graphmtx.h"
#include "GraphApp.h"
const int MaxVertices = 100;	//图中的最大顶点数目
const int MaxWeight = 10000;	//无穷大的权值


typedef char VT;	//图中顶点数据域类型VT
typedef int WT;		//图中边权值类型WT

//边信息类型定义
struct RowColWeight
{
	int row;							//行下标
	int col;							//列下标
	WT weight;							//权值
};
void PrintItem(VT item)	//输出顶点数据域
{
	cout << item<<" ";
}
template<class T,class E>
void CreatGraph(Graphlnk<T,E> &G, VT V[], int n, RowColWeight E[],int e)
{	//在图G中插入n个顶点V和e条边E

	//在图G中插入n个顶点
	for(int i = 0; i < n; i++) 
		G.insertVertex(V[i]);

	//在图G中插入e条边
	for(int k = 0; k < e; k++) 
		G.insertEdge(E[k].row, E[k].col, E[k].weight);
}
template<class T,class E>
void CreatGraph(Graphmtx<T,E> &G, VT V[], int n, RowColWeight E[],int e)
	//在图G中插入n个顶点V和e条边E
{
	//在图G中插入n个顶点
	for(int i = 0; i < n; i++) 
		G.insertVertex(V[i]);

	//在图G中插入e条边
	for(int k = 0; k < e; k++) 
		G.insertEdge(E[k].row, E[k].col, E[k].weight);
}
/*void readfile1()
{
	FILE *fp;
	int i;
	VT	v1[100];
	fp = fopen("dd.txt", "r");
	if (fp == NULL)
	{
		cout << "cannot open read file" << endl;
		return;
	}
	i = 0;
	while (!feof(fp))
	{
		fscanf(fp, " %s \n", &v1[i]);
		i++;
	}
	fclose(fp);
}
void readfile2()
{
	FILE *fp;
	int i;
	RowColWeight s[100];
	fp = fopen("edge.txt", "r");
	if (fp == NULL)
	{
		cout << "cannot open read file" << endl;
		return;
	}
	i = 0;
	while (!feof(fp))
	{
		fscanf(fp, " %d \n %d \n %d \n", &s[i].col, &s[i].row, &s[i].weight);
		i++;
	}
	fclose(fp);
}*/
int main()
{
	
	char v1[] = {'1','2','3','4','5','6','7','8','9'};//顶点信息
	RowColWeight rcw1[] = {{0,1,2},{0,5,1},{0,6,1},{1,3,4},{1,2,2},{2,5,3},{2,6,2},{2,3,1},{3,6,6},{3,4,1},{3,7,5},{3,8,2} ,{4,5,5},{5,6,1},{6,7,3},{7,8,2} };//边信息
	int n = 9, e = 16,i,m,v3,v2;
	WT *distance= new int[n];
	int *path= new int[n];
	MSTEdgeNode<VT,WT> MST[MaxVertices];
	Graphmtx<VT,WT> g1;
//	readfile1();
//	readfile2();
	CreatGraph(g1,v1,n,rcw1,e);
//	cout << g1;
	cout << "请输入需要路由表的路由器：（1-9）" << endl;
	cin >> i;
	ShortestPath(g1,i-1,distance,path);
	cin >> m;
	g1.removeVertex(m);
	cout << g1;
	cout << "请输入：" << endl;
	cin >> i;
	WT *distance1 = new int[8];
	int *path1= new int[15];
	ShortestPath(g1,i,distance1, path1);
	
	cin >> v2 >> v3;
	g1.removeEdge(v3, v2);
	cout << "请输入需要：" << endl;
	cin >> i;
	ShortestPath(g1, i, distance, path);
	cout<<endl;
	MinSpanTree<VT,WT> tree;
	system("pause");
	return 0;
}
