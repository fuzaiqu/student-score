#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define PATH "/mnt/hgfs/share-2/project/info"


//定义全局变量
int count = 0;  //统计学生总数
int file_f = 0;  //一开始如果选择了读取那么就值1，默认为0
int check_l = 1;  //判断是否重复读取

//菜单
void menu(int n)
{
	char *opt  = "			欢迎使用学生管理系统			\n";
	char *opt1 = "			1.增加一条学生信息			\n";
	char *opt2 = "			2.查找一条学生信息			\n";
	char *opt3 = "			3.删除一条学生信息			\n";
	char *opt4 = "			4.修改一条学生信息			\n";
	char *opt5 = "			5.显示所有学生信息			\n";
	char *opt6 = "			6.保存数据				\n";
	char *opt7 = "			7.读取数据				\n";
	char *opt8 = "			8.按成绩排序				\n";
	char *opt9 = "			9.退出系统				\n";
	
	system("clear");  //清屏
	printf("\033[44;33m%s\033[1m\033[0m",opt);  //标题不变
	
	if(n == 1)  //选项1为指针
	{
		printf("\033[41m%s\033[0m",opt1);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt1);
	}
	if(n == 2)  ////选项2为指针
	{
		printf("\033[41m%s\033[0m",opt2);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt2);
	}
	if(n == 3)  ////选项3为指针
	{
		printf("\033[41m%s\033[0m",opt3);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt3);
	}
	if(n == 4)  ////选项4为指针
	{
		printf("\033[41m%s\033[0m",opt4);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt4);
	}
	if(n == 5)  ////选项5为指针
	{
		printf("\033[41m%s\033[0m",opt5);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt5);
	}
	if(n == 6)  ////选项6为指针
	{
		printf("\033[41m%s\033[0m",opt6);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt6);
	}
	if(n == 7)  ////选项7为指针
	{
		printf("\033[41m%s\033[0m",opt7);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt7);
	}
	if(n == 8)  ////选项8为指针
	{
		printf("\033[41m%s\033[0m",opt8);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt8);
	}
	if(n == 9)  ////选项8为指针
	{
		printf("\033[41m%s\033[0m",opt9);
	}
	else
	{
		printf("\033[46;37m%s\033[1m\033[0m",opt9);
	}
    printf("\n");
}

//结构体定义
struct stu
{
	int id;
	char name[8];
	char sex[6];
	float score;
	struct stu *next;
};

//结构体初始化
struct stu *new_node()
{
	struct stu *p = (struct stu *)malloc(sizeof(struct stu));
	
	if(p == NULL)
	{
		printf("malloc failure\n");  //开辟空间失败，返回NULL
		return NULL;
	}
	
	p->id = 0;
	memset(p->name , 0 , sizeof(p->name));
	memset(p->sex , 0 , sizeof(p->sex));
	p->score = 0;
	p->next = NULL;
	
	return p;
	
}

//链接成链表
void link(struct stu *p , struct stu *new)
{
	
	new->next = p->next;
	p->next = new;
}

//显示链表内容（学生信息）
void display(struct stu *head)
{
	struct stu *p = head->next;
	
	printf("\033[44;33m\t\t 学生信息\t\t\033[1m\033[0m\n");
	
	while(p != NULL)
	{
		
		printf("\033[43m学号：\033[1m\033[0m%d\n",p->id);
		printf("\033[43m姓名：\033[1m\033[0m%s\n",p->name);
		printf("\033[43m性别：\033[1m\033[0m%s\n",p->sex);
		printf("\033[43m成绩：\033[1m\033[0m%f\n",p->score);
		printf("\033[44m                                        \033[1m\033[0m\n");
		p = p->next;
	}
	
	
}

//检查学号是否重复并返回标记
int check(struct stu *head , struct stu *new , int data)
{
	int f = 0;  //默认学号没有重复
	struct stu *p = head->next;
	
	while(p != NULL)
	{
		
		//地址相同则冲突了，p指向下一个
		if(p == new)
		{
			p = p->next;
		}
		//存在相同学号
		if(p->id == data)
		{
			f = 1;
			break;
		}
		
		p = p->next;
		
	}
	
	return f;
}

