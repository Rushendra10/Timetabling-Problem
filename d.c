#include<stdio.h>
#include<stdlib.h>

struct Student {
    int id;
    int ug;
    int num_courses;
    int* courses;
};

struct Faculty {

    int id;
    int free_time[6][8];   
    int num_courses;
    int* courses;
};

typedef struct Student Student;
typedef struct Faculty Faculty;

int num_faculty, num_course, num_students, num_classroom = 0;


// ----------------------------- UTILITY FUNCTIONS -----------------------------------------------//


void print_fac_cou_graph(int fac_cou_graph[num_faculty][num_course]){

    for (int i=0; i<num_faculty; i++){
        for (int j=0; j<num_course; j++){
            printf("%d ", (fac_cou_graph[i][j]));
        }

        printf("\n");
    }
}

void print_stu_cou_graph(int stu_cou_graph[3][num_course]){

    for (int i=0; i<3; i++){
        for (int j=0; j<num_course; j++){
            printf("%d ", (stu_cou_graph[i][j]));
        }

        printf("\n");
    }
}

int isStudentFree(int scg[3][num_course], int ug, int color){

    for (int i=0; i<num_course; i++){

        if (scg[ug][i]==color){
            return 0;
        }
    }

    return 1;
}

const char* courses[12] = {"CP", "DLD", "OC", "M1", "DSA", "M2", "BEC", "SS", "DBMS", "CA", "ADSA", "M3"};

void format_print(int a, int b){

    printf("%10s (%d)", courses[a], b);
}

void print_dashed_lines(){

    printf("\n");

    for (int i=0; i<100; i++){
        printf("-");
    }

    printf("\n");
}

// ----------------------------- REQUIRED FUNCTIONS -----------------------------------------------//

void getData(){

    printf("Enter the number of faculty: ");
    scanf("%d", &num_faculty);

    printf("Enter the number of courses offered: ");
    scanf("%d", &num_course);

    printf("Enter the total number of students: ");
    scanf("%d", &num_students);

    printf("Enter the number of classrooms available: ");
    scanf("%d", &num_classroom);
}

void getStudentEnrollment(Student* s){

    int ug1c, ug2c, ug3c;

    //-------------For UG-1 students--------------//

    printf("Enter the number of courses for UG-1: ");
    scanf("%d", &ug1c);

    s[0].num_courses=ug1c;

    s[0].courses = malloc(ug1c*sizeof(int));

    printf("Enter the course id (i.e. 1,2,3 etc) for UG-1 one after the other (press enter after every course):\n");

    for (int i=0; i<ug1c; i++){

        int course;
        scanf("%d", &course);
        s[0].courses[i] = course;

    }

    //-------------For UG-2 students--------------//

    printf("Enter the number of courses for UG-2: ");
    scanf("%d", &ug2c);

    s[1].num_courses=ug2c;
    s[1].courses = malloc(ug2c*sizeof(int));

    printf("Enter the course id (i.e. 1,2,3 etc) for UG-2 one after the other (press enter after every course):\n");

    for (int i=0; i<ug2c; i++){

        int course;
        scanf("%d", &course);
        s[1].courses[i] = course;

    }

    //-------------For UG-3 students--------------//


    printf("Enter the number of courses for UG-3: ");
    scanf("%d", &ug3c);

    s[2].num_courses=ug3c;
    s[2].courses = malloc(ug3c*sizeof(int));

    printf("Enter the course id (i.e. 1,2,3 etc) for UG-3 one after the other (press enter after every course):\n");

    for (int i=0; i<ug3c; i++){

        int course;
        scanf("%d", &course);
        s[2].courses[i] = course;

    }

}


void getCourseOffered(Faculty* f){

    for (int i=0; i<num_faculty; i++){

        int num;

        printf("Enter the number of courses offered by faculty id %d: ", i);

        scanf("%d", &num);

        f[i].num_courses = num;

        f[i].courses = malloc(num*sizeof(int));

        printf("Enter the course id of the courses offered by faculty id %d (i.e. 101,103 etc) one after the other:\n", i);

        for (int j=0; j<num; j++){

            int course;

            scanf("%d", &course);

            f[i].courses[j] = course;
        }

    }

}


