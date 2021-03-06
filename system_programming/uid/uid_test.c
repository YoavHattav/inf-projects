#include <stdio.h> /* printf */
#include <sys/types.h> /* pid_t */
#include <time.h> /* time_t */
#include <unistd.h>

#include "uid.h" /* API functions */

#define MAX_UID 10

static ilrd_uid_t g_arr[MAX_UID];

static void PrintUID()
{
    int  i = 0;
    
    for (; i < MAX_UID; ++i)
    {
        printf("UID: %d\nCounter: %lu\nTime Stamp: %ld\n\n", g_arr[i].process_id,
                                                             g_arr[i].counter,
                                                             g_arr[i].time_stamp);
    } 
}

static void TestUID()
{
    int  i = 0;
   
    g_arr[i] = UIDCreate();
    
   
    for (i = 1; i < MAX_UID; ++i)
    {
        g_arr[i] = UIDCreate();
    } 
    
    g_arr[1].counter = 0;
    g_arr[1].time_stamp = g_arr[0].time_stamp;
                                                                                                                                      
}

static void TestIsBad()
{
    int flag = 0, i = 0;
    for (; i < MAX_UID && !flag; ++i)
    {
        flag = UIDIsBad(g_arr[i]);
    }
    
    if (1 == flag)
    {
        printf("Bad UID!\n");
    } 
}

static void TestIsSame()
{
    int i = 0, j = 0, flag = 0;
    
    for (; i < MAX_UID && !flag; ++i)
    {
        for (j = i + 1; j < MAX_UID && !flag; ++j)
        {
            flag = UIDIsSame(g_arr[i], g_arr[j]);
        }
    }
    
    if (1 == flag)
    {
        printf("Same UID:\n");
        printf("UID %d: %d\nCounter: %lu\nTime Stamp: %ld\n\n", i, g_arr[i].process_id,
                                                                   g_arr[i].counter,
                                                                   g_arr[i].time_stamp);
        printf("UID %d: %d\nCounter: %lu\nTime Stamp: %ld\n\n", j, g_arr[i].process_id,
                                                                   g_arr[i].counter,
                                                                   g_arr[i].time_stamp);
    } 
}

int main()
{
    TestUID();
    
    PrintUID();
    
    TestIsBad();
    
    TestIsSame();
    
    return 0;
}