//检查是否多次读取
int check_load(struct stu *head)
{
	struct stu *p = head->next;
	if(p != NULL)
	{
		check_l = 0;
	}
	
	return check_l;
}

//查询学号并返回结点地址
struct stu *seek(struct stu *head , int data)
{
	struct stu *p = head->next;
	
	while(p != NULL)
	{
		if(p->id == data)
		{
			return p;  //找到则返回结点
		}
		
		p = p->next;
	}
	
	//未找到相应数据返回空
	return NULL;
}

//删除对应学号的结点
void delete(struct stu *head , struct stu *delete)
{
	struct stu *p = head;
	
	printf("\033[44;33m删除学生信息：\t\t\033[1m\033[0m\n");
	printf("\033[43m学号：\033[1m\033[0m%d\n",delete->id);
	printf("\033[43m姓名：\033[1m\033[0m%s\n",delete->name);
	printf("\033[43m性别：\033[1m\033[0m%s\n",delete->sex);
	printf("\033[43m成绩：\033[1m\033[0m%f\n",delete->score);
	
	//如果p的next不等于delete就找下一条
	while(p->next != delete) 
	{
		p = p->next;
	}
	
	p->next = delete->next;
	delete->next = NULL;
	
	free(delete);  //释放删除的结点，节约空间
}

//修改对应学号的结点
void modify(struct stu *head , struct stu *modify_node)
{
	int f = 0;  //学号标记默认不重复
	
	while(1)
	{
		printf("\033[44;33m修改学生信息：\t\t\033[1m\033[0m\n");
		printf("\033[43m学号：\033[1m\033[0m%d\n",modify_node->id);
		printf("\033[43m姓名：\033[1m\033[0m%s\n",modify_node->name);
		printf("\033[43m性别：\033[1m\033[0m%s\n",modify_node->sex);
		printf("\033[43m成绩：\033[1m\033[0m%f\n",modify_node->score);
		printf("\n");
		
		printf("\033[47;36m请输入学号：\033[1m\033[0m");
		scanf("%d",&modify_node->id);
		while(getchar() != '\n');
		
		if(count > 1)
		{
			f = check(head , modify_node , modify_node->id);  //检查输入的学号是否重复
			if(f == 1)  //学号重复
			{
				//清屏
				system("clear");
				printf("\033[;31m学号重复请重新输入！\033[1m\033[0m\n");
				continue;
			}
		}
		
		printf("\033[47;36m请输入姓名：\033[1m\033[0m");
		scanf("%s",modify_node->name);
		while(getchar() != '\n');
		printf("\033[47;36m请输入性别：\033[1m\033[0m");
		scanf("%s",modify_node->sex);
		while(getchar() != '\n');
		printf("\033[47;36m请输入成绩：\033[1m\033[0m");
		scanf("%f",&modify_node->score);
		while(getchar() != '\n');
		break;
	}
}

//保存数据
void save(struct stu *head)
{
	FILE *fp;
	struct stu *p = head->next;
	
	
	//每次全部保存的时候把之前的内容清空
	fp = fopen(PATH , "w");
	if(fp == NULL)
	{
		perror("open failure");
		return ;
	}
	
	while(p != NULL)
	{
		fwrite(p , sizeof(struct stu) , 1 , fp);
		p = p->next;
	}
	
	fclose(fp);
}

//读取数据
void load(struct stu *head)
{
	FILE *fp;
	int len;
	struct stu *new;
	
	new = new_node();  //先新增一个结点，并初始化
		
	fp = fopen(PATH , "r");
	if(fp == NULL)
	{
		perror("open failure");
		return ;
	}
	
	while(len = fread(new , sizeof(struct stu) , 1 , fp) != 0)
	{	
		
		//每读一个信息就链接一个
		link(head , new);
		
		count++;  //人数+1
		
		//读完一个还要再创建新的结点存储新的数据
		new = new_node();
		
	}
	
	free(new);  //因为最后退出循环会多出一个new
}

