#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "Graph.h"
#include "Graphmtx.h"
#include"qat.h"
using namespace std;
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
	cout << item << " ";
} 
//const int maxValue = INT_MAX;
struct MSTEdgeNode						//最小生成树边结点
{
	int  tail, head;						//两顶点的位置
	int key;								//边上的权值，为关键码
	MSTEdgeNode() :tail(-1), head(-1), key(0) {}
};
void CreatGraph(Graphmtx &G, char V[], int n, RowColWeight E[], int e)
//在图G中插入n个顶点V和e条边E
{
	//在图G中插入n个顶点
	for (int i = 0; i < n; i++)
		G.insertVertex(V[i]);

	//在图G中插入e条边
	for (int k = 0; k < e; k++)
		G.insertEdge(E[k].row, E[k].col, E[k].weight);
}

ostream& operator << (ostream& out, Graphmtx& G)
{
	int i, j;
	cout << "顶点个数为:" << G.NumberOfVertices() << endl;
	cout << "边的条数为:" << G.NunberOfEdges() << endl;
	cout << "结点集合为:";
	for (i = 0; i< G.NumberOfVertices(); i++)
		cout << "     " << G.getValue(i);
	cout << "\n";
	cout << "权值集合为:\n";
	for (i = 0; i<G.NumberOfVertices(); i++)
	{
		for (j = 0; j<G.NumberOfVertices(); j++)
		{
			if (G.getWeight(i, j) == INT_MAX)
				cout << setw(10) << "Max" << " ";
			else
				cout << setw(10) << G.getWeight(i, j) << "";
		}
		cout << "\n";
	}
	return out;
}

int main()
{
	int src;
	int head, tail;
	char v1[] = { '1','2','3','4','5','6','7','8','9' };//顶点信息
	RowColWeight rcw1[] = { { 0,1,2 },{ 0,5,1 },{ 0,6,1 },{ 1,2,2 },{ 1,3,4 },
	{ 2,3,1 },{ 2,5,3 },{ 2,6,2 },{ 3,4,1 },{ 3,6,6 },
	{ 3,7,5 },{ 3,8,2 },{ 4,5,5 },{ 5,6,1 },{ 6,7,3 },
	{ 7,8,2 } };//边信息
	int n = 9, e = 16;
	WT *distance = new int[n];
	int *path = new int[n];
	Graphmtx g1;
	CreatGraph(g1, v1, n, rcw1, e);
	cout << g1;						//输出图	
	cout << "请输入路由器号：";
	cin >> src;
	ShortestPath(g1, src - 1, distance, path);
	cout << endl;
	cout << "请输入您要删除的边:";
	cin >> head >> tail;
	g1.removeEdge(head, tail);
	cout << g1;
	cout << "请输入路由器号：";
	cin >> src;
	ShortestPath(g1, src - 1, distance, path);
	system("pause");
	return 0;
}