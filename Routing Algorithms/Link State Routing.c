#include <stdio.h>
int minimumDistance(int distance[], int visited[], int n)
{
	int min=9999, min_index;

	for(int i=0;i<n;i++)
    {
		if(visited[i]==0 && min>=distance[i])
		{
			min = distance[i];
			min_index = i;
		}
    }
	return min_index;
}

void linkState(int weight_matrix[10][10], int n, int source)
{
	int visited[10], distance[10], min_index;
	for(int i=0;i<n;i++)
	{
		visited[i]=0;
		distance[i]=9999;
	}
	distance[source] = 0;
	for(int i=0;i<n;i++)
	{
		min_index = minimumDistance(distance, visited, n);
		visited[min_index]=1;
		for(int j=0;j<n;j++)
		{
			if(visited[j]==0 && (distance[min_index] + weight_matrix[min_index][j] < distance[j]))
				distance[j] = distance[min_index] + weight_matrix[min_index][j];
		}
	}
	for(int i=0;i<n;i++)
	{
        printf("\nShortest distance from router %d to router %d: %d",source+1,i+1,distance[i]);
    }
}

int main()
{
	int weight_matrix[10][10], routers, edges, u, v, weight, source;

    printf("==============================\n");
    printf(" LINK STATE ROUTING ALGORITHM\n");
    printf("==============================\n");

	printf("Enter the number of routers: ");
	scanf("%d",&routers);

    printf("Routers: ");
    for(int i=1;i<=routers;i++)
        printf("%d ",i);
    printf("\n");

	for(int i=0;i<routers;i++)
    {
		for(int j=0;j<routers;j++)
        {
			if(i==j)
				weight_matrix[i][j]=0;
			else
				weight_matrix[i][j]=9999;
        }
    }

	printf("Enter the number of edges: ");
	scanf("%d",&edges);

	for(int i=0;i<edges;i++)
	{
		printf("\nEdge(Link): %d\n",i+1);
		printf("Enter the starting router: ");
		scanf("%d",&u);  
		printf("Enter the ending router: ");
		scanf("%d",&v);
		printf("Enter weight: ");
		scanf("%d",&weight);
		weight_matrix[u-1][v-1]=weight;
		weight_matrix[v-1][u-1]=weight;
	}

	printf("\nEnter the source router: ");
	scanf("%d",&source);
	linkState(weight_matrix, routers, source-1);
    return 0;
}