//移除结点
void remove_node(struct stu *head, struct stu *delete)
{
	struct stu *p;
	
	if(head == NULL || delete == NULL)
		return;
	
	p = head;   //移动指针在头节点
	//查找delete前面的节点p
	
	while(p->next != delete)
	{
		p = p->next;  //移动p指针
	}
	
	p->next = delete->next;
	delete->next = NULL;
	
}

//按成绩升序排序
void sort_up(struct stu *head)
{
	int num = 0 , i , j;
	struct stu *q , *p = head->next;
	
	
	while(p != NULL)
	{
		num++;  //记录结点个个数
		p = p->next;
	}
	
	p = head->next;
	q = p->next;
	
	for(i=0; i<(num-1); i++)
	{
		for(j=0; j<(num-1-i); j++)
		{
			if(p->score > q->score)  //前面节点数据比后面节点数据大时，则交换节点
			{	
				remove_node(head , p);  //将p解下来
				link(q , p);  //将p插入到q后面
				
				q = p->next;
			}
			else  //不需要移动节点。
			{
				//p q指针分别往后面移动
				q = q->next;
				p= p->next;
			}
		}
		
		p = head->next;
		q = p->next;
	}
	
}

//按成绩降序排序
void sort_down(struct stu *head)
{
	int num = 0 , i , j;
	struct stu *q , *p = head->next;
	
	
	while(p != NULL)
	{
		num++;  //记录结点个个数
		p = p->next;
	}
	
	p = head->next;
	q = p->next;
	
	for(i=0; i<(num-1); i++)
	{
		for(j=0; j<(num-1-i); j++)
		{
			if(p->score < q->score)  //前面节点数据比后面节点数据小时，则交换节点
			{	
				remove_node(head , p);  //将p解下来
				link(q , p);  //将p插入到q后面
				
				q = p->next;
			}
			else  //不需要移动节点。
			{
				//p q指针分别往后面移动
				q = q->next;
				p= p->next;
			}
		}
		
		p = head->next;
		q = p->next;
	}
	
}

