#include "ClassAssignment.h"
#include <cstdlib>
#include<cstring>

void ClassAssignment::run()
{
	printf("请输入课程信息文件的路径：");
	char path[256];
	scanf("%s", path);

	FILE* in_fp; //打开文件
	if (!(in_fp = fopen(path, "r")))
	{
		printf("文件打开失败！\n");
		exit(1);
	}

	int num_of_class[8] = { 0 }; //读入每学期要排的课的数量
	for (int i = 0; i < 8; i++)
		fscanf(in_fp, "%d", &num_of_class[i]);

	//下面逐行处理排课信息
	for (int i = 0; i < 38; i++) //38 行排课信息
	{
		//先定义一些临时变量
		class_num num = { '\0' }; //课程号
		class_name name = { '\0' }; //课程名
		int time = 0; //课时
		int term = -1; //开课学期
		class_num prerequisite = { '\0' }; //前置课程课程号
		fscanf(in_fp, "%s%s%d%d", num, name, &time, &term); //把除了前置课程以外的信息读入内存
		if (term)
		{
			//已经规定了开课学期
			class_table.push_back(term, name); //添加课程信息
		}
		else
		{
			//未规定开课学期
			int temp_c = 0; //一个临时的变量，用于存储 fgetc 返回的字符
			bool no_constraint = true; //这个标志位用于标识该课程是否存在前置课程
			class_num temp_num = { '\0' }; //这个临时变量用于存储前置课程的课程号
			while ((temp_c = fgetc(in_fp)) != '\n' && !feof(in_fp)) //跳过空白字符，直至读到一个'c'或者换行符
			{
				if (temp_c == 'c')
				{
					no_constraint = false; //读到了一个前置条件，标志位置为 false
					ungetc(temp_c, in_fp); //把这个字符放回去
					fscanf(in_fp, "%s", temp_num); //把这个前置课程的课程号读进内存
					graph.add_edge(name, num, temp_num); //把这条边加进去
				}
				else //读到了空白字符
					continue;
			}
			if (no_constraint) //检查标志位的情况
			{
				graph.add_edge(name, num, temp_num);
			}
		}
	}
	//下面进行排课，先排安排了学期的课程，再排没有安排学期的课程
	for (int i = 1; i <= 8; i++)
	{
		printf("第 %d 学期:", i);

		//安排了学期的课程
		class_name tmp_name = { '\0' };
		while (!class_table.empty(i))
		{
			class_table.pop_back(i, tmp_name); //取出课程名
			printf("%s ", tmp_name); //显示课程名
			num_of_class[i - 1]--; //计数器自减
		}
		//未安排学期的课程，拓扑排序
		graph.topological_sort(num_of_class[i - 1]);
		num_of_class[i - 1] = 0;
		
		printf("\n");
	}
}
