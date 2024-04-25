#include <iostream>
#include <sys/resource.h>
#include <sys/time.h> 

float current_timestamp(timeval *start, timeval *end) {
    return (((end->tv_sec * 1000000) + end->tv_usec) - ((start->tv_sec * 1000000) + start->tv_usec));
}

int main(int argc, char* argv[] ) {

    struct timeval start;
	struct timeval end;
	
    float laufzeit;
    float user_zeit;
    float system_zeit;

    std::string kommando;
    struct rusage res_usage;

    std::cout << "Kommando: ";

    if (argc == 1){
        std::cin >> kommando;
    }else{
        //concat the strings into kommando if more than one argument
        for (int i = 1; i < argc; i++) {
            kommando += argv[i];
            kommando += " ";
        }
        std::cout << kommando << std::endl;
    }
    

    gettimeofday(&start, NULL);
    system(kommando.c_str());
    getrusage(RUSAGE_CHILDREN, &res_usage);
    gettimeofday(&end, NULL);

    laufzeit = current_timestamp(&start, &end);
    user_zeit = (res_usage.ru_utime.tv_sec * 1000000) + res_usage.ru_utime.tv_usec;
    system_zeit = (res_usage.ru_stime.tv_sec * 1000000) + res_usage.ru_stime.tv_usec;

    printf("Laufzeit: %.4f sek\n", laufzeit * 1e-6);
    printf("User-Zeit: %.4f sek\n", user_zeit * 1e-6);
    printf("System-Zeit: %.4f sek\n", system_zeit * 1e-6);
    return 0;
}