int main()
{
	
	FILE *fp;
	
	int option , point = 1 , menu_option;  //UI界面变量
	int num , f , verify , verif;  //num判断输入学号是否重复，f判断是否继续输入，verify确认是否执行操作，verif不执行的标志
	int id;  //输入要进行判断的学号id
	struct stu *head ,*new , *seek_node , *delete_node , *modify_node , *p;
	int choice;
	
	while(1)
	{
		
		//显示主界面
		switch(point)
		{
			case 1:
				menu(point);
				break;
			
			case 2:
				menu(point);
				break;
			
			case 3:
				menu(point);
				break;
			
			case 4:
				menu(point);
				break;
			
			case 5:
				menu(point);
				break;
				
			case 6:
				menu(point);
				break;
			
			case 7:
				menu(point);
				break;
			
			case 8:
				menu(point);
				break;
			
			case 9:
				menu(point);
				break;
		}
		
		//按键回馈
		system("stty -echo");
		system("stty -icanon");
		option = getchar();
		system("stty icanon");
		system("stty echo");
		
		switch(option)
		{
			case 'A':
				point--;  //往上移动
				if(point < 1)
				{
					point = 9;
				}
				break;
			
			case 'B':
				point++;  //往下移动
				if(point > 9)
				{
					point = 1;
				}
				break;
			
			case 10:
				switch(point)
				
				{
					//增加一条学生信息
					case 1:
						
						f = 0;
						//清屏
						system("clear");
						
						
						while(f != 1)
						{
							
							if(file_f == 0)
							{
								head = new_node();  //创建一个头结点
								if(head == NULL)
								{
									perror("malloc failure:");  //头结点创建失败，退出程序
								}
								
								file_f = 1;  //创建了头结点就值1避免多次创建
							}
							
							new = new_node();  //创建一个新结点
							if(new == NULL)
							{
								printf("create failure\n");
								break;
							}
							
							while(1)
							{
								
								printf("\033[43;35m\t\t输入学生信息\t\t\033[1m\033[0m\n");
								
								printf("\033[47;36m请输入学号：\033[1m\033[0m");
								scanf("%d",&new->id);
								while(getchar() != '\n');
								
								//判断输入学号是否重复
								if(count > 0)
								{
									num = check(head , new ,new->id);
									if(num == 1)
									{
										//清屏
										system("clear");
										printf("\033[;31m学号重复请重新输入！\033[1m\033[0m\n");
										continue;
									}
								}
								
								printf("\033[47;36m请输入姓名：\033[1m\033[0m");
								scanf("%s",new->name);
								while(getchar() != '\n');
								printf("\033[47;36m请输入性别：\033[1m\033[0m");
								scanf("%s",new->sex);
								while(getchar() != '\n');
								printf("\033[47;36m请输入成绩：\033[1m\033[0m");
								scanf("%f",&new->score);
								while(getchar() != '\n');
								
								//插入新结点
								link(head,new);
								printf("\033[;34m添加成功！\033[1m\033[0m\n\n");
								count++;
								
								display(head);  //输入完之后显示一下输入的学生信息
								
								printf("\n\033[44;36m按1返回主菜单，按其它键继续输入：\033[1m\033[0m");
								scanf("%d",&menu_option);
								while(getchar() != '\n');
								if(menu_option == 1)
								{
									f = 1;
									break;
								}
								else 
								{
									new = new_node();  //创建一个新结点
									if(new == NULL)
									{
										printf("create failure\n");
										break;
									}
									continue;
								}
							}
						}
						break;
					
					//查找一条学生信息
					case 2:
						
						//清屏
						system("clear");
						
						if(count == 0)
						{
							printf("\033[;31m无数据，查找失败！\033[1m\033[0m\n");
							while(getchar() != '\n');
							break;
						}
						
						printf("\033[47;36m请输入学号：\033[1m\033[0m");
						scanf("%d",&id);
						while(getchar() != '\n');
						seek_node = seek(head , id);
						if(seek_node == NULL)
						{
							printf("\033[;31m查无此人！\033[1m\033[0m\n");
							while(getchar() != '\n');
							break;
						}
						
						printf("\033[44;33m\t\t 学生信息\t\t\033[1m\033[0m\n");
						printf("\033[43m学号：\033[1m\033[0m%d\n",seek_node->id);
						printf("\033[43m姓名：\033[1m\033[0m%s\n",seek_node->name);
						printf("\033[43m性别：\033[1m\033[0m%s\n",seek_node->sex);
						printf("\033[43m成绩：\033[1m\033[0m%f\n",seek_node->score);
						printf("\033[44m                                        \033[1m\033[0m\n");
						
						while(getchar() != '\n');
						//system("pause");
						break;
					
					//删除一条学生信息
					case 3:
						
						//清屏
						system("clear");
						
						if(count == 0)
						{
							printf("\033[;31m无数据，删除失败！\033[1m\033[0m\n");
							while(getchar() != '\n');
							break;
						}
						
						while(1)
						{
							verif = 1; //标记默认为“执行”
							
							printf("\033[47;36m请输入学号：\033[1m\033[0m");
							scanf("%d",&id);
							delete_node = seek(head , id);  //查找到要删除的结点的地址
							if(delete_node == NULL)  //判断要删除的结点是否为空
							{
								printf("\033[;31m查无此人,无法删除\033[1m\033[0m\n");
								printf("\033[;31m请重新输入！\033[1m\033[0m\n");
								continue;
							}
							
							printf("\033[44;36m确认删除（输入1确认，按其他键取消）？：\033[1m\033[0m");
							scanf("%d",&verify);
							while(getchar() != '\n');
							if(verify == 1)  //确认删除
							{
								delete(head , delete_node);  //删除结点								
								printf("\033[;34m删除成功！\033[1m\033[0m\n");
							}
							else
							{
								verif = 0;  //不执行则赋0
							}
							
							if(verif == 0)  //当verif等于0则返回主界面
							{
								break;
							}
							
							while(getchar() != '\n');
							while(getchar() != '\n');
							break;
						}
						break;
					
					//修改一条学生信息
					case 4:
						
						//清屏
						system("clear");
						
						if(count == 0)
						{
							printf("\033[;31m无数据，修改失败！\033[1m\033[0m\n");
							while(getchar() != '\n');
							break;
						}
						
						while(1)
						{	
							verif = 1;  //标记默认为“执行”
							
							printf("\033[47;36m请输入学号：\033[1m\033[0m");
							scanf("%d",&id);
							modify_node = seek(head , id);  //查找到要删除的结点的地址
							if(modify_node == NULL)  //判断要修改的结点是否为空
							{
								printf("\033[;31m查无此人,无法修改\033[1m\033[0m\n");
								printf("\033[;31m请重新输入！\033[1m\033[0m\n");
								continue;
							}
							
							printf("\033[44;33m修改学生信息：\t\t\033[1m\033[0m\n");
							printf("\033[43m学号：\033[1m\033[0m%d\n",modify_node->id);
							printf("\033[43m姓名：\033[1m\033[0m%s\n",modify_node->name);
							printf("\033[43m性别：\033[1m\033[0m%s\n",modify_node->sex);
							printf("\033[43m成绩：\033[1m\033[0m%f\n",modify_node->score);
							printf("\n");
							
							printf("\033[44;36m确认修改（1.确认，按其他键取消）？：\033[1m\033[0m");
							scanf("%d",&verify);
							while(getchar() != '\n');
							
							if(verify == 1)  //确认是否修改
							{
								modify(head , modify_node);  //修改结点信息
								printf("\033[;34m修改成功！\033[1m\033[0m\n");
							}
							else
							{
								verif = 0;  //不执行则赋0
							}
							
							if(verif == 0)  //当verif等于0则返回主界面
							{
								break;
							}
							
							while(getchar() != '\n');
							//while(getchar() != '\n');
						    break;
						}
						break;
					
					//显示所有学生信息
					case 5:
						
						//while(getchar() != '\n');
						//清屏
						system("clear");
						
						if(count == 0)
						{
							printf("\033[;31m无数据，显示失败！\033[1m\033[0m\n");
							while(getchar() != '\n');
							break;
						}
						
						//显示所有学生信息
						display(head);
						while(getchar() != '\n');
						
						break;
					
					//保存数据
					case 6:
						
						if(count == 0)
						{
							printf("\033[;31m无数据，保存失败！\033[1m\033[0m\n");
							while(getchar() != '\n');
							break;
						}
						save(head);
						printf("\033[;34m保存成功！\033[1m\033[0m\n");
						while(getchar() != '\n');
						
						break;
					
					//读取数据
					case 7:
						
						if(file_f == 0)
							{
								head = new_node();  //创建一个头结点
								if(head == NULL)
								{
									perror("malloc failure:");  //头结点创建失败，退出程序
								}
								
								file_f = 1;  //创建了头结点就值1避免多次创建
							}
						
						check_l = check_load(head);
						if(check_l == 0)
						{
							//清屏
							system("clear");
							
							printf("\033[;31m有数据正在进行，禁止继续读取！\033[1m\033[0m\n");
							while(getchar() != '\n');
							break;
						}
						
						load(head);
						printf("\033[;34m读取成功！\033[1m\033[0m\n");
						while(getchar() != '\n');
						break;
					
					//按成绩排序
					case 8:
						
						if(count == 0)
						{
							printf("\033[;31m无数据，排序失败！\033[1m\033[0m\n");
							while(getchar() != '\n');
							break;
						}
						
						printf("\033[44;36m请输入升序或降序排列（1、升序 2、降序）：\033[1m\033[0m");
						scanf("%d",&choice);
						
						if(choice == 1)
						{	
							sort_up(head);
						}
						else if(choice == 2)
						{
							sort_down(head);
						}
						else
						{
							printf("\033[;31m输入有误！\033[1m\033[0m\n");
							break;
						}
						printf("\033[;34m排序成功！\033[1m\033[0m\n");
						while(getchar() != '\n');
						while(getchar() != '\n');
						break;
					
					//退出系统
					case 9:
						
						//退出系统
						exit(0);
						
						break;
				}
			break;
		}
	}
	
}