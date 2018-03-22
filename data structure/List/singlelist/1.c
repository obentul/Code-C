#include "1.h"

int main(int argc,char ** argv)
{
	struct single_link *tmp,*new;

	initlink(&tmp,10,0);
	printflink(tmp);
	printf("LEN=%d\n",lenlink(tmp));

	insertlink(tmp,1,-1,9);
	printflink(tmp);
	printf("LEN=%d\n",lenlink(tmp));

	deletenode_by_seq(tmp,1);
	printflink(tmp);
	printf("LEN=%d\n",lenlink(tmp));

	reverselink(tmp,&new);
	printflink(new);
	
}


int initlink(struct single_link **out,int total,int value)
{
	struct single_link *head,*tmp;
	int i;	
	//head node
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
		printf("|%p|%d|%d|----->",tmp->next,tmp->value,tmp->seq);
		tmp=tmp->next;
	}
	printf("|NULL|%d|%d|\n",tmp->value,tmp->seq);
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
		tmp->next->value=value;
		tmp->next->seq=0;
		tmp->next->next=addr;
	}
	
	else if(orient<0)
	{
		if(seq==1)
		{	
			addr=tmp->next;// 2号节点的地址
			tmp->next=(struct single_link *)malloc(sizeof(struct single_link));	//一号节点指向新节点
			tmp->next->value=tmp->value;	//一号节点的值给新节点
			tmp->value=value;		//新值给一号节点
			tmp->next->next=addr;	//二号节点的地址给新节点
			goto out;			
		}
		
		addr=tmp;
		pre->next=(struct single_link *)malloc(sizeof(struct single_link));
		pre->next->value=value;
		pre->next->seq=0;
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
	struct single_link *a,*b,*s;

	if(tmp==NULL) return -1;

	
/*	有问题，还需要重新实现
	s=tmp->next->next;
	tmp->next->next=tmp;
	tmp->next=NULL;
		
	tmp=tmp->next;
*/
	while(tmp->next!=NULL)
	{
		s=tmp->next->next;
		tmp->next->next=tmp;
		tmp=tmp->next;
	}
	
	*new=tmp;

	return 0;
}
