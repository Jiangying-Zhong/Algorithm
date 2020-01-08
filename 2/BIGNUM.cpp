#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<string.h>
using namespace std;

#define MAX 10000

int StringToInt(string s){
    int ans=atoi(s.c_str());
    return ans;
}           

string IntToString(int i){
    stringstream str;
    str<<i;
    string s=str.str();
    return s;
} 
//大数乘法中必须用到大数加法，而大数加法的思路和大数乘法也是大同小异的，将串a和串b的末尾都切出一段长度为8的子串出来，
//a从左到右子串分别是a1和a2，b亦然。之后就是考虑t=a2+b2的不同情况，有可能t.size<8，那么这个时候我们就要通过补0的方式凑够8位。
string add(string a,string b){
    if(a.size()<=8&&b.size()<=8)
    	return IntToString(StringToInt(a)+StringToInt(b));

    string a1="0";
    string a2=a;
    if(a.size()>8){
        a1=a.substr(0,a.size()-8);
        a2=a.substr(a.size()-8);
    }
    string b1="0";
    string b2=b;
    if(b.size()>8){
        b1=b.substr(0,b.size()-8);
        b2=b.substr(b.size()-8);
    }

    string t=add(a2,b2);
    while(t.size()<8)
		t="0"+t;
    if(t.size()>8)
		return add(add(a1,b1),"1")+t.substr(1);
    return add(a1,b1)+t;
}

string stringBeforeZero(string a,int len){
   for(int i = 0; i < len; i++){
     a.insert(0,"0");
   }
   return a;
}

string sub(string a,string b){
   while('0' == a[0] && a.size() > 1){
     a = a.substr(1,a.size()-1);
   }
   while('0' == b[0]&&b.size() > 1){
     b = b.substr(1,b.size()-1);
   }
   if(a.size() > b.size()){
     b = stringBeforeZero(b,a.size()-b.size());
   }
   string result;
   for(int i = a.size() - 1;i >= 0;i--){
      int c= (a[i] - '0')-(b[i] - '0');
	  if(c < 0){
	     c += 10;
		 int m = i - 1;
		 char k = a[m];
		 while('0' == k){
		   a[m]='9';
		   m -= 1;
		   k = a[m];
		 }
		 a[m] -= 1;
	  }
	  result.insert(0,IntToString(c));
   }
   return result;
}

string zero(int n){
    if(n==0){
        return "";
    }
    if(n==1){
        return "0";
    }

return  zero(n/2)+zero(n/2)+zero(n%2);
}      
//大数乘法的思路就是把一个长的数字串拆分成两个部分,子串a1和子串a2，然后结果就是a1+...+a2。
//递归的边界条件就是当每个子串的长度都小于等于4的时候，就可以通过直接*运算返回结果。
string multi(string a,string b){
    if(a.size()<=4&&b.size()<=4){
        return IntToString(StringToInt(a)*StringToInt(b));
    }
    if(a.size()>4){
        int k=a.size()/2;
        string a1=a.substr(0,k);
        string a2=a.substr(k);

        return add(multi(a1,b)+zero(a2.size()),multi(a2,b));
    }
    return multi(b,a);
}

void cal(char* row, FILE* fp1, FILE* fp2)
{
    char *str1, *str2, *str3;
    char str_out[100];
    str1 = strtok(row, " ");
    str2 = strtok(NULL, " ");
    str3 = strtok(NULL, " ");
    string s1, s2, ans;
    int op;
    s1 = (str1);
    s2 = (str2);
    op = atoi(str3);
    switch(op)
    {
        case 1:
        	
            ans = add(s1, s2);
            strcpy(str_out, ans.c_str());
            fputs(str_out, fp2);
            fputs("\n", fp2);
            break;
        case 2:
            ans = sub(s1, s2);
            strcpy(str_out, ans.c_str());
            fputs(str_out, fp2);
            fputs("\n", fp2);
            break;
        case 3:
            ans = multi(s1, s2);
            strcpy(str_out, ans.c_str());
            fputs(str_out, fp2);
            fputs("\n", fp2);
            break;
    }
}

int main()
{
    FILE *fp1, *fp2;
    char row[MAX];
    fp1 = fopen("in.dat", "r");
    fp2 = fopen("out.dat", "w");
    while(!feof(fp1))
    {
        fgets(row, MAX, fp1);
        int n = atoi(row);
        int i = 0;
        while(fgets(row, MAX, fp1))
        {
            cal(row, fp1, fp2);
            i++;
            if(i==n)
                break;
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
