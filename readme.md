Trying to metaprogram in C

wip. 

-----
Goals:
ctfe
templates
reflection
introspection
-----



Work flow
-----
read meta file
make sense of said file
write to c file
compile/build generated file
------

Usage
```
@types := [int,float], [float, double]
void foo<T,A>(T a, A b)
{
    //do something
}
```

should generate
```
float foo_int_float(int a, float b)
{
    //do something
}

double foo_float_double(float a, double b)
{
    //do something
}
```