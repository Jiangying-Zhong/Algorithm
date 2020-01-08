#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

using namespace std;

int num;
int n;
#define MAX 99999

struct POINT{
    int x;
    int y;
}point;

struct EDGE{
    int x1, y1;
    int x2, y2;
    double dis;
}edge[100];

void distance(POINT a, POINT b, int n)
{
    edge[n].x1 = a.x;
    edge[n].x2 = b.x;
    edge[n].y1 = a.y;
    edge[n].y2 = b.y;
    edge[n].dis = sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
}

int main()
{
    int i,j;
    
    FILE *fp1, *fp2;
    fp1 = fopen("in.dat", "r");
    fp2 = fopen("out.dat", "w");
    fscanf(fp1, "%d", &num);
    POINT a[100], b[100];
    double min = 99999;
    while(num--)
    {
        fscanf(fp1, "%d", &n);
        for (i = 0; i < n; i++)
        {
            fscanf(fp1,"%d %d", &a[i].x, &a[i].y);
            b[i].x = a[i].x;
            b[i].y = a[i].y;
        }
        int k =0;
        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                distance(a[i],b[j],k);
                k++;
            }
        }
        
        for(i=0;i<(n*(n-1)/2);i++)
        {
            if(edge[i].dis<min)
                min = edge[i].dis;
        }
        for (i = 0; i <(n*(n-1)/2); i++)
        {
            if (edge[i].dis == min)
            {
                fprintf(fp2,"%d %d %d %d ",edge[i].x1, edge[i].y1, edge[i].x2, edge[i].y2);
                
            }
        }
        fprintf(fp2, "\n");
        min = 9999;
    }
    
    fclose(fp1);
    fclose(fp2);
    
    return 0;
    
}
