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

// int** fac_cou_graph=NULL;
// int** cou_stu_graph=NULL;


void print_fac_cou_graph(int** fac_cou_graph){

    for (int i=0; i<num_faculty; i++){
        for (int j=0; j<num_course; j++){
            printf("%d ", (fac_cou_graph[i][j]));
        }

        printf("\n");
    }
}

void print_stu_cou_graph(int** stu_cou_graph){

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

            printf("Day %d:\n", j+1);

            for (int k=0; k<8; k++){

                int free;

                scanf("%d", &free);

                f[i].free_time[j][k] = free;
            }
        }
        
    }

}

void generateGraph(Faculty* f, Student* s, int** fac_cou_graph, int** stu_cou_graph){

    printf("inside generate\n");

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

    printf("finished generate\n");
    
}

void colorGraph(Student* s, Faculty* f){

    for (int i=0; i<num_faculty; i++){

        int num_colors = 0;
        for (int x=0; x<6; x++){
            if (f[i].free_time[0][x]==1){
                num_colors++;
            }
        }


    }
}

int** allocate_fac_cou_graph(){

    int** g = (int**) malloc(num_faculty*sizeof(int*));

    for (int i=0; i<num_course; i++){

        g[i] = (int*) malloc(num_course*sizeof(int));
    }

    return g;

}

int** allocate_stu_cou_graph(){

    int** g = (int**) malloc(3*sizeof(int*));

    for (int i=0; i<num_course; i++){

        g[i] = (int*) malloc(num_course*sizeof(int));
    }

    return g;

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

    printf("Hello world before timeslot\n");

    getInitialTimeSlot(f);

    printf("Hello world after ts\n");

    // -----------------------------------------------------------------------------

    

    int** mon_fcg = (int**) malloc(num_faculty*sizeof(int*));

    for (int i=0; i<num_course; i++){

        mon_fcg[i] = (int*) malloc(num_course*sizeof(int));
    }

    int** mon_scg = (int**) malloc(3*sizeof(int*));

    for (int i=0; i<num_course; i++){

        mon_scg[i] = (int*) malloc(num_course*sizeof(int));
    }

    generateGraph(f, s, mon_fcg, mon_scg);

    print_fac_cou_graph(mon_fcg);
    print_stu_cou_graph(mon_scg);

    // -----------------------------------------------------------------------------

    int** tue_fcg = (int**) malloc(num_faculty*sizeof(int*));

    for (int i=0; i<num_course; i++){

        tue_fcg[i] = (int*) malloc(num_course*sizeof(int));
    }



    int** tue_scg = (int**) malloc(3*sizeof(int*));

    for (int i=0; i<num_course; i++){

        tue_scg[i] = (int*) malloc(num_course*sizeof(int));
    }

    // --------------------------------------------------------------------------------


    // int** mon_fcg = allocate_fac_cou_graph();
    // int** tue_fcg = allocate_fac_cou_graph();
    // int** wed_fcg = allocate_fac_cou_graph();
    // int** thu_fcg = allocate_fac_cou_graph();
    // int** fri_fcg = allocate_fac_cou_graph();
    // int** sat_fcg = allocate_fac_cou_graph();

    // int** mon_scg = allocate_stu_cou_graph();
    // int** tue_scg = allocate_stu_cou_graph();
    // int** wed_scg = allocate_stu_cou_graph();
    // int** thu_scg = allocate_stu_cou_graph();
    // int** fri_scg = allocate_stu_cou_graph();
    // int** sat_scg = allocate_stu_cou_graph();

    // int** fac_cou_graph = (int**) malloc(num_faculty*sizeof(int*));

    // for (int i=0; i<num_course; i++){

    //     fac_cou_graph[i] = (int*) malloc(num_course*sizeof(int));
    // }

    // int** stu_cou_graph = (int**) malloc(3*sizeof(int*));

    // for (int i=0; i<3; i++){

    //     stu_cou_graph[i] = (int*) malloc(num_course*sizeof(int));
    // }


    
    generateGraph(f, s, mon_fcg, mon_scg);
    // generateGraph(f, s, tue_fcg, tue_scg);
    // generateGraph(f, s, wed_fcg, wed_scg);
    // generateGraph(f, s, thu_fcg, thu_scg);
    // generateGraph(f, s, fri_fcg, fri_scg);
    // generateGraph(f, s, sat_fcg, sat_scg);

    if (mon_fcg==NULL){
        printf("NULL");
    }

    printf("Hello world\n");

    

    printf("\n\n");

    // print_fac_cou_graph(tue_fcg);

    printf("\n\n");

    // print_fac_cou_graph(wed_fcg);

    printf("\n\n");

    printf("Hello world\n");

    
    printf("\n\n");
    
    // print_fac_cou_graph(tue_scg);


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