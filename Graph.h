#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS

#include "Node.h"
#include "ClassInfo.h"
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

class Graph
{
private: 
	node_head head[30]; //邻接表头节点，head[i] 是第 i 节课
	priority_queue<node_head> zero_in_deg; //该优先队列存储入度为0的结点
	bool is_sort = false; //这个标志位用于指示是否执行过拓扑排序
public:
	void topological_sort(int constraint); //拓扑排序，constraint 是拓扑排序进行的轮数（一轮排出一门课）
	void add_edge(class_name name, class_num num, class_num prerequisite); //添加一条有向边到图中，num 是该节点的课序号，prerequsite 是先置课程的序号
	friend bool operator<(node_head left, node_head right); //重载<，用于大根堆排序
};

#endif

