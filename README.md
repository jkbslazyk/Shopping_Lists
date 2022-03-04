# Shopping_Lists

### Introduction
The program is used to manage shopping lists. Beyond obvious functions like creating, printing and modifying having lists, the program enables user to move product between two other lists, copy or merge shopping lists. Every lists can contain no more than 10 products whereas there is on limit about amount of lists.

### Main
After lauching Menu presents all features and let us choose an operation. Mostly operations requier having any list, so if you choose different operation than creating the first shopping lists you will see a proper message. After finishing every operation you will able to continue work with program as long as you will not require finishing program (typing 0).

### Different types of products
Due to different ways of determination amount of given product there are some additional classes (which are inherited from the base class Product) which allow to choose way of counting our products. Beyond units, sometimes you need to use volume (l/ml) or weight (kg/dag/g). 

### Running
The program can be run without arguments and operated directly by the user or with the use of a file containing values loaded by the program.
