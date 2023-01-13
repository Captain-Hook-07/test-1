
#include<stdio.h>
#include<stdlib.h>
// Merge Sort

void Merge(int *a,int n,int *b,int m,int *fin,int o){

    int i=0,j=0,k=0;
    while(k<o-1){
        if(*(a+i)<=*(b+j)){
            *(fin+k)=*(a+i);
            i++;
            k++;
        }
        else{
            *(fin+k)=*(b+j);
            j++;
            k++;
        }

        if(i==n){
            for(int p=j ; p<m ; p++){
                *(fin+k)=*(b+p);
                k++;
            }
        }
        if(j==m){
            for(int p=i ; p<n ; p++){
                *(fin+k)=*(a+p);
                k++;
            }
        }
    }
}

void merge_sort(int *a,int n){
    if(n==1) return;
    int l=0,mid=(n/2)-1,r=n-1;
    int left[n/2];
    for(int i=l ; i<=mid ; i++){
        left[i]=*(a+i);
    }
    int right[n-(n/2)];
    int j=0;
    for(int i=mid+1 ; i<=r ; i++){
        right[j]=*(a+i);
        j++;
    }
    merge_sort(left,n/2);
    merge_sort(right,n-(n/2));
    Merge(left,n/2,right,n-(n/2),a,n);
}

// void Merge(int *a,int *b,int *fin){
//     int n=sizeof(a)/sizeof(a[0]);
//     int m=sizeof(b)/sizeof(b[0]);
//     int o=sizeof(fin)/sizeof(fin[0]);
//     int i=0,j=0,k=0;
//     while(k<o-1){
//         if(a[i]<=b[j]){
//             fin[k]=a[i];
//             i++;
//             k++;
//         }
//         else{
//             fin[k]=b[j];
//             j++;
//             k++;
//         }

//         if(i==n){
//             for(int p=j ; p<m ; p++){
//                 fin[k]=b[p];
//                 k++;
//             }
//         }
//         if(j==m){
//             for(int p=i ; p<n ; p++){
//                 fin[k]=a[p];
//                 k++;
//             }
//         }
//     }
// }

// void Merge_Sort(int *a){
//     int n=sizeof(a)/sizeof(a[0]);
//     if(n==1) return;
//     int l=0,mid=(n/2)-1,r=n-1;
//     int left[n/2];
//     for(int i=l ; i<=mid ; i++){
//         left[i]=a[i];
//     }
//     int right[n-(n/2)];
//     int j=0;
//     for(int i=mid+1 ; i<=r ; i++){
//         right[j]=a[i];
//         j++;
//     }
//     Merge_Sort(left);
//     Merge_Sort(right);
//     Merge(left,right,a);
// }


// Heap Sort

int hs;

void max_heapify(int *a,int i){
    int lch=2*i;
    int rch=2*i+1;
    int largest;
    if(lch<=hs && *(a+lch)>*(a+i))
        largest=lch;
    else
        largest=i;
    if(rch<=hs && *(a+rch)>*(a+largest))
        largest=rch;

    if(largest!=i){
        int temp=*(a+i);
        *(a+i)=*(a+largest);
        *(a+largest)=temp;
        max_heapify(a,largest);
    }
}

void build_max_heap(int *a){
    for(int i=hs/2 ; i>=1 ; i--){
        max_heapify(a,i);
    }
}

void heap_sort(int *a){
    build_max_heap(a);
    int i=hs;
    for(i;i>=2;i--){
        int temp=*(a+1);
        *(a+1)=*(a+hs);
        *(a+hs)=temp;
        hs--;
        max_heapify(a,1);
    }
}

int partition(int *a,int start, int end){
    int pi=start;
    for(int j=start ; j<end ; j++){
        if(*(a+j)<*(a+end)){
            int temp=*(a+pi);
            *(a+pi)=*(a+j);
            *(a+j)=temp;
            pi++;
        }
    }
    int temp=*(a+pi);
    *(a+pi)=*(a+end);
    *(a+end)=temp;
    return pi;
}

void quick_sort(int *a,int start,int end){
    if(start>=end) return;

    int ind = partition(a,start,end);
    quick_sort(a,ind+1,end);
    quick_sort(a,start,ind-1);
}

int main(){
    int n;
    printf("Please enter size of array");
    scanf("%d",&n);
    hs=n;
    int a[n+1];
    a[0]=0;
    // Input the array (1 based indexing)
    for(int i=1 ; i<=n ; i++){
        scanf("%d",&a[i]);
    }
    merge_sort()
    heap_sort(a);
    quick_sort(a,1,8);
    for(int i=1 ; i<=8 ; i++){
        printf("%d ",a[i]);
    }
}