#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

int main(int argc, char* argv[])
{
    /* here are our global variables. */
    bool flag = false;
    string check;
    string concat = "";
    char* parse;
    int counter = 0;
    int comma = 0;
    const int max = 80;
    char date[max];
    time_t timeYear = time(0);
    strftime(date, max, "%m/%d/%Y", localtime(&timeYear));
    /* regular expression that only accepts strings as specified in the homework. */
    regex b("([^,]+)(\\,(\\s*[^,\\s]+\\s*)*)*");

    /* here is our cmds[] array, which will be referenced throughout the program. */
    const char* cmds[] = {
         "cd",
         "exec",
         "exit",
         "gcc",
         "ls",
         "man",
         "more",
         "mv",
         "rm",
         "pwd",
         "sh",
         "touch",
         "which",
         "$path"
    };

    /* parse all parameters into one string, so we can tokenize the string by ','. */
    for (int i = 1; i < argc; i++) {
        concat += argv[i];

        counter++;
        if (counter >= 1) {
            concat += " ";
        }
    }
    
    /* this if statement checks to see if user input passes our regular expression
     initialized above.  if the string is legal (no wrong inputs, no commas omitted,
     no multiple commas (back-to-back), no leading commas, no illegal commands), then
     we will execute the tokenization of the string. */
    if (regex_match(concat, b)) {
        /* count how many parameters are being passed to our cli (plus one, because this
         keeps track of how many commas exist in our string. */
        comma = count(concat.begin(), concat.end(), ',');

        /* we will now tokenize the string by ',', meaning we will break up the one string
         into several different strings, after there is a comma present. */
        parse = strtok((char*)concat.c_str(), ",");

        /* logic to get command up until a space, so we can check if it is predefined. */
        string s = parse;
        auto first = s.substr(0, s.find(' '));

        /* here is the logic for figuring out if the first parameter passed is in our cmds[] array.
         we are storing different values to the global variable 'check', depending on whether
         it is in the cmds[] array.  if the first parameter is in the array, there is no need to
         check anymore, and we can therefore 'break'. */
        for (int i = 0; i < 14; i++) {
            if ((string) first == cmds[i]) {
                check = "1st cmd '" + (string) first + "' is one of predefined.";
                break;
            } else {
                check = "1st cmd '" + (string) first + "' is not one of predefined.";
            }
        }

        /* here is the logic that is graphically displayed to the user if the parameters are legal. */
        cout << "mhg cli " << date << endl;
        cout << "Legal commands: cd exec exit gcc ls man more mv rm pwd sh touch which $path" << endl;
        cout << comma + 1 << " strings passed to argv[]" << endl;

        while (parse) {
            cout << "next string is '" << parse << "'" << endl;
            cout << "new string is '" << parse << " '" << endl;

            /* we only want the system to tell us if the first parameter is defined once, thus
             we use a flag. */
            if (!flag) {
                cout << check << endl;
                flag = true;
            }
            system(parse);

            parse = strtok(NULL, ",");
        }
        system("pwd");
    } else {
        cout << "ILLEGAL INPUT" << endl;
    }
    
    return 0;
}
