Trying to metaprogram in C
Basically uses a transpiler 
to convert "meta" code to C

wip. 

-----
Goals:
ctfe
templates
reflection
introspection
-----


How it works
-----
read meta file
make sense of said file
write to c file
compile/build generated file
------

Usage 
eg-1
```
@types : [int, Bar] [Goob, Bar]
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

eg-2
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