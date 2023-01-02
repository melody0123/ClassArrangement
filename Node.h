#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS

template<class data_type>
struct node
{
	data_type data; //数据域存数组下标或课程名
	node<int>* next = nullptr; //指针域存指向后继结点的的指针
};

#endif
