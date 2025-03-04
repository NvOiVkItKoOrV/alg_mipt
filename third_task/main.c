#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int *elem_1, int *elem_2)
{
    int sw = *elem_1;
    *elem_1 = *elem_2;
    *elem_2 = sw;
}

void my_bubble_sort(int data[], int size)
{
    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size-i-1; j++)
        {
            if (data[j] > data[j+1])
                swap(&data[j], &data[j+1]);
        }
    }
}


void my_shaker_sort(int data[], int size)
{
    int swapped = 1;
    int start = 0;
    int end = size - 1;

    while (swapped)
    {
        swapped = 0;
        // left-->right
        for (int i = start; i < end; i++)
        {
            if (data[i] > data[i+1])
            {
                swap(&data[i], &data[i+1]);
                swapped = 1;
            }
        }

        if (!swapped)
            break;

        swapped = 0;
        end--;

        // left<--right
        for (int i = end - 1; i >= start; i--)
        {
            if (data[i] > data[i+1])
            {
                swap(&data[i], &data[i+1]);
                swapped = 1;
            }
        }
        start++;
    }
}


void my_comb_sort(int data[], int size)
{
    int gap = size;
    float shrink = 1.3;
    int sorted = 0;

    while (!sorted)
    {
        gap = (int)(gap / shrink);
        if (gap <= 1)
        {
            gap = 1;
            sorted = 1;
        }

        for (int i = 0; i + gap < size; i++)
        {
            if (data[i] > data[i+gap])
            {
                swap(&data[i], &data[i+gap]);
                sorted = 0;
            }
        }
    }
}


int is_sorted(int data[], int size)
{
    for (int i = 0; i < size-1; i++)
    {
        if (data[i] > data[i+1]) 
            return 0;
    }
    return 1;
}



void generate_array(int data[], int size, float sortedness)
{
    for (int i = 0; i < size; i++)
        data[i] = i;

    int shuffle_count = (int)(size * (1 - sortedness));
    for (int i = 0; i < shuffle_count; i++)
    {
        int a = rand() % size;
        int b = rand() % size;
        swap(&data[a], &data[b]);
    }
}


long long measure_time_ns(void (*sort_func)(int[], int), int data[], int size)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); 
    sort_func(arr, size);
    clock_gettime(CLOCK_MONOTONIC, &end);   

    long long time_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    return time_ns;
}


int main()
{
    srand(time(NULL));


    int sizes[] = {10, 100, 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    int data_sz = sizeof(sizes)/sizeof(sizes[0]);


    float sortedness_levels[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    int sortedness_sz = sizeof(sortedness_levels)/sizeof(sortedness_levels[0]);


    for (int i = 0; i < data_sz; i++)
    {
        int data_size = sizes[i];
        int *arr = (int*)calloc(data_size, sizeof(int));


        for (int j = 0; j < sortedness_sz; j++)
        {
            float sortedness = sortedness_levels[j];
            generate_array(arr, data_size, sortedness);


            long long time_bubble_ns = measure_time_ns(my_bubble_sort, arr, data_size);
            long long time_shaker_ns = measure_time_ns(my_shaker_sort, arr, data_size);
            long long time_comb_ns   = measure_time_ns(my_comb_sort, arr, data_size);


            printf("Size: %d, Sortedness: %.2f, Bubble: %lld ns, Shaker: %lld ns, Comb: %lld ns\n",
                    data_size, sortedness, time_bubble_ns, time_shaker_ns, time_comb_ns);
        }
        free(arr);
    }

    return 0;
}