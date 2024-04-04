#include "types.h"
#include "stat.h"
#include "user.h"

char buf[1024];

void uniq(int fd, int cFlag, int dFlag, int iFlag) {
    char lineOne[1024];
    char lineTwo[1024];

    int l1CharIndex = 0;
    int l2CharIndex = 0;
    int linesRead = 0;

    int i, n;
    int comparisonRes = 1;

    //No options
    if (cFlag == 0 && dFlag == 0 && iFlag == 0){
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            for (i = 0; i < n; i++) {
                //char is a newline
                if (buf[i] == '\n'){
                    //check to see how many lines the user has entered
                    linesRead++;
                    if(linesRead > 1){
                        //compare line one and two lengths
                        if (l1CharIndex != l2CharIndex){
                            comparisonRes = 0;
                            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
                        }
                            //else compare the lines character by character
                        else {
                            for (int l = 0; l < l2CharIndex; l++){
                                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                                if (lineOne[l] != lineTwo[l]){
                                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                                    comparisonRes = 0;
                                }
                            }
                        }

                        //if lines are the the same
                        if (comparisonRes == 1){
                            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
                            //write line two to line one
                            for (int m = 0; m < l2CharIndex; m++){
                                lineOne[m] = lineTwo[m];
                            }
                        }
                            //If they are different
                        else {
                            // printf(1, "lines were different, comparison result was %d\n", comparisonRes);
                            //output line one
                            for(int m = 0; m < l1CharIndex; m++){
                                printf(1, "%c", lineOne[m]);
                            }
                            printf(1, "\n");
                            //write line two to line one
                            for (int m = 0; m < 1024; m++){
                                lineOne[m] = lineTwo[m];
                            }
                            l1CharIndex = l2CharIndex;

                        }
                        l2CharIndex = 0;
                        comparisonRes = 1;
                    }
                        //if user has entered less than two lines, do not compare. just push the line 2 to 1
                    else {
                        for (int m = 0; m < l2CharIndex; m++){
                            lineOne[m] = lineTwo[m];
                        }
                        l1CharIndex = l2CharIndex;
                        l2CharIndex = 0;
                    }

                }

                    //char is not a newline
                else {
                    //write char to line two at char index
                    lineTwo[l2CharIndex] = buf[i];
                    l2CharIndex++;
                }
            }
        }
        //outout remaining line in line 1
        for(int m = 0; m < l1CharIndex; m++){
            printf(1, "%c", lineOne[m]);
        }
        printf(1, "\n");
        //output remaining line in line 2
        for(int m = 0; m < l2CharIndex; m++){
            printf(1, "%c", lineTwo[m]);
        }
        printf(1, "\n");

        if (n < 0) {
            printf(1, "uniq: read error\n");
            exit();
        }
    }

    //Case 1, -c, output line count
    if (cFlag == 1 && dFlag == 0 && iFlag == 0){
        int occurenceCount = 1;
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            for (i = 0; i < n; i++) {
                //char is a newline
                if (buf[i] == '\n'){
                    //check to see how many lines the user has entered
                    linesRead++;
                    if(linesRead > 1){
                        //compare line one and two lengths
                        if (l1CharIndex != l2CharIndex){
                            comparisonRes = 0;
                            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
                        }
                            //else compare the lines character by character
                        else {
                            for (int l = 0; l < l2CharIndex; l++){
                                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                                if (lineOne[l] != lineTwo[l]){
                                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                                    comparisonRes = 0;
                                }
                            }
                        }

                        //if lines are the the same
                        if (comparisonRes == 1){
                            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
                            //write line two to line one
                            //increment line occurence count
                            occurenceCount++;
                            for (int m = 0; m < l2CharIndex; m++){
                                lineOne[m] = lineTwo[m];
                            }
                        }
                            //If they are different
                        else {
                            // printf(1, "lines were different, comparison result was %d\n", comparisonRes);
                            //output line one and its occurence count
                            //reset occurence count
                            printf(1, "%d ", occurenceCount);
                            occurenceCount = 1;
                            for(int m = 0; m < l1CharIndex; m++){
                                printf(1, "%c", lineOne[m]);
                            }
                            printf(1, "\n");
                            //write line two to line one
                            for (int m = 0; m < 1024; m++){
                                lineOne[m] = lineTwo[m];
                            }
                            l1CharIndex = l2CharIndex;

                        }
                        l2CharIndex = 0;
                        comparisonRes = 1;
                    }
                        //if user has entered less than two lines, do not compare. just push the line 2 to 1
                    else {
                        for (int m = 0; m < l2CharIndex; m++){
                            lineOne[m] = lineTwo[m];
                        }
                        l1CharIndex = l2CharIndex;
                        l2CharIndex = 0;
                    }

                }

                    //char is not a newline
                else {
                    //write char to line two at char index
                    lineTwo[l2CharIndex] = buf[i];
                    l2CharIndex++;
                }
            }
        }
        //output remaining line in line 1 and its occurence count
        occurenceCount = 1;
        printf(1, "%d ", occurenceCount);
        for(int m = 0; m < l1CharIndex; m++){
            printf(1, "%c", lineOne[m]);
        }
        printf(1, "\n");
        //output remaining line in line 2 and its occurence count
        printf(1, "%d ", occurenceCount);
        for(int m = 0; m < l2CharIndex; m++){
            printf(1, "%c", lineTwo[m]);
        }
        printf(1, "\n");

        if (n < 0) {
            printf(1, "uniq: read error\n");
            exit();
        }
    }

    //Case 2, -c and -i, output line count and ignore case
    if (cFlag == 1 && dFlag == 0 && iFlag == 1){
        int occurenceCount = 1;
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            for (i = 0; i < n; i++) {
                //char is a newline
                if (buf[i] == '\n'){
                    //check to see how many lines the user has entered
                    linesRead++;
                    if(linesRead > 1){
                        //compare line one and two lengths
                        if (l1CharIndex != l2CharIndex){
                            comparisonRes = 0;
                            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
                        }
                            //else compare the lines character by character
                        else {
                            for (int l = 0; l < l2CharIndex; l++){
                                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                                //Ignore Case
                                char l1Char = lineOne[l];
                                char l2Char = lineTwo[l];
                                //If l1 char is a lower case alpha, make it uppercase
                                if (l1Char >= 97 && l1Char <=122){
                                    l1Char = (l1Char % 97) + 65;
                                }
                                //If l2 char is lower case alpha, make it uppercase
                                if (l2Char >= 97 && l2Char <=122){
                                    l2Char = (l2Char % 97) + 65;
                                }
                                if (l1Char != l2Char){
                                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                                    comparisonRes = 0;
                                }
                            }
                        }

                        //if lines are the the same
                        if (comparisonRes == 1){
                            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
                            //write line two to line one
                            //increment line occurence count
                            occurenceCount++;
                            for (int m = 0; m < l2CharIndex; m++){
                                lineOne[m] = lineTwo[m];
                            }
                        }
                            //If they are different
                        else {
                            // printf(1, "lines were different, comparison result was %d\n", comparisonRes);
                            //output line one and its occurence count
                            //reset occurence count
                            printf(1, "%d ", occurenceCount);
                            occurenceCount = 1;
                            for(int m = 0; m < l1CharIndex; m++){
                                printf(1, "%c", lineOne[m]);
                            }
                            printf(1, "\n");
                            //write line two to line one
                            for (int m = 0; m < 1024; m++){
                                lineOne[m] = lineTwo[m];
                            }
                            l1CharIndex = l2CharIndex;

                        }
                        l2CharIndex = 0;
                        comparisonRes = 1;
                    }
                        //if user has entered less than two lines, do not compare. just push the line 2 to 1
                    else {
                        for (int m = 0; m < l2CharIndex; m++){
                            lineOne[m] = lineTwo[m];
                        }
                        l1CharIndex = l2CharIndex;
                        l2CharIndex = 0;
                    }

                }

                    //char is not a newline
                else {
                    //write char to line two at char index
                    lineTwo[l2CharIndex] = buf[i];
                    l2CharIndex++;
                }
            }
        }
        //compare remaining two lines in buffer
        //compare line one and two lengths
        if (l1CharIndex != l2CharIndex){
            comparisonRes = 0;
            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
        }
        else {
            for (int l = 0; l < l2CharIndex; l++){
                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                //Ignore Case
                char l1Char = lineOne[l];
                char l2Char = lineTwo[l];
                //If l1 char is a lower case alpha, make it uppercase
                if (l1Char >= 97 && l1Char <=122){
                    l1Char = (l1Char % 97) + 65;
                }
                //If l2 char is lower case alpha, make it uppercase
                if (l2Char >= 97 && l2Char <=122){
                    l2Char = (l2Char % 97) + 65;
                }
                if (l1Char != l2Char){
                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                    comparisonRes = 0;
                }
            }

        }

        //if buffer line one and two are the same
        if (comparisonRes == 1){
            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
            //increment line occurence count
            //output line one
            occurenceCount++;

            printf(1, "%d ", occurenceCount);
            for(int m = 0; m < l1CharIndex; m++){
                printf(1, "%c", lineOne[m]);
            }
            printf(1, "\n");

        }
            //if buffer line one and two are different
        else {
            //output line one and the occurence count
            printf(1, "%d ", occurenceCount);
            for(int m = 0; m < l1CharIndex; m++){
                printf(1, "%c", lineOne[m]);
            }
            printf(1, "\n");
            //reset the occurence count to 1
            occurenceCount = 1;
            //output line two
            printf(1, "%d ", occurenceCount);
            for(int m = 0; m < l2CharIndex; m++){
                printf(1, "%c", lineTwo[m]);
            }
            printf(1, "\n");
        }
        if (n < 0) {
            printf(1, "uniq: read error\n");
            exit();
        }
    }

    //Case 3, -i, ignore case
    if (cFlag == 0 && dFlag == 0 && iFlag == 1){
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            for (i = 0; i < n; i++) {
                //char is a newline
                if (buf[i] == '\n'){
                    //check to see how many lines the user has entered
                    linesRead++;
                    if(linesRead > 1){
                        //compare line one and two lengths
                        if (l1CharIndex != l2CharIndex){
                            comparisonRes = 0;
                            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
                        }
                            //else compare the lines character by character
                        else {
                            for (int l = 0; l < l2CharIndex; l++){
                                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                                //Ignore Case
                                char l1Char = lineOne[l];
                                char l2Char = lineTwo[l];
                                //If l1 char is a lower case alpha, make it uppercase
                                if (l1Char >= 97 && l1Char <=122){
                                    l1Char = (l1Char % 97) + 65;
                                }
                                //If l2 char is lower case alpha, make it uppercase
                                if (l2Char >= 97 && l2Char <=122){
                                    l2Char = (l2Char % 97) + 65;
                                }
                                if (l1Char != l2Char){
                                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                                    comparisonRes = 0;
                                }
                            }
                        }

                        //if lines are the the same
                        if (comparisonRes == 1){
                            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
                            //write line two to line one
                            //increment line occurence count
                            for (int m = 0; m < l2CharIndex; m++){
                                lineOne[m] = lineTwo[m];
                            }
                        }
                            //If they are different
                        else {
                            // printf(1, "lines were different, comparison result was %d\n", comparisonRes);
                            //output line one and its occurence count
                            //reset occurence count
                            for(int m = 0; m < l1CharIndex; m++){
                                printf(1, "%c", lineOne[m]);
                            }
                            printf(1, "\n");
                            //write line two to line one
                            for (int m = 0; m < 1024; m++){
                                lineOne[m] = lineTwo[m];
                            }
                            l1CharIndex = l2CharIndex;

                        }
                        l2CharIndex = 0;
                        comparisonRes = 1;
                    }
                        //if user has entered less than two lines, do not compare. just push the line 2 to 1
                    else {
                        for (int m = 0; m < l2CharIndex; m++){
                            lineOne[m] = lineTwo[m];
                        }
                        l1CharIndex = l2CharIndex;
                        l2CharIndex = 0;
                    }

                }

                    //char is not a newline
                else {
                    //write char to line two at char index
                    lineTwo[l2CharIndex] = buf[i];
                    l2CharIndex++;
                }
            }
        }
        //compare remaining two lines in buffer
        //compare line one and two lengths
        if (l1CharIndex != l2CharIndex){
            comparisonRes = 0;
            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
        }
        else {
            for (int l = 0; l < l2CharIndex; l++){
                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                //Ignore Case
                char l1Char = lineOne[l];
                char l2Char = lineTwo[l];
                //If l1 char is a lower case alpha, make it uppercase
                if (l1Char >= 97 && l1Char <=122){
                    l1Char = (l1Char % 97) + 65;
                }
                //If l2 char is lower case alpha, make it uppercase
                if (l2Char >= 97 && l2Char <=122){
                    l2Char = (l2Char % 97) + 65;
                }
                if (l1Char != l2Char){
                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                    comparisonRes = 0;
                }
            }

        }

        //if buffer line one and two are the same
        if (comparisonRes == 1){
            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
            //output line one

            for(int m = 0; m < l1CharIndex; m++){
                printf(1, "%c", lineOne[m]);
            }
            printf(1, "\n");

        }
            //if buffer line one and two are different
        else {
            //output line one and the occurence count
            for(int m = 0; m < l1CharIndex; m++){
                printf(1, "%c", lineOne[m]);
            }
            printf(1, "\n");
            //reset the occurence count to 1
            //output line two
            for(int m = 0; m < l2CharIndex; m++){
                printf(1, "%c", lineTwo[m]);
            }
            printf(1, "\n");
        }
        if (n < 0) {
            printf(1, "uniq: read error\n");
            exit();
        }
    }

    //Case 4, -i and -d, ignore case and only print duplicate
    if (cFlag == 0 && dFlag == 1 && iFlag == 1){
        int occurenceCount = 1;
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            for (i = 0; i < n; i++) {
                //char is a newline
                if (buf[i] == '\n'){
                    //check to see how many lines the user has entered
                    linesRead++;
                    if(linesRead > 1){
                        //compare line one and two lengths
                        if (l1CharIndex != l2CharIndex){
                            comparisonRes = 0;
                            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
                        }
                            //else compare the lines character by character
                        else {
                            for (int l = 0; l < l2CharIndex; l++){
                                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                                //Ignore Case
                                char l1Char = lineOne[l];
                                char l2Char = lineTwo[l];
                                //If l1 char is a lower case alpha, make it uppercase
                                if (l1Char >= 97 && l1Char <=122){
                                    l1Char = (l1Char % 97) + 65;
                                }
                                //If l2 char is lower case alpha, make it uppercase
                                if (l2Char >= 97 && l2Char <=122){
                                    l2Char = (l2Char % 97) + 65;
                                }
                                if (l1Char != l2Char){
                                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                                    comparisonRes = 0;
                                }
                            }
                        }

                        //if lines are the the same
                        if (comparisonRes == 1){
                            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
                            //write line two to line one
                            //increment line occurence count
                            occurenceCount++;
                            for (int m = 0; m < l2CharIndex; m++){
                                lineOne[m] = lineTwo[m];
                            }
                        }
                            //If they are different
                        else {
                            // printf(1, "lines were different, comparison result was %d\n", comparisonRes);
                            //output line one if its occurence count >= 2
                            //reset occurence count
                            if (occurenceCount >= 2){
                                for(int m = 0; m < l1CharIndex; m++){
                                    printf(1, "%c", lineOne[m]);
                                }
                                printf(1, "\n");
                            }

                            occurenceCount = 1;

                            //write line two to line one
                            for (int m = 0; m < 1024; m++){
                                lineOne[m] = lineTwo[m];
                            }
                            l1CharIndex = l2CharIndex;

                        }
                        l2CharIndex = 0;
                        comparisonRes = 1;
                    }
                        //if user has entered less than two lines, do not compare. just push the line 2 to 1
                    else {
                        for (int m = 0; m < l2CharIndex; m++){
                            lineOne[m] = lineTwo[m];
                        }
                        l1CharIndex = l2CharIndex;
                        l2CharIndex = 0;
                    }

                }

                    //char is not a newline
                else {
                    //write char to line two at char index
                    lineTwo[l2CharIndex] = buf[i];
                    l2CharIndex++;
                }
            }
        }
        //compare remaining two lines in buffer
        //compare line one and two lengths
        if (l1CharIndex != l2CharIndex){
            comparisonRes = 0;
            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
        }
        else {
            for (int l = 0; l < l2CharIndex; l++){
                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                //Ignore Case
                char l1Char = lineOne[l];
                char l2Char = lineTwo[l];
                //If l1 char is a lower case alpha, make it uppercase
                if (l1Char >= 97 && l1Char <=122){
                    l1Char = (l1Char % 97) + 65;
                }
                //If l2 char is lower case alpha, make it uppercase
                if (l2Char >= 97 && l2Char <=122){
                    l2Char = (l2Char % 97) + 65;
                }
                if (l1Char != l2Char){
                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                    comparisonRes = 0;
                }
            }

        }

        //if buffer line one and two are the same
        if (comparisonRes == 1){
            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
            //increment line occurence count
            //output line one
            occurenceCount++;

            for(int m = 0; m < l1CharIndex; m++){
                printf(1, "%c", lineOne[m]);
            }
            printf(1, "\n");

        }
        //if buffer line one and two are different neither is being outputted
        if (n < 0) {
            printf(1, "uniq: read error\n");
            exit();
        }
    }

    //Case 5, -d, only print duplicate
    if (cFlag == 0 && dFlag == 1 && iFlag == 0){
        int occurenceCount = 1;
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            for (i = 0; i < n; i++) {
                //char is a newline
                if (buf[i] == '\n'){
                    //check to see how many lines the user has entered
                    linesRead++;
                    if(linesRead > 1){
                        //compare line one and two lengths
                        if (l1CharIndex != l2CharIndex){
                            comparisonRes = 0;
                            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
                        }
                            //else compare the lines character by character
                        else {
                            for (int l = 0; l < l2CharIndex; l++){
                                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                                if (lineOne[l] != lineTwo[l]){
                                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                                    comparisonRes = 0;
                                }
                            }
                        }

                        //if lines are the the same
                        if (comparisonRes == 1){
                            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
                            //write line two to line one
                            //increment line occurence count
                            occurenceCount++;
                            for (int m = 0; m < l2CharIndex; m++){
                                lineOne[m] = lineTwo[m];
                            }
                        }
                            //If they are different
                        else {
                            // printf(1, "lines were different, comparison result was %d\n", comparisonRes);
                            //output line one if its occurence count >= 2
                            //reset occurence count
                            if (occurenceCount >= 2){
                                for(int m = 0; m < l1CharIndex; m++){
                                    printf(1, "%c", lineOne[m]);
                                }
                                printf(1, "\n");
                            }

                            occurenceCount = 1;

                            //write line two to line one
                            for (int m = 0; m < 1024; m++){
                                lineOne[m] = lineTwo[m];
                            }
                            l1CharIndex = l2CharIndex;

                        }
                        l2CharIndex = 0;
                        comparisonRes = 1;
                    }
                        //if user has entered less than two lines, do not compare. just push the line 2 to 1
                    else {
                        for (int m = 0; m < l2CharIndex; m++){
                            lineOne[m] = lineTwo[m];
                        }
                        l1CharIndex = l2CharIndex;
                        l2CharIndex = 0;
                    }

                }

                    //char is not a newline
                else {
                    //write char to line two at char index
                    lineTwo[l2CharIndex] = buf[i];
                    l2CharIndex++;
                }
            }
        }
        //compare remaining two lines in buffer
        //compare line one and two lengths
        if (l1CharIndex != l2CharIndex){
            comparisonRes = 0;
            // printf(1, "line 1 had a length of %d and line 2 had a char length of %d\n",l1CharIndex, l2CharIndex);
        }
        else {
            //compate character by character, case sensitive
            for (int l = 0; l < l2CharIndex; l++){
                // printf(1, "Comparing %c to %c\n", lineOne[l], lineTwo[l]);
                if (lineOne[l] != lineTwo[l]){
                    // printf(1, "The mismatch character is line1:%c and line2:%c\n", lineOne[l], lineTwo[l]);
                    comparisonRes = 0;
                }
            }

        }

        //if buffer line one and two are the same
        if (comparisonRes == 1){
            // printf(1, "lines were the same, comparison result was %d\n", comparisonRes);
            //increment line occurence count
            //output line one
            occurenceCount++;

            for(int m = 0; m < l1CharIndex; m++){
                printf(1, "%c", lineOne[m]);
            }
            printf(1, "\n");

        }
        //if buffer line one and two are different neither is being outputted
        if (n < 0) {
            printf(1, "uniq: read error\n");
            exit();
        }
    }
}

