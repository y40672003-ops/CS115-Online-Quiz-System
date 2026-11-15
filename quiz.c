#include <stdio.h>
#include <stdlib.h>
#include <conio.h>      

struct Question
{
    int ID;
    char ques[200];
    char options[4][100];
    int correct;
};

struct username
{
    char username[30];
    char password[30];
};

struct result
{
    char username[30];
    int total;
    int score;
};


void myStrcpy(char dest[], char src[]);
int myStrcmp(char [],char []);

void mainMenu();
void adminMenu();
void studentMenu(char *username);

int  adminLogin();
int  studentLogin(char *username);   
void studentRegister();

void addQuestion();
void viewQuestions();
void editQuestion();
void deleteQuestion();

void takeQuiz(char *username);
void saveResult(char *username, int score, int total);
void viewMyResults(char *username);
void viewAllResults();

void getPassword(char *pass);       
int readNumber();
void clearScreen();

int main() {
    mainMenu();
    return 0;
}

int myStrcmp(char str1[],char str2[])
{
    int cmp,index=0;
    while (1)
    {
        cmp=str1[index]-str2[index];
        if(cmp!=0)
        return cmp;
        if (str1[index] == '\0')
        return 0;
        index = index + 1;
    }
}

void myStrcpy(char dest[], char src[])
{
    int index=0;
    while( src[index] != '\0')
    {
        dest[index]=src[index];
        index ++;
    }
    dest[index]= '\0';
}

void mainMenu()
{
    char username[30];
    int num;
    while (1)
    {
        clearScreen();
        printf("                              ONLINE QUIZ SYSTEM                                       \n");
        printf("1. Admin log in: \n");
        printf("2. Student log in: \n");
        printf("3. Student register: \n");
        printf("4. Exit\n");
        printf("Enter a number between 1 to 4:\n");
        num = readNumber();
        switch (num)
        {
            case 1:
            if (adminLogin() == 1)
            {
                adminMenu();
            }
            else
            {
                printf("Please enter the correct password or username\n");
                printf("Press any key to continue...\n");
                getch();
            }
            break;

            case 2:
            if(studentLogin(username) == 1)
            {
                studentMenu(username);
            }    
            else
            {
                printf("Please enter the correct password or username\n");
                printf("Press any key to continue...\n");
                getch();
            }
            break;
    
            case 3:
            studentRegister();
            break;
            
            case 4:
            return;
            default:
            printf("Invalid input\n");
            printf("Press any key to continue...\n");
            getch();
            break;
        }
    }
}

int  adminLogin()
{
    int a;
    int b;
    char username[30] = "Yasir1234";
    char password[30]= "Yasir1234";
    char user[30];
    char word[30];
    clearScreen();
    printf("                              ADMIN LOGIN                                       \n");
    printf("Enter your user name please:\n");
    scanf("%29s", user);
    printf("Enter your password please:\n");
    getPassword(word);
    a = myStrcmp(username, user);
    b = myStrcmp(password, word);
    if(a == 0 && b == 0)
    return 1;
    else
    return 0;
}

void adminMenu()
{
    int b;
    while (1)
    {
        clearScreen();
        printf("                              ADMIN MENU                                       \n");
        printf("1. Add question: \n");
        printf("2. View all questions: \n");
        printf("3. Edit question: \n");
        printf("4. Delete question: \n");
        printf("5. View all student results: \n");
        printf("6. Log out: \n");
        printf("Enter a number between 1 to 6:\n");
        b = readNumber();        
        switch (b)
        {
            case 1:
            addQuestion();
            break;
            case 2:
            viewQuestions();
            break;
            case 3:
            editQuestion();
            break;
            case 4:
            deleteQuestion();
            break;
            case 5:
            viewAllResults();
            break;
            case 6:
            return;
            default:
            printf("Please enter a correct input\n");
            printf("Press any key to continue...\n");
            getch();
            break;
        }
    }
}

