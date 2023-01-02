#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS

#include "Node.h"
#include "ClassInfo.h"
#include <cstring>
#include <cstdio>


class Graph
{
private:
	int count[30]; //count[i] 用于指示第 i 个节点的入度
	node<class_name> head[30]; //邻接表头节点，head[i] 是第 i 节课
	int top; //栈顶指针

public:
	void topological_sort(int constraint); //拓扑排序，constraint 是拓扑排序进行的轮数（一轮排出一门课）
	void add_edge(class_name name, class_num num, class_num prerequisite); //添加一个节点到图中，num 是该节点的课序号，prerequsite 是先置课程的序号
	Graph(); //构造函数
	~Graph(){} //析构函数
};

#endif

