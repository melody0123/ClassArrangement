#include "Graph.h"
#include <cstdlib>

bool operator<(node_head left, node_head right)
{
	return left.weight < right.weight;
}

void Graph::add_edge(class_name name, class_num num, class_num prerequisite)
{
	int class_idx = (num[1] - '0') * 10 + num[2] - '0'; //获得欲添加的课程在 head 数组中的位置
	strcpy(head[class_idx].name, name); //把课程名添加进表头
	head[class_idx].idx = class_idx; //把课程号作为下标写入

	if (strlen(prerequisite))
	{
		head[class_idx].count++; //节点入度++
		int pre_idx = (prerequisite[1] - '0') * 10 + prerequisite[2] - '0'; //获得前置课程在 count 数组中的位置
		head[pre_idx].weight++; //结点出度++
		node_in* cur_ptr = head[pre_idx].next; //在前置课程的邻接表尾部插入当前课程
		if (!cur_ptr)
		{
			//邻接表当前行只有头节点
			head[pre_idx].next = new node_in; //添加新节点
			head[pre_idx].next->class_num = class_idx;
		}
		else
		{
			//邻接表当前行不为空
			while (cur_ptr->next) //寻找尾节点
				cur_ptr = cur_ptr->next;
			cur_ptr->next = new node_in; //添加新节点
			cur_ptr->next->class_num = class_idx;
		}
	}
	return;
}

void Graph::topological_sort(int constraint)
{
	int buffer[30] = { 0 }; //缓冲区，本程序所用拓扑排序与一般拓扑排序不同，该缓冲区用于存储每次新产生的 0 入度结点，在函数结束前将缓冲区内的结点一次性入栈
	int buf_tail = -1; //该缓冲区是队列结构，这个变量用于指示队列尾部

	if (!is_sort) //首次运行
	{
		is_sort = true;
		for (int i = 1; i < 30; i++) //把所有入度为 0 的顶点入栈
			if (head[i].count == 0)
				zero_in_deg.push(head[i]);
	}
		
	while (constraint--) //输出 constraint 个节点
	{
		if (!zero_in_deg.size())
		{
			printf("图中存在回路!\n");
			exit(1);
		}
		else
		{
			node_head temp; //临时变量，用于存储出队元素
			temp = zero_in_deg.top();
			zero_in_deg.pop(); //最大元素出队

			printf("%s ", temp.name); //输出课程名

			node_in* p_front = head[temp.idx].next; //双指针法释放链表空间
			node_in* p_back = head[temp.idx].next;
			while (p_front) //搜索一行邻接表
			{
				p_back = p_front;
				p_front = p_front->next;
				if (--head[p_back->class_num].count == 0) //检查这个结点入度是否为 0
				{
					//count[p_back->data] = top; //入栈
					buffer[++buf_tail] = p_back->class_num; //新的 0 入度结点写入缓冲区
				}
				delete p_back;
			}
		}
	}
	for (int i = 0; i <= buf_tail; i++) //将缓冲区内的结点入栈
	{
		zero_in_deg.push(head[buffer[i]]);
	}

	return;
}

