#include<stdio.h>
#include<time.h>
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void insertion(int A[], int front, int rear) {
    int i, j;
    int key;
 
    for (i = front + 1; i <= rear; ++i) {
        key = A[i];
        j = i - 1;
        while (j >= front && A[j] > key) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}
void insmergesort(int arr[], int l, int r)
{
	if(r - l < 5)
        insertion(arr,l, r);
	if (l < r)
	{
		int m = l+(r-l)/2;
		insmergesort(arr, l, m);
		insmergesort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}
int main()
{
	clock_t start, end;
        double time1,time2,time3;
	int n,a[1000000+1],i;
	printf ( "# n best av. worst case\n" );
	for(n=0;n<=1000000;n+=100000)
	{
		start = clock();
        	srand(time(0));
        	for(i=0;i<=n;i++)
        	{
                	a[i]=rand();
        	}
		insmergesort(a,0,n-1);
		end = clock();
    		time1 = ((double) (end - start)) / CLOCKS_PER_SEC;
		start = clock();
                for(i=0;i<n;i++)
                {
                        a[i]=i;
                }
                insmergesort(a,0,n-1);
                end = clock();
                time2 = ((double) (end - start)) / CLOCKS_PER_SEC;
		start = clock();
                for(i=0;i<n;i++)
                {
                        a[i]=n-i;
                }
                insmergesort(a,0,n-1);
                end = clock();
                time3 = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("%d %.3lf %.3lf %.3lf\n",n,time2,time1,time3);
	}
	return 0;
}