void getInitialTimeSlot(Faculty* f){

    printf("Assuming the classes are from 9-5 per day. For each faculty, for each day from Monday to Friday enter 8 binary inputs\n");

    for (int i=0; i<num_faculty; i++){

        printf("For faculty id %d:\n", i);

        for (int j=0; j<6; j++){

            printf("Day %d:", j+1);

            scanf("%d %d %d %d %d %d %d %d", &f[i].free_time[j][0], &f[i].free_time[j][1], &f[i].free_time[j][2], &f[i].free_time[j][3], &f[i].free_time[j][4], &f[i].free_time[j][5], &f[i].free_time[j][6], &f[i].free_time[j][7]);
        }
        
    }

}

void generateGraph(Faculty* f, Student* s, int fac_cou_graph[num_faculty][num_course], int stu_cou_graph[3][num_course]){

    // Faculty Course graph

    for (int i=0; i<num_faculty; i++){
        for (int j=0; j<num_course; j++){
            fac_cou_graph[i][j] = 0;
        }
    }

    for (int i=0; i<num_faculty; i++){

        for (int j=0; j<num_course; j++){

            for (int k=0; k<f[i].num_courses; k++){
                if (f[i].courses[k]==j){
                    fac_cou_graph[i][j] = 1;
                    break;
                }
                
            }
        }
    }

    //----------------------------------------------------------------------

    // Student Course graph

    for (int i=0; i<3; i++){
        for (int j=0; j<num_course; j++){
            stu_cou_graph[i][j] = 0;
        }
    }

    for (int i=0; i<3; i++){

        for (int j=0; j<num_course; j++){

            for (int k=0; k<s[i].num_courses; k++){
                if (s[i].courses[k]==j){
                    stu_cou_graph[i][j] = 1;
                    break;
                }
                
            }
        }
    }
    
}


int getAvailableTimeSlot(Faculty* f, int id, int fcg[num_faculty][num_course], int day, int ind){

    for(int i=ind; i<8; i++){

        if (f[id].free_time[day][i]==1){
            int j=0;
        
            for (j=0; j<num_course; j++){
                if (fcg[id][j]==((i+1)*11)){
                    break;
                }
            }

            if (j==num_course){
                return ((i+1)*11);
            }
        }
    }

    return -1;

}

int course_hours[12] = {0};
int color_usage[9] = {0};

//logic is that first you got a color from getAvai(). Now check is the ug batch taking that course is free at that color
// if not, get the next slot of faculty that is later than the current slot. 
// do this until the student is free in that color slot.
// Then you can color that color in both the graphs.

void colorEdges(Student* s, Faculty* f, int fcg[num_faculty][num_course], int scg[3][num_course], int day){

    for (int i=0; i<num_faculty; i++){

        for (int j=0; j<num_course; j++){

            if (course_hours[j]<3){

                if (fcg[i][j]==1){

                    int color = getAvailableTimeSlot(f, i, fcg, day, 0);  //change here for day thing

                    int r = 1;

                    while (color_usage[color/11]>6){

                        color = getAvailableTimeSlot(f, i, fcg, day, r);
                        r++;
                    }

                    for (int x=0; x<3; x++){
                        if (scg[x][j]==1){

                            while(isStudentFree(scg, x, color)!=1){

                                color = getAvailableTimeSlot(f, i, fcg, day, (color/11));

                                if (color==-1){
                                    break;
                                }
                            }

                            if (color!=-1){

                                fcg[i][j] = color;
                                scg[x][j] = color;

                                color_usage[color/11]++; 

                                course_hours[j]++;

                            }
                        }
                    }
                }
            }
        }
    }
}



