security_code_generator
=======================

Quickly generate a great number of Security Codes by C command line program


## How to compile it

Under linux, execute `make` in the source code folder, and a `codegen` program will be compiled

## How to use it

Execute the `codegen` program directly, it will promote you the usage information

```
./codegen
请输入唯一码长度(大于8)、需要生成的唯一码数量、起始流水号和名称:
Please input code length(bigger than 8), the total number of codes, start serial number and csv file name:
codegen 18 1000000 1010 Name

或输入唯一码长度(大于8)、需要生成的唯一码数量、起始流水号、名称和页码:
Please input code length(bigger than 8), the total number of codes, start serial number, csv file name and the page number:
codegen 18 1000000 1010 Name Page

```

Once the program was executed successfully, a csv file will be generated. For example, you execute the program like `./codegen 9 10 100 TestName`, it will generate csv file like following:

TestName.csv --
```
100,7FF898V6Z
101,7FF8A9C6J
102,7FF8A23EH
103,7FF8A27J7
104,7FF8A2D42
105,7FF8A3V6J
106,7FF8A36UH
107,7FF8A3C49
108,7FF8A3F6T
109,7FF8A432J
```

If you run it with a page parameter like `./codegen 10 15 201 TestName2 Page001`, it will generate TestName2.csv like:

```
Page001,201,CG786UAAYL
Page001,202,CB78ZC4ARX
Page001,203,C678GDH2GT
Page001,204,CH78NDDA47
Page001,205,C578TE7AL5
Page001,206,CE78CF24U9
Page001,207,CT785FC4D2
Page001,208,CM78946EW7
Page001,209,CM78QAEJRJ
Page001,210,CJ78K352U8
Page001,211,CY7863FCGV
Page001,212,CQ78C4A6S4
Page001,213,CG78F546YM
Page001,214,CW78P5FUZ9
Page001,215,CT7846BX4A
```
