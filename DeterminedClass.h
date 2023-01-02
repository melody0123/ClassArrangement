#ifndef DETERMINEDCLASS_H_INCLUDED
#define DETERMINEDCLASS_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS

#include "ClassInfo.h"
#include <cstring>

struct node_this //这种结点仅在本文件内使用
{
	class_name data = { '\0' }; //课程名称
	node_this* next = nullptr; //下一节点的指针
};

struct ClassTable
{
	node_this head[10]; //表头，head[i] 上挂的是第 i + 1 学期的课

	void push_back(int term, class_name name) //尾插法
	{
		node_this* tmp_ptr = &head[term];
		while (tmp_ptr->next)
			tmp_ptr = tmp_ptr->next; //寻找尾节点
		tmp_ptr->next = new node_this; //开辟新空间
		strcpy(tmp_ptr->next->data, name);
	}

	void pop_back(int term, class_name name) //尾部弹出一个结点
	{
		node_this* tmp_ptr = &head[term];
		node_this* tmp_ptr_previous = tmp_ptr;
		while (tmp_ptr->next)
		{
			tmp_ptr_previous = tmp_ptr;
			tmp_ptr = tmp_ptr->next; //找尾节点
		}
		if (tmp_ptr != &head[term])
		{
			strcpy(name, tmp_ptr->data); //取出课程名
			if (tmp_ptr != &head[term])
			{
				delete tmp_ptr; //释放空间
				tmp_ptr_previous->next = nullptr; //防止野指针
			}
		}
	}

	bool empty(int term)
	{
		return (bool)(!(head[term].next));
	}
};

#endif // !DETERMINEDCLASS_H_INCLUDED
