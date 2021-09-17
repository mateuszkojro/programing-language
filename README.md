# Unnamed programing language

This programing language has been created for the Object oriented programing class 

## Compiling and development

To download source:

```bash
git clone --recursive https://github.com/mateuszkojro/programing-language
```

Project is based on `CMake`

## Interpreter:
On Windows
```bash
./interpreter
```
and on Linux:
```bash
./interpreter
```

You should be greated with simple interactive prompt:

```python
=>
```

## Currently supported language features:

###  Not nested math expressions
For example:
```python
=> 2+2
4
=> 3*2
6
=> 12 / 3
4
```
| Operator | Performed operatrion          | Return value |
| :------: | ----------------------------- | :----------: |
|   `*`    | Floating point multiplication |   `float`    |
|   `/`    | Floating point multiplication |   `float`    |
|   `+`    | Floating point multiplication |   `float`    |
|   `-`    | Floating point multiplication |              |
|   `%`    | Integer modulus               |              |
|   `//`   | Integer division              |              |
|   `==`   | Equality comparassion         |              |
|   `!-`   | Inequality comparassion       |              |
|   `>`    | More than                     |              |
|   `<`    | Less thab                     |              |




### Binding and using variables
You can bind variable using `mat` keyword:
```python
=> mat x = 12
12
```
as you can see variable assigments return value that is currently being assigned

You can use variables in math equations
```python 
=> x
12
=> x + 12
24
=> x = x * 3
36
=> x
36
```

### Scopes
Scopes are defined using `{}` and are commonly used in other langugae constructs they always evaluate to the last contained expression. For example:
```python
=> {}
Null
=> {12}
12
=> {12 2}
2
```

Values from outer scope are present and mutable in inner scope:
```python
=> mat x = 12
12
=> { mat z = 20 x=20 x }
20
=> x
20
```

but reverse statment is not true

```python
=> { mat x = 7 }
7
=> x
Null
```


### Conditional statments

```python
=> if (1) {10}
10
=> if (0) {10}
Null
=> mat x = 1
1
=> if (13) {27}
27
=> if (x) {13}
13
```

```python
=> if (1) {12} else {10}
12
=> if (0) {1} else {10}
10
```

```python
=> mat x = 1
1
=> x = if (x) {20} else {11}
20
=> x
20 
```

### While loops

```python
=> while (i) { ... i=i-1 i }
0
```

```python
=> mat x = 0
0
=> mat sum = 0
0
=> mat i = 10
10
=> x = while (i) { sum =sum+i i=i-1 sum }
12
```

### Defining and calling functions

```python
=> fn two () {2}
Null
```

```python
=> two ()
2
```

```python
=> fn add (a b) {mat x = a+b x}
Null
```

```python
=> add(2 12)
14
```

## Planned features

- Builtin funtcions support - support for functions defined in C++