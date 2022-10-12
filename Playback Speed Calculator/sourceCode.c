//including header files
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    //Declaring necessary variables
    int hours, minutes, hours_to_minutes, videoLength, minutes_to_hours, actualLength, remaining_minutes ;
    float playbackSpeed;

    //Taking hours as input
    printf("\nEnter the hours of the video: ");
    scanf("%d", &hours);

    //Taking minutes as input
    printf("and the minutes: ");
    scanf("%d", &minutes);

    //Taking Playback speed as input
    printf("\nEnter Playback Speed in which you want to watch the video: ");
    scanf("%f", &playbackSpeed);
    

    //Calculation of playback speed 👇

    //Converting hours to minutes
    hours_to_minutes = hours*60;          

    //Calculating original length of video
    videoLength = hours_to_minutes + minutes;   

    //Calculating actual length of video after applying playback speed
    actualLength = videoLength/playbackSpeed;   

    //Converting minutes to hours 
    minutes_to_hours = actualLength/60;
    remaining_minutes = actualLength%60;

    //Giving the resultant time as output
    printf("\nIt will take %d hours and %d minutes at %.2f playback speed to watch the video.\n\n", minutes_to_hours, remaining_minutes, playbackSpeed);

    return 0;
}