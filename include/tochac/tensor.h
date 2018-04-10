#ifndef TOCHA_TENSOR_H_
# define TOCHA_TENSOR_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOCHA_TENSOR_FLOAT 0
#define TOCHA_TENSOR_INT 1


typedef struct
{
    int type;
    size_t size;
    int* dims;
    size_t ndims;
    size_t total_len;
    void* data;
} tocha_tensor_s;

typedef struct
{
    tocha_tensor_s* list;
    size_t size;
} tocha_tensors_s;

static void tocha_tensor_init_f64_0(tocha_tensor_s* t, double* data);
static void tocha_tensor_init_f64_1(tocha_tensor_s* t, int d1, double* data);
static void tocha_tensor_init_f64_2(tocha_tensor_s* t, int d1, int d2, double* data);
static void tocha_tensor_init_f64_3(tocha_tensor_s* t, int d1, int d2, int d3, double* data);
static void tocha_tensor_init_f64_4(tocha_tensor_s* t, int d1, int d2, int d3, int d4,
				    double* data);
static void tocha_tensor_free(tocha_tensor_s* t);
static void tocha_tensor_print(const tocha_tensor_s* t);


static void tocha_tensors_init(tocha_tensors_s* list);
static void tocha_tensors_add(tocha_tensors_s* list, tocha_tensor_s* t);
static void tocha_tensors_save(const tocha_tensors_s* list, const char* path);
static void tocha_tensors_load(tocha_tensors_s* list, const char* path);
static void tocha_tensors_free(tocha_tensors_s* list);
static void tocha_tensors_print(const tocha_tensors_s* list);


static inline void tocha_tensor_init_f64_0(tocha_tensor_s* t, double* data)
{
    if (data == NULL)
	data = malloc(sizeof(double));

    t->type = TOCHA_TENSOR_FLOAT;
    t->size = 8;
    t->dims = NULL;
    t->ndims = 0;
    t->total_len = 1;
    t->data = data;
}

static inline void tocha_tensor_init_f64_1(tocha_tensor_s* t, int d1, double* data)
{
    size_t len = d1;
    if (data == NULL)
	data = malloc(len * sizeof(double));

    t->type = TOCHA_TENSOR_FLOAT;
    t->size = 8;
    t->dims = malloc(1 * sizeof(int));
    t->dims[0] = d1;
    t->ndims = 1;
    t->total_len = len;
    t->data = data;
    
}

static inline void tocha_tensor_init_f64_2(tocha_tensor_s* t, int d1, int d2, double* data)
{
    size_t len = d1 * d2;
    if (data == NULL)
	data = malloc(len * sizeof(double));

    t->type = TOCHA_TENSOR_FLOAT;
    t->size = 8;
    t->dims = malloc(2 * sizeof(int));
    t->dims[0] = d1;
    t->dims[1] = d2;
    t->ndims = 2;
    t->total_len = len;
    t->data = data;
}

static inline void tocha_tensor_init_f64_3(tocha_tensor_s* t, int d1, int d2, int d3, double* data)
{
    size_t len = d1 * d2 * d3;
    if (data == NULL)
	data = malloc(len * sizeof(double));

    t->type = TOCHA_TENSOR_FLOAT;
    t->size = 8;
    t->dims = malloc(3 * sizeof(int));
    t->dims[0] = d1;
    t->dims[1] = d2;
    t->dims[2] = d3;
    t->ndims = 3;
    t->total_len = len;
    t->data = data;
}

static inline void tocha_tensor_init_f64_4(tocha_tensor_s* t, int d1, int d2, int d3, int d4,
					   double* data)
{
    size_t len = d1 * d2 * d3 * d4;
    if (data == NULL)
	data = malloc(len * sizeof(double));

    t->type = TOCHA_TENSOR_FLOAT;
    t->size = 8;
    t->dims = malloc(4 * sizeof(int));
    t->dims[0] = d1;
    t->dims[1] = d2;
    t->dims[2] = d3;
    t->dims[3] = d4;
    t->ndims = 4;
    t->total_len = len;
    t->data = data;
}

