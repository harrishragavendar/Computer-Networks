#include<stdio.h>
#include<string.h>
int main()
{
        char c[100][100],col[100],row[100];
        printf("Enter number of data words\n");
        int n;
        scanf("%d",&n);
        printf("Enter data words:");
        while ((getchar()) != '\n');
        int i,j,coun;
        for(i=0;i<n;i++)
                scanf("%s",&c[i]);
        int len=strlen(c[0]);
        for(i=0;i<len;i++)
        {
                coun=0;
                for(j=0;j<n;j++)
                        if(c[j][i]=='1')
                                coun++;
                if(coun%2==0)
                        col[i]='0';
                else
                        col[i]='1';
        }
        for(i=0;i<n;i++)
        {
                coun=0;
                for(j=0;j<len;j++)
                        if(c[i][j]=='1')
                                coun++;
                if(coun%2==0)
                        row[i]='0';
                else
                        row[i]='1';
        }
        coun=0;
        for(j=0;j<len;j++)
                if(col[j]=='1')
                        coun++;
        if(coun%2==0)
                row[i]='0';
        else
                row[i]='1';

        //printing
        printf("Data after 2d parity:\n");
        for(i=0;i<n;i++)
                printf("%s%c\t",c[i],row[i]);
        printf("%s%c\n",col,row[i]);
        return 0;
}
