#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int noOfNode,**costTable,**distanceVector,**nextNode;
//char node[10];
void displayCost()
{
    printf("\nCost Table\n");
    for(int i=0;i<noOfNode;i++)
        printf("\t%d",i+1);
    for(int i=0;i<noOfNode;i++){
        printf("\n%d",i+1);
        for(int j=0;j<noOfNode;j++)
            printf("\t%d",costTable[i][j]);
    }
    printf("\n");
}
void displayDVR()
{
    printf("\nDistance Vector Table\n");
    for(int i=0;i<noOfNode;i++)
        printf("\t%d",i+1);
    for(int i=0;i<noOfNode;i++){
        printf("\n%d",i+1);
        for(int j=0;j<noOfNode;j++)
            printf("\t%d",distanceVector[i][j]);
    }
    printf("\n");
}
void displayForwardingTable(int i)
{
    printf("\nForwarding Table for %d\n",i+1);
    printf("Node\tCost\tnextHop\n");
    for(int j=0;j<noOfNode;j++){
        //if(j!=i)
            printf("%d\t%d\t%d\n",j+1,distanceVector[i][j],nextNode[i][j]);
    }
    //printf("\n");
}
int min(int a,int b)
{
    if(a<b)
        return a;
    else
        return b;
}
int main()
{
    int temp,cost;
    printf("Enter the Number of Node : ");
    scanf("%d",&noOfNode);
    //node = (char*)malloc(noOfNode*sizeof(char *));
    costTable =(int **)malloc(noOfNode*sizeof(int *));
    for(int i=0;i<noOfNode;i++)
        costTable[i]=(int *)malloc(noOfNode*sizeof(int));
    distanceVector =(int **)malloc(noOfNode*sizeof(int *));
    for(int i=0;i<noOfNode;i++)
        distanceVector[i]=(int *)malloc(noOfNode*sizeof(int));
    nextNode =(int **)malloc(noOfNode*sizeof(int *));
    for(int i=0;i<noOfNode;i++)
        nextNode[i]=(int *)malloc(noOfNode*sizeof(int)); 
    for(int i=0;i<noOfNode;i++){ //Initialize cost and dv table
        for(int j=0;j<noOfNode;j++){
            costTable[i][j]=100;
            distanceVector[i][j]=100;
            nextNode[i][j]=i+1;
        }
        costTable[i][i]=0;
        distanceVector[i][i]=0;
        nextNode[i][i]=i+1;
    }
    for(int i=0;i<noOfNode;i++){
        printf("\nEnter Neihghbor Node for %d\n",i+1);
        while(1){
            printf("Enter Neihghbor Node : ");
            scanf("%d",&temp);
            if(temp==-1)
                break;
            printf("Enter Cost of Link : ");
            scanf("%d",&cost);
            costTable[i][temp-1]=cost;
            costTable[temp-1][i]=cost;
            distanceVector[i][temp-1]=cost;
            distanceVector[temp-1][i]=cost;
        }
    }
    displayCost();
    displayDVR();
    int flag=0;
    // Find distance vector table
    while(flag<3){
        for(int i=0;i<noOfNode;i++){//from
            for(int j=0;j<noOfNode;j++){ // to
                for(int k=0;k<noOfNode;k++){ // intermediate
                    temp = distanceVector[i][j];
                    distanceVector[i][j]=min(distanceVector[i][j],costTable[i][k]+distanceVector[k][j]);
                    if(temp!=distanceVector[i][j])
                        nextNode[i][j]=k+1;
                }
            }
        }
        flag+=1;
    }
    displayDVR();
    for(int i=0;i<noOfNode;i++)
        displayForwardingTable(i);
    return 0;
}