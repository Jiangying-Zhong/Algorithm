#include<iostream>
using namespace std;

#define NIL -1

void printAllPath(int note[11][11], int i, int j, FILE *fp2);

int main(void)
{
	FILE *fp1,*fp2;
	int num;
	if((fp1 = fopen("in.dat","r"))==NULL)
    	printf("打开文件失败！ \n");
	else
		fscanf(fp1, "%d", &num);
	fp2 = fopen("out.dat","w");
	fprintf(fp2, "%d\n", num);
	
	while(num--)
	{
		int n;
		fscanf(fp1, "%d", &n);
		fprintf(fp2, "%d\n", n);
		int edge[11][11]={-1};
		int note[11][11]={-1};
		int i,j;
		for(i=1; i<n+1; i++){
			for(j=1; j<n+1; j++){
				fscanf(fp1, "%d", &edge[i][j]);
				if(edge[i][j]==0||edge[i][j]>=100||i==j)
					note[i][j]=NIL;
				else
					note[i][j]=i;
			}
		}
		int k;
		for(k=1;k<=n; k++){
		    for(i=1; i<=n; i++){
		        for(j=1; j<=n; j++){
	        		if( edge[i][k]<100 && edge[k][j]<100 && edge[i][k]+edge[k][j]<edge[i][j] ){
	        			edge[i][j]=edge[i][k]+edge[k][j];
	            		note[i][j]=note[k][j];
				}
			}
		}
		
		for(i=1; i<=n; i++){
			for(j=1; j<=n; j++){
				if(edge[i][j]>=100)
					fprintf(fp2, "32767");
				else
					fprintf(fp2, "%d ", edge[i][j]);
			}	
			fprintf(fp2, "\n");
		}
		
		for(i=1; i<=n; i++) {
			for(j=1; j<=n; j++) 
			    printf("%d ", edge[i][j]);
			printf("\n");
		}

		for(i=1; i<=n; i++) {
			for(j=1; j<=n; j++) 
			    printf("%d ", note[i][j]);
			printf("\n");
		}
		
		
		for(i=1; i<=n; i++){
		    for(j=1; j<=n; j++) {
		        printAllPath(note, i, j, fp2);
				fprintf(fp2, "\n");
		    }
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
	}
}

void printAllPath(int note[11][11], int i, int j, FILE *fp2){
    if(i==j) 
		fprintf(fp2, "%d ", i);
    else if(note[i][j]==NIL)
    	fprintf(fp2, "NULL");
    else
	{
        printAllPath(note, i, note[i][j], fp2);
        fprintf(fp2, "%d ", j);
    }
}
