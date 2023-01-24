#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef struct process_queue
{
	int process_id;
	int k;
	int timestamp;
	int burst_time;
	int memory_req;
	int priority;
	int status; 
	struct process_queue *next;
}process_q;
typedef struct alloc_memoryblock
{
	int block_id;
	int block_size;
	int memory_used;
	int allocated_status;
	int process_id;
	struct alloc_memoryblock *next;
}alloc;
process_q *pq;
alloc *a;
typedef enum{FALSE,TRUE}boolean;
process_q *makenode(int process_id,int timestamp,int burst_time,int memory_req,int priority,int status);
void insert(int process_id,int timestamp,int burst_time,int memory_req,int priority,int status);
void delete();
void bubbleSort(process_q** pq,int count);
process_q * swap(process_q *a, process_q *b);
void initialise();
void firstfit(int memory,int processid);
void bestfit(int memory,int processid);
void delete(int processid);
void display();
alloc* reverseList(alloc *head)
{
    if(head==NULL||head->next==NULL)
    {
        return head;
    }
    alloc *prev,*curr,*later;
    prev=NULL;
    curr=head;
    later=head;
    while(later!=NULL)
    {
        later=later->next;
        curr->next=prev;
        prev=curr;
        curr=later;
    }
    head=prev;
}
void initialise()
{
	int n;
	FILE* fp=fopen("input2.txt","r");
	fscanf(fp,"%d",&n);
	printf(" memory blocks : %d\n",n);
	alloc *nptr,*ptr;
	int i;
	for(i=0;i<n;i++)
	{
		nptr=(alloc*)malloc(sizeof(alloc));
		if(a==NULL)
		{
			nptr->block_id=i+1;
			fscanf(fp,"%d",&nptr->block_size);
			printf(" the block size :%d\n",nptr->block_size);
			nptr->allocated_status=0;
			a=nptr;
			nptr->next=NULL;
		}
		else
		{
			nptr->block_id=i+1;
			fscanf(fp,"%d",&nptr->block_size);
			printf(" the block size :%d\n",nptr->block_size);
			nptr->allocated_status=0;
			nptr->next=a;
			a=nptr;                                            
		}
	}
	fclose(fp);
	a=reverseList(a);
}


void firstfit(int memory,int processid)
{
	alloc *ptr;
	ptr=a;
	int p=0;
	
	while(ptr->next!=NULL&&p==0)
	{
		if(ptr->allocated_status==0&&memory<=ptr->block_size)
		{
			ptr->process_id=processid;
			ptr->memory_used=memory;
			ptr->allocated_status=1;
			p=1;
		}	
		else
		{
			ptr=ptr->next;
		}
	}
	if(p==0)
	{
		printf("no enough space\n");
	}
	
	
}
void bestfit(int memory,int processid)
{
	alloc *ptr,*temp;
	ptr=a;
	int p=0;
	int min=1000;
	while(ptr!=NULL)
	{
		

		if(min>=ptr->block_size&&ptr->allocated_status==0&&memory<=ptr->block_size)
		{
		
			temp=ptr;
			min=ptr->block_size;
			p=1;
		}
		ptr=ptr->next;
		
		
	}
	temp->memory_used=memory;
	temp->process_id=processid;
	temp->allocated_status=1;
	if(p==0)
	{
		printf("no enough space\n");
	}
}

void delete(int processid)
{
	alloc *ptr;
	ptr=a;
	while(ptr!=NULL)
	{
		if(processid==ptr->process_id)
		{
			ptr->allocated_status=0;
			ptr->memory_used=0;
			ptr->process_id=-1;
		}
		ptr=ptr->next;
	}
}


void display()
{
	alloc *ptr;
	ptr=a;
	int numberoffreeblocks;
	while(ptr!=NULL)
	{
		
		if(ptr->allocated_status==0)
		{
			printf("--------------------------------\n");
			printf("the free blocks are :\n");
			printf("block id is %d\n",ptr->block_id);
			printf("block size is %d\n",ptr->block_size);
			numberoffreeblocks++;
		}
		else
		{
			printf("-----------------------------------------------\n");
			printf("the allocated blocks are :\n");
			printf("block id %d contains process_id %d ------ %d\n",ptr->block_id,ptr->process_id,ptr->block_size);
		}
		ptr=ptr->next;
		
	}
	printf("no of free blocks are %d\n",numberoffreeblocks);
}




process_q *makenode(int process_id,int timestamp,int burst_time,int memory_req,int priority,int status)
{
	process_q *nptr;
	nptr=(process_q*)malloc(sizeof(process_q));
	if(nptr!=NULL)
	{
		nptr->process_id=process_id;
		nptr->timestamp=timestamp;
		nptr->burst_time=burst_time;
		nptr->memory_req=memory_req;
		nptr->priority=priority;
		nptr->status=status;
		nptr->k=0;
		nptr->next=NULL;
	}
	else
	{
		
		printf("no node created");
	}
}

