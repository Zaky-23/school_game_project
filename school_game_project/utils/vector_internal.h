#ifndef VECTOR_INTERNAL_H_
#define VECTOR_INTERNAL_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#pragma region vector_init
#define vector_init_(type, type_name)													\
struct type_name type_name ## _init(size_t capacity)									\
{																						\
	type *ptr = calloc(capacity, sizeof(type));											\
	return (struct type_name)															\
		{																				\
			.data = ptr,																\
			.capacity = capacity,														\
			.size = 0																	\
		};																				\
}
#pragma endregion

#pragma region vector_init_with_data
#define vector_init_with_data(type, type_name)											\
struct type_name type_name ## _init_with_data(type *data, size_t size)					\
{																						\
	if(!data) return (struct type_name) { .data = NULL, .size = 0, .capacity = 0 };		\
	struct type_name v = type_name ## _init(size);										\
	v.size = size;																		\
	memcpy(v.data, data, size * sizeof(type));											\
	return v;																			\
}
#pragma endregion

#pragma region vector_destroy
#define vector_destroy_(type, type_name)												\
void type_name ## _destroy(struct type_name *vec)										\
{																						\
	vec->capacity = 0;																	\
	vec->size = 0;																		\
	free(vec->data);																	\
	vec->data = NULL;																	\
}
#pragma endregion

#pragma region vector_push
#define vector_push_(type, type_name)													\
bool type_name ## _push(struct type_name *vec, type element)							\
{																						\
	if ((vec->size + 1) >= vec->capacity)												\
	{																					\
		vec->capacity += 1;																\
		type *temp = realloc(vec->data, vec->capacity * 3 * sizeof(type));				\
		if (temp)																		\
		{																				\
			vec->data = temp;															\
		} else {																		\
			return false;																\
		}																				\
	}																					\
	vec->data[vec->size] = element;														\
	vec->size += 1;																		\
	return true;																		\
}
#pragma endregion

#pragma region vector_at
#define vector_at_(type, type_name)														\
bool type_name ## _at(struct type_name *vec, size_t index, type *out)					\
{																						\
	if(index < 0 || index > vec->capacity || !out) return false;						\
	*out = vec->data[index];															\
	return true;																		\
}

#define vector_clear_(type, type_name)													\
void type_name ## _clear(struct type_name *vec)											\
{																						\
	memset(vec->data, 0, vec->size * sizeof(type));										\
	vec->size = 0;																		\
}
#pragma endregion

#pragma region vector_pop
#define vector_pop_(type, type_name)													\
bool type_name ## _pop(struct type_name *vec, type *out)								\
{																						\
	if(vec->size == 0) return false;													\
	*out = vec->data[--vec->size];														\
	return true;																		\
}
#pragma endregion

#pragma region vector_implementation_macro
#define vector_implementation_(type, type_name)											\
vector_init_(type, type_name)															\
vector_init_with_data(type, type_name)													\
vector_destroy_(type, type_name)														\
vector_push_(type, type_name)															\
vector_at_(type, type_name)																\
vector_clear_(type, type_name)															\
vector_pop_(type, type_name)
#pragma endregion

#pragma region vector_declaration_macro
#define vector_declaration_(type, type_name)											\
struct type_name type_name ## _init(size_t capacity);									\
struct type_name type_name ## _init_with_data(type *data, size_t size);					\
void			 type_name ## _destroy(struct type_name *vec);							\
bool			 type_name ## _push(struct type_name *vec, type element);				\
bool			 type_name ## _at(struct type_name *vec, size_t index, type *out);		\
void			 type_name ## _clear(struct type_name *vec);							\
bool			 type_name ## _pop(struct type_name *vec, type *out);					
#pragma endregion

#pragma region vector_definition_macro
#define vector_definition(type, type_name)												\
typedef struct type_name																\
{																						\
	size_t size;																		\
	size_t capacity;																	\
	type *data;																			\
} type_name ## _t;																		\
vector_declaration_(type, type_name)
#pragma endregion

#pragma region vector_implementation_macro
#define vector_type_implementation(type, type_name)										\
vector_implementation_(type, type_name)
#pragma endregion
#endif