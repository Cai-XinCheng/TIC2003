# TIC2003

### Iteration 2:

- SIMPLE  
	- +If and while statement
	- +Assignment statements with expressions
```
procedure p {
	flag = 0;
	count = 0;
    cenX = 0;
    cenY = 0;
    read x;
    read y;
    while ((x * x + y * y) != 0) {
        count = count + 1;
        cenX = cenX + x;
        cenY = cenY + y;
        read x;
		read y;
    }
    if (count == 0) then {
        flag = 1;
    } else {
        cenX = cenX / count;
        cenY = cenY / count;
    }
    normSq = cenX * cenX + cenY * cenY;
	print flag;
    print cenX;
    print cenY;
    print normSq;
}
```
- PQL  
```
assign a; while w;
Select a such that Modifies (a, ¡°x¡±) such that Parent* (w, a) such that Next* (1, a)
```

## Database Design  
- ### Entities  
	- stmt
	- read (statement)
	- print (statement)
	- assign (statement)
	- call (statement)
	- while (statement)
	- if (statement)
	- variable
	- constant
	- procedure
	- ### Abstractions
	- Next/Next* (possible to use linked list to implement workflow)
	- Parent/Parent*
	- Uses
	- Modifies
	- Call/Calls*
