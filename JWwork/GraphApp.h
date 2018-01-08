#ifndef GRAPHAPP_H
#define GRAPHAPP_H
#include "Graphlnk.h"
#include "Graphmtx.h"
#include "Graph.h"
#include "SeqQueue.h"
#include "MinHeap.h"
#include <limits.h>
/*template<class T,class E>
void DFS(Graph<T,E>& G,const T& v)
{//�Ӷ���v��������ͼG����������ȱ���
	int i,loc,n = G.NumberOfVertices();
	bool * visited = new bool[n];                                 
	for( i = 0;i<n; i++)
		visited[i] = false;      
	loc = G.getVertexPos(v);
	for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n)
	{
		if (!visited[i])
			DFS(G, loc, visited);
	}
	delete[] visited;

}
template<class T,class E>
void DFS(Graph<T,E>& G,int v,bool visited[])
{//�Ӷ���v��������������ȷ�ʽ�����������пɶ������δ��λ���
	cout<<G.getValue(v)<<" ";
	visited[v] = true;
	int w = G.getFirstNeighbor(v);
	while (w != -1)
	{
		if(visited[w] == false)
			DFS(G,w,visited);
		w = G.getNextNeighbor(v,w);
	}
}
template<class T,class E>
void BFS(Graph<T,E>& G,const T& v)
{//�Ӷ���v�������Թ�����ȵĴ����������ͼ���㷨��ʹ����һ������
	int i ,w ,n = G.NumberOfVertices();
	bool * visited = new bool[n];
	for( i =0; i<n;i++)
		visited[i] = false;
	int loc = G.getVertexPos(v);
	SeqQueue<int> Q;

	for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n)
	{
		if (!visited[i])
		{
			cout << G.getValue(v) << " ";
			visited[loc] = true;
			Q.EnQueue(loc);
			while (!Q.IsEmpty())
			{
				Q.DeQueue(loc);
				w = G.getFirstNeighbor(loc);
				while (w != -1)
				{
					if (visited[w] == false)
					{
						cout << G.getValue(w) << " ";
						visited[w] = true;
						Q.EnQueue(w);
					}
					w = G.getNextNeighbor(loc, w);
				}
			}
			delete[] visited;
		}
	}
}

template<class T,class E >
int * Path(Graph<T,E> &G,int v1)//ʹ�ù�������������һ�����㵽�����������·����·��������С����
{ 
	int i, w, n = G.NumberOfVertices();
	bool * visited = new bool[n];
	for (i = 0; i<n; i++)
		visited[i] = false;
	SeqQueue<int> Q;
	for (i = v1; i <= (i + n - 1) % n; i = (i + 1) % n)
	{
		if (!visited[i])
		{
			cout << G.getValue(v1) << " ";
			visited[v1] = true;
			Q.EnQueue(v1);
			while (!Q.IsEmpty())
			{
				Q.DeQueue(v1);
				w = G.getFirstNeighbor(v1);
				while (w != -1)
				{
					if (visited[w] == false)
					{
						cout << G.getValue(w) << " ";
						visited[w] = true;
						Q.EnQueue(w);
					}
					w = G.getNextNeighbor(v1, w);
				}
			}
			delete[] visited;
		}
	}
	E dist[100];
	int path[100];
	while (!Q.IsEmpty())
	{
		ShortestPath(G, v1, dist, path);
		printPath(G, v1, dist, path);
		Q.DeQueue(v1);
	}
	//�����������Ĵ��룬�����ҵҪ���滻�������
	return NULL;
}*/

template<class T, class E>
void printPath(Graph<T, E>& G, int v, E dist[], int path[])
{//���path�����д洢��ͼG�Ӷ���v������������·���;���
	cout << "·����" << G.getValue(v) << "��·�ɱ�Ϊ��" << endl;
	int i, j, k, n = G.NumberOfVertices();
	int * d = new int[n];
	for (i = 0; i<n; i++)
	{
		if (i != v)
		{
			j = i;
			k = 0;
			while (j != v)
			{
				d[k++] = j;
				j = path[j];
			}
			cout << "Ŀ��·��" << G.getValue(i) << "����һ��Ϊ��" << " ";
			cout << G.getValue(d[k-1]) << endl;
		}
	}
	delete[] d;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Dijkstra���·��///////////////////////////////////////////////////////////////////
template<class T, class E>
void ShortestPath(Graph<T, E>& G, int v, E dist[], int path[])
{//Graph��һ����Ȩ����ͼ�����㷨����һ�����飬dist[j],0<=j<n;�ǵ�ǰ�󵽵ĴӶ���v������j�����·�����ȣ�ͬʱ������path����󵽵����·��
	int n = G.NumberOfVertices();
	bool *S = new bool[n];
	int i, j, k;
	E w, min;
	for (i = 0; i<n; i++)
	{
		dist[i] = G.getWeight(v, i);
		S[i] = false;
		if (i != v && dist[i] <maxValue)
			path[i] = v;
		else
		{
			path[i] = -1;
		}
	}
	S[v] = true;
	dist[v] = 0;
	for (i = 0; i<n - 1; i++)
	{
		min = maxValue;
		int u = v;
		for (j = 0; j<n; j++)
		{
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;
		for (k = 0; k<n; k++)
		{
			w = G.getWeight(u, k);
			if (S[k] == false && w <maxValue && dist[u] + w<dist[k])
			{
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	printPath(G, v, dist, path);
}


/////////////////////////////��С������//////////////////////////////////////////////////////////////////////////////
const int maxValue = INT_MAX;
template<class T,class E>		
struct MSTEdgeNode						//��С�������߽��
{
	int  tail,head;						//�������λ��
	E key;								//���ϵ�Ȩֵ��Ϊ�ؼ���
	MSTEdgeNode():tail(-1),head(-1),key(0){}
};
template<class T,class E>
class MinSpanTree
{
protected:
	MSTEdgeNode<T,E> * edgevalue;		//�ñ�ֵ�����ʾ��
	int maxSize,n;
public:
	MinSpanTree(int sz = DeafultVertices - 1): maxSize(sz),n(0)
	{
		edgevalue = new MSTEdgeNode<T,E>[sz];
	}
	int Insert(MSTEdgeNode<T,E>& item);
};
/*template<class T,class E>
void Prim(Graph<T,E>& G,const int u0,MinSpanTree<T,E>& MST)
{
	MSTEdgeNode<T,E> ed;
	int i,v,count;
	int n = G.NumberOfVertices();
	int m = G.NunberOfEdges();
	int u = u0;
	MinHeap<E,MSTEdgeNode<T,E>> H(m);		//��С�ѣ��ؼ���ΪE
	bool * Vmst = new bool[n];
	for (i = 0;i<n;i++)
	{
		Vmst[i] = false;
	}
	Vmst[u] = true;
	count = 1;
	do
	{
		v = G.getFirstNeighbor(u);
		while (v != -1)
		{
			if(Vmst[v] == false)
			{
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u,v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u,v);
		}
	
		while(H.IsEmpty() == false && count<n)
		{
			H.RemoveMin(ed);
			if(Vmst[ed.head] == false)
			{
				MST.Insert(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	}while (count<n);
}*/
