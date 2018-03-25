#include "1.h"

int main(int argc,char ** argv)
{
	struct single_link *tmp,*new;

	printf("init a link list:\n");
	initlink(&tmp,10,0);
	printflink(tmp);
	//printf("LEN=%d\n",lenlink(tmp));
	printf("\n");

	printf("insert a node to the 3rd node's left value=9:\n");
	insertlink(tmp,3,-1,9);
	printflink(tmp);
	//printf("LEN=%d\n",lenlink(tmp));
	printf("\n");

	printf("delete the first node from link list:\n");
	deletenode_by_seq(tmp,1);
	printflink(tmp);
	printf("\n");
	//printf("LEN=%d\n",lenlink(tmp));

	printf("reverse the link:\n");
	reverselink(tmp,&new);
	printflink(new);
	printf("\n");
	
}


int initlink(struct single_link **out,int total,int value)
{
	struct single_link *head,*tmp;
	int i;	
	//head ptr
	head = (struct single_link *)malloc(sizeof(struct single_link));
	if(head == NULL)
		{
			printf("malloc error\n");
			return -1;	
		}
	tmp=head;	

	//other nodes
	for(i=1;i<total;i++)
	{
		tmp->next = (struct single_link *)malloc(sizeof(struct single_link));
		if(tmp->next == NULL)		
			{
				printf("malloc error\n");
				return -1;
			}
		tmp->value=value;
		tmp->seq=i;
		tmp=tmp->next;
	}
	//last node
	tmp->seq=i++;	
	tmp->value=value;
	tmp->next=NULL;

	*out=head;
	return 0;
}


int printflink(struct single_link *tmp)
{
	if(tmp==NULL)	return -1;

	while(tmp->next!=NULL)
	{
		printf("|~%p-~|%d|%d|%p|===>",tmp,tmp->seq,tmp->value,tmp->next);
		tmp=tmp->next;
	}
	printf("|~%p~|%d|%d|%p|\n",tmp,tmp->seq,tmp->value,tmp->next);
	return 0;
}

int lenlink(struct single_link *tmp)
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

int insertlink(struct single_link *tmp,int seq,int orient,int value)
{
	struct single_link *head;
	struct single_link *addr;	
	struct single_link *pre;

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
		tmp->next=(struct single_link *)malloc(sizeof(struct single_link));
			if(tmp->next==NULL)
					{
						printf("malloc error");
						return -1;
					}
		tmp->next->value=value;
		tmp->next->next=addr;
	}
	
	else if(orient<0)
	{
		if(seq==1)
		{	
			addr=tmp->next;// 2号节点的地址
			tmp->next=(struct single_link *)malloc(sizeof(struct single_link));	//一号节点指向新节点
					{
						printf("malloc error");
						return -1;
					}
			//这里并不是在一号节点左侧加一个，二是在右侧加一个，然后交换一下值，这样的好处在于使用原有链表地址即可，不改变链表头结点地址
			tmp->next->value=tmp->value;	//一号节点的值给新节点
			tmp->value=value;		//新值给一号节点
			tmp->next->next=addr;	//二号节点的地址给新节点
			goto out;			
		}
		
		addr=tmp;
		pre->next=(struct single_link *)malloc(sizeof(struct single_link));
					{
						printf("malloc error");
						return -1;
					}	
		pre->next->value=value;
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

int deletenode_by_seq(struct single_link *tmp,int seq)
{
	struct single_link *pre,*head,*addr;
	pre=tmp;
	int i=0;
	head=tmp;

	//空指针，退出
	if(tmp==NULL) return -1;

	//为了保证链表引用地址的不变，在删除头结点是，选择将二号节点信息拷贝到头结点的办法，好在使用便捷，不好在从内存层面看，头结点并没有删除
	if(seq==1)
	{
		addr=tmp->next;
		tmp->value=tmp->next->value;
		tmp->next=tmp->next->next;	
		free(addr);
		goto out;
	}

	while(tmp->next!=NULL)
	{
		if(tmp->seq==seq)
		{
			pre->next=tmp->next;
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


int destorylink(struct single_link *tmp)
{
	int i=1,j;
	struct single_link *head,*pre;
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


int sortlink_by_value(struct single_link *tmp,struct single_link *new)
{
	
}

int reverselink(struct single_link *tmp,struct single_link **new)
{
	struct single_link *s,*pre;
	int i=0;

	if(tmp==NULL) return -1;
	pre=NULL;	

	while(tmp->next!=NULL)
	{
		s=tmp->next;
		tmp->next=pre;
		pre=tmp;
		tmp=s;
	}

	tmp->next=pre;
	*new=tmp;

        while(tmp->next!=NULL)
        {
               tmp->seq=++i;
                tmp=tmp->next;
        }
        tmp->seq=++i;

	return 0;
}
