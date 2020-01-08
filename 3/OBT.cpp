#include<stdio.h>
#define MAX 1000000
struct point{
	double pi;
	double qi;
};
 int main(){
 	FILE *fp1,*fp2;
    if((fp1 = fopen("in.dat","r"))==NULL){
    	printf("打开文件失败！\n");
	};
    fp2 = fopen("out.dat","w");
 	int n;
 	fscanf(fp1,"%d",&n);
 	point note[n + 1];
 	int root[n+1][n+1] = {0};
 	double e[n + 1][n],w[n + 1][n];
 	
 	for(int i = 0; i < n + 1; i++)
 	{
 		fscanf(fp1,"%lf",&note[i].pi);
 		fscanf(fp1,"%lf",&note[i].qi);
	}
	
	for(int i = 1; i <= n + 1; i++) 
	{
		e[i][i - 1] = note[i - 1].qi;
		w[i][i - 1] = note[i - 1].qi;
    }
    
    int r,l,i,j;
    double t;
    for(l =1; l < n + 1; l++)
 	{
 		for( i = 1; i <= n - l + 1; i++)
 	    {
 	    	j = i + l - 1;
 	    	e[i][j] = MAX;
 	    	w[i][j] = w[i][j - 1] + note[j].pi + note[j].qi;
 	    	for(r = i; r <= j; r++)
 	    	{
 	    	    t = e[i][r - 1] + e[r + 1][j] + w[i][j];
 	    	    if(t < e[i][j])
 	    	    {
 	    	    	e[i][j] = t;
 	    	    	root[i][j] = r;
				}
					
			}
 	    	
 	    }
 		
 	}
    for(i = 1; i <= n; i++)
    {
    	for(j = 1; j<=n;j++)
    	fprintf(fp2,"%d ",root[i][j]);
    	fprintf(fp2,"\n");
	}
	fclose(fp1);
	fclose(fp2);
    return 0;
 }
