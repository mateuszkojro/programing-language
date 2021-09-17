# Unnamed programing language

This programing language has been created for the Object oriented programing class 

## Compiling and development

### Binaries

To download compiled binary files for windows and linux go to:

<https://github.com/mateuszkojro/programing-language/releases>

and look for the assets tab. Pdf source documentaton can be found in the same places

### Source code

To download source:

```bash
git clone --recursive https://github.com/mateuszkojro/programing-language
```

or go to: 

<https://github.com/mateuszkojro/programing-language/releases> and find the

Source code packed in `zip` ot `tar.gz` archives in Assets section 

Project is based on `CMake` and needs a C++ compiler compatible with ISO C++ 17 standard so the steps are standard:

### 1. Configuring

```bash
cd ./programing-language
cmake -B build
```

### 2. Compiling

```bash
make -C build/
```

### 3. Running

On Windows
```bash
./build/interpreter.exe
```
and on Linux:
```bash
./build/interpreter
```

### 4. Testing
Tests are written using [Catch2]() testing framework and can be run after compiling by typing: 

On linux:
```bash
./build/language/tests
```

and on Windows
```bash
./build/language/tests.exe
```

You should be greated with simple interactive prompt:

```python
=== Unnamed programing languge ===
Compiled with MSVC 1929.0.0 on Sep 17 2021 23:29:44
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
|   `/`    | Floating point division       |   `float`    |
|   `+`    | Floating point addition       |   `float`    |
|   `-`    | Floating point subtraction    |   `float`    |
|   `%`    | Integer modulus               |    `int`     |
|   `//`   | Integer division              |    `int`     |
|   `==`   | Equality comparassion         |  `0` or `1`  |
|   `!-`   | Inequality comparassion       |  `0` or `1`  |
|   `>`    | More than                     |  `0` or `1`  |
|   `<`    | Less than                     |  `0` or `1`  |




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

In this language everything that is not floating point `NaN`, `Null` or `0`
is `True`


`if` statments:
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

`if() {} else {}` statments
```python
=> if (1) {12} else {10}
12
=> if (0) {1} else {10}
10
=> if (1) { do_sth() }
# do_sth() result 
=> if (check_prime(n)) { ... } else { ... }
```

If statments can be to assign values to variables, then the value assigned will 
be the last value in evaluated block or Null if the block does not exist
```python
=> mat x = 1
1
=> x = if (x) {20} else {11}
20
=> x
20 
```

### While loops

While loops will execute statments in coresponding block as long as 
condition is `True`

```python
=> while (i) { ... i=i-1 i }
0
```

While loops also return value 
(Evaluation of the last statment in the block on the last evaluation of the block)

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

Functions can be defined using `fn` keyword:

```python
=> fn two () {2}
Null
```

and called using `()` after function name:

```python
=> two ()
2
```

Functions can have arguments separated by whitespace

```python
=> fn add (a b) {mat x = a+b x}
Null
```

then while calling arguments need to be added that will be passed to function

```python
=> add(2 12)
14
```

## Planned features

- Builtin funtcions support - support for functions defined in C++
- Changing main datatype from `Scalar` to `Matrix`
- Loading files not interactivly
- Oreder of operations in math equations