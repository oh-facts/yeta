#include "yt_vector.h"

void yk_yektor_resize(YK_Yektor *vector)
{
    vector->capacity *= 2;
    vector->data = realloc(vector->data, vector->capacity * vector->element_size);
    if (vector->data == NULL)
    {
        perror("YK_Yektor resizing failed");
        exit(EXIT_FAILURE);
    }
}

void yk_yektor_innit(YK_Yektor *vector, size_t size, size_t element_size)
{

    vector->data = malloc(size * element_size);
    if (vector->data == NULL)
    {
        perror("YK_Yektor data allocation failed");
        free(vector);
        exit(EXIT_FAILURE);
    }

    vector->element_size = element_size;
    vector->size = 0;
    vector->capacity = size;
}

void *yk_yektor_push(YK_Yektor *vector, void *element)
{
    if (vector->size >= vector->capacity)
    {
        yk_yektor_resize(vector);
    }

    void *dest = (char *)vector->data + (vector->size * vector->element_size);

    vector->size++;
    memcpy(dest, element, vector->element_size);
    
    return dest;
}

void *yk_yektor_push_deep(YK_Yektor *vector, void *element, void (*copy_element)(void *dest, const void *src))
{
    if (vector->size >= vector->capacity)
    {
        yk_yektor_resize(vector);
    }

    void *dest = (char *)vector->data + (vector->size * vector->element_size);

    vector->size++;

    copy_element(dest, element);
    return dest;
}

void *yk_yektor_insert(YK_Yektor *vector, void *element, size_t index)
{
    if (index > vector->size)
    {
        size_t new_size = index + 1;
        if (new_size > vector->capacity)
        {
            yk_yektor_resize(vector);
        }
        vector->size = new_size;
    }

    void *dest = (char *)vector->data + ((index + 1) * vector->element_size);
    void *src = (char *)vector->data + (index * vector->element_size);
    size_t bytes_to_move = (vector->size - index) * vector->element_size;
    memmove(dest, src, bytes_to_move);

    dest = (char *)vector->data + (index * vector->element_size);
    memcpy(dest, element, vector->element_size);

    vector->size++;
    return dest;
}

void yk_yektor_set(YK_Yektor *vector, void *element, size_t index)
{
    if (index >= vector->capacity)
    {
        yk_yektor_resize(vector);
    }

    void *dest = (char *)vector->data + (index * vector->element_size);
    memcpy(dest, element, vector->element_size);

    if (index >= vector->size)
    {
        vector->size = index + 1;
    }
}

void *yk_yektor_get(YK_Yektor *vector, size_t index)
{

    if (index < vector->size)
    {
        return (char *)vector->data + (index * vector->element_size);
    }
    else
    {
        // pitiful
        printf("error \n");
        return NULL;
    }
}

// works but come back here.

void yk_yektor_pop(YK_Yektor *vector)
{
    if (vector->size > 0)
    {
        vector->size--;
    }
}

void *yk_yektor_pop_get(YK_Yektor *vector)
{
    void *out = (char *)vector->data + (vector->size * vector->element_size);
    if (vector->size > 0)
    {
        vector->size--;
    }
    return out;
}

void yk_yektor_destroy(YK_Yektor *vector)
{
    free(vector->data);
}

void yk_yektor_print(YK_Yektor *vector)
{
    if (vector == NULL)
    {
        printf("Yektor is NULL\n");
        return;
    }

    printf("Yektor Size: %zu\n", vector->size);
    printf("Yektor Capacity: %zu\n", vector->capacity);
    printf("Yektor Element Size: %zu\n", vector->element_size);

    printf("Yektor Contents:\n");

    if (vector->data == NULL)
    {
        printf("Yektor is empty\n");
        return;
    }

    for (size_t i = 0; i < vector->size; i++)
    {
        void *element = yk_yektor_get(vector, i);
        printf("[%zu]: %p\n", i, element);
    }
}