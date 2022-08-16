#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "5_1.h"
#define MAX_LEN 80
int max =0;
/*int recursion(int n)
{
    if ( n== 1)
    {
        return 1;
    }
    else 
    return n+recursion(n-1);
}

int p(int a[],int i, int j)
{
    if (i>j) return 0;
    if (i==j) return a[i];
    int m ;
    m = (i+j)/2;
    return p(a,i,m) + p(a,m+1,j);
}

*/
void Average(TreeType t, int n)
{
    if(t != NULL){
    Average(t->left,n);
    int i;
    float open =0;
    float close =0;
    for (i=0;i<10;i++)
    {
        close += t->data.gia_dong[i];
        open += t->data.gia_mo[i];
    }
    printf("%s\t%.3f\n",t->data.maCP,(close-open)/10);
    Average(t->right,n);
    }
}

void Rising_day(TreeType t)
{
    if (t != NULL)
    {
        Rising_day(t->left);
        int tmp_max =0;
        int i;
        for (i=0;i<10;i++)
        {
            if (t->data.gia_dong[i] > t->data.gia_mo[i])
            {
                tmp_max++;
            }
        }
        if (tmp_max > max) max = tmp_max;
        Rising_day(t->right);
    }
}

void maCP_max(TreeType t)
{
    if (t!= NULL)
    {
        maCP_max(t->left);
        int i ;
        int tmp_max =0;
        for (i=0;i<10;i++)
        {
            if (t->data.gia_dong[i] > t->data.gia_mo[i])
            {
                tmp_max++;
            }
        }
        if (tmp_max == max)
        {
            printf("%-16s%-16d\n",t->data.maCP,tmp_max);
        }
        maCP_max(t->right); 
    }
}
void Find_max_min(TreeType t)
{
    float max=t->data.gia_dong[0];
    float min =t->data.gia_dong[0];
    int i;
    for (i=0;i<10;i++)
    {
        if (max < t->data.gia_dong[i]) max = t->data.gia_dong[i];
        if (min > t->data.gia_dong[i]) min = t->data.gia_dong[i];
    }
    printf("%-16s%-16.3f%-30.3f\n",t->data.maCP,max,min);
}
int main()
{
	FILE *fp;
    fp = fopen("data.txt","r+");
    if (fp == NULL)
    {
        printf("Error\n");
        return 1;
    }
    
    int m =0;
    TreeType t;
                    
    int N;
    makenullTree(&t);
    while (m !=5)
    {
        printf("Menu\n");
        printf("----------------------------------------\n");
        printf("1. Doc file\n\n");
        printf("2. Tim kiem theo ma chung khoan\n\n");
        printf("3. Tim kiem ma chung khoan co xu huong tang\n\n");
        printf("4. Tim ma co so ngay tang lon nhat\n\n");
        printf("5. Thoat chuong trinh\n\n");
        printf("\nYour choice:");
        scanf("%d",&m);
        while (m<1 || m> 5)
        {
            printf("yeu cau nhap lai:");
            scanf("%d",&m);
        }
        switch(m)
        {
            case 1:
            {
                char s[MAX_LEN +1];
                fgets(s,MAX_LEN,fp);
                sscanf(s,"%d",&N);
                printf("So ma chung khoan:%d\n",N);
                elementtype *list;
                list = (elementtype *)malloc(N *sizeof(elementtype));
                if (list == NULL)
                {
                printf("Error\n");
                return 1;
                }
                int i;
                int count =0;
                for (i=0;i<N;i++)
                {
                    fscanf(fp,"%s\t%f\t%f\t",list[i].maCP,&list[i].gia_mo[count],&list[i].gia_dong[count]);
                }
                count += 1;
                i=1;
                while (i < 10)
                {
                    int j;
                    for (j=0;j<N;j++)
                    {
                        elementtype tmp;
                        fscanf(fp,"%s\t%f\t%f",tmp.maCP,&tmp.gia_mo[count],&tmp.gia_dong[count]);
                        int a ,b;
                        for (a =0; a<7;a++)
                        {
                            if (strcmp(tmp.maCP,list[a].maCP)== 0)
                            {
                                list[a].gia_mo[count] = tmp.gia_mo[count];
                                list[a].gia_dong[count] = tmp.gia_dong[count];
                            }
                        }
                    }
                    i++;
                    count += 1;
                }
                int b;
                b=0;
                /*for (i=0;i<N;i++)
                {
                    int y;
                    for (y = 0;y<10;y++)
                    {
                        printf("%-16s%-16f%-16f\n",list[i].maCP,list[i].gia_mo[y],list[i].gia_dong[y]);
                    }
                }*/
                for (i=0;i<N;i++)
                {
                    t = InsertNode(t,list[i]);
                }
                printf("%s\t%s\n","Ma CP","Trung binh");
                Average(t,N);
                free(list);
                break;
            }
            case 2:
            {
                elementtype tmp;
                printf("Nhap ma co phieu:");
                scanf("%s",tmp.maCP);
                TreeType check = NULL;
                check = Search(t,tmp);
                int i;
                if (check != NULL)
                {
                    printf("%-16s%-16s%-30s\n","Ma","Gia dong cua max","Gia Dong cua min");
                    Find_max_min(check);
                }
                else 
                {
                    printf("Khong co ma co phieu nay\n");
                }
                break;
            }
            case 3:
            {
                printf("cac ma co phieu tang trong ngay 1 va ngay 2:\n");
                printf("%-16s%-16s%-16s\n","Ma","gia mo cua","Gia Dong cua");

                Matang(t);
                break;
            }
            case 4:
            {
                Rising_day(t);
                printf("So ngay tang:%d\n",max);
                printf("Cac ma co so ngay tang lon nhat:\n");
                printf("%-16s%-16s\n","Ma CP","Ngay tang");
                maCP_max(t);

                break;
            }
            default:
            {
                printf("VanDangHuy-20205086-126900\n");
                FreeTree(t);
            }
        }
    }
    fclose(fp);
	return 0;
}