void addQuestion()
{
    struct Question q;
    struct Question temp;
    FILE *fp;
    int count;
    char key;
    while (1)
    {
        count = 0;
        fp = fopen("question.dat", "rb");
        if (fp != NULL)
        {
            while (fread(&temp, sizeof(temp), 1, fp))
            {
                count++;
            }
            fclose(fp);
        }
        q.ID = count + 1;    
        clearScreen();
        printf("                              ADDING QUESTIONS                                       \n");
        printf("Enter the questions:\n");
        scanf(" %199[^\n]", q.ques);
        for (int i = 0; i < 4; i++)
        {
            printf("Enter %d option:\n", i+1);
            scanf(" %99[^\n]", q.options[i]);
        }
        while (1)
        {
            printf("Enter the correct option between 1 to 4\n");
            q.correct = readNumber();
            if (q.correct >= 1 && q.correct <= 4)
            {
                break;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
        fp=fopen("question.dat", "ab");
        if (fp == NULL)
        {
            printf("Could not open the file\n");
            printf("Press any key to continue\n");
            getch();
            return;
        }
        fwrite(&q, sizeof(q), 1, fp);
        fclose(fp);
        printf("Question added successfully\n");
        printf("Want to add another question(1 for yes, any other key for no):\n");
        key = getch();
        if (key != '1')
        {
            break;
        }
    }
    printf("Press any key to continue...\n");
    getch();
}

void viewQuestions()
{
    struct Question q;
    FILE *fp;
    int b = 0;
    clearScreen();
    printf("                              ALL QUESTIONS                                       \n");    
    fp = fopen("question.dat", "rb");
    if(fp == NULL)
    {
        printf("No question found\n");
        printf("Press any key to continue\n");
        getch();
        return;    
    }
    while(fread(&q, sizeof(q), 1, fp))
    {
        printf("%d\n", q.ID);
        printf("%s\n", q.ques);
        for (int i = 0; i < 4; i++)
        {
            printf("%d: %s\n", i+1, q.options[i]);
        }
        printf("The correct answer is %d\n", q.correct);
        printf("\n");
        b += 1;
    }
    if(b==0)
    {
        printf("There is no question\n");
    }
    fclose(fp);
    printf("Press any key to continue...\n");
    getch();
}

void studentRegister()
{
    struct username a;
    struct username b;
    FILE *dp;
    clearScreen();
    printf("                              STUDENT REGISTER                                       \n");
    printf("Please enter a username:\n");
    scanf("%29s", a.username);
    printf("Please enter a password:\n");
    getPassword(a.password);
    dp = fopen("users.dat", "rb");
    if(dp != NULL)
    {
        while (fread(&b, sizeof(a), 1, dp))
        {
            int g;
            g = myStrcmp(a.username, b.username);
            if(g == 0)
            {
                printf("The username already exists, please change it\n");
                printf("Press any key to continue...\n");
                getch();
                fclose(dp);
                return;
            } 
        }
    fclose(dp);
    }
    dp = fopen("users.dat", "ab");
    if (dp == NULL)
    {
        printf("Could not open the file\n");
        printf("Press any key to continue\n");
        getch();
        return; 
    }
    fwrite(&a, sizeof(a), 1, dp);
    fclose(dp);
    printf("Registered successfully\n");
    printf("Press any key to continue...\n");
    getch();
}

int  studentLogin(char *username)
{
    struct username d;
    char typeduser[30];
    char typedpass[30];
    FILE *yz;
    clearScreen();
    printf("                              STUDENT LOGIN                                       \n");
    printf("Enter your username:\n");
    scanf("%29s", typeduser);
    printf("Enter your password:\n");
    getPassword(typedpass);
    yz = fopen("users.dat", "rb");
    if (yz == NULL)
    {
        return 0;
    }
    while (fread(&d, sizeof(d), 1, yz))
    {
        int a, b;
        a = myStrcmp(d.username, typeduser);
        b = myStrcmp(d.password, typedpass);
        if(a == 0 && b == 0)
        {
            myStrcpy(username, typeduser);
            fclose(yz);
            return 1;
        }
    }
    fclose(yz);
    return 0;
}

void studentMenu(char *username)
{
    while (1)
    {
        int d;
        clearScreen();
        printf("                              STUDENT MENU                                       \n");
        printf("Welcome to student menu %s\n", username);        
        printf("1. Take quiz:\n");
        printf("2. View your result:\n");
        printf("3. Log out\n");
        printf("Enter a number between 1 to 3:\n");
        d = readNumber();
        switch (d)
        {
            case 1:
            takeQuiz(username);
            break;
            case 2:
            viewMyResults(username);
            break;
            case 3:
            return;
            default:
            printf("Invalid input\n");
            printf("Press any key to continue...\n");
            getch();
            break;
        }
    }
}

void takeQuiz(char *username)
{
    struct Question q;
    FILE *hi;
    int score = 0, total = 0, answer;
    hi = fopen("question.dat", "rb");
    if (hi == NULL)
    {
        printf("No questions available\n");
        printf("Press any key to continue\n");
        getch();
        return;
    }
    while (fread(&q, sizeof(q), 1, hi))
    {
        clearScreen();
        printf("%s\n", q.ques);
        for (int i = 0; i < 4; i++)
        {
            printf("%d: %s\n", i+1, q.options[i]);
        }
        while (1)
        {            
            printf("Enter your answer between 1 to 4\n");
            answer = readNumber();
            if (answer >= 1 && answer <= 4)
            {
                break;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
        if (answer == q.correct)
        {
            printf("Correct answer\n");
            score++;
        }
        else
        {
            printf("Wrong answer\n");
        }
        printf("Press any key to continue\n");
        getch();
        total += 1;
    }
    fclose(hi);
    if (total == 0)
    {
        printf("No question available\n");
        printf("Press any key to continue\n");
        getch();
    }
    else if(total > 0)
    {
        printf("You scored %d out of %d\n", score, total);
        saveResult(username, score, total);
        printf("Press any key to continue\n");
        getch();
    }
}

void saveResult(char *username, int score, int total)
{
    struct result r;
    FILE *ef;
    myStrcpy(r.username, username);
    r.score = score;
    r.total = total ;
    ef = fopen("results.dat", "ab");
    if (ef == NULL)
    {
        printf("Could not save result\n");
        printf("Press any key to continue\n");
        getch();
        return;        
    }
    fwrite(&r, sizeof(r), 1, ef);
    fclose(ef);
}

void viewMyResults(char *username)
{
    struct result r;
    int counter = 0;
    FILE *fp;
    clearScreen();
    printf("                              MY RESULTS                                       \n");
    fp = fopen("results.dat", "rb");
    if (fp == NULL)
    {
        printf("No result found\n");
        printf("Press any key to continue\n");
        getch();
        return;        
    }
    while (fread(&r, sizeof(r), 1, fp))
    {
        int a;
        a = myStrcmp(r.username, username);
        if (a == 0)
        {
            printf("%s\n",r.username);
            printf("You scored %d out of %d\n\n", r.score, r.total);
            counter += 1;
        }        
    }
    fclose(fp);
    if (counter == 0)
    {
        printf("No result found\n");
    }
    printf("Press any key to continue\n");
    getch();
}

void viewAllResults()
{
    struct result r;
    FILE *fp;
    int counter = 0;
    clearScreen();
    printf("                              ALL STUDENT RESULTS                                       \n");
    fp = fopen("results.dat", "rb");
    if (fp == NULL)
    {
        printf("No result found\n");
        printf("Press any key to continue\n");
        getch();
        return;        
    }
    while (fread(&r, sizeof(r), 1, fp))
    {
        printf("%s\n", r.username);
        printf("Total: %d\n", r.total);
        printf("Score: %d\n", r.score);
        printf("\n");
        counter++;
    }
    fclose(fp);
    if (counter == 0)
    {
        printf("No result found\n");
    }
    printf("Press any key to continue\n");
    getch();
}

void deleteQuestion()
{
    struct Question q;
    FILE *fp;
    FILE *fd;
    int id, found = 0, newid = 1;
    clearScreen();
    printf("                              DELETE QUESTION                                       \n");
    printf("Please enter ID of the question:\n");
    id = readNumber();
    fp = fopen("question.dat", "rb");
    if (fp == NULL)
    {
        printf("No questions found\n");
        printf("Press any key to continue\n");
        getch();
        return;        
    }
    fd = fopen("temp.dat", "wb");
    if (fd == NULL)
    {
        fclose(fp);
        printf("Could not create temporary file\n");
        printf("Press any key to continue\n");
        getch();
        return;        
    }
    while (fread(&q, sizeof(q), 1, fp))
    {
        if (id == q.ID)
        {
            found++;
        }
        else
        {
            q.ID = newid;
            newid++;
            fwrite(&q, sizeof(q), 1, fd);
        }
    }
    fclose(fp);
    fclose(fd);
    if (found >= 1)
    {
        remove("question.dat");
        rename("temp.dat", "question.dat");
        printf("Question deleted. IDs have been renumbered\n");
    }
    if(found == 0)
    {
        remove("temp.dat");
        printf("ID wasn't found\n");
    }
    printf("Press any key to continue\n");
    getch();
}

void editQuestion()
{
    struct Question q;
    int id, found = 0;
    FILE *fp;
    FILE *fd;
    fp = fopen("question.dat", "rb");
    clearScreen();
    printf("                              EDIT QUESTION                                       \n");
    printf("Enter question ID:\n");
    id = readNumber();
    if (fp == NULL)
    {
        printf("No questions found\n");
        printf("Press any key to continue\n");
        getch();
        return;        
    }
    fd = fopen("temp.dat", "wb");
    if (fd == NULL)
    {
        fclose(fp);
        printf("Could not create temporary file\n");
        printf("Press any key to continue\n");
        getch();
        return;        
    }
    while (fread(&q, sizeof(q), 1, fp))
    {
        if (id == q.ID)
        {
            found++;
            printf("Current question: %s\n", q.ques);
            printf("Enter the new question:\n");
            scanf(" %199[^\n]", q.ques);
            for (int i = 0; i < 4; i++)
            {
                printf("Enter %d option:\n",i + 1);
                scanf(" %[^\n]", q.options[i]);
            }
            while (1)
            {
                printf("Enter the correct option between 1 to 4\n");
                q.correct = readNumber();
                if (q.correct >= 1 && q.correct <= 4)
                {
                    break;
                }
                else
                printf("Invalid input\n");
            }            
        }
        fwrite(&q, sizeof(q), 1, fd);
    }
    fclose(fp);
    fclose(fd);
    if (found >= 1)
    {
        remove("question.dat");
        rename("temp.dat", "question.dat");
        printf("Question updated\n");
    }
    if(found == 0)
    {
        remove("temp.dat");
        printf("ID wasn't found\n");
    }
    printf("Press any key to continue\n");
    getch();
}

void getPassword(char *pass)
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == '\r')
        {
            break;
        }
        else if (ch == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
            
        }
        else if (i < 29)
        {
            pass[i] = ch;
            i++;
            printf("*");
        }

    }
       pass[i] = '\0';
       printf("\n");
}

int readNumber()
{
    int num, okay, c;
    okay = scanf("%d", &num);
    while ((c = getchar()) != '\n');
    if (okay != 1)
    {
        return 0;
    }
    else 
    return num;
}

void clearScreen()
{
    system("cls");
}