security_code_generator
=======================

Quickly generate a great number of Security Codes by C command line program


## How to compile it

Under linux, execute `make` in the source code folder, and a `codegen` program will be compiled

## How to use it

Execute the `codegen` program directly, it will promote you the usage information

```
./codegen
请输入唯一码长度(大于8)、需要生成的唯一码数量、起始流水号、名称和纯数字开关(Y或者N):
Please input code length(bigger than 8), the total number of codes, start serial number, csv file name and the switch of only numbers (Y or N):
codegen 18 1000000 1010 Name N

或输入唯一码长度(大于8)、需要生成的唯一码数量、起始流水号、名称、纯数字开关(Y或者N)和页码:
Please input code length(bigger than 8), the total number of codes, start serial number, csv file name, the switch of only numbers (Y or N) and the page number:
codegen 18 1000000 1010 Name Y Page

```

Once the program was executed successfully, a csv file will be generated. For example, you execute the program like `./codegen 9 10 100 TestName N`, it will generate csv file like following:

TestName.csv --
```
100,4P96D6FAM
101,4V96E65EH
102,4K96E7HCF
103,4R96E7F8D
104,4D96E8984
105,4596E9384
106,4J96E9D8S
107,4C96EA789
108,4B96EBPES
109,4S96EBEAM
```

If you execute the program with full number switch as 'Y': `./codegen 9 10 100 TestName Y`, it will generate csv file like following:

TestName.csv --
```
100,741401008
101,741410501
102,741411125
103,741411315
104,741411625
105,741411819
106,741411180
107,741411405
108,741411552
109,741412162
```

If you run it with a page parameter like `./codegen 10 15 201 TestName2 N Page001`, it will generate TestName2.csv like:

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

If you run it with a page parameter and full number request like `./codegen 10 15 201 TestName2 Y Page001`, it will generate TestName2.csv like:

```
Page001,201,1210208353
Page001,202,1210239414
Page001,203,1210243400
Page001,204,1210242624
Page001,205,1210253848
Page001,206,1210253531
Page001,207,1210265167
Page001,208,1210262447
Page001,209,1210300459
Page001,210,1210305581
Page001,211,1210301576
Page001,212,1210306592
Page001,213,1210315890
Page001,214,1210311894
Page001,215,1210320278
```
