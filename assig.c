#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct assign{
    int stu_id;
    char stu_name[30];
    int assign_id;
    int due_day,due_month,due_year;
    int sub_day,sub_month,sub_year;
    char submitted;
    float marks;
    float totalmarks;

};
int datelate(struct assign a);
float a_penalty(float marks, int days);
int comparedates(struct assign a);
void loadfromfile();
void savetofile(struct assign a);
void addassignment();
void displayassignment();


 struct assign a[100];
 int i=0;

int main()
{
    int ch;
     loadfromfile(); 
     
    while (1)
    {
        printf("\n Menu");
        printf("\n 1.add assignment submission ");
        printf("\n 2.display assignment ");
        printf("\n 3.exit");
        printf("\n enter your choice:");
        scanf("%d",&ch);
       
        switch (ch) 
        {
            case 1:
               addassignment();
                break;
            case 2:
                displayassignment();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }

    }
     return 0;

}

void addassignment()
{
    printf("\n enter student id :");
    scanf("%d",&a[i].stu_id);
    printf("\n enter student name:");
    scanf("%s",a[i].stu_name);
    printf("\n enter student assignment id :");
    scanf("%d",&a[i].assign_id);
    printf("\n enter student submitted(Y/N):");
    scanf(" %c",&a[i].submitted);

    if(a[i].submitted=='Y'|| a[i].submitted=='y')
    {
        printf("\n enter submission date(dd mm yyyy):");
        scanf("%d %d %d",&a[i].sub_day,&a[i].sub_month,&a[i].sub_year);
        printf("\n enter due date (dd mm yyyy):");
        scanf("%d %d %d",&a[i].due_day,&a[i].due_month,&a[i].due_year);
        printf("\n enter marks:");
        scanf("%f",&a[i].marks);
        if(comparedates(a[i])==1)
        {
        int days = datelate(a[i]);
        float penalty =a_penalty(a[i].marks, days);

        a[i].marks = a[i].marks - penalty;
        }
    }
    else{
        printf("\n status :missing");
    }
   

    savetofile(a[i]);
    i++;


}

void displayassignment()
 {
     printf("\n%-6s %-10s %-8s %-10s %-8s %-10s %-10s %-10s\n", "Stu_ID", "Name", "asssign_ID","Submitted","Sub_dates","Due_date","Marks", "Status");
    printf("----------------------------------------\n");
    for(int j=0;j<i;j++) 
    { 
        printf("\n student id %d",a[j].stu_id); 
        printf("\n student name:%s",a[j].stu_name); 
        printf("\n student assignment id :%d",a[j].assign_id);
         printf("\n student submitted(Y/N): %c",a[j].submitted); 
         if(a[j].submitted == 'Y' || a[j].submitted == 'y')
          {
            printf("\n submission date(dd mm yyyy): %d %d %d",
                         a[j].sub_day, a[j].sub_month, a[j].sub_year);

              if(comparedates(a[j]) == 1)
               printf("\n Status : LATE");
              else
               printf("\n Status : ON TIME");

                printf("\n Marks  : %.2f", a[j].marks);
          }
         else
           {
            printf("\n Status : MISSING");
           }
             }
             }

    int comparedates(struct assign a)
    {
        if(a.sub_year>a.due_year)
        return 1;
        if(a.sub_year<a.due_year)
        return 0;
        if(a.sub_month>a.due_month)
        return 1;
        if(a.sub_month<a.due_month)
        return 0;
        if(a.sub_day>a.due_day)
        return 1;
       
        return 0;

    }
    int datelate(struct assign a)
    {
    int due_total, sub_total;
    due_total = a.due_year * 365 + a.due_month * 30 + a.due_day;
    sub_total = a.sub_year * 365 + a.sub_month * 30 + a.sub_day;

    if(sub_total > due_total)
        return sub_total - due_total;

    return 0;
    }
    float  a_penalty(float marks,int days)
    {
     if(days>=1 && days<=3)
        
          return marks * 0.05;
        
        else if(days>=4 && days<=6)
        
          return marks * 0.07;
        
        else if(days>=7)
        
          return marks * 0.09;
           else
        return 0.0;
        
       



    }   
    
    void savetofile(struct assign a)
{
    FILE *fp = fopen("assig.txt", "a");
    if (fp == NULL)
        return;

    fprintf(fp, "%d %s %d %c %d %d %d %d %d %d %.2f\n", a.stu_id, a.stu_name, a.assign_id, a.submitted,
            a.sub_day, a.sub_month, a.sub_year, a.due_day, a.due_month, a.due_year, a.marks);

    fclose(fp);
}

void loadfromfile()
{
    FILE *fp = fopen("assig.txt", "r");
    if (fp == NULL)
        return;

    while (fscanf(fp, "%d %s %d %c %d %d %d %d %d %d %f", &a[i].stu_id,a[i].stu_name,&a[i].assign_id,&a[i].submitted,
                  &a[i].sub_day,&a[i].sub_month, &a[i].sub_year, &a[i].due_day,&a[i].due_month,&a[i].due_year, &a[i].marks) != EOF)
    {
        i++;
    }

    fclose(fp);
}

    
   



    

   