void generateTimetable(int mon_fcg[num_faculty][num_course], int mon_scg[3][num_course], int tue_fcg[num_faculty][num_course], int tue_scg[3][num_course], int wed_fcg[num_faculty][num_course], int wed_scg[3][num_course], int thu_fcg[num_faculty][num_course], int thu_scg[3][num_course], int fri_fcg[num_faculty][num_course], int fri_scg[3][num_course], int sat_fcg[num_faculty][num_course], int sat_scg[3][num_course], int ug){

    printf("%20s", "9:00AM");
    printf("%16s", "10:00AM");
    printf("%16s", "11:00AM");
    printf("%16s", "12:00PM");
    printf("%16s", "1:00PM");
    printf("%16s", "2:00PM");
    printf("%16s", "3:00PM");
    printf("%16s", "4:00PM");

    printf("\n\n");


    int class1=0;
    int class2=0;

    if (ug==0){

        class1=101;
        class2=102;
    }

    else if (ug==1){
        class1=103;
        class2=104;
    }

    else {
        class1=105;
        class2=106;
    }

    printf("Mon: ");

    for (int i=1; i<9; i++){

        int color = i*11;

        int cflag=0;

        for (int j=0; j<num_faculty; j++){
            for (int k=0; k<num_course; k++){
                
                if (mon_fcg[j][k]==color){

                    if (mon_scg[ug][k]==color){

                        // printf("   %s (%d)   ", courses[k], class1);
                        format_print(k, class1);
                        cflag=1;
                    }
                }
            }
        }

        if (cflag==0){
            // printf("     //////   ");
            printf("%-10s//////", "");
        }
    }
    printf("\n");


    printf("Tue: ");

    for (int i=1; i<9; i++){

        int color = i*11;
        int cflag=0;

        for (int j=0; j<num_faculty; j++){
            for (int k=0; k<num_course; k++){
                
                if (tue_fcg[j][k]==color){

                    if (tue_scg[ug][k]==color){

                        // printf("   %s (%d)   ", courses[k], class1);
                        format_print(k, class1);
                        cflag=1;
                    }
                }
            }
        }

        if (cflag==0){
            // printf("     //////   ");
            printf("%-10s//////", "");
        }
    }
    printf("\n");

    printf("Wed: ");

    for (int i=1; i<9; i++){

        int color = i*11;
        int cflag=0;

        for (int j=0; j<num_faculty; j++){
            for (int k=0; k<num_course; k++){
                
                if (wed_fcg[j][k]==color){

                    if (wed_scg[ug][k]==color){

                        // printf("   %s (%d)   ", courses[k], class1);
                        format_print(k, class1);
                        cflag=1;
                    }
                }
            }
        }

        if (cflag==0){
            // printf("     //////   ");
            printf("%-10s//////", "");
        } 
    }
    printf("\n");

    printf("Thu: ");

    for (int i=1; i<9; i++){

        int color = i*11;
        int cflag=0;

        for (int j=0; j<num_faculty; j++){
            for (int k=0; k<num_course; k++){
                
                if (thu_fcg[j][k]==color){

                    if (thu_scg[ug][k]==color){

                        // printf("   %s (%d)   ", courses[k], class1);
                        format_print(k, class1);
                        cflag=1;
                    }
                }
            }
        }

        if (cflag==0){
            // printf("     //////   ");
            printf("%-10s//////", "");
        }
    }
    printf("\n");

    printf("Fri: ");

    for (int i=1; i<9; i++){

        int color = i*11;
        int cflag=0;

        for (int j=0; j<num_faculty; j++){
            for (int k=0; k<num_course; k++){
                
                if (fri_fcg[j][k]==color){

                    if (fri_scg[ug][k]==color){

                        // printf("   %s (%d)   ", courses[k], class1);
                        format_print(k, class1);
                        cflag=1;
                    }
                }
            }
        }

        if (cflag==0){
            // printf("     //////   ");
            printf("%-10s//////", "");
        }
    }
    printf("\n");

    printf("Sat: ");

    for (int i=1; i<9; i++){

        int color = i*11;
        int cflag=0;

        for (int j=0; j<num_faculty; j++){
            for (int k=0; k<num_course; k++){
                
                if (sat_fcg[j][k]==color){

                    if (sat_scg[ug][k]==color){

                        // printf("   %s (%d)   ", courses[k], class1);
                        format_print(k, class1);
                        cflag=1;
                    }
                }
            }
        }

        if (cflag==0){
            // printf("     //////   ");
            printf("%-10s//////", "");
        }
    }
    printf("\n");


}


