#include<stdio.h>
#include<stdbool.h>
//this is testng git 
struct disk
{
        int arr_time;
        int head_loc;
        int process_pid;
}disk[10009];
bool done[10009];
int head_pos;
int n;
int val;
int abs(int x)
{
        if(x<0)
                return ((-1)*x);
        else
                return (x);

}

void pre()
{
    head_pos=val;
    int i;
    for(i=0;i<n;i++)
        done[i]=false;
}

void sort_arrtime(struct disk arr[], int fst, int last)
{
 int i,j,pivot;
 struct disk tmp;
 if(fst<last)
 {
   pivot=fst;
   i=fst;
   j=last;
   while(i<j)
   {
     while(arr[i].arr_time<=arr[pivot].arr_time && i<last)
        i++;
     while(arr[j].arr_time > arr[pivot].arr_time)
        j--;
     if(i<j)
     {
        tmp=arr[i];
        arr[i]=arr[j];
        arr[j]=tmp;
     }
   }
   tmp=arr[pivot];
   arr[pivot]=arr[j];
   arr[j]=tmp;
   sort_arrtime(arr,fst,j-1);
   sort_arrtime(arr,j+1,last);
 }
}

void sort_headloc(struct disk arr[], int fst, int last)
{
 int i,j,pivot;
 struct disk tmp;
 if(fst<last)
 {
   pivot=fst;
   i=fst;
   j=last;
   while(i<j)
   {
     while(arr[i].head_loc<=arr[pivot].head_loc && i<last)
        i++;
     while(arr[j].head_loc > arr[pivot].head_loc)
        j--;
     if(i<j)
     {
        tmp=arr[i];
        arr[i]=arr[j];
        arr[j]=tmp;
     }
   }
   tmp=arr[pivot];
   arr[pivot]=arr[j];
   arr[j]=tmp;
   sort_headloc(arr,fst,j-1);
   sort_headloc(arr,j+1,last);
 }
}

int min(int x,int y)
{
    if(x<y)
        return x;
    return y;
}


int clook()
{
        pre();
        printf("performing c-look\n\n");
        int i,curr,j,now_time;
        int tot_time=0;
        bool first;
        int time;
        curr=head_pos;
        time=0;
        while(1)
        {
                bool check =false;
                for(i=0;i<n;i++)
                        if(done[i]==false)
                                check=true;
                if(check==false)
                        break;
                for(j=head_pos;j<=199;j++)
                {
                        time++;
                        for(i=0;i<n;i++)
                        {
                                if(disk[i].arr_time<=time && done[i]==false)
                                {
                                        done[i]=true;
                                        printf("request served for %d process\n",i+1);
                                        tot_time+=abs(head_pos-disk[i].head_loc);
                                        head_pos=disk[i].head_loc;
                                }
                        }
                }
                first=true;
                time=time-(199-head_pos);
                for(j=0;j<199;j++)
                {
                        if(first)
                            now_time=time+(199-j);
                        else
                            now_time++;
                        for(i=0;i<n;i++)
                        {
                                if(disk[i].arr_time<=now_time && done[i]==false)
                                {
                                        done[i]=true;
                                        printf("request served for %d process\n",i+1);
                                        if(first)
                                            tot_time+=now_time+abs(head_pos-disk[i].head_loc);
                                        else
                                            tot_time+=abs(head_pos-disk[i].head_loc);
                                        head_pos=disk[i].head_loc;
                                }
                        }
                }
        }
        return tot_time;
}

int cscan()
{
        pre();
        printf("performing c-scan\n\n");
        int i,curr,j;
        int tot_time=0;
        int time,time_diff;
        sort_headloc(disk,0,n-1);
        curr=head_pos;
        time=0;
        while(1)
        {
                bool check =false;
                for(i=0;i<n;i++)
                        if(done[i]==false)
                                check=true;
                if(check==false)
                        break;
                for(i=0;i<n;i++)
                {
                    time_diff = disk[i].head_loc - head_pos;
                    if(time_diff + time >= disk[i].arr_time && done[i]==false)
                    {
                        printf("request served for %d process\n",disk[i].process_pid);
                        done[i]=true;
                        time+=time_diff;
                        head_pos=disk[i].head_loc;
                    }
                }
                time+=(199-head_pos);
                time+=200;
        }
        tot_time = time;
        return tot_time;
}

