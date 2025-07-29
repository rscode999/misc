#July 23, 2023
#First use of timing functions and f-strings.
#Specifically designed to destroy your sanity.

import sys
from time import perf_counter

#Tests the timer and provides an example of the perf_counter()
def checkTimer() -> None:
    #take a perf_counter reading at the beginning of the program. perf_counter gives arbitrary values, so a start and end time are needed to determine total program runtime
    startTime=perf_counter();
    print(f"Program started at T={startTime}. ", end='');

    #ask user to stop the timer at any time (input function is to pause execution at any time)
    input("Press Enter to stop the timer.");

    #take perf_counter reading after pressing Enter
    stopTime=perf_counter();
    print(f"Program ended at T={stopTime}");

    #subtract start time from end time to get total program runtime and print the result
    print("");
    print(f"Time to press Enter is {stopTime-startTime} seconds.");



#########################################################################################################################################################

#quite cursed but keeps the clutter out of the main function
def printQuestion(qn:int, maxLength:int) -> None:
    print(f"{qn}: ", end='')

    if qn<=0 or qn>maxLength:
        print("ERROR: CHECK ARRAY INDEXING!");
    
    elif qn==1:
        print("Clicking on the Wicked logo at the top-center of the screen takes you to which subpage?");
        print(" a. The website's home page")
        print(" b. FAQ")
        print(" c. Plan Your Visit")
        print(" d. Shop")
        print(" e. Tickets")

    elif qn==2:
        print("How many images are on the main page?")
        print(" a. 0")
        print(" b. 1")
        print(" c. 2")
        print(" d. 3")
        print(" e. 4 or more")

    elif qn==3:
        print("The home page allows you to see seat availability for the next ______.");
        print(" a. 1 day")
        print(" b. 3 days")
        print(" c. 1 week")
        print(" d. 1 month")
        print(" e. 3 months")

    elif qn==4:
        print("""When hidden, the pop-up text input on the (bottom) right of the webpage is called "_______".""");
        print(" a. Q&A")
        print(" b. Buy Tickets")
        print(" c. AI Agent Chat")
        print(" d. Ticket Concierge")
        print(" e. General Inquiries FAQ")

    elif qn==5:
        print("On Broadway, Wicked is performed nearest to ____ Street.");
        print(" a. 31st")
        print(" b. 35th")
        print(" c. 44th")
        print(" d. 51st")
        print(" e. 54th")

    elif qn==6:
        print("Wicked on Broadway's official ticketing service is ______.");
        print(" a. TKM")
        print(" b. Ticketmaster")
        print(" c. TodayTix")
        print(" d. Nederlander Group")
        print(" e. Broadway Direct")

    elif qn==7:
        print("How many major themes are listed in the Linguification Library?");
        print(" a. 12")
        print(" b. 10")
        print(" c. 8")
        print(" d. 6")
        print(" e. 4")

    elif qn==8:
        print("The Broadway performance offers its military rate on which days?");
        print(" a. Monday-Thursday")
        print(" b. Tuesday-Thursday")
        print(" c. Wednesday-Friday")
        print(" d. Weekdays")
        print(" e. Every day")

    elif qn==9:
        print("Which language does the website NOT support?");
        print(" a. Portugese")
        print(" b. Russian")
        print(" c. French")
        print(" d. Korean")
        print(" e. Japanese")
    
    elif qn==10:
        print("Audien translator devices are available for $____.");
        print(" a. 0")
        print(" b. 5")
        print(" c. 7.50")
        print(" d. 10")
        print(" e. 15")

    elif qn==11:
        print("Which of the following social media platforms do NOT have links on the website?");
        print(" a. Facebook")
        print(" b. TikTok")
        print(" c. Instagram")
        print(" d. Snapchat")
        print(" e. YouTube")


    elif qn==12:
        print("Which service or company is responsible for the website's AI chatbot?");
        print(" a. Google Gemini")
        print(" b. AWS")
        print(" c. GPT-4o")
        print(" d. Background Intelligent Transfer Service")
        print(" e. Satisfi Labs")

    elif qn==13:
        print("In NBCUniversal's Privacy Policy, which of the following groups may NOT receive your browsing data directly from NBCUniversal?");
        print(" a. Search engines")
        print(" b. Partner websites")
        print(" c. Advertising companies")
        print(" d. Police departments")
        print(" e. Social media platforms")


    elif qn==14:
        print("Out of the options provided, which child is the youngest to be allowed to see Wicked on Broadway?");
        print(" a. Annie (8 years old)")
        print(" b. Bert (5 years old)")
        print(" c. Clara (3 years old)")
        print(" d. Douglas (2 years old)")
        print(" e. Edward (Three months old)")

    elif qn==15:
        print("You can purchase a Wicked London gift card for a minimum amount of ____ British pounds.");
        print(" a. 5")
        print(" b. 10")
        print(" c. 15")
        print(" d. 20")
        print(" e. 25")


#also cursed, but keeps the main function uncluttered
def setDifficultyInfo(qn:int, currentDifficulty:int) -> int:

    #change difficulty if there's a new level coming
    newDifficulty=currentDifficulty+1;

    if qn==1:
        print("Easy: Welcome to your warm-up. ")
    elif qn==4:
        print("Medium: Let's crank up the heat a little. ")
    elif qn==7:
        print("Hard: Ready for a real challenge? ")
    elif qn==11:
        print("SUKA BLYAT: Prepare to die, kid! ")
    #reset difficulty if there's no new level
    else:
        newDifficulty=newDifficulty-1;

    return newDifficulty;




