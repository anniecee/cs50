import sys
import csv

# Error message if user doesn't input correct number of command lines
if len(sys.argv) != 3:
    print("Error! Usage: python dna.py db.csv dna.txt.")
    exit(1)

# Open and read input files if the command lines are correct
elif len(sys.argv) == 3:
    with open(sys.argv[1], "r") as database_input:
        database_file = list(csv.reader(database_input))
        database_file[0].remove("name")
        headers = database_file[0] #headers are the STRs to check

    # Open DNA file
    with open(sys.argv[2], "r") as dna_input:
        dna_file = dna_input.read()
        
    # store a value list as below:
    # this valuelist will store data as: [maxcounter of 1st STR, maxcounter of 2nd STR,...]
    valuelist = []

    #Count STRs in DNA file
    #Iterate over each STRs listed in the database:
    for i in range(len(headers)):

        #Store STR sequence as substring to check later
        str_sequence = headers[i]#[0:len(headers[i])]
        
        #Declare variable to use
        counter = 0
        maxcounter = 0
        position = 0
        prev_position = 0
        
        #Iterate over each letter in DNA file
        while position < len(dna_file):

            # This gives the position at which the STR sequence is found
            position = dna_file.find(str_sequence, position)

            #If STR sequence is NOT found ("find" returns value -1)
            if position == -1:
                counter = 0 #reset counter
                break #stop loop

            #If STR sequence is found, then position is not -1

            #Case 1:
            #We find STR sequence for the first time (pre_position is still == 0)
            elif position != -1 and prev_position == 0:
                counter += 1
                maxcounter = counter
                prev_position = position

            #Case 2:
            #We find the next STR sequence, separated from previous STR sequence
            elif (position != -1) and (position - len(str_sequence) != prev_position):
                counter = 1
                prev_position = position
             
            #Case 3: Sequential occurences - repeated STR happens consecutively
            # Find the next STR sequence that happens repeatedly from previous STR sequence
            elif (position != -1) and ((position - len(str_sequence)) == prev_position):
                counter += 1
                prev_position = position
                if maxcounter < counter: #update max counter
                    maxcounter = counter

            #Increment position after each turn after counting
            position += 1

        #Save the max counter into value list
        valuelist.append(maxcounter)

    # Match STRs in DNA file with database file
    # Use str() to convert data in valuelist into list of strings for comparison
    # Note: map() is to run 1 function for each element in the list
    valuelist = list(map(str, valuelist))
    
    #Copy of database data and save into new list
    database_copy = list(database_file) #list of each row
    database_copy.pop(0) #remove the first index (header)
    
    # Compare valuelist to database_copy, print name if found

    # Iterate over each row after the header in the csv
    for person in database_copy:
        if person[1:] == valuelist: #omit the first element because it's the name of the person
            print(f"{person[0]}")
            break
        
    # https://docs.python.org/3/reference/index.html
    # In Python, if you are using else statement after the loop…
    # The else-block will not be executed if the break statement is executed inside the loop
    else:
        print("No match")


