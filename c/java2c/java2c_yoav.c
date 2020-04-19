#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) (void)x
#define ARRAY_SIZE 80

typedef void (*vFunc_t)(void *);
typedef int (*get_num_masters_t)(void *);

typedef enum vMetods{TO_STRING, FINALIZE, SAY_HELLO, NUM_MASTERS} vmethods_t;
/******************** structs ***********************/

char to_string_array[ARRAY_SIZE];
int counter = 0;

typedef struct Class
{
	char *name;
	size_t size;
	struct Class *super;
	vFunc_t (*vFuncTable)[];
}class_t;

typedef struct Object
{
	class_t *meta_data;
}obj_t;

typedef struct Animal
{
	obj_t obj;
	int id;
	int num_legs;
	int num_masters;
}animal_t;

typedef struct Dog
{
	animal_t animal;
	int num_legs;
}dog_t;

typedef struct Cat
{
	animal_t animal;
	char* colors;
	int num_masters;
}cat_t;

typedef struct LegendaryAnimal
{
	cat_t cat;
}legend_t;

/******************* declarations ******************/

void objectFinalize(obj_t *this);
void objectToString(void *pointer);
void animalSayHello(void *pointer);
void animalToString(void *pointer);
void animalFinalize(void *pointer);
void dogSayHello(void *pointer);
void dogFinalize(void *this);
void dogToString(void *pointer);
void catFinalize(void *this);
void catToString(void *pointer);
void catSayHello(void *pointer);
void LegendaryToString(void *pointer);
void LegendaryFinalize(void *this);
void LegendarySayHello(void *pointer);
int animalGetNumMasters(animal_t *this);
void AnimalshowCounter();

/******************** vfunc_tables ***********************/

vFunc_t ObjectVTable[] = {
							animalToString,
							(vFunc_t)objectFinalize,
							AnimalshowCounter,
							(vFunc_t)animalGetNumMasters
};

vFunc_t AnimalVTable[] = {
							animalToString,
							animalFinalize,
							animalSayHello,
							(vFunc_t)animalGetNumMasters
};
	
vFunc_t DogVTable[] = {
						dogToString,
						dogFinalize,
						dogSayHello,
						(vFunc_t)animalGetNumMasters
};

vFunc_t CatVTable[] = {
						catToString,
						catFinalize,
						animalSayHello,
						(vFunc_t)animalGetNumMasters
};

vFunc_t LegendVTable[] = {
							LegendaryToString,
							LegendaryFinalize,
							LegendarySayHello,
							(vFunc_t)animalGetNumMasters
};

/******************** meta_data ***********************/

class_t object_meta = {"Object", sizeof(obj_t), NULL, &ObjectVTable};
class_t animal_meta = {"Animal", sizeof(animal_t), &object_meta, &AnimalVTable};
class_t dog_meta = {"Dog", sizeof(dog_t), &animal_meta, &DogVTable};
class_t cat_meta = {"Cat", sizeof(cat_t), &animal_meta, &CatVTable};
class_t legend_meta = {"LegendaryAnimal", sizeof(legend_t), &legend_meta, &LegendVTable};

/******************** funcs ***********************/

void objectToString(void *pointer){UNUSED(pointer);}

void animalSayHello(void *pointer)
{
	printf("Animal Hello!\n");
	printf("I have %d legs\n", ((animal_t *)(pointer))->num_legs);
}

void animalToString(void *pointer)
{	
	sprintf(to_string_array, 
	        "Animal with ID: %d", ((animal_t *)((animal_t *)pointer))->id);
}

void dogSayHello(void *pointer)
{
	printf("Dog Hello!\n");
	printf("I have %d legs\n", ((dog_t *)((dog_t *)pointer))->num_legs);
}

void dogToString(void *pointer)
{
	sprintf(to_string_array, "Dog with ID: %d", 
			((animal_t *)pointer)->id);
}


void catToString(void *pointer)
{
	sprintf(to_string_array, "Cat with ID: %d",
	 		((animal_t *)pointer)->id);
}

void LegendaryToString(void *pointer)
{
	sprintf(to_string_array, "LegendaryAnimal with ID: %d", 
			((animal_t *)pointer)->id);
}

void LegendarySayHello(void *pointer)
{
	printf("Legendary Hello!\n");
}

void objectFinalize(obj_t *this)
{
	free(this);
}

void animalFinalize(void *this)
{
    printf("animal with id: %d\n", ((animal_t *)this)->id);
	objectFinalize((obj_t *)this);
}

void dogFinalize(void *this)
{
   	printf("Dog with ID: %d\n", ((animal_t *)this)->id);
	objectFinalize((obj_t *)this);
}

void catFinalize(void *this)
{
    printf("Cat with ID: %d\n", ((animal_t *)this)->id);
	objectFinalize((obj_t *)this);
}

void LegendaryFinalize(void *this)
{
   printf("Legend with ID: %d\n", ((animal_t *)this)->id);
	objectFinalize((obj_t *)this);
}

