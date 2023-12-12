
Trying to metaprogram in C

Basically uses a parser to convert "meta" code to C. Allows C program to make use of ASTs produced by meta code.


-----
### Goals
 1. ctfe 
 2. templates 
 3. reflection 
 4. introspection

----


### How it works


 1. read meta file 
 2. make sense of said file 
 3. write to c file
 4.  compile/build generated file

------

**(Hypothetical) Usage**
The grammar is a wip and goes to changes weekly as I better understand the scopes of this project.
eg -1 
```

@type
enum_types
{
    $A : A, B, C
}

@gen
{
    `typedef enum MyEnum`
    `{`
    `$(enum_types),`
    `MyEnum_COUNT`
    `}MyEnum;`
}

@gen
{
    `char *myenum_string_table[MyEnum_COUNT] =`
    `{`
        `"MyEnum_$(enum_types);"`
    `}`
}
```
Should generate ->
```
---header file---
typedef enum MyEnum
{
  MyEnum_A,
  MyEnum_B,
  MyEnum_C,
  MyEnum_COUNT
}
MyEnum;

extern char *myenum_string_table[3];

// --- c file -----------------------------------

char *myenum_string_table[3] =
{
  "A",
  "B",
  "C",
};
```

eg-2
```
@template : [int, Bar] [Goob, Bar]
void foo<T,A>(T a, A* b)
{
    //do something
}
```

should generate
```
void foo_int_Bar(int a, Bar* b)
{
    //do something
}

void foo_Goob_Bar(Goob a, Bar* b)
{
    //do something
}
```

eg-3
```
@constexpr
int func(int num)
{
    // does some math and returns a number x
}
```

should generate
```
const int FUNC = x;
```


## but why?

I like using C, but C doesn't have metaprogramming, unless you count scuffed macro templates. One day, I came across this article by Ryan Fleury "[Table Driven Code generation](https://www.rfleury.com/p/table-driven-code-generation)". Absolutely genius, changed my understanding of metaprogramming.
