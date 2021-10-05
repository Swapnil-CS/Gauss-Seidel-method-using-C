#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main()
{
	float **a;
	float *x,*y,*xcp,*temp;
	float ratio;
	int i,j,k,n,sum,max,indx,count=0,flag=0;
	
	printf("Enter number of variables: ");
	scanf("%d", &n);
	a = (float**)malloc(n*sizeof(float*));
	for(i=1;i<=n;i++)
	{
		a[i] = (float*)malloc((n+1)*sizeof(float));
	}

	x = (float*)malloc(n*sizeof(float));
	y = (float*)malloc(n*sizeof(float));
	xcp = (float*)malloc(n*sizeof(float));
	for(i=1;i<=n;i++)
	{
		printf("\nEnter Coefficients of equation number %d",i);
		for(j=1;j<=n;j++)
		{
			printf("\na[%d][%d] = ",i,j);
			scanf("%f", &a[i][j]);
		}
		printf("\nEnter Constant of equation number %d",i);
		printf("\na[%d][%d] = ",i,j);
		scanf("%f", &a[i][j]);
	}
	//checking if the equations satisfy the diagonal dominance or not. 
	i=1;
	while(i<=n)
	{
		sum=0;
		max=abs(a[i][i]);		//considering absoulte value everywhere to check diagonal dominance asper rules
		for(j=1;j<=n;j++)
		{
			if(i!=j)
			{
				sum=sum+abs(a[i][j]);
				if(abs(a[i][j])>=max)
				{
					max=abs(a[i][j]);
					indx=j;
				}
			}	
		}
		//if any equation doesn't satisfy diagonal dominance then arranging in proper order
		if(fabs(a[i][i])<sum)
		{
			temp=a[i];
			a[i]=a[indx];
			a[indx]=temp;
			count++;		//counting number of equations properly arranged if it was not in order
		}
		else
		{
			i++;
		}
		if(count==n-1)	//if all eqns except one are arranged then its clear the remaining one is also arranged	
			break;
	}

	if(count==0)
	{
		printf("\nGiven equations are already arranged properly acc to diagonal dominance rule");
	}
	//displaying the equations after arranging properly
	printf("\nEquations after arranging in diagonally dominant manner:\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n+1;j++)
		{
			printf("\t%0.4f",a[i][j]);
		}
		printf("\n");
	}
	printf("The iterations are:\n");
	for(i=1;i<=n;i++)
	{
		printf("\tx%d",i);		//making the table head for the iterations
	}
	printf("\n\t------------------------------------------------------------------\n");
	for(i=1;i<=n;i++)
	{
		x[i]=0;				//taking initial value of all the variables as 0
		printf("\t%0.4f",x[i]);		//printing the initial values of the variables
	}
	do
	{
		for(i=1;i<=n;i++)		//outer loop for each row i.e for each equations
		{
			for(j=n+1;j>=1;j--)		//inner loop for eac variable of the equations
			{
				if(j==n+1)		//checking if j is at the constant term of the eqn
				{
					y[i] = a[i][j];		//storing the constant term at the value of the variable
				}
				else if(j!=i)			// whenever the variable is other than the variable that is pointed by i
				{
					y[i] = y[i]-(a[i][j]*x[j]);			//subtracting the each term from the current value of variable
				}
			}
			y[i] = y[i]/a[i][i];		//finally dividing the value by coefficient of the pointed variable to get the final result of current iteration
			xcp[i] =x[i];		//copying the previous value of the variable
			x[i] = y[i];	 	//updating the current value of variable to get used in next iterations
		}
		count=0;
		for(i=1;i<=n;i++)		//loop for checking differences of values b/w prev and current iteration
		{
			if(fabs(x[i]-xcp[i])<0.0001)		//calculating difference by taking absolute value
			{
				count++;		//counting the number of times the condition satisfied
			}
		}
		if(count==n)			//if all the variables have shown convergence
		{
			printf("\nThe values of the variables are:");
			for(j=1;j<=n;j++)
			{
				printf("\nx%d = %0.4f",j,x[j]);		//then printing the final values
			}
			flag = 1;
		}
		else			//else the iterations will go on until convergence
		{
			printf("\n");
			for(j=1;j<=n;j++)
			{
				printf("\t%0.4f",x[j]);		//printing values after each iteration
			}
		}
	} while (flag!=1);		//if flag becomes 1 then it means all done
free(a);
free(x);
free(y);
free(xcp);		//deallocating all the allocated space
}