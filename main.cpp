#include <cstdlib>
#include <iostream>
#include "Controller.h"

using namespace std;

#define MAXIP 15
#define TOTALIPDIGITS 12
#define TOTALIPPERIODS 3
#define IPDIGITS 3

char* parseIP(int argc, char* argv);

int
main(int argc, char** argv)
{
//    char* ip = NULL;
//    ip = parseIP(argc, argv[1]); //devuelve NULL si hubo error
//    if (ip != NULL)
//    {
//        bool success;
//        srand(time(NULL));
//        Controller controller(ip);
//        //        success = controller.connect();
//        //
//        //        if (success)
//        //            cout << "connection succeed" << endl;
//        //        else
//        //            cout << "connection failed" << endl;
//    }
//    else
//        cout << "no se pasó ip" << endl;
    
    
    return 0;
}

char*
parseIP(int argc, char* argv)
{
    unsigned periodCounter = 0, digitCounter = 0, totalDigits = 0, totalPeriods = 0, i = 0, status = true;
    if (argc == 2)
    {
        while (argv[i] != '\0')
        {
            if (isdigit(argv[i]))
            {
                if (digitCounter < IPDIGITS && totalDigits < TOTALIPDIGITS)
                {
                    digitCounter++;
                    totalDigits++;
                    periodCounter = 0;
                }
                else
                    status = false;
            }
            else if (argv[0] != '.')
            {
                if (argv[i] == '.')
                {
                    if (periodCounter == 0 && totalPeriods < TOTALIPPERIODS)
                    {
                        periodCounter++;
                        totalPeriods++;
                        digitCounter = 0;
                    }
                }
                else
                    status = false;
            }
            else
                status = false;
            i++;
        }
    }
    else
        status = false;

    return status == false ? NULL : argv;
}