int fcfs()
{
        pre();
        printf("performing fcfs\n\n");
        sort_arrtime(disk,0,n-1);
        int curr=head_pos;
        int i;
        int tot_time=0;
        for(i=0;i<n;i++)
        {
                printf("request serve for %d process\n",disk[i].process_pid);
                tot_time+=abs(curr-disk[i].head_loc);
                curr=disk[i].head_loc;
        }
        return tot_time;
}

int look()
{
        pre();
        printf("performing look\n\n");
        int i,curr,j;
        int tot_time=0;
        int time_diff;
        int time;
        curr=head_pos;
        time=0;
        sort_headloc(disk,0,n-1);
        while(1)
        {
                bool check =false;
                for(i=0;i<n;i++)
                        if(done[i]==false)
                                check=true;
                if(check==false)
                        break;
                for(i=0;i<n;i++)
                {
                    time_diff = disk[i].head_loc - head_pos;
                    if(time_diff + time >= disk[i].arr_time && done[i]==false)
                    {
                        done[i]=true;
                        printf("request serve for %d process\n",disk[i].process_pid);
                        time+=time_diff;
                        head_pos=disk[i].head_loc;
                    }
                }
                for(i=n-1;i>=0;i--)
                {
                    time_diff = abs(head_pos-disk[i].head_loc);
                    if(time_diff + time >= disk[i].arr_time && done[i]==false)
                    {
                        done[i]=true;
                        printf("request serve for %d process\n",disk[i].process_pid);
                        time+=time_diff;
                        head_pos=disk[i].head_loc;
                    }
                }
        }
        tot_time=time;
        return tot_time;
}

int scan()
{
        pre();
        printf("performing scan\n\n");
        int i,curr,j;
        int tot_time=0;
        int time,time_diff;
        sort_headloc(disk,0,n-1);
        curr=head_pos;
        time=0;
        while(1)
        {
                bool check =false;
                for(i=0;i<n;i++)
                        if(done[i]==false)
                                check=true;
                if(check==false)
                        break;
                for(i=0;i<n;i++)
                {
                    time_diff = disk[i].head_loc - head_pos;
                    if(time_diff + time >= disk[i].arr_time && done[i]==false)
                    {
                        done[i]=true;
                        printf("request serve for %d process\n",disk[i].process_pid);
                        time+=time_diff;
                        head_pos=disk[i].head_loc;
                    }
                }
                time+=(199-head_pos);
                head_pos=199;
                for(i=n-1;i>=0;i--)
                {
                    time_diff = head_pos-disk[i].head_loc;
                    if(time_diff + time >= disk[i].arr_time && done[i]==false)
                    {
                        done[i]=true;
                        printf("request serve for %d process\n",disk[i].process_pid);
                        time+=time_diff;
                        head_pos=disk[i].head_loc;
                    }
                }
                check =false;
                for(i=0;i<n;i++)
                        if(done[i]==false)
                                check=true;
                if(check==false)
                        break;
                head_pos=0;
                time+=head_pos;
        }
        tot_time = time;
        return tot_time;
}

int sstf()
{
        pre();
        printf("performing sstf\n\n");
        int i,curr,j,minn;
        int tot_time=0;
        int time,time_diff;
        sort_headloc(disk,0,n-1);
        curr=head_pos;
        time=0;
        while(1)
        {
                bool check =false;
                for(i=0;i<n;i++)
                        if(done[i]==false)
                                check=true;
                if(check==false)
                        break;
                minn=100009;
               for(i=0;i<n;i++)
               {
                   if(done[i]==false)
                        minn=min(minn,abs(head_pos-disk[i].head_loc));
               }
               for(i=0;i<n;i++)
               {
                   if(abs(disk[i].head_loc-head_pos)==minn && done[i]==false)
                   {
                       tot_time+=abs(disk[i].head_loc-head_pos);
                       head_pos=disk[i].head_loc;
                       done[i]=true;
                       printf("served request for %d process\n",disk[i].process_pid);
                   }
               }
        }
        return tot_time;
}

void input()
{
        pre();
        int i;
        printf("enter number of process\n");
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
                printf("enter arrival time and head location of %d\n",i+1);
                scanf("%d%d",&disk[i].arr_time,&disk[i].head_loc);
                disk[i].process_pid=i+1;
                done[i]=false;
        }
        printf("enter head position\n");
        scanf("%d",&head_pos);
        val=head_pos;
}

int main()
{
    input();
    printf("%d\n\n\n",clook());
    printf("%d\n\n\n",cscan());
    printf("%d\n\n\n",fcfs());
    printf("%d\n\n\n",look());
    printf("%d\n\n\n",scan());
    printf("%d\n\n\n",sstf());
    return 0;
}
