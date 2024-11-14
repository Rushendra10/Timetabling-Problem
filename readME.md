# Timetabling Problem in C

This project provides a solution to the timetabling problem using C, aimed at generating a weekly schedule based on input constraints such as the number of classes, faculty availability, and course requirements. The approach leverages **graph coloring** to efficiently assign time slots to classes while avoiding conflicts.

## Key Features
- **Input Constraints**: Accepts parameters including the number of classes, faculty, and courses.
- **Graph Coloring**: Utilizes graph coloring to handle time slot assignments and prevent scheduling conflicts.
- **Output**: Generates a complete timetable for each day of the week.

This solution offers a systematic approach to scheduling problems, ensuring efficient resource allocation


## Implementation Details
-> Instructions before running code and the input format:
    -> If you are using VS Code, please make sure that the files explorer on the left side is minimised.
    -> This is to ensure that text does not wrap around and the timetable is printed properly in the right format.
    -> The courses_ids should be entered for each UG and the ids should range from 0 to 11 (because there are 12 courses).

-> Output Format explained:
    -> The GENERATED GRAPHS are the faculty-course graph and the student-course graph.
    -> 0 represents no edge and 1 represents the existence of an edge.
    -> The COLORED GRAPHS are the coloured versions of the generated graphs and they vary based the the day (i.e. monday tuesday etc).
    -> 0 represents no edge and 11,22,33,44,55,66,77,88 represents the timeslots from 9am to 4pm respectively.
    -> 1 represents an edge that could not be colored due to the hard constraints.


-> Hard Constraints:
    -> All classes occur between 9am to 5pm.
    -> At any point of time, there can be a maximum of 6 classes going on (because only 6 classrooms available).
    -> One faculty cannot have more than 1 class at a time.
    -> 

-> Soft Constraints:
    -> All UG-1 classes need power sockets so it is preferable to have classes in 101 and 102.
    -> All UG-2 classes need projectors so it is preferable to have their classes in 103 and 104.
    -> All UG-3 classes need single chairs so it is preferable to have their classes in 105 and 106.
    -> All classes should preferably be over as soon as possible so that the later days of the week can be free.
    -> Rooms 101 and 103 have AC so students want their classes in these rooms.
    -> Faculties prefer to have as many sessions as possible in the morning because the students feel sleepy after lunch.
    -> There should be as less classes on Saturday as possible.


-> Assumptions:
    -> 180 students are equally divided into 3 batches (UG1, UG2 and UG3) having 60 students each
    -> Two faculty cannot teach the same course
    -> Two UGs cannot have the same course


---------LOGIC-----------------------------------------------------------------------------------------------------

-> getData() takes the user input for the initial datas such as the the no. of faculty, no. of students, no. of rooms etc
-> getStudentEnrolled() takes the user input for the courses that each group of students are enrolled for i.e. which courses for UG-1, ug-2 and so on.
-> getCourseOffered() takes the user input for the courses that each faculty takes.
-> getInitialTimeSlot() takes the user input for the time slots that each faculty is free on for every day of the week.

Logic for generateGraph():

    -> Based on the input of the user, we will get a faculty-course graph and a student-course graph and we will be using adjacency matrices 
    to represent these graphs.
    -> The size of the faculty-course graph adjacency matrix is (num_faculty*num_courses).
    -> The size of the student-course graph adjacency matrix is(num_ugs*num_courses).
    -> We will generate 6 such pair graphs each corresponding to a day from Monday to Saturday.
    -> These graphs will be colored differently for each day of the week based ont he hard constraints.

Logic for getAvailableTimeSlots():

    -> This function needs to retun the next available timeslot based on the hard constraints.
    -> For example, the faculty is not free at 9am and 10am but available at 11am. So 11am can be the timeslot considered.

    -> So first, we go through the free hours of the faculty and once we get a freeslot, we see the faculty-course graph to ensure that
    that he is not taking any other class during that time. Then we return that timeslot (color).

Logic for colorEdges():

    -> We traverse through the faculty course graph. If we come across a 1, it means there is an edge and that faculty teaches that course.
    -> Then we use the getAvailableTimeSlots() function to get the time slot that the faculty is free on, based on the hard constraints
    of the faculty.
    -> Now we have to traverse the student-course graph and find out which UG students have that course. The most important thing is the
    see if the students have any other class on that timeslot returned by the getAvailableTimeSlots() function.
    -> If the students are available, then we color both that particular edge in both the graphs.
    -> If the students are not available in that timeslot, then we use the getAvailableTimeSlots() function till we get a time slot that
    is free for both the faculty and the student and then color the graphs.
    -> We do this for every day of the week.

    -> Most important conditions to be enforced are:
        -> One color can only be used 6 times (because there are only 6 rooms available at any point of time).
        -> Only 8 colors are available for use because there are only 8 working hours (9am to 4pm) per day.
        -> Each course only has 3 classes per week. So after 3 classes of that course, it will not be repeated.


Logic for GenerateTimeTable():

    -> Since the colorEdges() function has colored the edges based on the hard constraints, we do not need to worry about it now.
    -> We just need to traverse the student-course graph and allot rooms based on the soft constraints for each class and print it.
    -> This will be done for every UG.  
