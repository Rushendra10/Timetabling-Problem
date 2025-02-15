# Timetabling Problem in C

This project provides a solution to the timetabling problem using C, aimed at generating a weekly schedule based on input constraints such as the number of classes, faculty availability, and course requirements. The approach leverages **graph coloring** to efficiently assign time slots to classes while avoiding conflicts.

## Key Features
- **Input Constraints**: Accepts parameters including the number of classes, faculty, and courses.
- **Graph Coloring**: Utilizes graph coloring to handle time slot assignments and prevent scheduling conflicts.
- **Output**: Generates a complete timetable for each day of the week.

This solution offers a systematic approach to scheduling problems, ensuring efficient resource allocation


## Implementation Details

- Instructions before running code and the input format:  
  - If you are using VS Code, please make sure that the files explorer on the left side is minimized.  
  - This is to ensure that text does not wrap around and the timetable is printed properly in the right format.  
  - The course IDs should be entered for each UG, and the IDs should range from 0 to 11 (because there are 12 courses).  

- Output Format explained:  
  - The **GENERATED GRAPHS** are the faculty-course graph and the student-course graph.  
  - `0` represents no edge, and `1` represents the existence of an edge.  
  - The **COLORED GRAPHS** are the colored versions of the generated graphs, and they vary based on the day (i.e., Monday, Tuesday, etc.).  
  - `0` represents no edge, and `11, 22, 33, 44, 55, 66, 77, 88` represent the timeslots from 9 AM to 4 PM, respectively.  
  - `1` represents an edge that could not be colored due to the hard constraints.  

- Hard Constraints:  
  - All classes occur between 9 AM to 5 PM.  
  - At any point in time, there can be a maximum of 6 classes going on (because only 6 classrooms are available).  
  - One faculty cannot have more than one class at a time.  

- Soft Constraints:  
  - All UG-1 classes need power sockets, so it is preferable to have classes in rooms 101 and 102.  
  - All UG-2 classes need projectors, so it is preferable to have their classes in rooms 103 and 104.  
  - All UG-3 classes need single chairs, so it is preferable to have their classes in rooms 105 and 106.  
  - All classes should preferably be over as soon as possible so that the later days of the week can be free.  
  - Rooms 101 and 103 have AC, so students want their classes in these rooms.  
  - Faculties prefer to have as many sessions as possible in the morning because students feel sleepy after lunch.  
  - There should be as few classes on Saturday as possible.  

- Assumptions:  
  - 180 students are equally divided into 3 batches (UG1, UG2, and UG3) having 60 students each.  
  - Two faculty members cannot teach the same course.  
  - Two UGs cannot have the same course.  

---

## Logic

- **getData()**:  
  - Takes the user input for the initial data, such as the number of faculty, students, rooms, etc.  

- **getStudentEnrolled()**:  
  - Takes the user input for the courses that each group of students is enrolled in (i.e., which courses for UG-1, UG-2, and so on).  

- **getCourseOffered()**:  
  - Takes the user input for the courses that each faculty member teaches.  

- **getInitialTimeSlot()**:  
  - Takes the user input for the time slots that each faculty member is free for every day of the week.  

### Logic for generateGraph():  

- Based on the input of the user, we will get a faculty-course graph and a student-course graph, using adjacency matrices to represent these graphs.  
- The size of the faculty-course graph adjacency matrix is `(num_faculty * num_courses)`.  
- The size of the student-course graph adjacency matrix is `(num_ugs * num_courses)`.  
- We will generate 6 such pair graphs, each corresponding to a day from Monday to Saturday.  
- These graphs will be colored differently for each day of the week based on the hard constraints.  

### Logic for getAvailableTimeSlots():  

- This function needs to return the next available timeslot based on the hard constraints.  
- For example, if the faculty is not free at 9 AM and 10 AM but available at 11 AM, then 11 AM can be the considered timeslot.  
- First, we go through the free hours of the faculty. Once we get a free slot, we see the faculty-course graph to ensure that the faculty is not taking any other class during that time. Then we return that timeslot (color).  

### Logic for colorEdges():  

- Traverse the faculty-course graph. If we come across a `1`, it means there is an edge, and that faculty teaches that course.  
- Use the **getAvailableTimeSlots()** function to get the time slot the faculty is free on, based on the hard constraints of the faculty.  
- Traverse the student-course graph to find out which UG students have that course. The most important thing is to see if the students have any other class at the timeslot returned by the **getAvailableTimeSlots()** function.  
- If the students are available, color that particular edge in both graphs.  
- If the students are not available in that timeslot, use the **getAvailableTimeSlots()** function until a free timeslot is found for both the faculty and the students, and then color the graphs.  
- Perform this for every day of the week.  

  - Important conditions to enforce:  
    - One color can only be used 6 times (because there are only 6 rooms available at any point in time).  
    - Only 8 colors are available for use because there are only 8 working hours (9 AM to 4 PM) per day.  
    - Each course only has 3 classes per week, so after 3 classes of that course, it will not be repeated.  

### Logic for GenerateTimeTable():  

- Since the **colorEdges()** function has colored the edges based on the hard constraints, we do not need to worry about them now.  
- Traverse the student-course graph, allot rooms based on the soft constraints for each class, and print it.  
- Perform this for every UG.  