static inline void tocha_tensor_free(tocha_tensor_s* t)
{
    free(t->data);
    free(t->dims);
}

static inline void tocha_tensor_print(const tocha_tensor_s* t)
{
    const char* types = "fi";
    
    printf("%c%d(", types[t->type], (int) t->size * 8);

    for (size_t i = 0; i < t->ndims; ++i)
    {
	printf("%d", t->dims[i]);
	if (i + 1 != t->ndims)
	    printf("*");
    }

    printf(") {");

    double* data = t->data;
    for (size_t i = 0; i < t->total_len; ++i)
    {
	printf("%G", data[i]);
	
	if (i + 1 != t->total_len)
	{
	    printf(", ");
	    if (i > 15 && i + 2 != t->total_len)
	    {
		printf("..., ");
		i = t->total_len - 2;
	    }
	}
    }
    
    printf("}\n");
}


static inline void tocha_tensors_init(tocha_tensors_s* list)
{
    list->list = malloc(10 * sizeof(tocha_tensor_s));
    list->size = 0;
}

static inline void tocha_tensors_add(tocha_tensors_s* list, tocha_tensor_s* t)
{
    if (list->size && list->size % 10 == 0)
	list->list = realloc(list->list, (list->size + 10) * sizeof(tocha_tensor_s));
    memcpy(&list->list[list->size], t, sizeof(tocha_tensor_s));
    ++list->size;
}

static inline void tocha_tensors_save(const tocha_tensors_s* list, const char* path)
{
    FILE* f = fopen(path, "wb");
    uint16_t ntensors = list->size;

    fwrite(&ntensors, sizeof(uint16_t), 1, f);

    for (size_t i = 0; i < list->size; ++i)
    {
	tocha_tensor_s* t = &list->list[i];
	uint8_t type = t->type;
	uint8_t size = t->size;
	uint8_t ndims = t->ndims;
	fwrite(&type, sizeof(uint8_t), 1, f);
	fwrite(&size, sizeof(uint8_t), 1, f);
	fwrite(&ndims, sizeof(uint8_t), 1, f);

	fwrite(t->dims, sizeof(int), t->ndims, f);
	fwrite(t->data, t->size, t->total_len, f);
    }

    fclose(f);
}

static inline void tocha_tensors_load(tocha_tensors_s* list, const char* path)
{
    FILE* f = fopen(path, "rb");
    tocha_tensors_init(list);
    
    uint16_t ntensors;
    fread(&ntensors, sizeof(uint16_t), 1, f);

    for (uint16_t i = 0; i < ntensors; ++i)
    {
	
	tocha_tensor_s tensor;
	uint8_t type;
	uint8_t size;
	uint8_t ndims;	
	fread(&type, sizeof(uint8_t), 1, f);
	fread(&size, sizeof(uint8_t), 1, f);
	fread(&ndims, sizeof(uint8_t), 1, f);
	tensor.type = type;
	tensor.size = size;
	tensor.ndims = ndims;
	tensor.dims = malloc(tensor.ndims * sizeof(int));
	fread(tensor.dims, sizeof(int), tensor.ndims, f);

	tensor.total_len = 1;
	for (uint8_t i = 0; i < tensor.ndims; ++i)
	    tensor.total_len *= tensor.dims[i];

	tensor.data = malloc(tensor.total_len * tensor.size);
	fread(tensor.data, tensor.size, tensor.total_len, f);
	tocha_tensors_add(list, &tensor);
    }

    fclose(f);
}

static inline void tocha_tensors_free(tocha_tensors_s* list)
{
    for (size_t i = 0; i < list->size; ++i)
	tocha_tensor_free(list->list + i);
    free(list->list);
}

static inline void tocha_tensors_print(const tocha_tensors_s* list)
{
    for (size_t i = 0; i < list->size; ++i)
    {
	tocha_tensor_print(list->list + i);
	printf("\n");
    }
}


#endif
