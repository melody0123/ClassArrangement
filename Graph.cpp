#include "Graph.h"

void Graph::add_edge(class_name name, class_num num, class_num prerequisite)
{
	int class_idx = (num[1] - '0') * 10 + num[2] - '0'; //获得欲添加的课程在 count 数组中的位置
	if (!count[class_idx])
		strcpy(head[class_idx].data, name); //把课程名添加进表头
	if (strlen(prerequisite))
	{
		count[class_idx]++; //节点入度++
		int pre_idx = (prerequisite[1] - '0') * 10 + prerequisite[2] - '0'; //获得前置课程在 count 数组中的位置
		node<int>* cur_ptr = head[pre_idx].next; //在前置课程的邻接表尾部插入当前课程
		if (!cur_ptr)
		{
			//邻接表当前行只有头节点
			head[pre_idx].next = new node<int>; //添加新节点
			head[pre_idx].next->data = class_idx;
		}
		else
		{
			//邻接表当前行不为空
			while (cur_ptr->next) //寻找尾节点
				cur_ptr = cur_ptr->next;
			cur_ptr->next = new node<int>; //添加新节点
			cur_ptr->next->data = class_idx;
		}
	}
	return;
}

void Graph::topological_sort(int constraint)
{
	if(top == -1) //首次运行
		for (int i = 1; i < 30; i++) //把所有入度为 0 的顶点入栈
		{
			if (count[i] == 0)
			{
				count[i] = top;
				top = i;
			}
		}
	while (constraint--) //输出 constraint 个节点
	{
		if (top == -1)
			printf("图中存在回路!\n");
		else
		{
			int j = top;
			top = count[top]; //退栈
			printf("%s ", head[j].data); //输出课程名

			node<int>* p_front = head[j].next; //双指针法释放链表空间
			node<int>* p_back = head[j].next;
			while (p_front) //搜索一行邻接表
			{
				p_back = p_front;
				p_front = p_front->next;
				if (--count[p_back->data] == 0) //检查这个结点入度是否为 0
				{
					count[p_back->data] = top; //入栈
					top = p_back->data;
				}
				delete p_back;
			}
		}
	}

	return;
}

Graph::Graph()
{
	top = -1;
	memset(count, 0, sizeof(count));
	for (int i = 0; i < 30; i++)
	{
		memset(head[i].data, 0, sizeof(head[i].data));
	}
}

