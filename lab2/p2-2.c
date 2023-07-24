#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student{
	char *name;
	int student_id;
	char *major;
}Student;

int main(int argc, char** args)
{
	char *input_path, *output_path;
	FILE *fi, *fo;

	int num;
	int i;

	Student* student;

	input_path = args[1];
	output_path = args[2];

	fi = fopen(input_path, "r");
	fo = fopen(output_path, "w");
	
	fscanf(fi, "%d", &num);
	student = (Student*)malloc(sizeof(Student)*num);

	for(int i=0;i<num;i++){
		student[i].name = (char*)malloc(sizeof(char)*30);
		student[i].major = (char*)malloc(sizeof(char)*30);
		fscanf(fi,"%s %d %s", student[i].name, &student[i].student_id, student[i].major);
	}
	
	for(int i=0;i<num;i++){
		fprintf(fo,"%-8s %-15d %-10s\n", student[i].name, student[i].student_id, student[i].major); 
	}
	
	for(int i=0;i<num;i++){
		free(student[i].name);
		free(student[i].major);
	}
	free(student);
	fclose(fi);
	fclose(fo);
}
