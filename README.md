# Routing
# ReadMe

We have implemented **User Friendly Routing Program**.

The main aim of our project is to give minimum time and distance for given source and destination in the graph(source and destination will be entered by the user).

The code takes the input from the input file. As of now, there are 5 input files in the project which represents the 5 different graphs of 5 different cities. We ask the user the city he/she wants to explore and accordingly to that code selects the input file.

Basically, the project has two profiles, first is the Admin profile in which the admin can access the graph and can edit the graph like to add edge or remove edge or to print graph etc, but the changes admin will do will be temporary, if admin wants to do permanent changes he/she have to do changes in the input file.

And the second profile is the User profile in which the user will enter source and destination and output will be the minimum time to reach the destination from source, distance to be covered, time of departure, expected time of arrival, the path he/she has to follow.

As the program is quite user friendly and at every point, it asks the user which task the user wants to perform and the user just have to enter the number of the task and the code will perform that.

Added to all this we have also kept password protection for the admin window, i.e. the person will have to enter the password to access admin facilities.

# Installation:

```bash
git clone https://github.com/dassaniGeet/Routing.git
```

# How to Run the Code:

Firstly user has to download and put all of the following files in the same folder otherwise code will not work fine as in code we are calling various files so those all files should be present at the same place. Files are:

```bash
1. main.c
2. graph.c
3. graph.h
4. conio.h
5. input.txt
6. input_2.txt
7. input_3.txt
8. input_4.txt
9. input_5.txt
10. graphviz.dot
```

Now on the user's terminal, he/she has to compile the code to generate an executable file. Before compiling firstly user has to reach the following folder, in the terminal using commands ```**cd**``` and ```**ls**``` in which the user has stored all the files. For compiling user has the enter the following command on his/her terminal:


```bash
 gcc graph.c main.c 
 ```

When the user will run this command on his/her terminal an executable file will automatically be created in the same folder. Now to run that executable file user has to run the following command on terminal and the program will start working:

```bash
./a.out
```

The program will work in the following manner:

The screen is cleared, then it greets the User, asks the city person wants to explore and asks which profile the person wants to use:
```bash
1. Admin 
2. User  
3. Exit.
```

- **Case 1:**

A person enters '1' i.e. he/she is an admin, then he /she will be asked for the password to confirm whether he/she is an admin or not.

**"All The Changes Done By Admin will be Temporary. If Admin wants to do changes permanently he/she will have to do changes in the input file."**

If the person inputs the wrong password, a message will be printed on the screen as "Wrong password! Please try again." and the person will be taken to the point where it asks for Admin or User.

If the person enters the correct password, then the screen will be cleared and the following option will appear to the user i.e. what task the admin wants to perform:

1. Add Edge

2. Remove Edge

3. Search  Node

4. Search Edge

5. Print Graph

6. Exit

- If admin enters '1', then admin will be asked to enter two vertices to be connected, edge length and traffic on that road, given by the number of vehicles plying on the road. After entering all this the edge will be added to the graph.
- If admin enters '2', then admin will be asked to enter two vertices between which edge is to be removed and after entering, the edge is removed.
- If the admin enters '3', then the admin will be asked to enter the vertex he/she wants to search, if that vertex is connected to at least any one of the vertex, "Found" will be printed else "Not Found!" will be printed.
- If admin enters '4', then admin will be asked two enter two vertices between which edge has to be searched if the edge exists between those vertices the edge length and time will be printed otherwise "Not Found!" will be printed.
- If the admin enters '5', the adjacency list representing the graph will be printed on the screen in a neat manner in which the admin can see his/her changes. The graph visualization(if the number of edges is less than 1000), will be saved as a png file in the same directory.
- If admin enters '6', admin will be taken to the main page i.e. where it asks for Admin or User or Exit.

- **Case 2:**

The person enters '2' i.e. he/she will be taken to the user window and will be asked to enter the source from where he/she wants to start the travel and the destination.

Then in front of him following details will appear:

- Minimum Time Expected
- Distace to be travelled
- Time of Departure
- Expected Time of Arrival
- Path he/she has to travel on.

After these things are printed, the User is asked whether he/she wants to continue. If the user enters 'Y' or 'y' user is taken to the main page i.e. where it is asked Admin or User or Exit, and if the user enters 'N' or 'n' the program is ended.

- **Case 3:**

Person enters '3' the program will be ended.

# Files Description

- **graph.h**

In this file all the user-defined data types i.e. structs are defined here that are used in the code, all typedefs are done in this file only.

Adding to all this, defination of every function used in the code is written here.

- **graph.c**

In this file the codes of all functions are written, we can say core part of program is this file only.

There is no need for the user to open this file until or unless he/she either wants to read the code and understand it or to do any kind of editing in the code.

- **main.c**

This file divides the program into two profiles as described above i.e Admin profile and the User profile.

Whichever profile user will select, this file will direct the code to work in that manner.

This file is basically used to call the functions written in graph.c and to implement them.

- **conio.h**

This file is included only to use one function in the code i.e. the function which clears the screen.

- **input.txt**

There are 5 files of this kind which repreents 5 different graphs of 5 different cities.

From these files, only the code gets the input for making the graph and uses the graph to implement the following functions on it.
