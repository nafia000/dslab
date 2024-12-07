#include<stdio.h>
#include <stdlib.h>
int front=-1,rear=-1,*queue,item,i,size;
int display()
{
        if(front==-1 && rear==-1)
        {
                printf("\n nothing to display");
        }
        else
        {
                printf("\n elements are:");
                for(i=front;i!=rear;i=(i+1)%size)
                {
                        printf("%d\t",queue[i]);
                }
                printf("%d\t",queue[i]);
        }
}

int enqueue()
{
	if(front==-1 && rear==-1)
	{
		front=0;
		rear=0;
		printf("enter the element to be insert:");
		scanf("%d",&item);
		queue[front]=item;
}
	else if(((rear+1)%size)==front)
	{
		printf("\n queue is full");
	}
	else
	{
		printf("enter element to insert:");
		scanf("%d",&item);
		rear=(rear+1)%size;
		queue[rear]=item;
	}
}
int dequeue()
{
	if(front==-1 && rear==-1)
	{
	printf("\n queue underflow");
	}
	else if(front==rear) 
	{
		printf("deleted element is %d",queue[front]);
		front=-1;
		rear=-1;
	}
	else 
        {
                printf("deleted element is %d",queue[front]);
                front=(front+1)%size;
        }

	display();
}
int search()
{
	if(front==-1 && rear==-1)
	{
		printf("\n queue is empty");
	}
	else
	{
		int searchItem,found=0;
		printf("\n enter element to searched:");
		scanf("%d",&searchItem);
		for(i=front;i!=rear;i=(i+1)%size)
		{
                        if(queue[i]==searchItem)
                        {
                                found=1;
                                break;
                        }

                }
                if(queue[i]==searchItem)
                {
                found=1;
                }
		if(found)
 {
                        printf("Element %d found in Queue\n",searchItem);
                }
                else
                {
                        printf("Element %d not found in Queue\n",searchItem);
                }
        }
 }
int main()
{

        int choice;
        printf("Enter the size of circular Queue\n");
        scanf("%d",&size);
        queue=(int*)malloc(size * sizeof(int));
        if(queue==NULL)
        {
                printf("\nMemory Allocation Failed,Exiting Program\n");
                exit(1);
        }
        while(1)
        {
                printf("\nCircular Queue Operation\n");
                printf("1.Enqueue\n");
                printf("2.Dequeue\n");
                printf("3.Search\n");
                printf("4.Display\n");
                printf("5.Exit\n");
                printf("Enter your choice:\n");
                scanf("%d",&choice);
                switch(choice)
{
                        case 1:
                                enqueue();
                                break;

                        case 2:
                                dequeue();
                                break;

                        case 3:
                                search();
                                break;
                        case 4:
                                display();
                                break;
                        case 5:
                                free(queue);
                                exit(0);
                                break;
                        default:
                                printf("Please enter valid choice\n");
                                break;

                }
        }
}