void AnimalshowCounter()
{
	printf("%d\n", counter);
}

int animalGetNumMasters(animal_t *this)
{
	return this->num_masters;
}

void animalCtor(animal_t *this)
{
	static int static_animal_block = 0;

	if (0 == static_animal_block)
	{
		printf("Static block Animal 1\n");
		printf("Static block Animal 2\n");
		++static_animal_block;
	}

	printf("Instance initialization block Animal\n");

	((animal_t *)this)->id = ++counter;
	((animal_t *)this)->num_legs = 5;
	
	printf("Animal Ctor\n");
	((animal_t *)this)->num_masters = 1;
	(*this->obj.meta_data->vFuncTable)[SAY_HELLO](this);

    AnimalshowCounter(NULL);
    (*this->obj.meta_data->vFuncTable)[TO_STRING](this);
	printf("%s\n", to_string_array);
}

void animalCtorInt(animal_t *this, void *num_masters)
{
	printf("Instance initialization block Animal\n");

	((animal_t *)this)->id = ++counter;
	((animal_t *)this)->num_legs = 5;
	printf("Animal Ctor int\n");
	((animal_t *)this)->num_masters = *(int *)num_masters;
}

void dogCtor(dog_t *this)
{
	int i = 2;
	static int static_dog_block = 0;
	
	if(0 == static_dog_block)
	{
		printf("Static block Dog\n");
		++static_dog_block;
	}

	animalCtorInt((animal_t *)this, &i);
	printf("Instance initialization block Dog\n");
	printf("Dog Ctor\n");
	this->num_legs = 4;
}

void catCtor(cat_t *this, char *cat_color)
{
	cat_t *cat = (cat_t *)(this);
	static int static_cat_block = 0;
	animal_t *animal = NULL;

	cat->num_masters = 5;
	
	if (0 == static_cat_block)
	{
		printf("Static block Cat\n");
		++static_cat_block;
	}
	
	if (cat_color == NULL)
	{
		catCtor(this, "black");
		cat->num_masters = 2;
		printf("Cat Ctor\n");
	}
	
	else
	{
		animalCtor((animal_t *)this);
		cat->colors = cat_color;
		printf("Cat Ctor with color: %s\n", cat_color);
	}
}

void legendaryCtor(legend_t *this)
{
	static int static_block = 0;

	if (0 == static_block)
	{
		printf("Static block Legendary Animal\n");
		++static_block;
	}
	
	catCtor((cat_t *)this, NULL);
	
	printf("Legendary Ctor\n");
}

obj_t *objectAlloc(class_t *class)
{
	obj_t *object = (obj_t*)calloc(class->size,1);
    if (NULL == object)
    {
        return NULL;
    }
    object->meta_data = class;

    return object;
}

int main()
{
	animal_t *animal = (animal_t *)objectAlloc(&animal_meta);
	dog_t *dog = (dog_t *)objectAlloc(&dog_meta);
	cat_t *cat = (cat_t *)objectAlloc(&cat_meta);
	legend_t *legendary = (legend_t *)objectAlloc(&legend_meta);
	cat_t *cat_color = NULL;
	animal_t *animals_array[5] = {0};
    int i = 0;
    animalCtor(animal);
   	dogCtor(dog);
    catCtor(cat, NULL);
    legendaryCtor(legendary);
   
   	AnimalshowCounter();
   	
   	printf("%d\n", ((animal_t *)animal)->id);
	printf("%d\n", ((dog_t *)dog)->animal.id);
	printf("%d\n", ((cat_t *)cat)->animal.id);
	printf("%d\n", ((legend_t *)legendary)->cat.animal.id);
	
    free(animal), free(dog), free(cat), free(legendary);
	
	dog = (dog_t *)objectAlloc(&dog_meta);
	cat = (cat_t *)objectAlloc(&cat_meta);
	cat_color = (cat_t *)objectAlloc(&cat_meta);
	legendary = (legend_t *)objectAlloc(&legend_meta);
	animal = (animal_t *)objectAlloc(&animal_meta);
	
    dogCtor(dog);
    catCtor(cat, NULL);
    catCtor(cat_color, "white");
    legendaryCtor(legendary);
	animalCtor(animal);
	
 	animals_array[0] = (animal_t *)dog;
	animals_array[1] = (animal_t *)cat;
	animals_array[2] = (animal_t *)cat_color;
	animals_array[3] = (animal_t *)legendary;
	animals_array[4] = (animal_t *)animal;
	
	for (i = 0; i < 5; ++i)
	{
		(*animals_array[i]->obj.meta_data->vFuncTable)[SAY_HELLO](animals_array[i]);
		printf("%d\n", ((get_num_masters_t)
			((*animals_array[i]->obj.meta_data->vFuncTable)[NUM_MASTERS]))(animals_array[i]));
	}
	
	for (i = 0; i < 5; ++i)
	{
		(*animals_array[i]->obj.meta_data->vFuncTable)[FINALIZE](animals_array[i]);
	}
	
    return 0;
}