void insert(int process_id,int timestamp,int burst_time,int memory_req,int priority,int status)
{
	process_q *nptr=makenode(process_id,timestamp,burst_time,memory_req,priority,status);
	process_q *ptr;
	ptr=pq;
	if(pq==NULL)
	{
		pq=nptr;
	}
	else
	{
		while(ptr->next!=NULL)
		{
			ptr=ptr->next;
		}
		ptr->next=nptr;
	}
}
void deleteprocess()
{

	process_q *ptr;

	ptr=pq;

	pq=pq->next;

	ptr->next=NULL;

}

process_q* swap(process_q* ptr1, process_q* ptr2) 
{ 
    process_q* tmp = ptr2->next; 
    ptr2->next = ptr1; 
    ptr1->next = tmp; 
    return ptr2; 
} 
  

void bubbleSort(process_q** head, int count) 
{ 
    process_q** h; 
    int i, j, swapped; 
  
    for (i = 0; i <= count; i++) 
    { 
  
        h = head; 
        swapped = 0; 
  
        for (j = 0; j < count - i - 1; j++)  
        { 
  
            process_q* p1 = *h; 
            process_q* p2 = p1->next; 
  
            if (p1->priority > p2->priority) 
            { 
  
               
                *h = swap(p1, p2); 
                swapped = 1; 
            } 
  
            h = &(*h)->next; 
        } 
  
       
        if (swapped == 0) 
            break; 
    } 
}
int main()
{
	int time=0,sum=0,choice,p;
	int a1=0,n,i,m=0;
	int process_id,timestamp,burst_time,memory_req,priority,status;
	process_q *temp,*pq1,*ptr,*ptr1;
	
	
	initialise();
	
	FILE* fp=fopen("input1.txt","r");
	
		while(time<=sum)
		{
			
			fscanf(fp,"%d",&n);
			printf("no. of processes %d\n",n);
			m=m+n;
			for(i=0;i<n;i++)
			{
				fscanf(fp,"%d",&process_id);
				printf(" the process_id is : %d\n",process_id);
				fscanf(fp,"%d",&timestamp);
				printf(" the timestamp is : %d\n" ,timestamp);
				fscanf(fp,"%d",&burst_time);
				printf(" the burst_time is : %d\n",burst_time);
				fscanf(fp,"%d",&memory_req);
				printf("the memory_req is : %d \n",memory_req);	
				fscanf(fp,"%d",&priority);
				printf("the priority is : %d \n",priority);
				fscanf(fp,"%d",&status);
				printf("the status is : %d\n",status);
				printf("enter ur choice(1/2)    :  ");
				printf("1.first fit     2.best fit \n");
				scanf("%d",&choice);
				if(choice==1)
				{
					firstfit(memory_req,process_id);
				}
				else
				{
					bestfit(memory_req,process_id);
				}
				sum=sum+burst_time;
				insert(process_id,timestamp,burst_time,memory_req,priority,status);
			}
		
		
		
			bubbleSort(&pq,m);
	
			ptr=pq;
			ptr1=pq;
		
			if(ptr->k==1&&ptr->status==3)
			{
				printf("enter ur choice\n");
				printf("1.first fit \n 2.best fit");
				scanf("%d",&choice);
				if(choice==1)
				{
					firstfit(ptr->memory_req,ptr->process_id);
				}
				else
				{
					bestfit(ptr->memory_req,ptr->process_id);
				}
			}
			if((ptr)->burst_time!=0)
			{
				if((ptr==temp))
				{
					(ptr)->burst_time--;
					printf("running process at time  %d is %d\n",time,(ptr)->process_id);
				}
				else 
				{
					if(time!=0)
					{
						temp->status=3;
						delete(temp->process_id);
						temp->k=1;
					}
					(ptr)->status=2;
					(ptr)->burst_time--;
					printf("running process at time  %d is %d\n",time,(ptr)->process_id);
				}
			
			}
			if((ptr)->burst_time==0)
			{
			
				(ptr)->status=4;
				printf("completed process at time  %d is %d\n",time,(ptr)->process_id);
				delete(ptr->process_id);
				deleteprocess();
				m=m-1;
			}
			ptr1=pq;
			while((ptr1)!=NULL)
			{
				if(time!=0&&(time-(ptr1)->timestamp)%30==0)
				{
					(ptr1)->priority=(ptr1)->priority-1;
				}
				(ptr1)=(ptr1)->next;
			}
			display();
			temp=ptr;
			time++;	
			printf("------------------------------------------------------------------\n");
		}
		fclose(fp);
} 

































