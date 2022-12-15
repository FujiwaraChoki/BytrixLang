# Bytrix

Bytrix is an interpreted programming language that is designed to be easy to learn and use. It is a dynamically typed language, which means that you don't have to declare the type of a variable before using it. Bytrix is also a garbage collected language, which means that you don't have to worry about memory management.

## Usage

### Windows

```cmd
bytrix <file name>
```

### Linux

```bash
./bytrix <file name>
```

## Installation

### Windows

1. Download the latest release from [here](https://github.com/FujiwaraChoki/BytrixLang/releases/tag/latest_windows).
2. Move binary to your `C:\Windows` folder.
3. Run `setx path "%path%;C:\Windows"` to add the binary to your path.

### Linux

1. Download the latest release from [here](https://github.com/FujiwaraChoki/BytrixLang/releases/tag/latest_linux).
2. Move binary to your `/usr/local/bin` folder.
3. Run `chmod +x /usr/local/bin/bytrix` to make it executable.

## Compile from source

1. Clone the repository
```bash
git clone https://github.com/FujiwaraChoki/BytrixLang.git
```

2. Go to the source folder
```bash
cd BytrixLang/src
```

3. Compile
```
clang++ Bytrix.cpp -o bytrix
```

## Examples

### Hello World

```python
/* Hello World in Bytrix */
print "Hello World"
```

### Ask user their name and output it

```python
/* Ask user their name and output it */
input name -p "What is your name? "
print "Hello $name! Nice to meet you!"
```
