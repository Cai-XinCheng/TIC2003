# TIC2003

### Iteration 1:

- SIMPLE  
  - Single procedure  
  - Print / read statements  
  - Assignment statement with single integers / variables  
```
procedure p {  // single procedure
  read x;  // read statement
  varX = x;  // assignment statement with variable
  varY = 0;  // assignment statement with integer
  print x;  // print statement
  print y;  // print statement
}
```
- Database  
  - Design entities: statement, read, print, assignment, variable, constant, procedure.  
- PQL  
  - One declaration of a single synonym  
  - One Select clause  
  - A single synonym in the Select clause  
```
procedure p;
Select p
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
  - Next/Next*
  - Parent/Parent*
  - Uses
  - Modifies
  - Call/Calls*
