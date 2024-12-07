#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node*link;
}
*top=NULL;

int isEmpty()
{
	if(top==NULL)
		return 1;
	else
     		return 0;
}
void push(int data)
{
	struct node *newnode=(struct node*)malloc(sizeof(struct node));
	if(newnode==NULL)
	{
		printf("stack overflow");
		exit(1);
	}
	newnode->data=data;
	newnode->link=NULL;
	newnode->link=top;
	top=newnode;
}
int pop()
{
	struct node *temp;
	int val;
	if(isEmpty())
	{
		printf("stack underflow");
		exit(1);
	}
	temp=top;
	val=temp->data;
	top=temp->link;
	free(temp);
	temp=NULL;
	return val;
}
int peek()
{
	if(isEmpty())
	{
		printf("stack uderflow");
		exit(1);
	}
	return top->data;
}
void print()
{
	struct node *temp;
	temp=top;
	if(isEmpty())
	{
		printf("stack underflow");
		exit(1);
	}
	printf("stack elements are:");
	while(temp!=NULL)
	{
		printf("%d\t",temp->data);
		temp=temp->link;
	}
}
void search()
{
		struct node *temp;
		temp=top;
		int s,f=0;
		printf("enter an element to be search:");
		scanf("%d",&s);
		while(temp!=NULL)
		{
			if(temp->data==s)
			{
				f=1;
				printf("\n %d found at location %d",s,temp->link);
			}
		
		temp=temp->link;
	}
	if(f==0)
		printf("\n %d is not found",s);
}

int main()
{
	int ch,data;
	while(1)
	{
		printf("\n");
		printf("1.push \n 2.pop \n 3.print the top element \n 4.print all elements \n 5.search \n 6.exit");
		printf("\nenter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:	printf("enter the element to be pushed");
				scanf("%d",&data);
				push(data);
				break;
			case 2: data=pop();
				printf("deletd element is %d\n",data);
		          	break;
                        case 3: printf("the topmost element of the stack is %d\n",peek());
				break;
			case 4: print();
                                break;
			case 5: search();
				break;
			case 6:exit(0);
			default:printf("invalid choice \n");
		}
	}
	return 0;
}


