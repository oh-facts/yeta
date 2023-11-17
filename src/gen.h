int add_int_(int a,int b)
{
    return a + b;
}

typedef struct array_int_
{
    int* data;
    int size;
    int max_size;
}array_int_;

void init_array_int_(array_int_ *array, int max_size)
{
    array->data = malloc(max_size * sizeof(int));
    array->size = 0;
    array->max_size = max_size;
}
