#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS

#include "ClassInfo.h"
struct node_in
{
	int class_num = 0; //数据域存储课程号
	node_in* next = nullptr; //指针域存指向后继结点的的指针
};

struct node_head
{
	class_name name = { '\0' }; //数据域存课程名
	int idx = 0; //存该结点在数组中的下标，结点出队后用这个下标访问该节点在数组中的位置
	int count = 0; //数据域存储该结点的入度
	int weight = 0; //存储出度
	node_in* next = nullptr; //指针域存指向后继结点的的指针
};

#endif
