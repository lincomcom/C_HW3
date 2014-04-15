#include <stdio.h>
#include <stdlib.h>
/* leap year return=1,else return=0*/
int Isleap(int year){
    int leap=(year%4==0&&year%100!=0)||year%400==0? 1:0;
    return leap;
}

/* calculates the number of days since January 1, 1753*/
int CalDays(int year, int month, int day){
    int i, j, k, Days=0;

    /*count days till the pre-year*/
    for(i=1753;i<year;i++){
        /*if leap year Days+=366, else Days+=365*/
        Days+=(Isleap(i)==1)? 366: 365;
    }

    /*count days till the pre-month*/
    for(j=1;j<month;j++){
        if(j==2){
            /*if leap year Days+=29, else Days+=28*/
            Days+=(Isleap(year)==1)? 29: 28;
        }
        else if(j==4||j==6||j==9||j==11){
            Days+=30;/*if little month Days+=30*/
        }
        else
            Days+=31;/*if big month Days+=31*/
    }

    /*count days till the pre-day*/
     for(k=1;k<day;k++){
        Days++;
    }
    return Days;
}

/* calculates the number of seconds since 00:00:00*/
int CalSecs(hour, min, sec){
    int i, j, k, secs=0;

    for(i=1;i<=hour;i++){ /*transform hours to secs*/
        secs+=3600;
    }

    for(j=1;j<=min;j++){/*transform mins to secs*/
        secs+=60;
    }

    for(k=1;k<=sec;k++){
        secs++;
    }

    return secs;
}

/*print difference between time1 and time2*/
void PrintDelta(long long deltatosecs){
    printf("\n");

    /*if delta secs=time1-time2<0, print '-'*/
    if(deltatosecs<0){
        printf("-");
        deltatosecs=-1*deltatosecs;
    }

    int deltadays, deltahours, deltamins, deltasecs;
         /*transform delta secs to "deltadays deltahours:deltamins:deltasecs"*/
        deltadays=deltatosecs/86400;
        deltahours=(deltatosecs/3600)%24;
        deltamins=(deltatosecs/60)%60;
        deltasecs=(deltatosecs)%60;

    printf("%d days %d:%d:%d", deltadays, deltahours, deltamins, deltasecs);
}

/*print start*/
void week(int s){
    (s==1)?printf("Mon"):
        (s==2)?printf("Tue"):
            (s==3)?printf("Wed"):
                (s==4)?printf("Thu"):
                    (s==5)?printf("Fri"):
                        (s==6)?printf("Sat"):printf("Sun");
}

int IsBigMon(month){
    if(month==1||month==3||
       month==5||month==7||
       month==8||month==10||
       month==12)
        return 1;

    else
        return 0;
}
void PrintFinal(long long totalsecs){

    int days, hours, mins, secs;
        /*count how many days since 1753/1/1 00:00:00*/
        days=totalsecs/86400;
        hours=(totalsecs/3600)%24;
        mins=(totalsecs/60)%60;
        secs=(totalsecs)%60;
    int StartingDay=(days+1)%7;/*1=Mon,0=Sun*/

    /*count year since 1753/1/1 00:00:00*/
    int year=1753, month=1, day=1;

    while(days>=365+Isleap(year)){
        days-=(Isleap(year)==1)? 366: 365;
            year++;
    }

     /*if days<=31, jump while loop*/
    int endwhile=(days>31)? 1:0;

    while(endwhile){
        days-=IsBigMon(month)? 31:/*if big month days-=31*/
            (month==2)?(28+Isleap(year)):30;
            /*if february  days-=(28+Isleap), else-=30*/
            month++;

        /*days< the days of this month*/
        if( (month==2&&days<28+Isleap(year))||
            (IsBigMon(month)&&(days<31))||
            ((month==4||month==6||month==9||month==11)&&(days<30)))
        {
            endwhile=0;/*end of while*/
        }
    }
    /*let (the first day of month)=1*/
    day+=days;

    printf("\n%d/%d/%d (", year, month, day);
    week(StartingDay);
    printf(") %d:%d:%d", hours, mins, secs);
}

int main(){
    char determinant=0; /*determinant=d or + or -*/
    int year,month,day,hour,min,sec;

    /* input  determinant,and scan in*/
    printf("Enter [d] for difference or [+,-] for offset:");
    scanf("%c", &determinant);

    /* input  time1 as"year1/month/day hour:min:sec",and scan in*/
    printf("\nEnter year1/month/day hour:min:sec ");
    scanf("%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec);


    long long days1,secs1,totalsecs1;
        /* calculates the number of days since January 1, 1753*/
    days1=CalDays(year,month,day);
        /* calculates the number of seconds since midnight*/
    secs1=CalSecs(hour,min,sec);
        /* total secs1 = transform (days1) to seconds + secs1*/
    totalsecs1=days1*24*3600+secs1;


    if(determinant=='d'){
        /* input  time2 as"year2/month/day hour:min:sec",and scan in*/
        printf("\nEnter year2/month/day hour:min:sec ");
        scanf("%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec);

        long long days2,secs2, totalsecs2,deltatosecs;

            /* calculates the number of days since January 1, 1753*/
        days2=CalDays(year,month,day);
            /* calculates the number of seconds since midnight*/
        secs2=CalSecs(hour,min,sec);
            /* total secs2 = transform (days2) to seconds + secs2*/
        totalsecs2=days2*24*3600+secs2;
            /* delta total secs = totalsecs1-totalsecs2*/
        deltatosecs=totalsecs1-totalsecs2;
            /* transform delta total secs to "days hour:min:sec", and print out*/
        PrintDelta(deltatosecs);

        return 0;/* end of main*/
    }
    else{
        int days;

        /* input  delta time as"days hour:min:sec",and scan in*/
        printf("\nEnter number of days hour:min:sec ");
        scanf("%d %d:%d:%d", &days, &hour, &min, &sec);

        long long totalsecs2,totalsecs;

            /* total secs2 = transform (days) to seconds + secs2*/
        totalsecs2=days*24*3600+CalSecs(hour,min,sec);
            /*totalsecs=totalsecs1 (determinant) totalsecs2*/
        totalsecs=(determinant=='+')?totalsecs1+totalsecs2:totalsecs1-totalsecs2;
            /* transform total secs to "year/month/day hour:min:sec", and print out*/
        PrintFinal(totalsecs);

        return 0;/* end of main*/
    }
}
