#include<stdio.h>
#include<stdlib.h>

// char* courses[2] = {"ML","blue"};

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

////////////////////////////////////////////

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
    // printf("For each faculty, enter 6 numbers each representing the number of free hours per day from Monday to Saturday\n");

    // for (int i=0; i<num_faculty; i++){

    //     printf("Availability for faculty id %d: ", i+1);

    //     scanf("%d %d %d %d %d %d", &f[i].free_time[0], &f[i].free_time[1], &f[i].free_time[2], &f[i].free_time[3], &f[i].free_time[4], &f[i].free_time[5]);

    // }

    for (int i=0; i<num_faculty; i++){

        printf("For faculty id %d:\n", i);

        for (int j=0; j<6; j++){

            printf("Day %d:", j+1);

            scanf("%d %d %d %d %d %d %d %d", &f[i].free_time[j][0], &f[i].free_time[j][1], &f[i].free_time[j][2], &f[i].free_time[j][3], &f[i].free_time[j][4], &f[i].free_time[j][5], &f[i].free_time[j][6], &f[i].free_time[j][7]);

            // for (int k=0; k<8; k++){

            //     int free;

            //     scanf("%d", &free);

            //     f[i].free_time[j][k] = free;
            // }
        }
        
    }

}

void generateGraph(Faculty* f, Student* s, int fac_cou_graph[num_faculty][num_course], int stu_cou_graph[3][num_course]){

    // printf("inside generate\n");

    // Faculty course graph

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

    // printf("finished generate\n");
    
}

int color_usage[9] = {0};

// void colorGraph(Student* s, Faculty* f, int fcg[num_faculty][num_course], int scg[3][num_course]){

//     for (int i=0; i<num_faculty; i++){

//         int num_colors = 0;
//         for (int x=0; x<6; x++){
//             if (f[i].free_time[0][x]==1){
//                 num_colors++;
//             }
//         }

//         int color_ind = 1;

//         if (num_colors>0){

//             for (int j=0; j<num_course; j++){

//                 if (num_colors>0){

//                     if (fcg[i][j]==1){

//                         for (int k=0; k<3; k++){
//                             if (scg[k][j]==1){

//                                 fcg[i][j] = (color_ind*10) + color_ind;
//                                 scg[k][j] = (color_ind*10) + color_ind;
                                
//                                 num_colors--;
//                                 color_ind++;

//                                 break;
//                             }
//                         }
//                     }
//                 }

//                 else {
//                     break;
//                 }
                
//             }
//         }

//         else {
//             break;
//         }

//     }
// }

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

// int g1etobcolored(int fcg[num_faculty][num_course])

// void colorGraph(Student* s, Faculty* f, int fcg[num_faculty][num_course], int scg[3][num_course]){

//     for (int i=0; i<num_course; i++){

//         for (int j=0; j<num_faculty; j++){

//             if (fcg[j][i]==1){

//                 int color = getAvailableTimeSlot(f, j, 0);  //change here for day thing

                

//             }
//         }
//     }
    
// }

int isStudentFree(int scg[3][num_course], int ug, int color){

    for (int i=0; i<num_course; i++){

        if (scg[ug][i]==color){
            return 0;
        }
    }

    return 1;
}


//logic is that first you got a color from getAvai(). Now check is the ug batch taking that course is free at that color
// if not, get the next slot of faculty that is later than the current slot. 
// do this until the student is free in that color slot.
// Then you can color that color in both the graphs.

void colorGraph(Student* s, Faculty* f, int fcg[num_faculty][num_course], int scg[3][num_course]){

    for (int i=0; i<num_faculty; i++){

        for (int j=0; j<num_course; j++){

            if (course_hours[j]<=3){

                if (fcg[i][j]==1){

                    int color = getAvailableTimeSlot(f, i, fcg, 0, 0);  //change here for day thing

                    int r = 1;

                    while (color_usage[color/11]>6){

                        color = getAvailableTimeSlot(f, i, fcg, 0, r);
                        r++;
                    }

                    for (int x=0; x<3; x++){
                        if (scg[x][j]==1){

                            while(isStudentFree(scg, x, color)!=1){

                                color = getAvailableTimeSlot(f, i, fcg, 0, (color/11));

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


int main(void){

    getData();

    //------------Initialising Faculties and Students---------------//

    Faculty* f = malloc(num_faculty*sizeof(Faculty));
    Student* s = malloc(3*sizeof(Student));

    for (int i=0; i<num_faculty; i++){

        f[i].id=i;
    }

    // for (int i=0; i<3; i++){

    //     s[i].id=i;
    // }

    getStudentEnrollment(s);

    getCourseOffered(f);

    // printf("Hello world before timeslot\n");

    getInitialTimeSlot(f);

    // printf("Hello world after ts\n");

    // -----------------------------------------------------------------------------

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

    printf("-------------GENERATE GRAPHS--------------------");
    printf("\n");
    print_fac_cou_graph(mon_fcg);
    printf("\n");
    print_stu_cou_graph(mon_scg);

    printf("\n\n");

    colorGraph(s, f, mon_fcg, mon_scg);

    print_fac_cou_graph(mon_fcg);
    printf("\n");
    print_stu_cou_graph(mon_scg);

    // print_fac_cou_graph(thu_fcg);
    // printf("\n");
    // print_stu_cou_graph(thu_scg);


    // for (int i=0; i<6; i++){
    //     for (int j=0; j<8; j++){
    //         printf("%d ", f[1].free_time[i][j]);
    //     }

    //     printf("\n");
    // }

    // printf("%d", sizeof(f)/sizeof(Faculty));

    // printf("%d", sizeof(Faculty));


    // char* x;

    // scanf("%[^\n]%*c", x);

    // printf("%s", x);

    // printf("%d", s[0].id);
    
    // printf("====================");
    // printf("%d", f[0].id);
    // printf("%d", f[0].courses[0]);
    // printf("%d", f[0].courses[1]);
    // printf("%d", f[0].courses[2]);
    // printf("%d\n", f[0].courses[3]);
    
    // printf("%d", sizeof(f[1].courses));


    return 0;
}   