Name: Rushendra Sidibomma
Roll No.: S20200010179

-> Instructions before running code:
    -> If you are using VS Code, please make sure that the files explorer on the left side is minimised.
    -> This is to ensure that text does not wrap around and the timetable is printed properly in the right format.

-> Hard Constraints:
    -> All classes occur between 9am to 5pm.
    -> At any point of time, there can be a maximum of 6 classes going on (because only 6 classrooms available).
    -> One faculty cannot have more than 1 class at a time.
    -> 

-> Soft Constraints:
    -> All UG-1 classes occur only in rooms 101 or 102 because they need power sokcets.
    -> All UG-2 classes occur only in rooms 103 or 104 because they need projectors.
    -> All UG-3 classes occur only in rooms 105 or 106 because they need single chairs.
    -> All classes should preferably be over as soon as possible so that the later days of the week can be free.
    -> Rooms 101 and 103 have AC so students want their classes in these rooms,
    -> 

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
    -> size (num_faculty*num_courses)
    -> size (num_ugs*num_courses)

Logic for getAvailableTimeSlots():

    -> This function needs to retun the next available timeslot based on the hard constraints.
    -> For example, the faculty is not free at 9am and 10am but available at 11am. So 11am can be the timeslot considered.

    -> So first, we go through the free hours of the faculty and once we get a freeslot, we see the faculty-course graph to ensure that
    that he is not taking any other class during that time. Then we return that timeslot (color).

Lofic for colorGraph():

    -> 