def main() -> int:
    startTime=0;
    stopTime=0;
    ANSWER_TIME = 60 #in seconds

    #        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15
    answers=[2, 1, 4, 3, 4, 4, 5, 1, 2, 2, 1, 4, 5, 1, 2, 2]

    inputtedAnswer=chr(0);

    difficulty=1; #ranges from 1 (easy) to 4 (Suka Blyat)

    score=0;

    #print the rules
    print("wickedthemusical.com impossible test")
    input("Press Enter to view the rules")

    print("")
    print("RULES:")
    print("There are a total of 15 questions. Each question has five possible answers. Type one of the choices (a, b, c, d, e), then press Enter to submit your answer.")
    print("Each question has exactly one correct answer.")
    print("")
    print(f"For each question, you have {ANSWER_TIME} seconds to answer. Taking longer than {ANSWER_TIME} seconds will forfeit your points.")
    print("You will be prompted to press Enter before each question. Time starts when you press Enter.")
    print("You may use the website to help you.")
    print("")
    print("There are 3 easy questions (1 point each), 3 medium questions (2 points each), 4 hard questions (3 points each), and 5 Suka Blyat questions (4 points each) for a maximum score of 41.")
    print("")
    print("No knowledge of Wicked the Musical is needed to answer the questions. All answers can be found through https://wickedthemusical.com/")
    print("")
    print("THE AUTHOR IS NOT RESPONSIBLE FOR ANY LOSS OF SANITY!")
    input("Press Enter for an example question.")

    #do example question
    for p in range(500):
        print("")

    startTime=perf_counter()
    print("Example Question: Earth is the _____ planet from the Sun.");
    print(" a. 1st")
    print(" b. 2nd")
    print(" c. 3rd")
    print(" d. 4th")
    print(" e. 5th")
    inputtedAnswer=input("Type answer here, then press Enter to submit: ");
    if len(inputtedAnswer) <= 0:
        inputtedAnswer="z";
    else:
        inputtedAnswer=inputtedAnswer[0].lower();

    #then convert to a number (1 is 'a', 2 is 'b'...) corresponding to an answer choice in correctAnswers
    inputtedAnswer=ord(inputtedAnswer) - 96;

    #stop input timer
    stopTime=perf_counter();

    #compare timer and answer results, print the response
    if stopTime-startTime > ANSWER_TIME:
        print(f"You were {round(stopTime-startTime - ANSWER_TIME, 2)} seconds too slow. ", end='');
        if not inputtedAnswer==3:
            print(f"The correct answer is C");
        else:
            print("");

    elif not inputtedAnswer==3:
        print(f"Incorrect. The correct answer is C.")
    else:
        print("Correct! +0")


    print("")
    print("")
    input("Press Enter to start the test.")

    for s in range(500):
        print("");



    #do the test
    for i in range(1, len(answers)):

        print("");
        input(f"Press Enter when you're ready for the next question. The {ANSWER_TIME}-second timer starts after you press Enter.");
        #print a billion newlines so the test taker can't see the previous questions
        for p in range(500):
            print("");

        #print difficulty info
        difficulty=setDifficultyInfo(i, difficulty);
        print("");

        #display current question
        printQuestion(i, len(answers));

        #start timer
        startTime=perf_counter();

        #ask user for letter input
        inputtedAnswer = ''
        try:
            inputtedAnswer=input("Type answer here, then press Enter to submit: ");
        except (KeyboardInterrupt, EOFError) as e:
            print("\ncoward")
            sys.exit(-1)

        #check if inputtedAnswer is filled. if not, set to a bogus answer. if so, convert to lowercase letter
        if len(inputtedAnswer) <= 0:
            inputtedAnswer="z";
        else:
            inputtedAnswer=inputtedAnswer[0].lower();

        #then convert to a number (1 is 'a', 2 is 'b'...) corresponding to an answer choice in correctAnswers
        inputtedAnswer=ord(inputtedAnswer) - 96;

        #stop input timer
        stopTime=perf_counter();

        #compare timer and answer results, print the response
        if stopTime-startTime > ANSWER_TIME:
            print(f"You were {round(stopTime-startTime - ANSWER_TIME, 2)} seconds too slow. ", end='');
            if not inputtedAnswer==answers[i]:
                print(f"The correct answer is {chr(answers[i]+64)}");
            else:
                print("");

        elif not inputtedAnswer==answers[i]:
            print(f"Incorrect. The correct answer is {chr(answers[i]+64)}.")
        else:
            print(f"Correct! +{difficulty-1}")
            score=score + difficulty-1;

        print(f"Your score: {score}")


    print("");
    print(f"YOUR FINAL SCORE: {score}/41");

    if score<=3:
        print("Bro, you suck.")
    elif 3<score<=9:
        print("Half decent. Not bad at all.")
    elif 9<score<=21:
        print("You did great. Rejoicify!")
    elif 21<score<41:
        print("WOW! You defied gravity!")
    else:
        print("You cheated! Admit it!")

    print("");

    return 0;


if __name__=="__main__":
    main()