#include "1.h"

int main(int argc,char ** argv)
{
	struct double_link *tmp;
	initlink(&tmp,5,8);
	printflink(tmp);
	printf("%d\n",lenlink(tmp));
	printf("\n");
	
	printf("insert a node to the 3rd node's left value=9:\n");
	insertlink(tmp,3,-1,9);
	printflink(tmp);
	//printf("LEN=%d\n",lenlink(tmp));
	printf("\n");
	
	printf("insert a node to the 1st node's left value=9:\n");
	insertlink(tmp,1,-1,9);
	printflink(tmp);
	//printf("LEN=%d\n",lenlink(tmp));
	printf("\n");
	
	printf("delete the first node from link list:\n");
	deletenode_by_seq(tmp,1);
	printflink(tmp);
	printf("\n");
	
	return 0;
}

int initlink(struct double_link **out,int total,int value)
{
	struct double_link *tmp,*head,*pre;
	int i=1;
	
	//head
	tmp=(struct double_link *)malloc(sizeof(struct double_link));
	if(tmp==NULL)
			{
				printf("malloc error\n");
				return -1;	
			}
	tmp->next=NULL;
	tmp->pre=NULL;
	tmp->value=value;
	tmp->seq=i;
	pre=tmp;
	
	head=tmp;
	
	//others
	for(i=2;i<total+1;i++)
		{
			tmp = (struct double_link *)malloc(sizeof(struct double_link));
			if(tmp==NULL)
				{
					printf("malloc error\n");
					return -1;
				}
			pre->next = tmp;
			tmp->pre = pre;
			tmp->next = NULL;
			tmp->value = value;
			tmp->seq = i;
			pre = tmp;
		}
	
	*out=head;
	return 0;
		
}

int printflink(struct double_link *tmp)
{
	if(tmp==NULL)	return -1;

	while(tmp->next!=NULL)
	{
		printf("|~%p~|%p|%d|%d|%p|<===>",tmp,tmp->pre,tmp->seq,tmp->value,tmp->next);
		tmp=tmp->next;
	}
	printf("|~%p~|%p|%d|%d|%p|\n",tmp,tmp->pre,tmp->seq,tmp->value,tmp->next);

	return 0;
}

int lenlink(struct double_link * tmp)
{
	int i=1;

	if(tmp==NULL) return -1;

	while(tmp->next!=NULL)
	{
		tmp=tmp->next;
		i++;
	}
	
	return i;
}


int insertlink(struct double_link *tmp,int seq,int orient,int value)
{
	struct double_link *head;
	struct double_link *addr;	
	struct double_link *pre;

	head=tmp;

	int i=0;
	
	if(tmp==NULL)	return -1;
	
	while(tmp->seq!=seq)
	{	
		pre=tmp;
		tmp=tmp->next;
	}
	
	if(orient>0)
		{
			addr=tmp->next;	
			tmp->next=(struct double_link *)malloc(sizeof(struct double_link));
			if(tmp->next==NULL)
					{
						printf("malloc error");
						return -1;
					}
			tmp->next->value=value;
			tmp->next->next=addr;
			tmp->next->pre=tmp;
			addr->pre=tmp->next;
		}
	
	else if(orient<0)
	{
		if(seq==1)
		{	
			addr=tmp->next;// 2号节点的地址
			tmp->next=(struct double_link *)malloc(sizeof(struct double_link));	//一号节点指向新节点
			if(tmp->next==NULL)		
					{
						printf("malloc error");
						return -1;
					}
			//这里并不是在一号节点左侧加一个，二是在右侧加一个，然后交换一下值，这样的好处在于使用原有链表地址即可，不改变链表头结点地址
			tmp->next->value=tmp->value;	//一号节点的值给新节点
			tmp->value=value;		//新值给一号节点
			
			tmp->next->next=addr;
			tmp->next->pre=tmp;	//二号节点的地址给新节点
			addr->pre=tmp->next;
			goto out;			
		}
		
		addr=tmp;
		pre->next=(struct double_link *)malloc(sizeof(struct double_link));
			if(tmp->next==NULL)		
					{
						printf("malloc error");
						return -1;
					}	
		pre->next->value=value;

		pre->next->pre=pre;
		tmp->pre=pre->next;
		pre->next->next=addr;
	}
	
	else if(orient==0)
	{
		tmp->value=value;
	}
	
out:
	while(head->next!=NULL)
	{
		head->seq=++i;
		head=head->next;
	}
	head->seq=++i;
	
	return 0;
}



int deletenode_by_seq(struct double_link *tmp,int seq)
{
	struct double_link *pre,*head,*addr;
	pre=tmp;
	int i=0;
	head=tmp;

	//空指针，退出
	if(tmp==NULL) return -1;

	//为了保证链表引用地址的不变，在删除头结点时，选择将二号节点信息拷贝到头结点的办法，好在使用便捷，不好在从内存层面看，头结点并没有删除
	if(seq==1)
	{
		addr=tmp->next;
		tmp->value=addr->value;
		tmp->next=addr->next;
		addr->next->pre=tmp;
		free(addr);
		goto out;
	}

	while(tmp->next!=NULL)
	{
		if(tmp->seq==seq)
		{
			pre->next=tmp->next;
			tmp->next->pre=pre;
			free(tmp);
			goto out;
		}
		pre=tmp;
		tmp=tmp->next;
	}

	//最后一个节点
	if((tmp->next==NULL)&&(tmp->seq==seq))
	{
		pre->next=NULL;
		free(tmp);
	}	

out:
	//重置序列号
	while(head->next!=NULL)
	{
		head->seq=++i;
		head=head->next;
	}
	head->seq=++i;

	return 0;
}


int destorylink(struct double_link *tmp)
{
	int i=1,j;
	struct double_link *head,*pre;
	head=tmp;

        if(tmp==NULL) return -1;

        while(tmp->next!=NULL)
        {
                tmp=tmp->next;
                i++;
        }

	tmp->next=head;	//链表首位相连，防止coredump
	for(j=0;j<i;j++)
	{
		pre=head;
		head=head->next;
		free(pre);
	}
       return 0;
}