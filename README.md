# minish
### A minimal shell with pipes

The purpose of `minish` isn't to replace any existing useful shells suchs as bash, or zsh, instead it is for me to learn more about the OS concepts used in building a shell.  

It's a minimal shell, however, it does have pipe and redirection functionality.  
Something like this would work:
```
find . | grep src | wc | wc -l
```
It's a useless command, but it works.


## Download
```
git clone https://github.com/breakthatbass/minish.git
```

## Build
```
make
```

## Run
```
cd dist
./minish
```

## Exit Minish
```
exit
```

## Run Tests
```
make tests
```

## Usage
You use it like any other Unix shell. However, unlike most toy/project Unix shells, with `minish` you can use multiple pipes. 

## ToDo

1. add tests for redirection functions
2. add arrow key usage
3. add history