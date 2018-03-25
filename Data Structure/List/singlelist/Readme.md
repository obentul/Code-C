- 单向链表

- 1.c  源码  
  1.h  头文件  
  Note.md  知识点  

- 使用: gcc 1.c 1.h -o 1  

- TODO: 通过入参控制使用哪个接口做测试，而不是需要重复修改和编译源文件来跳转分支  

- 方法列表:  
//finished  
int initlink(struct single_link **out,int total,int value);	//初始化一个链表，一共total个，每个的值都是value  
int printflink(struct single_link *tmp);			//打印链表  
int lenlink(struct single_link * tmp);				//求总长度  
int insertlink(struct single_link *tmp,int seq,int orient,int value);		//插入到seq的node点,orient为正,则入右边,负入左边,0替换,value为值  
int deletenode_by_seq(struct single_link *tmp,int seq);		//删除序号为seq的node  
int destorylink(struct single_link *tmp);			//摧毁整个链表  
int reverselink(struct single_link *tmp,struct single_link **new);	//翻转链表  
//todo  
int deletenode_by_value(struct single_link *tmp,int value);	//删除所有值为value的节点
int sortlink(struct single_link *tmp,struct single_link *new,int orient);	//按value值的大小重新排序,orient为正,则从大到小,负从小到大,0刷新序列

- 2.c 第二版