int main(void){

    getData();

    //------------Initialising Faculties and Students---------------//

    Faculty* f = malloc(num_faculty*sizeof(Faculty));
    Student* s = malloc(3*sizeof(Student));

    for (int i=0; i<num_faculty; i++){

        f[i].id=i;
    }

    getStudentEnrollment(s);

    getCourseOffered(f);

    getInitialTimeSlot(f);


    int mon_fcg[num_faculty][num_course];
    int mon_scg[3][num_course];
    generateGraph(f, s, mon_fcg, mon_scg);

    int tue_fcg[num_faculty][num_course];
    int tue_scg[3][num_course];
    generateGraph(f, s, tue_fcg, tue_scg);
    
    int wed_fcg[num_faculty][num_course];
    int wed_scg[3][num_course];
    generateGraph(f, s, wed_fcg, wed_scg);

    int thu_fcg[num_faculty][num_course];
    int thu_scg[3][num_course];
    generateGraph(f, s, thu_fcg, thu_scg);
    
    int fri_fcg[num_faculty][num_course];
    int fri_scg[3][num_course];
    generateGraph(f, s, fri_fcg, fri_scg);
    
    int sat_fcg[num_faculty][num_course];
    int sat_scg[3][num_course];
    generateGraph(f, s, sat_fcg, sat_scg);

    printf("\n-------------GENERATE GRAPHS--------------------\n\n");
    printf("Faculty Course Graph (rows are faculties and columns are courses)\n\n");
    print_fac_cou_graph(mon_fcg);
    printf("\n");
    printf("\nStudent Course Graph (rows are groups of students (i.e. UG-1, UG-2 and Ug-3) and columns are courses)\n\n");
    print_stu_cou_graph(mon_scg);

    printf("\n");

    printf("\n-------------COLOURED GRAPHS--------------------\n\n");

    colorEdges(s, f, mon_fcg, mon_scg, 0);
    colorEdges(s, f, tue_fcg, tue_scg, 1);
    colorEdges(s, f, wed_fcg, wed_scg, 2);
    colorEdges(s, f, thu_fcg, thu_scg, 3);
    colorEdges(s, f, fri_fcg, fri_scg, 4);
    colorEdges(s, f, sat_fcg, sat_scg, 5);

    printf("\nMonday\n");
    printf("Coloured faculty course graph\n\n");
    print_fac_cou_graph(mon_fcg);
    printf("\nColoured student course graph\n");
    print_stu_cou_graph(mon_scg);
    print_dashed_lines();

    printf("\nTuesday\n");
    printf("Coloured faculty course graph\n\n");
    print_fac_cou_graph(tue_fcg);
    printf("\nColoured student course graph\n");
    print_stu_cou_graph(tue_scg);
    print_dashed_lines();

    printf("\nWednesday\n");
    printf("Coloured faculty course graph\n\n");
    print_fac_cou_graph(wed_fcg);
    printf("\nColoured student course graph\n");
    print_stu_cou_graph(wed_scg);
    print_dashed_lines();

    printf("\nThursday\n");
    printf("Coloured faculty course graph\n\n");
    print_fac_cou_graph(thu_fcg);
    printf("\nColoured student course graph\n");
    print_stu_cou_graph(thu_scg);
    print_dashed_lines();

    printf("\nFriday\n");
    printf("Coloured faculty course graph\n\n");
    print_fac_cou_graph(fri_fcg);
    printf("\nColoured student course graph\n");
    print_stu_cou_graph(fri_scg);
    print_dashed_lines();

    printf("\nSaturday\n");
    printf("Coloured faculty course graph\n\n");
    print_fac_cou_graph(sat_fcg);
    printf("\nColoured student course graph\n");
    print_stu_cou_graph(sat_scg);
    print_dashed_lines();


    printf("\n\n-------------UG1 TIMETABLE--------------------\n\n");

    generateTimetable(mon_fcg, mon_scg, tue_fcg, tue_scg, wed_fcg, wed_scg, thu_fcg, thu_scg, fri_fcg, fri_scg, sat_fcg, sat_scg, 0);

    printf("\n\n-------------UG2 TIMETABLE--------------------\n\n");

    generateTimetable(mon_fcg, mon_scg, tue_fcg, tue_scg, wed_fcg, wed_scg, thu_fcg, thu_scg, fri_fcg, fri_scg, sat_fcg, sat_scg, 1);

    printf("\n\n-------------UG3 TIMETABLE--------------------\n\n");

    generateTimetable(mon_fcg, mon_scg, tue_fcg, tue_scg, wed_fcg, wed_scg, thu_fcg, thu_scg, fri_fcg, fri_scg, sat_fcg, sat_scg, 2);

    print_dashed_lines();

    return 0;
}   