int main(int argc, char *argv[]) {
    int fd, i;

    char c;
    const char * prog = argv[0];
    // printf(1, "The number of arguements entered is %d\n", argc);

    // for (int i = 0; i < argc; i++){
    //     printf(1,"Arguement %d is %s\n", i, argv[i]);
    // }
    // printf(1,"Is this the file?: %s\n", argv[argc - 1]);

    int cFlag, dFlag, iFlag;
    cFlag = dFlag = iFlag = 0;

    //no arguements or a pipe with no arguements
    if (argc <= 1) {
        uniq(0,cFlag, dFlag, iFlag);
        exit();
    }

    //if more than one arguement was passed and the last arguement was a file
    if (argc > 1 && ((fd = open(argv[argc - 1], 0)) >= 0)){
        for (i = 1; i < argc -1; i++){
            //if the arguement starts with a '-'
            if (argv[i][0] == '-'){
                c = argv[i][1];
                switch(c) {
                    case 'c':
                        cFlag = 1; break;
                    case 'd':
                        dFlag = 1; break;
                    case 'i':
                        iFlag = 1; break;
                    default:
                        printf(1, "Option %c is unknown.\n", c);
                        printf(1, "Usage %s is  <-icd -h>.\n", prog);
                        exit();
                }
            }
        }
        //call uniq on the file with options set
        uniq(fd,cFlag, dFlag, iFlag);
        close(fd);
        exit();


    }
        //If more than one argument was passed and it was not a file (so a pipe with options)
    else {
        for (i = 1; i < argc; i++){
            //if the arguement starts with a '-'
            if (argv[i][0] == '-'){
                c = argv[i][1];
                switch(c) {
                    case 'c':
                        cFlag = 1; break;
                    case 'd':
                        dFlag = 1; break;
                    case 'i':
                        iFlag = 1; break;
                    default:
                        printf(1, "Option %c is unknown.\n", c);
                        printf(1, "Usage %s is  <-icd -h>.\n", prog);
                        exit();
                }
            }
        }

        uniq(0,cFlag, dFlag, iFlag);
        exit();
    }
}